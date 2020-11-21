 .data
 message: .asciiz " Enter a:"
 string: .asciiz  "Computer Science and Engineering, HCMUT"
 string1: .asciiz "Computer Architecture 2020"
.text

la $a0, message      #print out message
li $v0, 4
syscall

li $v0, 5       # read user input (integer)
syscall

move $t0,$v0          # t0 = a

andi $t1 , $t0 , 0x0001 #
bgtz $t1, LE
la $a0, string1      #print out message
li $v0, 4
syscall
b ENDIF
LE:
la $a0, string      #print out message
li $v0, 4
syscall
ENDIF:

li $v0,10
syscall

