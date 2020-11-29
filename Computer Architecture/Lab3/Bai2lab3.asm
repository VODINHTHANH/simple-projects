 .data
 message: .asciiz " Enter a:"
 message1: .asciiz " Enter b:"
 message2: .asciiz " Enter c:"
 message3: .asciiz " Lenh a sau khi tinh toan la: "
.text

la $a0, message      #print out message
li $v0, 4
syscall
li $v0, 5       # read user input (integer)
syscall
move $t0,$v0          # t0 = a
#############
la $a0, message1      #print out message
li $v0, 4
syscall

li $v0, 5       # read user input (integer)
syscall

move $t1,$v0          # t1 = b

la $a0, message2      #print out message
li $v0, 4
syscall

li $v0, 5       # read user input (integer)
syscall

move $t2,$v0          # t2 = c
#############
add $t3, $t0, 5 #t0 = t0 + 5
add $t4, $t0, -3 
bltz $t3, L1
bltz $t4, ELSE

L1:
mul $t0, $t1, $t2
j ENDIF
ELSE:
add $t0 ,$t1,$t2	
ENDIF:


la $a0, message3      #print out result
li $v0, 4
syscall
move $a0, $t0
li $v0, 1
syscall

li $v0,10
syscall

