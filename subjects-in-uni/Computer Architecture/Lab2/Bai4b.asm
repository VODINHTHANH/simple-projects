.data
     n1: .asciiz "1912041 - Vo Dinh Thanh"
.text
    la $t0, n1
    lb $t1, 0($t0) #t1 = 1
    lb $t2, 22($t0) #t2 = h
    sb $t1, 22($t0) #1912041 - Vo Dinh Than1
    sb $t2, 0($t0)#h912041 - Vo Dinh Than1
    la $a0, n1
    li $v0, 4
    syscall

    #end program.
    li $v0, 10
    syscall
