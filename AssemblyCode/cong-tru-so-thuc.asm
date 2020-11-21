# Chuong trinh cong tru 2 so thuc dang chuan voi do chinh xac don
# Input: 2 so thuc A, B
# Output: ket qua phep cong, tru 2 so thuc

################################# Data segment ###########################
.data
	nhapa: .asciiz "Nhap so thuc A: "
	nhapb: .asciiz "Nhap so thuc B: "
	kqcong: .asciiz "A + B = "
	kqtru: .asciiz "\nA - B = "
	loi: .asciiz "Loi! Gia tri nhap vuot nguong!"
	kqloi: .asciiz "!!! Vuot nguong !!!"
	
################################ Text segment #############################
# 2 so thuc truyen vao $s0, $s1
# ket qua phep cong truyen vao $t8
# ket qua phep tru truyen vao $t9

.text
.globl main
main:

	# In ra chu " nhap A " 
	la $a0, nhapa
	li $v0, 4
	syscall
	
	li $v0, 6 #nhap so thuc , f0 chua gia tri
	syscall

	mfc1 $s0, $f0 		# dua A vao $s0
	
	# nhap B
	la $a0, nhapb
	li $v0, 4
	syscall
	
	li $v0, 6
	syscall

	mfc1 $s1, $f0 		# dua B vao $s1
	
	# lay bit dau:	A -> $s2 ; B -> $s5
	li $s2, 0 
	srl $s2, $s0, 31	# dua bit dau cua A vao $s2
	li $s5, 0
	srl $s5, $s1, 31	#dua bit dau cua B vao $s5
	
	# lay exponent:	A -> $s3 ; B -> $s6
	li $t4, 255 #t4 = 255
	li $s3, 0 
	sll $s3, $s0, 1
	srl $s3, $s3, 24	# dua exponent cua A vao $s3
	beq $s3, $t4, loinhap	# kiem tra A
	
	li $s6, 0
	sll $s6, $s1, 1
	srl $s6, $s6, 24	# dua exponent cua B vao $s6
	beq $s6, $t4, loinhap	# kiem tra B
	
	# lay 1.fraction:	A -> $s4 ; B -> $s7
	li $t0, 1
	sll $t0, $t0, 23 #????????????
	
	li $s4, 0
	beqz $s0, A0		# A = 0 -> $s4 = 0
	sll $s4, $s0, 9	        #s:1 bit  E:8 bit Frac:23 bit
	srl $s4, $s4, 9		# dua fraction cua A vao $s4
	or $s4, $s4, $t0	# cong 1 -> A tro thanh 1.fraction

A0:	li $s7, 0
	beqz $s1, B0		# B = 0 -> $s7 = 0
	sll $s7, $s1, 9
	srl $s7, $s7, 9		# dua fraction cua B vao $s7
	or $s7, $s7, $t0	# cong 1 -> B tro thanh 1.fraction
B0:	
	# dieu chinh dau cham
	bgt $s6, $s3, Blon
	
Alon:	beq $s3, $s6, dieuchinh	# while (exponentA > exponentB) dieu chinh exponentB
	addi $s6, $s6, 1 #e cua B tang 1
	srl $s7, $s7, 1 #bit cua b qua phai 1
	j Alon
	
Blon:	beq $s3, $s6, dieuchinh	# while (exponentB > exponentA) dieu chinh exponentA
	addi $s3, $s3, 1
	srl $s4, $s4, 1
	j Blon
dieuchinh:			# hoan tat dieu chinh
# $s3, $s6 o dang m.n voi m la bit 9 bit dau va n la 23 bit cuoi

	li $t5, 0		# $t5 xac dinh phep toan cong hay tru
	# thuc hien phep cong, gan vao $t8
	
	la $a0, kqcong		# in ket qua cong
	li $v0, 4
	syscall
	
thuchien:
	move $t1, $s3		# gan exponent cua ket qua cho $t1
	bne $s2, $s5, khacdau	
				# A va B cung dau
	move $t0, $s2		# gan bit dau cua ket qua cho $t0
	add $t2, $s4, $s7	# $t2: he so cua ket qua
	j chuanhoacong
	
khacdau:			# A va B khac dau
	blt $s4, $s7, Anho
				# |A| >= |B|
	move $t0, $s2		# gan bit dau cua ket qua cho $t0
	sub $t2, $s4, $s7	# $t2: he so cua ket qua
	j chuanhoacong
Anho:				# |a| < |B|
	move $t0, $s5		# gan bit dau cua ket qua cho $t0
	sub $t2, $s7, $s4	# $t2: he so cua ket qua

chuanhoacong:			# chuan hoa ket qua
	beqz $t2, bang0
	srl $t3, $t2, 23	# $t3: phan nguyen cua he so ket qua
	beqz $t3, giam
	
tang:	srl $t3, $t3, 1
	beqz $t3, cong
	srl $t2, $t2, 1
	addi $t1, $t1, 1
	j tang

giam:	sll $t2, $t2, 1
	srl $t3, $t2, 23
	addi $t1, $t1, -1
	bnez $t3, cong
	j giam
	
cong:				# chuyen ket qua vao $t8
	beq $t1, $t4, loikq	# kiem tra ket qua
	sll $t0, $t0, 31
	sll $t1, $t1, 23
	sll $t2, $t2, 9
	srl $t2, $t2, 9
	j in
	
bang0:	li $t0, 0
	li $t1, 0
	li $t2, 0
	
in:	bnez $t5, pheptru
	or $t8, $t0, $t1
	or $t8, $t8, $t2
	
	mtc1 $t8, $f12
	li $v0, 2
	syscall
	
	j tru
	
loikq:	la $a0, kqloi
	li $v0, 4
	syscall
	
	bnez $t5, ketthuc
	
	# thuc hien phep tru, gan vao $t9
	
tru:	la $a0, kqtru		# in ket qua tru
	li $v0, 4
	syscall
	
	not $s5, $s5
	andi $s5, $s5, 1
	li $t5, 1
	j thuchien		# doi dau cua B va thuc hien phep cong:  A + (-B)
pheptru:
	or $t9, $t0, $t1
	or $t9, $t9, $t2
	
	mtc1 $t9, $f12
	li $v0, 2
	syscall
	j ketthuc
	
loinhap:
	la $a0, loi
	li $v0, 4
	syscall
	
ketthuc:			# ket thuc chuong trinh
	li $v0, 10		
	syscall
