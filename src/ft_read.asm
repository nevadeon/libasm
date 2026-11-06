global ft_read
extern __errno_location

%define ERROR_MIN -4095
%define ERROR_RETURN_VALUE -1

section .text

ft_read:
    xor rax, rax
    syscall
    cmp rax, ERROR_MIN
    jb .end
    push rax
    call __errno_location wrt ..plt
    pop rdx
    neg rdx
    mov [rax], edx  
    mov rax, ERROR_RETURN_VALUE

.end:
    ret