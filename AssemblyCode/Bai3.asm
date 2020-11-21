.data
    n1: .asciiz "Enter a: "
    n2: .asciiz "Enter b: "
    n3: .asciiz "Enter c: "
    n4: .asciiz "Enter d: "
    n5: .asciiz "Enter x: "
    result: .asciiz "f = a.x^3 - b.x^2 + c.x - d = "

.text
        #getting first input.
    la $a0, n1
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $s0, $v0
    #getting second input.
    la $a0, n2
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $s1, $v0
    #getting third input.
    la $a0, n3
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $s2, $v0
    #getting fourth input.
    la $a0, n4
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $s3, $v0
    #getting fourth input.
    la $a0, n5
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $s4, $v0
    #calculate and print out the result.
    la $a0, result
    li $v0, 4
    syscall
    
    mul $t0, $s0, $s4
    sub $t0, $t0, $s1
    mul $t0, $t0, $s4
    add $t0, $t0, $s2
    mul $t0, $t0, $s4
    sub $t0, $t0, $s3
    move $s0, $t0
    move $a0, $s0
    li $v0, 1
    syscall

    #end program.
    li $v0, 10
    syscall
