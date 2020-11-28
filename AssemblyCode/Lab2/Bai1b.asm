.data 
out_string: .asciiz "Kien Truc May Tinh 2020"
.text 
li $v0, 4 
la $a0, out_string
syscall 
li $v0, 10
syscall
