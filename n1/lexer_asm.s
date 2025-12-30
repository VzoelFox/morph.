# N1 Lexer - Assembly Workarounds for N0 Limitations
# Direct assembly implementation to bypass N0 parser issues

.section .data
    token_eof: .quad 0
    token_ident: .quad 1
    token_int: .quad 2
    token_plus: .quad 3
    token_minus: .quad 4
    token_assign: .quad 5
    token_lparen: .quad 6
    token_rparen: .quad 7
    token_lbrace: .quad 8
    token_rbrace: .quad 9
    token_string: .quad 10
    token_float: .quad 11

.section .text
.global lexer_next_token
.global lexer_new
.global lexer_read_char

# Lexer structure offsets
.equ LEXER_INPUT, 0
.equ LEXER_POSITION, 8
.equ LEXER_READ_POSITION, 16
.equ LEXER_CH, 24
.equ LEXER_LINE, 32
.equ LEXER_COLUMN, 40

# Token structure offsets  
.equ TOKEN_TYPE, 0
.equ TOKEN_LITERAL, 8
.equ TOKEN_LINE, 16
.equ TOKEN_COLUMN, 24

# lexer_new(input_string) -> lexer
lexer_new:
    push %rbp
    mov %rsp, %rbp
    
    # Allocate lexer struct (48 bytes)
    mov $48, %rdi
    call malloc
    mov %rax, %r8  # lexer pointer
    
    # Initialize lexer fields
    mov %rdi, LEXER_INPUT(%r8)     # input string
    movq $0, LEXER_POSITION(%r8)   # position = 0
    movq $0, LEXER_READ_POSITION(%r8) # read_position = 0
    movq $0, LEXER_CH(%r8)         # ch = 0
    movq $1, LEXER_LINE(%r8)       # line = 1
    movq $0, LEXER_COLUMN(%r8)     # column = 0
    
    # Call read_char
    mov %r8, %rdi
    call lexer_read_char
    
    mov %r8, %rax  # return lexer
    pop %rbp
    ret

# lexer_read_char(lexer)
lexer_read_char:
    push %rbp
    mov %rsp, %rbp
    mov %rdi, %r8  # lexer pointer
    
    # Get input string and read_position
    mov LEXER_INPUT(%r8), %rsi
    mov LEXER_READ_POSITION(%r8), %rdx
    
    # Check if read_position >= strlen(input)
    mov %rsi, %rdi
    call strlen
    cmp %rax, %rdx
    jge .read_char_eof
    
    # Get character at read_position
    add %rdx, %rsi
    movzbl (%rsi), %eax
    mov %rax, LEXER_CH(%r8)
    jmp .read_char_update
    
.read_char_eof:
    movq $0, LEXER_CH(%r8)
    
.read_char_update:
    # position = read_position
    mov LEXER_READ_POSITION(%r8), %rax
    mov %rax, LEXER_POSITION(%r8)
    
    # read_position++
    inc %rax
    mov %rax, LEXER_READ_POSITION(%r8)
    
    # Update line/column
    mov LEXER_CH(%r8), %rax
    cmp $10, %rax  # '\n'
    jne .read_char_inc_col
    
    # Newline: line++, column = 0
    incq LEXER_LINE(%r8)
    movq $0, LEXER_COLUMN(%r8)
    jmp .read_char_done
    
.read_char_inc_col:
    incq LEXER_COLUMN(%r8)
    
.read_char_done:
    pop %rbp
    ret

# lexer_next_token(lexer) -> token
lexer_next_token:
    push %rbp
    mov %rsp, %rbp
    push %rbx
    mov %rdi, %rbx  # lexer pointer
    
    # Allocate token struct (32 bytes)
    mov $32, %rdi
    call malloc
    mov %rax, %r9  # token pointer
    
    # Skip whitespace
.skip_whitespace:
    mov LEXER_CH(%rbx), %rax
    cmp $32, %rax   # space
    je .skip_char
    cmp $9, %rax    # tab
    je .skip_char
    cmp $10, %rax   # newline
    je .skip_char
    cmp $13, %rax   # carriage return
    je .skip_char
    jmp .tokenize
    
.skip_char:
    mov %rbx, %rdi
    call lexer_read_char
    jmp .skip_whitespace
    
.tokenize:
    # Get current line/column for token
    mov LEXER_LINE(%rbx), %rdx
    mov %rdx, TOKEN_LINE(%r9)
    mov LEXER_COLUMN(%rbx), %rdx
    mov %rdx, TOKEN_COLUMN(%r9)
    
    # Check character and create appropriate token
    mov LEXER_CH(%rbx), %rax
    
    cmp $43, %rax   # '+'
    je .token_plus
    cmp $45, %rax   # '-'
    je .token_minus
    cmp $61, %rax   # '='
    je .token_assign
    cmp $40, %rax   # '('
    je .token_lparen
    cmp $41, %rax   # ')'
    je .token_rparen
    cmp $123, %rax  # '{'
    je .token_lbrace
    cmp $125, %rax  # '}'
    je .token_rbrace
    cmp $0, %rax    # EOF
    je .token_eof_case
    
    # Default: identifier
    mov token_ident(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    jmp .create_literal

.token_plus:
    mov token_plus(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $plus_literal, %rdi
    jmp .set_literal

.token_minus:
    mov token_minus(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $minus_literal, %rdi
    jmp .set_literal

.token_assign:
    mov token_assign(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $assign_literal, %rdi
    jmp .set_literal

.token_lparen:
    mov token_lparen(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $lparen_literal, %rdi
    jmp .set_literal

.token_rparen:
    mov token_rparen(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $rparen_literal, %rdi
    jmp .set_literal

.token_lbrace:
    mov token_lbrace(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $lbrace_literal, %rdi
    jmp .set_literal

.token_rbrace:
    mov token_rbrace(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $rbrace_literal, %rdi
    jmp .set_literal

.token_eof_case:
    mov token_eof(%rip), %rax
    mov %rax, TOKEN_TYPE(%r9)
    mov $eof_literal, %rdi
    jmp .set_literal

.create_literal:
    mov $ident_literal, %rdi

.set_literal:
    mov %rdi, TOKEN_LITERAL(%r9)
    
    # Advance to next character
    mov %rbx, %rdi
    call lexer_read_char
    
    # Return token
    mov %r9, %rax
    pop %rbx
    pop %rbp
    ret

.section .rodata
plus_literal: .asciz "+"
minus_literal: .asciz "-"
assign_literal: .asciz "="
lparen_literal: .asciz "("
rparen_literal: .asciz ")"
lbrace_literal: .asciz "{"
rbrace_literal: .asciz "}"
eof_literal: .asciz ""
ident_literal: .asciz "ident"
