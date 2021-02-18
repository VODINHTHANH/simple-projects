.data
.text
    ori $t0, 100000
    addiu $t0, $t0, 5000
    subiu $t0, $t0, 400
    move $s0, $t0 
    move $a0, $s0
    li $v0, 1
    syscall 
    li $v0, 10
    syscall
