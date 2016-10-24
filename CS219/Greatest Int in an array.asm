
.data #What we store into this
IntArray: .word 0x1,0x2,0x4,0xFF,0xFE,0xFA,0x7,0x9,0x8,0xFD # initial values of
# integer array
size: .word 10 # number of integers in IntArray
result: .space 4 # declare 4 bytes of storage to hold integer result (greatest integer)

age: .word 23
message : .asciiz "The number"

.text
main:
	addi $t0, $zero, 0 #This is to start the array position at 0
	
	sw $t1, IntArray($t0) #This stores the first element into t1 register

while: 
	beq $t0, 40, exit # This is a branching condition in which it test if the number of bytes for $t0 will be equal to 40

	addi $t0, $t0, 4 #Increments the thing by 4 bytes
	
	lw $t2, IntArray($t0) #This gets the current element in the array at whatever byte it's on
	#addi $t2, $zero, 30
	
	bgt $t2, $t1, ifGreater #Branch to ifGreater if t2 is greater than t1

	
	j while
	
ifGreater:
	move $t1, $t2 #Copy the value of t2 into t1
	j while #Go back to jump while loop could use jr as well
	
#This is to exit the program and print the greastest int in the function	
exit:

	li $v0, 1 #This tells the system we need to print something out
	
	move $a0, $t1

	syscall
