.data
array: .word 5, 9, 7
.text
addi $a1, $zero, 3 #size of array
jal range
move $a0, $v0 #print range of array
li $v0, 1
syscall
li $v0, 10
syscall

range:
addi $sp, $sp, -4
sw $ra, 0($sp) # luu lai dia chi ve main
jal min
move $t5, $v0, #min = t5
jal max
move $t6, $v0 #max = t6
sub $v0, $t6, $t5 #range = max - min
lw $ra, 0($sp) #lay lai dia chi ve main
addi $sp, $sp, 4
jr $ra

min:
li $t0, 0 #t1= bien dem
li $t1, 0 #Location of array
lw $t3, array($t1) #min = t3
loop:
bge $t0, $a1, final #bien dem = size dung lai
lw $t2, array($t1) #t2 = array[i]
blt $t2, $t3, new_min
j update
new_min:
move $t3, $t2
update:
addi $t1, $t1, 4
addi $t0, $t0, 1
j loop
final:
move $v0, $t3
jr $ra

max:
li $t0, 0 #t1= bien dem
li $t1, 0 #Location of array
lw $t3, array($t1) #min = t3
loop_max:
bge $t0, $a1, final_max #bien dem = size dung lai
lw $t2, array($t1) #t2 = array[i]
bgt $t2, $t3, new_max
j update_max
new_max:
move $t3, $t2
update_max:
addi $t1, $t1, 4
addi $t0, $t0, 1
j loop_max
final_max:
move $v0, $t3
jr $ra