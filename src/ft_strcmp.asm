global ft_strcmp

section .text

ft_strcmp:
    xor rcx, rcx

.loop:
    movzx eax, byte [rdi + rcx]
    cmp al, [rsi + rcx]
    jne .notequal
    test al, al
    jz .equal
    inc rcx
    jmp .loop

.notequal:
    movzx edx, byte [rsi + rcx]
    movzx eax, al
    sub eax, edx

.equal:
    ret