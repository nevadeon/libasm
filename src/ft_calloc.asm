global ft_calloc
extern malloc
extern __errno_location

%define ENOMEM 12

section .text

ft_calloc:
    mov rax, rdi
    mul rsi
    test rdx, rdx
    jnz .error

    mov rdi, rax
    push rax
    call malloc wrt ..plt
    pop rcx
    test rax, rax
    jz .end

.zeroing_loop:
    test rcx, rcx
    jz .end
    dec rcx
    mov byte [rax + rcx], 0
    jmp .zeroing_loop

.error:
    sub rsp, 8
    call __errno_location wrt ..plt
    add rsp, 8
    mov dword [rax], ENOMEM
    xor rax, rax

.end:
    ret