section .note.morph
    db 'V', ' ', 'Z', ' ', 'O', ' ', 'E', ' ', 'L', ' ', 'F', ' ', 'O', ' ', 'X', 'S'
section .text
    global _start
_start:
    call main
    mov rdi, rax
    mov rax, 60
    syscall
main:
    push rbp
    mov rbp, rsp
    mov rax, 42
    pop rbp
    ret
    pop rbp
    ret
