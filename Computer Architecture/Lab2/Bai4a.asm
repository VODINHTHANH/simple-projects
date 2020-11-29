.data
     list: .word 3, 0, -2, 2, 6, 4, 4, 7, 3, 7
     n1: .asciiz "Hieu cua phan tu thu 2 va 5 la: "
.text
    la $t0, list
    lw $t1, 8($t0)
    lw $t2, 20($t0)
    sub $t2, $t1,$t2
    move $s0, $t2
    la $a0, n1
    li $v0, 4
    syscall
    move $a0, $s0
    li $v0, 1
    syscall

    #end program.
    li $v0, 10
    syscall
