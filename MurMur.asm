section .text

global MurMurHashAsm

; rdi  = string
; rsi = len

MurMurHashAsm:
        push r12
        push rbx

        xor rbx, rbx            ; seed
        mov r12, 0x5bd1e995     ; base

        xor rbx, rsi

.Next:  mov rax, [rdi]          ; curr = buffer

        mul r12
        mov r10, rax
        shl r10, 24

        xor rax, r12
        xchg rax, rbx

        mul r12
        xor rax, rbx
        add rdi, 4
        sub rsi, 4
        mov rbx, rax

        cmp rsi, 4
        jae .Next

        mov rax, rbx
        xor rbx, rbx

        cmp rsi, 3
        je .Three
        cmp  rsi, 2
        je .Two

        mov bl, byte [rdi]
        xor rax, rbx
        mul r12
        jmp .Done

.Three: mov bl, byte [rdi + 2]
        xor rbx, 16
        xor rax, rbx

        jmp .Done

.Two:   mov bl, byte [rdi + 1]
        shl rbx, 8
        xor rax, rbx

        jmp .Done

.Done:  mov rbx, rax
        shl rax, 13
        xor rax, rbx

        mul r12
        mov rbx, rax
        shl rbx, 15
        xor rax, rbx

        pop rbx
        pop r12

        ret

