%include "io.inc"

%define NUM_FIBO 10

section .text
global CMAIN
CMAIN:
    mov ebp, esp

    ; TODO - replace below instruction with the algorithm for the Fibonacci sequence
    mov ecx, NUM_FIBO
    mov eax, 1
    mov edx, 0
    push edx
    push eax
while:
    pop eax
    pop edx
    push edx
    push eax
    add edx, eax
    ;push eax
    push edx
    loop while
    
    mov ecx, NUM_FIBO
print:
    PRINT_UDEC 4, [esp + (ecx - 1) * 4]
    PRINT_STRING " "
    dec ecx
    cmp ecx, 0
    ja print

    mov esp, ebp
    xor eax, eax
    ret
