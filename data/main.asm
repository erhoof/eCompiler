    ; asm file generated by eCompiler from ../data/main.ts
section .text
    global main
    extern printf
    extern scanf
    
section .bss    ; uninitialized variables
    i resb 4
    j resb 1
section .data    ; strings and other big stuff
    line0 db 'Hello, World!'
    lenLine0 equ $-line0
    fmtd db '%d', 10, 0
    fmtf db '%f', 10, 0
    fmtc db '%c', 10, 0
    fmtb db '%d', 10, 0
    fmtdi db '%d', 0
    fmtci db '%c', 0
    fmtbi db '%d', 0
    
main:
L1:
    mov eax, [j]
    or eax, 0x01
    mov [j], eax
L3:
    mov eax, [j]
    cmp eax, 0x01
    jne L2
L4:
    mov eax, 4
    mov ebx, 1
    mov ecx, line0
    mov edx, lenLine0
    int 80h
L2:
    mov eax, 1
    mov ebx, 0
    int 80h
