# N1 AST - Assembly Implementation
# Direct memory management for AST nodes

.section .data
    # Node type constants
    .global AST_PROGRAM
    .global AST_VAR_STATEMENT
    .global AST_FUNCTION_STATEMENT
    .global AST_IDENTIFIER
    .global AST_INTEGER_LITERAL
    .global AST_STRING_LITERAL

    AST_PROGRAM: .quad 0
    AST_VAR_STATEMENT: .quad 1
    AST_FUNCTION_STATEMENT: .quad 2
    AST_IDENTIFIER: .quad 3
    AST_INTEGER_LITERAL: .quad 4
    AST_STRING_LITERAL: .quad 5

.section .text
.global ast_create_node
.global ast_create_program
.global ast_create_var_statement
.global ast_create_identifier

# Base AST node structure (32 bytes)
.equ AST_NODE_TYPE, 0
.equ AST_TOKEN_LITERAL, 8
.equ AST_LINE, 16
.equ AST_COLUMN, 24

# ast_create_node(type, literal, line, column) -> node
ast_create_node:
    push %rbp
    mov %rsp, %rbp
    
    # Save parameters
    push %rdi  # type
    push %rsi  # literal
    push %rdx  # line
    push %rcx  # column
    
    # Allocate node (32 bytes)
    mov $32, %rdi
    call malloc
    mov %rax, %r8  # node pointer
    
    # Restore parameters and set fields
    pop %rcx
    pop %rdx
    pop %rsi
    pop %rdi
    
    mov %rdi, AST_NODE_TYPE(%r8)
    mov %rsi, AST_TOKEN_LITERAL(%r8)
    mov %rdx, AST_LINE(%r8)
    mov %rcx, AST_COLUMN(%r8)
    
    mov %r8, %rax  # return node
    pop %rbp
    ret

# ast_create_program() -> program_node
ast_create_program:
    push %rbp
    mov %rsp, %rbp
    
    mov AST_PROGRAM(%rip), %rdi
    mov $program_str, %rsi
    mov $1, %rdx
    mov $1, %rcx
    call ast_create_node
    
    pop %rbp
    ret

# ast_create_var_statement(name, line, column) -> var_node
ast_create_var_statement:
    push %rbp
    mov %rsp, %rbp
    
    # Save name parameter
    push %rdi
    
    # Allocate extended var statement node (64 bytes)
    mov $64, %rdi
    call malloc
    mov %rax, %r8
    
    # Set base node fields
    mov AST_VAR_STATEMENT(%rip), %rdi
    mov %rdi, AST_NODE_TYPE(%r8)
    mov $var_str, %rdi
    mov %rdi, AST_TOKEN_LITERAL(%r8)
    mov %rsi, AST_LINE(%r8)
    mov %rdx, AST_COLUMN(%r8)
    
    # Set var-specific fields (name at offset 32)
    pop %rdi  # restore name
    mov %rdi, 32(%r8)
    
    mov %r8, %rax
    pop %rbp
    ret

# ast_create_identifier(name, line, column) -> identifier_node
ast_create_identifier:
    push %rbp
    mov %rsp, %rbp
    
    push %rdi  # save name
    
    # Allocate identifier node (64 bytes)
    mov $64, %rdi
    call malloc
    mov %rax, %r8
    
    # Set base fields
    mov AST_IDENTIFIER(%rip), %rdi
    mov %rdi, AST_NODE_TYPE(%r8)
    mov $identifier_str, %rdi
    mov %rdi, AST_TOKEN_LITERAL(%r8)
    mov %rsi, AST_LINE(%r8)
    mov %rdx, AST_COLUMN(%r8)
    
    # Set identifier name (at offset 32)
    pop %rdi
    mov %rdi, 32(%r8)
    
    mov %r8, %rax
    pop %rbp
    ret

# ast_create_integer_literal(value, line, column) -> integer_node
ast_create_integer_literal:
    push %rbp
    mov %rsp, %rbp
    
    push %rdi  # save value
    
    # Allocate integer literal node
    mov $64, %rdi
    call malloc
    mov %rax, %r8
    
    # Set base fields
    mov AST_INTEGER_LITERAL(%rip), %rdi
    mov %rdi, AST_NODE_TYPE(%r8)
    mov $integer_str, %rdi
    mov %rdi, AST_TOKEN_LITERAL(%r8)
    mov %rsi, AST_LINE(%r8)
    mov %rdx, AST_COLUMN(%r8)
    
    # Set integer value (at offset 32)
    pop %rdi
    mov %rdi, 32(%r8)
    
    mov %r8, %rax
    pop %rbp
    ret

# ast_print_node(node) - Debug function
ast_print_node:
    push %rbp
    mov %rsp, %rbp
    
    mov %rdi, %r8  # node pointer
    
    # Print node type
    mov $node_type_fmt, %rdi
    mov AST_NODE_TYPE(%r8), %rsi
    call printf
    
    # Print token literal
    mov $token_literal_fmt, %rdi
    mov AST_TOKEN_LITERAL(%r8), %rsi
    call printf
    
    # Print line/column
    mov $line_col_fmt, %rdi
    mov AST_LINE(%r8), %rsi
    mov AST_COLUMN(%r8), %rdx
    call printf
    
    pop %rbp
    ret

.section .rodata
program_str: .asciz "program"
var_str: .asciz "var"
identifier_str: .asciz "identifier"
integer_str: .asciz "integer"
node_type_fmt: .asciz "Node Type: %ld\n"
token_literal_fmt: .asciz "Token: %s\n"
line_col_fmt: .asciz "Position: %ld:%ld\n"
