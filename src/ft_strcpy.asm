global ft_strcpy

section .text

ft_strcpy:
    mov rax, rdi
    xor rcx, rcx

.loop:
    mov dl, [rsi + rcx]
    mov [rdi + rcx], dl
    test dl, dl
    jz .end
    inc rcx
    jmp .loop

.end:
    ret