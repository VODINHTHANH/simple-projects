.data
message: .asciiz " Enter input:"
message1: .asciiz " Gia tri a sau khi tinh toan:"
.text
ori $t1, 0 #t1 = a = 0
ori $t2, 100 #t2 = b = 100
ori $t3, 4 #t3 = c = 4
la $a0, message      #print out message
li $v0, 4
syscall
li $v0, 5       # read user input (integer)
syscall
move $t0,$v0 #t0 = intput
########################
beq $t0, 1, IM1
beq $t0, 2, IM2
beq $t0, 3, IM3
beq $t0, 4, IM4

j BREAK
IM4:
div $t1, $t2, $t3
j BREAK
IM3:
mul $t1, $t2, $t3
j BREAK
IM2:
sub $t1, $t2, $t3
j BREAK
IM1:
add $t1, $t2, $t3
j BREAK
BREAK:
la $a0, message1      #print out message
li $v0, 4
syscall
move $a0, $t1
li $v0, 1
syscall
li $v0, 10
syscall
