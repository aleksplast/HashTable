section .text

global MurMurHashAsm

; rdi  = string
; rsi = len

MurMurHashAsm:
        push rbx

        mov ebx, esi            ; seed ^ lenght
        xor eax, eax

.Next:  imul eax, dword [rdi], BASE     ; curr *= base
        mov ecx, eax
        shr ecx, 24             ; curr >> shift

        xor eax, ecx            ; curr ^= curr >> shift

        imul ebx, ebx, BASE     ; hash *= base
        xor ebx, eax            ; hash ^= curr
        add rdi, 4              ; buffer += 4
        sub rsi, 4              ; lenght -= 4

        cmp rsi, 4              ; while (lenght >= 4)
        jge .Next

        mov eax, ebx            ; hash in rax
        xor ebx, ebx

        cmp rsi, 3
        je .Three
        cmp  rsi, 2
        je .Two

        jmp .Done

.Three: movzx ebx, byte [rdi + 2]  ; buffer[2]
        sal ebx, 16             ; buffer[2] << 16
        xor eax, ebx            ; hash ^= buffer[2] << 16
        xor ebx, ebx


.Two:   movzx ebx, byte [rdi + 1]  ; buffer[1]
        sal ebx, 8              ; buffer[1] << 8
        xor eax, ebx            ; hash ^= buffer[1] << 8
        xor ebx, ebx

.Done:  movzx ebx, byte [rdi]      ; buffer[0]
        xor ebx, ebx            ; hash ^= buffer[0]
        imul eax, eax, BASE     ; hash *= r12

        mov ebx, eax            ; hash in rbx
        shr ebx, 13             ; hash >> 13
        xor eax, ebx            ; hash ^= hash >> 13

        imul eax, eax, BASE     ; hash *= base
        mov ebx, eax            ; hash in rbx
        shr ebx, 15             ; hash >> 15
        xor eax, ebx            ; hash ^= hash >> 15

        pop rbx
        ret

.data

BASE equ 0x5bd1e995
