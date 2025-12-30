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
#define MPH_TYPE_mph_types_TypeResult 3
#define MPH_TYPE_mph_Symbol 32
#define MPH_TYPE_mph_ast_VarStatement 5
#define MPH_TYPE_mph_ast_NullLiteral 17
#define MPH_TYPE_mph_ast_ImportStatement 28
#define MPH_TYPE_mph_ast_Node 4
#define MPH_TYPE_mph_ast_FunctionStatement 6
#define MPH_TYPE_mph_ast_ExpressionStatement 8
#define MPH_TYPE_mph_ast_IntegerLiteral 12
#define MPH_TYPE_mph_ast_BooleanLiteral 15
#define MPH_TYPE_mph_Checker 31
#define MPH_TYPE_mph_ast_BlockStatement 9
#define MPH_TYPE_mph_ast_Program 10
#define MPH_TYPE_mph_ast_FloatLiteral 13
#define MPH_TYPE_mph_ast_StringLiteral 14
#define MPH_TYPE_mph_ast_InfixExpression 19
#define MPH_TYPE_mph_ast_CallExpression 21
#define MPH_TYPE_mph_ast_ContinueStatement 30
#define MPH_TYPE_mph_token_Token 1
#define MPH_TYPE_mph_ast_CharLiteral 16
#define MPH_TYPE_mph_ast_PrefixExpression 18
#define MPH_TYPE_mph_ast_IfExpression 20
#define MPH_TYPE_mph_ast_IndexExpression 22
#define MPH_TYPE_mph_ast_MemberExpression 23
#define MPH_TYPE_mph_ast_CaseClause 24
#define MPH_TYPE_mph_ast_WhileStatement 26
#define MPH_TYPE_mph_ast_ReturnStatement 7
#define MPH_TYPE_mph_ast_BreakStatement 29
#define MPH_TYPE_mph_ast_Identifier 11
#define MPH_TYPE_mph_ast_StructStatement 27
#define MPH_TYPE_mph_types_Type 2
#define MPH_TYPE_mph_ast_SwitchStatement 25

// Struct Definitions (Env & Types)
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

typedef struct mph_Checker mph_Checker;
typedef struct mph_Symbol mph_Symbol;
struct mph_Checker {
	mph_int errors_count;
	mph_int current_scope_level;
};

struct mph_Symbol {
	MorphString* name;
	mph_types_Type* symbol_type;
	mph_bool is_constant;
	mph_int line;
	mph_int column;
};

MorphTypeInfo mph_ti_mph_types_Type = { "Type", sizeof(mph_types_Type), 1, (size_t[]){offsetof(mph_types_Type, name)} };
MorphTypeInfo mph_ti_mph_types_TypeResult = { "TypeResult", sizeof(mph_types_TypeResult), 2, (size_t[]){offsetof(mph_types_TypeResult, result), offsetof(mph_types_TypeResult, error_msg)} };
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
MorphTypeInfo mph_ti_mph_Checker = { "Checker", sizeof(mph_Checker), 0, NULL };
MorphTypeInfo mph_ti_mph_Symbol = { "Symbol", sizeof(mph_Symbol), 2, (size_t[]){offsetof(mph_Symbol, name), offsetof(mph_Symbol, symbol_type)} };

// Global Variables
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

// Function Prototypes
mph_Checker* mph_new_checker(MorphContext* ctx, void* _env_void);
void mph_checker_add_error(MorphContext* ctx, void* _env_void, mph_Checker* c, MorphString* message);
mph_bool mph_checker_has_errors(MorphContext* ctx, void* _env_void, mph_Checker* c);
mph_types_Type* mph_check_integer_literal(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_IntegerLiteral* lit);
mph_types_Type* mph_check_string_literal(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_StringLiteral* lit);
mph_types_Type* mph_check_boolean_literal(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_BooleanLiteral* lit);
mph_types_Type* mph_check_identifier(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_Identifier* ident);
mph_types_Type* mph_check_prefix_expression(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_PrefixExpression* expr);
mph_types_Type* mph_check_infix_expression(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_InfixExpression* expr);
mph_types_Type* mph_check_var_statement(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_VarStatement* stmt);
void mph_check_program(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_Program* program);
mph_types_Type* mph_check_builtin_function(MorphContext* ctx, void* _env_void, mph_Checker* c, MorphString* name, mph_int args_count);
mph_bool mph_check_assignment_compatibility(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type);
void mph_checker_enter_scope(MorphContext* ctx, void* _env_void, mph_Checker* c);
void mph_checker_exit_scope(MorphContext* ctx, void* _env_void, mph_Checker* c);
mph_types_Type* mph_infer_type_from_literal(MorphContext* ctx, void* _env_void, MorphString* literal, mph_int token_type);
mph_Checker* mph_NewChecker(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_CheckIntegerLiteral(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_IntegerLiteral* lit);
mph_types_Type* mph_CheckStringLiteral(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_StringLiteral* lit);
mph_types_Type* mph_CheckBooleanLiteral(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_BooleanLiteral* lit);
mph_types_Type* mph_CheckBuiltinFunction(MorphContext* ctx, void* _env_void, mph_Checker* c, MorphString* name, mph_int args_count);
mph_bool mph_CheckAssignmentCompatibility(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type);
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

// Function Definitions
mph_types_Type* mph_types_make_type(MorphContext* ctx, void* _env_void, mph_int k, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ mph_types_Type* _t = (mph_types_Type*)mph_alloc(ctx, sizeof(mph_types_Type), &mph_ti_mph_types_Type); mph_gc_push_root(ctx, (void**)&_t); _t->kind = k; _t->name = n; mph_gc_pop_roots(ctx, 1); _t; });
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

mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_ast_Node* _t = (mph_ast_Node*)mph_alloc(ctx, sizeof(mph_ast_Node), &mph_ti_mph_ast_Node); mph_gc_push_root(ctx, (void**)&_t); _t->node_type = node_type; _t->token_literal = literal; _t->line = line; _t->column = column; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void) {
	mph_ast_Node* base = ({ MorphString* _arg_528 = mph_string_new(ctx, "program"); mph_gc_push_root(ctx, (void**)&_arg_528); mph_ast_Node* _ret_529 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PROGRAM, _arg_528, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_529; });
	mph_gc_push_root(ctx, (void**)&base);
	mph_ast_VarStatement* stmt = ({ MorphString* _arg_530 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_530); MorphString* _arg_531 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_531); mph_ast_VarStatement* _ret_532 = mph_ast_MakeVarStatement(ctx, NULL, _arg_530, _arg_531, 1, 1); mph_gc_pop_roots(ctx, 2); _ret_532; });
	mph_gc_push_root(ctx, (void**)&stmt);
	return ({ mph_ast_Program* _t = (mph_ast_Program*)mph_alloc(ctx, sizeof(mph_ast_Program), &mph_ti_mph_ast_Program); mph_gc_push_root(ctx, (void**)&_t); _t->has_var_statement = 0; _t->base = base; _t->statements_count = 0; _t->var_statements_count = 0; _t->var_statement = stmt; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_Identifier* mph_ast_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_533 = name; mph_gc_push_root(ctx, (void**)&_arg_533); mph_ast_Node* _ret_534 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IDENTIFIER, _arg_533, line, column); mph_gc_pop_roots(ctx, 1); _ret_534; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_Identifier* _t = (mph_ast_Identifier*)mph_alloc(ctx, sizeof(mph_ast_Identifier), &mph_ti_mph_ast_Identifier); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = name; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_IntegerLiteral* mph_ast_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_535 = literal; mph_gc_push_root(ctx, (void**)&_arg_535); mph_ast_Node* _ret_536 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INTEGER_LITERAL, _arg_535, line, column); mph_gc_pop_roots(ctx, 1); _ret_536; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_IntegerLiteral* _t = (mph_ast_IntegerLiteral*)mph_alloc(ctx, sizeof(mph_ast_IntegerLiteral), &mph_ti_mph_ast_IntegerLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_FloatLiteral* mph_ast_MakeFloatLiteral(MorphContext* ctx, void* _env_void, MorphString* value_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value_str);
	mph_ast_Node* base = ({ MorphString* _arg_537 = value_str; mph_gc_push_root(ctx, (void**)&_arg_537); mph_ast_Node* _ret_538 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_FLOAT_LITERAL, _arg_537, line, column); mph_gc_pop_roots(ctx, 1); _ret_538; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_FloatLiteral* _t = (mph_ast_FloatLiteral*)mph_alloc(ctx, sizeof(mph_ast_FloatLiteral), &mph_ti_mph_ast_FloatLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value_str = value_str; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StringLiteral* mph_ast_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value);
	mph_ast_Node* base = ({ MorphString* _arg_539 = value; mph_gc_push_root(ctx, (void**)&_arg_539); mph_ast_Node* _ret_540 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRING_LITERAL, _arg_539, line, column); mph_gc_pop_roots(ctx, 1); _ret_540; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StringLiteral* _t = (mph_ast_StringLiteral*)mph_alloc(ctx, sizeof(mph_ast_StringLiteral), &mph_ti_mph_ast_StringLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BooleanLiteral* mph_ast_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_541 = literal; mph_gc_push_root(ctx, (void**)&_arg_541); mph_ast_Node* _ret_542 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BOOLEAN_LITERAL, _arg_541, line, column); mph_gc_pop_roots(ctx, 1); _ret_542; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BooleanLiteral* _t = (mph_ast_BooleanLiteral*)mph_alloc(ctx, sizeof(mph_ast_BooleanLiteral), &mph_ti_mph_ast_BooleanLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CharLiteral* mph_ast_MakeCharLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_543 = literal; mph_gc_push_root(ctx, (void**)&_arg_543); mph_ast_Node* _ret_544 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CHAR_LITERAL, _arg_543, line, column); mph_gc_pop_roots(ctx, 1); _ret_544; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CharLiteral* _t = (mph_ast_CharLiteral*)mph_alloc(ctx, sizeof(mph_ast_CharLiteral), &mph_ti_mph_ast_CharLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_NullLiteral* mph_ast_MakeNullLiteral(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_545 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_545); mph_ast_Node* _ret_546 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_NULL_LITERAL, _arg_545, line, column); mph_gc_pop_roots(ctx, 1); _ret_546; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_NullLiteral* _t = (mph_ast_NullLiteral*)mph_alloc(ctx, sizeof(mph_ast_NullLiteral), &mph_ti_mph_ast_NullLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_VarStatement* mph_ast_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&type_str);
	mph_ast_Node* base = ({ MorphString* _arg_547 = mph_string_new(ctx, "var"); mph_gc_push_root(ctx, (void**)&_arg_547); mph_ast_Node* _ret_548 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_VAR_STATEMENT, _arg_547, line, column); mph_gc_pop_roots(ctx, 1); _ret_548; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_VarStatement* _t = (mph_ast_VarStatement*)mph_alloc(ctx, sizeof(mph_ast_VarStatement), &mph_ti_mph_ast_VarStatement); mph_gc_push_root(ctx, (void**)&_t); _t->value_type = type_str; _t->has_value = 0; _t->value_literal = mph_string_new(ctx, "-"); _t->value_token_type = 0; _t->base = base; _t->name = name; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_PrefixExpression* mph_ast_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_549 = operator; mph_gc_push_root(ctx, (void**)&_arg_549); mph_ast_Node* _ret_550 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PREFIX_EXPRESSION, _arg_549, line, column); mph_gc_pop_roots(ctx, 1); _ret_550; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_PrefixExpression* _t = (mph_ast_PrefixExpression*)mph_alloc(ctx, sizeof(mph_ast_PrefixExpression), &mph_ti_mph_ast_PrefixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_InfixExpression* mph_ast_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_551 = operator; mph_gc_push_root(ctx, (void**)&_arg_551); mph_ast_Node* _ret_552 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INFIX_EXPRESSION, _arg_551, line, column); mph_gc_pop_roots(ctx, 1); _ret_552; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_InfixExpression* _t = (mph_ast_InfixExpression*)mph_alloc(ctx, sizeof(mph_ast_InfixExpression), &mph_ti_mph_ast_InfixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_553 = mph_string_new(ctx, "kasus"); mph_gc_push_root(ctx, (void**)&_arg_553); mph_ast_Node* _ret_554 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CASE_CLAUSE, _arg_553, line, column); mph_gc_pop_roots(ctx, 1); _ret_554; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CaseClause* _t = (mph_ast_CaseClause*)mph_alloc(ctx, sizeof(mph_ast_CaseClause), &mph_ti_mph_ast_CaseClause); mph_gc_push_root(ctx, (void**)&_t); _t->v3 = 0; _t->has_body = 0; _t->base = base; _t->values_count = 0; _t->v0 = 0; _t->v1 = 0; _t->v2 = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_case_add_value(MorphContext* ctx, void* _env_void, mph_ast_CaseClause* c, mph_int val) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_ast_CaseClause* _obj_555 = c; mph_gc_push_root(ctx, (void**)&_obj_555); mph_int _ret_556 = _obj_555->values_count; mph_gc_pop_roots(ctx, 1); _ret_556; }) == 0)) {
{
	({ mph_ast_CaseClause* _obj_557 = c; mph_gc_push_root(ctx, (void**)&_obj_557); _obj_557->v0 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_558 = c; mph_gc_push_root(ctx, (void**)&_obj_558); mph_int _ret_559 = _obj_558->values_count; mph_gc_pop_roots(ctx, 1); _ret_559; }) == 1)) {
{
	({ mph_ast_CaseClause* _obj_560 = c; mph_gc_push_root(ctx, (void**)&_obj_560); _obj_560->v1 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_561 = c; mph_gc_push_root(ctx, (void**)&_obj_561); mph_int _ret_562 = _obj_561->values_count; mph_gc_pop_roots(ctx, 1); _ret_562; }) == 2)) {
{
	({ mph_ast_CaseClause* _obj_563 = c; mph_gc_push_root(ctx, (void**)&_obj_563); _obj_563->v2 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_564 = c; mph_gc_push_root(ctx, (void**)&_obj_564); mph_int _ret_565 = _obj_564->values_count; mph_gc_pop_roots(ctx, 1); _ret_565; }) == 3)) {
{
	({ mph_ast_CaseClause* _obj_566 = c; mph_gc_push_root(ctx, (void**)&_obj_566); _obj_566->v3 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	({ mph_ast_CaseClause* _obj_569 = c; mph_gc_push_root(ctx, (void**)&_obj_569); _obj_569->values_count = (({ mph_ast_CaseClause* _obj_567 = c; mph_gc_push_root(ctx, (void**)&_obj_567); mph_int _ret_568 = _obj_567->values_count; mph_gc_pop_roots(ctx, 1); _ret_568; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return c;
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_SwitchStatement* mph_ast_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_570 = mph_string_new(ctx, "pilih"); mph_gc_push_root(ctx, (void**)&_arg_570); mph_ast_Node* _ret_571 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_SWITCH_STATEMENT, _arg_570, line, column); mph_gc_pop_roots(ctx, 1); _ret_571; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_SwitchStatement* _t = (mph_ast_SwitchStatement*)mph_alloc(ctx, sizeof(mph_ast_SwitchStatement), &mph_ti_mph_ast_SwitchStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->cases_count = 0; _t->has_default = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_WhileStatement* mph_ast_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_572 = mph_string_new(ctx, "selama"); mph_gc_push_root(ctx, (void**)&_arg_572); mph_ast_Node* _ret_573 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_WHILE_STATEMENT, _arg_572, line, column); mph_gc_pop_roots(ctx, 1); _ret_573; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_WhileStatement* _t = (mph_ast_WhileStatement*)mph_alloc(ctx, sizeof(mph_ast_WhileStatement), &mph_ti_mph_ast_WhileStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->has_body = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StructStatement* mph_ast_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_574 = mph_string_new(ctx, "struktur"); mph_gc_push_root(ctx, (void**)&_arg_574); mph_ast_Node* _ret_575 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRUCT_STATEMENT, _arg_574, line, column); mph_gc_pop_roots(ctx, 1); _ret_575; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StructStatement* _t = (mph_ast_StructStatement*)mph_alloc(ctx, sizeof(mph_ast_StructStatement), &mph_ti_mph_ast_StructStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->fields_count = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ImportStatement* mph_ast_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&path);
	mph_ast_Node* base = ({ MorphString* _arg_576 = mph_string_new(ctx, "ambil"); mph_gc_push_root(ctx, (void**)&_arg_576); mph_ast_Node* _ret_577 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IMPORT_STATEMENT, _arg_576, line, column); mph_gc_pop_roots(ctx, 1); _ret_577; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_ImportStatement* _t = (mph_ast_ImportStatement*)mph_alloc(ctx, sizeof(mph_ast_ImportStatement), &mph_ti_mph_ast_ImportStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->path = path; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BreakStatement* mph_ast_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_578 = mph_string_new(ctx, "putus"); mph_gc_push_root(ctx, (void**)&_arg_578); mph_ast_Node* _ret_579 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BREAK_STATEMENT, _arg_578, line, column); mph_gc_pop_roots(ctx, 1); _ret_579; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BreakStatement* _t = (mph_ast_BreakStatement*)mph_alloc(ctx, sizeof(mph_ast_BreakStatement), &mph_ti_mph_ast_BreakStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ContinueStatement* mph_ast_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_580 = mph_string_new(ctx, "lanjut"); mph_gc_push_root(ctx, (void**)&_arg_580); mph_ast_Node* _ret_581 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CONTINUE_STATEMENT, _arg_580, line, column); mph_gc_pop_roots(ctx, 1); _ret_581; });
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
	mph_native_print(ctx, mph_ast_node_type_string(ctx, NULL, ({ mph_ast_Node* _obj_582 = node; mph_gc_push_root(ctx, (void**)&_obj_582); mph_int _ret_583 = _obj_582->node_type; mph_gc_pop_roots(ctx, 1); _ret_583; })));
	mph_native_print(ctx, mph_string_new(ctx, " at line "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_584 = node; mph_gc_push_root(ctx, (void**)&_obj_584); mph_int _ret_585 = _obj_584->line; mph_gc_pop_roots(ctx, 1); _ret_585; }));
	mph_native_print(ctx, mph_string_new(ctx, ", column "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_586 = node; mph_gc_push_root(ctx, (void**)&_obj_586); mph_int _ret_587 = _obj_586->column; mph_gc_pop_roots(ctx, 1); _ret_587; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	mph_native_print(ctx, mph_string_new(ctx, "Identifier: "));
	mph_native_print(ctx, ({ mph_ast_Identifier* _obj_588 = ident; mph_gc_push_root(ctx, (void**)&_obj_588); MorphString* _ret_589 = _obj_588->value; mph_gc_pop_roots(ctx, 1); _ret_589; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_592 = ({ mph_ast_Identifier* _obj_590 = ident; mph_gc_push_root(ctx, (void**)&_obj_590); mph_ast_Node* _ret_591 = _obj_590->base; mph_gc_pop_roots(ctx, 1); _ret_591; }); mph_gc_push_root(ctx, (void**)&_obj_592); mph_int _ret_593 = _obj_592->line; mph_gc_pop_roots(ctx, 1); _ret_593; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_596 = ({ mph_ast_Identifier* _obj_594 = ident; mph_gc_push_root(ctx, (void**)&_obj_594); mph_ast_Node* _ret_595 = _obj_594->base; mph_gc_pop_roots(ctx, 1); _ret_595; }); mph_gc_push_root(ctx, (void**)&_obj_596); mph_int _ret_597 = _obj_596->column; mph_gc_pop_roots(ctx, 1); _ret_597; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "IntegerLiteral: "));
	mph_native_print_int(ctx, ({ mph_ast_IntegerLiteral* _obj_598 = lit; mph_gc_push_root(ctx, (void**)&_obj_598); mph_int _ret_599 = _obj_598->value; mph_gc_pop_roots(ctx, 1); _ret_599; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_602 = ({ mph_ast_IntegerLiteral* _obj_600 = lit; mph_gc_push_root(ctx, (void**)&_obj_600); mph_ast_Node* _ret_601 = _obj_600->base; mph_gc_pop_roots(ctx, 1); _ret_601; }); mph_gc_push_root(ctx, (void**)&_obj_602); mph_int _ret_603 = _obj_602->line; mph_gc_pop_roots(ctx, 1); _ret_603; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_606 = ({ mph_ast_IntegerLiteral* _obj_604 = lit; mph_gc_push_root(ctx, (void**)&_obj_604); mph_ast_Node* _ret_605 = _obj_604->base; mph_gc_pop_roots(ctx, 1); _ret_605; }); mph_gc_push_root(ctx, (void**)&_obj_606); mph_int _ret_607 = _obj_606->column; mph_gc_pop_roots(ctx, 1); _ret_607; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "StringLiteral: \""));
	mph_native_print(ctx, ({ mph_ast_StringLiteral* _obj_608 = lit; mph_gc_push_root(ctx, (void**)&_obj_608); MorphString* _ret_609 = _obj_608->value; mph_gc_pop_roots(ctx, 1); _ret_609; }));
	mph_native_print(ctx, mph_string_new(ctx, "\" ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_612 = ({ mph_ast_StringLiteral* _obj_610 = lit; mph_gc_push_root(ctx, (void**)&_obj_610); mph_ast_Node* _ret_611 = _obj_610->base; mph_gc_pop_roots(ctx, 1); _ret_611; }); mph_gc_push_root(ctx, (void**)&_obj_612); mph_int _ret_613 = _obj_612->line; mph_gc_pop_roots(ctx, 1); _ret_613; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_616 = ({ mph_ast_StringLiteral* _obj_614 = lit; mph_gc_push_root(ctx, (void**)&_obj_614); mph_ast_Node* _ret_615 = _obj_614->base; mph_gc_pop_roots(ctx, 1); _ret_615; }); mph_gc_push_root(ctx, (void**)&_obj_616); mph_int _ret_617 = _obj_616->column; mph_gc_pop_roots(ctx, 1); _ret_617; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "BooleanLiteral: "));
	if (({ mph_ast_BooleanLiteral* _obj_618 = lit; mph_gc_push_root(ctx, (void**)&_obj_618); mph_bool _ret_619 = _obj_618->value; mph_gc_pop_roots(ctx, 1); _ret_619; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "benar"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "salah"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_622 = ({ mph_ast_BooleanLiteral* _obj_620 = lit; mph_gc_push_root(ctx, (void**)&_obj_620); mph_ast_Node* _ret_621 = _obj_620->base; mph_gc_pop_roots(ctx, 1); _ret_621; }); mph_gc_push_root(ctx, (void**)&_obj_622); mph_int _ret_623 = _obj_622->line; mph_gc_pop_roots(ctx, 1); _ret_623; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_626 = ({ mph_ast_BooleanLiteral* _obj_624 = lit; mph_gc_push_root(ctx, (void**)&_obj_624); mph_ast_Node* _ret_625 = _obj_624->base; mph_gc_pop_roots(ctx, 1); _ret_625; }); mph_gc_push_root(ctx, (void**)&_obj_626); mph_int _ret_627 = _obj_626->column; mph_gc_pop_roots(ctx, 1); _ret_627; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

mph_token_Token* mph_token_MakeToken(MorphContext* ctx, void* _env_void, mph_int t_type, MorphString* lit, mph_int ln, mph_int col) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_token_Token* _t = (mph_token_Token*)mph_alloc(ctx, sizeof(mph_token_Token), &mph_ti_mph_token_Token); mph_gc_push_root(ctx, (void**)&_t); _t->column = col; _t->token_type = t_type; _t->literal = lit; _t->line = ln; mph_gc_pop_roots(ctx, 1); _t; });
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

mph_Checker* mph_new_checker(MorphContext* ctx, void* _env_void) {
	return ({ mph_Checker* _t = (mph_Checker*)mph_alloc(ctx, sizeof(mph_Checker), &mph_ti_mph_Checker); mph_gc_push_root(ctx, (void**)&_t); _t->errors_count = 0; _t->current_scope_level = 0; mph_gc_pop_roots(ctx, 1); _t; });
}

void mph_checker_add_error(MorphContext* ctx, void* _env_void, mph_Checker* c, MorphString* message) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&message);
	({ mph_Checker* _obj_630 = c; mph_gc_push_root(ctx, (void**)&_obj_630); _obj_630->errors_count = (({ mph_Checker* _obj_628 = c; mph_gc_push_root(ctx, (void**)&_obj_628); mph_int _ret_629 = _obj_628->errors_count; mph_gc_pop_roots(ctx, 1); _ret_629; }) + 1); mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Type Error: "));
	mph_native_print(ctx, message);
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_checker_has_errors(MorphContext* ctx, void* _env_void, mph_Checker* c) {
	mph_gc_push_root(ctx, (void**)&c);
	return (({ mph_Checker* _obj_631 = c; mph_gc_push_root(ctx, (void**)&_obj_631); mph_int _ret_632 = _obj_631->errors_count; mph_gc_pop_roots(ctx, 1); _ret_632; }) > 0);
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_check_integer_literal(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_types_IntType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_check_string_literal(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_types_StringType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_check_boolean_literal(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_types_BoolType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_check_identifier(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&ident);
	return mph_types_IntType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_check_prefix_expression(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_PrefixExpression* expr) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&expr);
	mph_types_Type* right_type = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&right_type);
	mph_types_TypeResult* result = ({ mph_types_Type* _arg_633 = right_type; mph_gc_push_root(ctx, (void**)&_arg_633); MorphString* _arg_636 = ({ mph_ast_PrefixExpression* _obj_634 = expr; mph_gc_push_root(ctx, (void**)&_obj_634); MorphString* _ret_635 = _obj_634->operator; mph_gc_pop_roots(ctx, 1); _ret_635; }); mph_gc_push_root(ctx, (void**)&_arg_636); mph_types_TypeResult* _ret_637 = mph_types_TypePrefixOp(ctx, NULL, _arg_633, _arg_636); mph_gc_pop_roots(ctx, 2); _ret_637; });
	mph_gc_push_root(ctx, (void**)&result);
	if (({ mph_types_TypeResult* _obj_638 = result; mph_gc_push_root(ctx, (void**)&_obj_638); mph_bool _ret_639 = _obj_638->has_error; mph_gc_pop_roots(ctx, 1); _ret_639; })) {
{
	({ mph_Checker* _arg_640 = c; mph_gc_push_root(ctx, (void**)&_arg_640); MorphString* _arg_643 = ({ mph_types_TypeResult* _obj_641 = result; mph_gc_push_root(ctx, (void**)&_obj_641); MorphString* _ret_642 = _obj_641->error_msg; mph_gc_pop_roots(ctx, 1); _ret_642; }); mph_gc_push_root(ctx, (void**)&_arg_643); mph_checker_add_error(ctx, NULL, _arg_640, _arg_643); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
	return ({ mph_types_TypeResult* _obj_644 = result; mph_gc_push_root(ctx, (void**)&_obj_644); mph_types_Type* _ret_645 = _obj_644->result; mph_gc_pop_roots(ctx, 1); _ret_645; });
	mph_gc_pop_roots(ctx, 2);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_check_infix_expression(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_InfixExpression* expr) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&expr);
	mph_types_Type* left_type = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&left_type);
	mph_types_Type* right_type = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&right_type);
	mph_types_TypeResult* result = ({ mph_types_Type* _arg_646 = left_type; mph_gc_push_root(ctx, (void**)&_arg_646); MorphString* _arg_649 = ({ mph_ast_InfixExpression* _obj_647 = expr; mph_gc_push_root(ctx, (void**)&_obj_647); MorphString* _ret_648 = _obj_647->operator; mph_gc_pop_roots(ctx, 1); _ret_648; }); mph_gc_push_root(ctx, (void**)&_arg_649); mph_types_Type* _arg_650 = right_type; mph_gc_push_root(ctx, (void**)&_arg_650); mph_types_TypeResult* _ret_651 = mph_types_TypeBinaryOp(ctx, NULL, _arg_646, _arg_649, _arg_650); mph_gc_pop_roots(ctx, 3); _ret_651; });
	mph_gc_push_root(ctx, (void**)&result);
	if (({ mph_types_TypeResult* _obj_652 = result; mph_gc_push_root(ctx, (void**)&_obj_652); mph_bool _ret_653 = _obj_652->has_error; mph_gc_pop_roots(ctx, 1); _ret_653; })) {
{
	({ mph_Checker* _arg_654 = c; mph_gc_push_root(ctx, (void**)&_arg_654); MorphString* _arg_657 = ({ mph_types_TypeResult* _obj_655 = result; mph_gc_push_root(ctx, (void**)&_obj_655); MorphString* _ret_656 = _obj_655->error_msg; mph_gc_pop_roots(ctx, 1); _ret_656; }); mph_gc_push_root(ctx, (void**)&_arg_657); mph_checker_add_error(ctx, NULL, _arg_654, _arg_657); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
	return ({ mph_types_TypeResult* _obj_658 = result; mph_gc_push_root(ctx, (void**)&_obj_658); mph_types_Type* _ret_659 = _obj_658->result; mph_gc_pop_roots(ctx, 1); _ret_659; });
	mph_gc_pop_roots(ctx, 3);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_check_var_statement(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&stmt);
	mph_types_Type* declared_type = mph_types_VoidType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&declared_type);
	if ((({ mph_ast_VarStatement* _obj_660 = stmt; mph_gc_push_root(ctx, (void**)&_obj_660); MorphString* _ret_661 = _obj_660->value_type; mph_gc_pop_roots(ctx, 1); _ret_661; }) != mph_string_new(ctx, "-"))) {
{
	if (mph_string_eq(ctx, ({ mph_ast_VarStatement* _obj_662 = stmt; mph_gc_push_root(ctx, (void**)&_obj_662); MorphString* _ret_663 = _obj_662->value_type; mph_gc_pop_roots(ctx, 1); _ret_663; }), mph_string_new(ctx, "int"))) {
{
	declared_type = mph_types_IntType(ctx, NULL);
}
	} else {
{
	if (mph_string_eq(ctx, ({ mph_ast_VarStatement* _obj_664 = stmt; mph_gc_push_root(ctx, (void**)&_obj_664); MorphString* _ret_665 = _obj_664->value_type; mph_gc_pop_roots(ctx, 1); _ret_665; }), mph_string_new(ctx, "string"))) {
{
	declared_type = mph_types_StringType(ctx, NULL);
}
	} else {
{
	if (mph_string_eq(ctx, ({ mph_ast_VarStatement* _obj_666 = stmt; mph_gc_push_root(ctx, (void**)&_obj_666); MorphString* _ret_667 = _obj_666->value_type; mph_gc_pop_roots(ctx, 1); _ret_667; }), mph_string_new(ctx, "bool"))) {
{
	declared_type = mph_types_BoolType(ctx, NULL);
}
	} else {
{
	({ mph_Checker* _arg_668 = c; mph_gc_push_root(ctx, (void**)&_arg_668); MorphString* _arg_674 = ({ MorphString* _lhs_671 = mph_string_new(ctx, "Unknown type: "); MorphString* _rhs_672 = ({ mph_ast_VarStatement* _obj_669 = stmt; mph_gc_push_root(ctx, (void**)&_obj_669); MorphString* _ret_670 = _obj_669->value_type; mph_gc_pop_roots(ctx, 1); _ret_670; }); mph_gc_push_root(ctx, (void**)&_lhs_671); mph_gc_push_root(ctx, (void**)&_rhs_672); MorphString* _ret_673 = mph_string_concat(ctx, _lhs_671, _rhs_672); mph_gc_pop_roots(ctx, 2); _ret_673; }); mph_gc_push_root(ctx, (void**)&_arg_674); mph_checker_add_error(ctx, NULL, _arg_668, _arg_674); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
}
	}
}
	}
}
	}
	if (({ mph_ast_VarStatement* _obj_675 = stmt; mph_gc_push_root(ctx, (void**)&_obj_675); mph_bool _ret_676 = _obj_675->has_value; mph_gc_pop_roots(ctx, 1); _ret_676; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "Variable '"));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_677 = stmt; mph_gc_push_root(ctx, (void**)&_obj_677); MorphString* _ret_678 = _obj_677->name; mph_gc_pop_roots(ctx, 1); _ret_678; }));
	mph_native_print(ctx, mph_string_new(ctx, "' declared with type "));
	mph_native_print(ctx, mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_679 = declared_type; mph_gc_push_root(ctx, (void**)&_obj_679); mph_int _ret_680 = _obj_679->kind; mph_gc_pop_roots(ctx, 1); _ret_680; })));
	mph_native_print(ctx, mph_string_new(ctx, " and has initial value\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "Variable '"));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_681 = stmt; mph_gc_push_root(ctx, (void**)&_obj_681); MorphString* _ret_682 = _obj_681->name; mph_gc_pop_roots(ctx, 1); _ret_682; }));
	mph_native_print(ctx, mph_string_new(ctx, "' declared with type "));
	mph_native_print(ctx, mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_683 = declared_type; mph_gc_push_root(ctx, (void**)&_obj_683); mph_int _ret_684 = _obj_683->kind; mph_gc_pop_roots(ctx, 1); _ret_684; })));
	mph_native_print(ctx, mph_string_new(ctx, " (no initial value)\n"));
}
	}
	return declared_type;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

void mph_check_program(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_Program* program) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&program);
	mph_native_print(ctx, mph_string_new(ctx, "Type checking program with "));
	mph_native_print_int(ctx, ({ mph_ast_Program* _obj_685 = program; mph_gc_push_root(ctx, (void**)&_obj_685); mph_int _ret_686 = _obj_685->statements_count; mph_gc_pop_roots(ctx, 1); _ret_686; }));
	mph_native_print(ctx, mph_string_new(ctx, " statements\n"));
	if (({ mph_Checker* _arg_687 = c; mph_gc_push_root(ctx, (void**)&_arg_687); mph_bool _ret_688 = mph_checker_has_errors(ctx, NULL, _arg_687); mph_gc_pop_roots(ctx, 1); _ret_688; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "Type checking completed with "));
	mph_native_print_int(ctx, ({ mph_Checker* _obj_689 = c; mph_gc_push_root(ctx, (void**)&_obj_689); mph_int _ret_690 = _obj_689->errors_count; mph_gc_pop_roots(ctx, 1); _ret_690; }));
	mph_native_print(ctx, mph_string_new(ctx, " error(s)\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "Type checking completed successfully\n"));
}
	}
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_check_builtin_function(MorphContext* ctx, void* _env_void, mph_Checker* c, MorphString* name, mph_int args_count) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&name);
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "native_print"))) {
{
	if ((args_count == 1)) {
{
	return mph_types_VoidType(ctx, NULL);
}
	} else {
{
	({ mph_Checker* _arg_691 = c; mph_gc_push_root(ctx, (void**)&_arg_691); MorphString* _arg_692 = mph_string_new(ctx, "native_print expects 1 argument"); mph_gc_push_root(ctx, (void**)&_arg_692); mph_checker_add_error(ctx, NULL, _arg_691, _arg_692); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "native_print_int"))) {
{
	if ((args_count == 1)) {
{
	return mph_types_VoidType(ctx, NULL);
}
	} else {
{
	({ mph_Checker* _arg_693 = c; mph_gc_push_root(ctx, (void**)&_arg_693); MorphString* _arg_694 = mph_string_new(ctx, "native_print_int expects 1 argument"); mph_gc_push_root(ctx, (void**)&_arg_694); mph_checker_add_error(ctx, NULL, _arg_693, _arg_694); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "panjang"))) {
{
	if ((args_count == 1)) {
{
	return mph_types_IntType(ctx, NULL);
}
	} else {
{
	({ mph_Checker* _arg_695 = c; mph_gc_push_root(ctx, (void**)&_arg_695); MorphString* _arg_696 = mph_string_new(ctx, "panjang expects 1 argument"); mph_gc_push_root(ctx, (void**)&_arg_696); mph_checker_add_error(ctx, NULL, _arg_695, _arg_696); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
}
	}
	if (mph_string_eq(ctx, name, mph_string_new(ctx, "substring"))) {
{
	if ((args_count == 3)) {
{
	return mph_types_StringType(ctx, NULL);
}
	} else {
{
	({ mph_Checker* _arg_697 = c; mph_gc_push_root(ctx, (void**)&_arg_697); MorphString* _arg_698 = mph_string_new(ctx, "substring expects 3 arguments"); mph_gc_push_root(ctx, (void**)&_arg_698); mph_checker_add_error(ctx, NULL, _arg_697, _arg_698); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
}
	}
	({ mph_Checker* _arg_699 = c; mph_gc_push_root(ctx, (void**)&_arg_699); MorphString* _arg_703 = ({ MorphString* _lhs_700 = mph_string_new(ctx, "Unknown built-in function: "); MorphString* _rhs_701 = name; mph_gc_push_root(ctx, (void**)&_lhs_700); mph_gc_push_root(ctx, (void**)&_rhs_701); MorphString* _ret_702 = mph_string_concat(ctx, _lhs_700, _rhs_701); mph_gc_pop_roots(ctx, 2); _ret_702; }); mph_gc_push_root(ctx, (void**)&_arg_703); mph_checker_add_error(ctx, NULL, _arg_699, _arg_703); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_check_assignment_compatibility(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&target_type);
	mph_gc_push_root(ctx, (void**)&value_type);
	if (({ mph_types_Type* _arg_704 = value_type; mph_gc_push_root(ctx, (void**)&_arg_704); mph_types_Type* _arg_705 = target_type; mph_gc_push_root(ctx, (void**)&_arg_705); mph_bool _ret_706 = mph_types_TypeAssignableTo(ctx, NULL, _arg_704, _arg_705); mph_gc_pop_roots(ctx, 2); _ret_706; })) {
{
	return 1;
}
	} else {
{
	({ mph_Checker* _arg_707 = c; mph_gc_push_root(ctx, (void**)&_arg_707); MorphString* _arg_721 = ({ MorphString* _lhs_718 = ({ MorphString* _lhs_713 = ({ MorphString* _lhs_710 = mph_string_new(ctx, "Cannot assign "); MorphString* _rhs_711 = mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_708 = value_type; mph_gc_push_root(ctx, (void**)&_obj_708); mph_int _ret_709 = _obj_708->kind; mph_gc_pop_roots(ctx, 1); _ret_709; })); mph_gc_push_root(ctx, (void**)&_lhs_710); mph_gc_push_root(ctx, (void**)&_rhs_711); MorphString* _ret_712 = mph_string_concat(ctx, _lhs_710, _rhs_711); mph_gc_pop_roots(ctx, 2); _ret_712; }); MorphString* _rhs_714 = mph_string_new(ctx, " to "); mph_gc_push_root(ctx, (void**)&_lhs_713); mph_gc_push_root(ctx, (void**)&_rhs_714); MorphString* _ret_715 = mph_string_concat(ctx, _lhs_713, _rhs_714); mph_gc_pop_roots(ctx, 2); _ret_715; }); MorphString* _rhs_719 = mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_716 = target_type; mph_gc_push_root(ctx, (void**)&_obj_716); mph_int _ret_717 = _obj_716->kind; mph_gc_pop_roots(ctx, 1); _ret_717; })); mph_gc_push_root(ctx, (void**)&_lhs_718); mph_gc_push_root(ctx, (void**)&_rhs_719); MorphString* _ret_720 = mph_string_concat(ctx, _lhs_718, _rhs_719); mph_gc_pop_roots(ctx, 2); _ret_720; }); mph_gc_push_root(ctx, (void**)&_arg_721); mph_checker_add_error(ctx, NULL, _arg_707, _arg_721); mph_gc_pop_roots(ctx, 2); });
	return 0;
}
	}
	mph_gc_pop_roots(ctx, 3);
}

void mph_checker_enter_scope(MorphContext* ctx, void* _env_void, mph_Checker* c) {
	mph_gc_push_root(ctx, (void**)&c);
	({ mph_Checker* _obj_724 = c; mph_gc_push_root(ctx, (void**)&_obj_724); _obj_724->current_scope_level = (({ mph_Checker* _obj_722 = c; mph_gc_push_root(ctx, (void**)&_obj_722); mph_int _ret_723 = _obj_722->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_723; }) + 1); mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Entered scope level "));
	mph_native_print_int(ctx, ({ mph_Checker* _obj_725 = c; mph_gc_push_root(ctx, (void**)&_obj_725); mph_int _ret_726 = _obj_725->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_726; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_checker_exit_scope(MorphContext* ctx, void* _env_void, mph_Checker* c) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_Checker* _obj_727 = c; mph_gc_push_root(ctx, (void**)&_obj_727); mph_int _ret_728 = _obj_727->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_728; }) > 0)) {
{
	({ mph_Checker* _obj_731 = c; mph_gc_push_root(ctx, (void**)&_obj_731); _obj_731->current_scope_level = (({ mph_Checker* _obj_729 = c; mph_gc_push_root(ctx, (void**)&_obj_729); mph_int _ret_730 = _obj_729->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_730; }) - 1); mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Exited to scope level "));
	mph_native_print_int(ctx, ({ mph_Checker* _obj_732 = c; mph_gc_push_root(ctx, (void**)&_obj_732); mph_int _ret_733 = _obj_732->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_733; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_infer_type_from_literal(MorphContext* ctx, void* _env_void, MorphString* literal, mph_int token_type) {
	mph_gc_push_root(ctx, (void**)&literal);
	if ((token_type == mph_token_TOKEN_INT)) {
{
	return mph_types_IntType(ctx, NULL);
}
	}
	if ((token_type == mph_token_TOKEN_STRING)) {
{
	return mph_types_StringType(ctx, NULL);
}
	}
	if ((token_type == mph_token_TOKEN_BENAR)) {
{
	return mph_types_BoolType(ctx, NULL);
}
	}
	if ((token_type == mph_token_TOKEN_SALAH)) {
{
	return mph_types_BoolType(ctx, NULL);
}
	}
	return mph_types_UnknownType(ctx, NULL);
	mph_gc_pop_roots(ctx, 1);
}

mph_Checker* mph_NewChecker(MorphContext* ctx, void* _env_void) {
	return mph_new_checker(ctx, NULL);
}

mph_types_Type* mph_CheckIntegerLiteral(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_Checker* _arg_734 = c; mph_gc_push_root(ctx, (void**)&_arg_734); mph_ast_IntegerLiteral* _arg_735 = lit; mph_gc_push_root(ctx, (void**)&_arg_735); mph_types_Type* _ret_736 = mph_check_integer_literal(ctx, NULL, _arg_734, _arg_735); mph_gc_pop_roots(ctx, 2); _ret_736; });
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_CheckStringLiteral(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_Checker* _arg_737 = c; mph_gc_push_root(ctx, (void**)&_arg_737); mph_ast_StringLiteral* _arg_738 = lit; mph_gc_push_root(ctx, (void**)&_arg_738); mph_types_Type* _ret_739 = mph_check_string_literal(ctx, NULL, _arg_737, _arg_738); mph_gc_pop_roots(ctx, 2); _ret_739; });
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_CheckBooleanLiteral(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_Checker* _arg_740 = c; mph_gc_push_root(ctx, (void**)&_arg_740); mph_ast_BooleanLiteral* _arg_741 = lit; mph_gc_push_root(ctx, (void**)&_arg_741); mph_types_Type* _ret_742 = mph_check_boolean_literal(ctx, NULL, _arg_740, _arg_741); mph_gc_pop_roots(ctx, 2); _ret_742; });
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_CheckBuiltinFunction(MorphContext* ctx, void* _env_void, mph_Checker* c, MorphString* name, mph_int args_count) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&name);
	return ({ mph_Checker* _arg_743 = c; mph_gc_push_root(ctx, (void**)&_arg_743); MorphString* _arg_744 = name; mph_gc_push_root(ctx, (void**)&_arg_744); mph_types_Type* _ret_745 = mph_check_builtin_function(ctx, NULL, _arg_743, _arg_744, args_count); mph_gc_pop_roots(ctx, 2); _ret_745; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_CheckAssignmentCompatibility(MorphContext* ctx, void* _env_void, mph_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&target_type);
	mph_gc_push_root(ctx, (void**)&value_type);
	return ({ mph_Checker* _arg_746 = c; mph_gc_push_root(ctx, (void**)&_arg_746); mph_types_Type* _arg_747 = target_type; mph_gc_push_root(ctx, (void**)&_arg_747); mph_types_Type* _arg_748 = value_type; mph_gc_push_root(ctx, (void**)&_arg_748); mph_bool _ret_749 = mph_check_assignment_compatibility(ctx, NULL, _arg_746, _arg_747, _arg_748); mph_gc_pop_roots(ctx, 3); _ret_749; });
	mph_gc_pop_roots(ctx, 3);
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
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
}
