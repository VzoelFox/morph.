# N1 Parser - Assembly Implementation
# Bypass N0 parser limitations with direct assembly

.section .data
    # AST Node Types
    node_program: .quad 0
    node_var_statement: .quad 1
    node_function_statement: .quad 2
    node_expression_statement: .quad 3
    node_identifier: .quad 4
    node_integer_literal: .quad 5

.section .text
.global parser_new
.global parser_parse_program
.global parser_next_token

# Parser structure offsets
.equ PARSER_LEXER, 0
.equ PARSER_CURRENT_TOKEN, 8
.equ PARSER_PEEK_TOKEN, 16
.equ PARSER_ERRORS, 24

# AST Node structure offsets
.equ NODE_TYPE, 0
.equ NODE_TOKEN_LITERAL, 8
.equ NODE_LINE, 16
.equ NODE_COLUMN, 24

# parser_new(lexer) -> parser
parser_new:
    push %rbp
    mov %rsp, %rbp
    
    # Allocate parser struct (32 bytes)
    mov $32, %rdi
    call malloc
    mov %rax, %r8  # parser pointer
    
    # Set lexer
    mov %rdi, PARSER_LEXER(%r8)
    
    # Initialize tokens by calling next_token twice
    mov %r8, %rdi
    call parser_next_token
    mov %r8, %rdi
    call parser_next_token
    
    # Initialize error count
    movq $0, PARSER_ERRORS(%r8)
    
    mov %r8, %rax  # return parser
    pop %rbp
    ret

# parser_next_token(parser)
parser_next_token:
    push %rbp
    mov %rsp, %rbp
    mov %rdi, %r8  # parser pointer
    
    # current_token = peek_token
    mov PARSER_PEEK_TOKEN(%r8), %rax
    mov %rax, PARSER_CURRENT_TOKEN(%r8)
    
    # peek_token = lexer_next_token(lexer)
    mov PARSER_LEXER(%r8), %rdi
    call lexer_next_token
    mov %rax, PARSER_PEEK_TOKEN(%r8)
    
    pop %rbp
    ret

# parser_parse_program(parser) -> program_node
parser_parse_program:
    push %rbp
    mov %rsp, %rbp
    push %rbx
    mov %rdi, %rbx  # parser pointer
    
    # Allocate program node (32 bytes)
    mov $32, %rdi
    call malloc
    mov %rax, %r9  # program node
    
    # Set node type
    mov node_program(%rip), %rdx
    mov %rdx, NODE_TYPE(%r9)
    
    # Set token literal
    mov $program_literal, %rdx
    mov %rdx, NODE_TOKEN_LITERAL(%r9)
    
    # Parse statements loop
.parse_loop:
    # Check if current token is EOF
    mov PARSER_CURRENT_TOKEN(%rbx), %rax
    mov TOKEN_TYPE(%rax), %rdx
    cmp token_eof(%rip), %rdx
    je .parse_done
    
    # Parse statement (simplified - just advance for now)
    mov %rbx, %rdi
    call parser_next_token
    
    jmp .parse_loop
    
.parse_done:
    mov %r9, %rax  # return program node
    pop %rbx
    pop %rbp
    ret

# parser_parse_var_statement(parser) -> var_node
parser_parse_var_statement:
    push %rbp
    mov %rsp, %rbp
    
    # Allocate var statement node
    mov $32, %rdi
    call malloc
    mov %rax, %r8
    
    # Set node type
    mov node_var_statement(%rip), %rdx
    mov %rdx, NODE_TYPE(%r8)
    
    mov %r8, %rax
    pop %rbp
    ret

# parser_parse_identifier(parser) -> identifier_node
parser_parse_identifier:
    push %rbp
    mov %rsp, %rbp
    
    # Allocate identifier node
    mov $32, %rdi
    call malloc
    mov %rax, %r8
    
    # Set node type
    mov node_identifier(%rip), %rdx
    mov %rdx, NODE_TYPE(%r8)
    
    mov %r8, %rax
    pop %rbp
    ret

.section .rodata
program_literal: .asciz "program"
