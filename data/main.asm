    ; asm file generated by eCompiler from ../data/main.ts
section .text
    global main
    extern printf
    
section .bss    ; uninitialized variables
    t1 resb 4
    t2 resb 4
    i resb 20
section .data    ; strings and other big stuff
    fmtd db '%d', 10, 0
    fmtf db '%f', 10, 0
    fmtc db '%c', 10, 0
    fmtb db '%d', 10, 0
    
main:
L1:
    mov eax, 0
    mov ebx, 4
    imul eax, ebx
    mov [t1], eax
    mov eax, 10
    mov ebx, [t1]
    mov dword [i + ebx * 4], eax
L3:
    mov eax, 0
    mov ebx, 4
    imul eax, ebx
    mov [t2], eax
    mov eax, [t2]
    mov ebx, dword [i + eax * 4]
    mov eax, ebx
    push eax
    push fmtd
    call printf
    add esp, 8
L2:
    mov eax, 1
    mov ebx, 0
    int 80h
