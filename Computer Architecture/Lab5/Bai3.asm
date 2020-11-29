.data
array: .float 4.5, 7.8, 3.7
xuongH: .asciiz "\n"
.text
#print array
    la      $t1, array
loop1:
    bge     $t0, 3, exit

    # load word from addrs and goes to the next addrs
    lwc1    $f0, 0($t1)
    addi    $t1, $t1, 4

    # syscall to print value
    mov.s    $f12, $f0
    li      $v0, 2     
    syscall
    # optional - syscall number for printing character (space)
    li      $a0, 32
    li      $v0, 11  
    syscall


    #increment counter
    addi    $t0, $t0, 1
    j      loop1
exit:
la $a0, xuongH
li $v0, 4
syscall
#END PRINT ARRAY
#Find MIN
la $t1, array  #t1 = array
addi $t5, $zero, 3 #size of array
li $t0, 0 #t1= bien dem
lwc1 $f0, 0($t1) #min = t3
loop:
bge $t0, $t5, keepFindMax #bien diem = size keep find max
lwc1 $f1, 0($t1) #f1 = array[i]
c.lt.s $f1, $f0
bc1t new_min
j update
new_min:
mov.s $f0, $f1
update: #update iterator and count
addi $t1, $t1, 4
addi $t0, $t0, 1
j loop
#END FIND MIN
keepFindMax:
#Find MAX
la $t1, array  #t1 = array
addi $t5, $zero, 3 #size of array
li $t0, 0 #t1= bien dem
lwc1 $f1, 0($t1) #max = t3
loopMax:
bge $t0, $t5, endProgram #bien diem = size keep find max
lwc1 $f2, 0($t1) #f1 = array[i]
c.lt.s $f2, $f1
bc1f new_max
j updateMax
new_max:
mov.s $f1, $f2
updateMax: #update iterator and count
addi $t1, $t1, 4
addi $t0, $t0, 1
j loopMax
#END FIND MAX
endProgram:
mov.s $f12, $f0########
li $v0, 2
syscall#############

la $a0, xuongH
li $v0, 4
syscall

mov.s $f12, $f1
li $v0, 2
syscall

li $v0, 10
syscall
