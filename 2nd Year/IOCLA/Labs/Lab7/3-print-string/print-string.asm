%include "io.inc"
extern puts

section .data
    mystring db "This is my string", 10, 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    ; TODO: call puts on string

    push mystring
    call puts
    add esp, 4
    
    PRINT_STRING mystring


    leave
    ret
