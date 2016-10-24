.data
	g: .word 4 # initial value of variable g
	h: .word 5 # initial value of variable h
	i: .word 1 # initial value of variable i
	j: .word 2 # initial value of variable j
	f: .space 4 # declare 4 bytes of storage to hold integer result
 
 .text
 main:
 	#Store arguments g-j into a-a3
 	lw $a0,  g 
 	lw $a1, h
 	lw $a2, i
 	lw $a3, j
 	
  	jal leaf_example #Function call that jumps and links
  	#addi f, $zero $v0
	
	li $v0, 1 
	addi $a0, $s0, 0
	syscall
	
	li $v0, 10
	syscall

#Function that does f = (g+h) - (i-j)
leaf_example: 
		lw $s0, f
		add $v0, $a0, $a1
		add $s0, $a2, $a3
		sub $s0, $v0, $s0
		jr $ra
