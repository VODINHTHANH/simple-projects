.data
.align 1
String: .asciiz "Computer Architecture 2020" 
msg1: .asciiz "Pls give a character: "
msg2: .asciiz "\n"
msg3: .asciiz "String is: "
msg4: .asciiz "\nString Reversed is: "
.text
.globl main
main:

la $a0,String #a0 = parameter for fc
addi $a1,$zero, 26#pass length-*change parameter a1 = size = 14
jal stringreverse #reverse

la $a0,msg4
li $v0,4
syscall #print "string reversed is: "

la $a0,String
li $v0,4
syscall #print string

li $v0,10
syscall #end program


stringreverse:

add $t0,$a0,$zero #beginning address

add $t1,$zero,$zero  #i=0
addi $t2,$a1,-1   #j=length-1

loop:

add $t3,$t0,$t1
lb $t4,0($t3) #lb String[i]

add $t5,$t0,$t2
lb $t6,0($t5) #lb String[j]

sb $t4,0($t5) #String[j]=String[i]
sb $t6,0($t3) #String[i]=String[j]

addi $t1,$t1,1 #i++
addi $t2,$t2,-1 #j--
#if i>=j break - $t1<$t2
slt $t6,$t2,$t1
beqz $t6,loop

jr $ra

#i-0;j=length-1;
# do {
# x = str[i]
# str[i]=str[j]
# str[j] = x
# i++;j--;
# } while(!(j<i))