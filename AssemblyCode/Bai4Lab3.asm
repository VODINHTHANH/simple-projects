.data
message: .asciiz " Enter n:"
message1: .asciiz " Gia tri fibo thu n:"
.text

la $a0, message      #print out message
li $v0, 4
syscall
li $v0, 5       # read user input (integer)
syscall
move $t0,$v0 #t0 = n
########################
ori $t4,0 #fn
beq $t0, 0, END0
beq $t0, 1, END1
ori $t2, 0 #t2 = f0 = 0
ori $t3, 1 #t3 = f1 = 1
ori $t1, 2 #t1 = i = 2

LOOP:
add $t4, $t2, $t3
add $t2, $zero, $t3
add $t3, $zero, $t4
addi $t1,$t1,1
ble $t1,$t0, LOOP
j END0
END1:
addi $t4, $t4, 1
END0:
la $a0, message1      #print out message
li $v0, 4
syscall
move $a0, $t4
li $v0, 1
syscall
li $v0, 10
syscall
