.data
    n1: .asciiz "Enter a: "
    n2: .asciiz "Enter b: "
    n3: .asciiz "Enter c: "
    result: .asciiz "(a-b)+c = "

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
    #getting first input.
    la $a0, n3
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $s3, $v0
    #calculate and print out the result.
    la $a0, result
    li $v0, 4
    syscall
    sub $t3, $s0, $s1
    add $s4, $t3,$s3
    move $a0, $s4
    li $v0, 1
    syscall

    #end program.
    li $v0, 10
    syscall
