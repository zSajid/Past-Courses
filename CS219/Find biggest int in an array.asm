
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h


    MOV BX, OFFSET IntArray
    MOV CL,0
    MOV DL,0
    MOV si, 0
       
    MOV CX, [BX+si] ; This takes the value of the current array pos                    

    ; Start of the main code
    mainCode:
    
    ; Compares the size of the array and the increment counter                  
    CMP SizeA, si            
    je f
    
    
    ; This is a portion of the code that increments the array and then adds 
    ; values of the array to the variables and compares them            
    a:            
        INC BX ; This increments the current array pos 
    
        MOV Ax, [BX+si] ; This takes the value of the second array pos
        

        ; If the comparison shows that AX is greater than CX, then we move
        ; and change the value of CX to AX and go back into the loop
        CMP AX, CX                                                 
        JA b 
        
        ; This is another situation in which if JA B always comes true
        CMP AX, CX
        JMP f
           
        b:
           MOV CX, AX
           ADD si, 1

           jmp mainCode 
        
    f:
MOV MAXV, CX ; This is just moving the biggest value of CX into MAXV 
RET
SizeA DW 10
MAXV DW 0
IntArray DW 0x1,0x2, 0x4,0xFF,0xFE,0xFA,0x7,0x9,0x8,0xFD

X DW 0
Y DW 0

                       
                       