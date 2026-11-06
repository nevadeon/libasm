global ft_strdup
extern ft_strlen
extern ft_strcpy
extern malloc

section .text

ft_strdup:
    push rdi
    call ft_strlen

    mov rdi, rax
    inc rdi
    call malloc wrt ..plt
    pop rsi
    test rax, rax
    jz .end

    mov rdi, rax
    sub rsp, 8
    call ft_strcpy
    add rsp, 8

.end:
    ret