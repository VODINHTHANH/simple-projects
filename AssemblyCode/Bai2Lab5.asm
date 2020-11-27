.data
array: .float 6.28, 3.14
endLine: .asciiz "\n"
.text
###Chu vi
li $v0, 6 #nhap so thuc , f0 chua gia tri
syscall
mov.s $f2, $f0
la $t1, array #t1 chi vao array
l.s $f1, 0($t1) #f1 = 6.28
mul.s $f0, $f0, $f1 #f0 = f0*f1
mov.s $f12, $f0
li $v0, 2
syscall
la $a0, endLine
li $v0, 4
syscall
###Dien tich
l.s $f1, 4($t1) #f1 = 3.14
mul.s $f0, $f2, $f2
mul.s $f0, $f0, $f1
mov.s $f12, $f0
li $v0, 2
syscall
li $v0, 10
syscall
