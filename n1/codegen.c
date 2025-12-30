#include "morph.h"

// Native bindings
void mph_native_print(MorphContext* ctx, MorphString* s);
void mph_native_print_int(MorphContext* ctx, mph_int n);
mph_int mph_string_index(MorphContext* ctx, MorphString* s, MorphString* sub);
MorphString* mph_string_trim(MorphContext* ctx, MorphString* s, MorphString* cut);
MorphArray* mph_string_split(MorphContext* ctx, MorphString* s, MorphString* sep);

// Struct Definitions

// RTTI Definitions

// Type IDs
#define MPH_TYPE_mph_ast_Program 7
#define MPH_TYPE_mph_ast_CharLiteral 13
#define MPH_TYPE_mph_ast_StructStatement 24
#define MPH_TYPE_mph_ast_ContinueStatement 27
#define MPH_TYPE_mph_token_Token 28
#define MPH_TYPE_mph_types_TypeResult 30
#define MPH_TYPE_mph_ast_ReturnStatement 4
#define MPH_TYPE_mph_ast_BlockStatement 6
#define MPH_TYPE_mph_ast_IfExpression 17
#define MPH_TYPE_mph_ast_IndexExpression 19
#define MPH_TYPE_mph_ast_SwitchStatement 22
#define MPH_TYPE_mph_ast_Node 1
#define MPH_TYPE_mph_ast_Identifier 8
#define MPH_TYPE_mph_ast_StringLiteral 11
#define MPH_TYPE_mph_ast_NullLiteral 14
#define MPH_TYPE_mph_ast_CaseClause 21
#define MPH_TYPE_mph_ast_WhileStatement 23
#define MPH_TYPE_mph_ast_FloatLiteral 10
#define MPH_TYPE_mph_ast_CallExpression 18
#define MPH_TYPE_mph_ast_MemberExpression 20
#define MPH_TYPE_mph_ast_ImportStatement 25
#define MPH_TYPE_mph_ast_BreakStatement 26
#define MPH_TYPE_mph_ast_ExpressionStatement 5
#define MPH_TYPE_mph_ast_PrefixExpression 15
#define MPH_TYPE_mph_types_Type 29
#define MPH_TYPE_mph_Codegen 31
#define MPH_TYPE_mph_ast_IntegerLiteral 9
#define MPH_TYPE_mph_ast_InfixExpression 16
#define MPH_TYPE_mph_ast_VarStatement 2
#define MPH_TYPE_mph_ast_FunctionStatement 3
#define MPH_TYPE_mph_ast_BooleanLiteral 12

// Struct Definitions (Env & Types)
typedef struct mph_ast_Node mph_ast_Node;
typedef struct mph_ast_VarStatement mph_ast_VarStatement;
typedef struct mph_ast_FunctionStatement mph_ast_FunctionStatement;
typedef struct mph_ast_ReturnStatement mph_ast_ReturnStatement;
typedef struct mph_ast_ExpressionStatement mph_ast_ExpressionStatement;
typedef struct mph_ast_BlockStatement mph_ast_BlockStatement;
typedef struct mph_ast_Program mph_ast_Program;
typedef struct mph_ast_Identifier mph_ast_Identifier;
typedef struct mph_ast_IntegerLiteral mph_ast_IntegerLiteral;
typedef struct mph_ast_FloatLiteral mph_ast_FloatLiteral;
typedef struct mph_ast_StringLiteral mph_ast_StringLiteral;
typedef struct mph_ast_BooleanLiteral mph_ast_BooleanLiteral;
typedef struct mph_ast_CharLiteral mph_ast_CharLiteral;
typedef struct mph_ast_NullLiteral mph_ast_NullLiteral;
typedef struct mph_ast_PrefixExpression mph_ast_PrefixExpression;
typedef struct mph_ast_InfixExpression mph_ast_InfixExpression;
typedef struct mph_ast_IfExpression mph_ast_IfExpression;
typedef struct mph_ast_CallExpression mph_ast_CallExpression;
typedef struct mph_ast_IndexExpression mph_ast_IndexExpression;
typedef struct mph_ast_MemberExpression mph_ast_MemberExpression;
typedef struct mph_ast_CaseClause mph_ast_CaseClause;
typedef struct mph_ast_SwitchStatement mph_ast_SwitchStatement;
typedef struct mph_ast_WhileStatement mph_ast_WhileStatement;
typedef struct mph_ast_StructStatement mph_ast_StructStatement;
typedef struct mph_ast_ImportStatement mph_ast_ImportStatement;
typedef struct mph_ast_BreakStatement mph_ast_BreakStatement;
typedef struct mph_ast_ContinueStatement mph_ast_ContinueStatement;
struct mph_ast_Node {
	mph_int node_type;
	MorphString* token_literal;
	mph_int line;
	mph_int column;
};

struct mph_ast_VarStatement {
	mph_ast_Node* base;
	MorphString* name;
	MorphString* value_type;
	mph_bool has_value;
	MorphString* value_literal;
	mph_int value_token_type;
};

struct mph_ast_FunctionStatement {
	mph_ast_Node* base;
	MorphString* name;
	mph_int parameters_count;
	MorphString* return_type;
};

struct mph_ast_ReturnStatement {
	mph_ast_Node* base;
	mph_bool has_value;
};

struct mph_ast_ExpressionStatement {
	mph_ast_Node* base;
};

struct mph_ast_BlockStatement {
	mph_ast_Node* base;
	mph_int statements_count;
};

struct mph_ast_Program {
	mph_ast_Node* base;
	mph_int statements_count;
	mph_int var_statements_count;
	mph_ast_VarStatement* var_statement;
	mph_bool has_var_statement;
};

struct mph_ast_Identifier {
	mph_ast_Node* base;
	MorphString* value;
};

struct mph_ast_IntegerLiteral {
	mph_ast_Node* base;
	mph_int value;
};

struct mph_ast_FloatLiteral {
	mph_ast_Node* base;
	MorphString* value_str;
};

struct mph_ast_StringLiteral {
	mph_ast_Node* base;
	MorphString* value;
};

struct mph_ast_BooleanLiteral {
	mph_ast_Node* base;
	mph_bool value;
};

struct mph_ast_CharLiteral {
	mph_ast_Node* base;
	mph_int value;
};

struct mph_ast_NullLiteral {
	mph_ast_Node* base;
};

struct mph_ast_PrefixExpression {
	mph_ast_Node* base;
	MorphString* operator;
};

struct mph_ast_InfixExpression {
	mph_ast_Node* base;
	MorphString* operator;
};

struct mph_ast_IfExpression {
	mph_ast_Node* base;
	mph_bool has_alternative;
};

struct mph_ast_CallExpression {
	mph_ast_Node* base;
	mph_int arguments_count;
};

struct mph_ast_IndexExpression {
	mph_ast_Node* base;
};

struct mph_ast_MemberExpression {
	mph_ast_Node* base;
	MorphString* member_name;
};

struct mph_ast_CaseClause {
	mph_ast_Node* base;
	mph_int values_count;
	mph_int v0;
	mph_int v1;
	mph_int v2;
	mph_int v3;
	mph_bool has_body;
};

struct mph_ast_SwitchStatement {
	mph_ast_Node* base;
	mph_int cases_count;
	mph_bool has_default;
};

struct mph_ast_WhileStatement {
	mph_ast_Node* base;
	mph_bool has_body;
};

struct mph_ast_StructStatement {
	mph_ast_Node* base;
	MorphString* name;
	mph_int fields_count;
};

struct mph_ast_ImportStatement {
	mph_ast_Node* base;
	MorphString* path;
};

struct mph_ast_BreakStatement {
	mph_ast_Node* base;
};

struct mph_ast_ContinueStatement {
	mph_ast_Node* base;
};

typedef struct mph_token_Token mph_token_Token;
struct mph_token_Token {
	mph_int token_type;
	MorphString* literal;
	mph_int line;
	mph_int column;
};

typedef struct mph_types_Type mph_types_Type;
typedef struct mph_types_TypeResult mph_types_TypeResult;
struct mph_types_Type {
	mph_int kind;
	MorphString* name;
};

struct mph_types_TypeResult {
	mph_types_Type* result;
	MorphString* error_msg;
	mph_bool has_error;
};

typedef struct mph_Codegen mph_Codegen;
struct mph_Codegen {
	MorphString* output;
	MorphString* type_defs;
	MorphString* global_defs;
	MorphString* prototypes;
	MorphString* func_defs;
	MorphString* entry_body;
	MorphString* pass_log;
	mph_int temp_index;
	mph_bool has_main;
	mph_int indent_level;
	MorphString* current_prefix;
};

MorphTypeInfo mph_ti_mph_ast_Node = { "Node", sizeof(mph_ast_Node), 1, (size_t[]){offsetof(mph_ast_Node, token_literal)} };
MorphTypeInfo mph_ti_mph_ast_VarStatement = { "VarStatement", sizeof(mph_ast_VarStatement), 4, (size_t[]){offsetof(mph_ast_VarStatement, base), offsetof(mph_ast_VarStatement, name), offsetof(mph_ast_VarStatement, value_type), offsetof(mph_ast_VarStatement, value_literal)} };
MorphTypeInfo mph_ti_mph_ast_FunctionStatement = { "FunctionStatement", sizeof(mph_ast_FunctionStatement), 3, (size_t[]){offsetof(mph_ast_FunctionStatement, base), offsetof(mph_ast_FunctionStatement, name), offsetof(mph_ast_FunctionStatement, return_type)} };
MorphTypeInfo mph_ti_mph_ast_ReturnStatement = { "ReturnStatement", sizeof(mph_ast_ReturnStatement), 1, (size_t[]){offsetof(mph_ast_ReturnStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_ExpressionStatement = { "ExpressionStatement", sizeof(mph_ast_ExpressionStatement), 1, (size_t[]){offsetof(mph_ast_ExpressionStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_BlockStatement = { "BlockStatement", sizeof(mph_ast_BlockStatement), 1, (size_t[]){offsetof(mph_ast_BlockStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_Program = { "Program", sizeof(mph_ast_Program), 2, (size_t[]){offsetof(mph_ast_Program, base), offsetof(mph_ast_Program, var_statement)} };
MorphTypeInfo mph_ti_mph_ast_Identifier = { "Identifier", sizeof(mph_ast_Identifier), 2, (size_t[]){offsetof(mph_ast_Identifier, base), offsetof(mph_ast_Identifier, value)} };
MorphTypeInfo mph_ti_mph_ast_IntegerLiteral = { "IntegerLiteral", sizeof(mph_ast_IntegerLiteral), 1, (size_t[]){offsetof(mph_ast_IntegerLiteral, base)} };
MorphTypeInfo mph_ti_mph_ast_FloatLiteral = { "FloatLiteral", sizeof(mph_ast_FloatLiteral), 2, (size_t[]){offsetof(mph_ast_FloatLiteral, base), offsetof(mph_ast_FloatLiteral, value_str)} };
MorphTypeInfo mph_ti_mph_ast_StringLiteral = { "StringLiteral", sizeof(mph_ast_StringLiteral), 2, (size_t[]){offsetof(mph_ast_StringLiteral, base), offsetof(mph_ast_StringLiteral, value)} };
MorphTypeInfo mph_ti_mph_ast_BooleanLiteral = { "BooleanLiteral", sizeof(mph_ast_BooleanLiteral), 1, (size_t[]){offsetof(mph_ast_BooleanLiteral, base)} };
MorphTypeInfo mph_ti_mph_ast_CharLiteral = { "CharLiteral", sizeof(mph_ast_CharLiteral), 1, (size_t[]){offsetof(mph_ast_CharLiteral, base)} };
MorphTypeInfo mph_ti_mph_ast_NullLiteral = { "NullLiteral", sizeof(mph_ast_NullLiteral), 1, (size_t[]){offsetof(mph_ast_NullLiteral, base)} };
MorphTypeInfo mph_ti_mph_ast_PrefixExpression = { "PrefixExpression", sizeof(mph_ast_PrefixExpression), 2, (size_t[]){offsetof(mph_ast_PrefixExpression, base), offsetof(mph_ast_PrefixExpression, operator)} };
MorphTypeInfo mph_ti_mph_ast_InfixExpression = { "InfixExpression", sizeof(mph_ast_InfixExpression), 2, (size_t[]){offsetof(mph_ast_InfixExpression, base), offsetof(mph_ast_InfixExpression, operator)} };
MorphTypeInfo mph_ti_mph_ast_IfExpression = { "IfExpression", sizeof(mph_ast_IfExpression), 1, (size_t[]){offsetof(mph_ast_IfExpression, base)} };
MorphTypeInfo mph_ti_mph_ast_CallExpression = { "CallExpression", sizeof(mph_ast_CallExpression), 1, (size_t[]){offsetof(mph_ast_CallExpression, base)} };
MorphTypeInfo mph_ti_mph_ast_IndexExpression = { "IndexExpression", sizeof(mph_ast_IndexExpression), 1, (size_t[]){offsetof(mph_ast_IndexExpression, base)} };
MorphTypeInfo mph_ti_mph_ast_MemberExpression = { "MemberExpression", sizeof(mph_ast_MemberExpression), 2, (size_t[]){offsetof(mph_ast_MemberExpression, base), offsetof(mph_ast_MemberExpression, member_name)} };
MorphTypeInfo mph_ti_mph_ast_CaseClause = { "CaseClause", sizeof(mph_ast_CaseClause), 1, (size_t[]){offsetof(mph_ast_CaseClause, base)} };
MorphTypeInfo mph_ti_mph_ast_SwitchStatement = { "SwitchStatement", sizeof(mph_ast_SwitchStatement), 1, (size_t[]){offsetof(mph_ast_SwitchStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_WhileStatement = { "WhileStatement", sizeof(mph_ast_WhileStatement), 1, (size_t[]){offsetof(mph_ast_WhileStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_StructStatement = { "StructStatement", sizeof(mph_ast_StructStatement), 2, (size_t[]){offsetof(mph_ast_StructStatement, base), offsetof(mph_ast_StructStatement, name)} };
MorphTypeInfo mph_ti_mph_ast_ImportStatement = { "ImportStatement", sizeof(mph_ast_ImportStatement), 2, (size_t[]){offsetof(mph_ast_ImportStatement, base), offsetof(mph_ast_ImportStatement, path)} };
MorphTypeInfo mph_ti_mph_ast_BreakStatement = { "BreakStatement", sizeof(mph_ast_BreakStatement), 1, (size_t[]){offsetof(mph_ast_BreakStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_ContinueStatement = { "ContinueStatement", sizeof(mph_ast_ContinueStatement), 1, (size_t[]){offsetof(mph_ast_ContinueStatement, base)} };
MorphTypeInfo mph_ti_mph_token_Token = { "Token", sizeof(mph_token_Token), 1, (size_t[]){offsetof(mph_token_Token, literal)} };
MorphTypeInfo mph_ti_mph_types_Type = { "Type", sizeof(mph_types_Type), 1, (size_t[]){offsetof(mph_types_Type, name)} };
MorphTypeInfo mph_ti_mph_types_TypeResult = { "TypeResult", sizeof(mph_types_TypeResult), 2, (size_t[]){offsetof(mph_types_TypeResult, result), offsetof(mph_types_TypeResult, error_msg)} };
MorphTypeInfo mph_ti_mph_Codegen = { "Codegen", sizeof(mph_Codegen), 8, (size_t[]){offsetof(mph_Codegen, output), offsetof(mph_Codegen, type_defs), offsetof(mph_Codegen, global_defs), offsetof(mph_Codegen, prototypes), offsetof(mph_Codegen, func_defs), offsetof(mph_Codegen, entry_body), offsetof(mph_Codegen, pass_log), offsetof(mph_Codegen, current_prefix)} };

// Global Variables
mph_int mph_ast_NODE_PROGRAM;
mph_int mph_ast_NODE_VAR_STATEMENT;
mph_int mph_ast_NODE_FUNCTION_STATEMENT;
mph_int mph_ast_NODE_RETURN_STATEMENT;
mph_int mph_ast_NODE_EXPRESSION_STATEMENT;
mph_int mph_ast_NODE_BLOCK_STATEMENT;
mph_int mph_ast_NODE_IF_EXPRESSION;
mph_int mph_ast_NODE_IDENTIFIER;
mph_int mph_ast_NODE_INTEGER_LITERAL;
mph_int mph_ast_NODE_FLOAT_LITERAL;
mph_int mph_ast_NODE_STRING_LITERAL;
mph_int mph_ast_NODE_BOOLEAN_LITERAL;
mph_int mph_ast_NODE_ARRAY_LITERAL;
mph_int mph_ast_NODE_HASH_LITERAL;
mph_int mph_ast_NODE_FUNCTION_LITERAL;
mph_int mph_ast_NODE_PREFIX_EXPRESSION;
mph_int mph_ast_NODE_INFIX_EXPRESSION;
mph_int mph_ast_NODE_CALL_EXPRESSION;
mph_int mph_ast_NODE_INDEX_EXPRESSION;
mph_int mph_ast_NODE_MEMBER_EXPRESSION;
mph_int mph_ast_NODE_ASSIGNMENT_EXPRESSION;
mph_int mph_ast_NODE_SWITCH_STATEMENT;
mph_int mph_ast_NODE_CASE_CLAUSE;
mph_int mph_ast_NODE_WHILE_STATEMENT;
mph_int mph_ast_NODE_STRUCT_STATEMENT;
mph_int mph_ast_NODE_STRUCT_LITERAL;
mph_int mph_ast_NODE_IMPORT_STATEMENT;
mph_int mph_ast_NODE_INTERFACE_STATEMENT;
mph_int mph_ast_NODE_BREAK_STATEMENT;
mph_int mph_ast_NODE_CONTINUE_STATEMENT;
mph_int mph_ast_NODE_CHAR_LITERAL;
mph_int mph_ast_NODE_NULL_LITERAL;
mph_int mph_token_TOKEN_ILLEGAL;
mph_int mph_token_TOKEN_EOF;
mph_int mph_token_TOKEN_IDENT;
mph_int mph_token_TOKEN_INT;
mph_int mph_token_TOKEN_FLOAT;
mph_int mph_token_TOKEN_STRING;
mph_int mph_token_TOKEN_CHAR;
mph_int mph_token_TOKEN_ASSIGN;
mph_int mph_token_TOKEN_PLUS;
mph_int mph_token_TOKEN_MINUS;
mph_int mph_token_TOKEN_BANG;
mph_int mph_token_TOKEN_ASTERISK;
mph_int mph_token_TOKEN_SLASH;
mph_int mph_token_TOKEN_PERCENT;
mph_int mph_token_TOKEN_LT;
mph_int mph_token_TOKEN_GT;
mph_int mph_token_TOKEN_EQ;
mph_int mph_token_TOKEN_NOT_EQ;
mph_int mph_token_TOKEN_LE;
mph_int mph_token_TOKEN_GE;
mph_int mph_token_TOKEN_BIT_AND;
mph_int mph_token_TOKEN_BIT_OR;
mph_int mph_token_TOKEN_BIT_XOR;
mph_int mph_token_TOKEN_BIT_NOT;
mph_int mph_token_TOKEN_LSHIFT;
mph_int mph_token_TOKEN_RSHIFT;
mph_int mph_token_TOKEN_AND;
mph_int mph_token_TOKEN_OR;
mph_int mph_token_TOKEN_COMMA;
mph_int mph_token_TOKEN_SEMICOLON;
mph_int mph_token_TOKEN_COLON;
mph_int mph_token_TOKEN_LPAREN;
mph_int mph_token_TOKEN_RPAREN;
mph_int mph_token_TOKEN_LBRACE;
mph_int mph_token_TOKEN_RBRACE;
mph_int mph_token_TOKEN_LBRACKET;
mph_int mph_token_TOKEN_RBRACKET;
mph_int mph_token_TOKEN_FUNGSI;
mph_int mph_token_TOKEN_VAR;
mph_int mph_token_TOKEN_TETAPAN;
mph_int mph_token_TOKEN_BENAR;
mph_int mph_token_TOKEN_SALAH;
mph_int mph_token_TOKEN_JIKA;
mph_int mph_token_TOKEN_LAINNYA;
mph_int mph_token_TOKEN_KEMBALIKAN;
mph_int mph_token_TOKEN_STRUKTUR;
mph_int mph_token_TOKEN_ANTARMUKA;
mph_int mph_token_TOKEN_AMBIL;
mph_int mph_token_TOKEN_UNTUK;
mph_int mph_token_TOKEN_SELAMA;
mph_int mph_token_TOKEN_PUTUS;
mph_int mph_token_TOKEN_LANJUT;
mph_int mph_token_TOKEN_PILIH;
mph_int mph_token_TOKEN_KASUS;
mph_int mph_token_TOKEN_BAWAAN;
mph_int mph_token_TOKEN_AKHIR;
mph_int mph_token_TOKEN_ATAU_JIKA;
mph_int mph_token_TOKEN_DAN;
mph_int mph_token_TOKEN_ATAU;
mph_int mph_token_TOKEN_KOSONG;
mph_int mph_token_TOKEN_LUNCURKAN;
mph_int mph_token_TOKEN_SALURAN_BARU;
mph_int mph_token_TOKEN_KIRIM;
mph_int mph_token_TOKEN_TERIMA;
mph_int mph_token_TOKEN_DOT;
mph_int mph_token_TOKEN_ARROW;
mph_int mph_types_KIND_INT;
mph_int mph_types_KIND_FLOAT;
mph_int mph_types_KIND_STRING;
mph_int mph_types_KIND_BOOL;
mph_int mph_types_KIND_VOID;
mph_int mph_types_KIND_FUNCTION;
mph_int mph_types_KIND_STRUCT;
mph_int mph_types_KIND_INTERFACE;
mph_int mph_types_KIND_ARRAY;
mph_int mph_types_KIND_MAP;
mph_int mph_types_KIND_POINTER;
mph_int mph_types_KIND_MULTI;
mph_int mph_types_KIND_UNKNOWN;
mph_int mph_types_KIND_ERROR;
mph_int mph_types_KIND_NULL;
mph_int mph_types_KIND_USER_ERROR;
mph_int mph_types_KIND_MODULE;
mph_int mph_types_KIND_CHANNEL;

// Function Prototypes
mph_Codegen* mph_new_codegen(MorphContext* ctx, void* _env_void);
MorphString* mph_codegen_compile(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_record_pass(MorphContext* ctx, void* _env_void, mph_Codegen* cg, MorphString* name);
void mph_codegen_pass_collect_globals(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_pass_analyze_captures(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_pass_compile_struct_types(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_pass_compile_struct_rtti(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_pass_compile_module(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog, MorphString* prefix);
void mph_codegen_compile_program(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog, MorphString* prefix);
MorphString* mph_codegen_map_type_to_c(MorphContext* ctx, void* _env_void, mph_types_Type* t);
MorphString* mph_codegen_next_temp(MorphContext* ctx, void* _env_void, mph_Codegen* cg, MorphString* prefix);
MorphString* mph_codegen_append(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text);
MorphString* mph_codegen_append_line(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text);
MorphString* mph_codegen_append_indent(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text, mph_int level);
MorphString* mph_codegen_compile_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit);
MorphString* mph_codegen_compile_float_literal(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit);
MorphString* mph_codegen_compile_char_literal(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit);
MorphString* mph_codegen_compile_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit);
MorphString* mph_codegen_compile_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit);
MorphString* mph_codegen_compile_null_literal(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit);
MorphString* mph_codegen_compile_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident);
MorphString* mph_codegen_compile_infix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_compile_prefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_resolve_builtin_name(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_codegen_compile_builtin_call(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code);
MorphString* mph_codegen_var_type_from_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str);
MorphString* mph_codegen_default_value_for_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str);
MorphString* mph_codegen_var_type_from_token(MorphContext* ctx, void* _env_void, mph_int token_type);
MorphString* mph_codegen_value_code_from_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal);
MorphString* mph_codegen_compile_var_statement_typed(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code, MorphString* c_type);
MorphString* mph_codegen_var_type_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_var_value_code_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_compile_global_var_declaration(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_compile_global_var_initialization(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_compile_var_statement_from_stmt(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_compile_var_statement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code);
MorphString* mph_codegen_compile_expression_statement(MorphContext* ctx, void* _env_void, MorphString* value_code);
MorphString* mph_codegen_compile_return_statement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code);
mph_Codegen* mph_NewCodegen(MorphContext* ctx, void* _env_void);
MorphString* mph_Compile(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog);
MorphString* mph_MapTypeToC(MorphContext* ctx, void* _env_void, mph_types_Type* t);
MorphString* mph_CompileIntegerLiteral(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit);
MorphString* mph_CompileFloatLiteral(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit);
MorphString* mph_CompileCharLiteral(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit);
MorphString* mph_CompileStringLiteral(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit);
MorphString* mph_CompileBooleanLiteral(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit);
MorphString* mph_CompileNullLiteral(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit);
MorphString* mph_CompileIdentifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident);
MorphString* mph_CompileInfix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code);
MorphString* mph_CompilePrefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code);
MorphString* mph_ResolveBuiltinName(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_CompileBuiltinCall(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code);
MorphString* mph_CompileVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code);
MorphString* mph_CompileExpressionStatement(MorphContext* ctx, void* _env_void, MorphString* value_code);
MorphString* mph_CompileReturnStatement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code);
mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column);
mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void);
mph_ast_Identifier* mph_ast_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column);
mph_ast_IntegerLiteral* mph_ast_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column);
mph_ast_FloatLiteral* mph_ast_MakeFloatLiteral(MorphContext* ctx, void* _env_void, MorphString* value_str, mph_int line, mph_int column);
mph_ast_StringLiteral* mph_ast_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column);
mph_ast_BooleanLiteral* mph_ast_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column);
mph_ast_CharLiteral* mph_ast_MakeCharLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column);
mph_ast_NullLiteral* mph_ast_MakeNullLiteral(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_ast_VarStatement* mph_ast_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column);
mph_ast_PrefixExpression* mph_ast_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column);
mph_ast_InfixExpression* mph_ast_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column);
mph_ast_CaseClause* mph_ast_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_ast_CaseClause* mph_ast_case_add_value(MorphContext* ctx, void* _env_void, mph_ast_CaseClause* c, mph_int val);
mph_ast_SwitchStatement* mph_ast_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_ast_WhileStatement* mph_ast_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_ast_StructStatement* mph_ast_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column);
mph_ast_ImportStatement* mph_ast_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column);
mph_ast_BreakStatement* mph_ast_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_ast_ContinueStatement* mph_ast_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
MorphString* mph_ast_node_type_string(MorphContext* ctx, void* _env_void, mph_int node_type);
void mph_ast_visit_node(MorphContext* ctx, void* _env_void, mph_ast_Node* node);
void mph_ast_print_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident);
void mph_ast_print_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit);
void mph_ast_print_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit);
void mph_ast_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit);
mph_token_Token* mph_token_MakeToken(MorphContext* ctx, void* _env_void, mph_int t_type, MorphString* lit, mph_int ln, mph_int col);
MorphString* mph_token_TokenTypeString(MorphContext* ctx, void* _env_void, mph_int t_type);
mph_int mph_token_LookupKeyword(MorphContext* ctx, void* _env_void, MorphString* ident);
mph_types_Type* mph_types_make_type(MorphContext* ctx, void* _env_void, mph_int k, MorphString* n);
mph_types_Type* mph_types_int_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_float_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_string_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_bool_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_void_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_null_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_unknown_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_error_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_user_error_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_channel_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_array_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_map_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_struct_type(MorphContext* ctx, void* _env_void, MorphString* n);
mph_types_Type* mph_types_interface_type(MorphContext* ctx, void* _env_void, MorphString* n);
mph_types_Type* mph_types_function_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_pointer_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_multi_type(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_module_type(MorphContext* ctx, void* _env_void, MorphString* n);
mph_bool mph_types_type_equals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2);
mph_bool mph_types_type_assignable_to(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target);
mph_bool mph_types_type_is_comparable(MorphContext* ctx, void* _env_void, mph_types_Type* t);
mph_types_TypeResult* mph_types_make_type_result(MorphContext* ctx, void* _env_void, mph_types_Type* t);
mph_types_TypeResult* mph_types_make_type_error(MorphContext* ctx, void* _env_void, MorphString* msg);
mph_types_TypeResult* mph_types_type_binary_op(MorphContext* ctx, void* _env_void, mph_types_Type* left, MorphString* op, mph_types_Type* right);
mph_types_TypeResult* mph_types_type_prefix_op(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op);
MorphString* mph_types_kind_to_string(MorphContext* ctx, void* _env_void, mph_int k);
mph_types_Type* mph_types_IntType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_FloatType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_StringType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_BoolType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_VoidType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_NullType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_UnknownType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_ErrorType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_UserErrorType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_ChannelType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_ArrayType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_MapType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_StructType(MorphContext* ctx, void* _env_void, MorphString* n);
mph_types_Type* mph_types_InterfaceType(MorphContext* ctx, void* _env_void, MorphString* n);
mph_types_Type* mph_types_FunctionType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_PointerType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_MultiType(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_types_ModuleType(MorphContext* ctx, void* _env_void, MorphString* n);
mph_bool mph_types_TypeEquals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2);
mph_bool mph_types_TypeAssignableTo(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target);
mph_bool mph_types_TypeIsComparable(MorphContext* ctx, void* _env_void, mph_types_Type* t);
mph_types_TypeResult* mph_types_TypeBinaryOp(MorphContext* ctx, void* _env_void, mph_types_Type* left, MorphString* op, mph_types_Type* right);
mph_types_TypeResult* mph_types_TypePrefixOp(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op);
MorphString* mph_types_KindToString(MorphContext* ctx, void* _env_void, mph_int k);
void mph_types_main(MorphContext* ctx, void* _env_void);
MorphString* mph_stdlib_codegen_int_to_string(MorphContext* ctx, void* _env_void, mph_int n);
MorphString* mph_stdlib_codegen_char_at(MorphContext* ctx, void* _env_void, MorphString* s, mph_int index);
MorphString* mph_stdlib_codegen_string_escape(MorphContext* ctx, void* _env_void, MorphString* s);
mph_bool mph_stdlib_codegen_is_alpha(MorphContext* ctx, void* _env_void, MorphString* ch);
mph_bool mph_stdlib_codegen_is_digit(MorphContext* ctx, void* _env_void, MorphString* ch);
mph_bool mph_stdlib_codegen_is_valid_c_ident(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_stdlib_codegen_module_to_prefix(MorphContext* ctx, void* _env_void, MorphString* path);
MorphString* mph_stdlib_codegen_IntToString(MorphContext* ctx, void* _env_void, mph_int n);
MorphString* mph_stdlib_codegen_StringEscape(MorphContext* ctx, void* _env_void, MorphString* s);
mph_bool mph_stdlib_codegen_IsValidCIdent(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_stdlib_codegen_ModuleToPrefix(MorphContext* ctx, void* _env_void, MorphString* path);
void mph_stdlib_codegen_main(MorphContext* ctx, void* _env_void);

// Function Definitions
mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_ast_Node* _t = (mph_ast_Node*)mph_alloc(ctx, sizeof(mph_ast_Node), &mph_ti_mph_ast_Node); mph_gc_push_root(ctx, (void**)&_t); _t->node_type = node_type; _t->token_literal = literal; _t->line = line; _t->column = column; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void) {
	mph_ast_Node* base = ({ MorphString* _arg_1 = mph_string_new(ctx, "program"); mph_gc_push_root(ctx, (void**)&_arg_1); mph_ast_Node* _ret_2 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PROGRAM, _arg_1, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_2; });
	mph_gc_push_root(ctx, (void**)&base);
	mph_ast_VarStatement* stmt = ({ MorphString* _arg_3 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_3); MorphString* _arg_4 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_4); mph_ast_VarStatement* _ret_5 = mph_ast_MakeVarStatement(ctx, NULL, _arg_3, _arg_4, 1, 1); mph_gc_pop_roots(ctx, 2); _ret_5; });
	mph_gc_push_root(ctx, (void**)&stmt);
	return ({ mph_ast_Program* _t = (mph_ast_Program*)mph_alloc(ctx, sizeof(mph_ast_Program), &mph_ti_mph_ast_Program); mph_gc_push_root(ctx, (void**)&_t); _t->var_statements_count = 0; _t->var_statement = stmt; _t->has_var_statement = 0; _t->base = base; _t->statements_count = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_Identifier* mph_ast_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_6 = name; mph_gc_push_root(ctx, (void**)&_arg_6); mph_ast_Node* _ret_7 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IDENTIFIER, _arg_6, line, column); mph_gc_pop_roots(ctx, 1); _ret_7; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_Identifier* _t = (mph_ast_Identifier*)mph_alloc(ctx, sizeof(mph_ast_Identifier), &mph_ti_mph_ast_Identifier); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = name; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_IntegerLiteral* mph_ast_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_8 = literal; mph_gc_push_root(ctx, (void**)&_arg_8); mph_ast_Node* _ret_9 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INTEGER_LITERAL, _arg_8, line, column); mph_gc_pop_roots(ctx, 1); _ret_9; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_IntegerLiteral* _t = (mph_ast_IntegerLiteral*)mph_alloc(ctx, sizeof(mph_ast_IntegerLiteral), &mph_ti_mph_ast_IntegerLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_FloatLiteral* mph_ast_MakeFloatLiteral(MorphContext* ctx, void* _env_void, MorphString* value_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value_str);
	mph_ast_Node* base = ({ MorphString* _arg_10 = value_str; mph_gc_push_root(ctx, (void**)&_arg_10); mph_ast_Node* _ret_11 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_FLOAT_LITERAL, _arg_10, line, column); mph_gc_pop_roots(ctx, 1); _ret_11; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_FloatLiteral* _t = (mph_ast_FloatLiteral*)mph_alloc(ctx, sizeof(mph_ast_FloatLiteral), &mph_ti_mph_ast_FloatLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value_str = value_str; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StringLiteral* mph_ast_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value);
	mph_ast_Node* base = ({ MorphString* _arg_12 = value; mph_gc_push_root(ctx, (void**)&_arg_12); mph_ast_Node* _ret_13 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRING_LITERAL, _arg_12, line, column); mph_gc_pop_roots(ctx, 1); _ret_13; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StringLiteral* _t = (mph_ast_StringLiteral*)mph_alloc(ctx, sizeof(mph_ast_StringLiteral), &mph_ti_mph_ast_StringLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BooleanLiteral* mph_ast_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_14 = literal; mph_gc_push_root(ctx, (void**)&_arg_14); mph_ast_Node* _ret_15 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BOOLEAN_LITERAL, _arg_14, line, column); mph_gc_pop_roots(ctx, 1); _ret_15; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BooleanLiteral* _t = (mph_ast_BooleanLiteral*)mph_alloc(ctx, sizeof(mph_ast_BooleanLiteral), &mph_ti_mph_ast_BooleanLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CharLiteral* mph_ast_MakeCharLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_16 = literal; mph_gc_push_root(ctx, (void**)&_arg_16); mph_ast_Node* _ret_17 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CHAR_LITERAL, _arg_16, line, column); mph_gc_pop_roots(ctx, 1); _ret_17; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CharLiteral* _t = (mph_ast_CharLiteral*)mph_alloc(ctx, sizeof(mph_ast_CharLiteral), &mph_ti_mph_ast_CharLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_NullLiteral* mph_ast_MakeNullLiteral(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_18 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_18); mph_ast_Node* _ret_19 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_NULL_LITERAL, _arg_18, line, column); mph_gc_pop_roots(ctx, 1); _ret_19; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_NullLiteral* _t = (mph_ast_NullLiteral*)mph_alloc(ctx, sizeof(mph_ast_NullLiteral), &mph_ti_mph_ast_NullLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_VarStatement* mph_ast_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&type_str);
	mph_ast_Node* base = ({ MorphString* _arg_20 = mph_string_new(ctx, "var"); mph_gc_push_root(ctx, (void**)&_arg_20); mph_ast_Node* _ret_21 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_VAR_STATEMENT, _arg_20, line, column); mph_gc_pop_roots(ctx, 1); _ret_21; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_VarStatement* _t = (mph_ast_VarStatement*)mph_alloc(ctx, sizeof(mph_ast_VarStatement), &mph_ti_mph_ast_VarStatement); mph_gc_push_root(ctx, (void**)&_t); _t->value_token_type = 0; _t->base = base; _t->name = name; _t->value_type = type_str; _t->has_value = 0; _t->value_literal = mph_string_new(ctx, "-"); mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_PrefixExpression* mph_ast_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_22 = operator; mph_gc_push_root(ctx, (void**)&_arg_22); mph_ast_Node* _ret_23 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PREFIX_EXPRESSION, _arg_22, line, column); mph_gc_pop_roots(ctx, 1); _ret_23; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_PrefixExpression* _t = (mph_ast_PrefixExpression*)mph_alloc(ctx, sizeof(mph_ast_PrefixExpression), &mph_ti_mph_ast_PrefixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_InfixExpression* mph_ast_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_24 = operator; mph_gc_push_root(ctx, (void**)&_arg_24); mph_ast_Node* _ret_25 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INFIX_EXPRESSION, _arg_24, line, column); mph_gc_pop_roots(ctx, 1); _ret_25; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_InfixExpression* _t = (mph_ast_InfixExpression*)mph_alloc(ctx, sizeof(mph_ast_InfixExpression), &mph_ti_mph_ast_InfixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_26 = mph_string_new(ctx, "kasus"); mph_gc_push_root(ctx, (void**)&_arg_26); mph_ast_Node* _ret_27 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CASE_CLAUSE, _arg_26, line, column); mph_gc_pop_roots(ctx, 1); _ret_27; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CaseClause* _t = (mph_ast_CaseClause*)mph_alloc(ctx, sizeof(mph_ast_CaseClause), &mph_ti_mph_ast_CaseClause); mph_gc_push_root(ctx, (void**)&_t); _t->v2 = 0; _t->v3 = 0; _t->has_body = 0; _t->base = base; _t->values_count = 0; _t->v0 = 0; _t->v1 = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_case_add_value(MorphContext* ctx, void* _env_void, mph_ast_CaseClause* c, mph_int val) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_ast_CaseClause* _obj_28 = c; mph_gc_push_root(ctx, (void**)&_obj_28); mph_int _ret_29 = _obj_28->values_count; mph_gc_pop_roots(ctx, 1); _ret_29; }) == 0)) {
{
	({ mph_ast_CaseClause* _obj_30 = c; mph_gc_push_root(ctx, (void**)&_obj_30); _obj_30->v0 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_31 = c; mph_gc_push_root(ctx, (void**)&_obj_31); mph_int _ret_32 = _obj_31->values_count; mph_gc_pop_roots(ctx, 1); _ret_32; }) == 1)) {
{
	({ mph_ast_CaseClause* _obj_33 = c; mph_gc_push_root(ctx, (void**)&_obj_33); _obj_33->v1 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_34 = c; mph_gc_push_root(ctx, (void**)&_obj_34); mph_int _ret_35 = _obj_34->values_count; mph_gc_pop_roots(ctx, 1); _ret_35; }) == 2)) {
{
	({ mph_ast_CaseClause* _obj_36 = c; mph_gc_push_root(ctx, (void**)&_obj_36); _obj_36->v2 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_37 = c; mph_gc_push_root(ctx, (void**)&_obj_37); mph_int _ret_38 = _obj_37->values_count; mph_gc_pop_roots(ctx, 1); _ret_38; }) == 3)) {
{
	({ mph_ast_CaseClause* _obj_39 = c; mph_gc_push_root(ctx, (void**)&_obj_39); _obj_39->v3 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	({ mph_ast_CaseClause* _obj_42 = c; mph_gc_push_root(ctx, (void**)&_obj_42); _obj_42->values_count = (({ mph_ast_CaseClause* _obj_40 = c; mph_gc_push_root(ctx, (void**)&_obj_40); mph_int _ret_41 = _obj_40->values_count; mph_gc_pop_roots(ctx, 1); _ret_41; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return c;
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_SwitchStatement* mph_ast_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_43 = mph_string_new(ctx, "pilih"); mph_gc_push_root(ctx, (void**)&_arg_43); mph_ast_Node* _ret_44 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_SWITCH_STATEMENT, _arg_43, line, column); mph_gc_pop_roots(ctx, 1); _ret_44; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_SwitchStatement* _t = (mph_ast_SwitchStatement*)mph_alloc(ctx, sizeof(mph_ast_SwitchStatement), &mph_ti_mph_ast_SwitchStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->cases_count = 0; _t->has_default = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_WhileStatement* mph_ast_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_45 = mph_string_new(ctx, "selama"); mph_gc_push_root(ctx, (void**)&_arg_45); mph_ast_Node* _ret_46 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_WHILE_STATEMENT, _arg_45, line, column); mph_gc_pop_roots(ctx, 1); _ret_46; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_WhileStatement* _t = (mph_ast_WhileStatement*)mph_alloc(ctx, sizeof(mph_ast_WhileStatement), &mph_ti_mph_ast_WhileStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->has_body = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StructStatement* mph_ast_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_47 = mph_string_new(ctx, "struktur"); mph_gc_push_root(ctx, (void**)&_arg_47); mph_ast_Node* _ret_48 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRUCT_STATEMENT, _arg_47, line, column); mph_gc_pop_roots(ctx, 1); _ret_48; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StructStatement* _t = (mph_ast_StructStatement*)mph_alloc(ctx, sizeof(mph_ast_StructStatement), &mph_ti_mph_ast_StructStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->fields_count = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ImportStatement* mph_ast_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&path);
	mph_ast_Node* base = ({ MorphString* _arg_49 = mph_string_new(ctx, "ambil"); mph_gc_push_root(ctx, (void**)&_arg_49); mph_ast_Node* _ret_50 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IMPORT_STATEMENT, _arg_49, line, column); mph_gc_pop_roots(ctx, 1); _ret_50; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_ImportStatement* _t = (mph_ast_ImportStatement*)mph_alloc(ctx, sizeof(mph_ast_ImportStatement), &mph_ti_mph_ast_ImportStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->path = path; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BreakStatement* mph_ast_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_51 = mph_string_new(ctx, "putus"); mph_gc_push_root(ctx, (void**)&_arg_51); mph_ast_Node* _ret_52 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BREAK_STATEMENT, _arg_51, line, column); mph_gc_pop_roots(ctx, 1); _ret_52; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BreakStatement* _t = (mph_ast_BreakStatement*)mph_alloc(ctx, sizeof(mph_ast_BreakStatement), &mph_ti_mph_ast_BreakStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ContinueStatement* mph_ast_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_53 = mph_string_new(ctx, "lanjut"); mph_gc_push_root(ctx, (void**)&_arg_53); mph_ast_Node* _ret_54 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CONTINUE_STATEMENT, _arg_53, line, column); mph_gc_pop_roots(ctx, 1); _ret_54; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_ContinueStatement* _t = (mph_ast_ContinueStatement*)mph_alloc(ctx, sizeof(mph_ast_ContinueStatement), &mph_ti_mph_ast_ContinueStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_ast_node_type_string(MorphContext* ctx, void* _env_void, mph_int node_type) {
	if ((node_type == mph_ast_NODE_PROGRAM)) {
{
	return mph_string_new(ctx, "Program");
}
	}
	if ((node_type == mph_ast_NODE_VAR_STATEMENT)) {
{
	return mph_string_new(ctx, "VarStatement");
}
	}
	if ((node_type == mph_ast_NODE_FUNCTION_STATEMENT)) {
{
	return mph_string_new(ctx, "FunctionStatement");
}
	}
	if ((node_type == mph_ast_NODE_RETURN_STATEMENT)) {
{
	return mph_string_new(ctx, "ReturnStatement");
}
	}
	if ((node_type == mph_ast_NODE_EXPRESSION_STATEMENT)) {
{
	return mph_string_new(ctx, "ExpressionStatement");
}
	}
	if ((node_type == mph_ast_NODE_BLOCK_STATEMENT)) {
{
	return mph_string_new(ctx, "BlockStatement");
}
	}
	if ((node_type == mph_ast_NODE_IF_EXPRESSION)) {
{
	return mph_string_new(ctx, "IfExpression");
}
	}
	if ((node_type == mph_ast_NODE_IDENTIFIER)) {
{
	return mph_string_new(ctx, "Identifier");
}
	}
	if ((node_type == mph_ast_NODE_INTEGER_LITERAL)) {
{
	return mph_string_new(ctx, "IntegerLiteral");
}
	}
	if ((node_type == mph_ast_NODE_FLOAT_LITERAL)) {
{
	return mph_string_new(ctx, "FloatLiteral");
}
	}
	if ((node_type == mph_ast_NODE_STRING_LITERAL)) {
{
	return mph_string_new(ctx, "StringLiteral");
}
	}
	if ((node_type == mph_ast_NODE_BOOLEAN_LITERAL)) {
{
	return mph_string_new(ctx, "BooleanLiteral");
}
	}
	if ((node_type == mph_ast_NODE_CHAR_LITERAL)) {
{
	return mph_string_new(ctx, "CharLiteral");
}
	}
	if ((node_type == mph_ast_NODE_NULL_LITERAL)) {
{
	return mph_string_new(ctx, "NullLiteral");
}
	}
	if ((node_type == mph_ast_NODE_ARRAY_LITERAL)) {
{
	return mph_string_new(ctx, "ArrayLiteral");
}
	}
	if ((node_type == mph_ast_NODE_HASH_LITERAL)) {
{
	return mph_string_new(ctx, "HashLiteral");
}
	}
	if ((node_type == mph_ast_NODE_FUNCTION_LITERAL)) {
{
	return mph_string_new(ctx, "FunctionLiteral");
}
	}
	if ((node_type == mph_ast_NODE_PREFIX_EXPRESSION)) {
{
	return mph_string_new(ctx, "PrefixExpression");
}
	}
	if ((node_type == mph_ast_NODE_INFIX_EXPRESSION)) {
{
	return mph_string_new(ctx, "InfixExpression");
}
	}
	if ((node_type == mph_ast_NODE_CALL_EXPRESSION)) {
{
	return mph_string_new(ctx, "CallExpression");
}
	}
	if ((node_type == mph_ast_NODE_INDEX_EXPRESSION)) {
{
	return mph_string_new(ctx, "IndexExpression");
}
	}
	if ((node_type == mph_ast_NODE_MEMBER_EXPRESSION)) {
{
	return mph_string_new(ctx, "MemberExpression");
}
	}
	if ((node_type == mph_ast_NODE_ASSIGNMENT_EXPRESSION)) {
{
	return mph_string_new(ctx, "AssignmentExpression");
}
	}
	return mph_string_new(ctx, "Unknown");
}

void mph_ast_visit_node(MorphContext* ctx, void* _env_void, mph_ast_Node* node) {
	mph_gc_push_root(ctx, (void**)&node);
	mph_native_print(ctx, mph_string_new(ctx, "Visiting "));
	mph_native_print(ctx, mph_ast_node_type_string(ctx, NULL, ({ mph_ast_Node* _obj_55 = node; mph_gc_push_root(ctx, (void**)&_obj_55); mph_int _ret_56 = _obj_55->node_type; mph_gc_pop_roots(ctx, 1); _ret_56; })));
	mph_native_print(ctx, mph_string_new(ctx, " at line "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_57 = node; mph_gc_push_root(ctx, (void**)&_obj_57); mph_int _ret_58 = _obj_57->line; mph_gc_pop_roots(ctx, 1); _ret_58; }));
	mph_native_print(ctx, mph_string_new(ctx, ", column "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_59 = node; mph_gc_push_root(ctx, (void**)&_obj_59); mph_int _ret_60 = _obj_59->column; mph_gc_pop_roots(ctx, 1); _ret_60; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	mph_native_print(ctx, mph_string_new(ctx, "Identifier: "));
	mph_native_print(ctx, ({ mph_ast_Identifier* _obj_61 = ident; mph_gc_push_root(ctx, (void**)&_obj_61); MorphString* _ret_62 = _obj_61->value; mph_gc_pop_roots(ctx, 1); _ret_62; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_65 = ({ mph_ast_Identifier* _obj_63 = ident; mph_gc_push_root(ctx, (void**)&_obj_63); mph_ast_Node* _ret_64 = _obj_63->base; mph_gc_pop_roots(ctx, 1); _ret_64; }); mph_gc_push_root(ctx, (void**)&_obj_65); mph_int _ret_66 = _obj_65->line; mph_gc_pop_roots(ctx, 1); _ret_66; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_69 = ({ mph_ast_Identifier* _obj_67 = ident; mph_gc_push_root(ctx, (void**)&_obj_67); mph_ast_Node* _ret_68 = _obj_67->base; mph_gc_pop_roots(ctx, 1); _ret_68; }); mph_gc_push_root(ctx, (void**)&_obj_69); mph_int _ret_70 = _obj_69->column; mph_gc_pop_roots(ctx, 1); _ret_70; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "IntegerLiteral: "));
	mph_native_print_int(ctx, ({ mph_ast_IntegerLiteral* _obj_71 = lit; mph_gc_push_root(ctx, (void**)&_obj_71); mph_int _ret_72 = _obj_71->value; mph_gc_pop_roots(ctx, 1); _ret_72; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_75 = ({ mph_ast_IntegerLiteral* _obj_73 = lit; mph_gc_push_root(ctx, (void**)&_obj_73); mph_ast_Node* _ret_74 = _obj_73->base; mph_gc_pop_roots(ctx, 1); _ret_74; }); mph_gc_push_root(ctx, (void**)&_obj_75); mph_int _ret_76 = _obj_75->line; mph_gc_pop_roots(ctx, 1); _ret_76; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_79 = ({ mph_ast_IntegerLiteral* _obj_77 = lit; mph_gc_push_root(ctx, (void**)&_obj_77); mph_ast_Node* _ret_78 = _obj_77->base; mph_gc_pop_roots(ctx, 1); _ret_78; }); mph_gc_push_root(ctx, (void**)&_obj_79); mph_int _ret_80 = _obj_79->column; mph_gc_pop_roots(ctx, 1); _ret_80; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "StringLiteral: \""));
	mph_native_print(ctx, ({ mph_ast_StringLiteral* _obj_81 = lit; mph_gc_push_root(ctx, (void**)&_obj_81); MorphString* _ret_82 = _obj_81->value; mph_gc_pop_roots(ctx, 1); _ret_82; }));
	mph_native_print(ctx, mph_string_new(ctx, "\" ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_85 = ({ mph_ast_StringLiteral* _obj_83 = lit; mph_gc_push_root(ctx, (void**)&_obj_83); mph_ast_Node* _ret_84 = _obj_83->base; mph_gc_pop_roots(ctx, 1); _ret_84; }); mph_gc_push_root(ctx, (void**)&_obj_85); mph_int _ret_86 = _obj_85->line; mph_gc_pop_roots(ctx, 1); _ret_86; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_89 = ({ mph_ast_StringLiteral* _obj_87 = lit; mph_gc_push_root(ctx, (void**)&_obj_87); mph_ast_Node* _ret_88 = _obj_87->base; mph_gc_pop_roots(ctx, 1); _ret_88; }); mph_gc_push_root(ctx, (void**)&_obj_89); mph_int _ret_90 = _obj_89->column; mph_gc_pop_roots(ctx, 1); _ret_90; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "BooleanLiteral: "));
	if (({ mph_ast_BooleanLiteral* _obj_91 = lit; mph_gc_push_root(ctx, (void**)&_obj_91); mph_bool _ret_92 = _obj_91->value; mph_gc_pop_roots(ctx, 1); _ret_92; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "benar"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "salah"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_95 = ({ mph_ast_BooleanLiteral* _obj_93 = lit; mph_gc_push_root(ctx, (void**)&_obj_93); mph_ast_Node* _ret_94 = _obj_93->base; mph_gc_pop_roots(ctx, 1); _ret_94; }); mph_gc_push_root(ctx, (void**)&_obj_95); mph_int _ret_96 = _obj_95->line; mph_gc_pop_roots(ctx, 1); _ret_96; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_99 = ({ mph_ast_BooleanLiteral* _obj_97 = lit; mph_gc_push_root(ctx, (void**)&_obj_97); mph_ast_Node* _ret_98 = _obj_97->base; mph_gc_pop_roots(ctx, 1); _ret_98; }); mph_gc_push_root(ctx, (void**)&_obj_99); mph_int _ret_100 = _obj_99->column; mph_gc_pop_roots(ctx, 1); _ret_100; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

mph_token_Token* mph_token_MakeToken(MorphContext* ctx, void* _env_void, mph_int t_type, MorphString* lit, mph_int ln, mph_int col) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_token_Token* _t = (mph_token_Token*)mph_alloc(ctx, sizeof(mph_token_Token), &mph_ti_mph_token_Token); mph_gc_push_root(ctx, (void**)&_t); _t->token_type = t_type; _t->literal = lit; _t->line = ln; _t->column = col; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_token_TokenTypeString(MorphContext* ctx, void* _env_void, mph_int t_type) {
	if ((t_type == mph_token_TOKEN_ILLEGAL)) {
{
	return mph_string_new(ctx, "ILLEGAL");
}
	}
	if ((t_type == mph_token_TOKEN_EOF)) {
{
	return mph_string_new(ctx, "EOF");
}
	}
	if ((t_type == mph_token_TOKEN_IDENT)) {
{
	return mph_string_new(ctx, "IDENT");
}
	}
	if ((t_type == mph_token_TOKEN_INT)) {
{
	return mph_string_new(ctx, "INT");
}
	}
	if ((t_type == mph_token_TOKEN_FLOAT)) {
{
	return mph_string_new(ctx, "FLOAT");
}
	}
	if ((t_type == mph_token_TOKEN_STRING)) {
{
	return mph_string_new(ctx, "STRING");
}
	}
	if ((t_type == mph_token_TOKEN_CHAR)) {
{
	return mph_string_new(ctx, "CHAR");
}
	}
	if ((t_type == mph_token_TOKEN_ASSIGN)) {
{
	return mph_string_new(ctx, "=");
}
	}
	if ((t_type == mph_token_TOKEN_PLUS)) {
{
	return mph_string_new(ctx, "+");
}
	}
	if ((t_type == mph_token_TOKEN_MINUS)) {
{
	return mph_string_new(ctx, "-");
}
	}
	if ((t_type == mph_token_TOKEN_BANG)) {
{
	return mph_string_new(ctx, "!");
}
	}
	if ((t_type == mph_token_TOKEN_ASTERISK)) {
{
	return mph_string_new(ctx, "*");
}
	}
	if ((t_type == mph_token_TOKEN_SLASH)) {
{
	return mph_string_new(ctx, "/");
}
	}
	if ((t_type == mph_token_TOKEN_PERCENT)) {
{
	return mph_string_new(ctx, "%");
}
	}
	if ((t_type == mph_token_TOKEN_LT)) {
{
	return mph_string_new(ctx, "<");
}
	}
	if ((t_type == mph_token_TOKEN_GT)) {
{
	return mph_string_new(ctx, ">");
}
	}
	if ((t_type == mph_token_TOKEN_EQ)) {
{
	return mph_string_new(ctx, "==");
}
	}
	if ((t_type == mph_token_TOKEN_NOT_EQ)) {
{
	return mph_string_new(ctx, "!=");
}
	}
	if ((t_type == mph_token_TOKEN_LE)) {
{
	return mph_string_new(ctx, "<=");
}
	}
	if ((t_type == mph_token_TOKEN_GE)) {
{
	return mph_string_new(ctx, ">=");
}
	}
	if ((t_type == mph_token_TOKEN_BIT_AND)) {
{
	return mph_string_new(ctx, "&");
}
	}
	if ((t_type == mph_token_TOKEN_BIT_OR)) {
{
	return mph_string_new(ctx, "|");
}
	}
	if ((t_type == mph_token_TOKEN_BIT_XOR)) {
{
	return mph_string_new(ctx, "^");
}
	}
	if ((t_type == mph_token_TOKEN_BIT_NOT)) {
{
	return mph_string_new(ctx, "~");
}
	}
	if ((t_type == mph_token_TOKEN_LSHIFT)) {
{
	return mph_string_new(ctx, "<<");
}
	}
	if ((t_type == mph_token_TOKEN_RSHIFT)) {
{
	return mph_string_new(ctx, ">>");
}
	}
	if ((t_type == mph_token_TOKEN_AND)) {
{
	return mph_string_new(ctx, "&&");
}
	}
	if ((t_type == mph_token_TOKEN_OR)) {
{
	return mph_string_new(ctx, "||");
}
	}
	if ((t_type == mph_token_TOKEN_COMMA)) {
{
	return mph_string_new(ctx, ",");
}
	}
	if ((t_type == mph_token_TOKEN_SEMICOLON)) {
{
	return mph_string_new(ctx, ";");
}
	}
	if ((t_type == mph_token_TOKEN_COLON)) {
{
	return mph_string_new(ctx, ":");
}
	}
	if ((t_type == mph_token_TOKEN_LPAREN)) {
{
	return mph_string_new(ctx, "(");
}
	}
	if ((t_type == mph_token_TOKEN_RPAREN)) {
{
	return mph_string_new(ctx, ")");
}
	}
	if ((t_type == mph_token_TOKEN_LBRACE)) {
{
	return mph_string_new(ctx, "{");
}
	}
	if ((t_type == mph_token_TOKEN_RBRACE)) {
{
	return mph_string_new(ctx, "}");
}
	}
	if ((t_type == mph_token_TOKEN_LBRACKET)) {
{
	return mph_string_new(ctx, "[");
}
	}
	if ((t_type == mph_token_TOKEN_RBRACKET)) {
{
	return mph_string_new(ctx, "]");
}
	}
	if ((t_type == mph_token_TOKEN_FUNGSI)) {
{
	return mph_string_new(ctx, "fungsi");
}
	}
	if ((t_type == mph_token_TOKEN_VAR)) {
{
	return mph_string_new(ctx, "var");
}
	}
	if ((t_type == mph_token_TOKEN_TETAPAN)) {
{
	return mph_string_new(ctx, "tetapan");
}
	}
	if ((t_type == mph_token_TOKEN_BENAR)) {
{
	return mph_string_new(ctx, "benar");
}
	}
	if ((t_type == mph_token_TOKEN_SALAH)) {
{
	return mph_string_new(ctx, "salah");
}
	}
	if ((t_type == mph_token_TOKEN_JIKA)) {
{
	return mph_string_new(ctx, "jika");
}
	}
	if ((t_type == mph_token_TOKEN_LAINNYA)) {
{
	return mph_string_new(ctx, "lainnya");
}
	}
	if ((t_type == mph_token_TOKEN_KEMBALIKAN)) {
{
	return mph_string_new(ctx, "kembalikan");
}
	}
	if ((t_type == mph_token_TOKEN_STRUKTUR)) {
{
	return mph_string_new(ctx, "struktur");
}
	}
	if ((t_type == mph_token_TOKEN_ANTARMUKA)) {
{
	return mph_string_new(ctx, "antarmuka");
}
	}
	if ((t_type == mph_token_TOKEN_AMBIL)) {
{
	return mph_string_new(ctx, "ambil");
}
	}
	if ((t_type == mph_token_TOKEN_UNTUK)) {
{
	return mph_string_new(ctx, "untuk");
}
	}
	if ((t_type == mph_token_TOKEN_SELAMA)) {
{
	return mph_string_new(ctx, "selama");
}
	}
	if ((t_type == mph_token_TOKEN_PUTUS)) {
{
	return mph_string_new(ctx, "putus");
}
	}
	if ((t_type == mph_token_TOKEN_LANJUT)) {
{
	return mph_string_new(ctx, "lanjut");
}
	}
	if ((t_type == mph_token_TOKEN_PILIH)) {
{
	return mph_string_new(ctx, "pilih");
}
	}
	if ((t_type == mph_token_TOKEN_KASUS)) {
{
	return mph_string_new(ctx, "kasus");
}
	}
	if ((t_type == mph_token_TOKEN_BAWAAN)) {
{
	return mph_string_new(ctx, "bawaan");
}
	}
	if ((t_type == mph_token_TOKEN_AKHIR)) {
{
	return mph_string_new(ctx, "akhir");
}
	}
	if ((t_type == mph_token_TOKEN_ATAU_JIKA)) {
{
	return mph_string_new(ctx, "atau_jika");
}
	}
	if ((t_type == mph_token_TOKEN_DAN)) {
{
	return mph_string_new(ctx, "dan");
}
	}
	if ((t_type == mph_token_TOKEN_ATAU)) {
{
	return mph_string_new(ctx, "atau");
}
	}
	if ((t_type == mph_token_TOKEN_KOSONG)) {
{
	return mph_string_new(ctx, "kosong");
}
	}
	if ((t_type == mph_token_TOKEN_LUNCURKAN)) {
{
	return mph_string_new(ctx, "luncurkan");
}
	}
	if ((t_type == mph_token_TOKEN_SALURAN_BARU)) {
{
	return mph_string_new(ctx, "saluran_baru");
}
	}
	if ((t_type == mph_token_TOKEN_KIRIM)) {
{
	return mph_string_new(ctx, "kirim");
}
	}
	if ((t_type == mph_token_TOKEN_TERIMA)) {
{
	return mph_string_new(ctx, "terima");
}
	}
	if ((t_type == mph_token_TOKEN_DOT)) {
{
	return mph_string_new(ctx, ".");
}
	}
	if ((t_type == mph_token_TOKEN_ARROW)) {
{
	return mph_string_new(ctx, "->");
}
	}
	return mph_string_new(ctx, "UNKNOWN");
}

mph_int mph_token_LookupKeyword(MorphContext* ctx, void* _env_void, MorphString* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "fungsi"))) {
{
	return mph_token_TOKEN_FUNGSI;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "var"))) {
{
	return mph_token_TOKEN_VAR;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "tetapan"))) {
{
	return mph_token_TOKEN_TETAPAN;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "benar"))) {
{
	return mph_token_TOKEN_BENAR;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "salah"))) {
{
	return mph_token_TOKEN_SALAH;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "jika"))) {
{
	return mph_token_TOKEN_JIKA;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "lainnya"))) {
{
	return mph_token_TOKEN_LAINNYA;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "kembalikan"))) {
{
	return mph_token_TOKEN_KEMBALIKAN;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "struktur"))) {
{
	return mph_token_TOKEN_STRUKTUR;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "antarmuka"))) {
{
	return mph_token_TOKEN_ANTARMUKA;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "ambil"))) {
{
	return mph_token_TOKEN_AMBIL;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "untuk"))) {
{
	return mph_token_TOKEN_UNTUK;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "selama"))) {
{
	return mph_token_TOKEN_SELAMA;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "putus"))) {
{
	return mph_token_TOKEN_PUTUS;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "lanjut"))) {
{
	return mph_token_TOKEN_LANJUT;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "pilih"))) {
{
	return mph_token_TOKEN_PILIH;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "kasus"))) {
{
	return mph_token_TOKEN_KASUS;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "bawaan"))) {
{
	return mph_token_TOKEN_BAWAAN;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "akhir"))) {
{
	return mph_token_TOKEN_AKHIR;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "atau_jika"))) {
{
	return mph_token_TOKEN_ATAU_JIKA;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "dan"))) {
{
	return mph_token_TOKEN_DAN;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "atau"))) {
{
	return mph_token_TOKEN_ATAU;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "kosong"))) {
{
	return mph_token_TOKEN_KOSONG;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "luncurkan"))) {
{
	return mph_token_TOKEN_LUNCURKAN;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "saluran_baru"))) {
{
	return mph_token_TOKEN_SALURAN_BARU;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "kirim"))) {
{
	return mph_token_TOKEN_KIRIM;
}
	}
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "terima"))) {
{
	return mph_token_TOKEN_TERIMA;
}
	}
	return mph_token_TOKEN_IDENT;
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_make_type(MorphContext* ctx, void* _env_void, mph_int k, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ mph_types_Type* _t = (mph_types_Type*)mph_alloc(ctx, sizeof(mph_types_Type), &mph_ti_mph_types_Type); mph_gc_push_root(ctx, (void**)&_t); _t->kind = k; _t->name = n; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_int_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_101 = mph_string_new(ctx, "int"); mph_gc_push_root(ctx, (void**)&_arg_101); mph_types_Type* _ret_102 = mph_types_make_type(ctx, NULL, mph_types_KIND_INT, _arg_101); mph_gc_pop_roots(ctx, 1); _ret_102; });
}

mph_types_Type* mph_types_float_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_103 = mph_string_new(ctx, "float"); mph_gc_push_root(ctx, (void**)&_arg_103); mph_types_Type* _ret_104 = mph_types_make_type(ctx, NULL, mph_types_KIND_FLOAT, _arg_103); mph_gc_pop_roots(ctx, 1); _ret_104; });
}

mph_types_Type* mph_types_string_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_105 = mph_string_new(ctx, "string"); mph_gc_push_root(ctx, (void**)&_arg_105); mph_types_Type* _ret_106 = mph_types_make_type(ctx, NULL, mph_types_KIND_STRING, _arg_105); mph_gc_pop_roots(ctx, 1); _ret_106; });
}

mph_types_Type* mph_types_bool_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_107 = mph_string_new(ctx, "bool"); mph_gc_push_root(ctx, (void**)&_arg_107); mph_types_Type* _ret_108 = mph_types_make_type(ctx, NULL, mph_types_KIND_BOOL, _arg_107); mph_gc_pop_roots(ctx, 1); _ret_108; });
}

mph_types_Type* mph_types_void_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_109 = mph_string_new(ctx, "void"); mph_gc_push_root(ctx, (void**)&_arg_109); mph_types_Type* _ret_110 = mph_types_make_type(ctx, NULL, mph_types_KIND_VOID, _arg_109); mph_gc_pop_roots(ctx, 1); _ret_110; });
}

mph_types_Type* mph_types_null_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_111 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_111); mph_types_Type* _ret_112 = mph_types_make_type(ctx, NULL, mph_types_KIND_NULL, _arg_111); mph_gc_pop_roots(ctx, 1); _ret_112; });
}

mph_types_Type* mph_types_unknown_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_113 = mph_string_new(ctx, "unknown"); mph_gc_push_root(ctx, (void**)&_arg_113); mph_types_Type* _ret_114 = mph_types_make_type(ctx, NULL, mph_types_KIND_UNKNOWN, _arg_113); mph_gc_pop_roots(ctx, 1); _ret_114; });
}

mph_types_Type* mph_types_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_115 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_115); mph_types_Type* _ret_116 = mph_types_make_type(ctx, NULL, mph_types_KIND_ERROR, _arg_115); mph_gc_pop_roots(ctx, 1); _ret_116; });
}

mph_types_Type* mph_types_user_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_117 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_117); mph_types_Type* _ret_118 = mph_types_make_type(ctx, NULL, mph_types_KIND_USER_ERROR, _arg_117); mph_gc_pop_roots(ctx, 1); _ret_118; });
}

mph_types_Type* mph_types_channel_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_119 = mph_string_new(ctx, "channel"); mph_gc_push_root(ctx, (void**)&_arg_119); mph_types_Type* _ret_120 = mph_types_make_type(ctx, NULL, mph_types_KIND_CHANNEL, _arg_119); mph_gc_pop_roots(ctx, 1); _ret_120; });
}

mph_types_Type* mph_types_array_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_121 = mph_string_new(ctx, "array"); mph_gc_push_root(ctx, (void**)&_arg_121); mph_types_Type* _ret_122 = mph_types_make_type(ctx, NULL, mph_types_KIND_ARRAY, _arg_121); mph_gc_pop_roots(ctx, 1); _ret_122; });
}

mph_types_Type* mph_types_map_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_123 = mph_string_new(ctx, "map"); mph_gc_push_root(ctx, (void**)&_arg_123); mph_types_Type* _ret_124 = mph_types_make_type(ctx, NULL, mph_types_KIND_MAP, _arg_123); mph_gc_pop_roots(ctx, 1); _ret_124; });
}

mph_types_Type* mph_types_struct_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_125 = n; mph_gc_push_root(ctx, (void**)&_arg_125); mph_types_Type* _ret_126 = mph_types_make_type(ctx, NULL, mph_types_KIND_STRUCT, _arg_125); mph_gc_pop_roots(ctx, 1); _ret_126; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_interface_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_127 = n; mph_gc_push_root(ctx, (void**)&_arg_127); mph_types_Type* _ret_128 = mph_types_make_type(ctx, NULL, mph_types_KIND_INTERFACE, _arg_127); mph_gc_pop_roots(ctx, 1); _ret_128; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_function_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_129 = mph_string_new(ctx, "function"); mph_gc_push_root(ctx, (void**)&_arg_129); mph_types_Type* _ret_130 = mph_types_make_type(ctx, NULL, mph_types_KIND_FUNCTION, _arg_129); mph_gc_pop_roots(ctx, 1); _ret_130; });
}

mph_types_Type* mph_types_pointer_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_131 = mph_string_new(ctx, "pointer"); mph_gc_push_root(ctx, (void**)&_arg_131); mph_types_Type* _ret_132 = mph_types_make_type(ctx, NULL, mph_types_KIND_POINTER, _arg_131); mph_gc_pop_roots(ctx, 1); _ret_132; });
}

mph_types_Type* mph_types_multi_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_133 = mph_string_new(ctx, "multi"); mph_gc_push_root(ctx, (void**)&_arg_133); mph_types_Type* _ret_134 = mph_types_make_type(ctx, NULL, mph_types_KIND_MULTI, _arg_133); mph_gc_pop_roots(ctx, 1); _ret_134; });
}

mph_types_Type* mph_types_module_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_135 = n; mph_gc_push_root(ctx, (void**)&_arg_135); mph_types_Type* _ret_136 = mph_types_make_type(ctx, NULL, mph_types_KIND_MODULE, _arg_135); mph_gc_pop_roots(ctx, 1); _ret_136; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_types_type_equals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return (({ mph_types_Type* _obj_137 = t1; mph_gc_push_root(ctx, (void**)&_obj_137); mph_int _ret_138 = _obj_137->kind; mph_gc_pop_roots(ctx, 1); _ret_138; }) == ({ mph_types_Type* _obj_139 = t2; mph_gc_push_root(ctx, (void**)&_obj_139); mph_int _ret_140 = _obj_139->kind; mph_gc_pop_roots(ctx, 1); _ret_140; }));
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_type_assignable_to(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	if ((({ mph_types_Type* _obj_141 = source; mph_gc_push_root(ctx, (void**)&_obj_141); mph_int _ret_142 = _obj_141->kind; mph_gc_pop_roots(ctx, 1); _ret_142; }) == mph_types_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_143 = target; mph_gc_push_root(ctx, (void**)&_obj_143); mph_int _ret_144 = _obj_143->kind; mph_gc_pop_roots(ctx, 1); _ret_144; }) == mph_types_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_145 = source; mph_gc_push_root(ctx, (void**)&_obj_145); mph_int _ret_146 = _obj_145->kind; mph_gc_pop_roots(ctx, 1); _ret_146; }) == mph_types_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_147 = target; mph_gc_push_root(ctx, (void**)&_obj_147); mph_int _ret_148 = _obj_147->kind; mph_gc_pop_roots(ctx, 1); _ret_148; }) == mph_types_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_149 = source; mph_gc_push_root(ctx, (void**)&_obj_149); mph_int _ret_150 = _obj_149->kind; mph_gc_pop_roots(ctx, 1); _ret_150; }) == mph_types_KIND_NULL)) {
{
	if ((({ mph_types_Type* _obj_151 = target; mph_gc_push_root(ctx, (void**)&_obj_151); mph_int _ret_152 = _obj_151->kind; mph_gc_pop_roots(ctx, 1); _ret_152; }) == mph_types_KIND_ARRAY)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_153 = target; mph_gc_push_root(ctx, (void**)&_obj_153); mph_int _ret_154 = _obj_153->kind; mph_gc_pop_roots(ctx, 1); _ret_154; }) == mph_types_KIND_MAP)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_155 = target; mph_gc_push_root(ctx, (void**)&_obj_155); mph_int _ret_156 = _obj_155->kind; mph_gc_pop_roots(ctx, 1); _ret_156; }) == mph_types_KIND_POINTER)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_157 = target; mph_gc_push_root(ctx, (void**)&_obj_157); mph_int _ret_158 = _obj_157->kind; mph_gc_pop_roots(ctx, 1); _ret_158; }) == mph_types_KIND_INTERFACE)) {
{
	return 1;
}
	}
	return 0;
}
	}
	return ({ mph_types_Type* _arg_159 = source; mph_gc_push_root(ctx, (void**)&_arg_159); mph_types_Type* _arg_160 = target; mph_gc_push_root(ctx, (void**)&_arg_160); mph_bool _ret_161 = mph_types_type_equals(ctx, NULL, _arg_159, _arg_160); mph_gc_pop_roots(ctx, 2); _ret_161; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_type_is_comparable(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	if ((({ mph_types_Type* _obj_162 = t; mph_gc_push_root(ctx, (void**)&_obj_162); mph_int _ret_163 = _obj_162->kind; mph_gc_pop_roots(ctx, 1); _ret_163; }) == mph_types_KIND_INT)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_164 = t; mph_gc_push_root(ctx, (void**)&_obj_164); mph_int _ret_165 = _obj_164->kind; mph_gc_pop_roots(ctx, 1); _ret_165; }) == mph_types_KIND_FLOAT)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_166 = t; mph_gc_push_root(ctx, (void**)&_obj_166); mph_int _ret_167 = _obj_166->kind; mph_gc_pop_roots(ctx, 1); _ret_167; }) == mph_types_KIND_STRING)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_168 = t; mph_gc_push_root(ctx, (void**)&_obj_168); mph_int _ret_169 = _obj_168->kind; mph_gc_pop_roots(ctx, 1); _ret_169; }) == mph_types_KIND_BOOL)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_170 = t; mph_gc_push_root(ctx, (void**)&_obj_170); mph_int _ret_171 = _obj_170->kind; mph_gc_pop_roots(ctx, 1); _ret_171; }) == mph_types_KIND_NULL)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_172 = t; mph_gc_push_root(ctx, (void**)&_obj_172); mph_int _ret_173 = _obj_172->kind; mph_gc_pop_roots(ctx, 1); _ret_173; }) == mph_types_KIND_USER_ERROR)) {
{
	return 1;
}
	}
	return 0;
	mph_gc_pop_roots(ctx, 1);
}

mph_types_TypeResult* mph_types_make_type_result(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_types_TypeResult* _t = (mph_types_TypeResult*)mph_alloc(ctx, sizeof(mph_types_TypeResult), &mph_ti_mph_types_TypeResult); mph_gc_push_root(ctx, (void**)&_t); _t->has_error = 0; _t->result = t; _t->error_msg = mph_string_new(ctx, "ok"); mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_TypeResult* mph_types_make_type_error(MorphContext* ctx, void* _env_void, MorphString* msg) {
	mph_gc_push_root(ctx, (void**)&msg);
	return ({ mph_types_TypeResult* _t = (mph_types_TypeResult*)mph_alloc(ctx, sizeof(mph_types_TypeResult), &mph_ti_mph_types_TypeResult); mph_gc_push_root(ctx, (void**)&_t); _t->result = mph_types_error_type(ctx, NULL); _t->error_msg = msg; _t->has_error = 1; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_TypeResult* mph_types_type_binary_op(MorphContext* ctx, void* _env_void, mph_types_Type* left, MorphString* op, mph_types_Type* right) {
	mph_gc_push_root(ctx, (void**)&left);
	mph_gc_push_root(ctx, (void**)&op);
	mph_gc_push_root(ctx, (void**)&right);
	if ((({ mph_types_Type* _obj_174 = left; mph_gc_push_root(ctx, (void**)&_obj_174); mph_int _ret_175 = _obj_174->kind; mph_gc_pop_roots(ctx, 1); _ret_175; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_176 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_176); mph_types_TypeResult* _ret_177 = mph_types_make_type_result(ctx, NULL, _arg_176); mph_gc_pop_roots(ctx, 1); _ret_177; });
}
	}
	if ((({ mph_types_Type* _obj_178 = right; mph_gc_push_root(ctx, (void**)&_obj_178); mph_int _ret_179 = _obj_178->kind; mph_gc_pop_roots(ctx, 1); _ret_179; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_180 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_180); mph_types_TypeResult* _ret_181 = mph_types_make_type_result(ctx, NULL, _arg_180); mph_gc_pop_roots(ctx, 1); _ret_181; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "+"))) {
{
	if ((({ mph_types_Type* _obj_182 = left; mph_gc_push_root(ctx, (void**)&_obj_182); mph_int _ret_183 = _obj_182->kind; mph_gc_pop_roots(ctx, 1); _ret_183; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_184 = right; mph_gc_push_root(ctx, (void**)&_obj_184); mph_int _ret_185 = _obj_184->kind; mph_gc_pop_roots(ctx, 1); _ret_185; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_186 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_186); mph_types_TypeResult* _ret_187 = mph_types_make_type_result(ctx, NULL, _arg_186); mph_gc_pop_roots(ctx, 1); _ret_187; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_188 = left; mph_gc_push_root(ctx, (void**)&_obj_188); mph_int _ret_189 = _obj_188->kind; mph_gc_pop_roots(ctx, 1); _ret_189; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_190 = right; mph_gc_push_root(ctx, (void**)&_obj_190); mph_int _ret_191 = _obj_190->kind; mph_gc_pop_roots(ctx, 1); _ret_191; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_192 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_192); mph_types_TypeResult* _ret_193 = mph_types_make_type_result(ctx, NULL, _arg_192); mph_gc_pop_roots(ctx, 1); _ret_193; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_194 = left; mph_gc_push_root(ctx, (void**)&_obj_194); mph_int _ret_195 = _obj_194->kind; mph_gc_pop_roots(ctx, 1); _ret_195; }) == mph_types_KIND_STRING)) {
{
	if ((({ mph_types_Type* _obj_196 = right; mph_gc_push_root(ctx, (void**)&_obj_196); mph_int _ret_197 = _obj_196->kind; mph_gc_pop_roots(ctx, 1); _ret_197; }) == mph_types_KIND_STRING)) {
{
	return ({ mph_types_Type* _arg_198 = mph_types_string_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_198); mph_types_TypeResult* _ret_199 = mph_types_make_type_result(ctx, NULL, _arg_198); mph_gc_pop_roots(ctx, 1); _ret_199; });
}
	}
}
	}
	return ({ MorphString* _arg_200 = mph_string_new(ctx, "+ tidak didukung untuk tipe ini"); mph_gc_push_root(ctx, (void**)&_arg_200); mph_types_TypeResult* _ret_201 = mph_types_make_type_error(ctx, NULL, _arg_200); mph_gc_pop_roots(ctx, 1); _ret_201; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_types_Type* _obj_202 = left; mph_gc_push_root(ctx, (void**)&_obj_202); mph_int _ret_203 = _obj_202->kind; mph_gc_pop_roots(ctx, 1); _ret_203; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_204 = right; mph_gc_push_root(ctx, (void**)&_obj_204); mph_int _ret_205 = _obj_204->kind; mph_gc_pop_roots(ctx, 1); _ret_205; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_206 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_206); mph_types_TypeResult* _ret_207 = mph_types_make_type_result(ctx, NULL, _arg_206); mph_gc_pop_roots(ctx, 1); _ret_207; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_208 = left; mph_gc_push_root(ctx, (void**)&_obj_208); mph_int _ret_209 = _obj_208->kind; mph_gc_pop_roots(ctx, 1); _ret_209; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_210 = right; mph_gc_push_root(ctx, (void**)&_obj_210); mph_int _ret_211 = _obj_210->kind; mph_gc_pop_roots(ctx, 1); _ret_211; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_212 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_212); mph_types_TypeResult* _ret_213 = mph_types_make_type_result(ctx, NULL, _arg_212); mph_gc_pop_roots(ctx, 1); _ret_213; });
}
	}
}
	}
	return ({ MorphString* _arg_214 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_214); mph_types_TypeResult* _ret_215 = mph_types_make_type_error(ctx, NULL, _arg_214); mph_gc_pop_roots(ctx, 1); _ret_215; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "*"))) {
{
	if ((({ mph_types_Type* _obj_216 = left; mph_gc_push_root(ctx, (void**)&_obj_216); mph_int _ret_217 = _obj_216->kind; mph_gc_pop_roots(ctx, 1); _ret_217; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_218 = right; mph_gc_push_root(ctx, (void**)&_obj_218); mph_int _ret_219 = _obj_218->kind; mph_gc_pop_roots(ctx, 1); _ret_219; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_220 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_220); mph_types_TypeResult* _ret_221 = mph_types_make_type_result(ctx, NULL, _arg_220); mph_gc_pop_roots(ctx, 1); _ret_221; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_222 = left; mph_gc_push_root(ctx, (void**)&_obj_222); mph_int _ret_223 = _obj_222->kind; mph_gc_pop_roots(ctx, 1); _ret_223; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_224 = right; mph_gc_push_root(ctx, (void**)&_obj_224); mph_int _ret_225 = _obj_224->kind; mph_gc_pop_roots(ctx, 1); _ret_225; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_226 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_226); mph_types_TypeResult* _ret_227 = mph_types_make_type_result(ctx, NULL, _arg_226); mph_gc_pop_roots(ctx, 1); _ret_227; });
}
	}
}
	}
	return ({ MorphString* _arg_228 = mph_string_new(ctx, "* memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_228); mph_types_TypeResult* _ret_229 = mph_types_make_type_error(ctx, NULL, _arg_228); mph_gc_pop_roots(ctx, 1); _ret_229; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "/"))) {
{
	if ((({ mph_types_Type* _obj_230 = left; mph_gc_push_root(ctx, (void**)&_obj_230); mph_int _ret_231 = _obj_230->kind; mph_gc_pop_roots(ctx, 1); _ret_231; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_232 = right; mph_gc_push_root(ctx, (void**)&_obj_232); mph_int _ret_233 = _obj_232->kind; mph_gc_pop_roots(ctx, 1); _ret_233; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_234 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_234); mph_types_TypeResult* _ret_235 = mph_types_make_type_result(ctx, NULL, _arg_234); mph_gc_pop_roots(ctx, 1); _ret_235; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_236 = left; mph_gc_push_root(ctx, (void**)&_obj_236); mph_int _ret_237 = _obj_236->kind; mph_gc_pop_roots(ctx, 1); _ret_237; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_238 = right; mph_gc_push_root(ctx, (void**)&_obj_238); mph_int _ret_239 = _obj_238->kind; mph_gc_pop_roots(ctx, 1); _ret_239; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_240 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_240); mph_types_TypeResult* _ret_241 = mph_types_make_type_result(ctx, NULL, _arg_240); mph_gc_pop_roots(ctx, 1); _ret_241; });
}
	}
}
	}
	return ({ MorphString* _arg_242 = mph_string_new(ctx, "/ memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_242); mph_types_TypeResult* _ret_243 = mph_types_make_type_error(ctx, NULL, _arg_242); mph_gc_pop_roots(ctx, 1); _ret_243; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "%"))) {
{
	if ((({ mph_types_Type* _obj_244 = left; mph_gc_push_root(ctx, (void**)&_obj_244); mph_int _ret_245 = _obj_244->kind; mph_gc_pop_roots(ctx, 1); _ret_245; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_246 = right; mph_gc_push_root(ctx, (void**)&_obj_246); mph_int _ret_247 = _obj_246->kind; mph_gc_pop_roots(ctx, 1); _ret_247; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_248 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_248); mph_types_TypeResult* _ret_249 = mph_types_make_type_result(ctx, NULL, _arg_248); mph_gc_pop_roots(ctx, 1); _ret_249; });
}
	}
}
	}
	return ({ MorphString* _arg_250 = mph_string_new(ctx, "% memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_250); mph_types_TypeResult* _ret_251 = mph_types_make_type_error(ctx, NULL, _arg_250); mph_gc_pop_roots(ctx, 1); _ret_251; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "=="))) {
{
	if (({ mph_types_Type* _arg_252 = left; mph_gc_push_root(ctx, (void**)&_arg_252); mph_types_Type* _arg_253 = right; mph_gc_push_root(ctx, (void**)&_arg_253); mph_bool _ret_254 = mph_types_type_equals(ctx, NULL, _arg_252, _arg_253); mph_gc_pop_roots(ctx, 2); _ret_254; })) {
{
	return ({ mph_types_Type* _arg_255 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_255); mph_types_TypeResult* _ret_256 = mph_types_make_type_result(ctx, NULL, _arg_255); mph_gc_pop_roots(ctx, 1); _ret_256; });
}
	}
	if ((({ mph_types_Type* _obj_257 = left; mph_gc_push_root(ctx, (void**)&_obj_257); mph_int _ret_258 = _obj_257->kind; mph_gc_pop_roots(ctx, 1); _ret_258; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_259 = left; mph_gc_push_root(ctx, (void**)&_arg_259); mph_types_Type* _arg_260 = right; mph_gc_push_root(ctx, (void**)&_arg_260); mph_bool _ret_261 = mph_types_type_assignable_to(ctx, NULL, _arg_259, _arg_260); mph_gc_pop_roots(ctx, 2); _ret_261; })) {
{
	return ({ mph_types_Type* _arg_262 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_262); mph_types_TypeResult* _ret_263 = mph_types_make_type_result(ctx, NULL, _arg_262); mph_gc_pop_roots(ctx, 1); _ret_263; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_264 = right; mph_gc_push_root(ctx, (void**)&_obj_264); mph_int _ret_265 = _obj_264->kind; mph_gc_pop_roots(ctx, 1); _ret_265; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_266 = right; mph_gc_push_root(ctx, (void**)&_arg_266); mph_types_Type* _arg_267 = left; mph_gc_push_root(ctx, (void**)&_arg_267); mph_bool _ret_268 = mph_types_type_assignable_to(ctx, NULL, _arg_266, _arg_267); mph_gc_pop_roots(ctx, 2); _ret_268; })) {
{
	return ({ mph_types_Type* _arg_269 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_269); mph_types_TypeResult* _ret_270 = mph_types_make_type_result(ctx, NULL, _arg_269); mph_gc_pop_roots(ctx, 1); _ret_270; });
}
	}
}
	}
	return ({ MorphString* _arg_271 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_271); mph_types_TypeResult* _ret_272 = mph_types_make_type_error(ctx, NULL, _arg_271); mph_gc_pop_roots(ctx, 1); _ret_272; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!="))) {
{
	if (({ mph_types_Type* _arg_273 = left; mph_gc_push_root(ctx, (void**)&_arg_273); mph_types_Type* _arg_274 = right; mph_gc_push_root(ctx, (void**)&_arg_274); mph_bool _ret_275 = mph_types_type_equals(ctx, NULL, _arg_273, _arg_274); mph_gc_pop_roots(ctx, 2); _ret_275; })) {
{
	return ({ mph_types_Type* _arg_276 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_276); mph_types_TypeResult* _ret_277 = mph_types_make_type_result(ctx, NULL, _arg_276); mph_gc_pop_roots(ctx, 1); _ret_277; });
}
	}
	if ((({ mph_types_Type* _obj_278 = left; mph_gc_push_root(ctx, (void**)&_obj_278); mph_int _ret_279 = _obj_278->kind; mph_gc_pop_roots(ctx, 1); _ret_279; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_280 = left; mph_gc_push_root(ctx, (void**)&_arg_280); mph_types_Type* _arg_281 = right; mph_gc_push_root(ctx, (void**)&_arg_281); mph_bool _ret_282 = mph_types_type_assignable_to(ctx, NULL, _arg_280, _arg_281); mph_gc_pop_roots(ctx, 2); _ret_282; })) {
{
	return ({ mph_types_Type* _arg_283 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_283); mph_types_TypeResult* _ret_284 = mph_types_make_type_result(ctx, NULL, _arg_283); mph_gc_pop_roots(ctx, 1); _ret_284; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_285 = right; mph_gc_push_root(ctx, (void**)&_obj_285); mph_int _ret_286 = _obj_285->kind; mph_gc_pop_roots(ctx, 1); _ret_286; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_287 = right; mph_gc_push_root(ctx, (void**)&_arg_287); mph_types_Type* _arg_288 = left; mph_gc_push_root(ctx, (void**)&_arg_288); mph_bool _ret_289 = mph_types_type_assignable_to(ctx, NULL, _arg_287, _arg_288); mph_gc_pop_roots(ctx, 2); _ret_289; })) {
{
	return ({ mph_types_Type* _arg_290 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_290); mph_types_TypeResult* _ret_291 = mph_types_make_type_result(ctx, NULL, _arg_290); mph_gc_pop_roots(ctx, 1); _ret_291; });
}
	}
}
	}
	return ({ MorphString* _arg_292 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_292); mph_types_TypeResult* _ret_293 = mph_types_make_type_error(ctx, NULL, _arg_292); mph_gc_pop_roots(ctx, 1); _ret_293; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&&"))) {
{
	if ((({ mph_types_Type* _obj_294 = left; mph_gc_push_root(ctx, (void**)&_obj_294); mph_int _ret_295 = _obj_294->kind; mph_gc_pop_roots(ctx, 1); _ret_295; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_296 = right; mph_gc_push_root(ctx, (void**)&_obj_296); mph_int _ret_297 = _obj_296->kind; mph_gc_pop_roots(ctx, 1); _ret_297; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_298 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_298); mph_types_TypeResult* _ret_299 = mph_types_make_type_result(ctx, NULL, _arg_298); mph_gc_pop_roots(ctx, 1); _ret_299; });
}
	}
}
	}
	return ({ MorphString* _arg_300 = mph_string_new(ctx, "&& memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_300); mph_types_TypeResult* _ret_301 = mph_types_make_type_error(ctx, NULL, _arg_300); mph_gc_pop_roots(ctx, 1); _ret_301; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "||"))) {
{
	if ((({ mph_types_Type* _obj_302 = left; mph_gc_push_root(ctx, (void**)&_obj_302); mph_int _ret_303 = _obj_302->kind; mph_gc_pop_roots(ctx, 1); _ret_303; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_304 = right; mph_gc_push_root(ctx, (void**)&_obj_304); mph_int _ret_305 = _obj_304->kind; mph_gc_pop_roots(ctx, 1); _ret_305; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_306 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_306); mph_types_TypeResult* _ret_307 = mph_types_make_type_result(ctx, NULL, _arg_306); mph_gc_pop_roots(ctx, 1); _ret_307; });
}
	}
}
	}
	return ({ MorphString* _arg_308 = mph_string_new(ctx, "|| memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_308); mph_types_TypeResult* _ret_309 = mph_types_make_type_error(ctx, NULL, _arg_308); mph_gc_pop_roots(ctx, 1); _ret_309; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "dan"))) {
{
	if ((({ mph_types_Type* _obj_310 = left; mph_gc_push_root(ctx, (void**)&_obj_310); mph_int _ret_311 = _obj_310->kind; mph_gc_pop_roots(ctx, 1); _ret_311; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_312 = right; mph_gc_push_root(ctx, (void**)&_obj_312); mph_int _ret_313 = _obj_312->kind; mph_gc_pop_roots(ctx, 1); _ret_313; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_314 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_314); mph_types_TypeResult* _ret_315 = mph_types_make_type_result(ctx, NULL, _arg_314); mph_gc_pop_roots(ctx, 1); _ret_315; });
}
	}
}
	}
	return ({ MorphString* _arg_316 = mph_string_new(ctx, "dan memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_316); mph_types_TypeResult* _ret_317 = mph_types_make_type_error(ctx, NULL, _arg_316); mph_gc_pop_roots(ctx, 1); _ret_317; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "atau"))) {
{
	if ((({ mph_types_Type* _obj_318 = left; mph_gc_push_root(ctx, (void**)&_obj_318); mph_int _ret_319 = _obj_318->kind; mph_gc_pop_roots(ctx, 1); _ret_319; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_320 = right; mph_gc_push_root(ctx, (void**)&_obj_320); mph_int _ret_321 = _obj_320->kind; mph_gc_pop_roots(ctx, 1); _ret_321; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_322 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_322); mph_types_TypeResult* _ret_323 = mph_types_make_type_result(ctx, NULL, _arg_322); mph_gc_pop_roots(ctx, 1); _ret_323; });
}
	}
}
	}
	return ({ MorphString* _arg_324 = mph_string_new(ctx, "atau memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_324); mph_types_TypeResult* _ret_325 = mph_types_make_type_error(ctx, NULL, _arg_324); mph_gc_pop_roots(ctx, 1); _ret_325; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<"))) {
{
	if ((({ mph_types_Type* _obj_326 = left; mph_gc_push_root(ctx, (void**)&_obj_326); mph_int _ret_327 = _obj_326->kind; mph_gc_pop_roots(ctx, 1); _ret_327; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_328 = right; mph_gc_push_root(ctx, (void**)&_obj_328); mph_int _ret_329 = _obj_328->kind; mph_gc_pop_roots(ctx, 1); _ret_329; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_330 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_330); mph_types_TypeResult* _ret_331 = mph_types_make_type_result(ctx, NULL, _arg_330); mph_gc_pop_roots(ctx, 1); _ret_331; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_332 = left; mph_gc_push_root(ctx, (void**)&_obj_332); mph_int _ret_333 = _obj_332->kind; mph_gc_pop_roots(ctx, 1); _ret_333; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_334 = right; mph_gc_push_root(ctx, (void**)&_obj_334); mph_int _ret_335 = _obj_334->kind; mph_gc_pop_roots(ctx, 1); _ret_335; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_336 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_336); mph_types_TypeResult* _ret_337 = mph_types_make_type_result(ctx, NULL, _arg_336); mph_gc_pop_roots(ctx, 1); _ret_337; });
}
	}
}
	}
	return ({ MorphString* _arg_338 = mph_string_new(ctx, "< memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_338); mph_types_TypeResult* _ret_339 = mph_types_make_type_error(ctx, NULL, _arg_338); mph_gc_pop_roots(ctx, 1); _ret_339; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">"))) {
{
	if ((({ mph_types_Type* _obj_340 = left; mph_gc_push_root(ctx, (void**)&_obj_340); mph_int _ret_341 = _obj_340->kind; mph_gc_pop_roots(ctx, 1); _ret_341; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_342 = right; mph_gc_push_root(ctx, (void**)&_obj_342); mph_int _ret_343 = _obj_342->kind; mph_gc_pop_roots(ctx, 1); _ret_343; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_344 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_344); mph_types_TypeResult* _ret_345 = mph_types_make_type_result(ctx, NULL, _arg_344); mph_gc_pop_roots(ctx, 1); _ret_345; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_346 = left; mph_gc_push_root(ctx, (void**)&_obj_346); mph_int _ret_347 = _obj_346->kind; mph_gc_pop_roots(ctx, 1); _ret_347; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_348 = right; mph_gc_push_root(ctx, (void**)&_obj_348); mph_int _ret_349 = _obj_348->kind; mph_gc_pop_roots(ctx, 1); _ret_349; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_350 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_350); mph_types_TypeResult* _ret_351 = mph_types_make_type_result(ctx, NULL, _arg_350); mph_gc_pop_roots(ctx, 1); _ret_351; });
}
	}
}
	}
	return ({ MorphString* _arg_352 = mph_string_new(ctx, "> memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_352); mph_types_TypeResult* _ret_353 = mph_types_make_type_error(ctx, NULL, _arg_352); mph_gc_pop_roots(ctx, 1); _ret_353; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<="))) {
{
	if ((({ mph_types_Type* _obj_354 = left; mph_gc_push_root(ctx, (void**)&_obj_354); mph_int _ret_355 = _obj_354->kind; mph_gc_pop_roots(ctx, 1); _ret_355; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_356 = right; mph_gc_push_root(ctx, (void**)&_obj_356); mph_int _ret_357 = _obj_356->kind; mph_gc_pop_roots(ctx, 1); _ret_357; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_358 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_358); mph_types_TypeResult* _ret_359 = mph_types_make_type_result(ctx, NULL, _arg_358); mph_gc_pop_roots(ctx, 1); _ret_359; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_360 = left; mph_gc_push_root(ctx, (void**)&_obj_360); mph_int _ret_361 = _obj_360->kind; mph_gc_pop_roots(ctx, 1); _ret_361; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_362 = right; mph_gc_push_root(ctx, (void**)&_obj_362); mph_int _ret_363 = _obj_362->kind; mph_gc_pop_roots(ctx, 1); _ret_363; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_364 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_364); mph_types_TypeResult* _ret_365 = mph_types_make_type_result(ctx, NULL, _arg_364); mph_gc_pop_roots(ctx, 1); _ret_365; });
}
	}
}
	}
	return ({ MorphString* _arg_366 = mph_string_new(ctx, "<= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_366); mph_types_TypeResult* _ret_367 = mph_types_make_type_error(ctx, NULL, _arg_366); mph_gc_pop_roots(ctx, 1); _ret_367; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">="))) {
{
	if ((({ mph_types_Type* _obj_368 = left; mph_gc_push_root(ctx, (void**)&_obj_368); mph_int _ret_369 = _obj_368->kind; mph_gc_pop_roots(ctx, 1); _ret_369; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_370 = right; mph_gc_push_root(ctx, (void**)&_obj_370); mph_int _ret_371 = _obj_370->kind; mph_gc_pop_roots(ctx, 1); _ret_371; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_372 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_372); mph_types_TypeResult* _ret_373 = mph_types_make_type_result(ctx, NULL, _arg_372); mph_gc_pop_roots(ctx, 1); _ret_373; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_374 = left; mph_gc_push_root(ctx, (void**)&_obj_374); mph_int _ret_375 = _obj_374->kind; mph_gc_pop_roots(ctx, 1); _ret_375; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_376 = right; mph_gc_push_root(ctx, (void**)&_obj_376); mph_int _ret_377 = _obj_376->kind; mph_gc_pop_roots(ctx, 1); _ret_377; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_378 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_378); mph_types_TypeResult* _ret_379 = mph_types_make_type_result(ctx, NULL, _arg_378); mph_gc_pop_roots(ctx, 1); _ret_379; });
}
	}
}
	}
	return ({ MorphString* _arg_380 = mph_string_new(ctx, ">= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_380); mph_types_TypeResult* _ret_381 = mph_types_make_type_error(ctx, NULL, _arg_380); mph_gc_pop_roots(ctx, 1); _ret_381; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&"))) {
{
	if ((({ mph_types_Type* _obj_382 = left; mph_gc_push_root(ctx, (void**)&_obj_382); mph_int _ret_383 = _obj_382->kind; mph_gc_pop_roots(ctx, 1); _ret_383; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_384 = right; mph_gc_push_root(ctx, (void**)&_obj_384); mph_int _ret_385 = _obj_384->kind; mph_gc_pop_roots(ctx, 1); _ret_385; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_386 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_386); mph_types_TypeResult* _ret_387 = mph_types_make_type_result(ctx, NULL, _arg_386); mph_gc_pop_roots(ctx, 1); _ret_387; });
}
	}
}
	}
	return ({ MorphString* _arg_388 = mph_string_new(ctx, "& memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_388); mph_types_TypeResult* _ret_389 = mph_types_make_type_error(ctx, NULL, _arg_388); mph_gc_pop_roots(ctx, 1); _ret_389; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "|"))) {
{
	if ((({ mph_types_Type* _obj_390 = left; mph_gc_push_root(ctx, (void**)&_obj_390); mph_int _ret_391 = _obj_390->kind; mph_gc_pop_roots(ctx, 1); _ret_391; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_392 = right; mph_gc_push_root(ctx, (void**)&_obj_392); mph_int _ret_393 = _obj_392->kind; mph_gc_pop_roots(ctx, 1); _ret_393; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_394 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_394); mph_types_TypeResult* _ret_395 = mph_types_make_type_result(ctx, NULL, _arg_394); mph_gc_pop_roots(ctx, 1); _ret_395; });
}
	}
}
	}
	return ({ MorphString* _arg_396 = mph_string_new(ctx, "| memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_396); mph_types_TypeResult* _ret_397 = mph_types_make_type_error(ctx, NULL, _arg_396); mph_gc_pop_roots(ctx, 1); _ret_397; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "^"))) {
{
	if ((({ mph_types_Type* _obj_398 = left; mph_gc_push_root(ctx, (void**)&_obj_398); mph_int _ret_399 = _obj_398->kind; mph_gc_pop_roots(ctx, 1); _ret_399; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_400 = right; mph_gc_push_root(ctx, (void**)&_obj_400); mph_int _ret_401 = _obj_400->kind; mph_gc_pop_roots(ctx, 1); _ret_401; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_402 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_402); mph_types_TypeResult* _ret_403 = mph_types_make_type_result(ctx, NULL, _arg_402); mph_gc_pop_roots(ctx, 1); _ret_403; });
}
	}
}
	}
	return ({ MorphString* _arg_404 = mph_string_new(ctx, "^ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_404); mph_types_TypeResult* _ret_405 = mph_types_make_type_error(ctx, NULL, _arg_404); mph_gc_pop_roots(ctx, 1); _ret_405; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<<"))) {
{
	if ((({ mph_types_Type* _obj_406 = left; mph_gc_push_root(ctx, (void**)&_obj_406); mph_int _ret_407 = _obj_406->kind; mph_gc_pop_roots(ctx, 1); _ret_407; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_408 = right; mph_gc_push_root(ctx, (void**)&_obj_408); mph_int _ret_409 = _obj_408->kind; mph_gc_pop_roots(ctx, 1); _ret_409; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_410 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_410); mph_types_TypeResult* _ret_411 = mph_types_make_type_result(ctx, NULL, _arg_410); mph_gc_pop_roots(ctx, 1); _ret_411; });
}
	}
}
	}
	return ({ MorphString* _arg_412 = mph_string_new(ctx, "<< memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_412); mph_types_TypeResult* _ret_413 = mph_types_make_type_error(ctx, NULL, _arg_412); mph_gc_pop_roots(ctx, 1); _ret_413; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">>"))) {
{
	if ((({ mph_types_Type* _obj_414 = left; mph_gc_push_root(ctx, (void**)&_obj_414); mph_int _ret_415 = _obj_414->kind; mph_gc_pop_roots(ctx, 1); _ret_415; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_416 = right; mph_gc_push_root(ctx, (void**)&_obj_416); mph_int _ret_417 = _obj_416->kind; mph_gc_pop_roots(ctx, 1); _ret_417; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_418 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_418); mph_types_TypeResult* _ret_419 = mph_types_make_type_result(ctx, NULL, _arg_418); mph_gc_pop_roots(ctx, 1); _ret_419; });
}
	}
}
	}
	return ({ MorphString* _arg_420 = mph_string_new(ctx, ">> memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_420); mph_types_TypeResult* _ret_421 = mph_types_make_type_error(ctx, NULL, _arg_420); mph_gc_pop_roots(ctx, 1); _ret_421; });
}
	}
	return ({ MorphString* _arg_422 = mph_string_new(ctx, "operator tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_422); mph_types_TypeResult* _ret_423 = mph_types_make_type_error(ctx, NULL, _arg_422); mph_gc_pop_roots(ctx, 1); _ret_423; });
	mph_gc_pop_roots(ctx, 3);
}

mph_types_TypeResult* mph_types_type_prefix_op(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	if ((({ mph_types_Type* _obj_424 = t; mph_gc_push_root(ctx, (void**)&_obj_424); mph_int _ret_425 = _obj_424->kind; mph_gc_pop_roots(ctx, 1); _ret_425; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_426 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_426); mph_types_TypeResult* _ret_427 = mph_types_make_type_result(ctx, NULL, _arg_426); mph_gc_pop_roots(ctx, 1); _ret_427; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!"))) {
{
	if ((({ mph_types_Type* _obj_428 = t; mph_gc_push_root(ctx, (void**)&_obj_428); mph_int _ret_429 = _obj_428->kind; mph_gc_pop_roots(ctx, 1); _ret_429; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_430 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_430); mph_types_TypeResult* _ret_431 = mph_types_make_type_result(ctx, NULL, _arg_430); mph_gc_pop_roots(ctx, 1); _ret_431; });
}
	}
	return ({ MorphString* _arg_432 = mph_string_new(ctx, "! memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_432); mph_types_TypeResult* _ret_433 = mph_types_make_type_error(ctx, NULL, _arg_432); mph_gc_pop_roots(ctx, 1); _ret_433; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_types_Type* _obj_434 = t; mph_gc_push_root(ctx, (void**)&_obj_434); mph_int _ret_435 = _obj_434->kind; mph_gc_pop_roots(ctx, 1); _ret_435; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_436 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_436); mph_types_TypeResult* _ret_437 = mph_types_make_type_result(ctx, NULL, _arg_436); mph_gc_pop_roots(ctx, 1); _ret_437; });
}
	}
	if ((({ mph_types_Type* _obj_438 = t; mph_gc_push_root(ctx, (void**)&_obj_438); mph_int _ret_439 = _obj_438->kind; mph_gc_pop_roots(ctx, 1); _ret_439; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_440 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_440); mph_types_TypeResult* _ret_441 = mph_types_make_type_result(ctx, NULL, _arg_440); mph_gc_pop_roots(ctx, 1); _ret_441; });
}
	}
	return ({ MorphString* _arg_442 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_442); mph_types_TypeResult* _ret_443 = mph_types_make_type_error(ctx, NULL, _arg_442); mph_gc_pop_roots(ctx, 1); _ret_443; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "~"))) {
{
	if ((({ mph_types_Type* _obj_444 = t; mph_gc_push_root(ctx, (void**)&_obj_444); mph_int _ret_445 = _obj_444->kind; mph_gc_pop_roots(ctx, 1); _ret_445; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_446 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_446); mph_types_TypeResult* _ret_447 = mph_types_make_type_result(ctx, NULL, _arg_446); mph_gc_pop_roots(ctx, 1); _ret_447; });
}
	}
	return ({ MorphString* _arg_448 = mph_string_new(ctx, "~ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_448); mph_types_TypeResult* _ret_449 = mph_types_make_type_error(ctx, NULL, _arg_448); mph_gc_pop_roots(ctx, 1); _ret_449; });
}
	}
	return ({ MorphString* _arg_450 = mph_string_new(ctx, "prefix tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_450); mph_types_TypeResult* _ret_451 = mph_types_make_type_error(ctx, NULL, _arg_450); mph_gc_pop_roots(ctx, 1); _ret_451; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_types_kind_to_string(MorphContext* ctx, void* _env_void, mph_int k) {
	if ((k == mph_types_KIND_INT)) {
{
	return mph_string_new(ctx, "int");
}
	}
	if ((k == mph_types_KIND_FLOAT)) {
{
	return mph_string_new(ctx, "float");
}
	}
	if ((k == mph_types_KIND_STRING)) {
{
	return mph_string_new(ctx, "string");
}
	}
	if ((k == mph_types_KIND_BOOL)) {
{
	return mph_string_new(ctx, "bool");
}
	}
	if ((k == mph_types_KIND_VOID)) {
{
	return mph_string_new(ctx, "void");
}
	}
	if ((k == mph_types_KIND_FUNCTION)) {
{
	return mph_string_new(ctx, "function");
}
	}
	if ((k == mph_types_KIND_STRUCT)) {
{
	return mph_string_new(ctx, "struct");
}
	}
	if ((k == mph_types_KIND_INTERFACE)) {
{
	return mph_string_new(ctx, "interface");
}
	}
	if ((k == mph_types_KIND_ARRAY)) {
{
	return mph_string_new(ctx, "array");
}
	}
	if ((k == mph_types_KIND_MAP)) {
{
	return mph_string_new(ctx, "map");
}
	}
	if ((k == mph_types_KIND_POINTER)) {
{
	return mph_string_new(ctx, "pointer");
}
	}
	if ((k == mph_types_KIND_MULTI)) {
{
	return mph_string_new(ctx, "multi");
}
	}
	if ((k == mph_types_KIND_UNKNOWN)) {
{
	return mph_string_new(ctx, "unknown");
}
	}
	if ((k == mph_types_KIND_ERROR)) {
{
	return mph_string_new(ctx, "error");
}
	}
	if ((k == mph_types_KIND_NULL)) {
{
	return mph_string_new(ctx, "null");
}
	}
	if ((k == mph_types_KIND_USER_ERROR)) {
{
	return mph_string_new(ctx, "user_error");
}
	}
	if ((k == mph_types_KIND_MODULE)) {
{
	return mph_string_new(ctx, "module");
}
	}
	if ((k == mph_types_KIND_CHANNEL)) {
{
	return mph_string_new(ctx, "channel");
}
	}
	return mph_string_new(ctx, "unknown");
}

mph_types_Type* mph_types_IntType(MorphContext* ctx, void* _env_void) {
	return mph_types_int_type(ctx, NULL);
}

mph_types_Type* mph_types_FloatType(MorphContext* ctx, void* _env_void) {
	return mph_types_float_type(ctx, NULL);
}

mph_types_Type* mph_types_StringType(MorphContext* ctx, void* _env_void) {
	return mph_types_string_type(ctx, NULL);
}

mph_types_Type* mph_types_BoolType(MorphContext* ctx, void* _env_void) {
	return mph_types_bool_type(ctx, NULL);
}

mph_types_Type* mph_types_VoidType(MorphContext* ctx, void* _env_void) {
	return mph_types_void_type(ctx, NULL);
}

mph_types_Type* mph_types_NullType(MorphContext* ctx, void* _env_void) {
	return mph_types_null_type(ctx, NULL);
}

mph_types_Type* mph_types_UnknownType(MorphContext* ctx, void* _env_void) {
	return mph_types_unknown_type(ctx, NULL);
}

mph_types_Type* mph_types_ErrorType(MorphContext* ctx, void* _env_void) {
	return mph_types_error_type(ctx, NULL);
}

mph_types_Type* mph_types_UserErrorType(MorphContext* ctx, void* _env_void) {
	return mph_types_user_error_type(ctx, NULL);
}

mph_types_Type* mph_types_ChannelType(MorphContext* ctx, void* _env_void) {
	return mph_types_channel_type(ctx, NULL);
}

mph_types_Type* mph_types_ArrayType(MorphContext* ctx, void* _env_void) {
	return mph_types_array_type(ctx, NULL);
}

mph_types_Type* mph_types_MapType(MorphContext* ctx, void* _env_void) {
	return mph_types_map_type(ctx, NULL);
}

mph_types_Type* mph_types_StructType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_452 = n; mph_gc_push_root(ctx, (void**)&_arg_452); mph_types_Type* _ret_453 = mph_types_struct_type(ctx, NULL, _arg_452); mph_gc_pop_roots(ctx, 1); _ret_453; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_InterfaceType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_454 = n; mph_gc_push_root(ctx, (void**)&_arg_454); mph_types_Type* _ret_455 = mph_types_interface_type(ctx, NULL, _arg_454); mph_gc_pop_roots(ctx, 1); _ret_455; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_FunctionType(MorphContext* ctx, void* _env_void) {
	return mph_types_function_type(ctx, NULL);
}

mph_types_Type* mph_types_PointerType(MorphContext* ctx, void* _env_void) {
	return mph_types_pointer_type(ctx, NULL);
}

mph_types_Type* mph_types_MultiType(MorphContext* ctx, void* _env_void) {
	return mph_types_multi_type(ctx, NULL);
}

mph_types_Type* mph_types_ModuleType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_456 = n; mph_gc_push_root(ctx, (void**)&_arg_456); mph_types_Type* _ret_457 = mph_types_module_type(ctx, NULL, _arg_456); mph_gc_pop_roots(ctx, 1); _ret_457; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_types_TypeEquals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return ({ mph_types_Type* _arg_458 = t1; mph_gc_push_root(ctx, (void**)&_arg_458); mph_types_Type* _arg_459 = t2; mph_gc_push_root(ctx, (void**)&_arg_459); mph_bool _ret_460 = mph_types_type_equals(ctx, NULL, _arg_458, _arg_459); mph_gc_pop_roots(ctx, 2); _ret_460; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_TypeAssignableTo(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	return ({ mph_types_Type* _arg_461 = source; mph_gc_push_root(ctx, (void**)&_arg_461); mph_types_Type* _arg_462 = target; mph_gc_push_root(ctx, (void**)&_arg_462); mph_bool _ret_463 = mph_types_type_assignable_to(ctx, NULL, _arg_461, _arg_462); mph_gc_pop_roots(ctx, 2); _ret_463; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_TypeIsComparable(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_types_Type* _arg_464 = t; mph_gc_push_root(ctx, (void**)&_arg_464); mph_bool _ret_465 = mph_types_type_is_comparable(ctx, NULL, _arg_464); mph_gc_pop_roots(ctx, 1); _ret_465; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_TypeResult* mph_types_TypeBinaryOp(MorphContext* ctx, void* _env_void, mph_types_Type* left, MorphString* op, mph_types_Type* right) {
	mph_gc_push_root(ctx, (void**)&left);
	mph_gc_push_root(ctx, (void**)&op);
	mph_gc_push_root(ctx, (void**)&right);
	return ({ mph_types_Type* _arg_466 = left; mph_gc_push_root(ctx, (void**)&_arg_466); MorphString* _arg_467 = op; mph_gc_push_root(ctx, (void**)&_arg_467); mph_types_Type* _arg_468 = right; mph_gc_push_root(ctx, (void**)&_arg_468); mph_types_TypeResult* _ret_469 = mph_types_type_binary_op(ctx, NULL, _arg_466, _arg_467, _arg_468); mph_gc_pop_roots(ctx, 3); _ret_469; });
	mph_gc_pop_roots(ctx, 3);
}

mph_types_TypeResult* mph_types_TypePrefixOp(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	return ({ mph_types_Type* _arg_470 = t; mph_gc_push_root(ctx, (void**)&_arg_470); MorphString* _arg_471 = op; mph_gc_push_root(ctx, (void**)&_arg_471); mph_types_TypeResult* _ret_472 = mph_types_type_prefix_op(ctx, NULL, _arg_470, _arg_471); mph_gc_pop_roots(ctx, 2); _ret_472; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_types_KindToString(MorphContext* ctx, void* _env_void, mph_int k) {
	return mph_types_kind_to_string(ctx, NULL, k);
}

void mph_types_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â   N1 Type System - Full Test Suite   â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n\n"));
	mph_int passed = 0;
	mph_int failed = 0;
	mph_native_print(ctx, mph_string_new(ctx, "[Test 1] Type Creation\n"));
	mph_types_Type* t_int = mph_types_int_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_int);
	mph_types_Type* t_float = mph_types_float_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_float);
	mph_types_Type* t_string = mph_types_string_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_string);
	mph_types_Type* t_bool = mph_types_bool_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_bool);
	if ((({ mph_types_Type* _obj_473 = t_int; mph_gc_push_root(ctx, (void**)&_obj_473); mph_int _ret_474 = _obj_473->kind; mph_gc_pop_roots(ctx, 1); _ret_474; }) == mph_types_KIND_INT)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int_type().kind == KIND_INT\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int_type().kind FAILED\n"));
	failed = (failed + 1);
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 2] Type Equality\n"));
	if (({ mph_types_Type* _arg_475 = t_int; mph_gc_push_root(ctx, (void**)&_arg_475); mph_types_Type* _arg_476 = t_int; mph_gc_push_root(ctx, (void**)&_arg_476); mph_bool _ret_477 = mph_types_type_equals(ctx, NULL, _arg_475, _arg_476); mph_gc_pop_roots(ctx, 2); _ret_477; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int FAILED\n"));
	failed = (failed + 1);
}
	}
	if (({ mph_types_Type* _arg_478 = t_int; mph_gc_push_root(ctx, (void**)&_arg_478); mph_types_Type* _arg_479 = t_float; mph_gc_push_root(ctx, (void**)&_arg_479); mph_bool _ret_480 = mph_types_type_equals(ctx, NULL, _arg_478, _arg_479); mph_gc_pop_roots(ctx, 2); _ret_480; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int != float FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int != float\n"));
	passed = (passed + 1);
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 3] Null Assignability\n"));
	mph_types_Type* t_null = mph_types_null_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_null);
	mph_types_Type* t_array = mph_types_array_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_array);
	mph_types_Type* t_map = mph_types_map_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_map);
	if (({ mph_types_Type* _arg_481 = t_null; mph_gc_push_root(ctx, (void**)&_arg_481); mph_types_Type* _arg_482 = t_array; mph_gc_push_root(ctx, (void**)&_arg_482); mph_bool _ret_483 = mph_types_type_assignable_to(ctx, NULL, _arg_481, _arg_482); mph_gc_pop_roots(ctx, 2); _ret_483; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â null -> array\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â null -> array FAILED\n"));
	failed = (failed + 1);
}
	}
	if (({ mph_types_Type* _arg_484 = t_null; mph_gc_push_root(ctx, (void**)&_arg_484); mph_types_Type* _arg_485 = t_map; mph_gc_push_root(ctx, (void**)&_arg_485); mph_bool _ret_486 = mph_types_type_assignable_to(ctx, NULL, _arg_484, _arg_485); mph_gc_pop_roots(ctx, 2); _ret_486; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â null -> map\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â null -> map FAILED\n"));
	failed = (failed + 1);
}
	}
	if (({ mph_types_Type* _arg_487 = t_null; mph_gc_push_root(ctx, (void**)&_arg_487); mph_types_Type* _arg_488 = t_int; mph_gc_push_root(ctx, (void**)&_arg_488); mph_bool _ret_489 = mph_types_type_assignable_to(ctx, NULL, _arg_487, _arg_488); mph_gc_pop_roots(ctx, 2); _ret_489; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â null !-> int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â null !-> int\n"));
	passed = (passed + 1);
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 4] Type Comparability\n"));
	if (({ mph_types_Type* _arg_490 = t_int; mph_gc_push_root(ctx, (void**)&_arg_490); mph_bool _ret_491 = mph_types_type_is_comparable(ctx, NULL, _arg_490); mph_gc_pop_roots(ctx, 1); _ret_491; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int is comparable\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int is comparable FAILED\n"));
	failed = (failed + 1);
}
	}
	mph_types_Type* t_void = mph_types_void_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_void);
	if (({ mph_types_Type* _arg_492 = t_void; mph_gc_push_root(ctx, (void**)&_arg_492); mph_bool _ret_493 = mph_types_type_is_comparable(ctx, NULL, _arg_492); mph_gc_pop_roots(ctx, 1); _ret_493; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â void not comparable FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â void not comparable\n"));
	passed = (passed + 1);
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 5] Binary Ops - Arithmetic\n"));
	mph_types_TypeResult* r1 = ({ mph_types_Type* _arg_494 = t_int; mph_gc_push_root(ctx, (void**)&_arg_494); MorphString* _arg_495 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_495); mph_types_Type* _arg_496 = t_int; mph_gc_push_root(ctx, (void**)&_arg_496); mph_types_TypeResult* _ret_497 = mph_types_type_binary_op(ctx, NULL, _arg_494, _arg_495, _arg_496); mph_gc_pop_roots(ctx, 3); _ret_497; });
	mph_gc_push_root(ctx, (void**)&r1);
	if (({ mph_types_TypeResult* _obj_498 = r1; mph_gc_push_root(ctx, (void**)&_obj_498); mph_bool _ret_499 = _obj_498->has_error; mph_gc_pop_roots(ctx, 1); _ret_499; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_502 = ({ mph_types_TypeResult* _obj_500 = r1; mph_gc_push_root(ctx, (void**)&_obj_500); mph_types_Type* _ret_501 = _obj_500->result; mph_gc_pop_roots(ctx, 1); _ret_501; }); mph_gc_push_root(ctx, (void**)&_obj_502); mph_int _ret_503 = _obj_502->kind; mph_gc_pop_roots(ctx, 1); _ret_503; }) == mph_types_KIND_INT)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + int = int\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + int wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r2 = ({ mph_types_Type* _arg_504 = t_string; mph_gc_push_root(ctx, (void**)&_arg_504); MorphString* _arg_505 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_505); mph_types_Type* _arg_506 = t_string; mph_gc_push_root(ctx, (void**)&_arg_506); mph_types_TypeResult* _ret_507 = mph_types_type_binary_op(ctx, NULL, _arg_504, _arg_505, _arg_506); mph_gc_pop_roots(ctx, 3); _ret_507; });
	mph_gc_push_root(ctx, (void**)&r2);
	if (({ mph_types_TypeResult* _obj_508 = r2; mph_gc_push_root(ctx, (void**)&_obj_508); mph_bool _ret_509 = _obj_508->has_error; mph_gc_pop_roots(ctx, 1); _ret_509; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string + string FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_512 = ({ mph_types_TypeResult* _obj_510 = r2; mph_gc_push_root(ctx, (void**)&_obj_510); mph_types_Type* _ret_511 = _obj_510->result; mph_gc_pop_roots(ctx, 1); _ret_511; }); mph_gc_push_root(ctx, (void**)&_obj_512); mph_int _ret_513 = _obj_512->kind; mph_gc_pop_roots(ctx, 1); _ret_513; }) == mph_types_KIND_STRING)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string + string = string\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string + string wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r3 = ({ mph_types_Type* _arg_514 = t_float; mph_gc_push_root(ctx, (void**)&_arg_514); MorphString* _arg_515 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_arg_515); mph_types_Type* _arg_516 = t_float; mph_gc_push_root(ctx, (void**)&_arg_516); mph_types_TypeResult* _ret_517 = mph_types_type_binary_op(ctx, NULL, _arg_514, _arg_515, _arg_516); mph_gc_pop_roots(ctx, 3); _ret_517; });
	mph_gc_push_root(ctx, (void**)&r3);
	if (({ mph_types_TypeResult* _obj_518 = r3; mph_gc_push_root(ctx, (void**)&_obj_518); mph_bool _ret_519 = _obj_518->has_error; mph_gc_pop_roots(ctx, 1); _ret_519; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â float * float FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_522 = ({ mph_types_TypeResult* _obj_520 = r3; mph_gc_push_root(ctx, (void**)&_obj_520); mph_types_Type* _ret_521 = _obj_520->result; mph_gc_pop_roots(ctx, 1); _ret_521; }); mph_gc_push_root(ctx, (void**)&_obj_522); mph_int _ret_523 = _obj_522->kind; mph_gc_pop_roots(ctx, 1); _ret_523; }) == mph_types_KIND_FLOAT)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â float * float = float\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â float * float wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 6] Binary Ops - Comparison\n"));
	mph_types_TypeResult* r4 = ({ mph_types_Type* _arg_524 = t_int; mph_gc_push_root(ctx, (void**)&_arg_524); MorphString* _arg_525 = mph_string_new(ctx, "<"); mph_gc_push_root(ctx, (void**)&_arg_525); mph_types_Type* _arg_526 = t_int; mph_gc_push_root(ctx, (void**)&_arg_526); mph_types_TypeResult* _ret_527 = mph_types_type_binary_op(ctx, NULL, _arg_524, _arg_525, _arg_526); mph_gc_pop_roots(ctx, 3); _ret_527; });
	mph_gc_push_root(ctx, (void**)&r4);
	if (({ mph_types_TypeResult* _obj_528 = r4; mph_gc_push_root(ctx, (void**)&_obj_528); mph_bool _ret_529 = _obj_528->has_error; mph_gc_pop_roots(ctx, 1); _ret_529; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int < int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_532 = ({ mph_types_TypeResult* _obj_530 = r4; mph_gc_push_root(ctx, (void**)&_obj_530); mph_types_Type* _ret_531 = _obj_530->result; mph_gc_pop_roots(ctx, 1); _ret_531; }); mph_gc_push_root(ctx, (void**)&_obj_532); mph_int _ret_533 = _obj_532->kind; mph_gc_pop_roots(ctx, 1); _ret_533; }) == mph_types_KIND_BOOL)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int < int = bool\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int < int wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r5 = ({ mph_types_Type* _arg_534 = t_int; mph_gc_push_root(ctx, (void**)&_arg_534); MorphString* _arg_535 = mph_string_new(ctx, "=="); mph_gc_push_root(ctx, (void**)&_arg_535); mph_types_Type* _arg_536 = t_int; mph_gc_push_root(ctx, (void**)&_arg_536); mph_types_TypeResult* _ret_537 = mph_types_type_binary_op(ctx, NULL, _arg_534, _arg_535, _arg_536); mph_gc_pop_roots(ctx, 3); _ret_537; });
	mph_gc_push_root(ctx, (void**)&r5);
	if (({ mph_types_TypeResult* _obj_538 = r5; mph_gc_push_root(ctx, (void**)&_obj_538); mph_bool _ret_539 = _obj_538->has_error; mph_gc_pop_roots(ctx, 1); _ret_539; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_542 = ({ mph_types_TypeResult* _obj_540 = r5; mph_gc_push_root(ctx, (void**)&_obj_540); mph_types_Type* _ret_541 = _obj_540->result; mph_gc_pop_roots(ctx, 1); _ret_541; }); mph_gc_push_root(ctx, (void**)&_obj_542); mph_int _ret_543 = _obj_542->kind; mph_gc_pop_roots(ctx, 1); _ret_543; }) == mph_types_KIND_BOOL)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int = bool\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 7] Binary Ops - Logical\n"));
	mph_types_TypeResult* r6 = ({ mph_types_Type* _arg_544 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_544); MorphString* _arg_545 = mph_string_new(ctx, "dan"); mph_gc_push_root(ctx, (void**)&_arg_545); mph_types_Type* _arg_546 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_546); mph_types_TypeResult* _ret_547 = mph_types_type_binary_op(ctx, NULL, _arg_544, _arg_545, _arg_546); mph_gc_pop_roots(ctx, 3); _ret_547; });
	mph_gc_push_root(ctx, (void**)&r6);
	if (({ mph_types_TypeResult* _obj_548 = r6; mph_gc_push_root(ctx, (void**)&_obj_548); mph_bool _ret_549 = _obj_548->has_error; mph_gc_pop_roots(ctx, 1); _ret_549; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool dan bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_552 = ({ mph_types_TypeResult* _obj_550 = r6; mph_gc_push_root(ctx, (void**)&_obj_550); mph_types_Type* _ret_551 = _obj_550->result; mph_gc_pop_roots(ctx, 1); _ret_551; }); mph_gc_push_root(ctx, (void**)&_obj_552); mph_int _ret_553 = _obj_552->kind; mph_gc_pop_roots(ctx, 1); _ret_553; }) == mph_types_KIND_BOOL)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool dan bool = bool\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool dan bool wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r7 = ({ mph_types_Type* _arg_554 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_554); MorphString* _arg_555 = mph_string_new(ctx, "||"); mph_gc_push_root(ctx, (void**)&_arg_555); mph_types_Type* _arg_556 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_556); mph_types_TypeResult* _ret_557 = mph_types_type_binary_op(ctx, NULL, _arg_554, _arg_555, _arg_556); mph_gc_pop_roots(ctx, 3); _ret_557; });
	mph_gc_push_root(ctx, (void**)&r7);
	if (({ mph_types_TypeResult* _obj_558 = r7; mph_gc_push_root(ctx, (void**)&_obj_558); mph_bool _ret_559 = _obj_558->has_error; mph_gc_pop_roots(ctx, 1); _ret_559; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool || bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_562 = ({ mph_types_TypeResult* _obj_560 = r7; mph_gc_push_root(ctx, (void**)&_obj_560); mph_types_Type* _ret_561 = _obj_560->result; mph_gc_pop_roots(ctx, 1); _ret_561; }); mph_gc_push_root(ctx, (void**)&_obj_562); mph_int _ret_563 = _obj_562->kind; mph_gc_pop_roots(ctx, 1); _ret_563; }) == mph_types_KIND_BOOL)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool || bool = bool\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool || bool wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 8] Binary Ops - Bitwise\n"));
	mph_types_TypeResult* r8 = ({ mph_types_Type* _arg_564 = t_int; mph_gc_push_root(ctx, (void**)&_arg_564); MorphString* _arg_565 = mph_string_new(ctx, "&"); mph_gc_push_root(ctx, (void**)&_arg_565); mph_types_Type* _arg_566 = t_int; mph_gc_push_root(ctx, (void**)&_arg_566); mph_types_TypeResult* _ret_567 = mph_types_type_binary_op(ctx, NULL, _arg_564, _arg_565, _arg_566); mph_gc_pop_roots(ctx, 3); _ret_567; });
	mph_gc_push_root(ctx, (void**)&r8);
	if (({ mph_types_TypeResult* _obj_568 = r8; mph_gc_push_root(ctx, (void**)&_obj_568); mph_bool _ret_569 = _obj_568->has_error; mph_gc_pop_roots(ctx, 1); _ret_569; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int & int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_572 = ({ mph_types_TypeResult* _obj_570 = r8; mph_gc_push_root(ctx, (void**)&_obj_570); mph_types_Type* _ret_571 = _obj_570->result; mph_gc_pop_roots(ctx, 1); _ret_571; }); mph_gc_push_root(ctx, (void**)&_obj_572); mph_int _ret_573 = _obj_572->kind; mph_gc_pop_roots(ctx, 1); _ret_573; }) == mph_types_KIND_INT)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int & int = int\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int & int wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r9 = ({ mph_types_Type* _arg_574 = t_int; mph_gc_push_root(ctx, (void**)&_arg_574); MorphString* _arg_575 = mph_string_new(ctx, "<<"); mph_gc_push_root(ctx, (void**)&_arg_575); mph_types_Type* _arg_576 = t_int; mph_gc_push_root(ctx, (void**)&_arg_576); mph_types_TypeResult* _ret_577 = mph_types_type_binary_op(ctx, NULL, _arg_574, _arg_575, _arg_576); mph_gc_pop_roots(ctx, 3); _ret_577; });
	mph_gc_push_root(ctx, (void**)&r9);
	if (({ mph_types_TypeResult* _obj_578 = r9; mph_gc_push_root(ctx, (void**)&_obj_578); mph_bool _ret_579 = _obj_578->has_error; mph_gc_pop_roots(ctx, 1); _ret_579; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int << int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_582 = ({ mph_types_TypeResult* _obj_580 = r9; mph_gc_push_root(ctx, (void**)&_obj_580); mph_types_Type* _ret_581 = _obj_580->result; mph_gc_pop_roots(ctx, 1); _ret_581; }); mph_gc_push_root(ctx, (void**)&_obj_582); mph_int _ret_583 = _obj_582->kind; mph_gc_pop_roots(ctx, 1); _ret_583; }) == mph_types_KIND_INT)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int << int = int\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int << int wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 9] Error Detection\n"));
	mph_types_TypeResult* r10 = ({ mph_types_Type* _arg_584 = t_int; mph_gc_push_root(ctx, (void**)&_arg_584); MorphString* _arg_585 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_585); mph_types_Type* _arg_586 = t_string; mph_gc_push_root(ctx, (void**)&_arg_586); mph_types_TypeResult* _ret_587 = mph_types_type_binary_op(ctx, NULL, _arg_584, _arg_585, _arg_586); mph_gc_pop_roots(ctx, 3); _ret_587; });
	mph_gc_push_root(ctx, (void**)&r10);
	if (({ mph_types_TypeResult* _obj_588 = r10; mph_gc_push_root(ctx, (void**)&_obj_588); mph_bool _ret_589 = _obj_588->has_error; mph_gc_pop_roots(ctx, 1); _ret_589; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + string = ERROR\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + string should error\n"));
	failed = (failed + 1);
}
	}
	mph_types_TypeResult* r11 = ({ mph_types_Type* _arg_590 = t_string; mph_gc_push_root(ctx, (void**)&_arg_590); MorphString* _arg_591 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_591); mph_types_Type* _arg_592 = t_string; mph_gc_push_root(ctx, (void**)&_arg_592); mph_types_TypeResult* _ret_593 = mph_types_type_binary_op(ctx, NULL, _arg_590, _arg_591, _arg_592); mph_gc_pop_roots(ctx, 3); _ret_593; });
	mph_gc_push_root(ctx, (void**)&r11);
	if (({ mph_types_TypeResult* _obj_594 = r11; mph_gc_push_root(ctx, (void**)&_obj_594); mph_bool _ret_595 = _obj_594->has_error; mph_gc_pop_roots(ctx, 1); _ret_595; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string - string = ERROR\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string - string should error\n"));
	failed = (failed + 1);
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 10] Prefix Operations\n"));
	mph_types_TypeResult* r12 = ({ mph_types_Type* _arg_596 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_596); MorphString* _arg_597 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_597); mph_types_TypeResult* _ret_598 = mph_types_type_prefix_op(ctx, NULL, _arg_596, _arg_597); mph_gc_pop_roots(ctx, 2); _ret_598; });
	mph_gc_push_root(ctx, (void**)&r12);
	if (({ mph_types_TypeResult* _obj_599 = r12; mph_gc_push_root(ctx, (void**)&_obj_599); mph_bool _ret_600 = _obj_599->has_error; mph_gc_pop_roots(ctx, 1); _ret_600; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_603 = ({ mph_types_TypeResult* _obj_601 = r12; mph_gc_push_root(ctx, (void**)&_obj_601); mph_types_Type* _ret_602 = _obj_601->result; mph_gc_pop_roots(ctx, 1); _ret_602; }); mph_gc_push_root(ctx, (void**)&_obj_603); mph_int _ret_604 = _obj_603->kind; mph_gc_pop_roots(ctx, 1); _ret_604; }) == mph_types_KIND_BOOL)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !bool = bool\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !bool wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r13 = ({ mph_types_Type* _arg_605 = t_int; mph_gc_push_root(ctx, (void**)&_arg_605); MorphString* _arg_606 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_606); mph_types_TypeResult* _ret_607 = mph_types_type_prefix_op(ctx, NULL, _arg_605, _arg_606); mph_gc_pop_roots(ctx, 2); _ret_607; });
	mph_gc_push_root(ctx, (void**)&r13);
	if (({ mph_types_TypeResult* _obj_608 = r13; mph_gc_push_root(ctx, (void**)&_obj_608); mph_bool _ret_609 = _obj_608->has_error; mph_gc_pop_roots(ctx, 1); _ret_609; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â -int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_612 = ({ mph_types_TypeResult* _obj_610 = r13; mph_gc_push_root(ctx, (void**)&_obj_610); mph_types_Type* _ret_611 = _obj_610->result; mph_gc_pop_roots(ctx, 1); _ret_611; }); mph_gc_push_root(ctx, (void**)&_obj_612); mph_int _ret_613 = _obj_612->kind; mph_gc_pop_roots(ctx, 1); _ret_613; }) == mph_types_KIND_INT)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â -int = int\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â -int wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r14 = ({ mph_types_Type* _arg_614 = t_int; mph_gc_push_root(ctx, (void**)&_arg_614); MorphString* _arg_615 = mph_string_new(ctx, "~"); mph_gc_push_root(ctx, (void**)&_arg_615); mph_types_TypeResult* _ret_616 = mph_types_type_prefix_op(ctx, NULL, _arg_614, _arg_615); mph_gc_pop_roots(ctx, 2); _ret_616; });
	mph_gc_push_root(ctx, (void**)&r14);
	if (({ mph_types_TypeResult* _obj_617 = r14; mph_gc_push_root(ctx, (void**)&_obj_617); mph_bool _ret_618 = _obj_617->has_error; mph_gc_pop_roots(ctx, 1); _ret_618; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â ~int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_621 = ({ mph_types_TypeResult* _obj_619 = r14; mph_gc_push_root(ctx, (void**)&_obj_619); mph_types_Type* _ret_620 = _obj_619->result; mph_gc_pop_roots(ctx, 1); _ret_620; }); mph_gc_push_root(ctx, (void**)&_obj_621); mph_int _ret_622 = _obj_621->kind; mph_gc_pop_roots(ctx, 1); _ret_622; }) == mph_types_KIND_INT)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â ~int = int\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â ~int wrong type\n"));
	failed = (failed + 1);
}
	}
}
	}
	mph_types_TypeResult* r15 = ({ mph_types_Type* _arg_623 = t_string; mph_gc_push_root(ctx, (void**)&_arg_623); MorphString* _arg_624 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_624); mph_types_TypeResult* _ret_625 = mph_types_type_prefix_op(ctx, NULL, _arg_623, _arg_624); mph_gc_pop_roots(ctx, 2); _ret_625; });
	mph_gc_push_root(ctx, (void**)&r15);
	if (({ mph_types_TypeResult* _obj_626 = r15; mph_gc_push_root(ctx, (void**)&_obj_626); mph_bool _ret_627 = _obj_626->has_error; mph_gc_pop_roots(ctx, 1); _ret_627; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !string = ERROR\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !string should error\n"));
	failed = (failed + 1);
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 11] Kind to String\n"));
	MorphString* s1 = mph_types_kind_to_string(ctx, NULL, mph_types_KIND_INT);
	mph_gc_push_root(ctx, (void**)&s1);
	if (mph_string_eq(ctx, s1, mph_string_new(ctx, "int"))) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â KIND_INT -> \"int\"\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â KIND_INT -> string FAILED\n"));
	failed = (failed + 1);
}
	}
	MorphString* s2 = mph_types_kind_to_string(ctx, NULL, mph_types_KIND_CHANNEL);
	mph_gc_push_root(ctx, (void**)&s2);
	if (mph_string_eq(ctx, s2, mph_string_new(ctx, "channel"))) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â KIND_CHANNEL -> \"channel\"\n"));
	passed = (passed + 1);
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â KIND_CHANNEL -> string FAILED\n"));
	failed = (failed + 1);
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\nââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â            TEST SUMMARY              â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  Passed: "));
	mph_native_print_int(ctx, passed);
	mph_native_print(ctx, mph_string_new(ctx, "\n  Failed: "));
	mph_native_print_int(ctx, failed);
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	if ((failed == 0)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "\n  â ALL TESTS PASSED! â\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "\n  â SOME TESTS FAILED\n"));
}
	}
	mph_gc_pop_roots(ctx, 25);
}

MorphString* mph_stdlib_codegen_int_to_string(MorphContext* ctx, void* _env_void, mph_int n) {
	if ((n == 0)) {
{
	return mph_string_new(ctx, "0");
}
	}
	mph_bool is_negative = 0;
	mph_int num = n;
	if ((n < 0)) {
{
	is_negative = 1;
	num = (0 - n);
}
	}
	MorphString* result = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&result);
	while ((num > 0)) {
{
	mph_int digit = (num - ((num / 10) * 10));
	num = (num / 10);
	if ((digit == 0)) {
{
	result = ({ MorphString* _lhs_628 = mph_string_new(ctx, "0"); MorphString* _rhs_629 = result; mph_gc_push_root(ctx, (void**)&_lhs_628); mph_gc_push_root(ctx, (void**)&_rhs_629); MorphString* _ret_630 = mph_string_concat(ctx, _lhs_628, _rhs_629); mph_gc_pop_roots(ctx, 2); _ret_630; });
}
	}
	if ((digit == 1)) {
{
	result = ({ MorphString* _lhs_631 = mph_string_new(ctx, "1"); MorphString* _rhs_632 = result; mph_gc_push_root(ctx, (void**)&_lhs_631); mph_gc_push_root(ctx, (void**)&_rhs_632); MorphString* _ret_633 = mph_string_concat(ctx, _lhs_631, _rhs_632); mph_gc_pop_roots(ctx, 2); _ret_633; });
}
	}
	if ((digit == 2)) {
{
	result = ({ MorphString* _lhs_634 = mph_string_new(ctx, "2"); MorphString* _rhs_635 = result; mph_gc_push_root(ctx, (void**)&_lhs_634); mph_gc_push_root(ctx, (void**)&_rhs_635); MorphString* _ret_636 = mph_string_concat(ctx, _lhs_634, _rhs_635); mph_gc_pop_roots(ctx, 2); _ret_636; });
}
	}
	if ((digit == 3)) {
{
	result = ({ MorphString* _lhs_637 = mph_string_new(ctx, "3"); MorphString* _rhs_638 = result; mph_gc_push_root(ctx, (void**)&_lhs_637); mph_gc_push_root(ctx, (void**)&_rhs_638); MorphString* _ret_639 = mph_string_concat(ctx, _lhs_637, _rhs_638); mph_gc_pop_roots(ctx, 2); _ret_639; });
}
	}
	if ((digit == 4)) {
{
	result = ({ MorphString* _lhs_640 = mph_string_new(ctx, "4"); MorphString* _rhs_641 = result; mph_gc_push_root(ctx, (void**)&_lhs_640); mph_gc_push_root(ctx, (void**)&_rhs_641); MorphString* _ret_642 = mph_string_concat(ctx, _lhs_640, _rhs_641); mph_gc_pop_roots(ctx, 2); _ret_642; });
}
	}
	if ((digit == 5)) {
{
	result = ({ MorphString* _lhs_643 = mph_string_new(ctx, "5"); MorphString* _rhs_644 = result; mph_gc_push_root(ctx, (void**)&_lhs_643); mph_gc_push_root(ctx, (void**)&_rhs_644); MorphString* _ret_645 = mph_string_concat(ctx, _lhs_643, _rhs_644); mph_gc_pop_roots(ctx, 2); _ret_645; });
}
	}
	if ((digit == 6)) {
{
	result = ({ MorphString* _lhs_646 = mph_string_new(ctx, "6"); MorphString* _rhs_647 = result; mph_gc_push_root(ctx, (void**)&_lhs_646); mph_gc_push_root(ctx, (void**)&_rhs_647); MorphString* _ret_648 = mph_string_concat(ctx, _lhs_646, _rhs_647); mph_gc_pop_roots(ctx, 2); _ret_648; });
}
	}
	if ((digit == 7)) {
{
	result = ({ MorphString* _lhs_649 = mph_string_new(ctx, "7"); MorphString* _rhs_650 = result; mph_gc_push_root(ctx, (void**)&_lhs_649); mph_gc_push_root(ctx, (void**)&_rhs_650); MorphString* _ret_651 = mph_string_concat(ctx, _lhs_649, _rhs_650); mph_gc_pop_roots(ctx, 2); _ret_651; });
}
	}
	if ((digit == 8)) {
{
	result = ({ MorphString* _lhs_652 = mph_string_new(ctx, "8"); MorphString* _rhs_653 = result; mph_gc_push_root(ctx, (void**)&_lhs_652); mph_gc_push_root(ctx, (void**)&_rhs_653); MorphString* _ret_654 = mph_string_concat(ctx, _lhs_652, _rhs_653); mph_gc_pop_roots(ctx, 2); _ret_654; });
}
	}
	if ((digit == 9)) {
{
	result = ({ MorphString* _lhs_655 = mph_string_new(ctx, "9"); MorphString* _rhs_656 = result; mph_gc_push_root(ctx, (void**)&_lhs_655); mph_gc_push_root(ctx, (void**)&_rhs_656); MorphString* _ret_657 = mph_string_concat(ctx, _lhs_655, _rhs_656); mph_gc_pop_roots(ctx, 2); _ret_657; });
}
	}
}
	}
	if (is_negative) {
{
	result = ({ MorphString* _lhs_658 = mph_string_new(ctx, "-"); MorphString* _rhs_659 = result; mph_gc_push_root(ctx, (void**)&_lhs_658); mph_gc_push_root(ctx, (void**)&_rhs_659); MorphString* _ret_660 = mph_string_concat(ctx, _lhs_658, _rhs_659); mph_gc_pop_roots(ctx, 2); _ret_660; });
}
	}
	return result;
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_char_at(MorphContext* ctx, void* _env_void, MorphString* s, mph_int index) {
	mph_gc_push_root(ctx, (void**)&s);
	return mph_string_substring(ctx, s, index, (index + 1));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_string_escape(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	MorphString* result = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&result);
	mph_int i = 0;
	mph_int len = ({ MorphString* _len_arg_661 = s; mph_gc_push_root(ctx, (void**)&_len_arg_661); mph_int _ret_662 = ((MorphString*)_len_arg_661)->length; mph_gc_pop_roots(ctx, 1); _ret_662; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_663 = s; mph_gc_push_root(ctx, (void**)&_arg_663); MorphString* _ret_664 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_663, i); mph_gc_pop_roots(ctx, 1); _ret_664; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\\"))) {
{
	result = ({ MorphString* _lhs_665 = result; MorphString* _rhs_666 = mph_string_new(ctx, "\\\\"); mph_gc_push_root(ctx, (void**)&_lhs_665); mph_gc_push_root(ctx, (void**)&_rhs_666); MorphString* _ret_667 = mph_string_concat(ctx, _lhs_665, _rhs_666); mph_gc_pop_roots(ctx, 2); _ret_667; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\""))) {
{
	result = ({ MorphString* _lhs_668 = result; MorphString* _rhs_669 = mph_string_new(ctx, "\\\""); mph_gc_push_root(ctx, (void**)&_lhs_668); mph_gc_push_root(ctx, (void**)&_rhs_669); MorphString* _ret_670 = mph_string_concat(ctx, _lhs_668, _rhs_669); mph_gc_pop_roots(ctx, 2); _ret_670; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\n"))) {
{
	result = ({ MorphString* _lhs_671 = result; MorphString* _rhs_672 = mph_string_new(ctx, "\\n"); mph_gc_push_root(ctx, (void**)&_lhs_671); mph_gc_push_root(ctx, (void**)&_rhs_672); MorphString* _ret_673 = mph_string_concat(ctx, _lhs_671, _rhs_672); mph_gc_pop_roots(ctx, 2); _ret_673; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\r"))) {
{
	result = ({ MorphString* _lhs_674 = result; MorphString* _rhs_675 = mph_string_new(ctx, "\\r"); mph_gc_push_root(ctx, (void**)&_lhs_674); mph_gc_push_root(ctx, (void**)&_rhs_675); MorphString* _ret_676 = mph_string_concat(ctx, _lhs_674, _rhs_675); mph_gc_pop_roots(ctx, 2); _ret_676; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\t"))) {
{
	result = ({ MorphString* _lhs_677 = result; MorphString* _rhs_678 = mph_string_new(ctx, "\\t"); mph_gc_push_root(ctx, (void**)&_lhs_677); mph_gc_push_root(ctx, (void**)&_rhs_678); MorphString* _ret_679 = mph_string_concat(ctx, _lhs_677, _rhs_678); mph_gc_pop_roots(ctx, 2); _ret_679; });
}
	} else {
{
	result = ({ MorphString* _lhs_680 = result; MorphString* _rhs_681 = ch; mph_gc_push_root(ctx, (void**)&_lhs_680); mph_gc_push_root(ctx, (void**)&_rhs_681); MorphString* _ret_682 = mph_string_concat(ctx, _lhs_680, _rhs_681); mph_gc_pop_roots(ctx, 2); _ret_682; });
}
	}
}
	}
}
	}
}
	}
}
	}
	i = (i + 1);
	mph_gc_pop_roots(ctx, 1);
}
	}
	return result;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_stdlib_codegen_is_alpha(MorphContext* ctx, void* _env_void, MorphString* ch) {
	mph_gc_push_root(ctx, (void**)&ch);
	return (((((((((((((((((((((((((((((((((((((((((((((((((((mph_string_eq(ctx, ch, mph_string_new(ctx, "a")) || mph_string_eq(ctx, ch, mph_string_new(ctx, "b"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "c"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "d"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "e"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "f"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "g"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "h"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "i"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "j"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "k"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "l"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "m"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "n"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "o"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "p"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "q"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "r"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "s"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "t"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "u"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "v"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "w"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "x"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "y"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "z"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "A"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "B"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "C"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "D"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "E"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "F"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "G"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "H"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "I"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "J"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "K"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "L"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "M"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "N"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "O"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "P"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "Q"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "R"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "S"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "T"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "U"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "V"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "W"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "X"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "Y"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "Z")));
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_stdlib_codegen_is_digit(MorphContext* ctx, void* _env_void, MorphString* ch) {
	mph_gc_push_root(ctx, (void**)&ch);
	return (((((((((mph_string_eq(ctx, ch, mph_string_new(ctx, "0")) || mph_string_eq(ctx, ch, mph_string_new(ctx, "1"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "2"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "3"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "4"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "5"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "6"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "7"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "8"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "9")));
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_stdlib_codegen_is_valid_c_ident(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_int len = ({ MorphString* _len_arg_683 = name; mph_gc_push_root(ctx, (void**)&_len_arg_683); mph_int _ret_684 = ((MorphString*)_len_arg_683)->length; mph_gc_pop_roots(ctx, 1); _ret_684; });
	if ((len == 0)) {
{
	return 0;
}
	}
	MorphString* first = ({ MorphString* _arg_685 = name; mph_gc_push_root(ctx, (void**)&_arg_685); MorphString* _ret_686 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_685, 0); mph_gc_pop_roots(ctx, 1); _ret_686; });
	mph_gc_push_root(ctx, (void**)&first);
	if (((first != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_687 = first; mph_gc_push_root(ctx, (void**)&_arg_687); mph_bool _ret_688 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_687); mph_gc_pop_roots(ctx, 1); _ret_688; })))) {
{
	return 0;
}
	}
	mph_int i = 1;
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_689 = name; mph_gc_push_root(ctx, (void**)&_arg_689); MorphString* _ret_690 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_689, i); mph_gc_pop_roots(ctx, 1); _ret_690; });
	mph_gc_push_root(ctx, (void**)&ch);
	if ((((ch != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_691 = ch; mph_gc_push_root(ctx, (void**)&_arg_691); mph_bool _ret_692 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_691); mph_gc_pop_roots(ctx, 1); _ret_692; }))) && (!({ MorphString* _arg_693 = ch; mph_gc_push_root(ctx, (void**)&_arg_693); mph_bool _ret_694 = mph_stdlib_codegen_is_digit(ctx, NULL, _arg_693); mph_gc_pop_roots(ctx, 1); _ret_694; })))) {
{
	return 0;
}
	}
	i = (i + 1);
	mph_gc_pop_roots(ctx, 1);
}
	}
	return 1;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_module_to_prefix(MorphContext* ctx, void* _env_void, MorphString* path) {
	mph_gc_push_root(ctx, (void**)&path);
	MorphString* result = mph_string_new(ctx, "mph_");
	mph_gc_push_root(ctx, (void**)&result);
	mph_int i = 0;
	mph_int len = ({ MorphString* _len_arg_695 = path; mph_gc_push_root(ctx, (void**)&_len_arg_695); mph_int _ret_696 = ((MorphString*)_len_arg_695)->length; mph_gc_pop_roots(ctx, 1); _ret_696; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_697 = path; mph_gc_push_root(ctx, (void**)&_arg_697); MorphString* _ret_698 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_697, i); mph_gc_pop_roots(ctx, 1); _ret_698; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "/"))) {
{
	result = ({ MorphString* _lhs_699 = result; MorphString* _rhs_700 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_699); mph_gc_push_root(ctx, (void**)&_rhs_700); MorphString* _ret_701 = mph_string_concat(ctx, _lhs_699, _rhs_700); mph_gc_pop_roots(ctx, 2); _ret_701; });
}
	} else {
{
	if (((({ MorphString* _arg_702 = ch; mph_gc_push_root(ctx, (void**)&_arg_702); mph_bool _ret_703 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_702); mph_gc_pop_roots(ctx, 1); _ret_703; }) || ({ MorphString* _arg_704 = ch; mph_gc_push_root(ctx, (void**)&_arg_704); mph_bool _ret_705 = mph_stdlib_codegen_is_digit(ctx, NULL, _arg_704); mph_gc_pop_roots(ctx, 1); _ret_705; })) || mph_string_eq(ctx, ch, mph_string_new(ctx, "_")))) {
{
	result = ({ MorphString* _lhs_706 = result; MorphString* _rhs_707 = ch; mph_gc_push_root(ctx, (void**)&_lhs_706); mph_gc_push_root(ctx, (void**)&_rhs_707); MorphString* _ret_708 = mph_string_concat(ctx, _lhs_706, _rhs_707); mph_gc_pop_roots(ctx, 2); _ret_708; });
}
	} else {
{
	result = ({ MorphString* _lhs_709 = result; MorphString* _rhs_710 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_709); mph_gc_push_root(ctx, (void**)&_rhs_710); MorphString* _ret_711 = mph_string_concat(ctx, _lhs_709, _rhs_710); mph_gc_pop_roots(ctx, 2); _ret_711; });
}
	}
}
	}
	i = (i + 1);
	mph_gc_pop_roots(ctx, 1);
}
	}
	result = ({ MorphString* _lhs_712 = result; MorphString* _rhs_713 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_712); mph_gc_push_root(ctx, (void**)&_rhs_713); MorphString* _ret_714 = mph_string_concat(ctx, _lhs_712, _rhs_713); mph_gc_pop_roots(ctx, 2); _ret_714; });
	return result;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_IntToString(MorphContext* ctx, void* _env_void, mph_int n) {
	return mph_stdlib_codegen_int_to_string(ctx, NULL, n);
}

MorphString* mph_stdlib_codegen_StringEscape(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	return ({ MorphString* _arg_715 = s; mph_gc_push_root(ctx, (void**)&_arg_715); MorphString* _ret_716 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_715); mph_gc_pop_roots(ctx, 1); _ret_716; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_stdlib_codegen_IsValidCIdent(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	return ({ MorphString* _arg_717 = name; mph_gc_push_root(ctx, (void**)&_arg_717); mph_bool _ret_718 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_717); mph_gc_pop_roots(ctx, 1); _ret_718; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_ModuleToPrefix(MorphContext* ctx, void* _env_void, MorphString* path) {
	mph_gc_push_root(ctx, (void**)&path);
	return ({ MorphString* _arg_719 = path; mph_gc_push_root(ctx, (void**)&_arg_719); MorphString* _ret_720 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_719); mph_gc_pop_roots(ctx, 1); _ret_720; });
	mph_gc_pop_roots(ctx, 1);
}

void mph_stdlib_codegen_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â  Stdlib Codegen Utilities Test      â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n\n"));
	mph_native_print(ctx, mph_string_new(ctx, "[Test 1] int_to_string()\n"));
	MorphString* s1 = mph_stdlib_codegen_int_to_string(ctx, NULL, 0);
	mph_gc_push_root(ctx, (void**)&s1);
	mph_native_print(ctx, mph_string_new(ctx, "  0 â \""));
	mph_native_print(ctx, s1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* s2 = mph_stdlib_codegen_int_to_string(ctx, NULL, 42);
	mph_gc_push_root(ctx, (void**)&s2);
	mph_native_print(ctx, mph_string_new(ctx, "  42 â \""));
	mph_native_print(ctx, s2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* s3 = mph_stdlib_codegen_int_to_string(ctx, NULL, (-123));
	mph_gc_push_root(ctx, (void**)&s3);
	mph_native_print(ctx, mph_string_new(ctx, "  -123 â \""));
	mph_native_print(ctx, s3);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* s4 = mph_stdlib_codegen_int_to_string(ctx, NULL, 9876);
	mph_gc_push_root(ctx, (void**)&s4);
	mph_native_print(ctx, mph_string_new(ctx, "  9876 â \""));
	mph_native_print(ctx, s4);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n\n"));
	mph_native_print(ctx, mph_string_new(ctx, "[Test 2] string_escape()\n"));
	MorphString* e1 = ({ MorphString* _arg_721 = mph_string_new(ctx, "hello"); mph_gc_push_root(ctx, (void**)&_arg_721); MorphString* _ret_722 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_721); mph_gc_pop_roots(ctx, 1); _ret_722; });
	mph_gc_push_root(ctx, (void**)&e1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\" â \""));
	mph_native_print(ctx, e1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* e2 = ({ MorphString* _arg_723 = mph_string_new(ctx, "hello\nworld"); mph_gc_push_root(ctx, (void**)&_arg_723); MorphString* _ret_724 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_723); mph_gc_pop_roots(ctx, 1); _ret_724; });
	mph_gc_push_root(ctx, (void**)&e2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\\nworld\" â \""));
	mph_native_print(ctx, e2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 3] module_to_prefix()\n"));
	MorphString* p1 = ({ MorphString* _arg_725 = mph_string_new(ctx, "token"); mph_gc_push_root(ctx, (void**)&_arg_725); MorphString* _ret_726 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_725); mph_gc_pop_roots(ctx, 1); _ret_726; });
	mph_gc_push_root(ctx, (void**)&p1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"token\" â \""));
	mph_native_print(ctx, p1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* p2 = ({ MorphString* _arg_727 = mph_string_new(ctx, "std/string"); mph_gc_push_root(ctx, (void**)&_arg_727); MorphString* _ret_728 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_727); mph_gc_pop_roots(ctx, 1); _ret_728; });
	mph_gc_push_root(ctx, (void**)&p2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"std/string\" â \""));
	mph_native_print(ctx, p2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 4] is_valid_c_ident()\n"));
	mph_bool v1 = ({ MorphString* _arg_729 = mph_string_new(ctx, "foo"); mph_gc_push_root(ctx, (void**)&_arg_729); mph_bool _ret_730 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_729); mph_gc_pop_roots(ctx, 1); _ret_730; });
	mph_native_print(ctx, mph_string_new(ctx, "  \"foo\" â "));
	if (v1) {
{
	mph_native_print(ctx, mph_string_new(ctx, "valid\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "invalid\n"));
}
	}
	mph_bool v2 = ({ MorphString* _arg_731 = mph_string_new(ctx, "_bar123"); mph_gc_push_root(ctx, (void**)&_arg_731); mph_bool _ret_732 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_731); mph_gc_pop_roots(ctx, 1); _ret_732; });
	mph_native_print(ctx, mph_string_new(ctx, "  \"_bar123\" â "));
	if (v2) {
{
	mph_native_print(ctx, mph_string_new(ctx, "valid\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "invalid\n"));
}
	}
	mph_bool v3 = ({ MorphString* _arg_733 = mph_string_new(ctx, "123bad"); mph_gc_push_root(ctx, (void**)&_arg_733); mph_bool _ret_734 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_733); mph_gc_pop_roots(ctx, 1); _ret_734; });
	mph_native_print(ctx, mph_string_new(ctx, "  \"123bad\" â "));
	if (v3) {
{
	mph_native_print(ctx, mph_string_new(ctx, "valid\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "invalid\n"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\nâ All utility functions tested\n"));
	mph_gc_pop_roots(ctx, 8);
}

mph_Codegen* mph_new_codegen(MorphContext* ctx, void* _env_void) {
	return ({ mph_Codegen* _t = (mph_Codegen*)mph_alloc(ctx, sizeof(mph_Codegen), &mph_ti_mph_Codegen); mph_gc_push_root(ctx, (void**)&_t); _t->func_defs = mph_string_new(ctx, ""); _t->entry_body = mph_string_new(ctx, ""); _t->pass_log = mph_string_new(ctx, ""); _t->temp_index = 0; _t->output = mph_string_new(ctx, ""); _t->global_defs = mph_string_new(ctx, ""); _t->has_main = 0; _t->indent_level = 0; _t->current_prefix = mph_string_new(ctx, "mph_"); _t->type_defs = mph_string_new(ctx, ""); _t->prototypes = mph_string_new(ctx, ""); mph_gc_pop_roots(ctx, 1); _t; });
}

MorphString* mph_codegen_compile(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_Codegen* _obj_735 = cg; mph_gc_push_root(ctx, (void**)&_obj_735); MorphString* _val_736 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_736); _obj_735->output = _val_736; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_737 = cg; mph_gc_push_root(ctx, (void**)&_obj_737); MorphString* _val_738 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_738); _obj_737->type_defs = _val_738; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_739 = cg; mph_gc_push_root(ctx, (void**)&_obj_739); MorphString* _val_740 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_740); _obj_739->global_defs = _val_740; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_741 = cg; mph_gc_push_root(ctx, (void**)&_obj_741); MorphString* _val_742 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_742); _obj_741->prototypes = _val_742; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_743 = cg; mph_gc_push_root(ctx, (void**)&_obj_743); MorphString* _val_744 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_744); _obj_743->func_defs = _val_744; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_745 = cg; mph_gc_push_root(ctx, (void**)&_obj_745); MorphString* _val_746 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_746); _obj_745->entry_body = _val_746; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_747 = cg; mph_gc_push_root(ctx, (void**)&_obj_747); MorphString* _val_748 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_748); _obj_747->pass_log = _val_748; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_749 = cg; mph_gc_push_root(ctx, (void**)&_obj_749); _obj_749->temp_index = 0; mph_gc_pop_roots(ctx, 1); });
	({ mph_Codegen* _obj_750 = cg; mph_gc_push_root(ctx, (void**)&_obj_750); _obj_750->has_main = 0; mph_gc_pop_roots(ctx, 1); });
	({ mph_Codegen* _obj_756 = cg; mph_gc_push_root(ctx, (void**)&_obj_756); MorphString* _val_757 = ({ MorphString* _lhs_753 = ({ mph_Codegen* _obj_751 = cg; mph_gc_push_root(ctx, (void**)&_obj_751); MorphString* _ret_752 = _obj_751->output; mph_gc_pop_roots(ctx, 1); _ret_752; }); MorphString* _rhs_754 = mph_string_new(ctx, "#include \"morph.h\"\n\n"); mph_gc_push_root(ctx, (void**)&_lhs_753); mph_gc_push_root(ctx, (void**)&_rhs_754); MorphString* _ret_755 = mph_string_concat(ctx, _lhs_753, _rhs_754); mph_gc_pop_roots(ctx, 2); _ret_755; }); mph_gc_push_root(ctx, (void**)&_val_757); _obj_756->output = _val_757; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_763 = cg; mph_gc_push_root(ctx, (void**)&_obj_763); MorphString* _val_764 = ({ MorphString* _lhs_760 = ({ mph_Codegen* _obj_758 = cg; mph_gc_push_root(ctx, (void**)&_obj_758); MorphString* _ret_759 = _obj_758->output; mph_gc_pop_roots(ctx, 1); _ret_759; }); MorphString* _rhs_761 = mph_string_new(ctx, "// Native bindings\n"); mph_gc_push_root(ctx, (void**)&_lhs_760); mph_gc_push_root(ctx, (void**)&_rhs_761); MorphString* _ret_762 = mph_string_concat(ctx, _lhs_760, _rhs_761); mph_gc_pop_roots(ctx, 2); _ret_762; }); mph_gc_push_root(ctx, (void**)&_val_764); _obj_763->output = _val_764; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_770 = cg; mph_gc_push_root(ctx, (void**)&_obj_770); MorphString* _val_771 = ({ MorphString* _lhs_767 = ({ mph_Codegen* _obj_765 = cg; mph_gc_push_root(ctx, (void**)&_obj_765); MorphString* _ret_766 = _obj_765->output; mph_gc_pop_roots(ctx, 1); _ret_766; }); MorphString* _rhs_768 = mph_string_new(ctx, "void mph_native_print(MorphContext* ctx, MorphString* s);\n"); mph_gc_push_root(ctx, (void**)&_lhs_767); mph_gc_push_root(ctx, (void**)&_rhs_768); MorphString* _ret_769 = mph_string_concat(ctx, _lhs_767, _rhs_768); mph_gc_pop_roots(ctx, 2); _ret_769; }); mph_gc_push_root(ctx, (void**)&_val_771); _obj_770->output = _val_771; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_777 = cg; mph_gc_push_root(ctx, (void**)&_obj_777); MorphString* _val_778 = ({ MorphString* _lhs_774 = ({ mph_Codegen* _obj_772 = cg; mph_gc_push_root(ctx, (void**)&_obj_772); MorphString* _ret_773 = _obj_772->output; mph_gc_pop_roots(ctx, 1); _ret_773; }); MorphString* _rhs_775 = mph_string_new(ctx, "void mph_native_print_int(MorphContext* ctx, mph_int n);\n"); mph_gc_push_root(ctx, (void**)&_lhs_774); mph_gc_push_root(ctx, (void**)&_rhs_775); MorphString* _ret_776 = mph_string_concat(ctx, _lhs_774, _rhs_775); mph_gc_pop_roots(ctx, 2); _ret_776; }); mph_gc_push_root(ctx, (void**)&_val_778); _obj_777->output = _val_778; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_784 = cg; mph_gc_push_root(ctx, (void**)&_obj_784); MorphString* _val_785 = ({ MorphString* _lhs_781 = ({ mph_Codegen* _obj_779 = cg; mph_gc_push_root(ctx, (void**)&_obj_779); MorphString* _ret_780 = _obj_779->output; mph_gc_pop_roots(ctx, 1); _ret_780; }); MorphString* _rhs_782 = mph_string_new(ctx, "void mph_native_print_error(MorphContext* ctx, MorphError* err);\n"); mph_gc_push_root(ctx, (void**)&_lhs_781); mph_gc_push_root(ctx, (void**)&_rhs_782); MorphString* _ret_783 = mph_string_concat(ctx, _lhs_781, _rhs_782); mph_gc_pop_roots(ctx, 2); _ret_783; }); mph_gc_push_root(ctx, (void**)&_val_785); _obj_784->output = _val_785; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_791 = cg; mph_gc_push_root(ctx, (void**)&_obj_791); MorphString* _val_792 = ({ MorphString* _lhs_788 = ({ mph_Codegen* _obj_786 = cg; mph_gc_push_root(ctx, (void**)&_obj_786); MorphString* _ret_787 = _obj_786->output; mph_gc_pop_roots(ctx, 1); _ret_787; }); MorphString* _rhs_789 = mph_string_new(ctx, "mph_int mph_string_index(MorphContext* ctx, MorphString* s, MorphString* sub);\n"); mph_gc_push_root(ctx, (void**)&_lhs_788); mph_gc_push_root(ctx, (void**)&_rhs_789); MorphString* _ret_790 = mph_string_concat(ctx, _lhs_788, _rhs_789); mph_gc_pop_roots(ctx, 2); _ret_790; }); mph_gc_push_root(ctx, (void**)&_val_792); _obj_791->output = _val_792; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_798 = cg; mph_gc_push_root(ctx, (void**)&_obj_798); MorphString* _val_799 = ({ MorphString* _lhs_795 = ({ mph_Codegen* _obj_793 = cg; mph_gc_push_root(ctx, (void**)&_obj_793); MorphString* _ret_794 = _obj_793->output; mph_gc_pop_roots(ctx, 1); _ret_794; }); MorphString* _rhs_796 = mph_string_new(ctx, "MorphString* mph_string_trim(MorphContext* ctx, MorphString* s, MorphString* cut);\n"); mph_gc_push_root(ctx, (void**)&_lhs_795); mph_gc_push_root(ctx, (void**)&_rhs_796); MorphString* _ret_797 = mph_string_concat(ctx, _lhs_795, _rhs_796); mph_gc_pop_roots(ctx, 2); _ret_797; }); mph_gc_push_root(ctx, (void**)&_val_799); _obj_798->output = _val_799; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_805 = cg; mph_gc_push_root(ctx, (void**)&_obj_805); MorphString* _val_806 = ({ MorphString* _lhs_802 = ({ mph_Codegen* _obj_800 = cg; mph_gc_push_root(ctx, (void**)&_obj_800); MorphString* _ret_801 = _obj_800->output; mph_gc_pop_roots(ctx, 1); _ret_801; }); MorphString* _rhs_803 = mph_string_new(ctx, "MorphArray* mph_string_split(MorphContext* ctx, MorphString* s, MorphString* sep);\n"); mph_gc_push_root(ctx, (void**)&_lhs_802); mph_gc_push_root(ctx, (void**)&_rhs_803); MorphString* _ret_804 = mph_string_concat(ctx, _lhs_802, _rhs_803); mph_gc_pop_roots(ctx, 2); _ret_804; }); mph_gc_push_root(ctx, (void**)&_val_806); _obj_805->output = _val_806; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_812 = cg; mph_gc_push_root(ctx, (void**)&_obj_812); MorphString* _val_813 = ({ MorphString* _lhs_809 = ({ mph_Codegen* _obj_807 = cg; mph_gc_push_root(ctx, (void**)&_obj_807); MorphString* _ret_808 = _obj_807->output; mph_gc_pop_roots(ctx, 1); _ret_808; }); MorphString* _rhs_810 = mph_string_new(ctx, "MorphString* mph_string_substring(MorphContext* ctx, MorphString* s, mph_int start, mph_int end);\n"); mph_gc_push_root(ctx, (void**)&_lhs_809); mph_gc_push_root(ctx, (void**)&_rhs_810); MorphString* _ret_811 = mph_string_concat(ctx, _lhs_809, _rhs_810); mph_gc_pop_roots(ctx, 2); _ret_811; }); mph_gc_push_root(ctx, (void**)&_val_813); _obj_812->output = _val_813; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_819 = cg; mph_gc_push_root(ctx, (void**)&_obj_819); MorphString* _val_820 = ({ MorphString* _lhs_816 = ({ mph_Codegen* _obj_814 = cg; mph_gc_push_root(ctx, (void**)&_obj_814); MorphString* _ret_815 = _obj_814->output; mph_gc_pop_roots(ctx, 1); _ret_815; }); MorphString* _rhs_817 = mph_string_new(ctx, "MorphError* mph_error_new(MorphContext* ctx, MorphString* msg);\n\n"); mph_gc_push_root(ctx, (void**)&_lhs_816); mph_gc_push_root(ctx, (void**)&_rhs_817); MorphString* _ret_818 = mph_string_concat(ctx, _lhs_816, _rhs_817); mph_gc_pop_roots(ctx, 2); _ret_818; }); mph_gc_push_root(ctx, (void**)&_val_820); _obj_819->output = _val_820; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _arg_821 = cg; mph_gc_push_root(ctx, (void**)&_arg_821); mph_ast_Program* _arg_822 = prog; mph_gc_push_root(ctx, (void**)&_arg_822); mph_codegen_pass_collect_globals(ctx, NULL, _arg_821, _arg_822); mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _arg_823 = cg; mph_gc_push_root(ctx, (void**)&_arg_823); mph_ast_Program* _arg_824 = prog; mph_gc_push_root(ctx, (void**)&_arg_824); mph_codegen_pass_analyze_captures(ctx, NULL, _arg_823, _arg_824); mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _arg_825 = cg; mph_gc_push_root(ctx, (void**)&_arg_825); mph_ast_Program* _arg_826 = prog; mph_gc_push_root(ctx, (void**)&_arg_826); mph_codegen_pass_compile_struct_types(ctx, NULL, _arg_825, _arg_826); mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _arg_827 = cg; mph_gc_push_root(ctx, (void**)&_arg_827); mph_ast_Program* _arg_828 = prog; mph_gc_push_root(ctx, (void**)&_arg_828); mph_codegen_pass_compile_struct_rtti(ctx, NULL, _arg_827, _arg_828); mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _arg_829 = cg; mph_gc_push_root(ctx, (void**)&_arg_829); mph_ast_Program* _arg_830 = prog; mph_gc_push_root(ctx, (void**)&_arg_830); MorphString* _arg_831 = mph_string_new(ctx, "mph_"); mph_gc_push_root(ctx, (void**)&_arg_831); mph_codegen_pass_compile_module(ctx, NULL, _arg_829, _arg_830, _arg_831); mph_gc_pop_roots(ctx, 3); });
	({ mph_Codegen* _obj_837 = cg; mph_gc_push_root(ctx, (void**)&_obj_837); MorphString* _val_838 = ({ MorphString* _lhs_834 = ({ mph_Codegen* _obj_832 = cg; mph_gc_push_root(ctx, (void**)&_obj_832); MorphString* _ret_833 = _obj_832->output; mph_gc_pop_roots(ctx, 1); _ret_833; }); MorphString* _rhs_835 = mph_string_new(ctx, "// Pass Log\n"); mph_gc_push_root(ctx, (void**)&_lhs_834); mph_gc_push_root(ctx, (void**)&_rhs_835); MorphString* _ret_836 = mph_string_concat(ctx, _lhs_834, _rhs_835); mph_gc_pop_roots(ctx, 2); _ret_836; }); mph_gc_push_root(ctx, (void**)&_val_838); _obj_837->output = _val_838; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_846 = cg; mph_gc_push_root(ctx, (void**)&_obj_846); MorphString* _val_847 = ({ MorphString* _lhs_843 = ({ mph_Codegen* _obj_839 = cg; mph_gc_push_root(ctx, (void**)&_obj_839); MorphString* _ret_840 = _obj_839->output; mph_gc_pop_roots(ctx, 1); _ret_840; }); MorphString* _rhs_844 = ({ mph_Codegen* _obj_841 = cg; mph_gc_push_root(ctx, (void**)&_obj_841); MorphString* _ret_842 = _obj_841->pass_log; mph_gc_pop_roots(ctx, 1); _ret_842; }); mph_gc_push_root(ctx, (void**)&_lhs_843); mph_gc_push_root(ctx, (void**)&_rhs_844); MorphString* _ret_845 = mph_string_concat(ctx, _lhs_843, _rhs_844); mph_gc_pop_roots(ctx, 2); _ret_845; }); mph_gc_push_root(ctx, (void**)&_val_847); _obj_846->output = _val_847; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_853 = cg; mph_gc_push_root(ctx, (void**)&_obj_853); MorphString* _val_854 = ({ MorphString* _lhs_850 = ({ mph_Codegen* _obj_848 = cg; mph_gc_push_root(ctx, (void**)&_obj_848); MorphString* _ret_849 = _obj_848->output; mph_gc_pop_roots(ctx, 1); _ret_849; }); MorphString* _rhs_851 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_850); mph_gc_push_root(ctx, (void**)&_rhs_851); MorphString* _ret_852 = mph_string_concat(ctx, _lhs_850, _rhs_851); mph_gc_pop_roots(ctx, 2); _ret_852; }); mph_gc_push_root(ctx, (void**)&_val_854); _obj_853->output = _val_854; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_860 = cg; mph_gc_push_root(ctx, (void**)&_obj_860); MorphString* _val_861 = ({ MorphString* _lhs_857 = ({ mph_Codegen* _obj_855 = cg; mph_gc_push_root(ctx, (void**)&_obj_855); MorphString* _ret_856 = _obj_855->output; mph_gc_pop_roots(ctx, 1); _ret_856; }); MorphString* _rhs_858 = mph_string_new(ctx, "// Type Definitions\n"); mph_gc_push_root(ctx, (void**)&_lhs_857); mph_gc_push_root(ctx, (void**)&_rhs_858); MorphString* _ret_859 = mph_string_concat(ctx, _lhs_857, _rhs_858); mph_gc_pop_roots(ctx, 2); _ret_859; }); mph_gc_push_root(ctx, (void**)&_val_861); _obj_860->output = _val_861; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_869 = cg; mph_gc_push_root(ctx, (void**)&_obj_869); MorphString* _val_870 = ({ MorphString* _lhs_866 = ({ mph_Codegen* _obj_862 = cg; mph_gc_push_root(ctx, (void**)&_obj_862); MorphString* _ret_863 = _obj_862->output; mph_gc_pop_roots(ctx, 1); _ret_863; }); MorphString* _rhs_867 = ({ mph_Codegen* _obj_864 = cg; mph_gc_push_root(ctx, (void**)&_obj_864); MorphString* _ret_865 = _obj_864->type_defs; mph_gc_pop_roots(ctx, 1); _ret_865; }); mph_gc_push_root(ctx, (void**)&_lhs_866); mph_gc_push_root(ctx, (void**)&_rhs_867); MorphString* _ret_868 = mph_string_concat(ctx, _lhs_866, _rhs_867); mph_gc_pop_roots(ctx, 2); _ret_868; }); mph_gc_push_root(ctx, (void**)&_val_870); _obj_869->output = _val_870; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_876 = cg; mph_gc_push_root(ctx, (void**)&_obj_876); MorphString* _val_877 = ({ MorphString* _lhs_873 = ({ mph_Codegen* _obj_871 = cg; mph_gc_push_root(ctx, (void**)&_obj_871); MorphString* _ret_872 = _obj_871->output; mph_gc_pop_roots(ctx, 1); _ret_872; }); MorphString* _rhs_874 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_873); mph_gc_push_root(ctx, (void**)&_rhs_874); MorphString* _ret_875 = mph_string_concat(ctx, _lhs_873, _rhs_874); mph_gc_pop_roots(ctx, 2); _ret_875; }); mph_gc_push_root(ctx, (void**)&_val_877); _obj_876->output = _val_877; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_883 = cg; mph_gc_push_root(ctx, (void**)&_obj_883); MorphString* _val_884 = ({ MorphString* _lhs_880 = ({ mph_Codegen* _obj_878 = cg; mph_gc_push_root(ctx, (void**)&_obj_878); MorphString* _ret_879 = _obj_878->output; mph_gc_pop_roots(ctx, 1); _ret_879; }); MorphString* _rhs_881 = mph_string_new(ctx, "// Global Variables\n"); mph_gc_push_root(ctx, (void**)&_lhs_880); mph_gc_push_root(ctx, (void**)&_rhs_881); MorphString* _ret_882 = mph_string_concat(ctx, _lhs_880, _rhs_881); mph_gc_pop_roots(ctx, 2); _ret_882; }); mph_gc_push_root(ctx, (void**)&_val_884); _obj_883->output = _val_884; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_892 = cg; mph_gc_push_root(ctx, (void**)&_obj_892); MorphString* _val_893 = ({ MorphString* _lhs_889 = ({ mph_Codegen* _obj_885 = cg; mph_gc_push_root(ctx, (void**)&_obj_885); MorphString* _ret_886 = _obj_885->output; mph_gc_pop_roots(ctx, 1); _ret_886; }); MorphString* _rhs_890 = ({ mph_Codegen* _obj_887 = cg; mph_gc_push_root(ctx, (void**)&_obj_887); MorphString* _ret_888 = _obj_887->global_defs; mph_gc_pop_roots(ctx, 1); _ret_888; }); mph_gc_push_root(ctx, (void**)&_lhs_889); mph_gc_push_root(ctx, (void**)&_rhs_890); MorphString* _ret_891 = mph_string_concat(ctx, _lhs_889, _rhs_890); mph_gc_pop_roots(ctx, 2); _ret_891; }); mph_gc_push_root(ctx, (void**)&_val_893); _obj_892->output = _val_893; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_899 = cg; mph_gc_push_root(ctx, (void**)&_obj_899); MorphString* _val_900 = ({ MorphString* _lhs_896 = ({ mph_Codegen* _obj_894 = cg; mph_gc_push_root(ctx, (void**)&_obj_894); MorphString* _ret_895 = _obj_894->output; mph_gc_pop_roots(ctx, 1); _ret_895; }); MorphString* _rhs_897 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_896); mph_gc_push_root(ctx, (void**)&_rhs_897); MorphString* _ret_898 = mph_string_concat(ctx, _lhs_896, _rhs_897); mph_gc_pop_roots(ctx, 2); _ret_898; }); mph_gc_push_root(ctx, (void**)&_val_900); _obj_899->output = _val_900; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_906 = cg; mph_gc_push_root(ctx, (void**)&_obj_906); MorphString* _val_907 = ({ MorphString* _lhs_903 = ({ mph_Codegen* _obj_901 = cg; mph_gc_push_root(ctx, (void**)&_obj_901); MorphString* _ret_902 = _obj_901->output; mph_gc_pop_roots(ctx, 1); _ret_902; }); MorphString* _rhs_904 = mph_string_new(ctx, "// Function Prototypes\n"); mph_gc_push_root(ctx, (void**)&_lhs_903); mph_gc_push_root(ctx, (void**)&_rhs_904); MorphString* _ret_905 = mph_string_concat(ctx, _lhs_903, _rhs_904); mph_gc_pop_roots(ctx, 2); _ret_905; }); mph_gc_push_root(ctx, (void**)&_val_907); _obj_906->output = _val_907; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_915 = cg; mph_gc_push_root(ctx, (void**)&_obj_915); MorphString* _val_916 = ({ MorphString* _lhs_912 = ({ mph_Codegen* _obj_908 = cg; mph_gc_push_root(ctx, (void**)&_obj_908); MorphString* _ret_909 = _obj_908->output; mph_gc_pop_roots(ctx, 1); _ret_909; }); MorphString* _rhs_913 = ({ mph_Codegen* _obj_910 = cg; mph_gc_push_root(ctx, (void**)&_obj_910); MorphString* _ret_911 = _obj_910->prototypes; mph_gc_pop_roots(ctx, 1); _ret_911; }); mph_gc_push_root(ctx, (void**)&_lhs_912); mph_gc_push_root(ctx, (void**)&_rhs_913); MorphString* _ret_914 = mph_string_concat(ctx, _lhs_912, _rhs_913); mph_gc_pop_roots(ctx, 2); _ret_914; }); mph_gc_push_root(ctx, (void**)&_val_916); _obj_915->output = _val_916; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_922 = cg; mph_gc_push_root(ctx, (void**)&_obj_922); MorphString* _val_923 = ({ MorphString* _lhs_919 = ({ mph_Codegen* _obj_917 = cg; mph_gc_push_root(ctx, (void**)&_obj_917); MorphString* _ret_918 = _obj_917->output; mph_gc_pop_roots(ctx, 1); _ret_918; }); MorphString* _rhs_920 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_919); mph_gc_push_root(ctx, (void**)&_rhs_920); MorphString* _ret_921 = mph_string_concat(ctx, _lhs_919, _rhs_920); mph_gc_pop_roots(ctx, 2); _ret_921; }); mph_gc_push_root(ctx, (void**)&_val_923); _obj_922->output = _val_923; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_929 = cg; mph_gc_push_root(ctx, (void**)&_obj_929); MorphString* _val_930 = ({ MorphString* _lhs_926 = ({ mph_Codegen* _obj_924 = cg; mph_gc_push_root(ctx, (void**)&_obj_924); MorphString* _ret_925 = _obj_924->output; mph_gc_pop_roots(ctx, 1); _ret_925; }); MorphString* _rhs_927 = mph_string_new(ctx, "// Function Definitions\n"); mph_gc_push_root(ctx, (void**)&_lhs_926); mph_gc_push_root(ctx, (void**)&_rhs_927); MorphString* _ret_928 = mph_string_concat(ctx, _lhs_926, _rhs_927); mph_gc_pop_roots(ctx, 2); _ret_928; }); mph_gc_push_root(ctx, (void**)&_val_930); _obj_929->output = _val_930; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_938 = cg; mph_gc_push_root(ctx, (void**)&_obj_938); MorphString* _val_939 = ({ MorphString* _lhs_935 = ({ mph_Codegen* _obj_931 = cg; mph_gc_push_root(ctx, (void**)&_obj_931); MorphString* _ret_932 = _obj_931->output; mph_gc_pop_roots(ctx, 1); _ret_932; }); MorphString* _rhs_936 = ({ mph_Codegen* _obj_933 = cg; mph_gc_push_root(ctx, (void**)&_obj_933); MorphString* _ret_934 = _obj_933->func_defs; mph_gc_pop_roots(ctx, 1); _ret_934; }); mph_gc_push_root(ctx, (void**)&_lhs_935); mph_gc_push_root(ctx, (void**)&_rhs_936); MorphString* _ret_937 = mph_string_concat(ctx, _lhs_935, _rhs_936); mph_gc_pop_roots(ctx, 2); _ret_937; }); mph_gc_push_root(ctx, (void**)&_val_939); _obj_938->output = _val_939; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_945 = cg; mph_gc_push_root(ctx, (void**)&_obj_945); MorphString* _val_946 = ({ MorphString* _lhs_942 = ({ mph_Codegen* _obj_940 = cg; mph_gc_push_root(ctx, (void**)&_obj_940); MorphString* _ret_941 = _obj_940->output; mph_gc_pop_roots(ctx, 1); _ret_941; }); MorphString* _rhs_943 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_942); mph_gc_push_root(ctx, (void**)&_rhs_943); MorphString* _ret_944 = mph_string_concat(ctx, _lhs_942, _rhs_943); mph_gc_pop_roots(ctx, 2); _ret_944; }); mph_gc_push_root(ctx, (void**)&_val_946); _obj_945->output = _val_946; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_952 = cg; mph_gc_push_root(ctx, (void**)&_obj_952); MorphString* _val_953 = ({ MorphString* _lhs_949 = ({ mph_Codegen* _obj_947 = cg; mph_gc_push_root(ctx, (void**)&_obj_947); MorphString* _ret_948 = _obj_947->output; mph_gc_pop_roots(ctx, 1); _ret_948; }); MorphString* _rhs_950 = mph_string_new(ctx, "// Entry Point\n"); mph_gc_push_root(ctx, (void**)&_lhs_949); mph_gc_push_root(ctx, (void**)&_rhs_950); MorphString* _ret_951 = mph_string_concat(ctx, _lhs_949, _rhs_950); mph_gc_pop_roots(ctx, 2); _ret_951; }); mph_gc_push_root(ctx, (void**)&_val_953); _obj_952->output = _val_953; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_959 = cg; mph_gc_push_root(ctx, (void**)&_obj_959); MorphString* _val_960 = ({ MorphString* _lhs_956 = ({ mph_Codegen* _obj_954 = cg; mph_gc_push_root(ctx, (void**)&_obj_954); MorphString* _ret_955 = _obj_954->output; mph_gc_pop_roots(ctx, 1); _ret_955; }); MorphString* _rhs_957 = mph_string_new(ctx, "void morph_entry_point(MorphContext* ctx) {\n"); mph_gc_push_root(ctx, (void**)&_lhs_956); mph_gc_push_root(ctx, (void**)&_rhs_957); MorphString* _ret_958 = mph_string_concat(ctx, _lhs_956, _rhs_957); mph_gc_pop_roots(ctx, 2); _ret_958; }); mph_gc_push_root(ctx, (void**)&_val_960); _obj_959->output = _val_960; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_968 = cg; mph_gc_push_root(ctx, (void**)&_obj_968); MorphString* _val_969 = ({ MorphString* _lhs_965 = ({ mph_Codegen* _obj_961 = cg; mph_gc_push_root(ctx, (void**)&_obj_961); MorphString* _ret_962 = _obj_961->output; mph_gc_pop_roots(ctx, 1); _ret_962; }); MorphString* _rhs_966 = ({ mph_Codegen* _obj_963 = cg; mph_gc_push_root(ctx, (void**)&_obj_963); MorphString* _ret_964 = _obj_963->entry_body; mph_gc_pop_roots(ctx, 1); _ret_964; }); mph_gc_push_root(ctx, (void**)&_lhs_965); mph_gc_push_root(ctx, (void**)&_rhs_966); MorphString* _ret_967 = mph_string_concat(ctx, _lhs_965, _rhs_966); mph_gc_pop_roots(ctx, 2); _ret_967; }); mph_gc_push_root(ctx, (void**)&_val_969); _obj_968->output = _val_969; mph_gc_pop_roots(ctx, 2); });
	if (({ mph_Codegen* _obj_970 = cg; mph_gc_push_root(ctx, (void**)&_obj_970); mph_bool _ret_971 = _obj_970->has_main; mph_gc_pop_roots(ctx, 1); _ret_971; })) {
{
	({ mph_Codegen* _obj_977 = cg; mph_gc_push_root(ctx, (void**)&_obj_977); MorphString* _val_978 = ({ MorphString* _lhs_974 = ({ mph_Codegen* _obj_972 = cg; mph_gc_push_root(ctx, (void**)&_obj_972); MorphString* _ret_973 = _obj_972->output; mph_gc_pop_roots(ctx, 1); _ret_973; }); MorphString* _rhs_975 = mph_string_new(ctx, "\tmph_main(ctx, NULL);\n"); mph_gc_push_root(ctx, (void**)&_lhs_974); mph_gc_push_root(ctx, (void**)&_rhs_975); MorphString* _ret_976 = mph_string_concat(ctx, _lhs_974, _rhs_975); mph_gc_pop_roots(ctx, 2); _ret_976; }); mph_gc_push_root(ctx, (void**)&_val_978); _obj_977->output = _val_978; mph_gc_pop_roots(ctx, 2); });
}
	}
	({ mph_Codegen* _obj_984 = cg; mph_gc_push_root(ctx, (void**)&_obj_984); MorphString* _val_985 = ({ MorphString* _lhs_981 = ({ mph_Codegen* _obj_979 = cg; mph_gc_push_root(ctx, (void**)&_obj_979); MorphString* _ret_980 = _obj_979->output; mph_gc_pop_roots(ctx, 1); _ret_980; }); MorphString* _rhs_982 = mph_string_new(ctx, "}\n"); mph_gc_push_root(ctx, (void**)&_lhs_981); mph_gc_push_root(ctx, (void**)&_rhs_982); MorphString* _ret_983 = mph_string_concat(ctx, _lhs_981, _rhs_982); mph_gc_pop_roots(ctx, 2); _ret_983; }); mph_gc_push_root(ctx, (void**)&_val_985); _obj_984->output = _val_985; mph_gc_pop_roots(ctx, 2); });
	return ({ mph_Codegen* _obj_986 = cg; mph_gc_push_root(ctx, (void**)&_obj_986); MorphString* _ret_987 = _obj_986->output; mph_gc_pop_roots(ctx, 1); _ret_987; });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_record_pass(MorphContext* ctx, void* _env_void, mph_Codegen* cg, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&name);
	({ mph_Codegen* _obj_999 = cg; mph_gc_push_root(ctx, (void**)&_obj_999); MorphString* _val_1000 = ({ MorphString* _lhs_996 = ({ MorphString* _lhs_993 = ({ MorphString* _lhs_990 = ({ mph_Codegen* _obj_988 = cg; mph_gc_push_root(ctx, (void**)&_obj_988); MorphString* _ret_989 = _obj_988->pass_log; mph_gc_pop_roots(ctx, 1); _ret_989; }); MorphString* _rhs_991 = mph_string_new(ctx, "// "); mph_gc_push_root(ctx, (void**)&_lhs_990); mph_gc_push_root(ctx, (void**)&_rhs_991); MorphString* _ret_992 = mph_string_concat(ctx, _lhs_990, _rhs_991); mph_gc_pop_roots(ctx, 2); _ret_992; }); MorphString* _rhs_994 = name; mph_gc_push_root(ctx, (void**)&_lhs_993); mph_gc_push_root(ctx, (void**)&_rhs_994); MorphString* _ret_995 = mph_string_concat(ctx, _lhs_993, _rhs_994); mph_gc_pop_roots(ctx, 2); _ret_995; }); MorphString* _rhs_997 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_996); mph_gc_push_root(ctx, (void**)&_rhs_997); MorphString* _ret_998 = mph_string_concat(ctx, _lhs_996, _rhs_997); mph_gc_pop_roots(ctx, 2); _ret_998; }); mph_gc_push_root(ctx, (void**)&_val_1000); _obj_999->pass_log = _val_1000; mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_pass_collect_globals(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_Codegen* _arg_1001 = cg; mph_gc_push_root(ctx, (void**)&_arg_1001); MorphString* _arg_1002 = mph_string_new(ctx, "pass1_collect_globals"); mph_gc_push_root(ctx, (void**)&_arg_1002); mph_codegen_record_pass(ctx, NULL, _arg_1001, _arg_1002); mph_gc_pop_roots(ctx, 2); });
	if (({ mph_ast_Program* _obj_1003 = prog; mph_gc_push_root(ctx, (void**)&_obj_1003); mph_bool _ret_1004 = _obj_1003->has_var_statement; mph_gc_pop_roots(ctx, 1); _ret_1004; })) {
{
	({ mph_Codegen* _obj_1014 = cg; mph_gc_push_root(ctx, (void**)&_obj_1014); MorphString* _val_1015 = ({ MorphString* _lhs_1011 = ({ mph_Codegen* _obj_1005 = cg; mph_gc_push_root(ctx, (void**)&_obj_1005); MorphString* _ret_1006 = _obj_1005->global_defs; mph_gc_pop_roots(ctx, 1); _ret_1006; }); MorphString* _rhs_1012 = ({ mph_ast_VarStatement* _arg_1009 = ({ mph_ast_Program* _obj_1007 = prog; mph_gc_push_root(ctx, (void**)&_obj_1007); mph_ast_VarStatement* _ret_1008 = _obj_1007->var_statement; mph_gc_pop_roots(ctx, 1); _ret_1008; }); mph_gc_push_root(ctx, (void**)&_arg_1009); MorphString* _ret_1010 = mph_codegen_compile_global_var_declaration(ctx, NULL, _arg_1009); mph_gc_pop_roots(ctx, 1); _ret_1010; }); mph_gc_push_root(ctx, (void**)&_lhs_1011); mph_gc_push_root(ctx, (void**)&_rhs_1012); MorphString* _ret_1013 = mph_string_concat(ctx, _lhs_1011, _rhs_1012); mph_gc_pop_roots(ctx, 2); _ret_1013; }); mph_gc_push_root(ctx, (void**)&_val_1015); _obj_1014->global_defs = _val_1015; mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _obj_1025 = cg; mph_gc_push_root(ctx, (void**)&_obj_1025); MorphString* _val_1026 = ({ MorphString* _lhs_1022 = ({ mph_Codegen* _obj_1016 = cg; mph_gc_push_root(ctx, (void**)&_obj_1016); MorphString* _ret_1017 = _obj_1016->entry_body; mph_gc_pop_roots(ctx, 1); _ret_1017; }); MorphString* _rhs_1023 = ({ mph_ast_VarStatement* _arg_1020 = ({ mph_ast_Program* _obj_1018 = prog; mph_gc_push_root(ctx, (void**)&_obj_1018); mph_ast_VarStatement* _ret_1019 = _obj_1018->var_statement; mph_gc_pop_roots(ctx, 1); _ret_1019; }); mph_gc_push_root(ctx, (void**)&_arg_1020); MorphString* _ret_1021 = mph_codegen_compile_global_var_initialization(ctx, NULL, _arg_1020); mph_gc_pop_roots(ctx, 1); _ret_1021; }); mph_gc_push_root(ctx, (void**)&_lhs_1022); mph_gc_push_root(ctx, (void**)&_rhs_1023); MorphString* _ret_1024 = mph_string_concat(ctx, _lhs_1022, _rhs_1023); mph_gc_pop_roots(ctx, 2); _ret_1024; }); mph_gc_push_root(ctx, (void**)&_val_1026); _obj_1025->entry_body = _val_1026; mph_gc_pop_roots(ctx, 2); });
}
	}
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_pass_analyze_captures(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_Codegen* _arg_1027 = cg; mph_gc_push_root(ctx, (void**)&_arg_1027); MorphString* _arg_1028 = mph_string_new(ctx, "pass2_analyze_captures"); mph_gc_push_root(ctx, (void**)&_arg_1028); mph_codegen_record_pass(ctx, NULL, _arg_1027, _arg_1028); mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_pass_compile_struct_types(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_Codegen* _arg_1029 = cg; mph_gc_push_root(ctx, (void**)&_arg_1029); MorphString* _arg_1030 = mph_string_new(ctx, "pass3_compile_struct_types"); mph_gc_push_root(ctx, (void**)&_arg_1030); mph_codegen_record_pass(ctx, NULL, _arg_1029, _arg_1030); mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_pass_compile_struct_rtti(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_Codegen* _arg_1031 = cg; mph_gc_push_root(ctx, (void**)&_arg_1031); MorphString* _arg_1032 = mph_string_new(ctx, "pass4_compile_struct_rtti"); mph_gc_push_root(ctx, (void**)&_arg_1032); mph_codegen_record_pass(ctx, NULL, _arg_1031, _arg_1032); mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_pass_compile_module(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_Codegen* _arg_1033 = cg; mph_gc_push_root(ctx, (void**)&_arg_1033); MorphString* _arg_1034 = mph_string_new(ctx, "pass5_compile_module"); mph_gc_push_root(ctx, (void**)&_arg_1034); mph_codegen_record_pass(ctx, NULL, _arg_1033, _arg_1034); mph_gc_pop_roots(ctx, 2); });
	({ mph_Codegen* _arg_1035 = cg; mph_gc_push_root(ctx, (void**)&_arg_1035); mph_ast_Program* _arg_1036 = prog; mph_gc_push_root(ctx, (void**)&_arg_1036); MorphString* _arg_1037 = prefix; mph_gc_push_root(ctx, (void**)&_arg_1037); mph_codegen_compile_program(ctx, NULL, _arg_1035, _arg_1036, _arg_1037); mph_gc_pop_roots(ctx, 3); });
	mph_gc_pop_roots(ctx, 3);
}

void mph_codegen_compile_program(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_Codegen* _obj_1038 = cg; mph_gc_push_root(ctx, (void**)&_obj_1038); MorphString* _val_1039 = prefix; mph_gc_push_root(ctx, (void**)&_val_1039); _obj_1038->current_prefix = _val_1039; mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_map_type_to_c(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	if ((({ mph_types_Type* _obj_1040 = t; mph_gc_push_root(ctx, (void**)&_obj_1040); mph_int _ret_1041 = _obj_1040->kind; mph_gc_pop_roots(ctx, 1); _ret_1041; }) == mph_types_KIND_INT)) {
{
	return mph_string_new(ctx, "mph_int");
}
	}
	if ((({ mph_types_Type* _obj_1042 = t; mph_gc_push_root(ctx, (void**)&_obj_1042); mph_int _ret_1043 = _obj_1042->kind; mph_gc_pop_roots(ctx, 1); _ret_1043; }) == mph_types_KIND_FLOAT)) {
{
	return mph_string_new(ctx, "mph_float");
}
	}
	if ((({ mph_types_Type* _obj_1044 = t; mph_gc_push_root(ctx, (void**)&_obj_1044); mph_int _ret_1045 = _obj_1044->kind; mph_gc_pop_roots(ctx, 1); _ret_1045; }) == mph_types_KIND_STRING)) {
{
	return mph_string_new(ctx, "MorphString*");
}
	}
	if ((({ mph_types_Type* _obj_1046 = t; mph_gc_push_root(ctx, (void**)&_obj_1046); mph_int _ret_1047 = _obj_1046->kind; mph_gc_pop_roots(ctx, 1); _ret_1047; }) == mph_types_KIND_BOOL)) {
{
	return mph_string_new(ctx, "mph_bool");
}
	}
	if ((({ mph_types_Type* _obj_1048 = t; mph_gc_push_root(ctx, (void**)&_obj_1048); mph_int _ret_1049 = _obj_1048->kind; mph_gc_pop_roots(ctx, 1); _ret_1049; }) == mph_types_KIND_VOID)) {
{
	return mph_string_new(ctx, "void");
}
	}
	if ((({ mph_types_Type* _obj_1050 = t; mph_gc_push_root(ctx, (void**)&_obj_1050); mph_int _ret_1051 = _obj_1050->kind; mph_gc_pop_roots(ctx, 1); _ret_1051; }) == mph_types_KIND_FUNCTION)) {
{
	return mph_string_new(ctx, "MorphClosure*");
}
	}
	if ((({ mph_types_Type* _obj_1052 = t; mph_gc_push_root(ctx, (void**)&_obj_1052); mph_int _ret_1053 = _obj_1052->kind; mph_gc_pop_roots(ctx, 1); _ret_1053; }) == mph_types_KIND_STRUCT)) {
{
	if ((({ mph_types_Type* _obj_1054 = t; mph_gc_push_root(ctx, (void**)&_obj_1054); MorphString* _ret_1055 = _obj_1054->name; mph_gc_pop_roots(ctx, 1); _ret_1055; }) != mph_string_new(ctx, ""))) {
{
	return ({ MorphString* _lhs_1061 = ({ MorphString* _lhs_1058 = mph_string_new(ctx, "mph_"); MorphString* _rhs_1059 = ({ mph_types_Type* _obj_1056 = t; mph_gc_push_root(ctx, (void**)&_obj_1056); MorphString* _ret_1057 = _obj_1056->name; mph_gc_pop_roots(ctx, 1); _ret_1057; }); mph_gc_push_root(ctx, (void**)&_lhs_1058); mph_gc_push_root(ctx, (void**)&_rhs_1059); MorphString* _ret_1060 = mph_string_concat(ctx, _lhs_1058, _rhs_1059); mph_gc_pop_roots(ctx, 2); _ret_1060; }); MorphString* _rhs_1062 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_lhs_1061); mph_gc_push_root(ctx, (void**)&_rhs_1062); MorphString* _ret_1063 = mph_string_concat(ctx, _lhs_1061, _rhs_1062); mph_gc_pop_roots(ctx, 2); _ret_1063; });
}
	}
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_1064 = t; mph_gc_push_root(ctx, (void**)&_obj_1064); mph_int _ret_1065 = _obj_1064->kind; mph_gc_pop_roots(ctx, 1); _ret_1065; }) == mph_types_KIND_INTERFACE)) {
{
	return mph_string_new(ctx, "MorphInterface");
}
	}
	if ((({ mph_types_Type* _obj_1066 = t; mph_gc_push_root(ctx, (void**)&_obj_1066); mph_int _ret_1067 = _obj_1066->kind; mph_gc_pop_roots(ctx, 1); _ret_1067; }) == mph_types_KIND_ARRAY)) {
{
	return mph_string_new(ctx, "MorphArray*");
}
	}
	if ((({ mph_types_Type* _obj_1068 = t; mph_gc_push_root(ctx, (void**)&_obj_1068); mph_int _ret_1069 = _obj_1068->kind; mph_gc_pop_roots(ctx, 1); _ret_1069; }) == mph_types_KIND_MAP)) {
{
	return mph_string_new(ctx, "MorphMap*");
}
	}
	if ((({ mph_types_Type* _obj_1070 = t; mph_gc_push_root(ctx, (void**)&_obj_1070); mph_int _ret_1071 = _obj_1070->kind; mph_gc_pop_roots(ctx, 1); _ret_1071; }) == mph_types_KIND_POINTER)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_1072 = t; mph_gc_push_root(ctx, (void**)&_obj_1072); mph_int _ret_1073 = _obj_1072->kind; mph_gc_pop_roots(ctx, 1); _ret_1073; }) == mph_types_KIND_MULTI)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_1074 = t; mph_gc_push_root(ctx, (void**)&_obj_1074); mph_int _ret_1075 = _obj_1074->kind; mph_gc_pop_roots(ctx, 1); _ret_1075; }) == mph_types_KIND_ERROR)) {
{
	return mph_string_new(ctx, "MorphError*");
}
	}
	if ((({ mph_types_Type* _obj_1076 = t; mph_gc_push_root(ctx, (void**)&_obj_1076); mph_int _ret_1077 = _obj_1076->kind; mph_gc_pop_roots(ctx, 1); _ret_1077; }) == mph_types_KIND_USER_ERROR)) {
{
	return mph_string_new(ctx, "MorphError*");
}
	}
	if ((({ mph_types_Type* _obj_1078 = t; mph_gc_push_root(ctx, (void**)&_obj_1078); mph_int _ret_1079 = _obj_1078->kind; mph_gc_pop_roots(ctx, 1); _ret_1079; }) == mph_types_KIND_NULL)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_1080 = t; mph_gc_push_root(ctx, (void**)&_obj_1080); mph_int _ret_1081 = _obj_1080->kind; mph_gc_pop_roots(ctx, 1); _ret_1081; }) == mph_types_KIND_UNKNOWN)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_1082 = t; mph_gc_push_root(ctx, (void**)&_obj_1082); mph_int _ret_1083 = _obj_1082->kind; mph_gc_pop_roots(ctx, 1); _ret_1083; }) == mph_types_KIND_CHANNEL)) {
{
	return mph_string_new(ctx, "MorphChannel*");
}
	}
	if ((({ mph_types_Type* _obj_1084 = t; mph_gc_push_root(ctx, (void**)&_obj_1084); mph_int _ret_1085 = _obj_1084->kind; mph_gc_pop_roots(ctx, 1); _ret_1085; }) == mph_types_KIND_MODULE)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	return mph_string_new(ctx, "void*");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_next_temp(MorphContext* ctx, void* _env_void, mph_Codegen* cg, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_Codegen* _obj_1088 = cg; mph_gc_push_root(ctx, (void**)&_obj_1088); _obj_1088->temp_index = (({ mph_Codegen* _obj_1086 = cg; mph_gc_push_root(ctx, (void**)&_obj_1086); mph_int _ret_1087 = _obj_1086->temp_index; mph_gc_pop_roots(ctx, 1); _ret_1087; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return ({ MorphString* _lhs_1091 = prefix; MorphString* _rhs_1092 = mph_stdlib_codegen_IntToString(ctx, NULL, ({ mph_Codegen* _obj_1089 = cg; mph_gc_push_root(ctx, (void**)&_obj_1089); mph_int _ret_1090 = _obj_1089->temp_index; mph_gc_pop_roots(ctx, 1); _ret_1090; })); mph_gc_push_root(ctx, (void**)&_lhs_1091); mph_gc_push_root(ctx, (void**)&_rhs_1092); MorphString* _ret_1093 = mph_string_concat(ctx, _lhs_1091, _rhs_1092); mph_gc_pop_roots(ctx, 2); _ret_1093; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_append(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	return ({ MorphString* _lhs_1094 = buf; MorphString* _rhs_1095 = text; mph_gc_push_root(ctx, (void**)&_lhs_1094); mph_gc_push_root(ctx, (void**)&_rhs_1095); MorphString* _ret_1096 = mph_string_concat(ctx, _lhs_1094, _rhs_1095); mph_gc_pop_roots(ctx, 2); _ret_1096; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_append_line(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	return ({ MorphString* _lhs_1100 = ({ MorphString* _lhs_1097 = buf; MorphString* _rhs_1098 = text; mph_gc_push_root(ctx, (void**)&_lhs_1097); mph_gc_push_root(ctx, (void**)&_rhs_1098); MorphString* _ret_1099 = mph_string_concat(ctx, _lhs_1097, _rhs_1098); mph_gc_pop_roots(ctx, 2); _ret_1099; }); MorphString* _rhs_1101 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_1100); mph_gc_push_root(ctx, (void**)&_rhs_1101); MorphString* _ret_1102 = mph_string_concat(ctx, _lhs_1100, _rhs_1101); mph_gc_pop_roots(ctx, 2); _ret_1102; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_append_indent(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text, mph_int level) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	MorphString* indent = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&indent);
	mph_int i = 0;
	while ((i < level)) {
{
	indent = ({ MorphString* _lhs_1103 = indent; MorphString* _rhs_1104 = mph_string_new(ctx, "\t"); mph_gc_push_root(ctx, (void**)&_lhs_1103); mph_gc_push_root(ctx, (void**)&_rhs_1104); MorphString* _ret_1105 = mph_string_concat(ctx, _lhs_1103, _rhs_1104); mph_gc_pop_roots(ctx, 2); _ret_1105; });
	i = (i + 1);
}
	}
	return ({ MorphString* _lhs_1112 = ({ MorphString* _lhs_1109 = ({ MorphString* _lhs_1106 = buf; MorphString* _rhs_1107 = indent; mph_gc_push_root(ctx, (void**)&_lhs_1106); mph_gc_push_root(ctx, (void**)&_rhs_1107); MorphString* _ret_1108 = mph_string_concat(ctx, _lhs_1106, _rhs_1107); mph_gc_pop_roots(ctx, 2); _ret_1108; }); MorphString* _rhs_1110 = text; mph_gc_push_root(ctx, (void**)&_lhs_1109); mph_gc_push_root(ctx, (void**)&_rhs_1110); MorphString* _ret_1111 = mph_string_concat(ctx, _lhs_1109, _rhs_1110); mph_gc_pop_roots(ctx, 2); _ret_1111; }); MorphString* _rhs_1113 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_1112); mph_gc_push_root(ctx, (void**)&_rhs_1113); MorphString* _ret_1114 = mph_string_concat(ctx, _lhs_1112, _rhs_1113); mph_gc_pop_roots(ctx, 2); _ret_1114; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_compile_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_stdlib_codegen_IntToString(ctx, NULL, ({ mph_ast_IntegerLiteral* _obj_1115 = lit; mph_gc_push_root(ctx, (void**)&_obj_1115); mph_int _ret_1116 = _obj_1115->value; mph_gc_pop_roots(ctx, 1); _ret_1116; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_float_literal(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_FloatLiteral* _obj_1117 = lit; mph_gc_push_root(ctx, (void**)&_obj_1117); MorphString* _ret_1118 = _obj_1117->value_str; mph_gc_pop_roots(ctx, 1); _ret_1118; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_char_literal(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_stdlib_codegen_IntToString(ctx, NULL, ({ mph_ast_CharLiteral* _obj_1119 = lit; mph_gc_push_root(ctx, (void**)&_obj_1119); mph_int _ret_1120 = _obj_1119->value; mph_gc_pop_roots(ctx, 1); _ret_1120; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	MorphString* escaped = ({ MorphString* _arg_1123 = ({ mph_ast_StringLiteral* _obj_1121 = lit; mph_gc_push_root(ctx, (void**)&_obj_1121); MorphString* _ret_1122 = _obj_1121->value; mph_gc_pop_roots(ctx, 1); _ret_1122; }); mph_gc_push_root(ctx, (void**)&_arg_1123); MorphString* _ret_1124 = mph_stdlib_codegen_StringEscape(ctx, NULL, _arg_1123); mph_gc_pop_roots(ctx, 1); _ret_1124; });
	mph_gc_push_root(ctx, (void**)&escaped);
	return ({ MorphString* _lhs_1128 = ({ MorphString* _lhs_1125 = mph_string_new(ctx, "mph_string_new(ctx, \""); MorphString* _rhs_1126 = escaped; mph_gc_push_root(ctx, (void**)&_lhs_1125); mph_gc_push_root(ctx, (void**)&_rhs_1126); MorphString* _ret_1127 = mph_string_concat(ctx, _lhs_1125, _rhs_1126); mph_gc_pop_roots(ctx, 2); _ret_1127; }); MorphString* _rhs_1129 = mph_string_new(ctx, "\")"); mph_gc_push_root(ctx, (void**)&_lhs_1128); mph_gc_push_root(ctx, (void**)&_rhs_1129); MorphString* _ret_1130 = mph_string_concat(ctx, _lhs_1128, _rhs_1129); mph_gc_pop_roots(ctx, 2); _ret_1130; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	if (({ mph_ast_BooleanLiteral* _obj_1131 = lit; mph_gc_push_root(ctx, (void**)&_obj_1131); mph_bool _ret_1132 = _obj_1131->value; mph_gc_pop_roots(ctx, 1); _ret_1132; })) {
{
	return mph_string_new(ctx, "1");
}
	}
	return mph_string_new(ctx, "0");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_null_literal(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_string_new(ctx, "NULL");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	return ({ mph_ast_Identifier* _obj_1133 = ident; mph_gc_push_root(ctx, (void**)&_obj_1133); MorphString* _ret_1134 = _obj_1133->value; mph_gc_pop_roots(ctx, 1); _ret_1134; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_infix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&left_code);
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	MorphString* c_operator = operator;
	mph_gc_push_root(ctx, (void**)&c_operator);
	if (mph_string_eq(ctx, operator, mph_string_new(ctx, "dan"))) {
{
	c_operator = mph_string_new(ctx, "&&");
}
	} else {
{
	if (mph_string_eq(ctx, operator, mph_string_new(ctx, "atau"))) {
{
	c_operator = mph_string_new(ctx, "||");
}
	}
}
	}
	return ({ MorphString* _lhs_1150 = ({ MorphString* _lhs_1147 = ({ MorphString* _lhs_1144 = ({ MorphString* _lhs_1141 = ({ MorphString* _lhs_1138 = ({ MorphString* _lhs_1135 = mph_string_new(ctx, "("); MorphString* _rhs_1136 = left_code; mph_gc_push_root(ctx, (void**)&_lhs_1135); mph_gc_push_root(ctx, (void**)&_rhs_1136); MorphString* _ret_1137 = mph_string_concat(ctx, _lhs_1135, _rhs_1136); mph_gc_pop_roots(ctx, 2); _ret_1137; }); MorphString* _rhs_1139 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1138); mph_gc_push_root(ctx, (void**)&_rhs_1139); MorphString* _ret_1140 = mph_string_concat(ctx, _lhs_1138, _rhs_1139); mph_gc_pop_roots(ctx, 2); _ret_1140; }); MorphString* _rhs_1142 = c_operator; mph_gc_push_root(ctx, (void**)&_lhs_1141); mph_gc_push_root(ctx, (void**)&_rhs_1142); MorphString* _ret_1143 = mph_string_concat(ctx, _lhs_1141, _rhs_1142); mph_gc_pop_roots(ctx, 2); _ret_1143; }); MorphString* _rhs_1145 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1144); mph_gc_push_root(ctx, (void**)&_rhs_1145); MorphString* _ret_1146 = mph_string_concat(ctx, _lhs_1144, _rhs_1145); mph_gc_pop_roots(ctx, 2); _ret_1146; }); MorphString* _rhs_1148 = right_code; mph_gc_push_root(ctx, (void**)&_lhs_1147); mph_gc_push_root(ctx, (void**)&_rhs_1148); MorphString* _ret_1149 = mph_string_concat(ctx, _lhs_1147, _rhs_1148); mph_gc_pop_roots(ctx, 2); _ret_1149; }); MorphString* _rhs_1151 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_lhs_1150); mph_gc_push_root(ctx, (void**)&_rhs_1151); MorphString* _ret_1152 = mph_string_concat(ctx, _lhs_1150, _rhs_1151); mph_gc_pop_roots(ctx, 2); _ret_1152; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_compile_prefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	MorphString* c_operator = operator;
	mph_gc_push_root(ctx, (void**)&c_operator);
	if (mph_string_eq(ctx, operator, mph_string_new(ctx, "tidak"))) {
{
	c_operator = mph_string_new(ctx, "!");
}
	}
	return ({ MorphString* _lhs_1159 = ({ MorphString* _lhs_1156 = ({ MorphString* _lhs_1153 = mph_string_new(ctx, "("); MorphString* _rhs_1154 = c_operator; mph_gc_push_root(ctx, (void**)&_lhs_1153); mph_gc_push_root(ctx, (void**)&_rhs_1154); MorphString* _ret_1155 = mph_string_concat(ctx, _lhs_1153, _rhs_1154); mph_gc_pop_roots(ctx, 2); _ret_1155; }); MorphString* _rhs_1157 = right_code; mph_gc_push_root(ctx, (void**)&_lhs_1156); mph_gc_push_root(ctx, (void**)&_rhs_1157); MorphString* _ret_1158 = mph_string_concat(ctx, _lhs_1156, _rhs_1157); mph_gc_pop_roots(ctx, 2); _ret_1158; }); MorphString* _rhs_1160 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_lhs_1159); mph_gc_push_root(ctx, (void**)&_rhs_1160); MorphString* _ret_1161 = mph_string_concat(ctx, _lhs_1159, _rhs_1160); mph_gc_pop_roots(ctx, 2); _ret_1161; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_resolve_builtin_name(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "native_print"))) {
{
	return mph_string_new(ctx, "mph_native_print");
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "native_print_error"))) {
{
	return mph_string_new(ctx, "mph_native_print_error");
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "native_print_int"))) {
{
	return mph_string_new(ctx, "mph_native_print_int");
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "error"))) {
{
	return mph_string_new(ctx, "mph_error_new");
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "index"))) {
{
	return mph_string_new(ctx, "mph_string_index");
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "trim"))) {
{
	return mph_string_new(ctx, "mph_string_trim");
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "split"))) {
{
	return mph_string_new(ctx, "mph_string_split");
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "substring"))) {
{
	return mph_string_new(ctx, "mph_string_substring");
}
	}
	return mph_string_new(ctx, "");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_builtin_call(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&args_code);
	MorphString* c_name = ({ MorphString* _arg_1162 = name; mph_gc_push_root(ctx, (void**)&_arg_1162); MorphString* _ret_1163 = mph_codegen_resolve_builtin_name(ctx, NULL, _arg_1162); mph_gc_pop_roots(ctx, 1); _ret_1163; });
	mph_gc_push_root(ctx, (void**)&c_name);
	if (mph_string_eq(ctx, c_name, mph_string_new(ctx, ""))) {
{
	return mph_string_new(ctx, "");
}
	}
	if (mph_string_eq(ctx, args_code, mph_string_new(ctx, ""))) {
{
	return ({ MorphString* _lhs_1164 = c_name; MorphString* _rhs_1165 = mph_string_new(ctx, "(ctx)"); mph_gc_push_root(ctx, (void**)&_lhs_1164); mph_gc_push_root(ctx, (void**)&_rhs_1165); MorphString* _ret_1166 = mph_string_concat(ctx, _lhs_1164, _rhs_1165); mph_gc_pop_roots(ctx, 2); _ret_1166; });
}
	}
	return ({ MorphString* _lhs_1173 = ({ MorphString* _lhs_1170 = ({ MorphString* _lhs_1167 = c_name; MorphString* _rhs_1168 = mph_string_new(ctx, "(ctx, "); mph_gc_push_root(ctx, (void**)&_lhs_1167); mph_gc_push_root(ctx, (void**)&_rhs_1168); MorphString* _ret_1169 = mph_string_concat(ctx, _lhs_1167, _rhs_1168); mph_gc_pop_roots(ctx, 2); _ret_1169; }); MorphString* _rhs_1171 = args_code; mph_gc_push_root(ctx, (void**)&_lhs_1170); mph_gc_push_root(ctx, (void**)&_rhs_1171); MorphString* _ret_1172 = mph_string_concat(ctx, _lhs_1170, _rhs_1171); mph_gc_pop_roots(ctx, 2); _ret_1172; }); MorphString* _rhs_1174 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_lhs_1173); mph_gc_push_root(ctx, (void**)&_rhs_1174); MorphString* _ret_1175 = mph_string_concat(ctx, _lhs_1173, _rhs_1174); mph_gc_pop_roots(ctx, 2); _ret_1175; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_var_type_from_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str) {
	mph_gc_push_root(ctx, (void**)&type_str);
	if (mph_string_eq(ctx, type_str, mph_string_new(ctx, "int"))) {
{
	return mph_string_new(ctx, "mph_int");
}
	}
	if (mph_string_eq(ctx, type_str, mph_string_new(ctx, "float"))) {
{
	return mph_string_new(ctx, "mph_float");
}
	}
	if (mph_string_eq(ctx, type_str, mph_string_new(ctx, "bool"))) {
{
	return mph_string_new(ctx, "mph_bool");
}
	}
	if (mph_string_eq(ctx, type_str, mph_string_new(ctx, "string"))) {
{
	return mph_string_new(ctx, "MorphString*");
}
	}
	return mph_string_new(ctx, "mph_int");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_default_value_for_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str) {
	mph_gc_push_root(ctx, (void**)&type_str);
	if (mph_string_eq(ctx, type_str, mph_string_new(ctx, "float"))) {
{
	return mph_string_new(ctx, "0.0");
}
	}
	if (mph_string_eq(ctx, type_str, mph_string_new(ctx, "string"))) {
{
	return mph_string_new(ctx, "NULL");
}
	}
	return mph_string_new(ctx, "0");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_var_type_from_token(MorphContext* ctx, void* _env_void, mph_int token_type) {
	if ((token_type == mph_token_TOKEN_STRING)) {
{
	return mph_string_new(ctx, "MorphString*");
}
	}
	if ((token_type == mph_token_TOKEN_FLOAT)) {
{
	return mph_string_new(ctx, "mph_float");
}
	}
	if ((token_type == mph_token_TOKEN_INT)) {
{
	return mph_string_new(ctx, "mph_int");
}
	}
	if ((token_type == mph_token_TOKEN_BENAR)) {
{
	return mph_string_new(ctx, "mph_bool");
}
	}
	if ((token_type == mph_token_TOKEN_SALAH)) {
{
	return mph_string_new(ctx, "mph_bool");
}
	}
	if ((token_type == mph_token_TOKEN_CHAR)) {
{
	return mph_string_new(ctx, "mph_int");
}
	}
	return mph_string_new(ctx, "mph_int");
}

MorphString* mph_codegen_value_code_from_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal) {
	mph_gc_push_root(ctx, (void**)&literal);
	if ((token_type == mph_token_TOKEN_STRING)) {
{
	mph_ast_StringLiteral* lit = ({ MorphString* _arg_1176 = literal; mph_gc_push_root(ctx, (void**)&_arg_1176); mph_ast_StringLiteral* _ret_1177 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_1176, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_1177; });
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_StringLiteral* _arg_1178 = lit; mph_gc_push_root(ctx, (void**)&_arg_1178); MorphString* _ret_1179 = mph_codegen_compile_string_literal(ctx, NULL, _arg_1178); mph_gc_pop_roots(ctx, 1); _ret_1179; });
	mph_gc_pop_roots(ctx, 1);
}
	}
	if ((token_type == mph_token_TOKEN_FLOAT)) {
{
	return literal;
}
	}
	if ((token_type == mph_token_TOKEN_INT)) {
{
	return literal;
}
	}
	if ((token_type == mph_token_TOKEN_BENAR)) {
{
	mph_ast_BooleanLiteral* lit_true = ({ MorphString* _arg_1180 = mph_string_new(ctx, "benar"); mph_gc_push_root(ctx, (void**)&_arg_1180); mph_ast_BooleanLiteral* _ret_1181 = mph_ast_MakeBooleanLiteral(ctx, NULL, 1, _arg_1180, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_1181; });
	mph_gc_push_root(ctx, (void**)&lit_true);
	return ({ mph_ast_BooleanLiteral* _arg_1182 = lit_true; mph_gc_push_root(ctx, (void**)&_arg_1182); MorphString* _ret_1183 = mph_codegen_compile_boolean_literal(ctx, NULL, _arg_1182); mph_gc_pop_roots(ctx, 1); _ret_1183; });
	mph_gc_pop_roots(ctx, 1);
}
	}
	if ((token_type == mph_token_TOKEN_SALAH)) {
{
	mph_ast_BooleanLiteral* lit_false = ({ MorphString* _arg_1184 = mph_string_new(ctx, "salah"); mph_gc_push_root(ctx, (void**)&_arg_1184); mph_ast_BooleanLiteral* _ret_1185 = mph_ast_MakeBooleanLiteral(ctx, NULL, 0, _arg_1184, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_1185; });
	mph_gc_push_root(ctx, (void**)&lit_false);
	return ({ mph_ast_BooleanLiteral* _arg_1186 = lit_false; mph_gc_push_root(ctx, (void**)&_arg_1186); MorphString* _ret_1187 = mph_codegen_compile_boolean_literal(ctx, NULL, _arg_1186); mph_gc_pop_roots(ctx, 1); _ret_1187; });
	mph_gc_pop_roots(ctx, 1);
}
	}
	return literal;
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_var_statement_typed(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code, MorphString* c_type) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	mph_gc_push_root(ctx, (void**)&c_type);
	return ({ MorphString* _lhs_1203 = ({ MorphString* _lhs_1200 = ({ MorphString* _lhs_1197 = ({ MorphString* _lhs_1194 = ({ MorphString* _lhs_1191 = ({ MorphString* _lhs_1188 = mph_string_new(ctx, "\t"); MorphString* _rhs_1189 = c_type; mph_gc_push_root(ctx, (void**)&_lhs_1188); mph_gc_push_root(ctx, (void**)&_rhs_1189); MorphString* _ret_1190 = mph_string_concat(ctx, _lhs_1188, _rhs_1189); mph_gc_pop_roots(ctx, 2); _ret_1190; }); MorphString* _rhs_1192 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1191); mph_gc_push_root(ctx, (void**)&_rhs_1192); MorphString* _ret_1193 = mph_string_concat(ctx, _lhs_1191, _rhs_1192); mph_gc_pop_roots(ctx, 2); _ret_1193; }); MorphString* _rhs_1195 = name; mph_gc_push_root(ctx, (void**)&_lhs_1194); mph_gc_push_root(ctx, (void**)&_rhs_1195); MorphString* _ret_1196 = mph_string_concat(ctx, _lhs_1194, _rhs_1195); mph_gc_pop_roots(ctx, 2); _ret_1196; }); MorphString* _rhs_1198 = mph_string_new(ctx, " = "); mph_gc_push_root(ctx, (void**)&_lhs_1197); mph_gc_push_root(ctx, (void**)&_rhs_1198); MorphString* _ret_1199 = mph_string_concat(ctx, _lhs_1197, _rhs_1198); mph_gc_pop_roots(ctx, 2); _ret_1199; }); MorphString* _rhs_1201 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1200); mph_gc_push_root(ctx, (void**)&_rhs_1201); MorphString* _ret_1202 = mph_string_concat(ctx, _lhs_1200, _rhs_1201); mph_gc_pop_roots(ctx, 2); _ret_1202; }); MorphString* _rhs_1204 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1203); mph_gc_push_root(ctx, (void**)&_rhs_1204); MorphString* _ret_1205 = mph_string_concat(ctx, _lhs_1203, _rhs_1204); mph_gc_pop_roots(ctx, 2); _ret_1205; });
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_var_type_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	if ((({ mph_ast_VarStatement* _obj_1206 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1206); MorphString* _ret_1207 = _obj_1206->value_type; mph_gc_pop_roots(ctx, 1); _ret_1207; }) != mph_string_new(ctx, "-"))) {
{
	return ({ MorphString* _arg_1210 = ({ mph_ast_VarStatement* _obj_1208 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1208); MorphString* _ret_1209 = _obj_1208->value_type; mph_gc_pop_roots(ctx, 1); _ret_1209; }); mph_gc_push_root(ctx, (void**)&_arg_1210); MorphString* _ret_1211 = mph_codegen_var_type_from_annotation(ctx, NULL, _arg_1210); mph_gc_pop_roots(ctx, 1); _ret_1211; });
}
	}
	if (({ mph_ast_VarStatement* _obj_1212 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1212); mph_bool _ret_1213 = _obj_1212->has_value; mph_gc_pop_roots(ctx, 1); _ret_1213; })) {
{
	return mph_codegen_var_type_from_token(ctx, NULL, ({ mph_ast_VarStatement* _obj_1214 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1214); mph_int _ret_1215 = _obj_1214->value_token_type; mph_gc_pop_roots(ctx, 1); _ret_1215; }));
}
	}
	return ({ MorphString* _arg_1218 = ({ mph_ast_VarStatement* _obj_1216 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1216); MorphString* _ret_1217 = _obj_1216->value_type; mph_gc_pop_roots(ctx, 1); _ret_1217; }); mph_gc_push_root(ctx, (void**)&_arg_1218); MorphString* _ret_1219 = mph_codegen_var_type_from_annotation(ctx, NULL, _arg_1218); mph_gc_pop_roots(ctx, 1); _ret_1219; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_var_value_code_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	if (({ mph_ast_VarStatement* _obj_1220 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1220); mph_bool _ret_1221 = _obj_1220->has_value; mph_gc_pop_roots(ctx, 1); _ret_1221; })) {
{
	return ({ MorphString* _arg_1226 = ({ mph_ast_VarStatement* _obj_1224 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1224); MorphString* _ret_1225 = _obj_1224->value_literal; mph_gc_pop_roots(ctx, 1); _ret_1225; }); mph_gc_push_root(ctx, (void**)&_arg_1226); MorphString* _ret_1227 = mph_codegen_value_code_from_token(ctx, NULL, ({ mph_ast_VarStatement* _obj_1222 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1222); mph_int _ret_1223 = _obj_1222->value_token_type; mph_gc_pop_roots(ctx, 1); _ret_1223; }), _arg_1226); mph_gc_pop_roots(ctx, 1); _ret_1227; });
}
	}
	return ({ MorphString* _arg_1230 = ({ mph_ast_VarStatement* _obj_1228 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1228); MorphString* _ret_1229 = _obj_1228->value_type; mph_gc_pop_roots(ctx, 1); _ret_1229; }); mph_gc_push_root(ctx, (void**)&_arg_1230); MorphString* _ret_1231 = mph_codegen_default_value_for_annotation(ctx, NULL, _arg_1230); mph_gc_pop_roots(ctx, 1); _ret_1231; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_global_var_declaration(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	MorphString* c_type = ({ mph_ast_VarStatement* _arg_1232 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1232); MorphString* _ret_1233 = mph_codegen_var_type_from_statement(ctx, NULL, _arg_1232); mph_gc_pop_roots(ctx, 1); _ret_1233; });
	mph_gc_push_root(ctx, (void**)&c_type);
	return ({ MorphString* _lhs_1242 = ({ MorphString* _lhs_1239 = ({ MorphString* _lhs_1234 = c_type; MorphString* _rhs_1235 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1234); mph_gc_push_root(ctx, (void**)&_rhs_1235); MorphString* _ret_1236 = mph_string_concat(ctx, _lhs_1234, _rhs_1235); mph_gc_pop_roots(ctx, 2); _ret_1236; }); MorphString* _rhs_1240 = ({ mph_ast_VarStatement* _obj_1237 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1237); MorphString* _ret_1238 = _obj_1237->name; mph_gc_pop_roots(ctx, 1); _ret_1238; }); mph_gc_push_root(ctx, (void**)&_lhs_1239); mph_gc_push_root(ctx, (void**)&_rhs_1240); MorphString* _ret_1241 = mph_string_concat(ctx, _lhs_1239, _rhs_1240); mph_gc_pop_roots(ctx, 2); _ret_1241; }); MorphString* _rhs_1243 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1242); mph_gc_push_root(ctx, (void**)&_rhs_1243); MorphString* _ret_1244 = mph_string_concat(ctx, _lhs_1242, _rhs_1243); mph_gc_pop_roots(ctx, 2); _ret_1244; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_global_var_initialization(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	MorphString* value_code = ({ mph_ast_VarStatement* _arg_1245 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1245); MorphString* _ret_1246 = mph_codegen_var_value_code_from_statement(ctx, NULL, _arg_1245); mph_gc_pop_roots(ctx, 1); _ret_1246; });
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _lhs_1258 = ({ MorphString* _lhs_1255 = ({ MorphString* _lhs_1252 = ({ MorphString* _lhs_1249 = mph_string_new(ctx, "\t"); MorphString* _rhs_1250 = ({ mph_ast_VarStatement* _obj_1247 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1247); MorphString* _ret_1248 = _obj_1247->name; mph_gc_pop_roots(ctx, 1); _ret_1248; }); mph_gc_push_root(ctx, (void**)&_lhs_1249); mph_gc_push_root(ctx, (void**)&_rhs_1250); MorphString* _ret_1251 = mph_string_concat(ctx, _lhs_1249, _rhs_1250); mph_gc_pop_roots(ctx, 2); _ret_1251; }); MorphString* _rhs_1253 = mph_string_new(ctx, " = "); mph_gc_push_root(ctx, (void**)&_lhs_1252); mph_gc_push_root(ctx, (void**)&_rhs_1253); MorphString* _ret_1254 = mph_string_concat(ctx, _lhs_1252, _rhs_1253); mph_gc_pop_roots(ctx, 2); _ret_1254; }); MorphString* _rhs_1256 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1255); mph_gc_push_root(ctx, (void**)&_rhs_1256); MorphString* _ret_1257 = mph_string_concat(ctx, _lhs_1255, _rhs_1256); mph_gc_pop_roots(ctx, 2); _ret_1257; }); MorphString* _rhs_1259 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1258); mph_gc_push_root(ctx, (void**)&_rhs_1259); MorphString* _ret_1260 = mph_string_concat(ctx, _lhs_1258, _rhs_1259); mph_gc_pop_roots(ctx, 2); _ret_1260; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_var_statement_from_stmt(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	MorphString* c_type = ({ mph_ast_VarStatement* _arg_1261 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1261); MorphString* _ret_1262 = mph_codegen_var_type_from_statement(ctx, NULL, _arg_1261); mph_gc_pop_roots(ctx, 1); _ret_1262; });
	mph_gc_push_root(ctx, (void**)&c_type);
	MorphString* value_code = ({ mph_ast_VarStatement* _arg_1263 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1263); MorphString* _ret_1264 = mph_codegen_var_value_code_from_statement(ctx, NULL, _arg_1263); mph_gc_pop_roots(ctx, 1); _ret_1264; });
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1267 = ({ mph_ast_VarStatement* _obj_1265 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1265); MorphString* _ret_1266 = _obj_1265->name; mph_gc_pop_roots(ctx, 1); _ret_1266; }); mph_gc_push_root(ctx, (void**)&_arg_1267); MorphString* _arg_1268 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1268); MorphString* _arg_1269 = c_type; mph_gc_push_root(ctx, (void**)&_arg_1269); MorphString* _ret_1270 = mph_codegen_compile_var_statement_typed(ctx, NULL, _arg_1267, _arg_1268, _arg_1269); mph_gc_pop_roots(ctx, 3); _ret_1270; });
	mph_gc_pop_roots(ctx, 2);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_var_statement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _lhs_1280 = ({ MorphString* _lhs_1277 = ({ MorphString* _lhs_1274 = ({ MorphString* _lhs_1271 = mph_string_new(ctx, "\tmph_int "); MorphString* _rhs_1272 = name; mph_gc_push_root(ctx, (void**)&_lhs_1271); mph_gc_push_root(ctx, (void**)&_rhs_1272); MorphString* _ret_1273 = mph_string_concat(ctx, _lhs_1271, _rhs_1272); mph_gc_pop_roots(ctx, 2); _ret_1273; }); MorphString* _rhs_1275 = mph_string_new(ctx, " = "); mph_gc_push_root(ctx, (void**)&_lhs_1274); mph_gc_push_root(ctx, (void**)&_rhs_1275); MorphString* _ret_1276 = mph_string_concat(ctx, _lhs_1274, _rhs_1275); mph_gc_pop_roots(ctx, 2); _ret_1276; }); MorphString* _rhs_1278 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1277); mph_gc_push_root(ctx, (void**)&_rhs_1278); MorphString* _ret_1279 = mph_string_concat(ctx, _lhs_1277, _rhs_1278); mph_gc_pop_roots(ctx, 2); _ret_1279; }); MorphString* _rhs_1281 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1280); mph_gc_push_root(ctx, (void**)&_rhs_1281); MorphString* _ret_1282 = mph_string_concat(ctx, _lhs_1280, _rhs_1281); mph_gc_pop_roots(ctx, 2); _ret_1282; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_compile_expression_statement(MorphContext* ctx, void* _env_void, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _lhs_1286 = ({ MorphString* _lhs_1283 = mph_string_new(ctx, "\t"); MorphString* _rhs_1284 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1283); mph_gc_push_root(ctx, (void**)&_rhs_1284); MorphString* _ret_1285 = mph_string_concat(ctx, _lhs_1283, _rhs_1284); mph_gc_pop_roots(ctx, 2); _ret_1285; }); MorphString* _rhs_1287 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1286); mph_gc_push_root(ctx, (void**)&_rhs_1287); MorphString* _ret_1288 = mph_string_concat(ctx, _lhs_1286, _rhs_1287); mph_gc_pop_roots(ctx, 2); _ret_1288; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_compile_return_statement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	if (has_value) {
{
	return ({ MorphString* _lhs_1292 = ({ MorphString* _lhs_1289 = mph_string_new(ctx, "\treturn "); MorphString* _rhs_1290 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1289); mph_gc_push_root(ctx, (void**)&_rhs_1290); MorphString* _ret_1291 = mph_string_concat(ctx, _lhs_1289, _rhs_1290); mph_gc_pop_roots(ctx, 2); _ret_1291; }); MorphString* _rhs_1293 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1292); mph_gc_push_root(ctx, (void**)&_rhs_1293); MorphString* _ret_1294 = mph_string_concat(ctx, _lhs_1292, _rhs_1293); mph_gc_pop_roots(ctx, 2); _ret_1294; });
}
	}
	return mph_string_new(ctx, "\treturn;\n");
	mph_gc_pop_roots(ctx, 1);
}

mph_Codegen* mph_NewCodegen(MorphContext* ctx, void* _env_void) {
	return mph_new_codegen(ctx, NULL);
}

MorphString* mph_Compile(MorphContext* ctx, void* _env_void, mph_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	return ({ mph_Codegen* _arg_1295 = cg; mph_gc_push_root(ctx, (void**)&_arg_1295); mph_ast_Program* _arg_1296 = prog; mph_gc_push_root(ctx, (void**)&_arg_1296); MorphString* _ret_1297 = mph_codegen_compile(ctx, NULL, _arg_1295, _arg_1296); mph_gc_pop_roots(ctx, 2); _ret_1297; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_MapTypeToC(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_types_Type* _arg_1298 = t; mph_gc_push_root(ctx, (void**)&_arg_1298); MorphString* _ret_1299 = mph_codegen_map_type_to_c(ctx, NULL, _arg_1298); mph_gc_pop_roots(ctx, 1); _ret_1299; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileIntegerLiteral(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_IntegerLiteral* _arg_1300 = lit; mph_gc_push_root(ctx, (void**)&_arg_1300); MorphString* _ret_1301 = mph_codegen_compile_integer_literal(ctx, NULL, _arg_1300); mph_gc_pop_roots(ctx, 1); _ret_1301; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileFloatLiteral(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_FloatLiteral* _arg_1302 = lit; mph_gc_push_root(ctx, (void**)&_arg_1302); MorphString* _ret_1303 = mph_codegen_compile_float_literal(ctx, NULL, _arg_1302); mph_gc_pop_roots(ctx, 1); _ret_1303; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileCharLiteral(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_CharLiteral* _arg_1304 = lit; mph_gc_push_root(ctx, (void**)&_arg_1304); MorphString* _ret_1305 = mph_codegen_compile_char_literal(ctx, NULL, _arg_1304); mph_gc_pop_roots(ctx, 1); _ret_1305; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileStringLiteral(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_StringLiteral* _arg_1306 = lit; mph_gc_push_root(ctx, (void**)&_arg_1306); MorphString* _ret_1307 = mph_codegen_compile_string_literal(ctx, NULL, _arg_1306); mph_gc_pop_roots(ctx, 1); _ret_1307; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileBooleanLiteral(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_BooleanLiteral* _arg_1308 = lit; mph_gc_push_root(ctx, (void**)&_arg_1308); MorphString* _ret_1309 = mph_codegen_compile_boolean_literal(ctx, NULL, _arg_1308); mph_gc_pop_roots(ctx, 1); _ret_1309; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileNullLiteral(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_NullLiteral* _arg_1310 = lit; mph_gc_push_root(ctx, (void**)&_arg_1310); MorphString* _ret_1311 = mph_codegen_compile_null_literal(ctx, NULL, _arg_1310); mph_gc_pop_roots(ctx, 1); _ret_1311; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileIdentifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	return ({ mph_ast_Identifier* _arg_1312 = ident; mph_gc_push_root(ctx, (void**)&_arg_1312); MorphString* _ret_1313 = mph_codegen_compile_identifier(ctx, NULL, _arg_1312); mph_gc_pop_roots(ctx, 1); _ret_1313; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileInfix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&left_code);
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	return ({ MorphString* _arg_1314 = left_code; mph_gc_push_root(ctx, (void**)&_arg_1314); MorphString* _arg_1315 = operator; mph_gc_push_root(ctx, (void**)&_arg_1315); MorphString* _arg_1316 = right_code; mph_gc_push_root(ctx, (void**)&_arg_1316); MorphString* _ret_1317 = mph_codegen_compile_infix(ctx, NULL, _arg_1314, _arg_1315, _arg_1316); mph_gc_pop_roots(ctx, 3); _ret_1317; });
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_CompilePrefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	return ({ MorphString* _arg_1318 = operator; mph_gc_push_root(ctx, (void**)&_arg_1318); MorphString* _arg_1319 = right_code; mph_gc_push_root(ctx, (void**)&_arg_1319); MorphString* _ret_1320 = mph_codegen_compile_prefix(ctx, NULL, _arg_1318, _arg_1319); mph_gc_pop_roots(ctx, 2); _ret_1320; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_ResolveBuiltinName(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	return ({ MorphString* _arg_1321 = name; mph_gc_push_root(ctx, (void**)&_arg_1321); MorphString* _ret_1322 = mph_codegen_resolve_builtin_name(ctx, NULL, _arg_1321); mph_gc_pop_roots(ctx, 1); _ret_1322; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileBuiltinCall(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&args_code);
	return ({ MorphString* _arg_1323 = name; mph_gc_push_root(ctx, (void**)&_arg_1323); MorphString* _arg_1324 = args_code; mph_gc_push_root(ctx, (void**)&_arg_1324); MorphString* _ret_1325 = mph_codegen_compile_builtin_call(ctx, NULL, _arg_1323, _arg_1324); mph_gc_pop_roots(ctx, 2); _ret_1325; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_CompileVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1326 = name; mph_gc_push_root(ctx, (void**)&_arg_1326); MorphString* _arg_1327 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1327); MorphString* _ret_1328 = mph_codegen_compile_var_statement(ctx, NULL, _arg_1326, _arg_1327); mph_gc_pop_roots(ctx, 2); _ret_1328; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_CompileExpressionStatement(MorphContext* ctx, void* _env_void, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1329 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1329); MorphString* _ret_1330 = mph_codegen_compile_expression_statement(ctx, NULL, _arg_1329); mph_gc_pop_roots(ctx, 1); _ret_1330; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_CompileReturnStatement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1331 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1331); MorphString* _ret_1332 = mph_codegen_compile_return_statement(ctx, NULL, has_value, _arg_1331); mph_gc_pop_roots(ctx, 1); _ret_1332; });
	mph_gc_pop_roots(ctx, 1);
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_ast_NODE_PROGRAM = 0;
	mph_ast_NODE_VAR_STATEMENT = 1;
	mph_ast_NODE_FUNCTION_STATEMENT = 2;
	mph_ast_NODE_RETURN_STATEMENT = 3;
	mph_ast_NODE_EXPRESSION_STATEMENT = 4;
	mph_ast_NODE_BLOCK_STATEMENT = 5;
	mph_ast_NODE_IF_EXPRESSION = 6;
	mph_ast_NODE_IDENTIFIER = 7;
	mph_ast_NODE_INTEGER_LITERAL = 8;
	mph_ast_NODE_FLOAT_LITERAL = 9;
	mph_ast_NODE_STRING_LITERAL = 10;
	mph_ast_NODE_BOOLEAN_LITERAL = 11;
	mph_ast_NODE_ARRAY_LITERAL = 12;
	mph_ast_NODE_HASH_LITERAL = 13;
	mph_ast_NODE_FUNCTION_LITERAL = 14;
	mph_ast_NODE_PREFIX_EXPRESSION = 15;
	mph_ast_NODE_INFIX_EXPRESSION = 16;
	mph_ast_NODE_CALL_EXPRESSION = 17;
	mph_ast_NODE_INDEX_EXPRESSION = 18;
	mph_ast_NODE_MEMBER_EXPRESSION = 19;
	mph_ast_NODE_ASSIGNMENT_EXPRESSION = 20;
	mph_ast_NODE_SWITCH_STATEMENT = 21;
	mph_ast_NODE_CASE_CLAUSE = 22;
	mph_ast_NODE_WHILE_STATEMENT = 23;
	mph_ast_NODE_STRUCT_STATEMENT = 24;
	mph_ast_NODE_STRUCT_LITERAL = 25;
	mph_ast_NODE_IMPORT_STATEMENT = 26;
	mph_ast_NODE_INTERFACE_STATEMENT = 27;
	mph_ast_NODE_BREAK_STATEMENT = 28;
	mph_ast_NODE_CONTINUE_STATEMENT = 29;
	mph_ast_NODE_CHAR_LITERAL = 30;
	mph_ast_NODE_NULL_LITERAL = 31;
	mph_token_TOKEN_ILLEGAL = 0;
	mph_token_TOKEN_EOF = 1;
	mph_token_TOKEN_IDENT = 2;
	mph_token_TOKEN_INT = 3;
	mph_token_TOKEN_FLOAT = 4;
	mph_token_TOKEN_STRING = 5;
	mph_token_TOKEN_CHAR = 6;
	mph_token_TOKEN_ASSIGN = 7;
	mph_token_TOKEN_PLUS = 8;
	mph_token_TOKEN_MINUS = 9;
	mph_token_TOKEN_BANG = 10;
	mph_token_TOKEN_ASTERISK = 11;
	mph_token_TOKEN_SLASH = 12;
	mph_token_TOKEN_PERCENT = 13;
	mph_token_TOKEN_LT = 14;
	mph_token_TOKEN_GT = 15;
	mph_token_TOKEN_EQ = 16;
	mph_token_TOKEN_NOT_EQ = 17;
	mph_token_TOKEN_LE = 18;
	mph_token_TOKEN_GE = 19;
	mph_token_TOKEN_BIT_AND = 20;
	mph_token_TOKEN_BIT_OR = 21;
	mph_token_TOKEN_BIT_XOR = 22;
	mph_token_TOKEN_BIT_NOT = 23;
	mph_token_TOKEN_LSHIFT = 24;
	mph_token_TOKEN_RSHIFT = 25;
	mph_token_TOKEN_AND = 26;
	mph_token_TOKEN_OR = 27;
	mph_token_TOKEN_COMMA = 28;
	mph_token_TOKEN_SEMICOLON = 29;
	mph_token_TOKEN_COLON = 30;
	mph_token_TOKEN_LPAREN = 31;
	mph_token_TOKEN_RPAREN = 32;
	mph_token_TOKEN_LBRACE = 33;
	mph_token_TOKEN_RBRACE = 34;
	mph_token_TOKEN_LBRACKET = 35;
	mph_token_TOKEN_RBRACKET = 36;
	mph_token_TOKEN_FUNGSI = 37;
	mph_token_TOKEN_VAR = 38;
	mph_token_TOKEN_TETAPAN = 39;
	mph_token_TOKEN_BENAR = 40;
	mph_token_TOKEN_SALAH = 41;
	mph_token_TOKEN_JIKA = 42;
	mph_token_TOKEN_LAINNYA = 43;
	mph_token_TOKEN_KEMBALIKAN = 44;
	mph_token_TOKEN_STRUKTUR = 45;
	mph_token_TOKEN_ANTARMUKA = 46;
	mph_token_TOKEN_AMBIL = 47;
	mph_token_TOKEN_UNTUK = 48;
	mph_token_TOKEN_SELAMA = 49;
	mph_token_TOKEN_PUTUS = 50;
	mph_token_TOKEN_LANJUT = 51;
	mph_token_TOKEN_PILIH = 52;
	mph_token_TOKEN_KASUS = 53;
	mph_token_TOKEN_BAWAAN = 54;
	mph_token_TOKEN_AKHIR = 55;
	mph_token_TOKEN_ATAU_JIKA = 56;
	mph_token_TOKEN_DAN = 57;
	mph_token_TOKEN_ATAU = 58;
	mph_token_TOKEN_KOSONG = 59;
	mph_token_TOKEN_LUNCURKAN = 60;
	mph_token_TOKEN_SALURAN_BARU = 61;
	mph_token_TOKEN_KIRIM = 62;
	mph_token_TOKEN_TERIMA = 63;
	mph_token_TOKEN_DOT = 64;
	mph_token_TOKEN_ARROW = 65;
	mph_types_KIND_INT = 0;
	mph_types_KIND_FLOAT = 1;
	mph_types_KIND_STRING = 2;
	mph_types_KIND_BOOL = 3;
	mph_types_KIND_VOID = 4;
	mph_types_KIND_FUNCTION = 5;
	mph_types_KIND_STRUCT = 6;
	mph_types_KIND_INTERFACE = 7;
	mph_types_KIND_ARRAY = 8;
	mph_types_KIND_MAP = 9;
	mph_types_KIND_POINTER = 10;
	mph_types_KIND_MULTI = 11;
	mph_types_KIND_UNKNOWN = 12;
	mph_types_KIND_ERROR = 13;
	mph_types_KIND_NULL = 14;
	mph_types_KIND_USER_ERROR = 15;
	mph_types_KIND_MODULE = 16;
	mph_types_KIND_CHANNEL = 17;
}
