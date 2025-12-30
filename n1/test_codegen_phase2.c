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
#define MPH_TYPE_mph_ast_BreakStatement 26
#define MPH_TYPE_mph_ast_ContinueStatement 27
#define MPH_TYPE_mph_ast_ReturnStatement 4
#define MPH_TYPE_mph_ast_StringLiteral 11
#define MPH_TYPE_mph_ast_CaseClause 21
#define MPH_TYPE_mph_types_TypeResult 30
#define MPH_TYPE_mph_ast_BlockStatement 6
#define MPH_TYPE_mph_ast_CharLiteral 13
#define MPH_TYPE_mph_ast_NullLiteral 14
#define MPH_TYPE_mph_ast_InfixExpression 16
#define MPH_TYPE_mph_token_Token 28
#define MPH_TYPE_mph_codegen_Codegen 31
#define MPH_TYPE_mph_ast_WhileStatement 23
#define MPH_TYPE_mph_types_Type 29
#define MPH_TYPE_mph_ast_Program 7
#define MPH_TYPE_mph_ast_Node 1
#define MPH_TYPE_mph_ast_FunctionStatement 3
#define MPH_TYPE_mph_ast_IfExpression 17
#define MPH_TYPE_mph_ast_IndexExpression 19
#define MPH_TYPE_mph_ast_MemberExpression 20
#define MPH_TYPE_mph_ast_IntegerLiteral 9
#define MPH_TYPE_mph_ast_FloatLiteral 10
#define MPH_TYPE_mph_ast_StructStatement 24
#define MPH_TYPE_mph_ast_ImportStatement 25
#define MPH_TYPE_mph_ast_ExpressionStatement 5
#define MPH_TYPE_mph_ast_Identifier 8
#define MPH_TYPE_mph_ast_BooleanLiteral 12
#define MPH_TYPE_mph_ast_SwitchStatement 22
#define MPH_TYPE_mph_ast_VarStatement 2
#define MPH_TYPE_mph_ast_PrefixExpression 15
#define MPH_TYPE_mph_ast_CallExpression 18

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

typedef struct mph_codegen_Codegen mph_codegen_Codegen;
struct mph_codegen_Codegen {
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

MorphTypeInfo mph_ti_mph_types_Type = { "Type", sizeof(mph_types_Type), 1, (size_t[]){offsetof(mph_types_Type, name)} };
MorphTypeInfo mph_ti_mph_types_TypeResult = { "TypeResult", sizeof(mph_types_TypeResult), 2, (size_t[]){offsetof(mph_types_TypeResult, result), offsetof(mph_types_TypeResult, error_msg)} };
MorphTypeInfo mph_ti_mph_codegen_Codegen = { "Codegen", sizeof(mph_codegen_Codegen), 8, (size_t[]){offsetof(mph_codegen_Codegen, output), offsetof(mph_codegen_Codegen, type_defs), offsetof(mph_codegen_Codegen, global_defs), offsetof(mph_codegen_Codegen, prototypes), offsetof(mph_codegen_Codegen, func_defs), offsetof(mph_codegen_Codegen, entry_body), offsetof(mph_codegen_Codegen, pass_log), offsetof(mph_codegen_Codegen, current_prefix)} };
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

// Global Variables
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

// Function Prototypes
void mph_test_identifier(MorphContext* ctx, void* _env_void);
void mph_test_infix(MorphContext* ctx, void* _env_void);
void mph_test_var_statement(MorphContext* ctx, void* _env_void);
void mph_test_expression_statement(MorphContext* ctx, void* _env_void);
void mph_test_return_statement(MorphContext* ctx, void* _env_void);
void mph_test_prefix_expression(MorphContext* ctx, void* _env_void);
void mph_test_builtin_call(MorphContext* ctx, void* _env_void);
void mph_test_type_mapping(MorphContext* ctx, void* _env_void);
void mph_test_multipass_log(MorphContext* ctx, void* _env_void);
void mph_main(MorphContext* ctx, void* _env_void);
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
mph_codegen_Codegen* mph_codegen_new_codegen(MorphContext* ctx, void* _env_void);
MorphString* mph_codegen_codegen_compile(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_codegen_record_pass(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, MorphString* name);
void mph_codegen_codegen_pass_collect_globals(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_codegen_pass_analyze_captures(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_codegen_pass_compile_struct_types(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_codegen_pass_compile_struct_rtti(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog);
void mph_codegen_codegen_pass_compile_module(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog, MorphString* prefix);
void mph_codegen_codegen_compile_program(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog, MorphString* prefix);
MorphString* mph_codegen_codegen_map_type_to_c(MorphContext* ctx, void* _env_void, mph_types_Type* t);
MorphString* mph_codegen_codegen_next_temp(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, MorphString* prefix);
MorphString* mph_codegen_codegen_append(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text);
MorphString* mph_codegen_codegen_append_line(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text);
MorphString* mph_codegen_codegen_append_indent(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text, mph_int level);
MorphString* mph_codegen_codegen_compile_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit);
MorphString* mph_codegen_codegen_compile_float_literal(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit);
MorphString* mph_codegen_codegen_compile_char_literal(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit);
MorphString* mph_codegen_codegen_compile_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit);
MorphString* mph_codegen_codegen_compile_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit);
MorphString* mph_codegen_codegen_compile_null_literal(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit);
MorphString* mph_codegen_codegen_compile_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident);
MorphString* mph_codegen_codegen_compile_infix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_codegen_compile_prefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_codegen_resolve_builtin_name(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_codegen_codegen_compile_builtin_call(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code);
MorphString* mph_codegen_codegen_var_type_from_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str);
MorphString* mph_codegen_codegen_default_value_for_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str);
MorphString* mph_codegen_codegen_var_type_from_token(MorphContext* ctx, void* _env_void, mph_int token_type);
MorphString* mph_codegen_codegen_value_code_from_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal);
MorphString* mph_codegen_codegen_compile_var_statement_typed(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code, MorphString* c_type);
MorphString* mph_codegen_codegen_var_type_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_codegen_var_value_code_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_codegen_compile_global_var_declaration(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_codegen_compile_global_var_initialization(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_codegen_compile_var_statement_from_stmt(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt);
MorphString* mph_codegen_codegen_compile_var_statement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code);
MorphString* mph_codegen_codegen_compile_expression_statement(MorphContext* ctx, void* _env_void, MorphString* value_code);
MorphString* mph_codegen_codegen_compile_return_statement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code);
mph_codegen_Codegen* mph_codegen_NewCodegen(MorphContext* ctx, void* _env_void);
MorphString* mph_codegen_Compile(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog);
MorphString* mph_codegen_MapTypeToC(MorphContext* ctx, void* _env_void, mph_types_Type* t);
MorphString* mph_codegen_CompileIntegerLiteral(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit);
MorphString* mph_codegen_CompileFloatLiteral(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit);
MorphString* mph_codegen_CompileCharLiteral(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit);
MorphString* mph_codegen_CompileStringLiteral(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit);
MorphString* mph_codegen_CompileBooleanLiteral(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit);
MorphString* mph_codegen_CompileNullLiteral(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit);
MorphString* mph_codegen_CompileIdentifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident);
MorphString* mph_codegen_CompileInfix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_CompilePrefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_ResolveBuiltinName(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_codegen_CompileBuiltinCall(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code);
MorphString* mph_codegen_CompileVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code);
MorphString* mph_codegen_CompileExpressionStatement(MorphContext* ctx, void* _env_void, MorphString* value_code);
MorphString* mph_codegen_CompileReturnStatement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code);

// Function Definitions
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
	return ({ mph_types_Type* _t = (mph_types_Type*)mph_alloc(ctx, sizeof(mph_types_Type), &mph_ti_mph_types_Type); mph_gc_push_root(ctx, (void**)&_t); _t->name = n; _t->kind = k; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_int_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_1 = mph_string_new(ctx, "int"); mph_gc_push_root(ctx, (void**)&_arg_1); mph_types_Type* _ret_2 = mph_types_make_type(ctx, NULL, mph_types_KIND_INT, _arg_1); mph_gc_pop_roots(ctx, 1); _ret_2; });
}

mph_types_Type* mph_types_float_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_3 = mph_string_new(ctx, "float"); mph_gc_push_root(ctx, (void**)&_arg_3); mph_types_Type* _ret_4 = mph_types_make_type(ctx, NULL, mph_types_KIND_FLOAT, _arg_3); mph_gc_pop_roots(ctx, 1); _ret_4; });
}

mph_types_Type* mph_types_string_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_5 = mph_string_new(ctx, "string"); mph_gc_push_root(ctx, (void**)&_arg_5); mph_types_Type* _ret_6 = mph_types_make_type(ctx, NULL, mph_types_KIND_STRING, _arg_5); mph_gc_pop_roots(ctx, 1); _ret_6; });
}

mph_types_Type* mph_types_bool_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_7 = mph_string_new(ctx, "bool"); mph_gc_push_root(ctx, (void**)&_arg_7); mph_types_Type* _ret_8 = mph_types_make_type(ctx, NULL, mph_types_KIND_BOOL, _arg_7); mph_gc_pop_roots(ctx, 1); _ret_8; });
}

mph_types_Type* mph_types_void_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_9 = mph_string_new(ctx, "void"); mph_gc_push_root(ctx, (void**)&_arg_9); mph_types_Type* _ret_10 = mph_types_make_type(ctx, NULL, mph_types_KIND_VOID, _arg_9); mph_gc_pop_roots(ctx, 1); _ret_10; });
}

mph_types_Type* mph_types_null_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_11 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_11); mph_types_Type* _ret_12 = mph_types_make_type(ctx, NULL, mph_types_KIND_NULL, _arg_11); mph_gc_pop_roots(ctx, 1); _ret_12; });
}

mph_types_Type* mph_types_unknown_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_13 = mph_string_new(ctx, "unknown"); mph_gc_push_root(ctx, (void**)&_arg_13); mph_types_Type* _ret_14 = mph_types_make_type(ctx, NULL, mph_types_KIND_UNKNOWN, _arg_13); mph_gc_pop_roots(ctx, 1); _ret_14; });
}

mph_types_Type* mph_types_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_15 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_15); mph_types_Type* _ret_16 = mph_types_make_type(ctx, NULL, mph_types_KIND_ERROR, _arg_15); mph_gc_pop_roots(ctx, 1); _ret_16; });
}

mph_types_Type* mph_types_user_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_17 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_17); mph_types_Type* _ret_18 = mph_types_make_type(ctx, NULL, mph_types_KIND_USER_ERROR, _arg_17); mph_gc_pop_roots(ctx, 1); _ret_18; });
}

mph_types_Type* mph_types_channel_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_19 = mph_string_new(ctx, "channel"); mph_gc_push_root(ctx, (void**)&_arg_19); mph_types_Type* _ret_20 = mph_types_make_type(ctx, NULL, mph_types_KIND_CHANNEL, _arg_19); mph_gc_pop_roots(ctx, 1); _ret_20; });
}

mph_types_Type* mph_types_array_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_21 = mph_string_new(ctx, "array"); mph_gc_push_root(ctx, (void**)&_arg_21); mph_types_Type* _ret_22 = mph_types_make_type(ctx, NULL, mph_types_KIND_ARRAY, _arg_21); mph_gc_pop_roots(ctx, 1); _ret_22; });
}

mph_types_Type* mph_types_map_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_23 = mph_string_new(ctx, "map"); mph_gc_push_root(ctx, (void**)&_arg_23); mph_types_Type* _ret_24 = mph_types_make_type(ctx, NULL, mph_types_KIND_MAP, _arg_23); mph_gc_pop_roots(ctx, 1); _ret_24; });
}

mph_types_Type* mph_types_struct_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_25 = n; mph_gc_push_root(ctx, (void**)&_arg_25); mph_types_Type* _ret_26 = mph_types_make_type(ctx, NULL, mph_types_KIND_STRUCT, _arg_25); mph_gc_pop_roots(ctx, 1); _ret_26; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_interface_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_27 = n; mph_gc_push_root(ctx, (void**)&_arg_27); mph_types_Type* _ret_28 = mph_types_make_type(ctx, NULL, mph_types_KIND_INTERFACE, _arg_27); mph_gc_pop_roots(ctx, 1); _ret_28; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_function_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_29 = mph_string_new(ctx, "function"); mph_gc_push_root(ctx, (void**)&_arg_29); mph_types_Type* _ret_30 = mph_types_make_type(ctx, NULL, mph_types_KIND_FUNCTION, _arg_29); mph_gc_pop_roots(ctx, 1); _ret_30; });
}

mph_types_Type* mph_types_pointer_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_31 = mph_string_new(ctx, "pointer"); mph_gc_push_root(ctx, (void**)&_arg_31); mph_types_Type* _ret_32 = mph_types_make_type(ctx, NULL, mph_types_KIND_POINTER, _arg_31); mph_gc_pop_roots(ctx, 1); _ret_32; });
}

mph_types_Type* mph_types_multi_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_33 = mph_string_new(ctx, "multi"); mph_gc_push_root(ctx, (void**)&_arg_33); mph_types_Type* _ret_34 = mph_types_make_type(ctx, NULL, mph_types_KIND_MULTI, _arg_33); mph_gc_pop_roots(ctx, 1); _ret_34; });
}

mph_types_Type* mph_types_module_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_35 = n; mph_gc_push_root(ctx, (void**)&_arg_35); mph_types_Type* _ret_36 = mph_types_make_type(ctx, NULL, mph_types_KIND_MODULE, _arg_35); mph_gc_pop_roots(ctx, 1); _ret_36; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_types_type_equals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return (({ mph_types_Type* _obj_37 = t1; mph_gc_push_root(ctx, (void**)&_obj_37); mph_int _ret_38 = _obj_37->kind; mph_gc_pop_roots(ctx, 1); _ret_38; }) == ({ mph_types_Type* _obj_39 = t2; mph_gc_push_root(ctx, (void**)&_obj_39); mph_int _ret_40 = _obj_39->kind; mph_gc_pop_roots(ctx, 1); _ret_40; }));
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_type_assignable_to(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	if ((({ mph_types_Type* _obj_41 = source; mph_gc_push_root(ctx, (void**)&_obj_41); mph_int _ret_42 = _obj_41->kind; mph_gc_pop_roots(ctx, 1); _ret_42; }) == mph_types_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_43 = target; mph_gc_push_root(ctx, (void**)&_obj_43); mph_int _ret_44 = _obj_43->kind; mph_gc_pop_roots(ctx, 1); _ret_44; }) == mph_types_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_45 = source; mph_gc_push_root(ctx, (void**)&_obj_45); mph_int _ret_46 = _obj_45->kind; mph_gc_pop_roots(ctx, 1); _ret_46; }) == mph_types_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_47 = target; mph_gc_push_root(ctx, (void**)&_obj_47); mph_int _ret_48 = _obj_47->kind; mph_gc_pop_roots(ctx, 1); _ret_48; }) == mph_types_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_49 = source; mph_gc_push_root(ctx, (void**)&_obj_49); mph_int _ret_50 = _obj_49->kind; mph_gc_pop_roots(ctx, 1); _ret_50; }) == mph_types_KIND_NULL)) {
{
	if ((({ mph_types_Type* _obj_51 = target; mph_gc_push_root(ctx, (void**)&_obj_51); mph_int _ret_52 = _obj_51->kind; mph_gc_pop_roots(ctx, 1); _ret_52; }) == mph_types_KIND_ARRAY)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_53 = target; mph_gc_push_root(ctx, (void**)&_obj_53); mph_int _ret_54 = _obj_53->kind; mph_gc_pop_roots(ctx, 1); _ret_54; }) == mph_types_KIND_MAP)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_55 = target; mph_gc_push_root(ctx, (void**)&_obj_55); mph_int _ret_56 = _obj_55->kind; mph_gc_pop_roots(ctx, 1); _ret_56; }) == mph_types_KIND_POINTER)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_57 = target; mph_gc_push_root(ctx, (void**)&_obj_57); mph_int _ret_58 = _obj_57->kind; mph_gc_pop_roots(ctx, 1); _ret_58; }) == mph_types_KIND_INTERFACE)) {
{
	return 1;
}
	}
	return 0;
}
	}
	return ({ mph_types_Type* _arg_59 = source; mph_gc_push_root(ctx, (void**)&_arg_59); mph_types_Type* _arg_60 = target; mph_gc_push_root(ctx, (void**)&_arg_60); mph_bool _ret_61 = mph_types_type_equals(ctx, NULL, _arg_59, _arg_60); mph_gc_pop_roots(ctx, 2); _ret_61; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_type_is_comparable(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	if ((({ mph_types_Type* _obj_62 = t; mph_gc_push_root(ctx, (void**)&_obj_62); mph_int _ret_63 = _obj_62->kind; mph_gc_pop_roots(ctx, 1); _ret_63; }) == mph_types_KIND_INT)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_64 = t; mph_gc_push_root(ctx, (void**)&_obj_64); mph_int _ret_65 = _obj_64->kind; mph_gc_pop_roots(ctx, 1); _ret_65; }) == mph_types_KIND_FLOAT)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_66 = t; mph_gc_push_root(ctx, (void**)&_obj_66); mph_int _ret_67 = _obj_66->kind; mph_gc_pop_roots(ctx, 1); _ret_67; }) == mph_types_KIND_STRING)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_68 = t; mph_gc_push_root(ctx, (void**)&_obj_68); mph_int _ret_69 = _obj_68->kind; mph_gc_pop_roots(ctx, 1); _ret_69; }) == mph_types_KIND_BOOL)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_70 = t; mph_gc_push_root(ctx, (void**)&_obj_70); mph_int _ret_71 = _obj_70->kind; mph_gc_pop_roots(ctx, 1); _ret_71; }) == mph_types_KIND_NULL)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_72 = t; mph_gc_push_root(ctx, (void**)&_obj_72); mph_int _ret_73 = _obj_72->kind; mph_gc_pop_roots(ctx, 1); _ret_73; }) == mph_types_KIND_USER_ERROR)) {
{
	return 1;
}
	}
	return 0;
	mph_gc_pop_roots(ctx, 1);
}

mph_types_TypeResult* mph_types_make_type_result(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_types_TypeResult* _t = (mph_types_TypeResult*)mph_alloc(ctx, sizeof(mph_types_TypeResult), &mph_ti_mph_types_TypeResult); mph_gc_push_root(ctx, (void**)&_t); _t->result = t; _t->error_msg = mph_string_new(ctx, "ok"); _t->has_error = 0; mph_gc_pop_roots(ctx, 1); _t; });
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
	if ((({ mph_types_Type* _obj_74 = left; mph_gc_push_root(ctx, (void**)&_obj_74); mph_int _ret_75 = _obj_74->kind; mph_gc_pop_roots(ctx, 1); _ret_75; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_76 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_76); mph_types_TypeResult* _ret_77 = mph_types_make_type_result(ctx, NULL, _arg_76); mph_gc_pop_roots(ctx, 1); _ret_77; });
}
	}
	if ((({ mph_types_Type* _obj_78 = right; mph_gc_push_root(ctx, (void**)&_obj_78); mph_int _ret_79 = _obj_78->kind; mph_gc_pop_roots(ctx, 1); _ret_79; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_80 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_80); mph_types_TypeResult* _ret_81 = mph_types_make_type_result(ctx, NULL, _arg_80); mph_gc_pop_roots(ctx, 1); _ret_81; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "+"))) {
{
	if ((({ mph_types_Type* _obj_82 = left; mph_gc_push_root(ctx, (void**)&_obj_82); mph_int _ret_83 = _obj_82->kind; mph_gc_pop_roots(ctx, 1); _ret_83; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_84 = right; mph_gc_push_root(ctx, (void**)&_obj_84); mph_int _ret_85 = _obj_84->kind; mph_gc_pop_roots(ctx, 1); _ret_85; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_86 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_86); mph_types_TypeResult* _ret_87 = mph_types_make_type_result(ctx, NULL, _arg_86); mph_gc_pop_roots(ctx, 1); _ret_87; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_88 = left; mph_gc_push_root(ctx, (void**)&_obj_88); mph_int _ret_89 = _obj_88->kind; mph_gc_pop_roots(ctx, 1); _ret_89; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_90 = right; mph_gc_push_root(ctx, (void**)&_obj_90); mph_int _ret_91 = _obj_90->kind; mph_gc_pop_roots(ctx, 1); _ret_91; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_92 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_92); mph_types_TypeResult* _ret_93 = mph_types_make_type_result(ctx, NULL, _arg_92); mph_gc_pop_roots(ctx, 1); _ret_93; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_94 = left; mph_gc_push_root(ctx, (void**)&_obj_94); mph_int _ret_95 = _obj_94->kind; mph_gc_pop_roots(ctx, 1); _ret_95; }) == mph_types_KIND_STRING)) {
{
	if ((({ mph_types_Type* _obj_96 = right; mph_gc_push_root(ctx, (void**)&_obj_96); mph_int _ret_97 = _obj_96->kind; mph_gc_pop_roots(ctx, 1); _ret_97; }) == mph_types_KIND_STRING)) {
{
	return ({ mph_types_Type* _arg_98 = mph_types_string_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_98); mph_types_TypeResult* _ret_99 = mph_types_make_type_result(ctx, NULL, _arg_98); mph_gc_pop_roots(ctx, 1); _ret_99; });
}
	}
}
	}
	return ({ MorphString* _arg_100 = mph_string_new(ctx, "+ tidak didukung untuk tipe ini"); mph_gc_push_root(ctx, (void**)&_arg_100); mph_types_TypeResult* _ret_101 = mph_types_make_type_error(ctx, NULL, _arg_100); mph_gc_pop_roots(ctx, 1); _ret_101; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_types_Type* _obj_102 = left; mph_gc_push_root(ctx, (void**)&_obj_102); mph_int _ret_103 = _obj_102->kind; mph_gc_pop_roots(ctx, 1); _ret_103; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_104 = right; mph_gc_push_root(ctx, (void**)&_obj_104); mph_int _ret_105 = _obj_104->kind; mph_gc_pop_roots(ctx, 1); _ret_105; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_106 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_106); mph_types_TypeResult* _ret_107 = mph_types_make_type_result(ctx, NULL, _arg_106); mph_gc_pop_roots(ctx, 1); _ret_107; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_108 = left; mph_gc_push_root(ctx, (void**)&_obj_108); mph_int _ret_109 = _obj_108->kind; mph_gc_pop_roots(ctx, 1); _ret_109; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_110 = right; mph_gc_push_root(ctx, (void**)&_obj_110); mph_int _ret_111 = _obj_110->kind; mph_gc_pop_roots(ctx, 1); _ret_111; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_112 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_112); mph_types_TypeResult* _ret_113 = mph_types_make_type_result(ctx, NULL, _arg_112); mph_gc_pop_roots(ctx, 1); _ret_113; });
}
	}
}
	}
	return ({ MorphString* _arg_114 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_114); mph_types_TypeResult* _ret_115 = mph_types_make_type_error(ctx, NULL, _arg_114); mph_gc_pop_roots(ctx, 1); _ret_115; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "*"))) {
{
	if ((({ mph_types_Type* _obj_116 = left; mph_gc_push_root(ctx, (void**)&_obj_116); mph_int _ret_117 = _obj_116->kind; mph_gc_pop_roots(ctx, 1); _ret_117; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_118 = right; mph_gc_push_root(ctx, (void**)&_obj_118); mph_int _ret_119 = _obj_118->kind; mph_gc_pop_roots(ctx, 1); _ret_119; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_120 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_120); mph_types_TypeResult* _ret_121 = mph_types_make_type_result(ctx, NULL, _arg_120); mph_gc_pop_roots(ctx, 1); _ret_121; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_122 = left; mph_gc_push_root(ctx, (void**)&_obj_122); mph_int _ret_123 = _obj_122->kind; mph_gc_pop_roots(ctx, 1); _ret_123; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_124 = right; mph_gc_push_root(ctx, (void**)&_obj_124); mph_int _ret_125 = _obj_124->kind; mph_gc_pop_roots(ctx, 1); _ret_125; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_126 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_126); mph_types_TypeResult* _ret_127 = mph_types_make_type_result(ctx, NULL, _arg_126); mph_gc_pop_roots(ctx, 1); _ret_127; });
}
	}
}
	}
	return ({ MorphString* _arg_128 = mph_string_new(ctx, "* memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_128); mph_types_TypeResult* _ret_129 = mph_types_make_type_error(ctx, NULL, _arg_128); mph_gc_pop_roots(ctx, 1); _ret_129; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "/"))) {
{
	if ((({ mph_types_Type* _obj_130 = left; mph_gc_push_root(ctx, (void**)&_obj_130); mph_int _ret_131 = _obj_130->kind; mph_gc_pop_roots(ctx, 1); _ret_131; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_132 = right; mph_gc_push_root(ctx, (void**)&_obj_132); mph_int _ret_133 = _obj_132->kind; mph_gc_pop_roots(ctx, 1); _ret_133; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_134 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_134); mph_types_TypeResult* _ret_135 = mph_types_make_type_result(ctx, NULL, _arg_134); mph_gc_pop_roots(ctx, 1); _ret_135; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_136 = left; mph_gc_push_root(ctx, (void**)&_obj_136); mph_int _ret_137 = _obj_136->kind; mph_gc_pop_roots(ctx, 1); _ret_137; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_138 = right; mph_gc_push_root(ctx, (void**)&_obj_138); mph_int _ret_139 = _obj_138->kind; mph_gc_pop_roots(ctx, 1); _ret_139; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_140 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_140); mph_types_TypeResult* _ret_141 = mph_types_make_type_result(ctx, NULL, _arg_140); mph_gc_pop_roots(ctx, 1); _ret_141; });
}
	}
}
	}
	return ({ MorphString* _arg_142 = mph_string_new(ctx, "/ memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_142); mph_types_TypeResult* _ret_143 = mph_types_make_type_error(ctx, NULL, _arg_142); mph_gc_pop_roots(ctx, 1); _ret_143; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "%"))) {
{
	if ((({ mph_types_Type* _obj_144 = left; mph_gc_push_root(ctx, (void**)&_obj_144); mph_int _ret_145 = _obj_144->kind; mph_gc_pop_roots(ctx, 1); _ret_145; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_146 = right; mph_gc_push_root(ctx, (void**)&_obj_146); mph_int _ret_147 = _obj_146->kind; mph_gc_pop_roots(ctx, 1); _ret_147; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_148 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_148); mph_types_TypeResult* _ret_149 = mph_types_make_type_result(ctx, NULL, _arg_148); mph_gc_pop_roots(ctx, 1); _ret_149; });
}
	}
}
	}
	return ({ MorphString* _arg_150 = mph_string_new(ctx, "% memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_150); mph_types_TypeResult* _ret_151 = mph_types_make_type_error(ctx, NULL, _arg_150); mph_gc_pop_roots(ctx, 1); _ret_151; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "=="))) {
{
	if (({ mph_types_Type* _arg_152 = left; mph_gc_push_root(ctx, (void**)&_arg_152); mph_types_Type* _arg_153 = right; mph_gc_push_root(ctx, (void**)&_arg_153); mph_bool _ret_154 = mph_types_type_equals(ctx, NULL, _arg_152, _arg_153); mph_gc_pop_roots(ctx, 2); _ret_154; })) {
{
	return ({ mph_types_Type* _arg_155 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_155); mph_types_TypeResult* _ret_156 = mph_types_make_type_result(ctx, NULL, _arg_155); mph_gc_pop_roots(ctx, 1); _ret_156; });
}
	}
	if ((({ mph_types_Type* _obj_157 = left; mph_gc_push_root(ctx, (void**)&_obj_157); mph_int _ret_158 = _obj_157->kind; mph_gc_pop_roots(ctx, 1); _ret_158; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_159 = left; mph_gc_push_root(ctx, (void**)&_arg_159); mph_types_Type* _arg_160 = right; mph_gc_push_root(ctx, (void**)&_arg_160); mph_bool _ret_161 = mph_types_type_assignable_to(ctx, NULL, _arg_159, _arg_160); mph_gc_pop_roots(ctx, 2); _ret_161; })) {
{
	return ({ mph_types_Type* _arg_162 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_162); mph_types_TypeResult* _ret_163 = mph_types_make_type_result(ctx, NULL, _arg_162); mph_gc_pop_roots(ctx, 1); _ret_163; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_164 = right; mph_gc_push_root(ctx, (void**)&_obj_164); mph_int _ret_165 = _obj_164->kind; mph_gc_pop_roots(ctx, 1); _ret_165; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_166 = right; mph_gc_push_root(ctx, (void**)&_arg_166); mph_types_Type* _arg_167 = left; mph_gc_push_root(ctx, (void**)&_arg_167); mph_bool _ret_168 = mph_types_type_assignable_to(ctx, NULL, _arg_166, _arg_167); mph_gc_pop_roots(ctx, 2); _ret_168; })) {
{
	return ({ mph_types_Type* _arg_169 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_169); mph_types_TypeResult* _ret_170 = mph_types_make_type_result(ctx, NULL, _arg_169); mph_gc_pop_roots(ctx, 1); _ret_170; });
}
	}
}
	}
	return ({ MorphString* _arg_171 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_171); mph_types_TypeResult* _ret_172 = mph_types_make_type_error(ctx, NULL, _arg_171); mph_gc_pop_roots(ctx, 1); _ret_172; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!="))) {
{
	if (({ mph_types_Type* _arg_173 = left; mph_gc_push_root(ctx, (void**)&_arg_173); mph_types_Type* _arg_174 = right; mph_gc_push_root(ctx, (void**)&_arg_174); mph_bool _ret_175 = mph_types_type_equals(ctx, NULL, _arg_173, _arg_174); mph_gc_pop_roots(ctx, 2); _ret_175; })) {
{
	return ({ mph_types_Type* _arg_176 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_176); mph_types_TypeResult* _ret_177 = mph_types_make_type_result(ctx, NULL, _arg_176); mph_gc_pop_roots(ctx, 1); _ret_177; });
}
	}
	if ((({ mph_types_Type* _obj_178 = left; mph_gc_push_root(ctx, (void**)&_obj_178); mph_int _ret_179 = _obj_178->kind; mph_gc_pop_roots(ctx, 1); _ret_179; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_180 = left; mph_gc_push_root(ctx, (void**)&_arg_180); mph_types_Type* _arg_181 = right; mph_gc_push_root(ctx, (void**)&_arg_181); mph_bool _ret_182 = mph_types_type_assignable_to(ctx, NULL, _arg_180, _arg_181); mph_gc_pop_roots(ctx, 2); _ret_182; })) {
{
	return ({ mph_types_Type* _arg_183 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_183); mph_types_TypeResult* _ret_184 = mph_types_make_type_result(ctx, NULL, _arg_183); mph_gc_pop_roots(ctx, 1); _ret_184; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_185 = right; mph_gc_push_root(ctx, (void**)&_obj_185); mph_int _ret_186 = _obj_185->kind; mph_gc_pop_roots(ctx, 1); _ret_186; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_187 = right; mph_gc_push_root(ctx, (void**)&_arg_187); mph_types_Type* _arg_188 = left; mph_gc_push_root(ctx, (void**)&_arg_188); mph_bool _ret_189 = mph_types_type_assignable_to(ctx, NULL, _arg_187, _arg_188); mph_gc_pop_roots(ctx, 2); _ret_189; })) {
{
	return ({ mph_types_Type* _arg_190 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_190); mph_types_TypeResult* _ret_191 = mph_types_make_type_result(ctx, NULL, _arg_190); mph_gc_pop_roots(ctx, 1); _ret_191; });
}
	}
}
	}
	return ({ MorphString* _arg_192 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_192); mph_types_TypeResult* _ret_193 = mph_types_make_type_error(ctx, NULL, _arg_192); mph_gc_pop_roots(ctx, 1); _ret_193; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&&"))) {
{
	if ((({ mph_types_Type* _obj_194 = left; mph_gc_push_root(ctx, (void**)&_obj_194); mph_int _ret_195 = _obj_194->kind; mph_gc_pop_roots(ctx, 1); _ret_195; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_196 = right; mph_gc_push_root(ctx, (void**)&_obj_196); mph_int _ret_197 = _obj_196->kind; mph_gc_pop_roots(ctx, 1); _ret_197; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_198 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_198); mph_types_TypeResult* _ret_199 = mph_types_make_type_result(ctx, NULL, _arg_198); mph_gc_pop_roots(ctx, 1); _ret_199; });
}
	}
}
	}
	return ({ MorphString* _arg_200 = mph_string_new(ctx, "&& memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_200); mph_types_TypeResult* _ret_201 = mph_types_make_type_error(ctx, NULL, _arg_200); mph_gc_pop_roots(ctx, 1); _ret_201; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "||"))) {
{
	if ((({ mph_types_Type* _obj_202 = left; mph_gc_push_root(ctx, (void**)&_obj_202); mph_int _ret_203 = _obj_202->kind; mph_gc_pop_roots(ctx, 1); _ret_203; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_204 = right; mph_gc_push_root(ctx, (void**)&_obj_204); mph_int _ret_205 = _obj_204->kind; mph_gc_pop_roots(ctx, 1); _ret_205; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_206 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_206); mph_types_TypeResult* _ret_207 = mph_types_make_type_result(ctx, NULL, _arg_206); mph_gc_pop_roots(ctx, 1); _ret_207; });
}
	}
}
	}
	return ({ MorphString* _arg_208 = mph_string_new(ctx, "|| memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_208); mph_types_TypeResult* _ret_209 = mph_types_make_type_error(ctx, NULL, _arg_208); mph_gc_pop_roots(ctx, 1); _ret_209; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "dan"))) {
{
	if ((({ mph_types_Type* _obj_210 = left; mph_gc_push_root(ctx, (void**)&_obj_210); mph_int _ret_211 = _obj_210->kind; mph_gc_pop_roots(ctx, 1); _ret_211; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_212 = right; mph_gc_push_root(ctx, (void**)&_obj_212); mph_int _ret_213 = _obj_212->kind; mph_gc_pop_roots(ctx, 1); _ret_213; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_214 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_214); mph_types_TypeResult* _ret_215 = mph_types_make_type_result(ctx, NULL, _arg_214); mph_gc_pop_roots(ctx, 1); _ret_215; });
}
	}
}
	}
	return ({ MorphString* _arg_216 = mph_string_new(ctx, "dan memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_216); mph_types_TypeResult* _ret_217 = mph_types_make_type_error(ctx, NULL, _arg_216); mph_gc_pop_roots(ctx, 1); _ret_217; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "atau"))) {
{
	if ((({ mph_types_Type* _obj_218 = left; mph_gc_push_root(ctx, (void**)&_obj_218); mph_int _ret_219 = _obj_218->kind; mph_gc_pop_roots(ctx, 1); _ret_219; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_220 = right; mph_gc_push_root(ctx, (void**)&_obj_220); mph_int _ret_221 = _obj_220->kind; mph_gc_pop_roots(ctx, 1); _ret_221; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_222 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_222); mph_types_TypeResult* _ret_223 = mph_types_make_type_result(ctx, NULL, _arg_222); mph_gc_pop_roots(ctx, 1); _ret_223; });
}
	}
}
	}
	return ({ MorphString* _arg_224 = mph_string_new(ctx, "atau memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_224); mph_types_TypeResult* _ret_225 = mph_types_make_type_error(ctx, NULL, _arg_224); mph_gc_pop_roots(ctx, 1); _ret_225; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<"))) {
{
	if ((({ mph_types_Type* _obj_226 = left; mph_gc_push_root(ctx, (void**)&_obj_226); mph_int _ret_227 = _obj_226->kind; mph_gc_pop_roots(ctx, 1); _ret_227; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_228 = right; mph_gc_push_root(ctx, (void**)&_obj_228); mph_int _ret_229 = _obj_228->kind; mph_gc_pop_roots(ctx, 1); _ret_229; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_230 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_230); mph_types_TypeResult* _ret_231 = mph_types_make_type_result(ctx, NULL, _arg_230); mph_gc_pop_roots(ctx, 1); _ret_231; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_232 = left; mph_gc_push_root(ctx, (void**)&_obj_232); mph_int _ret_233 = _obj_232->kind; mph_gc_pop_roots(ctx, 1); _ret_233; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_234 = right; mph_gc_push_root(ctx, (void**)&_obj_234); mph_int _ret_235 = _obj_234->kind; mph_gc_pop_roots(ctx, 1); _ret_235; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_236 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_236); mph_types_TypeResult* _ret_237 = mph_types_make_type_result(ctx, NULL, _arg_236); mph_gc_pop_roots(ctx, 1); _ret_237; });
}
	}
}
	}
	return ({ MorphString* _arg_238 = mph_string_new(ctx, "< memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_238); mph_types_TypeResult* _ret_239 = mph_types_make_type_error(ctx, NULL, _arg_238); mph_gc_pop_roots(ctx, 1); _ret_239; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">"))) {
{
	if ((({ mph_types_Type* _obj_240 = left; mph_gc_push_root(ctx, (void**)&_obj_240); mph_int _ret_241 = _obj_240->kind; mph_gc_pop_roots(ctx, 1); _ret_241; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_242 = right; mph_gc_push_root(ctx, (void**)&_obj_242); mph_int _ret_243 = _obj_242->kind; mph_gc_pop_roots(ctx, 1); _ret_243; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_244 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_244); mph_types_TypeResult* _ret_245 = mph_types_make_type_result(ctx, NULL, _arg_244); mph_gc_pop_roots(ctx, 1); _ret_245; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_246 = left; mph_gc_push_root(ctx, (void**)&_obj_246); mph_int _ret_247 = _obj_246->kind; mph_gc_pop_roots(ctx, 1); _ret_247; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_248 = right; mph_gc_push_root(ctx, (void**)&_obj_248); mph_int _ret_249 = _obj_248->kind; mph_gc_pop_roots(ctx, 1); _ret_249; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_250 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_250); mph_types_TypeResult* _ret_251 = mph_types_make_type_result(ctx, NULL, _arg_250); mph_gc_pop_roots(ctx, 1); _ret_251; });
}
	}
}
	}
	return ({ MorphString* _arg_252 = mph_string_new(ctx, "> memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_252); mph_types_TypeResult* _ret_253 = mph_types_make_type_error(ctx, NULL, _arg_252); mph_gc_pop_roots(ctx, 1); _ret_253; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<="))) {
{
	if ((({ mph_types_Type* _obj_254 = left; mph_gc_push_root(ctx, (void**)&_obj_254); mph_int _ret_255 = _obj_254->kind; mph_gc_pop_roots(ctx, 1); _ret_255; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_256 = right; mph_gc_push_root(ctx, (void**)&_obj_256); mph_int _ret_257 = _obj_256->kind; mph_gc_pop_roots(ctx, 1); _ret_257; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_258 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_258); mph_types_TypeResult* _ret_259 = mph_types_make_type_result(ctx, NULL, _arg_258); mph_gc_pop_roots(ctx, 1); _ret_259; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_260 = left; mph_gc_push_root(ctx, (void**)&_obj_260); mph_int _ret_261 = _obj_260->kind; mph_gc_pop_roots(ctx, 1); _ret_261; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_262 = right; mph_gc_push_root(ctx, (void**)&_obj_262); mph_int _ret_263 = _obj_262->kind; mph_gc_pop_roots(ctx, 1); _ret_263; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_264 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_264); mph_types_TypeResult* _ret_265 = mph_types_make_type_result(ctx, NULL, _arg_264); mph_gc_pop_roots(ctx, 1); _ret_265; });
}
	}
}
	}
	return ({ MorphString* _arg_266 = mph_string_new(ctx, "<= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_266); mph_types_TypeResult* _ret_267 = mph_types_make_type_error(ctx, NULL, _arg_266); mph_gc_pop_roots(ctx, 1); _ret_267; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">="))) {
{
	if ((({ mph_types_Type* _obj_268 = left; mph_gc_push_root(ctx, (void**)&_obj_268); mph_int _ret_269 = _obj_268->kind; mph_gc_pop_roots(ctx, 1); _ret_269; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_270 = right; mph_gc_push_root(ctx, (void**)&_obj_270); mph_int _ret_271 = _obj_270->kind; mph_gc_pop_roots(ctx, 1); _ret_271; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_272 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_272); mph_types_TypeResult* _ret_273 = mph_types_make_type_result(ctx, NULL, _arg_272); mph_gc_pop_roots(ctx, 1); _ret_273; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_274 = left; mph_gc_push_root(ctx, (void**)&_obj_274); mph_int _ret_275 = _obj_274->kind; mph_gc_pop_roots(ctx, 1); _ret_275; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_276 = right; mph_gc_push_root(ctx, (void**)&_obj_276); mph_int _ret_277 = _obj_276->kind; mph_gc_pop_roots(ctx, 1); _ret_277; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_278 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_278); mph_types_TypeResult* _ret_279 = mph_types_make_type_result(ctx, NULL, _arg_278); mph_gc_pop_roots(ctx, 1); _ret_279; });
}
	}
}
	}
	return ({ MorphString* _arg_280 = mph_string_new(ctx, ">= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_280); mph_types_TypeResult* _ret_281 = mph_types_make_type_error(ctx, NULL, _arg_280); mph_gc_pop_roots(ctx, 1); _ret_281; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&"))) {
{
	if ((({ mph_types_Type* _obj_282 = left; mph_gc_push_root(ctx, (void**)&_obj_282); mph_int _ret_283 = _obj_282->kind; mph_gc_pop_roots(ctx, 1); _ret_283; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_284 = right; mph_gc_push_root(ctx, (void**)&_obj_284); mph_int _ret_285 = _obj_284->kind; mph_gc_pop_roots(ctx, 1); _ret_285; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_286 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_286); mph_types_TypeResult* _ret_287 = mph_types_make_type_result(ctx, NULL, _arg_286); mph_gc_pop_roots(ctx, 1); _ret_287; });
}
	}
}
	}
	return ({ MorphString* _arg_288 = mph_string_new(ctx, "& memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_288); mph_types_TypeResult* _ret_289 = mph_types_make_type_error(ctx, NULL, _arg_288); mph_gc_pop_roots(ctx, 1); _ret_289; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "|"))) {
{
	if ((({ mph_types_Type* _obj_290 = left; mph_gc_push_root(ctx, (void**)&_obj_290); mph_int _ret_291 = _obj_290->kind; mph_gc_pop_roots(ctx, 1); _ret_291; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_292 = right; mph_gc_push_root(ctx, (void**)&_obj_292); mph_int _ret_293 = _obj_292->kind; mph_gc_pop_roots(ctx, 1); _ret_293; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_294 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_294); mph_types_TypeResult* _ret_295 = mph_types_make_type_result(ctx, NULL, _arg_294); mph_gc_pop_roots(ctx, 1); _ret_295; });
}
	}
}
	}
	return ({ MorphString* _arg_296 = mph_string_new(ctx, "| memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_296); mph_types_TypeResult* _ret_297 = mph_types_make_type_error(ctx, NULL, _arg_296); mph_gc_pop_roots(ctx, 1); _ret_297; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "^"))) {
{
	if ((({ mph_types_Type* _obj_298 = left; mph_gc_push_root(ctx, (void**)&_obj_298); mph_int _ret_299 = _obj_298->kind; mph_gc_pop_roots(ctx, 1); _ret_299; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_300 = right; mph_gc_push_root(ctx, (void**)&_obj_300); mph_int _ret_301 = _obj_300->kind; mph_gc_pop_roots(ctx, 1); _ret_301; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_302 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_302); mph_types_TypeResult* _ret_303 = mph_types_make_type_result(ctx, NULL, _arg_302); mph_gc_pop_roots(ctx, 1); _ret_303; });
}
	}
}
	}
	return ({ MorphString* _arg_304 = mph_string_new(ctx, "^ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_304); mph_types_TypeResult* _ret_305 = mph_types_make_type_error(ctx, NULL, _arg_304); mph_gc_pop_roots(ctx, 1); _ret_305; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<<"))) {
{
	if ((({ mph_types_Type* _obj_306 = left; mph_gc_push_root(ctx, (void**)&_obj_306); mph_int _ret_307 = _obj_306->kind; mph_gc_pop_roots(ctx, 1); _ret_307; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_308 = right; mph_gc_push_root(ctx, (void**)&_obj_308); mph_int _ret_309 = _obj_308->kind; mph_gc_pop_roots(ctx, 1); _ret_309; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_310 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_310); mph_types_TypeResult* _ret_311 = mph_types_make_type_result(ctx, NULL, _arg_310); mph_gc_pop_roots(ctx, 1); _ret_311; });
}
	}
}
	}
	return ({ MorphString* _arg_312 = mph_string_new(ctx, "<< memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_312); mph_types_TypeResult* _ret_313 = mph_types_make_type_error(ctx, NULL, _arg_312); mph_gc_pop_roots(ctx, 1); _ret_313; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">>"))) {
{
	if ((({ mph_types_Type* _obj_314 = left; mph_gc_push_root(ctx, (void**)&_obj_314); mph_int _ret_315 = _obj_314->kind; mph_gc_pop_roots(ctx, 1); _ret_315; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_316 = right; mph_gc_push_root(ctx, (void**)&_obj_316); mph_int _ret_317 = _obj_316->kind; mph_gc_pop_roots(ctx, 1); _ret_317; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_318 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_318); mph_types_TypeResult* _ret_319 = mph_types_make_type_result(ctx, NULL, _arg_318); mph_gc_pop_roots(ctx, 1); _ret_319; });
}
	}
}
	}
	return ({ MorphString* _arg_320 = mph_string_new(ctx, ">> memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_320); mph_types_TypeResult* _ret_321 = mph_types_make_type_error(ctx, NULL, _arg_320); mph_gc_pop_roots(ctx, 1); _ret_321; });
}
	}
	return ({ MorphString* _arg_322 = mph_string_new(ctx, "operator tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_322); mph_types_TypeResult* _ret_323 = mph_types_make_type_error(ctx, NULL, _arg_322); mph_gc_pop_roots(ctx, 1); _ret_323; });
	mph_gc_pop_roots(ctx, 3);
}

mph_types_TypeResult* mph_types_type_prefix_op(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	if ((({ mph_types_Type* _obj_324 = t; mph_gc_push_root(ctx, (void**)&_obj_324); mph_int _ret_325 = _obj_324->kind; mph_gc_pop_roots(ctx, 1); _ret_325; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_326 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_326); mph_types_TypeResult* _ret_327 = mph_types_make_type_result(ctx, NULL, _arg_326); mph_gc_pop_roots(ctx, 1); _ret_327; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!"))) {
{
	if ((({ mph_types_Type* _obj_328 = t; mph_gc_push_root(ctx, (void**)&_obj_328); mph_int _ret_329 = _obj_328->kind; mph_gc_pop_roots(ctx, 1); _ret_329; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_330 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_330); mph_types_TypeResult* _ret_331 = mph_types_make_type_result(ctx, NULL, _arg_330); mph_gc_pop_roots(ctx, 1); _ret_331; });
}
	}
	return ({ MorphString* _arg_332 = mph_string_new(ctx, "! memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_332); mph_types_TypeResult* _ret_333 = mph_types_make_type_error(ctx, NULL, _arg_332); mph_gc_pop_roots(ctx, 1); _ret_333; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_types_Type* _obj_334 = t; mph_gc_push_root(ctx, (void**)&_obj_334); mph_int _ret_335 = _obj_334->kind; mph_gc_pop_roots(ctx, 1); _ret_335; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_336 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_336); mph_types_TypeResult* _ret_337 = mph_types_make_type_result(ctx, NULL, _arg_336); mph_gc_pop_roots(ctx, 1); _ret_337; });
}
	}
	if ((({ mph_types_Type* _obj_338 = t; mph_gc_push_root(ctx, (void**)&_obj_338); mph_int _ret_339 = _obj_338->kind; mph_gc_pop_roots(ctx, 1); _ret_339; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_340 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_340); mph_types_TypeResult* _ret_341 = mph_types_make_type_result(ctx, NULL, _arg_340); mph_gc_pop_roots(ctx, 1); _ret_341; });
}
	}
	return ({ MorphString* _arg_342 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_342); mph_types_TypeResult* _ret_343 = mph_types_make_type_error(ctx, NULL, _arg_342); mph_gc_pop_roots(ctx, 1); _ret_343; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "~"))) {
{
	if ((({ mph_types_Type* _obj_344 = t; mph_gc_push_root(ctx, (void**)&_obj_344); mph_int _ret_345 = _obj_344->kind; mph_gc_pop_roots(ctx, 1); _ret_345; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_346 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_346); mph_types_TypeResult* _ret_347 = mph_types_make_type_result(ctx, NULL, _arg_346); mph_gc_pop_roots(ctx, 1); _ret_347; });
}
	}
	return ({ MorphString* _arg_348 = mph_string_new(ctx, "~ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_348); mph_types_TypeResult* _ret_349 = mph_types_make_type_error(ctx, NULL, _arg_348); mph_gc_pop_roots(ctx, 1); _ret_349; });
}
	}
	return ({ MorphString* _arg_350 = mph_string_new(ctx, "prefix tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_350); mph_types_TypeResult* _ret_351 = mph_types_make_type_error(ctx, NULL, _arg_350); mph_gc_pop_roots(ctx, 1); _ret_351; });
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
	return ({ MorphString* _arg_352 = n; mph_gc_push_root(ctx, (void**)&_arg_352); mph_types_Type* _ret_353 = mph_types_struct_type(ctx, NULL, _arg_352); mph_gc_pop_roots(ctx, 1); _ret_353; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_InterfaceType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_354 = n; mph_gc_push_root(ctx, (void**)&_arg_354); mph_types_Type* _ret_355 = mph_types_interface_type(ctx, NULL, _arg_354); mph_gc_pop_roots(ctx, 1); _ret_355; });
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
	return ({ MorphString* _arg_356 = n; mph_gc_push_root(ctx, (void**)&_arg_356); mph_types_Type* _ret_357 = mph_types_module_type(ctx, NULL, _arg_356); mph_gc_pop_roots(ctx, 1); _ret_357; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_types_TypeEquals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return ({ mph_types_Type* _arg_358 = t1; mph_gc_push_root(ctx, (void**)&_arg_358); mph_types_Type* _arg_359 = t2; mph_gc_push_root(ctx, (void**)&_arg_359); mph_bool _ret_360 = mph_types_type_equals(ctx, NULL, _arg_358, _arg_359); mph_gc_pop_roots(ctx, 2); _ret_360; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_TypeAssignableTo(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	return ({ mph_types_Type* _arg_361 = source; mph_gc_push_root(ctx, (void**)&_arg_361); mph_types_Type* _arg_362 = target; mph_gc_push_root(ctx, (void**)&_arg_362); mph_bool _ret_363 = mph_types_type_assignable_to(ctx, NULL, _arg_361, _arg_362); mph_gc_pop_roots(ctx, 2); _ret_363; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_TypeIsComparable(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_types_Type* _arg_364 = t; mph_gc_push_root(ctx, (void**)&_arg_364); mph_bool _ret_365 = mph_types_type_is_comparable(ctx, NULL, _arg_364); mph_gc_pop_roots(ctx, 1); _ret_365; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_TypeResult* mph_types_TypeBinaryOp(MorphContext* ctx, void* _env_void, mph_types_Type* left, MorphString* op, mph_types_Type* right) {
	mph_gc_push_root(ctx, (void**)&left);
	mph_gc_push_root(ctx, (void**)&op);
	mph_gc_push_root(ctx, (void**)&right);
	return ({ mph_types_Type* _arg_366 = left; mph_gc_push_root(ctx, (void**)&_arg_366); MorphString* _arg_367 = op; mph_gc_push_root(ctx, (void**)&_arg_367); mph_types_Type* _arg_368 = right; mph_gc_push_root(ctx, (void**)&_arg_368); mph_types_TypeResult* _ret_369 = mph_types_type_binary_op(ctx, NULL, _arg_366, _arg_367, _arg_368); mph_gc_pop_roots(ctx, 3); _ret_369; });
	mph_gc_pop_roots(ctx, 3);
}

mph_types_TypeResult* mph_types_TypePrefixOp(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	return ({ mph_types_Type* _arg_370 = t; mph_gc_push_root(ctx, (void**)&_arg_370); MorphString* _arg_371 = op; mph_gc_push_root(ctx, (void**)&_arg_371); mph_types_TypeResult* _ret_372 = mph_types_type_prefix_op(ctx, NULL, _arg_370, _arg_371); mph_gc_pop_roots(ctx, 2); _ret_372; });
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
	if ((({ mph_types_Type* _obj_373 = t_int; mph_gc_push_root(ctx, (void**)&_obj_373); mph_int _ret_374 = _obj_373->kind; mph_gc_pop_roots(ctx, 1); _ret_374; }) == mph_types_KIND_INT)) {
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
	if (({ mph_types_Type* _arg_375 = t_int; mph_gc_push_root(ctx, (void**)&_arg_375); mph_types_Type* _arg_376 = t_int; mph_gc_push_root(ctx, (void**)&_arg_376); mph_bool _ret_377 = mph_types_type_equals(ctx, NULL, _arg_375, _arg_376); mph_gc_pop_roots(ctx, 2); _ret_377; })) {
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
	if (({ mph_types_Type* _arg_378 = t_int; mph_gc_push_root(ctx, (void**)&_arg_378); mph_types_Type* _arg_379 = t_float; mph_gc_push_root(ctx, (void**)&_arg_379); mph_bool _ret_380 = mph_types_type_equals(ctx, NULL, _arg_378, _arg_379); mph_gc_pop_roots(ctx, 2); _ret_380; })) {
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
	if (({ mph_types_Type* _arg_381 = t_null; mph_gc_push_root(ctx, (void**)&_arg_381); mph_types_Type* _arg_382 = t_array; mph_gc_push_root(ctx, (void**)&_arg_382); mph_bool _ret_383 = mph_types_type_assignable_to(ctx, NULL, _arg_381, _arg_382); mph_gc_pop_roots(ctx, 2); _ret_383; })) {
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
	if (({ mph_types_Type* _arg_384 = t_null; mph_gc_push_root(ctx, (void**)&_arg_384); mph_types_Type* _arg_385 = t_map; mph_gc_push_root(ctx, (void**)&_arg_385); mph_bool _ret_386 = mph_types_type_assignable_to(ctx, NULL, _arg_384, _arg_385); mph_gc_pop_roots(ctx, 2); _ret_386; })) {
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
	if (({ mph_types_Type* _arg_387 = t_null; mph_gc_push_root(ctx, (void**)&_arg_387); mph_types_Type* _arg_388 = t_int; mph_gc_push_root(ctx, (void**)&_arg_388); mph_bool _ret_389 = mph_types_type_assignable_to(ctx, NULL, _arg_387, _arg_388); mph_gc_pop_roots(ctx, 2); _ret_389; })) {
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
	if (({ mph_types_Type* _arg_390 = t_int; mph_gc_push_root(ctx, (void**)&_arg_390); mph_bool _ret_391 = mph_types_type_is_comparable(ctx, NULL, _arg_390); mph_gc_pop_roots(ctx, 1); _ret_391; })) {
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
	if (({ mph_types_Type* _arg_392 = t_void; mph_gc_push_root(ctx, (void**)&_arg_392); mph_bool _ret_393 = mph_types_type_is_comparable(ctx, NULL, _arg_392); mph_gc_pop_roots(ctx, 1); _ret_393; })) {
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
	mph_types_TypeResult* r1 = ({ mph_types_Type* _arg_394 = t_int; mph_gc_push_root(ctx, (void**)&_arg_394); MorphString* _arg_395 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_395); mph_types_Type* _arg_396 = t_int; mph_gc_push_root(ctx, (void**)&_arg_396); mph_types_TypeResult* _ret_397 = mph_types_type_binary_op(ctx, NULL, _arg_394, _arg_395, _arg_396); mph_gc_pop_roots(ctx, 3); _ret_397; });
	mph_gc_push_root(ctx, (void**)&r1);
	if (({ mph_types_TypeResult* _obj_398 = r1; mph_gc_push_root(ctx, (void**)&_obj_398); mph_bool _ret_399 = _obj_398->has_error; mph_gc_pop_roots(ctx, 1); _ret_399; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_402 = ({ mph_types_TypeResult* _obj_400 = r1; mph_gc_push_root(ctx, (void**)&_obj_400); mph_types_Type* _ret_401 = _obj_400->result; mph_gc_pop_roots(ctx, 1); _ret_401; }); mph_gc_push_root(ctx, (void**)&_obj_402); mph_int _ret_403 = _obj_402->kind; mph_gc_pop_roots(ctx, 1); _ret_403; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r2 = ({ mph_types_Type* _arg_404 = t_string; mph_gc_push_root(ctx, (void**)&_arg_404); MorphString* _arg_405 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_405); mph_types_Type* _arg_406 = t_string; mph_gc_push_root(ctx, (void**)&_arg_406); mph_types_TypeResult* _ret_407 = mph_types_type_binary_op(ctx, NULL, _arg_404, _arg_405, _arg_406); mph_gc_pop_roots(ctx, 3); _ret_407; });
	mph_gc_push_root(ctx, (void**)&r2);
	if (({ mph_types_TypeResult* _obj_408 = r2; mph_gc_push_root(ctx, (void**)&_obj_408); mph_bool _ret_409 = _obj_408->has_error; mph_gc_pop_roots(ctx, 1); _ret_409; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string + string FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_412 = ({ mph_types_TypeResult* _obj_410 = r2; mph_gc_push_root(ctx, (void**)&_obj_410); mph_types_Type* _ret_411 = _obj_410->result; mph_gc_pop_roots(ctx, 1); _ret_411; }); mph_gc_push_root(ctx, (void**)&_obj_412); mph_int _ret_413 = _obj_412->kind; mph_gc_pop_roots(ctx, 1); _ret_413; }) == mph_types_KIND_STRING)) {
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
	mph_types_TypeResult* r3 = ({ mph_types_Type* _arg_414 = t_float; mph_gc_push_root(ctx, (void**)&_arg_414); MorphString* _arg_415 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_arg_415); mph_types_Type* _arg_416 = t_float; mph_gc_push_root(ctx, (void**)&_arg_416); mph_types_TypeResult* _ret_417 = mph_types_type_binary_op(ctx, NULL, _arg_414, _arg_415, _arg_416); mph_gc_pop_roots(ctx, 3); _ret_417; });
	mph_gc_push_root(ctx, (void**)&r3);
	if (({ mph_types_TypeResult* _obj_418 = r3; mph_gc_push_root(ctx, (void**)&_obj_418); mph_bool _ret_419 = _obj_418->has_error; mph_gc_pop_roots(ctx, 1); _ret_419; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â float * float FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_422 = ({ mph_types_TypeResult* _obj_420 = r3; mph_gc_push_root(ctx, (void**)&_obj_420); mph_types_Type* _ret_421 = _obj_420->result; mph_gc_pop_roots(ctx, 1); _ret_421; }); mph_gc_push_root(ctx, (void**)&_obj_422); mph_int _ret_423 = _obj_422->kind; mph_gc_pop_roots(ctx, 1); _ret_423; }) == mph_types_KIND_FLOAT)) {
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
	mph_types_TypeResult* r4 = ({ mph_types_Type* _arg_424 = t_int; mph_gc_push_root(ctx, (void**)&_arg_424); MorphString* _arg_425 = mph_string_new(ctx, "<"); mph_gc_push_root(ctx, (void**)&_arg_425); mph_types_Type* _arg_426 = t_int; mph_gc_push_root(ctx, (void**)&_arg_426); mph_types_TypeResult* _ret_427 = mph_types_type_binary_op(ctx, NULL, _arg_424, _arg_425, _arg_426); mph_gc_pop_roots(ctx, 3); _ret_427; });
	mph_gc_push_root(ctx, (void**)&r4);
	if (({ mph_types_TypeResult* _obj_428 = r4; mph_gc_push_root(ctx, (void**)&_obj_428); mph_bool _ret_429 = _obj_428->has_error; mph_gc_pop_roots(ctx, 1); _ret_429; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int < int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_432 = ({ mph_types_TypeResult* _obj_430 = r4; mph_gc_push_root(ctx, (void**)&_obj_430); mph_types_Type* _ret_431 = _obj_430->result; mph_gc_pop_roots(ctx, 1); _ret_431; }); mph_gc_push_root(ctx, (void**)&_obj_432); mph_int _ret_433 = _obj_432->kind; mph_gc_pop_roots(ctx, 1); _ret_433; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r5 = ({ mph_types_Type* _arg_434 = t_int; mph_gc_push_root(ctx, (void**)&_arg_434); MorphString* _arg_435 = mph_string_new(ctx, "=="); mph_gc_push_root(ctx, (void**)&_arg_435); mph_types_Type* _arg_436 = t_int; mph_gc_push_root(ctx, (void**)&_arg_436); mph_types_TypeResult* _ret_437 = mph_types_type_binary_op(ctx, NULL, _arg_434, _arg_435, _arg_436); mph_gc_pop_roots(ctx, 3); _ret_437; });
	mph_gc_push_root(ctx, (void**)&r5);
	if (({ mph_types_TypeResult* _obj_438 = r5; mph_gc_push_root(ctx, (void**)&_obj_438); mph_bool _ret_439 = _obj_438->has_error; mph_gc_pop_roots(ctx, 1); _ret_439; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_442 = ({ mph_types_TypeResult* _obj_440 = r5; mph_gc_push_root(ctx, (void**)&_obj_440); mph_types_Type* _ret_441 = _obj_440->result; mph_gc_pop_roots(ctx, 1); _ret_441; }); mph_gc_push_root(ctx, (void**)&_obj_442); mph_int _ret_443 = _obj_442->kind; mph_gc_pop_roots(ctx, 1); _ret_443; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r6 = ({ mph_types_Type* _arg_444 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_444); MorphString* _arg_445 = mph_string_new(ctx, "dan"); mph_gc_push_root(ctx, (void**)&_arg_445); mph_types_Type* _arg_446 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_446); mph_types_TypeResult* _ret_447 = mph_types_type_binary_op(ctx, NULL, _arg_444, _arg_445, _arg_446); mph_gc_pop_roots(ctx, 3); _ret_447; });
	mph_gc_push_root(ctx, (void**)&r6);
	if (({ mph_types_TypeResult* _obj_448 = r6; mph_gc_push_root(ctx, (void**)&_obj_448); mph_bool _ret_449 = _obj_448->has_error; mph_gc_pop_roots(ctx, 1); _ret_449; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool dan bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_452 = ({ mph_types_TypeResult* _obj_450 = r6; mph_gc_push_root(ctx, (void**)&_obj_450); mph_types_Type* _ret_451 = _obj_450->result; mph_gc_pop_roots(ctx, 1); _ret_451; }); mph_gc_push_root(ctx, (void**)&_obj_452); mph_int _ret_453 = _obj_452->kind; mph_gc_pop_roots(ctx, 1); _ret_453; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r7 = ({ mph_types_Type* _arg_454 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_454); MorphString* _arg_455 = mph_string_new(ctx, "||"); mph_gc_push_root(ctx, (void**)&_arg_455); mph_types_Type* _arg_456 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_456); mph_types_TypeResult* _ret_457 = mph_types_type_binary_op(ctx, NULL, _arg_454, _arg_455, _arg_456); mph_gc_pop_roots(ctx, 3); _ret_457; });
	mph_gc_push_root(ctx, (void**)&r7);
	if (({ mph_types_TypeResult* _obj_458 = r7; mph_gc_push_root(ctx, (void**)&_obj_458); mph_bool _ret_459 = _obj_458->has_error; mph_gc_pop_roots(ctx, 1); _ret_459; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool || bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_462 = ({ mph_types_TypeResult* _obj_460 = r7; mph_gc_push_root(ctx, (void**)&_obj_460); mph_types_Type* _ret_461 = _obj_460->result; mph_gc_pop_roots(ctx, 1); _ret_461; }); mph_gc_push_root(ctx, (void**)&_obj_462); mph_int _ret_463 = _obj_462->kind; mph_gc_pop_roots(ctx, 1); _ret_463; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r8 = ({ mph_types_Type* _arg_464 = t_int; mph_gc_push_root(ctx, (void**)&_arg_464); MorphString* _arg_465 = mph_string_new(ctx, "&"); mph_gc_push_root(ctx, (void**)&_arg_465); mph_types_Type* _arg_466 = t_int; mph_gc_push_root(ctx, (void**)&_arg_466); mph_types_TypeResult* _ret_467 = mph_types_type_binary_op(ctx, NULL, _arg_464, _arg_465, _arg_466); mph_gc_pop_roots(ctx, 3); _ret_467; });
	mph_gc_push_root(ctx, (void**)&r8);
	if (({ mph_types_TypeResult* _obj_468 = r8; mph_gc_push_root(ctx, (void**)&_obj_468); mph_bool _ret_469 = _obj_468->has_error; mph_gc_pop_roots(ctx, 1); _ret_469; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int & int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_472 = ({ mph_types_TypeResult* _obj_470 = r8; mph_gc_push_root(ctx, (void**)&_obj_470); mph_types_Type* _ret_471 = _obj_470->result; mph_gc_pop_roots(ctx, 1); _ret_471; }); mph_gc_push_root(ctx, (void**)&_obj_472); mph_int _ret_473 = _obj_472->kind; mph_gc_pop_roots(ctx, 1); _ret_473; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r9 = ({ mph_types_Type* _arg_474 = t_int; mph_gc_push_root(ctx, (void**)&_arg_474); MorphString* _arg_475 = mph_string_new(ctx, "<<"); mph_gc_push_root(ctx, (void**)&_arg_475); mph_types_Type* _arg_476 = t_int; mph_gc_push_root(ctx, (void**)&_arg_476); mph_types_TypeResult* _ret_477 = mph_types_type_binary_op(ctx, NULL, _arg_474, _arg_475, _arg_476); mph_gc_pop_roots(ctx, 3); _ret_477; });
	mph_gc_push_root(ctx, (void**)&r9);
	if (({ mph_types_TypeResult* _obj_478 = r9; mph_gc_push_root(ctx, (void**)&_obj_478); mph_bool _ret_479 = _obj_478->has_error; mph_gc_pop_roots(ctx, 1); _ret_479; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int << int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_482 = ({ mph_types_TypeResult* _obj_480 = r9; mph_gc_push_root(ctx, (void**)&_obj_480); mph_types_Type* _ret_481 = _obj_480->result; mph_gc_pop_roots(ctx, 1); _ret_481; }); mph_gc_push_root(ctx, (void**)&_obj_482); mph_int _ret_483 = _obj_482->kind; mph_gc_pop_roots(ctx, 1); _ret_483; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r10 = ({ mph_types_Type* _arg_484 = t_int; mph_gc_push_root(ctx, (void**)&_arg_484); MorphString* _arg_485 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_485); mph_types_Type* _arg_486 = t_string; mph_gc_push_root(ctx, (void**)&_arg_486); mph_types_TypeResult* _ret_487 = mph_types_type_binary_op(ctx, NULL, _arg_484, _arg_485, _arg_486); mph_gc_pop_roots(ctx, 3); _ret_487; });
	mph_gc_push_root(ctx, (void**)&r10);
	if (({ mph_types_TypeResult* _obj_488 = r10; mph_gc_push_root(ctx, (void**)&_obj_488); mph_bool _ret_489 = _obj_488->has_error; mph_gc_pop_roots(ctx, 1); _ret_489; })) {
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
	mph_types_TypeResult* r11 = ({ mph_types_Type* _arg_490 = t_string; mph_gc_push_root(ctx, (void**)&_arg_490); MorphString* _arg_491 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_491); mph_types_Type* _arg_492 = t_string; mph_gc_push_root(ctx, (void**)&_arg_492); mph_types_TypeResult* _ret_493 = mph_types_type_binary_op(ctx, NULL, _arg_490, _arg_491, _arg_492); mph_gc_pop_roots(ctx, 3); _ret_493; });
	mph_gc_push_root(ctx, (void**)&r11);
	if (({ mph_types_TypeResult* _obj_494 = r11; mph_gc_push_root(ctx, (void**)&_obj_494); mph_bool _ret_495 = _obj_494->has_error; mph_gc_pop_roots(ctx, 1); _ret_495; })) {
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
	mph_types_TypeResult* r12 = ({ mph_types_Type* _arg_496 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_496); MorphString* _arg_497 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_497); mph_types_TypeResult* _ret_498 = mph_types_type_prefix_op(ctx, NULL, _arg_496, _arg_497); mph_gc_pop_roots(ctx, 2); _ret_498; });
	mph_gc_push_root(ctx, (void**)&r12);
	if (({ mph_types_TypeResult* _obj_499 = r12; mph_gc_push_root(ctx, (void**)&_obj_499); mph_bool _ret_500 = _obj_499->has_error; mph_gc_pop_roots(ctx, 1); _ret_500; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_503 = ({ mph_types_TypeResult* _obj_501 = r12; mph_gc_push_root(ctx, (void**)&_obj_501); mph_types_Type* _ret_502 = _obj_501->result; mph_gc_pop_roots(ctx, 1); _ret_502; }); mph_gc_push_root(ctx, (void**)&_obj_503); mph_int _ret_504 = _obj_503->kind; mph_gc_pop_roots(ctx, 1); _ret_504; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r13 = ({ mph_types_Type* _arg_505 = t_int; mph_gc_push_root(ctx, (void**)&_arg_505); MorphString* _arg_506 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_506); mph_types_TypeResult* _ret_507 = mph_types_type_prefix_op(ctx, NULL, _arg_505, _arg_506); mph_gc_pop_roots(ctx, 2); _ret_507; });
	mph_gc_push_root(ctx, (void**)&r13);
	if (({ mph_types_TypeResult* _obj_508 = r13; mph_gc_push_root(ctx, (void**)&_obj_508); mph_bool _ret_509 = _obj_508->has_error; mph_gc_pop_roots(ctx, 1); _ret_509; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â -int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_512 = ({ mph_types_TypeResult* _obj_510 = r13; mph_gc_push_root(ctx, (void**)&_obj_510); mph_types_Type* _ret_511 = _obj_510->result; mph_gc_pop_roots(ctx, 1); _ret_511; }); mph_gc_push_root(ctx, (void**)&_obj_512); mph_int _ret_513 = _obj_512->kind; mph_gc_pop_roots(ctx, 1); _ret_513; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r14 = ({ mph_types_Type* _arg_514 = t_int; mph_gc_push_root(ctx, (void**)&_arg_514); MorphString* _arg_515 = mph_string_new(ctx, "~"); mph_gc_push_root(ctx, (void**)&_arg_515); mph_types_TypeResult* _ret_516 = mph_types_type_prefix_op(ctx, NULL, _arg_514, _arg_515); mph_gc_pop_roots(ctx, 2); _ret_516; });
	mph_gc_push_root(ctx, (void**)&r14);
	if (({ mph_types_TypeResult* _obj_517 = r14; mph_gc_push_root(ctx, (void**)&_obj_517); mph_bool _ret_518 = _obj_517->has_error; mph_gc_pop_roots(ctx, 1); _ret_518; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â ~int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_521 = ({ mph_types_TypeResult* _obj_519 = r14; mph_gc_push_root(ctx, (void**)&_obj_519); mph_types_Type* _ret_520 = _obj_519->result; mph_gc_pop_roots(ctx, 1); _ret_520; }); mph_gc_push_root(ctx, (void**)&_obj_521); mph_int _ret_522 = _obj_521->kind; mph_gc_pop_roots(ctx, 1); _ret_522; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r15 = ({ mph_types_Type* _arg_523 = t_string; mph_gc_push_root(ctx, (void**)&_arg_523); MorphString* _arg_524 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_524); mph_types_TypeResult* _ret_525 = mph_types_type_prefix_op(ctx, NULL, _arg_523, _arg_524); mph_gc_pop_roots(ctx, 2); _ret_525; });
	mph_gc_push_root(ctx, (void**)&r15);
	if (({ mph_types_TypeResult* _obj_526 = r15; mph_gc_push_root(ctx, (void**)&_obj_526); mph_bool _ret_527 = _obj_526->has_error; mph_gc_pop_roots(ctx, 1); _ret_527; })) {
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
	result = ({ MorphString* _lhs_528 = mph_string_new(ctx, "0"); MorphString* _rhs_529 = result; mph_gc_push_root(ctx, (void**)&_lhs_528); mph_gc_push_root(ctx, (void**)&_rhs_529); MorphString* _ret_530 = mph_string_concat(ctx, _lhs_528, _rhs_529); mph_gc_pop_roots(ctx, 2); _ret_530; });
}
	}
	if ((digit == 1)) {
{
	result = ({ MorphString* _lhs_531 = mph_string_new(ctx, "1"); MorphString* _rhs_532 = result; mph_gc_push_root(ctx, (void**)&_lhs_531); mph_gc_push_root(ctx, (void**)&_rhs_532); MorphString* _ret_533 = mph_string_concat(ctx, _lhs_531, _rhs_532); mph_gc_pop_roots(ctx, 2); _ret_533; });
}
	}
	if ((digit == 2)) {
{
	result = ({ MorphString* _lhs_534 = mph_string_new(ctx, "2"); MorphString* _rhs_535 = result; mph_gc_push_root(ctx, (void**)&_lhs_534); mph_gc_push_root(ctx, (void**)&_rhs_535); MorphString* _ret_536 = mph_string_concat(ctx, _lhs_534, _rhs_535); mph_gc_pop_roots(ctx, 2); _ret_536; });
}
	}
	if ((digit == 3)) {
{
	result = ({ MorphString* _lhs_537 = mph_string_new(ctx, "3"); MorphString* _rhs_538 = result; mph_gc_push_root(ctx, (void**)&_lhs_537); mph_gc_push_root(ctx, (void**)&_rhs_538); MorphString* _ret_539 = mph_string_concat(ctx, _lhs_537, _rhs_538); mph_gc_pop_roots(ctx, 2); _ret_539; });
}
	}
	if ((digit == 4)) {
{
	result = ({ MorphString* _lhs_540 = mph_string_new(ctx, "4"); MorphString* _rhs_541 = result; mph_gc_push_root(ctx, (void**)&_lhs_540); mph_gc_push_root(ctx, (void**)&_rhs_541); MorphString* _ret_542 = mph_string_concat(ctx, _lhs_540, _rhs_541); mph_gc_pop_roots(ctx, 2); _ret_542; });
}
	}
	if ((digit == 5)) {
{
	result = ({ MorphString* _lhs_543 = mph_string_new(ctx, "5"); MorphString* _rhs_544 = result; mph_gc_push_root(ctx, (void**)&_lhs_543); mph_gc_push_root(ctx, (void**)&_rhs_544); MorphString* _ret_545 = mph_string_concat(ctx, _lhs_543, _rhs_544); mph_gc_pop_roots(ctx, 2); _ret_545; });
}
	}
	if ((digit == 6)) {
{
	result = ({ MorphString* _lhs_546 = mph_string_new(ctx, "6"); MorphString* _rhs_547 = result; mph_gc_push_root(ctx, (void**)&_lhs_546); mph_gc_push_root(ctx, (void**)&_rhs_547); MorphString* _ret_548 = mph_string_concat(ctx, _lhs_546, _rhs_547); mph_gc_pop_roots(ctx, 2); _ret_548; });
}
	}
	if ((digit == 7)) {
{
	result = ({ MorphString* _lhs_549 = mph_string_new(ctx, "7"); MorphString* _rhs_550 = result; mph_gc_push_root(ctx, (void**)&_lhs_549); mph_gc_push_root(ctx, (void**)&_rhs_550); MorphString* _ret_551 = mph_string_concat(ctx, _lhs_549, _rhs_550); mph_gc_pop_roots(ctx, 2); _ret_551; });
}
	}
	if ((digit == 8)) {
{
	result = ({ MorphString* _lhs_552 = mph_string_new(ctx, "8"); MorphString* _rhs_553 = result; mph_gc_push_root(ctx, (void**)&_lhs_552); mph_gc_push_root(ctx, (void**)&_rhs_553); MorphString* _ret_554 = mph_string_concat(ctx, _lhs_552, _rhs_553); mph_gc_pop_roots(ctx, 2); _ret_554; });
}
	}
	if ((digit == 9)) {
{
	result = ({ MorphString* _lhs_555 = mph_string_new(ctx, "9"); MorphString* _rhs_556 = result; mph_gc_push_root(ctx, (void**)&_lhs_555); mph_gc_push_root(ctx, (void**)&_rhs_556); MorphString* _ret_557 = mph_string_concat(ctx, _lhs_555, _rhs_556); mph_gc_pop_roots(ctx, 2); _ret_557; });
}
	}
}
	}
	if (is_negative) {
{
	result = ({ MorphString* _lhs_558 = mph_string_new(ctx, "-"); MorphString* _rhs_559 = result; mph_gc_push_root(ctx, (void**)&_lhs_558); mph_gc_push_root(ctx, (void**)&_rhs_559); MorphString* _ret_560 = mph_string_concat(ctx, _lhs_558, _rhs_559); mph_gc_pop_roots(ctx, 2); _ret_560; });
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
	mph_int len = ({ MorphString* _len_arg_561 = s; mph_gc_push_root(ctx, (void**)&_len_arg_561); mph_int _ret_562 = ((MorphString*)_len_arg_561)->length; mph_gc_pop_roots(ctx, 1); _ret_562; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_563 = s; mph_gc_push_root(ctx, (void**)&_arg_563); MorphString* _ret_564 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_563, i); mph_gc_pop_roots(ctx, 1); _ret_564; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\\"))) {
{
	result = ({ MorphString* _lhs_565 = result; MorphString* _rhs_566 = mph_string_new(ctx, "\\\\"); mph_gc_push_root(ctx, (void**)&_lhs_565); mph_gc_push_root(ctx, (void**)&_rhs_566); MorphString* _ret_567 = mph_string_concat(ctx, _lhs_565, _rhs_566); mph_gc_pop_roots(ctx, 2); _ret_567; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\""))) {
{
	result = ({ MorphString* _lhs_568 = result; MorphString* _rhs_569 = mph_string_new(ctx, "\\\""); mph_gc_push_root(ctx, (void**)&_lhs_568); mph_gc_push_root(ctx, (void**)&_rhs_569); MorphString* _ret_570 = mph_string_concat(ctx, _lhs_568, _rhs_569); mph_gc_pop_roots(ctx, 2); _ret_570; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\n"))) {
{
	result = ({ MorphString* _lhs_571 = result; MorphString* _rhs_572 = mph_string_new(ctx, "\\n"); mph_gc_push_root(ctx, (void**)&_lhs_571); mph_gc_push_root(ctx, (void**)&_rhs_572); MorphString* _ret_573 = mph_string_concat(ctx, _lhs_571, _rhs_572); mph_gc_pop_roots(ctx, 2); _ret_573; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\r"))) {
{
	result = ({ MorphString* _lhs_574 = result; MorphString* _rhs_575 = mph_string_new(ctx, "\\r"); mph_gc_push_root(ctx, (void**)&_lhs_574); mph_gc_push_root(ctx, (void**)&_rhs_575); MorphString* _ret_576 = mph_string_concat(ctx, _lhs_574, _rhs_575); mph_gc_pop_roots(ctx, 2); _ret_576; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\t"))) {
{
	result = ({ MorphString* _lhs_577 = result; MorphString* _rhs_578 = mph_string_new(ctx, "\\t"); mph_gc_push_root(ctx, (void**)&_lhs_577); mph_gc_push_root(ctx, (void**)&_rhs_578); MorphString* _ret_579 = mph_string_concat(ctx, _lhs_577, _rhs_578); mph_gc_pop_roots(ctx, 2); _ret_579; });
}
	} else {
{
	result = ({ MorphString* _lhs_580 = result; MorphString* _rhs_581 = ch; mph_gc_push_root(ctx, (void**)&_lhs_580); mph_gc_push_root(ctx, (void**)&_rhs_581); MorphString* _ret_582 = mph_string_concat(ctx, _lhs_580, _rhs_581); mph_gc_pop_roots(ctx, 2); _ret_582; });
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
	mph_int len = ({ MorphString* _len_arg_583 = name; mph_gc_push_root(ctx, (void**)&_len_arg_583); mph_int _ret_584 = ((MorphString*)_len_arg_583)->length; mph_gc_pop_roots(ctx, 1); _ret_584; });
	if ((len == 0)) {
{
	return 0;
}
	}
	MorphString* first = ({ MorphString* _arg_585 = name; mph_gc_push_root(ctx, (void**)&_arg_585); MorphString* _ret_586 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_585, 0); mph_gc_pop_roots(ctx, 1); _ret_586; });
	mph_gc_push_root(ctx, (void**)&first);
	if (((first != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_587 = first; mph_gc_push_root(ctx, (void**)&_arg_587); mph_bool _ret_588 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_587); mph_gc_pop_roots(ctx, 1); _ret_588; })))) {
{
	return 0;
}
	}
	mph_int i = 1;
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_589 = name; mph_gc_push_root(ctx, (void**)&_arg_589); MorphString* _ret_590 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_589, i); mph_gc_pop_roots(ctx, 1); _ret_590; });
	mph_gc_push_root(ctx, (void**)&ch);
	if ((((ch != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_591 = ch; mph_gc_push_root(ctx, (void**)&_arg_591); mph_bool _ret_592 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_591); mph_gc_pop_roots(ctx, 1); _ret_592; }))) && (!({ MorphString* _arg_593 = ch; mph_gc_push_root(ctx, (void**)&_arg_593); mph_bool _ret_594 = mph_stdlib_codegen_is_digit(ctx, NULL, _arg_593); mph_gc_pop_roots(ctx, 1); _ret_594; })))) {
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
	mph_int len = ({ MorphString* _len_arg_595 = path; mph_gc_push_root(ctx, (void**)&_len_arg_595); mph_int _ret_596 = ((MorphString*)_len_arg_595)->length; mph_gc_pop_roots(ctx, 1); _ret_596; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_597 = path; mph_gc_push_root(ctx, (void**)&_arg_597); MorphString* _ret_598 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_597, i); mph_gc_pop_roots(ctx, 1); _ret_598; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "/"))) {
{
	result = ({ MorphString* _lhs_599 = result; MorphString* _rhs_600 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_599); mph_gc_push_root(ctx, (void**)&_rhs_600); MorphString* _ret_601 = mph_string_concat(ctx, _lhs_599, _rhs_600); mph_gc_pop_roots(ctx, 2); _ret_601; });
}
	} else {
{
	if (((({ MorphString* _arg_602 = ch; mph_gc_push_root(ctx, (void**)&_arg_602); mph_bool _ret_603 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_602); mph_gc_pop_roots(ctx, 1); _ret_603; }) || ({ MorphString* _arg_604 = ch; mph_gc_push_root(ctx, (void**)&_arg_604); mph_bool _ret_605 = mph_stdlib_codegen_is_digit(ctx, NULL, _arg_604); mph_gc_pop_roots(ctx, 1); _ret_605; })) || mph_string_eq(ctx, ch, mph_string_new(ctx, "_")))) {
{
	result = ({ MorphString* _lhs_606 = result; MorphString* _rhs_607 = ch; mph_gc_push_root(ctx, (void**)&_lhs_606); mph_gc_push_root(ctx, (void**)&_rhs_607); MorphString* _ret_608 = mph_string_concat(ctx, _lhs_606, _rhs_607); mph_gc_pop_roots(ctx, 2); _ret_608; });
}
	} else {
{
	result = ({ MorphString* _lhs_609 = result; MorphString* _rhs_610 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_609); mph_gc_push_root(ctx, (void**)&_rhs_610); MorphString* _ret_611 = mph_string_concat(ctx, _lhs_609, _rhs_610); mph_gc_pop_roots(ctx, 2); _ret_611; });
}
	}
}
	}
	i = (i + 1);
	mph_gc_pop_roots(ctx, 1);
}
	}
	result = ({ MorphString* _lhs_612 = result; MorphString* _rhs_613 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_612); mph_gc_push_root(ctx, (void**)&_rhs_613); MorphString* _ret_614 = mph_string_concat(ctx, _lhs_612, _rhs_613); mph_gc_pop_roots(ctx, 2); _ret_614; });
	return result;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_IntToString(MorphContext* ctx, void* _env_void, mph_int n) {
	return mph_stdlib_codegen_int_to_string(ctx, NULL, n);
}

MorphString* mph_stdlib_codegen_StringEscape(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	return ({ MorphString* _arg_615 = s; mph_gc_push_root(ctx, (void**)&_arg_615); MorphString* _ret_616 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_615); mph_gc_pop_roots(ctx, 1); _ret_616; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_stdlib_codegen_IsValidCIdent(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	return ({ MorphString* _arg_617 = name; mph_gc_push_root(ctx, (void**)&_arg_617); mph_bool _ret_618 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_617); mph_gc_pop_roots(ctx, 1); _ret_618; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_ModuleToPrefix(MorphContext* ctx, void* _env_void, MorphString* path) {
	mph_gc_push_root(ctx, (void**)&path);
	return ({ MorphString* _arg_619 = path; mph_gc_push_root(ctx, (void**)&_arg_619); MorphString* _ret_620 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_619); mph_gc_pop_roots(ctx, 1); _ret_620; });
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
	MorphString* e1 = ({ MorphString* _arg_621 = mph_string_new(ctx, "hello"); mph_gc_push_root(ctx, (void**)&_arg_621); MorphString* _ret_622 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_621); mph_gc_pop_roots(ctx, 1); _ret_622; });
	mph_gc_push_root(ctx, (void**)&e1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\" â \""));
	mph_native_print(ctx, e1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* e2 = ({ MorphString* _arg_623 = mph_string_new(ctx, "hello\nworld"); mph_gc_push_root(ctx, (void**)&_arg_623); MorphString* _ret_624 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_623); mph_gc_pop_roots(ctx, 1); _ret_624; });
	mph_gc_push_root(ctx, (void**)&e2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\\nworld\" â \""));
	mph_native_print(ctx, e2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 3] module_to_prefix()\n"));
	MorphString* p1 = ({ MorphString* _arg_625 = mph_string_new(ctx, "token"); mph_gc_push_root(ctx, (void**)&_arg_625); MorphString* _ret_626 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_625); mph_gc_pop_roots(ctx, 1); _ret_626; });
	mph_gc_push_root(ctx, (void**)&p1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"token\" â \""));
	mph_native_print(ctx, p1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* p2 = ({ MorphString* _arg_627 = mph_string_new(ctx, "std/string"); mph_gc_push_root(ctx, (void**)&_arg_627); MorphString* _ret_628 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_627); mph_gc_pop_roots(ctx, 1); _ret_628; });
	mph_gc_push_root(ctx, (void**)&p2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"std/string\" â \""));
	mph_native_print(ctx, p2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 4] is_valid_c_ident()\n"));
	mph_bool v1 = ({ MorphString* _arg_629 = mph_string_new(ctx, "foo"); mph_gc_push_root(ctx, (void**)&_arg_629); mph_bool _ret_630 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_629); mph_gc_pop_roots(ctx, 1); _ret_630; });
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
	mph_bool v2 = ({ MorphString* _arg_631 = mph_string_new(ctx, "_bar123"); mph_gc_push_root(ctx, (void**)&_arg_631); mph_bool _ret_632 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_631); mph_gc_pop_roots(ctx, 1); _ret_632; });
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
	mph_bool v3 = ({ MorphString* _arg_633 = mph_string_new(ctx, "123bad"); mph_gc_push_root(ctx, (void**)&_arg_633); mph_bool _ret_634 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_633); mph_gc_pop_roots(ctx, 1); _ret_634; });
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

mph_codegen_Codegen* mph_codegen_new_codegen(MorphContext* ctx, void* _env_void) {
	return ({ mph_codegen_Codegen* _t = (mph_codegen_Codegen*)mph_alloc(ctx, sizeof(mph_codegen_Codegen), &mph_ti_mph_codegen_Codegen); mph_gc_push_root(ctx, (void**)&_t); _t->type_defs = mph_string_new(ctx, ""); _t->global_defs = mph_string_new(ctx, ""); _t->indent_level = 0; _t->current_prefix = mph_string_new(ctx, "mph_"); _t->output = mph_string_new(ctx, ""); _t->prototypes = mph_string_new(ctx, ""); _t->func_defs = mph_string_new(ctx, ""); _t->entry_body = mph_string_new(ctx, ""); _t->pass_log = mph_string_new(ctx, ""); _t->temp_index = 0; _t->has_main = 0; mph_gc_pop_roots(ctx, 1); _t; });
}

MorphString* mph_codegen_codegen_compile(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_codegen_Codegen* _obj_635 = cg; mph_gc_push_root(ctx, (void**)&_obj_635); MorphString* _val_636 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_636); _obj_635->output = _val_636; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_637 = cg; mph_gc_push_root(ctx, (void**)&_obj_637); MorphString* _val_638 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_638); _obj_637->type_defs = _val_638; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_639 = cg; mph_gc_push_root(ctx, (void**)&_obj_639); MorphString* _val_640 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_640); _obj_639->global_defs = _val_640; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_641 = cg; mph_gc_push_root(ctx, (void**)&_obj_641); MorphString* _val_642 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_642); _obj_641->prototypes = _val_642; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_643 = cg; mph_gc_push_root(ctx, (void**)&_obj_643); MorphString* _val_644 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_644); _obj_643->func_defs = _val_644; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_645 = cg; mph_gc_push_root(ctx, (void**)&_obj_645); MorphString* _val_646 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_646); _obj_645->entry_body = _val_646; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_647 = cg; mph_gc_push_root(ctx, (void**)&_obj_647); MorphString* _val_648 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_648); _obj_647->pass_log = _val_648; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_649 = cg; mph_gc_push_root(ctx, (void**)&_obj_649); _obj_649->temp_index = 0; mph_gc_pop_roots(ctx, 1); });
	({ mph_codegen_Codegen* _obj_650 = cg; mph_gc_push_root(ctx, (void**)&_obj_650); _obj_650->has_main = 0; mph_gc_pop_roots(ctx, 1); });
	({ mph_codegen_Codegen* _obj_656 = cg; mph_gc_push_root(ctx, (void**)&_obj_656); MorphString* _val_657 = ({ MorphString* _lhs_653 = ({ mph_codegen_Codegen* _obj_651 = cg; mph_gc_push_root(ctx, (void**)&_obj_651); MorphString* _ret_652 = _obj_651->output; mph_gc_pop_roots(ctx, 1); _ret_652; }); MorphString* _rhs_654 = mph_string_new(ctx, "#include \"morph.h\"\n\n"); mph_gc_push_root(ctx, (void**)&_lhs_653); mph_gc_push_root(ctx, (void**)&_rhs_654); MorphString* _ret_655 = mph_string_concat(ctx, _lhs_653, _rhs_654); mph_gc_pop_roots(ctx, 2); _ret_655; }); mph_gc_push_root(ctx, (void**)&_val_657); _obj_656->output = _val_657; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_663 = cg; mph_gc_push_root(ctx, (void**)&_obj_663); MorphString* _val_664 = ({ MorphString* _lhs_660 = ({ mph_codegen_Codegen* _obj_658 = cg; mph_gc_push_root(ctx, (void**)&_obj_658); MorphString* _ret_659 = _obj_658->output; mph_gc_pop_roots(ctx, 1); _ret_659; }); MorphString* _rhs_661 = mph_string_new(ctx, "// Native bindings\n"); mph_gc_push_root(ctx, (void**)&_lhs_660); mph_gc_push_root(ctx, (void**)&_rhs_661); MorphString* _ret_662 = mph_string_concat(ctx, _lhs_660, _rhs_661); mph_gc_pop_roots(ctx, 2); _ret_662; }); mph_gc_push_root(ctx, (void**)&_val_664); _obj_663->output = _val_664; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_670 = cg; mph_gc_push_root(ctx, (void**)&_obj_670); MorphString* _val_671 = ({ MorphString* _lhs_667 = ({ mph_codegen_Codegen* _obj_665 = cg; mph_gc_push_root(ctx, (void**)&_obj_665); MorphString* _ret_666 = _obj_665->output; mph_gc_pop_roots(ctx, 1); _ret_666; }); MorphString* _rhs_668 = mph_string_new(ctx, "void mph_native_print(MorphContext* ctx, MorphString* s);\n"); mph_gc_push_root(ctx, (void**)&_lhs_667); mph_gc_push_root(ctx, (void**)&_rhs_668); MorphString* _ret_669 = mph_string_concat(ctx, _lhs_667, _rhs_668); mph_gc_pop_roots(ctx, 2); _ret_669; }); mph_gc_push_root(ctx, (void**)&_val_671); _obj_670->output = _val_671; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_677 = cg; mph_gc_push_root(ctx, (void**)&_obj_677); MorphString* _val_678 = ({ MorphString* _lhs_674 = ({ mph_codegen_Codegen* _obj_672 = cg; mph_gc_push_root(ctx, (void**)&_obj_672); MorphString* _ret_673 = _obj_672->output; mph_gc_pop_roots(ctx, 1); _ret_673; }); MorphString* _rhs_675 = mph_string_new(ctx, "void mph_native_print_int(MorphContext* ctx, mph_int n);\n"); mph_gc_push_root(ctx, (void**)&_lhs_674); mph_gc_push_root(ctx, (void**)&_rhs_675); MorphString* _ret_676 = mph_string_concat(ctx, _lhs_674, _rhs_675); mph_gc_pop_roots(ctx, 2); _ret_676; }); mph_gc_push_root(ctx, (void**)&_val_678); _obj_677->output = _val_678; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_684 = cg; mph_gc_push_root(ctx, (void**)&_obj_684); MorphString* _val_685 = ({ MorphString* _lhs_681 = ({ mph_codegen_Codegen* _obj_679 = cg; mph_gc_push_root(ctx, (void**)&_obj_679); MorphString* _ret_680 = _obj_679->output; mph_gc_pop_roots(ctx, 1); _ret_680; }); MorphString* _rhs_682 = mph_string_new(ctx, "void mph_native_print_error(MorphContext* ctx, MorphError* err);\n"); mph_gc_push_root(ctx, (void**)&_lhs_681); mph_gc_push_root(ctx, (void**)&_rhs_682); MorphString* _ret_683 = mph_string_concat(ctx, _lhs_681, _rhs_682); mph_gc_pop_roots(ctx, 2); _ret_683; }); mph_gc_push_root(ctx, (void**)&_val_685); _obj_684->output = _val_685; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_691 = cg; mph_gc_push_root(ctx, (void**)&_obj_691); MorphString* _val_692 = ({ MorphString* _lhs_688 = ({ mph_codegen_Codegen* _obj_686 = cg; mph_gc_push_root(ctx, (void**)&_obj_686); MorphString* _ret_687 = _obj_686->output; mph_gc_pop_roots(ctx, 1); _ret_687; }); MorphString* _rhs_689 = mph_string_new(ctx, "mph_int mph_string_index(MorphContext* ctx, MorphString* s, MorphString* sub);\n"); mph_gc_push_root(ctx, (void**)&_lhs_688); mph_gc_push_root(ctx, (void**)&_rhs_689); MorphString* _ret_690 = mph_string_concat(ctx, _lhs_688, _rhs_689); mph_gc_pop_roots(ctx, 2); _ret_690; }); mph_gc_push_root(ctx, (void**)&_val_692); _obj_691->output = _val_692; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_698 = cg; mph_gc_push_root(ctx, (void**)&_obj_698); MorphString* _val_699 = ({ MorphString* _lhs_695 = ({ mph_codegen_Codegen* _obj_693 = cg; mph_gc_push_root(ctx, (void**)&_obj_693); MorphString* _ret_694 = _obj_693->output; mph_gc_pop_roots(ctx, 1); _ret_694; }); MorphString* _rhs_696 = mph_string_new(ctx, "MorphString* mph_string_trim(MorphContext* ctx, MorphString* s, MorphString* cut);\n"); mph_gc_push_root(ctx, (void**)&_lhs_695); mph_gc_push_root(ctx, (void**)&_rhs_696); MorphString* _ret_697 = mph_string_concat(ctx, _lhs_695, _rhs_696); mph_gc_pop_roots(ctx, 2); _ret_697; }); mph_gc_push_root(ctx, (void**)&_val_699); _obj_698->output = _val_699; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_705 = cg; mph_gc_push_root(ctx, (void**)&_obj_705); MorphString* _val_706 = ({ MorphString* _lhs_702 = ({ mph_codegen_Codegen* _obj_700 = cg; mph_gc_push_root(ctx, (void**)&_obj_700); MorphString* _ret_701 = _obj_700->output; mph_gc_pop_roots(ctx, 1); _ret_701; }); MorphString* _rhs_703 = mph_string_new(ctx, "MorphArray* mph_string_split(MorphContext* ctx, MorphString* s, MorphString* sep);\n"); mph_gc_push_root(ctx, (void**)&_lhs_702); mph_gc_push_root(ctx, (void**)&_rhs_703); MorphString* _ret_704 = mph_string_concat(ctx, _lhs_702, _rhs_703); mph_gc_pop_roots(ctx, 2); _ret_704; }); mph_gc_push_root(ctx, (void**)&_val_706); _obj_705->output = _val_706; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_712 = cg; mph_gc_push_root(ctx, (void**)&_obj_712); MorphString* _val_713 = ({ MorphString* _lhs_709 = ({ mph_codegen_Codegen* _obj_707 = cg; mph_gc_push_root(ctx, (void**)&_obj_707); MorphString* _ret_708 = _obj_707->output; mph_gc_pop_roots(ctx, 1); _ret_708; }); MorphString* _rhs_710 = mph_string_new(ctx, "MorphString* mph_string_substring(MorphContext* ctx, MorphString* s, mph_int start, mph_int end);\n"); mph_gc_push_root(ctx, (void**)&_lhs_709); mph_gc_push_root(ctx, (void**)&_rhs_710); MorphString* _ret_711 = mph_string_concat(ctx, _lhs_709, _rhs_710); mph_gc_pop_roots(ctx, 2); _ret_711; }); mph_gc_push_root(ctx, (void**)&_val_713); _obj_712->output = _val_713; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_719 = cg; mph_gc_push_root(ctx, (void**)&_obj_719); MorphString* _val_720 = ({ MorphString* _lhs_716 = ({ mph_codegen_Codegen* _obj_714 = cg; mph_gc_push_root(ctx, (void**)&_obj_714); MorphString* _ret_715 = _obj_714->output; mph_gc_pop_roots(ctx, 1); _ret_715; }); MorphString* _rhs_717 = mph_string_new(ctx, "MorphError* mph_error_new(MorphContext* ctx, MorphString* msg);\n\n"); mph_gc_push_root(ctx, (void**)&_lhs_716); mph_gc_push_root(ctx, (void**)&_rhs_717); MorphString* _ret_718 = mph_string_concat(ctx, _lhs_716, _rhs_717); mph_gc_pop_roots(ctx, 2); _ret_718; }); mph_gc_push_root(ctx, (void**)&_val_720); _obj_719->output = _val_720; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _arg_721 = cg; mph_gc_push_root(ctx, (void**)&_arg_721); mph_ast_Program* _arg_722 = prog; mph_gc_push_root(ctx, (void**)&_arg_722); mph_codegen_codegen_pass_collect_globals(ctx, NULL, _arg_721, _arg_722); mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _arg_723 = cg; mph_gc_push_root(ctx, (void**)&_arg_723); mph_ast_Program* _arg_724 = prog; mph_gc_push_root(ctx, (void**)&_arg_724); mph_codegen_codegen_pass_analyze_captures(ctx, NULL, _arg_723, _arg_724); mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _arg_725 = cg; mph_gc_push_root(ctx, (void**)&_arg_725); mph_ast_Program* _arg_726 = prog; mph_gc_push_root(ctx, (void**)&_arg_726); mph_codegen_codegen_pass_compile_struct_types(ctx, NULL, _arg_725, _arg_726); mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _arg_727 = cg; mph_gc_push_root(ctx, (void**)&_arg_727); mph_ast_Program* _arg_728 = prog; mph_gc_push_root(ctx, (void**)&_arg_728); mph_codegen_codegen_pass_compile_struct_rtti(ctx, NULL, _arg_727, _arg_728); mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _arg_729 = cg; mph_gc_push_root(ctx, (void**)&_arg_729); mph_ast_Program* _arg_730 = prog; mph_gc_push_root(ctx, (void**)&_arg_730); MorphString* _arg_731 = mph_string_new(ctx, "mph_"); mph_gc_push_root(ctx, (void**)&_arg_731); mph_codegen_codegen_pass_compile_module(ctx, NULL, _arg_729, _arg_730, _arg_731); mph_gc_pop_roots(ctx, 3); });
	({ mph_codegen_Codegen* _obj_737 = cg; mph_gc_push_root(ctx, (void**)&_obj_737); MorphString* _val_738 = ({ MorphString* _lhs_734 = ({ mph_codegen_Codegen* _obj_732 = cg; mph_gc_push_root(ctx, (void**)&_obj_732); MorphString* _ret_733 = _obj_732->output; mph_gc_pop_roots(ctx, 1); _ret_733; }); MorphString* _rhs_735 = mph_string_new(ctx, "// Pass Log\n"); mph_gc_push_root(ctx, (void**)&_lhs_734); mph_gc_push_root(ctx, (void**)&_rhs_735); MorphString* _ret_736 = mph_string_concat(ctx, _lhs_734, _rhs_735); mph_gc_pop_roots(ctx, 2); _ret_736; }); mph_gc_push_root(ctx, (void**)&_val_738); _obj_737->output = _val_738; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_746 = cg; mph_gc_push_root(ctx, (void**)&_obj_746); MorphString* _val_747 = ({ MorphString* _lhs_743 = ({ mph_codegen_Codegen* _obj_739 = cg; mph_gc_push_root(ctx, (void**)&_obj_739); MorphString* _ret_740 = _obj_739->output; mph_gc_pop_roots(ctx, 1); _ret_740; }); MorphString* _rhs_744 = ({ mph_codegen_Codegen* _obj_741 = cg; mph_gc_push_root(ctx, (void**)&_obj_741); MorphString* _ret_742 = _obj_741->pass_log; mph_gc_pop_roots(ctx, 1); _ret_742; }); mph_gc_push_root(ctx, (void**)&_lhs_743); mph_gc_push_root(ctx, (void**)&_rhs_744); MorphString* _ret_745 = mph_string_concat(ctx, _lhs_743, _rhs_744); mph_gc_pop_roots(ctx, 2); _ret_745; }); mph_gc_push_root(ctx, (void**)&_val_747); _obj_746->output = _val_747; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_753 = cg; mph_gc_push_root(ctx, (void**)&_obj_753); MorphString* _val_754 = ({ MorphString* _lhs_750 = ({ mph_codegen_Codegen* _obj_748 = cg; mph_gc_push_root(ctx, (void**)&_obj_748); MorphString* _ret_749 = _obj_748->output; mph_gc_pop_roots(ctx, 1); _ret_749; }); MorphString* _rhs_751 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_750); mph_gc_push_root(ctx, (void**)&_rhs_751); MorphString* _ret_752 = mph_string_concat(ctx, _lhs_750, _rhs_751); mph_gc_pop_roots(ctx, 2); _ret_752; }); mph_gc_push_root(ctx, (void**)&_val_754); _obj_753->output = _val_754; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_760 = cg; mph_gc_push_root(ctx, (void**)&_obj_760); MorphString* _val_761 = ({ MorphString* _lhs_757 = ({ mph_codegen_Codegen* _obj_755 = cg; mph_gc_push_root(ctx, (void**)&_obj_755); MorphString* _ret_756 = _obj_755->output; mph_gc_pop_roots(ctx, 1); _ret_756; }); MorphString* _rhs_758 = mph_string_new(ctx, "// Type Definitions\n"); mph_gc_push_root(ctx, (void**)&_lhs_757); mph_gc_push_root(ctx, (void**)&_rhs_758); MorphString* _ret_759 = mph_string_concat(ctx, _lhs_757, _rhs_758); mph_gc_pop_roots(ctx, 2); _ret_759; }); mph_gc_push_root(ctx, (void**)&_val_761); _obj_760->output = _val_761; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_769 = cg; mph_gc_push_root(ctx, (void**)&_obj_769); MorphString* _val_770 = ({ MorphString* _lhs_766 = ({ mph_codegen_Codegen* _obj_762 = cg; mph_gc_push_root(ctx, (void**)&_obj_762); MorphString* _ret_763 = _obj_762->output; mph_gc_pop_roots(ctx, 1); _ret_763; }); MorphString* _rhs_767 = ({ mph_codegen_Codegen* _obj_764 = cg; mph_gc_push_root(ctx, (void**)&_obj_764); MorphString* _ret_765 = _obj_764->type_defs; mph_gc_pop_roots(ctx, 1); _ret_765; }); mph_gc_push_root(ctx, (void**)&_lhs_766); mph_gc_push_root(ctx, (void**)&_rhs_767); MorphString* _ret_768 = mph_string_concat(ctx, _lhs_766, _rhs_767); mph_gc_pop_roots(ctx, 2); _ret_768; }); mph_gc_push_root(ctx, (void**)&_val_770); _obj_769->output = _val_770; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_776 = cg; mph_gc_push_root(ctx, (void**)&_obj_776); MorphString* _val_777 = ({ MorphString* _lhs_773 = ({ mph_codegen_Codegen* _obj_771 = cg; mph_gc_push_root(ctx, (void**)&_obj_771); MorphString* _ret_772 = _obj_771->output; mph_gc_pop_roots(ctx, 1); _ret_772; }); MorphString* _rhs_774 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_773); mph_gc_push_root(ctx, (void**)&_rhs_774); MorphString* _ret_775 = mph_string_concat(ctx, _lhs_773, _rhs_774); mph_gc_pop_roots(ctx, 2); _ret_775; }); mph_gc_push_root(ctx, (void**)&_val_777); _obj_776->output = _val_777; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_783 = cg; mph_gc_push_root(ctx, (void**)&_obj_783); MorphString* _val_784 = ({ MorphString* _lhs_780 = ({ mph_codegen_Codegen* _obj_778 = cg; mph_gc_push_root(ctx, (void**)&_obj_778); MorphString* _ret_779 = _obj_778->output; mph_gc_pop_roots(ctx, 1); _ret_779; }); MorphString* _rhs_781 = mph_string_new(ctx, "// Global Variables\n"); mph_gc_push_root(ctx, (void**)&_lhs_780); mph_gc_push_root(ctx, (void**)&_rhs_781); MorphString* _ret_782 = mph_string_concat(ctx, _lhs_780, _rhs_781); mph_gc_pop_roots(ctx, 2); _ret_782; }); mph_gc_push_root(ctx, (void**)&_val_784); _obj_783->output = _val_784; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_792 = cg; mph_gc_push_root(ctx, (void**)&_obj_792); MorphString* _val_793 = ({ MorphString* _lhs_789 = ({ mph_codegen_Codegen* _obj_785 = cg; mph_gc_push_root(ctx, (void**)&_obj_785); MorphString* _ret_786 = _obj_785->output; mph_gc_pop_roots(ctx, 1); _ret_786; }); MorphString* _rhs_790 = ({ mph_codegen_Codegen* _obj_787 = cg; mph_gc_push_root(ctx, (void**)&_obj_787); MorphString* _ret_788 = _obj_787->global_defs; mph_gc_pop_roots(ctx, 1); _ret_788; }); mph_gc_push_root(ctx, (void**)&_lhs_789); mph_gc_push_root(ctx, (void**)&_rhs_790); MorphString* _ret_791 = mph_string_concat(ctx, _lhs_789, _rhs_790); mph_gc_pop_roots(ctx, 2); _ret_791; }); mph_gc_push_root(ctx, (void**)&_val_793); _obj_792->output = _val_793; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_799 = cg; mph_gc_push_root(ctx, (void**)&_obj_799); MorphString* _val_800 = ({ MorphString* _lhs_796 = ({ mph_codegen_Codegen* _obj_794 = cg; mph_gc_push_root(ctx, (void**)&_obj_794); MorphString* _ret_795 = _obj_794->output; mph_gc_pop_roots(ctx, 1); _ret_795; }); MorphString* _rhs_797 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_796); mph_gc_push_root(ctx, (void**)&_rhs_797); MorphString* _ret_798 = mph_string_concat(ctx, _lhs_796, _rhs_797); mph_gc_pop_roots(ctx, 2); _ret_798; }); mph_gc_push_root(ctx, (void**)&_val_800); _obj_799->output = _val_800; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_806 = cg; mph_gc_push_root(ctx, (void**)&_obj_806); MorphString* _val_807 = ({ MorphString* _lhs_803 = ({ mph_codegen_Codegen* _obj_801 = cg; mph_gc_push_root(ctx, (void**)&_obj_801); MorphString* _ret_802 = _obj_801->output; mph_gc_pop_roots(ctx, 1); _ret_802; }); MorphString* _rhs_804 = mph_string_new(ctx, "// Function Prototypes\n"); mph_gc_push_root(ctx, (void**)&_lhs_803); mph_gc_push_root(ctx, (void**)&_rhs_804); MorphString* _ret_805 = mph_string_concat(ctx, _lhs_803, _rhs_804); mph_gc_pop_roots(ctx, 2); _ret_805; }); mph_gc_push_root(ctx, (void**)&_val_807); _obj_806->output = _val_807; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_815 = cg; mph_gc_push_root(ctx, (void**)&_obj_815); MorphString* _val_816 = ({ MorphString* _lhs_812 = ({ mph_codegen_Codegen* _obj_808 = cg; mph_gc_push_root(ctx, (void**)&_obj_808); MorphString* _ret_809 = _obj_808->output; mph_gc_pop_roots(ctx, 1); _ret_809; }); MorphString* _rhs_813 = ({ mph_codegen_Codegen* _obj_810 = cg; mph_gc_push_root(ctx, (void**)&_obj_810); MorphString* _ret_811 = _obj_810->prototypes; mph_gc_pop_roots(ctx, 1); _ret_811; }); mph_gc_push_root(ctx, (void**)&_lhs_812); mph_gc_push_root(ctx, (void**)&_rhs_813); MorphString* _ret_814 = mph_string_concat(ctx, _lhs_812, _rhs_813); mph_gc_pop_roots(ctx, 2); _ret_814; }); mph_gc_push_root(ctx, (void**)&_val_816); _obj_815->output = _val_816; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_822 = cg; mph_gc_push_root(ctx, (void**)&_obj_822); MorphString* _val_823 = ({ MorphString* _lhs_819 = ({ mph_codegen_Codegen* _obj_817 = cg; mph_gc_push_root(ctx, (void**)&_obj_817); MorphString* _ret_818 = _obj_817->output; mph_gc_pop_roots(ctx, 1); _ret_818; }); MorphString* _rhs_820 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_819); mph_gc_push_root(ctx, (void**)&_rhs_820); MorphString* _ret_821 = mph_string_concat(ctx, _lhs_819, _rhs_820); mph_gc_pop_roots(ctx, 2); _ret_821; }); mph_gc_push_root(ctx, (void**)&_val_823); _obj_822->output = _val_823; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_829 = cg; mph_gc_push_root(ctx, (void**)&_obj_829); MorphString* _val_830 = ({ MorphString* _lhs_826 = ({ mph_codegen_Codegen* _obj_824 = cg; mph_gc_push_root(ctx, (void**)&_obj_824); MorphString* _ret_825 = _obj_824->output; mph_gc_pop_roots(ctx, 1); _ret_825; }); MorphString* _rhs_827 = mph_string_new(ctx, "// Function Definitions\n"); mph_gc_push_root(ctx, (void**)&_lhs_826); mph_gc_push_root(ctx, (void**)&_rhs_827); MorphString* _ret_828 = mph_string_concat(ctx, _lhs_826, _rhs_827); mph_gc_pop_roots(ctx, 2); _ret_828; }); mph_gc_push_root(ctx, (void**)&_val_830); _obj_829->output = _val_830; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_838 = cg; mph_gc_push_root(ctx, (void**)&_obj_838); MorphString* _val_839 = ({ MorphString* _lhs_835 = ({ mph_codegen_Codegen* _obj_831 = cg; mph_gc_push_root(ctx, (void**)&_obj_831); MorphString* _ret_832 = _obj_831->output; mph_gc_pop_roots(ctx, 1); _ret_832; }); MorphString* _rhs_836 = ({ mph_codegen_Codegen* _obj_833 = cg; mph_gc_push_root(ctx, (void**)&_obj_833); MorphString* _ret_834 = _obj_833->func_defs; mph_gc_pop_roots(ctx, 1); _ret_834; }); mph_gc_push_root(ctx, (void**)&_lhs_835); mph_gc_push_root(ctx, (void**)&_rhs_836); MorphString* _ret_837 = mph_string_concat(ctx, _lhs_835, _rhs_836); mph_gc_pop_roots(ctx, 2); _ret_837; }); mph_gc_push_root(ctx, (void**)&_val_839); _obj_838->output = _val_839; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_845 = cg; mph_gc_push_root(ctx, (void**)&_obj_845); MorphString* _val_846 = ({ MorphString* _lhs_842 = ({ mph_codegen_Codegen* _obj_840 = cg; mph_gc_push_root(ctx, (void**)&_obj_840); MorphString* _ret_841 = _obj_840->output; mph_gc_pop_roots(ctx, 1); _ret_841; }); MorphString* _rhs_843 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_842); mph_gc_push_root(ctx, (void**)&_rhs_843); MorphString* _ret_844 = mph_string_concat(ctx, _lhs_842, _rhs_843); mph_gc_pop_roots(ctx, 2); _ret_844; }); mph_gc_push_root(ctx, (void**)&_val_846); _obj_845->output = _val_846; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_852 = cg; mph_gc_push_root(ctx, (void**)&_obj_852); MorphString* _val_853 = ({ MorphString* _lhs_849 = ({ mph_codegen_Codegen* _obj_847 = cg; mph_gc_push_root(ctx, (void**)&_obj_847); MorphString* _ret_848 = _obj_847->output; mph_gc_pop_roots(ctx, 1); _ret_848; }); MorphString* _rhs_850 = mph_string_new(ctx, "// Entry Point\n"); mph_gc_push_root(ctx, (void**)&_lhs_849); mph_gc_push_root(ctx, (void**)&_rhs_850); MorphString* _ret_851 = mph_string_concat(ctx, _lhs_849, _rhs_850); mph_gc_pop_roots(ctx, 2); _ret_851; }); mph_gc_push_root(ctx, (void**)&_val_853); _obj_852->output = _val_853; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_859 = cg; mph_gc_push_root(ctx, (void**)&_obj_859); MorphString* _val_860 = ({ MorphString* _lhs_856 = ({ mph_codegen_Codegen* _obj_854 = cg; mph_gc_push_root(ctx, (void**)&_obj_854); MorphString* _ret_855 = _obj_854->output; mph_gc_pop_roots(ctx, 1); _ret_855; }); MorphString* _rhs_857 = mph_string_new(ctx, "void morph_entry_point(MorphContext* ctx) {\n"); mph_gc_push_root(ctx, (void**)&_lhs_856); mph_gc_push_root(ctx, (void**)&_rhs_857); MorphString* _ret_858 = mph_string_concat(ctx, _lhs_856, _rhs_857); mph_gc_pop_roots(ctx, 2); _ret_858; }); mph_gc_push_root(ctx, (void**)&_val_860); _obj_859->output = _val_860; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_868 = cg; mph_gc_push_root(ctx, (void**)&_obj_868); MorphString* _val_869 = ({ MorphString* _lhs_865 = ({ mph_codegen_Codegen* _obj_861 = cg; mph_gc_push_root(ctx, (void**)&_obj_861); MorphString* _ret_862 = _obj_861->output; mph_gc_pop_roots(ctx, 1); _ret_862; }); MorphString* _rhs_866 = ({ mph_codegen_Codegen* _obj_863 = cg; mph_gc_push_root(ctx, (void**)&_obj_863); MorphString* _ret_864 = _obj_863->entry_body; mph_gc_pop_roots(ctx, 1); _ret_864; }); mph_gc_push_root(ctx, (void**)&_lhs_865); mph_gc_push_root(ctx, (void**)&_rhs_866); MorphString* _ret_867 = mph_string_concat(ctx, _lhs_865, _rhs_866); mph_gc_pop_roots(ctx, 2); _ret_867; }); mph_gc_push_root(ctx, (void**)&_val_869); _obj_868->output = _val_869; mph_gc_pop_roots(ctx, 2); });
	if (({ mph_codegen_Codegen* _obj_870 = cg; mph_gc_push_root(ctx, (void**)&_obj_870); mph_bool _ret_871 = _obj_870->has_main; mph_gc_pop_roots(ctx, 1); _ret_871; })) {
{
	({ mph_codegen_Codegen* _obj_877 = cg; mph_gc_push_root(ctx, (void**)&_obj_877); MorphString* _val_878 = ({ MorphString* _lhs_874 = ({ mph_codegen_Codegen* _obj_872 = cg; mph_gc_push_root(ctx, (void**)&_obj_872); MorphString* _ret_873 = _obj_872->output; mph_gc_pop_roots(ctx, 1); _ret_873; }); MorphString* _rhs_875 = mph_string_new(ctx, "\tmph_main(ctx, NULL);\n"); mph_gc_push_root(ctx, (void**)&_lhs_874); mph_gc_push_root(ctx, (void**)&_rhs_875); MorphString* _ret_876 = mph_string_concat(ctx, _lhs_874, _rhs_875); mph_gc_pop_roots(ctx, 2); _ret_876; }); mph_gc_push_root(ctx, (void**)&_val_878); _obj_877->output = _val_878; mph_gc_pop_roots(ctx, 2); });
}
	}
	({ mph_codegen_Codegen* _obj_884 = cg; mph_gc_push_root(ctx, (void**)&_obj_884); MorphString* _val_885 = ({ MorphString* _lhs_881 = ({ mph_codegen_Codegen* _obj_879 = cg; mph_gc_push_root(ctx, (void**)&_obj_879); MorphString* _ret_880 = _obj_879->output; mph_gc_pop_roots(ctx, 1); _ret_880; }); MorphString* _rhs_882 = mph_string_new(ctx, "}\n"); mph_gc_push_root(ctx, (void**)&_lhs_881); mph_gc_push_root(ctx, (void**)&_rhs_882); MorphString* _ret_883 = mph_string_concat(ctx, _lhs_881, _rhs_882); mph_gc_pop_roots(ctx, 2); _ret_883; }); mph_gc_push_root(ctx, (void**)&_val_885); _obj_884->output = _val_885; mph_gc_pop_roots(ctx, 2); });
	return ({ mph_codegen_Codegen* _obj_886 = cg; mph_gc_push_root(ctx, (void**)&_obj_886); MorphString* _ret_887 = _obj_886->output; mph_gc_pop_roots(ctx, 1); _ret_887; });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_codegen_record_pass(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&name);
	({ mph_codegen_Codegen* _obj_899 = cg; mph_gc_push_root(ctx, (void**)&_obj_899); MorphString* _val_900 = ({ MorphString* _lhs_896 = ({ MorphString* _lhs_893 = ({ MorphString* _lhs_890 = ({ mph_codegen_Codegen* _obj_888 = cg; mph_gc_push_root(ctx, (void**)&_obj_888); MorphString* _ret_889 = _obj_888->pass_log; mph_gc_pop_roots(ctx, 1); _ret_889; }); MorphString* _rhs_891 = mph_string_new(ctx, "// "); mph_gc_push_root(ctx, (void**)&_lhs_890); mph_gc_push_root(ctx, (void**)&_rhs_891); MorphString* _ret_892 = mph_string_concat(ctx, _lhs_890, _rhs_891); mph_gc_pop_roots(ctx, 2); _ret_892; }); MorphString* _rhs_894 = name; mph_gc_push_root(ctx, (void**)&_lhs_893); mph_gc_push_root(ctx, (void**)&_rhs_894); MorphString* _ret_895 = mph_string_concat(ctx, _lhs_893, _rhs_894); mph_gc_pop_roots(ctx, 2); _ret_895; }); MorphString* _rhs_897 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_896); mph_gc_push_root(ctx, (void**)&_rhs_897); MorphString* _ret_898 = mph_string_concat(ctx, _lhs_896, _rhs_897); mph_gc_pop_roots(ctx, 2); _ret_898; }); mph_gc_push_root(ctx, (void**)&_val_900); _obj_899->pass_log = _val_900; mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_codegen_pass_collect_globals(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_codegen_Codegen* _arg_901 = cg; mph_gc_push_root(ctx, (void**)&_arg_901); MorphString* _arg_902 = mph_string_new(ctx, "pass1_collect_globals"); mph_gc_push_root(ctx, (void**)&_arg_902); mph_codegen_codegen_record_pass(ctx, NULL, _arg_901, _arg_902); mph_gc_pop_roots(ctx, 2); });
	if (({ mph_ast_Program* _obj_903 = prog; mph_gc_push_root(ctx, (void**)&_obj_903); mph_bool _ret_904 = _obj_903->has_var_statement; mph_gc_pop_roots(ctx, 1); _ret_904; })) {
{
	({ mph_codegen_Codegen* _obj_914 = cg; mph_gc_push_root(ctx, (void**)&_obj_914); MorphString* _val_915 = ({ MorphString* _lhs_911 = ({ mph_codegen_Codegen* _obj_905 = cg; mph_gc_push_root(ctx, (void**)&_obj_905); MorphString* _ret_906 = _obj_905->global_defs; mph_gc_pop_roots(ctx, 1); _ret_906; }); MorphString* _rhs_912 = ({ mph_ast_VarStatement* _arg_909 = ({ mph_ast_Program* _obj_907 = prog; mph_gc_push_root(ctx, (void**)&_obj_907); mph_ast_VarStatement* _ret_908 = _obj_907->var_statement; mph_gc_pop_roots(ctx, 1); _ret_908; }); mph_gc_push_root(ctx, (void**)&_arg_909); MorphString* _ret_910 = mph_codegen_codegen_compile_global_var_declaration(ctx, NULL, _arg_909); mph_gc_pop_roots(ctx, 1); _ret_910; }); mph_gc_push_root(ctx, (void**)&_lhs_911); mph_gc_push_root(ctx, (void**)&_rhs_912); MorphString* _ret_913 = mph_string_concat(ctx, _lhs_911, _rhs_912); mph_gc_pop_roots(ctx, 2); _ret_913; }); mph_gc_push_root(ctx, (void**)&_val_915); _obj_914->global_defs = _val_915; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_925 = cg; mph_gc_push_root(ctx, (void**)&_obj_925); MorphString* _val_926 = ({ MorphString* _lhs_922 = ({ mph_codegen_Codegen* _obj_916 = cg; mph_gc_push_root(ctx, (void**)&_obj_916); MorphString* _ret_917 = _obj_916->entry_body; mph_gc_pop_roots(ctx, 1); _ret_917; }); MorphString* _rhs_923 = ({ mph_ast_VarStatement* _arg_920 = ({ mph_ast_Program* _obj_918 = prog; mph_gc_push_root(ctx, (void**)&_obj_918); mph_ast_VarStatement* _ret_919 = _obj_918->var_statement; mph_gc_pop_roots(ctx, 1); _ret_919; }); mph_gc_push_root(ctx, (void**)&_arg_920); MorphString* _ret_921 = mph_codegen_codegen_compile_global_var_initialization(ctx, NULL, _arg_920); mph_gc_pop_roots(ctx, 1); _ret_921; }); mph_gc_push_root(ctx, (void**)&_lhs_922); mph_gc_push_root(ctx, (void**)&_rhs_923); MorphString* _ret_924 = mph_string_concat(ctx, _lhs_922, _rhs_923); mph_gc_pop_roots(ctx, 2); _ret_924; }); mph_gc_push_root(ctx, (void**)&_val_926); _obj_925->entry_body = _val_926; mph_gc_pop_roots(ctx, 2); });
}
	}
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_codegen_pass_analyze_captures(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_codegen_Codegen* _arg_927 = cg; mph_gc_push_root(ctx, (void**)&_arg_927); MorphString* _arg_928 = mph_string_new(ctx, "pass2_analyze_captures"); mph_gc_push_root(ctx, (void**)&_arg_928); mph_codegen_codegen_record_pass(ctx, NULL, _arg_927, _arg_928); mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_codegen_pass_compile_struct_types(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_codegen_Codegen* _arg_929 = cg; mph_gc_push_root(ctx, (void**)&_arg_929); MorphString* _arg_930 = mph_string_new(ctx, "pass3_compile_struct_types"); mph_gc_push_root(ctx, (void**)&_arg_930); mph_codegen_codegen_record_pass(ctx, NULL, _arg_929, _arg_930); mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_codegen_pass_compile_struct_rtti(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_codegen_Codegen* _arg_931 = cg; mph_gc_push_root(ctx, (void**)&_arg_931); MorphString* _arg_932 = mph_string_new(ctx, "pass4_compile_struct_rtti"); mph_gc_push_root(ctx, (void**)&_arg_932); mph_codegen_codegen_record_pass(ctx, NULL, _arg_931, _arg_932); mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_codegen_pass_compile_module(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_codegen_Codegen* _arg_933 = cg; mph_gc_push_root(ctx, (void**)&_arg_933); MorphString* _arg_934 = mph_string_new(ctx, "pass5_compile_module"); mph_gc_push_root(ctx, (void**)&_arg_934); mph_codegen_codegen_record_pass(ctx, NULL, _arg_933, _arg_934); mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _arg_935 = cg; mph_gc_push_root(ctx, (void**)&_arg_935); mph_ast_Program* _arg_936 = prog; mph_gc_push_root(ctx, (void**)&_arg_936); MorphString* _arg_937 = prefix; mph_gc_push_root(ctx, (void**)&_arg_937); mph_codegen_codegen_compile_program(ctx, NULL, _arg_935, _arg_936, _arg_937); mph_gc_pop_roots(ctx, 3); });
	mph_gc_pop_roots(ctx, 3);
}

void mph_codegen_codegen_compile_program(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_codegen_Codegen* _obj_938 = cg; mph_gc_push_root(ctx, (void**)&_obj_938); MorphString* _val_939 = prefix; mph_gc_push_root(ctx, (void**)&_val_939); _obj_938->current_prefix = _val_939; mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_codegen_map_type_to_c(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	if ((({ mph_types_Type* _obj_940 = t; mph_gc_push_root(ctx, (void**)&_obj_940); mph_int _ret_941 = _obj_940->kind; mph_gc_pop_roots(ctx, 1); _ret_941; }) == mph_types_KIND_INT)) {
{
	return mph_string_new(ctx, "mph_int");
}
	}
	if ((({ mph_types_Type* _obj_942 = t; mph_gc_push_root(ctx, (void**)&_obj_942); mph_int _ret_943 = _obj_942->kind; mph_gc_pop_roots(ctx, 1); _ret_943; }) == mph_types_KIND_FLOAT)) {
{
	return mph_string_new(ctx, "mph_float");
}
	}
	if ((({ mph_types_Type* _obj_944 = t; mph_gc_push_root(ctx, (void**)&_obj_944); mph_int _ret_945 = _obj_944->kind; mph_gc_pop_roots(ctx, 1); _ret_945; }) == mph_types_KIND_STRING)) {
{
	return mph_string_new(ctx, "MorphString*");
}
	}
	if ((({ mph_types_Type* _obj_946 = t; mph_gc_push_root(ctx, (void**)&_obj_946); mph_int _ret_947 = _obj_946->kind; mph_gc_pop_roots(ctx, 1); _ret_947; }) == mph_types_KIND_BOOL)) {
{
	return mph_string_new(ctx, "mph_bool");
}
	}
	if ((({ mph_types_Type* _obj_948 = t; mph_gc_push_root(ctx, (void**)&_obj_948); mph_int _ret_949 = _obj_948->kind; mph_gc_pop_roots(ctx, 1); _ret_949; }) == mph_types_KIND_VOID)) {
{
	return mph_string_new(ctx, "void");
}
	}
	if ((({ mph_types_Type* _obj_950 = t; mph_gc_push_root(ctx, (void**)&_obj_950); mph_int _ret_951 = _obj_950->kind; mph_gc_pop_roots(ctx, 1); _ret_951; }) == mph_types_KIND_FUNCTION)) {
{
	return mph_string_new(ctx, "MorphClosure*");
}
	}
	if ((({ mph_types_Type* _obj_952 = t; mph_gc_push_root(ctx, (void**)&_obj_952); mph_int _ret_953 = _obj_952->kind; mph_gc_pop_roots(ctx, 1); _ret_953; }) == mph_types_KIND_STRUCT)) {
{
	if ((({ mph_types_Type* _obj_954 = t; mph_gc_push_root(ctx, (void**)&_obj_954); MorphString* _ret_955 = _obj_954->name; mph_gc_pop_roots(ctx, 1); _ret_955; }) != mph_string_new(ctx, ""))) {
{
	return ({ MorphString* _lhs_961 = ({ MorphString* _lhs_958 = mph_string_new(ctx, "mph_"); MorphString* _rhs_959 = ({ mph_types_Type* _obj_956 = t; mph_gc_push_root(ctx, (void**)&_obj_956); MorphString* _ret_957 = _obj_956->name; mph_gc_pop_roots(ctx, 1); _ret_957; }); mph_gc_push_root(ctx, (void**)&_lhs_958); mph_gc_push_root(ctx, (void**)&_rhs_959); MorphString* _ret_960 = mph_string_concat(ctx, _lhs_958, _rhs_959); mph_gc_pop_roots(ctx, 2); _ret_960; }); MorphString* _rhs_962 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_lhs_961); mph_gc_push_root(ctx, (void**)&_rhs_962); MorphString* _ret_963 = mph_string_concat(ctx, _lhs_961, _rhs_962); mph_gc_pop_roots(ctx, 2); _ret_963; });
}
	}
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_964 = t; mph_gc_push_root(ctx, (void**)&_obj_964); mph_int _ret_965 = _obj_964->kind; mph_gc_pop_roots(ctx, 1); _ret_965; }) == mph_types_KIND_INTERFACE)) {
{
	return mph_string_new(ctx, "MorphInterface");
}
	}
	if ((({ mph_types_Type* _obj_966 = t; mph_gc_push_root(ctx, (void**)&_obj_966); mph_int _ret_967 = _obj_966->kind; mph_gc_pop_roots(ctx, 1); _ret_967; }) == mph_types_KIND_ARRAY)) {
{
	return mph_string_new(ctx, "MorphArray*");
}
	}
	if ((({ mph_types_Type* _obj_968 = t; mph_gc_push_root(ctx, (void**)&_obj_968); mph_int _ret_969 = _obj_968->kind; mph_gc_pop_roots(ctx, 1); _ret_969; }) == mph_types_KIND_MAP)) {
{
	return mph_string_new(ctx, "MorphMap*");
}
	}
	if ((({ mph_types_Type* _obj_970 = t; mph_gc_push_root(ctx, (void**)&_obj_970); mph_int _ret_971 = _obj_970->kind; mph_gc_pop_roots(ctx, 1); _ret_971; }) == mph_types_KIND_POINTER)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_972 = t; mph_gc_push_root(ctx, (void**)&_obj_972); mph_int _ret_973 = _obj_972->kind; mph_gc_pop_roots(ctx, 1); _ret_973; }) == mph_types_KIND_MULTI)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_974 = t; mph_gc_push_root(ctx, (void**)&_obj_974); mph_int _ret_975 = _obj_974->kind; mph_gc_pop_roots(ctx, 1); _ret_975; }) == mph_types_KIND_ERROR)) {
{
	return mph_string_new(ctx, "MorphError*");
}
	}
	if ((({ mph_types_Type* _obj_976 = t; mph_gc_push_root(ctx, (void**)&_obj_976); mph_int _ret_977 = _obj_976->kind; mph_gc_pop_roots(ctx, 1); _ret_977; }) == mph_types_KIND_USER_ERROR)) {
{
	return mph_string_new(ctx, "MorphError*");
}
	}
	if ((({ mph_types_Type* _obj_978 = t; mph_gc_push_root(ctx, (void**)&_obj_978); mph_int _ret_979 = _obj_978->kind; mph_gc_pop_roots(ctx, 1); _ret_979; }) == mph_types_KIND_NULL)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_980 = t; mph_gc_push_root(ctx, (void**)&_obj_980); mph_int _ret_981 = _obj_980->kind; mph_gc_pop_roots(ctx, 1); _ret_981; }) == mph_types_KIND_UNKNOWN)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	if ((({ mph_types_Type* _obj_982 = t; mph_gc_push_root(ctx, (void**)&_obj_982); mph_int _ret_983 = _obj_982->kind; mph_gc_pop_roots(ctx, 1); _ret_983; }) == mph_types_KIND_CHANNEL)) {
{
	return mph_string_new(ctx, "MorphChannel*");
}
	}
	if ((({ mph_types_Type* _obj_984 = t; mph_gc_push_root(ctx, (void**)&_obj_984); mph_int _ret_985 = _obj_984->kind; mph_gc_pop_roots(ctx, 1); _ret_985; }) == mph_types_KIND_MODULE)) {
{
	return mph_string_new(ctx, "void*");
}
	}
	return mph_string_new(ctx, "void*");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_next_temp(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_codegen_Codegen* _obj_988 = cg; mph_gc_push_root(ctx, (void**)&_obj_988); _obj_988->temp_index = (({ mph_codegen_Codegen* _obj_986 = cg; mph_gc_push_root(ctx, (void**)&_obj_986); mph_int _ret_987 = _obj_986->temp_index; mph_gc_pop_roots(ctx, 1); _ret_987; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return ({ MorphString* _lhs_991 = prefix; MorphString* _rhs_992 = mph_stdlib_codegen_IntToString(ctx, NULL, ({ mph_codegen_Codegen* _obj_989 = cg; mph_gc_push_root(ctx, (void**)&_obj_989); mph_int _ret_990 = _obj_989->temp_index; mph_gc_pop_roots(ctx, 1); _ret_990; })); mph_gc_push_root(ctx, (void**)&_lhs_991); mph_gc_push_root(ctx, (void**)&_rhs_992); MorphString* _ret_993 = mph_string_concat(ctx, _lhs_991, _rhs_992); mph_gc_pop_roots(ctx, 2); _ret_993; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_append(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	return ({ MorphString* _lhs_994 = buf; MorphString* _rhs_995 = text; mph_gc_push_root(ctx, (void**)&_lhs_994); mph_gc_push_root(ctx, (void**)&_rhs_995); MorphString* _ret_996 = mph_string_concat(ctx, _lhs_994, _rhs_995); mph_gc_pop_roots(ctx, 2); _ret_996; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_append_line(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	return ({ MorphString* _lhs_1000 = ({ MorphString* _lhs_997 = buf; MorphString* _rhs_998 = text; mph_gc_push_root(ctx, (void**)&_lhs_997); mph_gc_push_root(ctx, (void**)&_rhs_998); MorphString* _ret_999 = mph_string_concat(ctx, _lhs_997, _rhs_998); mph_gc_pop_roots(ctx, 2); _ret_999; }); MorphString* _rhs_1001 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_1000); mph_gc_push_root(ctx, (void**)&_rhs_1001); MorphString* _ret_1002 = mph_string_concat(ctx, _lhs_1000, _rhs_1001); mph_gc_pop_roots(ctx, 2); _ret_1002; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_append_indent(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text, mph_int level) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	MorphString* indent = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&indent);
	mph_int i = 0;
	while ((i < level)) {
{
	indent = ({ MorphString* _lhs_1003 = indent; MorphString* _rhs_1004 = mph_string_new(ctx, "\t"); mph_gc_push_root(ctx, (void**)&_lhs_1003); mph_gc_push_root(ctx, (void**)&_rhs_1004); MorphString* _ret_1005 = mph_string_concat(ctx, _lhs_1003, _rhs_1004); mph_gc_pop_roots(ctx, 2); _ret_1005; });
	i = (i + 1);
}
	}
	return ({ MorphString* _lhs_1012 = ({ MorphString* _lhs_1009 = ({ MorphString* _lhs_1006 = buf; MorphString* _rhs_1007 = indent; mph_gc_push_root(ctx, (void**)&_lhs_1006); mph_gc_push_root(ctx, (void**)&_rhs_1007); MorphString* _ret_1008 = mph_string_concat(ctx, _lhs_1006, _rhs_1007); mph_gc_pop_roots(ctx, 2); _ret_1008; }); MorphString* _rhs_1010 = text; mph_gc_push_root(ctx, (void**)&_lhs_1009); mph_gc_push_root(ctx, (void**)&_rhs_1010); MorphString* _ret_1011 = mph_string_concat(ctx, _lhs_1009, _rhs_1010); mph_gc_pop_roots(ctx, 2); _ret_1011; }); MorphString* _rhs_1013 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_1012); mph_gc_push_root(ctx, (void**)&_rhs_1013); MorphString* _ret_1014 = mph_string_concat(ctx, _lhs_1012, _rhs_1013); mph_gc_pop_roots(ctx, 2); _ret_1014; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_compile_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_stdlib_codegen_IntToString(ctx, NULL, ({ mph_ast_IntegerLiteral* _obj_1015 = lit; mph_gc_push_root(ctx, (void**)&_obj_1015); mph_int _ret_1016 = _obj_1015->value; mph_gc_pop_roots(ctx, 1); _ret_1016; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_float_literal(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_FloatLiteral* _obj_1017 = lit; mph_gc_push_root(ctx, (void**)&_obj_1017); MorphString* _ret_1018 = _obj_1017->value_str; mph_gc_pop_roots(ctx, 1); _ret_1018; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_char_literal(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_stdlib_codegen_IntToString(ctx, NULL, ({ mph_ast_CharLiteral* _obj_1019 = lit; mph_gc_push_root(ctx, (void**)&_obj_1019); mph_int _ret_1020 = _obj_1019->value; mph_gc_pop_roots(ctx, 1); _ret_1020; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	MorphString* escaped = ({ MorphString* _arg_1023 = ({ mph_ast_StringLiteral* _obj_1021 = lit; mph_gc_push_root(ctx, (void**)&_obj_1021); MorphString* _ret_1022 = _obj_1021->value; mph_gc_pop_roots(ctx, 1); _ret_1022; }); mph_gc_push_root(ctx, (void**)&_arg_1023); MorphString* _ret_1024 = mph_stdlib_codegen_StringEscape(ctx, NULL, _arg_1023); mph_gc_pop_roots(ctx, 1); _ret_1024; });
	mph_gc_push_root(ctx, (void**)&escaped);
	return ({ MorphString* _lhs_1028 = ({ MorphString* _lhs_1025 = mph_string_new(ctx, "mph_string_new(ctx, \""); MorphString* _rhs_1026 = escaped; mph_gc_push_root(ctx, (void**)&_lhs_1025); mph_gc_push_root(ctx, (void**)&_rhs_1026); MorphString* _ret_1027 = mph_string_concat(ctx, _lhs_1025, _rhs_1026); mph_gc_pop_roots(ctx, 2); _ret_1027; }); MorphString* _rhs_1029 = mph_string_new(ctx, "\")"); mph_gc_push_root(ctx, (void**)&_lhs_1028); mph_gc_push_root(ctx, (void**)&_rhs_1029); MorphString* _ret_1030 = mph_string_concat(ctx, _lhs_1028, _rhs_1029); mph_gc_pop_roots(ctx, 2); _ret_1030; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	if (({ mph_ast_BooleanLiteral* _obj_1031 = lit; mph_gc_push_root(ctx, (void**)&_obj_1031); mph_bool _ret_1032 = _obj_1031->value; mph_gc_pop_roots(ctx, 1); _ret_1032; })) {
{
	return mph_string_new(ctx, "1");
}
	}
	return mph_string_new(ctx, "0");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_null_literal(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_string_new(ctx, "NULL");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	return ({ mph_ast_Identifier* _obj_1033 = ident; mph_gc_push_root(ctx, (void**)&_obj_1033); MorphString* _ret_1034 = _obj_1033->value; mph_gc_pop_roots(ctx, 1); _ret_1034; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_infix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code) {
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
	return ({ MorphString* _lhs_1050 = ({ MorphString* _lhs_1047 = ({ MorphString* _lhs_1044 = ({ MorphString* _lhs_1041 = ({ MorphString* _lhs_1038 = ({ MorphString* _lhs_1035 = mph_string_new(ctx, "("); MorphString* _rhs_1036 = left_code; mph_gc_push_root(ctx, (void**)&_lhs_1035); mph_gc_push_root(ctx, (void**)&_rhs_1036); MorphString* _ret_1037 = mph_string_concat(ctx, _lhs_1035, _rhs_1036); mph_gc_pop_roots(ctx, 2); _ret_1037; }); MorphString* _rhs_1039 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1038); mph_gc_push_root(ctx, (void**)&_rhs_1039); MorphString* _ret_1040 = mph_string_concat(ctx, _lhs_1038, _rhs_1039); mph_gc_pop_roots(ctx, 2); _ret_1040; }); MorphString* _rhs_1042 = c_operator; mph_gc_push_root(ctx, (void**)&_lhs_1041); mph_gc_push_root(ctx, (void**)&_rhs_1042); MorphString* _ret_1043 = mph_string_concat(ctx, _lhs_1041, _rhs_1042); mph_gc_pop_roots(ctx, 2); _ret_1043; }); MorphString* _rhs_1045 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1044); mph_gc_push_root(ctx, (void**)&_rhs_1045); MorphString* _ret_1046 = mph_string_concat(ctx, _lhs_1044, _rhs_1045); mph_gc_pop_roots(ctx, 2); _ret_1046; }); MorphString* _rhs_1048 = right_code; mph_gc_push_root(ctx, (void**)&_lhs_1047); mph_gc_push_root(ctx, (void**)&_rhs_1048); MorphString* _ret_1049 = mph_string_concat(ctx, _lhs_1047, _rhs_1048); mph_gc_pop_roots(ctx, 2); _ret_1049; }); MorphString* _rhs_1051 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_lhs_1050); mph_gc_push_root(ctx, (void**)&_rhs_1051); MorphString* _ret_1052 = mph_string_concat(ctx, _lhs_1050, _rhs_1051); mph_gc_pop_roots(ctx, 2); _ret_1052; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_codegen_compile_prefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	MorphString* c_operator = operator;
	mph_gc_push_root(ctx, (void**)&c_operator);
	if (mph_string_eq(ctx, operator, mph_string_new(ctx, "tidak"))) {
{
	c_operator = mph_string_new(ctx, "!");
}
	}
	return ({ MorphString* _lhs_1059 = ({ MorphString* _lhs_1056 = ({ MorphString* _lhs_1053 = mph_string_new(ctx, "("); MorphString* _rhs_1054 = c_operator; mph_gc_push_root(ctx, (void**)&_lhs_1053); mph_gc_push_root(ctx, (void**)&_rhs_1054); MorphString* _ret_1055 = mph_string_concat(ctx, _lhs_1053, _rhs_1054); mph_gc_pop_roots(ctx, 2); _ret_1055; }); MorphString* _rhs_1057 = right_code; mph_gc_push_root(ctx, (void**)&_lhs_1056); mph_gc_push_root(ctx, (void**)&_rhs_1057); MorphString* _ret_1058 = mph_string_concat(ctx, _lhs_1056, _rhs_1057); mph_gc_pop_roots(ctx, 2); _ret_1058; }); MorphString* _rhs_1060 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_lhs_1059); mph_gc_push_root(ctx, (void**)&_rhs_1060); MorphString* _ret_1061 = mph_string_concat(ctx, _lhs_1059, _rhs_1060); mph_gc_pop_roots(ctx, 2); _ret_1061; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_resolve_builtin_name(MorphContext* ctx, void* _env_void, MorphString* name) {
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

MorphString* mph_codegen_codegen_compile_builtin_call(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&args_code);
	MorphString* c_name = ({ MorphString* _arg_1062 = name; mph_gc_push_root(ctx, (void**)&_arg_1062); MorphString* _ret_1063 = mph_codegen_codegen_resolve_builtin_name(ctx, NULL, _arg_1062); mph_gc_pop_roots(ctx, 1); _ret_1063; });
	mph_gc_push_root(ctx, (void**)&c_name);
	if (mph_string_eq(ctx, c_name, mph_string_new(ctx, ""))) {
{
	return mph_string_new(ctx, "");
}
	}
	if (mph_string_eq(ctx, args_code, mph_string_new(ctx, ""))) {
{
	return ({ MorphString* _lhs_1064 = c_name; MorphString* _rhs_1065 = mph_string_new(ctx, "(ctx)"); mph_gc_push_root(ctx, (void**)&_lhs_1064); mph_gc_push_root(ctx, (void**)&_rhs_1065); MorphString* _ret_1066 = mph_string_concat(ctx, _lhs_1064, _rhs_1065); mph_gc_pop_roots(ctx, 2); _ret_1066; });
}
	}
	return ({ MorphString* _lhs_1073 = ({ MorphString* _lhs_1070 = ({ MorphString* _lhs_1067 = c_name; MorphString* _rhs_1068 = mph_string_new(ctx, "(ctx, "); mph_gc_push_root(ctx, (void**)&_lhs_1067); mph_gc_push_root(ctx, (void**)&_rhs_1068); MorphString* _ret_1069 = mph_string_concat(ctx, _lhs_1067, _rhs_1068); mph_gc_pop_roots(ctx, 2); _ret_1069; }); MorphString* _rhs_1071 = args_code; mph_gc_push_root(ctx, (void**)&_lhs_1070); mph_gc_push_root(ctx, (void**)&_rhs_1071); MorphString* _ret_1072 = mph_string_concat(ctx, _lhs_1070, _rhs_1071); mph_gc_pop_roots(ctx, 2); _ret_1072; }); MorphString* _rhs_1074 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_lhs_1073); mph_gc_push_root(ctx, (void**)&_rhs_1074); MorphString* _ret_1075 = mph_string_concat(ctx, _lhs_1073, _rhs_1074); mph_gc_pop_roots(ctx, 2); _ret_1075; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_var_type_from_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str) {
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

MorphString* mph_codegen_codegen_default_value_for_annotation(MorphContext* ctx, void* _env_void, MorphString* type_str) {
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

MorphString* mph_codegen_codegen_var_type_from_token(MorphContext* ctx, void* _env_void, mph_int token_type) {
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

MorphString* mph_codegen_codegen_value_code_from_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal) {
	mph_gc_push_root(ctx, (void**)&literal);
	if ((token_type == mph_token_TOKEN_STRING)) {
{
	mph_ast_StringLiteral* lit = ({ MorphString* _arg_1076 = literal; mph_gc_push_root(ctx, (void**)&_arg_1076); mph_ast_StringLiteral* _ret_1077 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_1076, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_1077; });
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_StringLiteral* _arg_1078 = lit; mph_gc_push_root(ctx, (void**)&_arg_1078); MorphString* _ret_1079 = mph_codegen_codegen_compile_string_literal(ctx, NULL, _arg_1078); mph_gc_pop_roots(ctx, 1); _ret_1079; });
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
	mph_ast_BooleanLiteral* lit_true = ({ MorphString* _arg_1080 = mph_string_new(ctx, "benar"); mph_gc_push_root(ctx, (void**)&_arg_1080); mph_ast_BooleanLiteral* _ret_1081 = mph_ast_MakeBooleanLiteral(ctx, NULL, 1, _arg_1080, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_1081; });
	mph_gc_push_root(ctx, (void**)&lit_true);
	return ({ mph_ast_BooleanLiteral* _arg_1082 = lit_true; mph_gc_push_root(ctx, (void**)&_arg_1082); MorphString* _ret_1083 = mph_codegen_codegen_compile_boolean_literal(ctx, NULL, _arg_1082); mph_gc_pop_roots(ctx, 1); _ret_1083; });
	mph_gc_pop_roots(ctx, 1);
}
	}
	if ((token_type == mph_token_TOKEN_SALAH)) {
{
	mph_ast_BooleanLiteral* lit_false = ({ MorphString* _arg_1084 = mph_string_new(ctx, "salah"); mph_gc_push_root(ctx, (void**)&_arg_1084); mph_ast_BooleanLiteral* _ret_1085 = mph_ast_MakeBooleanLiteral(ctx, NULL, 0, _arg_1084, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_1085; });
	mph_gc_push_root(ctx, (void**)&lit_false);
	return ({ mph_ast_BooleanLiteral* _arg_1086 = lit_false; mph_gc_push_root(ctx, (void**)&_arg_1086); MorphString* _ret_1087 = mph_codegen_codegen_compile_boolean_literal(ctx, NULL, _arg_1086); mph_gc_pop_roots(ctx, 1); _ret_1087; });
	mph_gc_pop_roots(ctx, 1);
}
	}
	return literal;
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_var_statement_typed(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code, MorphString* c_type) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	mph_gc_push_root(ctx, (void**)&c_type);
	return ({ MorphString* _lhs_1103 = ({ MorphString* _lhs_1100 = ({ MorphString* _lhs_1097 = ({ MorphString* _lhs_1094 = ({ MorphString* _lhs_1091 = ({ MorphString* _lhs_1088 = mph_string_new(ctx, "\t"); MorphString* _rhs_1089 = c_type; mph_gc_push_root(ctx, (void**)&_lhs_1088); mph_gc_push_root(ctx, (void**)&_rhs_1089); MorphString* _ret_1090 = mph_string_concat(ctx, _lhs_1088, _rhs_1089); mph_gc_pop_roots(ctx, 2); _ret_1090; }); MorphString* _rhs_1092 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1091); mph_gc_push_root(ctx, (void**)&_rhs_1092); MorphString* _ret_1093 = mph_string_concat(ctx, _lhs_1091, _rhs_1092); mph_gc_pop_roots(ctx, 2); _ret_1093; }); MorphString* _rhs_1095 = name; mph_gc_push_root(ctx, (void**)&_lhs_1094); mph_gc_push_root(ctx, (void**)&_rhs_1095); MorphString* _ret_1096 = mph_string_concat(ctx, _lhs_1094, _rhs_1095); mph_gc_pop_roots(ctx, 2); _ret_1096; }); MorphString* _rhs_1098 = mph_string_new(ctx, " = "); mph_gc_push_root(ctx, (void**)&_lhs_1097); mph_gc_push_root(ctx, (void**)&_rhs_1098); MorphString* _ret_1099 = mph_string_concat(ctx, _lhs_1097, _rhs_1098); mph_gc_pop_roots(ctx, 2); _ret_1099; }); MorphString* _rhs_1101 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1100); mph_gc_push_root(ctx, (void**)&_rhs_1101); MorphString* _ret_1102 = mph_string_concat(ctx, _lhs_1100, _rhs_1101); mph_gc_pop_roots(ctx, 2); _ret_1102; }); MorphString* _rhs_1104 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1103); mph_gc_push_root(ctx, (void**)&_rhs_1104); MorphString* _ret_1105 = mph_string_concat(ctx, _lhs_1103, _rhs_1104); mph_gc_pop_roots(ctx, 2); _ret_1105; });
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_codegen_var_type_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	if ((({ mph_ast_VarStatement* _obj_1106 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1106); MorphString* _ret_1107 = _obj_1106->value_type; mph_gc_pop_roots(ctx, 1); _ret_1107; }) != mph_string_new(ctx, "-"))) {
{
	return ({ MorphString* _arg_1110 = ({ mph_ast_VarStatement* _obj_1108 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1108); MorphString* _ret_1109 = _obj_1108->value_type; mph_gc_pop_roots(ctx, 1); _ret_1109; }); mph_gc_push_root(ctx, (void**)&_arg_1110); MorphString* _ret_1111 = mph_codegen_codegen_var_type_from_annotation(ctx, NULL, _arg_1110); mph_gc_pop_roots(ctx, 1); _ret_1111; });
}
	}
	if (({ mph_ast_VarStatement* _obj_1112 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1112); mph_bool _ret_1113 = _obj_1112->has_value; mph_gc_pop_roots(ctx, 1); _ret_1113; })) {
{
	return mph_codegen_codegen_var_type_from_token(ctx, NULL, ({ mph_ast_VarStatement* _obj_1114 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1114); mph_int _ret_1115 = _obj_1114->value_token_type; mph_gc_pop_roots(ctx, 1); _ret_1115; }));
}
	}
	return ({ MorphString* _arg_1118 = ({ mph_ast_VarStatement* _obj_1116 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1116); MorphString* _ret_1117 = _obj_1116->value_type; mph_gc_pop_roots(ctx, 1); _ret_1117; }); mph_gc_push_root(ctx, (void**)&_arg_1118); MorphString* _ret_1119 = mph_codegen_codegen_var_type_from_annotation(ctx, NULL, _arg_1118); mph_gc_pop_roots(ctx, 1); _ret_1119; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_var_value_code_from_statement(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	if (({ mph_ast_VarStatement* _obj_1120 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1120); mph_bool _ret_1121 = _obj_1120->has_value; mph_gc_pop_roots(ctx, 1); _ret_1121; })) {
{
	return ({ MorphString* _arg_1126 = ({ mph_ast_VarStatement* _obj_1124 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1124); MorphString* _ret_1125 = _obj_1124->value_literal; mph_gc_pop_roots(ctx, 1); _ret_1125; }); mph_gc_push_root(ctx, (void**)&_arg_1126); MorphString* _ret_1127 = mph_codegen_codegen_value_code_from_token(ctx, NULL, ({ mph_ast_VarStatement* _obj_1122 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1122); mph_int _ret_1123 = _obj_1122->value_token_type; mph_gc_pop_roots(ctx, 1); _ret_1123; }), _arg_1126); mph_gc_pop_roots(ctx, 1); _ret_1127; });
}
	}
	return ({ MorphString* _arg_1130 = ({ mph_ast_VarStatement* _obj_1128 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1128); MorphString* _ret_1129 = _obj_1128->value_type; mph_gc_pop_roots(ctx, 1); _ret_1129; }); mph_gc_push_root(ctx, (void**)&_arg_1130); MorphString* _ret_1131 = mph_codegen_codegen_default_value_for_annotation(ctx, NULL, _arg_1130); mph_gc_pop_roots(ctx, 1); _ret_1131; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_global_var_declaration(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	MorphString* c_type = ({ mph_ast_VarStatement* _arg_1132 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1132); MorphString* _ret_1133 = mph_codegen_codegen_var_type_from_statement(ctx, NULL, _arg_1132); mph_gc_pop_roots(ctx, 1); _ret_1133; });
	mph_gc_push_root(ctx, (void**)&c_type);
	return ({ MorphString* _lhs_1142 = ({ MorphString* _lhs_1139 = ({ MorphString* _lhs_1134 = c_type; MorphString* _rhs_1135 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_1134); mph_gc_push_root(ctx, (void**)&_rhs_1135); MorphString* _ret_1136 = mph_string_concat(ctx, _lhs_1134, _rhs_1135); mph_gc_pop_roots(ctx, 2); _ret_1136; }); MorphString* _rhs_1140 = ({ mph_ast_VarStatement* _obj_1137 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1137); MorphString* _ret_1138 = _obj_1137->name; mph_gc_pop_roots(ctx, 1); _ret_1138; }); mph_gc_push_root(ctx, (void**)&_lhs_1139); mph_gc_push_root(ctx, (void**)&_rhs_1140); MorphString* _ret_1141 = mph_string_concat(ctx, _lhs_1139, _rhs_1140); mph_gc_pop_roots(ctx, 2); _ret_1141; }); MorphString* _rhs_1143 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1142); mph_gc_push_root(ctx, (void**)&_rhs_1143); MorphString* _ret_1144 = mph_string_concat(ctx, _lhs_1142, _rhs_1143); mph_gc_pop_roots(ctx, 2); _ret_1144; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_global_var_initialization(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	MorphString* value_code = ({ mph_ast_VarStatement* _arg_1145 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1145); MorphString* _ret_1146 = mph_codegen_codegen_var_value_code_from_statement(ctx, NULL, _arg_1145); mph_gc_pop_roots(ctx, 1); _ret_1146; });
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _lhs_1158 = ({ MorphString* _lhs_1155 = ({ MorphString* _lhs_1152 = ({ MorphString* _lhs_1149 = mph_string_new(ctx, "\t"); MorphString* _rhs_1150 = ({ mph_ast_VarStatement* _obj_1147 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1147); MorphString* _ret_1148 = _obj_1147->name; mph_gc_pop_roots(ctx, 1); _ret_1148; }); mph_gc_push_root(ctx, (void**)&_lhs_1149); mph_gc_push_root(ctx, (void**)&_rhs_1150); MorphString* _ret_1151 = mph_string_concat(ctx, _lhs_1149, _rhs_1150); mph_gc_pop_roots(ctx, 2); _ret_1151; }); MorphString* _rhs_1153 = mph_string_new(ctx, " = "); mph_gc_push_root(ctx, (void**)&_lhs_1152); mph_gc_push_root(ctx, (void**)&_rhs_1153); MorphString* _ret_1154 = mph_string_concat(ctx, _lhs_1152, _rhs_1153); mph_gc_pop_roots(ctx, 2); _ret_1154; }); MorphString* _rhs_1156 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1155); mph_gc_push_root(ctx, (void**)&_rhs_1156); MorphString* _ret_1157 = mph_string_concat(ctx, _lhs_1155, _rhs_1156); mph_gc_pop_roots(ctx, 2); _ret_1157; }); MorphString* _rhs_1159 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1158); mph_gc_push_root(ctx, (void**)&_rhs_1159); MorphString* _ret_1160 = mph_string_concat(ctx, _lhs_1158, _rhs_1159); mph_gc_pop_roots(ctx, 2); _ret_1160; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_var_statement_from_stmt(MorphContext* ctx, void* _env_void, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&stmt);
	MorphString* c_type = ({ mph_ast_VarStatement* _arg_1161 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1161); MorphString* _ret_1162 = mph_codegen_codegen_var_type_from_statement(ctx, NULL, _arg_1161); mph_gc_pop_roots(ctx, 1); _ret_1162; });
	mph_gc_push_root(ctx, (void**)&c_type);
	MorphString* value_code = ({ mph_ast_VarStatement* _arg_1163 = stmt; mph_gc_push_root(ctx, (void**)&_arg_1163); MorphString* _ret_1164 = mph_codegen_codegen_var_value_code_from_statement(ctx, NULL, _arg_1163); mph_gc_pop_roots(ctx, 1); _ret_1164; });
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1167 = ({ mph_ast_VarStatement* _obj_1165 = stmt; mph_gc_push_root(ctx, (void**)&_obj_1165); MorphString* _ret_1166 = _obj_1165->name; mph_gc_pop_roots(ctx, 1); _ret_1166; }); mph_gc_push_root(ctx, (void**)&_arg_1167); MorphString* _arg_1168 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1168); MorphString* _arg_1169 = c_type; mph_gc_push_root(ctx, (void**)&_arg_1169); MorphString* _ret_1170 = mph_codegen_codegen_compile_var_statement_typed(ctx, NULL, _arg_1167, _arg_1168, _arg_1169); mph_gc_pop_roots(ctx, 3); _ret_1170; });
	mph_gc_pop_roots(ctx, 2);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_var_statement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _lhs_1180 = ({ MorphString* _lhs_1177 = ({ MorphString* _lhs_1174 = ({ MorphString* _lhs_1171 = mph_string_new(ctx, "\tmph_int "); MorphString* _rhs_1172 = name; mph_gc_push_root(ctx, (void**)&_lhs_1171); mph_gc_push_root(ctx, (void**)&_rhs_1172); MorphString* _ret_1173 = mph_string_concat(ctx, _lhs_1171, _rhs_1172); mph_gc_pop_roots(ctx, 2); _ret_1173; }); MorphString* _rhs_1175 = mph_string_new(ctx, " = "); mph_gc_push_root(ctx, (void**)&_lhs_1174); mph_gc_push_root(ctx, (void**)&_rhs_1175); MorphString* _ret_1176 = mph_string_concat(ctx, _lhs_1174, _rhs_1175); mph_gc_pop_roots(ctx, 2); _ret_1176; }); MorphString* _rhs_1178 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1177); mph_gc_push_root(ctx, (void**)&_rhs_1178); MorphString* _ret_1179 = mph_string_concat(ctx, _lhs_1177, _rhs_1178); mph_gc_pop_roots(ctx, 2); _ret_1179; }); MorphString* _rhs_1181 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1180); mph_gc_push_root(ctx, (void**)&_rhs_1181); MorphString* _ret_1182 = mph_string_concat(ctx, _lhs_1180, _rhs_1181); mph_gc_pop_roots(ctx, 2); _ret_1182; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_compile_expression_statement(MorphContext* ctx, void* _env_void, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _lhs_1186 = ({ MorphString* _lhs_1183 = mph_string_new(ctx, "\t"); MorphString* _rhs_1184 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1183); mph_gc_push_root(ctx, (void**)&_rhs_1184); MorphString* _ret_1185 = mph_string_concat(ctx, _lhs_1183, _rhs_1184); mph_gc_pop_roots(ctx, 2); _ret_1185; }); MorphString* _rhs_1187 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1186); mph_gc_push_root(ctx, (void**)&_rhs_1187); MorphString* _ret_1188 = mph_string_concat(ctx, _lhs_1186, _rhs_1187); mph_gc_pop_roots(ctx, 2); _ret_1188; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_return_statement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	if (has_value) {
{
	return ({ MorphString* _lhs_1192 = ({ MorphString* _lhs_1189 = mph_string_new(ctx, "\treturn "); MorphString* _rhs_1190 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_1189); mph_gc_push_root(ctx, (void**)&_rhs_1190); MorphString* _ret_1191 = mph_string_concat(ctx, _lhs_1189, _rhs_1190); mph_gc_pop_roots(ctx, 2); _ret_1191; }); MorphString* _rhs_1193 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_1192); mph_gc_push_root(ctx, (void**)&_rhs_1193); MorphString* _ret_1194 = mph_string_concat(ctx, _lhs_1192, _rhs_1193); mph_gc_pop_roots(ctx, 2); _ret_1194; });
}
	}
	return mph_string_new(ctx, "\treturn;\n");
	mph_gc_pop_roots(ctx, 1);
}

mph_codegen_Codegen* mph_codegen_NewCodegen(MorphContext* ctx, void* _env_void) {
	return mph_codegen_new_codegen(ctx, NULL);
}

MorphString* mph_codegen_Compile(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	return ({ mph_codegen_Codegen* _arg_1195 = cg; mph_gc_push_root(ctx, (void**)&_arg_1195); mph_ast_Program* _arg_1196 = prog; mph_gc_push_root(ctx, (void**)&_arg_1196); MorphString* _ret_1197 = mph_codegen_codegen_compile(ctx, NULL, _arg_1195, _arg_1196); mph_gc_pop_roots(ctx, 2); _ret_1197; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_MapTypeToC(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_types_Type* _arg_1198 = t; mph_gc_push_root(ctx, (void**)&_arg_1198); MorphString* _ret_1199 = mph_codegen_codegen_map_type_to_c(ctx, NULL, _arg_1198); mph_gc_pop_roots(ctx, 1); _ret_1199; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileIntegerLiteral(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_IntegerLiteral* _arg_1200 = lit; mph_gc_push_root(ctx, (void**)&_arg_1200); MorphString* _ret_1201 = mph_codegen_codegen_compile_integer_literal(ctx, NULL, _arg_1200); mph_gc_pop_roots(ctx, 1); _ret_1201; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileFloatLiteral(MorphContext* ctx, void* _env_void, mph_ast_FloatLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_FloatLiteral* _arg_1202 = lit; mph_gc_push_root(ctx, (void**)&_arg_1202); MorphString* _ret_1203 = mph_codegen_codegen_compile_float_literal(ctx, NULL, _arg_1202); mph_gc_pop_roots(ctx, 1); _ret_1203; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileCharLiteral(MorphContext* ctx, void* _env_void, mph_ast_CharLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_CharLiteral* _arg_1204 = lit; mph_gc_push_root(ctx, (void**)&_arg_1204); MorphString* _ret_1205 = mph_codegen_codegen_compile_char_literal(ctx, NULL, _arg_1204); mph_gc_pop_roots(ctx, 1); _ret_1205; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileStringLiteral(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_StringLiteral* _arg_1206 = lit; mph_gc_push_root(ctx, (void**)&_arg_1206); MorphString* _ret_1207 = mph_codegen_codegen_compile_string_literal(ctx, NULL, _arg_1206); mph_gc_pop_roots(ctx, 1); _ret_1207; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileBooleanLiteral(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_BooleanLiteral* _arg_1208 = lit; mph_gc_push_root(ctx, (void**)&_arg_1208); MorphString* _ret_1209 = mph_codegen_codegen_compile_boolean_literal(ctx, NULL, _arg_1208); mph_gc_pop_roots(ctx, 1); _ret_1209; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileNullLiteral(MorphContext* ctx, void* _env_void, mph_ast_NullLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_NullLiteral* _arg_1210 = lit; mph_gc_push_root(ctx, (void**)&_arg_1210); MorphString* _ret_1211 = mph_codegen_codegen_compile_null_literal(ctx, NULL, _arg_1210); mph_gc_pop_roots(ctx, 1); _ret_1211; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileIdentifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	return ({ mph_ast_Identifier* _arg_1212 = ident; mph_gc_push_root(ctx, (void**)&_arg_1212); MorphString* _ret_1213 = mph_codegen_codegen_compile_identifier(ctx, NULL, _arg_1212); mph_gc_pop_roots(ctx, 1); _ret_1213; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileInfix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&left_code);
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	return ({ MorphString* _arg_1214 = left_code; mph_gc_push_root(ctx, (void**)&_arg_1214); MorphString* _arg_1215 = operator; mph_gc_push_root(ctx, (void**)&_arg_1215); MorphString* _arg_1216 = right_code; mph_gc_push_root(ctx, (void**)&_arg_1216); MorphString* _ret_1217 = mph_codegen_codegen_compile_infix(ctx, NULL, _arg_1214, _arg_1215, _arg_1216); mph_gc_pop_roots(ctx, 3); _ret_1217; });
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_CompilePrefix(MorphContext* ctx, void* _env_void, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	return ({ MorphString* _arg_1218 = operator; mph_gc_push_root(ctx, (void**)&_arg_1218); MorphString* _arg_1219 = right_code; mph_gc_push_root(ctx, (void**)&_arg_1219); MorphString* _ret_1220 = mph_codegen_codegen_compile_prefix(ctx, NULL, _arg_1218, _arg_1219); mph_gc_pop_roots(ctx, 2); _ret_1220; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_ResolveBuiltinName(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	return ({ MorphString* _arg_1221 = name; mph_gc_push_root(ctx, (void**)&_arg_1221); MorphString* _ret_1222 = mph_codegen_codegen_resolve_builtin_name(ctx, NULL, _arg_1221); mph_gc_pop_roots(ctx, 1); _ret_1222; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileBuiltinCall(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* args_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&args_code);
	return ({ MorphString* _arg_1223 = name; mph_gc_push_root(ctx, (void**)&_arg_1223); MorphString* _arg_1224 = args_code; mph_gc_push_root(ctx, (void**)&_arg_1224); MorphString* _ret_1225 = mph_codegen_codegen_compile_builtin_call(ctx, NULL, _arg_1223, _arg_1224); mph_gc_pop_roots(ctx, 2); _ret_1225; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_CompileVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1226 = name; mph_gc_push_root(ctx, (void**)&_arg_1226); MorphString* _arg_1227 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1227); MorphString* _ret_1228 = mph_codegen_codegen_compile_var_statement(ctx, NULL, _arg_1226, _arg_1227); mph_gc_pop_roots(ctx, 2); _ret_1228; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_CompileExpressionStatement(MorphContext* ctx, void* _env_void, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1229 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1229); MorphString* _ret_1230 = mph_codegen_codegen_compile_expression_statement(ctx, NULL, _arg_1229); mph_gc_pop_roots(ctx, 1); _ret_1230; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileReturnStatement(MorphContext* ctx, void* _env_void, mph_bool has_value, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_1231 = value_code; mph_gc_push_root(ctx, (void**)&_arg_1231); MorphString* _ret_1232 = mph_codegen_codegen_compile_return_statement(ctx, NULL, has_value, _arg_1231); mph_gc_pop_roots(ctx, 1); _ret_1232; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_ast_Node* _t = (mph_ast_Node*)mph_alloc(ctx, sizeof(mph_ast_Node), &mph_ti_mph_ast_Node); mph_gc_push_root(ctx, (void**)&_t); _t->line = line; _t->column = column; _t->node_type = node_type; _t->token_literal = literal; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void) {
	mph_ast_Node* base = ({ MorphString* _arg_1233 = mph_string_new(ctx, "program"); mph_gc_push_root(ctx, (void**)&_arg_1233); mph_ast_Node* _ret_1234 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PROGRAM, _arg_1233, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_1234; });
	mph_gc_push_root(ctx, (void**)&base);
	mph_ast_VarStatement* stmt = ({ MorphString* _arg_1235 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_1235); MorphString* _arg_1236 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_1236); mph_ast_VarStatement* _ret_1237 = mph_ast_MakeVarStatement(ctx, NULL, _arg_1235, _arg_1236, 1, 1); mph_gc_pop_roots(ctx, 2); _ret_1237; });
	mph_gc_push_root(ctx, (void**)&stmt);
	return ({ mph_ast_Program* _t = (mph_ast_Program*)mph_alloc(ctx, sizeof(mph_ast_Program), &mph_ti_mph_ast_Program); mph_gc_push_root(ctx, (void**)&_t); _t->statements_count = 0; _t->var_statements_count = 0; _t->var_statement = stmt; _t->has_var_statement = 0; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_Identifier* mph_ast_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_1238 = name; mph_gc_push_root(ctx, (void**)&_arg_1238); mph_ast_Node* _ret_1239 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IDENTIFIER, _arg_1238, line, column); mph_gc_pop_roots(ctx, 1); _ret_1239; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_Identifier* _t = (mph_ast_Identifier*)mph_alloc(ctx, sizeof(mph_ast_Identifier), &mph_ti_mph_ast_Identifier); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = name; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_IntegerLiteral* mph_ast_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_1240 = literal; mph_gc_push_root(ctx, (void**)&_arg_1240); mph_ast_Node* _ret_1241 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INTEGER_LITERAL, _arg_1240, line, column); mph_gc_pop_roots(ctx, 1); _ret_1241; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_IntegerLiteral* _t = (mph_ast_IntegerLiteral*)mph_alloc(ctx, sizeof(mph_ast_IntegerLiteral), &mph_ti_mph_ast_IntegerLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_FloatLiteral* mph_ast_MakeFloatLiteral(MorphContext* ctx, void* _env_void, MorphString* value_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value_str);
	mph_ast_Node* base = ({ MorphString* _arg_1242 = value_str; mph_gc_push_root(ctx, (void**)&_arg_1242); mph_ast_Node* _ret_1243 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_FLOAT_LITERAL, _arg_1242, line, column); mph_gc_pop_roots(ctx, 1); _ret_1243; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_FloatLiteral* _t = (mph_ast_FloatLiteral*)mph_alloc(ctx, sizeof(mph_ast_FloatLiteral), &mph_ti_mph_ast_FloatLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value_str = value_str; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StringLiteral* mph_ast_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value);
	mph_ast_Node* base = ({ MorphString* _arg_1244 = value; mph_gc_push_root(ctx, (void**)&_arg_1244); mph_ast_Node* _ret_1245 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRING_LITERAL, _arg_1244, line, column); mph_gc_pop_roots(ctx, 1); _ret_1245; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StringLiteral* _t = (mph_ast_StringLiteral*)mph_alloc(ctx, sizeof(mph_ast_StringLiteral), &mph_ti_mph_ast_StringLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BooleanLiteral* mph_ast_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_1246 = literal; mph_gc_push_root(ctx, (void**)&_arg_1246); mph_ast_Node* _ret_1247 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BOOLEAN_LITERAL, _arg_1246, line, column); mph_gc_pop_roots(ctx, 1); _ret_1247; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BooleanLiteral* _t = (mph_ast_BooleanLiteral*)mph_alloc(ctx, sizeof(mph_ast_BooleanLiteral), &mph_ti_mph_ast_BooleanLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CharLiteral* mph_ast_MakeCharLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_1248 = literal; mph_gc_push_root(ctx, (void**)&_arg_1248); mph_ast_Node* _ret_1249 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CHAR_LITERAL, _arg_1248, line, column); mph_gc_pop_roots(ctx, 1); _ret_1249; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CharLiteral* _t = (mph_ast_CharLiteral*)mph_alloc(ctx, sizeof(mph_ast_CharLiteral), &mph_ti_mph_ast_CharLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_NullLiteral* mph_ast_MakeNullLiteral(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_1250 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_1250); mph_ast_Node* _ret_1251 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_NULL_LITERAL, _arg_1250, line, column); mph_gc_pop_roots(ctx, 1); _ret_1251; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_NullLiteral* _t = (mph_ast_NullLiteral*)mph_alloc(ctx, sizeof(mph_ast_NullLiteral), &mph_ti_mph_ast_NullLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_VarStatement* mph_ast_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&type_str);
	mph_ast_Node* base = ({ MorphString* _arg_1252 = mph_string_new(ctx, "var"); mph_gc_push_root(ctx, (void**)&_arg_1252); mph_ast_Node* _ret_1253 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_VAR_STATEMENT, _arg_1252, line, column); mph_gc_pop_roots(ctx, 1); _ret_1253; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_VarStatement* _t = (mph_ast_VarStatement*)mph_alloc(ctx, sizeof(mph_ast_VarStatement), &mph_ti_mph_ast_VarStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->value_type = type_str; _t->has_value = 0; _t->value_literal = mph_string_new(ctx, "-"); _t->value_token_type = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_PrefixExpression* mph_ast_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_1254 = operator; mph_gc_push_root(ctx, (void**)&_arg_1254); mph_ast_Node* _ret_1255 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PREFIX_EXPRESSION, _arg_1254, line, column); mph_gc_pop_roots(ctx, 1); _ret_1255; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_PrefixExpression* _t = (mph_ast_PrefixExpression*)mph_alloc(ctx, sizeof(mph_ast_PrefixExpression), &mph_ti_mph_ast_PrefixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_InfixExpression* mph_ast_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_1256 = operator; mph_gc_push_root(ctx, (void**)&_arg_1256); mph_ast_Node* _ret_1257 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INFIX_EXPRESSION, _arg_1256, line, column); mph_gc_pop_roots(ctx, 1); _ret_1257; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_InfixExpression* _t = (mph_ast_InfixExpression*)mph_alloc(ctx, sizeof(mph_ast_InfixExpression), &mph_ti_mph_ast_InfixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->operator = operator; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_1258 = mph_string_new(ctx, "kasus"); mph_gc_push_root(ctx, (void**)&_arg_1258); mph_ast_Node* _ret_1259 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CASE_CLAUSE, _arg_1258, line, column); mph_gc_pop_roots(ctx, 1); _ret_1259; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CaseClause* _t = (mph_ast_CaseClause*)mph_alloc(ctx, sizeof(mph_ast_CaseClause), &mph_ti_mph_ast_CaseClause); mph_gc_push_root(ctx, (void**)&_t); _t->has_body = 0; _t->base = base; _t->values_count = 0; _t->v0 = 0; _t->v1 = 0; _t->v2 = 0; _t->v3 = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_case_add_value(MorphContext* ctx, void* _env_void, mph_ast_CaseClause* c, mph_int val) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_ast_CaseClause* _obj_1260 = c; mph_gc_push_root(ctx, (void**)&_obj_1260); mph_int _ret_1261 = _obj_1260->values_count; mph_gc_pop_roots(ctx, 1); _ret_1261; }) == 0)) {
{
	({ mph_ast_CaseClause* _obj_1262 = c; mph_gc_push_root(ctx, (void**)&_obj_1262); _obj_1262->v0 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_1263 = c; mph_gc_push_root(ctx, (void**)&_obj_1263); mph_int _ret_1264 = _obj_1263->values_count; mph_gc_pop_roots(ctx, 1); _ret_1264; }) == 1)) {
{
	({ mph_ast_CaseClause* _obj_1265 = c; mph_gc_push_root(ctx, (void**)&_obj_1265); _obj_1265->v1 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_1266 = c; mph_gc_push_root(ctx, (void**)&_obj_1266); mph_int _ret_1267 = _obj_1266->values_count; mph_gc_pop_roots(ctx, 1); _ret_1267; }) == 2)) {
{
	({ mph_ast_CaseClause* _obj_1268 = c; mph_gc_push_root(ctx, (void**)&_obj_1268); _obj_1268->v2 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_1269 = c; mph_gc_push_root(ctx, (void**)&_obj_1269); mph_int _ret_1270 = _obj_1269->values_count; mph_gc_pop_roots(ctx, 1); _ret_1270; }) == 3)) {
{
	({ mph_ast_CaseClause* _obj_1271 = c; mph_gc_push_root(ctx, (void**)&_obj_1271); _obj_1271->v3 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	({ mph_ast_CaseClause* _obj_1274 = c; mph_gc_push_root(ctx, (void**)&_obj_1274); _obj_1274->values_count = (({ mph_ast_CaseClause* _obj_1272 = c; mph_gc_push_root(ctx, (void**)&_obj_1272); mph_int _ret_1273 = _obj_1272->values_count; mph_gc_pop_roots(ctx, 1); _ret_1273; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return c;
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_SwitchStatement* mph_ast_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_1275 = mph_string_new(ctx, "pilih"); mph_gc_push_root(ctx, (void**)&_arg_1275); mph_ast_Node* _ret_1276 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_SWITCH_STATEMENT, _arg_1275, line, column); mph_gc_pop_roots(ctx, 1); _ret_1276; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_SwitchStatement* _t = (mph_ast_SwitchStatement*)mph_alloc(ctx, sizeof(mph_ast_SwitchStatement), &mph_ti_mph_ast_SwitchStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->cases_count = 0; _t->has_default = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_WhileStatement* mph_ast_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_1277 = mph_string_new(ctx, "selama"); mph_gc_push_root(ctx, (void**)&_arg_1277); mph_ast_Node* _ret_1278 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_WHILE_STATEMENT, _arg_1277, line, column); mph_gc_pop_roots(ctx, 1); _ret_1278; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_WhileStatement* _t = (mph_ast_WhileStatement*)mph_alloc(ctx, sizeof(mph_ast_WhileStatement), &mph_ti_mph_ast_WhileStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->has_body = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StructStatement* mph_ast_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_1279 = mph_string_new(ctx, "struktur"); mph_gc_push_root(ctx, (void**)&_arg_1279); mph_ast_Node* _ret_1280 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRUCT_STATEMENT, _arg_1279, line, column); mph_gc_pop_roots(ctx, 1); _ret_1280; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StructStatement* _t = (mph_ast_StructStatement*)mph_alloc(ctx, sizeof(mph_ast_StructStatement), &mph_ti_mph_ast_StructStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->fields_count = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ImportStatement* mph_ast_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&path);
	mph_ast_Node* base = ({ MorphString* _arg_1281 = mph_string_new(ctx, "ambil"); mph_gc_push_root(ctx, (void**)&_arg_1281); mph_ast_Node* _ret_1282 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IMPORT_STATEMENT, _arg_1281, line, column); mph_gc_pop_roots(ctx, 1); _ret_1282; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_ImportStatement* _t = (mph_ast_ImportStatement*)mph_alloc(ctx, sizeof(mph_ast_ImportStatement), &mph_ti_mph_ast_ImportStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->path = path; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BreakStatement* mph_ast_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_1283 = mph_string_new(ctx, "putus"); mph_gc_push_root(ctx, (void**)&_arg_1283); mph_ast_Node* _ret_1284 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BREAK_STATEMENT, _arg_1283, line, column); mph_gc_pop_roots(ctx, 1); _ret_1284; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BreakStatement* _t = (mph_ast_BreakStatement*)mph_alloc(ctx, sizeof(mph_ast_BreakStatement), &mph_ti_mph_ast_BreakStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ContinueStatement* mph_ast_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_1285 = mph_string_new(ctx, "lanjut"); mph_gc_push_root(ctx, (void**)&_arg_1285); mph_ast_Node* _ret_1286 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CONTINUE_STATEMENT, _arg_1285, line, column); mph_gc_pop_roots(ctx, 1); _ret_1286; });
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
	mph_native_print(ctx, mph_ast_node_type_string(ctx, NULL, ({ mph_ast_Node* _obj_1287 = node; mph_gc_push_root(ctx, (void**)&_obj_1287); mph_int _ret_1288 = _obj_1287->node_type; mph_gc_pop_roots(ctx, 1); _ret_1288; })));
	mph_native_print(ctx, mph_string_new(ctx, " at line "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1289 = node; mph_gc_push_root(ctx, (void**)&_obj_1289); mph_int _ret_1290 = _obj_1289->line; mph_gc_pop_roots(ctx, 1); _ret_1290; }));
	mph_native_print(ctx, mph_string_new(ctx, ", column "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1291 = node; mph_gc_push_root(ctx, (void**)&_obj_1291); mph_int _ret_1292 = _obj_1291->column; mph_gc_pop_roots(ctx, 1); _ret_1292; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	mph_native_print(ctx, mph_string_new(ctx, "Identifier: "));
	mph_native_print(ctx, ({ mph_ast_Identifier* _obj_1293 = ident; mph_gc_push_root(ctx, (void**)&_obj_1293); MorphString* _ret_1294 = _obj_1293->value; mph_gc_pop_roots(ctx, 1); _ret_1294; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1297 = ({ mph_ast_Identifier* _obj_1295 = ident; mph_gc_push_root(ctx, (void**)&_obj_1295); mph_ast_Node* _ret_1296 = _obj_1295->base; mph_gc_pop_roots(ctx, 1); _ret_1296; }); mph_gc_push_root(ctx, (void**)&_obj_1297); mph_int _ret_1298 = _obj_1297->line; mph_gc_pop_roots(ctx, 1); _ret_1298; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1301 = ({ mph_ast_Identifier* _obj_1299 = ident; mph_gc_push_root(ctx, (void**)&_obj_1299); mph_ast_Node* _ret_1300 = _obj_1299->base; mph_gc_pop_roots(ctx, 1); _ret_1300; }); mph_gc_push_root(ctx, (void**)&_obj_1301); mph_int _ret_1302 = _obj_1301->column; mph_gc_pop_roots(ctx, 1); _ret_1302; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "IntegerLiteral: "));
	mph_native_print_int(ctx, ({ mph_ast_IntegerLiteral* _obj_1303 = lit; mph_gc_push_root(ctx, (void**)&_obj_1303); mph_int _ret_1304 = _obj_1303->value; mph_gc_pop_roots(ctx, 1); _ret_1304; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1307 = ({ mph_ast_IntegerLiteral* _obj_1305 = lit; mph_gc_push_root(ctx, (void**)&_obj_1305); mph_ast_Node* _ret_1306 = _obj_1305->base; mph_gc_pop_roots(ctx, 1); _ret_1306; }); mph_gc_push_root(ctx, (void**)&_obj_1307); mph_int _ret_1308 = _obj_1307->line; mph_gc_pop_roots(ctx, 1); _ret_1308; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1311 = ({ mph_ast_IntegerLiteral* _obj_1309 = lit; mph_gc_push_root(ctx, (void**)&_obj_1309); mph_ast_Node* _ret_1310 = _obj_1309->base; mph_gc_pop_roots(ctx, 1); _ret_1310; }); mph_gc_push_root(ctx, (void**)&_obj_1311); mph_int _ret_1312 = _obj_1311->column; mph_gc_pop_roots(ctx, 1); _ret_1312; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "StringLiteral: \""));
	mph_native_print(ctx, ({ mph_ast_StringLiteral* _obj_1313 = lit; mph_gc_push_root(ctx, (void**)&_obj_1313); MorphString* _ret_1314 = _obj_1313->value; mph_gc_pop_roots(ctx, 1); _ret_1314; }));
	mph_native_print(ctx, mph_string_new(ctx, "\" ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1317 = ({ mph_ast_StringLiteral* _obj_1315 = lit; mph_gc_push_root(ctx, (void**)&_obj_1315); mph_ast_Node* _ret_1316 = _obj_1315->base; mph_gc_pop_roots(ctx, 1); _ret_1316; }); mph_gc_push_root(ctx, (void**)&_obj_1317); mph_int _ret_1318 = _obj_1317->line; mph_gc_pop_roots(ctx, 1); _ret_1318; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1321 = ({ mph_ast_StringLiteral* _obj_1319 = lit; mph_gc_push_root(ctx, (void**)&_obj_1319); mph_ast_Node* _ret_1320 = _obj_1319->base; mph_gc_pop_roots(ctx, 1); _ret_1320; }); mph_gc_push_root(ctx, (void**)&_obj_1321); mph_int _ret_1322 = _obj_1321->column; mph_gc_pop_roots(ctx, 1); _ret_1322; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "BooleanLiteral: "));
	if (({ mph_ast_BooleanLiteral* _obj_1323 = lit; mph_gc_push_root(ctx, (void**)&_obj_1323); mph_bool _ret_1324 = _obj_1323->value; mph_gc_pop_roots(ctx, 1); _ret_1324; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "benar"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "salah"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1327 = ({ mph_ast_BooleanLiteral* _obj_1325 = lit; mph_gc_push_root(ctx, (void**)&_obj_1325); mph_ast_Node* _ret_1326 = _obj_1325->base; mph_gc_pop_roots(ctx, 1); _ret_1326; }); mph_gc_push_root(ctx, (void**)&_obj_1327); mph_int _ret_1328 = _obj_1327->line; mph_gc_pop_roots(ctx, 1); _ret_1328; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_1331 = ({ mph_ast_BooleanLiteral* _obj_1329 = lit; mph_gc_push_root(ctx, (void**)&_obj_1329); mph_ast_Node* _ret_1330 = _obj_1329->base; mph_gc_pop_roots(ctx, 1); _ret_1330; }); mph_gc_push_root(ctx, (void**)&_obj_1331); mph_int _ret_1332 = _obj_1331->column; mph_gc_pop_roots(ctx, 1); _ret_1332; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_test_identifier(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 1] Identifier Compilation\n"));
	mph_ast_Identifier* ident = ({ MorphString* _arg_1333 = mph_string_new(ctx, "x"); mph_gc_push_root(ctx, (void**)&_arg_1333); mph_ast_Identifier* _ret_1334 = mph_ast_MakeIdentifier(ctx, NULL, _arg_1333, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_1334; });
	mph_gc_push_root(ctx, (void**)&ident);
	MorphString* result = ({ mph_ast_Identifier* _arg_1335 = ident; mph_gc_push_root(ctx, (void**)&_arg_1335); MorphString* _ret_1336 = mph_codegen_CompileIdentifier(ctx, NULL, _arg_1335); mph_gc_pop_roots(ctx, 1); _ret_1336; });
	mph_gc_push_root(ctx, (void**)&result);
	mph_native_print(ctx, mph_string_new(ctx, "  Identifier x â \""));
	mph_native_print(ctx, result);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â Identifier tests passed\n\n"));
	mph_gc_pop_roots(ctx, 2);
}

void mph_test_infix(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 2] Infix Compilation\n"));
	MorphString* result1 = ({ MorphString* _arg_1337 = mph_string_new(ctx, "1"); mph_gc_push_root(ctx, (void**)&_arg_1337); MorphString* _arg_1338 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_1338); MorphString* _arg_1339 = mph_string_new(ctx, "2"); mph_gc_push_root(ctx, (void**)&_arg_1339); MorphString* _ret_1340 = mph_codegen_CompileInfix(ctx, NULL, _arg_1337, _arg_1338, _arg_1339); mph_gc_pop_roots(ctx, 3); _ret_1340; });
	mph_gc_push_root(ctx, (void**)&result1);
	mph_native_print(ctx, mph_string_new(ctx, "  1 + 2 â \""));
	mph_native_print(ctx, result1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* result2 = ({ MorphString* _arg_1341 = mph_string_new(ctx, "a"); mph_gc_push_root(ctx, (void**)&_arg_1341); MorphString* _arg_1342 = mph_string_new(ctx, "dan"); mph_gc_push_root(ctx, (void**)&_arg_1342); MorphString* _arg_1343 = mph_string_new(ctx, "b"); mph_gc_push_root(ctx, (void**)&_arg_1343); MorphString* _ret_1344 = mph_codegen_CompileInfix(ctx, NULL, _arg_1341, _arg_1342, _arg_1343); mph_gc_pop_roots(ctx, 3); _ret_1344; });
	mph_gc_push_root(ctx, (void**)&result2);
	mph_native_print(ctx, mph_string_new(ctx, "  a dan b â \""));
	mph_native_print(ctx, result2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* result3 = ({ MorphString* _arg_1345 = mph_string_new(ctx, "a"); mph_gc_push_root(ctx, (void**)&_arg_1345); MorphString* _arg_1346 = mph_string_new(ctx, "atau"); mph_gc_push_root(ctx, (void**)&_arg_1346); MorphString* _arg_1347 = mph_string_new(ctx, "b"); mph_gc_push_root(ctx, (void**)&_arg_1347); MorphString* _ret_1348 = mph_codegen_CompileInfix(ctx, NULL, _arg_1345, _arg_1346, _arg_1347); mph_gc_pop_roots(ctx, 3); _ret_1348; });
	mph_gc_push_root(ctx, (void**)&result3);
	mph_native_print(ctx, mph_string_new(ctx, "  a atau b â \""));
	mph_native_print(ctx, result3);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â Infix tests passed\n\n"));
	mph_gc_pop_roots(ctx, 3);
}

void mph_test_var_statement(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 3] VarStatement Compilation\n"));
	MorphString* result = ({ MorphString* _arg_1349 = mph_string_new(ctx, "x"); mph_gc_push_root(ctx, (void**)&_arg_1349); MorphString* _arg_1350 = mph_string_new(ctx, "42"); mph_gc_push_root(ctx, (void**)&_arg_1350); MorphString* _ret_1351 = mph_codegen_CompileVarStatement(ctx, NULL, _arg_1349, _arg_1350); mph_gc_pop_roots(ctx, 2); _ret_1351; });
	mph_gc_push_root(ctx, (void**)&result);
	mph_native_print(ctx, mph_string_new(ctx, "  var x = 42 â \""));
	mph_native_print(ctx, result);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â VarStatement tests passed\n\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_test_expression_statement(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 4] ExpressionStatement Compilation\n"));
	MorphString* result = ({ MorphString* _arg_1352 = mph_string_new(ctx, "native_print(\"ok\")"); mph_gc_push_root(ctx, (void**)&_arg_1352); MorphString* _ret_1353 = mph_codegen_CompileExpressionStatement(ctx, NULL, _arg_1352); mph_gc_pop_roots(ctx, 1); _ret_1353; });
	mph_gc_push_root(ctx, (void**)&result);
	mph_native_print(ctx, mph_string_new(ctx, "  native_print(\"ok\") â \""));
	mph_native_print(ctx, result);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â ExpressionStatement tests passed\n\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_test_return_statement(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 5] ReturnStatement Compilation\n"));
	MorphString* result1 = ({ MorphString* _arg_1354 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_arg_1354); MorphString* _ret_1355 = mph_codegen_CompileReturnStatement(ctx, NULL, 0, _arg_1354); mph_gc_pop_roots(ctx, 1); _ret_1355; });
	mph_gc_push_root(ctx, (void**)&result1);
	mph_native_print(ctx, mph_string_new(ctx, "  return; â \""));
	mph_native_print(ctx, result1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* result2 = ({ MorphString* _arg_1356 = mph_string_new(ctx, "42"); mph_gc_push_root(ctx, (void**)&_arg_1356); MorphString* _ret_1357 = mph_codegen_CompileReturnStatement(ctx, NULL, 1, _arg_1356); mph_gc_pop_roots(ctx, 1); _ret_1357; });
	mph_gc_push_root(ctx, (void**)&result2);
	mph_native_print(ctx, mph_string_new(ctx, "  return 42; â \""));
	mph_native_print(ctx, result2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â ReturnStatement tests passed\n\n"));
	mph_gc_pop_roots(ctx, 2);
}

void mph_test_prefix_expression(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 6] PrefixExpression Compilation\n"));
	MorphString* result1 = ({ MorphString* _arg_1358 = mph_string_new(ctx, "tidak"); mph_gc_push_root(ctx, (void**)&_arg_1358); MorphString* _arg_1359 = mph_string_new(ctx, "x"); mph_gc_push_root(ctx, (void**)&_arg_1359); MorphString* _ret_1360 = mph_codegen_CompilePrefix(ctx, NULL, _arg_1358, _arg_1359); mph_gc_pop_roots(ctx, 2); _ret_1360; });
	mph_gc_push_root(ctx, (void**)&result1);
	mph_native_print(ctx, mph_string_new(ctx, "  tidak x â \""));
	mph_native_print(ctx, result1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* result2 = ({ MorphString* _arg_1361 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_1361); MorphString* _arg_1362 = mph_string_new(ctx, "5"); mph_gc_push_root(ctx, (void**)&_arg_1362); MorphString* _ret_1363 = mph_codegen_CompilePrefix(ctx, NULL, _arg_1361, _arg_1362); mph_gc_pop_roots(ctx, 2); _ret_1363; });
	mph_gc_push_root(ctx, (void**)&result2);
	mph_native_print(ctx, mph_string_new(ctx, "  -5 â \""));
	mph_native_print(ctx, result2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â PrefixExpression tests passed\n\n"));
	mph_gc_pop_roots(ctx, 2);
}

void mph_test_builtin_call(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 7] Builtin Call Compilation\n"));
	MorphString* result1 = ({ MorphString* _arg_1364 = mph_string_new(ctx, "native_print"); mph_gc_push_root(ctx, (void**)&_arg_1364); MorphString* _arg_1365 = mph_string_new(ctx, "mph_string_new(ctx, \"ok\")"); mph_gc_push_root(ctx, (void**)&_arg_1365); MorphString* _ret_1366 = mph_codegen_CompileBuiltinCall(ctx, NULL, _arg_1364, _arg_1365); mph_gc_pop_roots(ctx, 2); _ret_1366; });
	mph_gc_push_root(ctx, (void**)&result1);
	mph_native_print(ctx, mph_string_new(ctx, "  native_print(\"ok\") â \""));
	mph_native_print(ctx, result1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* result2 = ({ MorphString* _arg_1367 = mph_string_new(ctx, "native_print_int"); mph_gc_push_root(ctx, (void**)&_arg_1367); MorphString* _arg_1368 = mph_string_new(ctx, "42"); mph_gc_push_root(ctx, (void**)&_arg_1368); MorphString* _ret_1369 = mph_codegen_CompileBuiltinCall(ctx, NULL, _arg_1367, _arg_1368); mph_gc_pop_roots(ctx, 2); _ret_1369; });
	mph_gc_push_root(ctx, (void**)&result2);
	mph_native_print(ctx, mph_string_new(ctx, "  native_print_int(42) â \""));
	mph_native_print(ctx, result2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* result3 = ({ MorphString* _arg_1370 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_1370); MorphString* _arg_1371 = mph_string_new(ctx, "mph_string_new(ctx, \"oops\")"); mph_gc_push_root(ctx, (void**)&_arg_1371); MorphString* _ret_1372 = mph_codegen_CompileBuiltinCall(ctx, NULL, _arg_1370, _arg_1371); mph_gc_pop_roots(ctx, 2); _ret_1372; });
	mph_gc_push_root(ctx, (void**)&result3);
	mph_native_print(ctx, mph_string_new(ctx, "  error(\"oops\") â \""));
	mph_native_print(ctx, result3);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* result4 = ({ MorphString* _arg_1373 = mph_string_new(ctx, "index"); mph_gc_push_root(ctx, (void**)&_arg_1373); MorphString* _arg_1374 = mph_string_new(ctx, "a, b"); mph_gc_push_root(ctx, (void**)&_arg_1374); MorphString* _ret_1375 = mph_codegen_CompileBuiltinCall(ctx, NULL, _arg_1373, _arg_1374); mph_gc_pop_roots(ctx, 2); _ret_1375; });
	mph_gc_push_root(ctx, (void**)&result4);
	mph_native_print(ctx, mph_string_new(ctx, "  index(a, b) â \""));
	mph_native_print(ctx, result4);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â Builtin Call tests passed\n\n"));
	mph_gc_pop_roots(ctx, 4);
}

void mph_test_type_mapping(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 8] Type Mapping to C\n"));
	mph_types_Type* int_type = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&int_type);
	mph_types_Type* string_type = mph_types_StringType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&string_type);
	mph_types_Type* bool_type = mph_types_BoolType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&bool_type);
	mph_types_Type* struct_type = ({ MorphString* _arg_1376 = mph_string_new(ctx, "User"); mph_gc_push_root(ctx, (void**)&_arg_1376); mph_types_Type* _ret_1377 = mph_types_StructType(ctx, NULL, _arg_1376); mph_gc_pop_roots(ctx, 1); _ret_1377; });
	mph_gc_push_root(ctx, (void**)&struct_type);
	mph_types_Type* channel_type = mph_types_ChannelType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&channel_type);
	MorphString* int_code = ({ mph_types_Type* _arg_1378 = int_type; mph_gc_push_root(ctx, (void**)&_arg_1378); MorphString* _ret_1379 = mph_codegen_MapTypeToC(ctx, NULL, _arg_1378); mph_gc_pop_roots(ctx, 1); _ret_1379; });
	mph_gc_push_root(ctx, (void**)&int_code);
	MorphString* string_code = ({ mph_types_Type* _arg_1380 = string_type; mph_gc_push_root(ctx, (void**)&_arg_1380); MorphString* _ret_1381 = mph_codegen_MapTypeToC(ctx, NULL, _arg_1380); mph_gc_pop_roots(ctx, 1); _ret_1381; });
	mph_gc_push_root(ctx, (void**)&string_code);
	MorphString* bool_code = ({ mph_types_Type* _arg_1382 = bool_type; mph_gc_push_root(ctx, (void**)&_arg_1382); MorphString* _ret_1383 = mph_codegen_MapTypeToC(ctx, NULL, _arg_1382); mph_gc_pop_roots(ctx, 1); _ret_1383; });
	mph_gc_push_root(ctx, (void**)&bool_code);
	MorphString* struct_code = ({ mph_types_Type* _arg_1384 = struct_type; mph_gc_push_root(ctx, (void**)&_arg_1384); MorphString* _ret_1385 = mph_codegen_MapTypeToC(ctx, NULL, _arg_1384); mph_gc_pop_roots(ctx, 1); _ret_1385; });
	mph_gc_push_root(ctx, (void**)&struct_code);
	MorphString* channel_code = ({ mph_types_Type* _arg_1386 = channel_type; mph_gc_push_root(ctx, (void**)&_arg_1386); MorphString* _ret_1387 = mph_codegen_MapTypeToC(ctx, NULL, _arg_1386); mph_gc_pop_roots(ctx, 1); _ret_1387; });
	mph_gc_push_root(ctx, (void**)&channel_code);
	mph_native_print(ctx, mph_string_new(ctx, "  int â \""));
	mph_native_print(ctx, int_code);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  string â \""));
	mph_native_print(ctx, string_code);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  bool â \""));
	mph_native_print(ctx, bool_code);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  struct User â \""));
	mph_native_print(ctx, struct_code);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  channel â \""));
	mph_native_print(ctx, channel_code);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â Type mapping tests passed\n\n"));
	mph_gc_pop_roots(ctx, 10);
}

void mph_test_multipass_log(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 9] Multi-Pass Compilation Log\n"));
	mph_ast_Program* prog = mph_ast_MakeProgram(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&prog);
	mph_codegen_Codegen* cg = mph_codegen_NewCodegen(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&cg);
	MorphString* output = ({ mph_codegen_Codegen* _arg_1388 = cg; mph_gc_push_root(ctx, (void**)&_arg_1388); mph_ast_Program* _arg_1389 = prog; mph_gc_push_root(ctx, (void**)&_arg_1389); MorphString* _ret_1390 = mph_codegen_Compile(ctx, NULL, _arg_1388, _arg_1389); mph_gc_pop_roots(ctx, 2); _ret_1390; });
	mph_gc_push_root(ctx, (void**)&output);
	mph_native_print(ctx, output);
	mph_native_print(ctx, mph_string_new(ctx, "  â Multi-pass log test printed\n\n"));
	mph_gc_pop_roots(ctx, 3);
}

void mph_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â  N1 Codegen Phase 2: Basics Test   â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n\n"));
	mph_test_identifier(ctx, NULL);
	mph_test_infix(ctx, NULL);
	mph_test_var_statement(ctx, NULL);
	mph_test_expression_statement(ctx, NULL);
	mph_test_return_statement(ctx, NULL);
	mph_test_prefix_expression(ctx, NULL);
	mph_test_builtin_call(ctx, NULL);
	mph_test_type_mapping(ctx, NULL);
	mph_test_multipass_log(ctx, NULL);
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â  â All Phase 2 Tests Passed       â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
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
	mph_main(ctx, NULL);
}
