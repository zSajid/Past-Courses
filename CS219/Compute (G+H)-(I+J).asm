
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; Store all the values of g-j into data segment registers
Mov AX,4  
Mov BX, 5
Mov CX, 1
Mov DX, 2


; Compute g+H, and i+j
ADD AX, BX  
ADD CX, DX

; Subtract those two and stored it in AX
SUB AX, CX

; Return
RET






