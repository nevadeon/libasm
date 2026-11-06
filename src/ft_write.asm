global ft_write
extern __errno_location

%define WRITE_SYSCALL_NUMBER 1
%define ERROR_MIN -4095
%define ERROR_RETURN_VALUE -1

section .text

ft_write:
    mov rax, WRITE_SYSCALL_NUMBER
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