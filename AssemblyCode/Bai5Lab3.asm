.data
message: .asciiz  "Computr Architctur CSE-HCMUT"
e: .asciiz "e"
.text
la $t0, message #t0 = dia chi cua message
la $t4, e #
lb $t5, 0($t4) #t5 = "e"
addi $t3, $zero, 0 #t3 = i
L1:
lb $t2, 0($t0) #t2 = C
beq $t5, $t2 , end
beq $t2, $zero, endDiff
addiu $t3, $t3, 1
addiu $t0, $t0, 1
j L1



end:
move $a0,$t3
li $v0, 1
syscall
j endGame
endDiff:
addi $t3, $zero, -1
move $a0,$t3
li $v0, 1
syscall


endGame:
li $v0, 10
syscall
