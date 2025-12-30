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
#define MPH_TYPE_mph_ast_IndexExpression 22
#define MPH_TYPE_mph_parser_Parser 2
#define MPH_TYPE_mph_checker_Symbol 4
#define MPH_TYPE_mph_ast_Program 7
#define MPH_TYPE_mph_ast_VarStatement 8
#define MPH_TYPE_mph_ast_BlockStatement 12
#define MPH_TYPE_mph_ast_FloatLiteral 15
#define MPH_TYPE_mph_ast_BooleanLiteral 17
#define MPH_TYPE_mph_ast_CaseClause 24
#define MPH_TYPE_mph_ast_ContinueStatement 30
#define MPH_TYPE_mph_ast_Identifier 13
#define MPH_TYPE_mph_ast_InfixExpression 19
#define MPH_TYPE_mph_lexer_Lexer 1
#define MPH_TYPE_mph_checker_Checker 3
#define MPH_TYPE_mph_ast_Node 6
#define MPH_TYPE_mph_ast_IfExpression 20
#define MPH_TYPE_mph_ast_BreakStatement 29
#define MPH_TYPE_mph_types_Type 31
#define MPH_TYPE_mph_types_TypeResult 32
#define MPH_TYPE_mph_token_Token 5
#define MPH_TYPE_mph_ast_IntegerLiteral 14
#define MPH_TYPE_mph_ast_StringLiteral 16
#define MPH_TYPE_mph_ast_StructStatement 27
#define MPH_TYPE_mph_ast_ExpressionStatement 11
#define MPH_TYPE_mph_ast_PrefixExpression 18
#define MPH_TYPE_mph_ast_CallExpression 21
#define MPH_TYPE_mph_ast_MemberExpression 23
#define MPH_TYPE_mph_ast_SwitchStatement 25
#define MPH_TYPE_mph_ast_WhileStatement 26
#define MPH_TYPE_mph_ast_ImportStatement 28
#define MPH_TYPE_mph_ast_FunctionStatement 9
#define MPH_TYPE_mph_ast_ReturnStatement 10

// Struct Definitions (Env & Types)
typedef struct mph_lexer_Lexer mph_lexer_Lexer;
struct mph_lexer_Lexer {
	MorphString* input;
	mph_int position;
	mph_int read_position;
	mph_int ch;
	mph_int line;
	mph_int column;
};

typedef struct mph_parser_Parser mph_parser_Parser;
struct mph_parser_Parser {
	mph_lexer_Lexer* lexer;
	mph_token_Token* current_token;
	mph_token_Token* peek_token;
	mph_int errors_count;
};

typedef struct mph_checker_Checker mph_checker_Checker;
typedef struct mph_checker_Symbol mph_checker_Symbol;
struct mph_checker_Checker {
	mph_int errors_count;
	mph_int current_scope_level;
};

struct mph_checker_Symbol {
	MorphString* name;
	mph_types_Type* symbol_type;
	mph_bool is_constant;
	mph_int line;
	mph_int column;
};

typedef struct mph_token_Token mph_token_Token;
struct mph_token_Token {
	mph_int token_type;
	MorphString* literal;
	mph_int line;
	mph_int column;
};

typedef struct mph_ast_Node mph_ast_Node;
typedef struct mph_ast_Program mph_ast_Program;
typedef struct mph_ast_VarStatement mph_ast_VarStatement;
typedef struct mph_ast_FunctionStatement mph_ast_FunctionStatement;
typedef struct mph_ast_ReturnStatement mph_ast_ReturnStatement;
typedef struct mph_ast_ExpressionStatement mph_ast_ExpressionStatement;
typedef struct mph_ast_BlockStatement mph_ast_BlockStatement;
typedef struct mph_ast_Identifier mph_ast_Identifier;
typedef struct mph_ast_IntegerLiteral mph_ast_IntegerLiteral;
typedef struct mph_ast_FloatLiteral mph_ast_FloatLiteral;
typedef struct mph_ast_StringLiteral mph_ast_StringLiteral;
typedef struct mph_ast_BooleanLiteral mph_ast_BooleanLiteral;
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

struct mph_ast_Program {
	mph_ast_Node* base;
	mph_int statements_count;
};

struct mph_ast_VarStatement {
	mph_ast_Node* base;
	MorphString* name;
	MorphString* value_type;
	mph_bool has_value;
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

MorphTypeInfo mph_ti_mph_lexer_Lexer = { "Lexer", sizeof(mph_lexer_Lexer), 1, (size_t[]){offsetof(mph_lexer_Lexer, input)} };
MorphTypeInfo mph_ti_mph_parser_Parser = { "Parser", sizeof(mph_parser_Parser), 3, (size_t[]){offsetof(mph_parser_Parser, lexer), offsetof(mph_parser_Parser, current_token), offsetof(mph_parser_Parser, peek_token)} };
MorphTypeInfo mph_ti_mph_checker_Checker = { "Checker", sizeof(mph_checker_Checker), 0, NULL };
MorphTypeInfo mph_ti_mph_checker_Symbol = { "Symbol", sizeof(mph_checker_Symbol), 2, (size_t[]){offsetof(mph_checker_Symbol, name), offsetof(mph_checker_Symbol, symbol_type)} };
MorphTypeInfo mph_ti_mph_token_Token = { "Token", sizeof(mph_token_Token), 1, (size_t[]){offsetof(mph_token_Token, literal)} };
MorphTypeInfo mph_ti_mph_ast_Node = { "Node", sizeof(mph_ast_Node), 1, (size_t[]){offsetof(mph_ast_Node, token_literal)} };
MorphTypeInfo mph_ti_mph_ast_Program = { "Program", sizeof(mph_ast_Program), 1, (size_t[]){offsetof(mph_ast_Program, base)} };
MorphTypeInfo mph_ti_mph_ast_VarStatement = { "VarStatement", sizeof(mph_ast_VarStatement), 3, (size_t[]){offsetof(mph_ast_VarStatement, base), offsetof(mph_ast_VarStatement, name), offsetof(mph_ast_VarStatement, value_type)} };
MorphTypeInfo mph_ti_mph_ast_FunctionStatement = { "FunctionStatement", sizeof(mph_ast_FunctionStatement), 3, (size_t[]){offsetof(mph_ast_FunctionStatement, base), offsetof(mph_ast_FunctionStatement, name), offsetof(mph_ast_FunctionStatement, return_type)} };
MorphTypeInfo mph_ti_mph_ast_ReturnStatement = { "ReturnStatement", sizeof(mph_ast_ReturnStatement), 1, (size_t[]){offsetof(mph_ast_ReturnStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_ExpressionStatement = { "ExpressionStatement", sizeof(mph_ast_ExpressionStatement), 1, (size_t[]){offsetof(mph_ast_ExpressionStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_BlockStatement = { "BlockStatement", sizeof(mph_ast_BlockStatement), 1, (size_t[]){offsetof(mph_ast_BlockStatement, base)} };
MorphTypeInfo mph_ti_mph_ast_Identifier = { "Identifier", sizeof(mph_ast_Identifier), 2, (size_t[]){offsetof(mph_ast_Identifier, base), offsetof(mph_ast_Identifier, value)} };
MorphTypeInfo mph_ti_mph_ast_IntegerLiteral = { "IntegerLiteral", sizeof(mph_ast_IntegerLiteral), 1, (size_t[]){offsetof(mph_ast_IntegerLiteral, base)} };
MorphTypeInfo mph_ti_mph_ast_FloatLiteral = { "FloatLiteral", sizeof(mph_ast_FloatLiteral), 2, (size_t[]){offsetof(mph_ast_FloatLiteral, base), offsetof(mph_ast_FloatLiteral, value_str)} };
MorphTypeInfo mph_ti_mph_ast_StringLiteral = { "StringLiteral", sizeof(mph_ast_StringLiteral), 2, (size_t[]){offsetof(mph_ast_StringLiteral, base), offsetof(mph_ast_StringLiteral, value)} };
MorphTypeInfo mph_ti_mph_ast_BooleanLiteral = { "BooleanLiteral", sizeof(mph_ast_BooleanLiteral), 1, (size_t[]){offsetof(mph_ast_BooleanLiteral, base)} };
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
MorphTypeInfo mph_ti_mph_types_Type = { "Type", sizeof(mph_types_Type), 1, (size_t[]){offsetof(mph_types_Type, name)} };
MorphTypeInfo mph_ti_mph_types_TypeResult = { "TypeResult", sizeof(mph_types_TypeResult), 2, (size_t[]){offsetof(mph_types_TypeResult, result), offsetof(mph_types_TypeResult, error_msg)} };

// Global Variables
mph_int mph_parser_PRECEDENCE_LOWEST;
mph_int mph_parser_PRECEDENCE_EQUALS;
mph_int mph_parser_PRECEDENCE_LESSGREATER;
mph_int mph_parser_PRECEDENCE_SUM;
mph_int mph_parser_PRECEDENCE_PRODUCT;
mph_int mph_parser_PRECEDENCE_PREFIX;
mph_int mph_parser_PRECEDENCE_CALL;
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
mph_int mph_total_tests;
mph_int mph_passed_tests;
mph_int mph_failed_tests;

// Function Prototypes
void mph_test_pass(MorphContext* ctx, void* _env_void, MorphString* name);
void mph_test_fail(MorphContext* ctx, void* _env_void, MorphString* name);
void mph_test_token_module(MorphContext* ctx, void* _env_void);
void mph_test_types_module(MorphContext* ctx, void* _env_void);
void mph_test_ast_module(MorphContext* ctx, void* _env_void);
void mph_test_lexer_module(MorphContext* ctx, void* _env_void);
void mph_test_parser_module(MorphContext* ctx, void* _env_void);
void mph_test_checker_module(MorphContext* ctx, void* _env_void);
void mph_test_integration(MorphContext* ctx, void* _env_void);
void mph_main(MorphContext* ctx, void* _env_void);
mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column);
mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void);
mph_ast_Identifier* mph_ast_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column);
mph_ast_IntegerLiteral* mph_ast_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column);
mph_ast_StringLiteral* mph_ast_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column);
mph_ast_BooleanLiteral* mph_ast_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column);
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
mph_lexer_Lexer* mph_lexer_new_lexer(MorphContext* ctx, void* _env_void, MorphString* input);
void mph_lexer_lexer_read_char(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
mph_int mph_lexer_char_to_ascii(MorphContext* ctx, void* _env_void, MorphString* char_str);
mph_bool mph_lexer_is_letter(MorphContext* ctx, void* _env_void, mph_int ch);
mph_bool mph_lexer_is_digit(MorphContext* ctx, void* _env_void, mph_int ch);
mph_bool mph_lexer_is_whitespace(MorphContext* ctx, void* _env_void, mph_int ch);
mph_int mph_lexer_lexer_peek_char(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
void mph_lexer_lexer_skip_whitespace(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
MorphString* mph_lexer_lexer_read_identifier(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
MorphString* mph_lexer_lexer_read_number(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
MorphString* mph_lexer_lexer_read_string(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
mph_lexer_Lexer* mph_lexer_NewLexer(MorphContext* ctx, void* _env_void, MorphString* input);
mph_token_Token* mph_lexer_LexerNextToken(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
mph_parser_Parser* mph_parser_NewParser(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
void mph_parser_ParserNextToken(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_bool mph_parser_ParserCurrentTokenIs(MorphContext* ctx, void* _env_void, mph_parser_Parser* p, mph_int token_type);
mph_bool mph_parser_ParserPeekTokenIs(MorphContext* ctx, void* _env_void, mph_parser_Parser* p, mph_int token_type);
mph_bool mph_parser_ParserExpectPeek(MorphContext* ctx, void* _env_void, mph_parser_Parser* p, mph_int token_type);
mph_int mph_parser_GetTokenPrecedence(MorphContext* ctx, void* _env_void, mph_int token_type);
mph_int mph_parser_ParserPeekPrecedence(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_int mph_parser_ParserCurrentPrecedence(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_ast_Identifier* mph_parser_ParserParseIdentifier(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_ast_IntegerLiteral* mph_parser_ParserParseIntegerLiteral(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_ast_StringLiteral* mph_parser_ParserParseStringLiteral(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_ast_BooleanLiteral* mph_parser_ParserParseBooleanLiteral(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_ast_PrefixExpression* mph_parser_ParserParsePrefixExpression(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_ast_VarStatement* mph_parser_ParserParseVarStatement(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_ast_Program* mph_parser_ParserParseProgram(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_int mph_parser_StringToInt(MorphContext* ctx, void* _env_void, MorphString* s);
mph_bool mph_parser_ParserHasErrors(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
void mph_parser_ParserPrintErrors(MorphContext* ctx, void* _env_void, mph_parser_Parser* p);
mph_checker_Checker* mph_checker_new_checker(MorphContext* ctx, void* _env_void);
void mph_checker_checker_add_error(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, MorphString* message);
mph_bool mph_checker_checker_has_errors(MorphContext* ctx, void* _env_void, mph_checker_Checker* c);
mph_types_Type* mph_checker_check_integer_literal(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_IntegerLiteral* lit);
mph_types_Type* mph_checker_check_string_literal(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_StringLiteral* lit);
mph_types_Type* mph_checker_check_boolean_literal(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_BooleanLiteral* lit);
mph_types_Type* mph_checker_check_identifier(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_Identifier* ident);
mph_types_Type* mph_checker_check_prefix_expression(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_PrefixExpression* expr);
mph_types_Type* mph_checker_check_infix_expression(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_InfixExpression* expr);
mph_types_Type* mph_checker_check_var_statement(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_VarStatement* stmt);
void mph_checker_check_program(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_Program* program);
mph_types_Type* mph_checker_check_builtin_function(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, MorphString* name, mph_int args_count);
mph_bool mph_checker_check_assignment_compatibility(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type);
void mph_checker_checker_enter_scope(MorphContext* ctx, void* _env_void, mph_checker_Checker* c);
void mph_checker_checker_exit_scope(MorphContext* ctx, void* _env_void, mph_checker_Checker* c);
mph_types_Type* mph_checker_infer_type_from_literal(MorphContext* ctx, void* _env_void, MorphString* literal, mph_int token_type);
mph_checker_Checker* mph_checker_NewChecker(MorphContext* ctx, void* _env_void);
mph_types_Type* mph_checker_CheckIntegerLiteral(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_IntegerLiteral* lit);
mph_types_Type* mph_checker_CheckStringLiteral(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_StringLiteral* lit);
mph_types_Type* mph_checker_CheckBooleanLiteral(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_BooleanLiteral* lit);
mph_types_Type* mph_checker_CheckBuiltinFunction(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, MorphString* name, mph_int args_count);
mph_bool mph_checker_CheckAssignmentCompatibility(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type);
mph_token_Token* mph_token_MakeToken(MorphContext* ctx, void* _env_void, mph_int t_type, MorphString* lit, mph_int ln, mph_int col);
MorphString* mph_token_TokenTypeString(MorphContext* ctx, void* _env_void, mph_int t_type);
mph_int mph_token_LookupKeyword(MorphContext* ctx, void* _env_void, MorphString* ident);

// Function Definitions
mph_lexer_Lexer* mph_lexer_new_lexer(MorphContext* ctx, void* _env_void, MorphString* input) {
	mph_gc_push_root(ctx, (void**)&input);
	mph_lexer_Lexer* l = ({ mph_lexer_Lexer* _t = (mph_lexer_Lexer*)mph_alloc(ctx, sizeof(mph_lexer_Lexer), &mph_ti_mph_lexer_Lexer); mph_gc_push_root(ctx, (void**)&_t); _t->line = 1; _t->column = 0; _t->input = input; _t->position = 0; _t->read_position = 0; _t->ch = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_lexer_Lexer* _arg_1 = l; mph_gc_push_root(ctx, (void**)&_arg_1); mph_lexer_lexer_read_char(ctx, NULL, _arg_1); mph_gc_pop_roots(ctx, 1); });
	return l;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

void mph_lexer_lexer_read_char(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	if ((({ mph_lexer_Lexer* _obj_2 = l; mph_gc_push_root(ctx, (void**)&_obj_2); mph_int _ret_3 = _obj_2->read_position; mph_gc_pop_roots(ctx, 1); _ret_3; }) >= ({ MorphString* _len_arg_6 = ({ mph_lexer_Lexer* _obj_4 = l; mph_gc_push_root(ctx, (void**)&_obj_4); MorphString* _ret_5 = _obj_4->input; mph_gc_pop_roots(ctx, 1); _ret_5; }); mph_gc_push_root(ctx, (void**)&_len_arg_6); mph_int _ret_7 = ((MorphString*)_len_arg_6)->length; mph_gc_pop_roots(ctx, 1); _ret_7; }))) {
{
	({ mph_lexer_Lexer* _obj_8 = l; mph_gc_push_root(ctx, (void**)&_obj_8); _obj_8->ch = 0; mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	MorphString* char_str = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_9 = l; mph_gc_push_root(ctx, (void**)&_obj_9); MorphString* _ret_10 = _obj_9->input; mph_gc_pop_roots(ctx, 1); _ret_10; }), ({ mph_lexer_Lexer* _obj_11 = l; mph_gc_push_root(ctx, (void**)&_obj_11); mph_int _ret_12 = _obj_11->read_position; mph_gc_pop_roots(ctx, 1); _ret_12; }), (({ mph_lexer_Lexer* _obj_13 = l; mph_gc_push_root(ctx, (void**)&_obj_13); mph_int _ret_14 = _obj_13->read_position; mph_gc_pop_roots(ctx, 1); _ret_14; }) + 1));
	mph_gc_push_root(ctx, (void**)&char_str);
	({ mph_lexer_Lexer* _obj_17 = l; mph_gc_push_root(ctx, (void**)&_obj_17); _obj_17->ch = ({ MorphString* _arg_15 = char_str; mph_gc_push_root(ctx, (void**)&_arg_15); mph_int _ret_16 = mph_lexer_char_to_ascii(ctx, NULL, _arg_15); mph_gc_pop_roots(ctx, 1); _ret_16; }); mph_gc_pop_roots(ctx, 1); });
	mph_gc_pop_roots(ctx, 1);
}
	}
	({ mph_lexer_Lexer* _obj_20 = l; mph_gc_push_root(ctx, (void**)&_obj_20); _obj_20->position = ({ mph_lexer_Lexer* _obj_18 = l; mph_gc_push_root(ctx, (void**)&_obj_18); mph_int _ret_19 = _obj_18->read_position; mph_gc_pop_roots(ctx, 1); _ret_19; }); mph_gc_pop_roots(ctx, 1); });
	({ mph_lexer_Lexer* _obj_23 = l; mph_gc_push_root(ctx, (void**)&_obj_23); _obj_23->read_position = (({ mph_lexer_Lexer* _obj_21 = l; mph_gc_push_root(ctx, (void**)&_obj_21); mph_int _ret_22 = _obj_21->read_position; mph_gc_pop_roots(ctx, 1); _ret_22; }) + 1); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_lexer_Lexer* _obj_24 = l; mph_gc_push_root(ctx, (void**)&_obj_24); mph_int _ret_25 = _obj_24->ch; mph_gc_pop_roots(ctx, 1); _ret_25; }) == 10)) {
{
	({ mph_lexer_Lexer* _obj_28 = l; mph_gc_push_root(ctx, (void**)&_obj_28); _obj_28->line = (({ mph_lexer_Lexer* _obj_26 = l; mph_gc_push_root(ctx, (void**)&_obj_26); mph_int _ret_27 = _obj_26->line; mph_gc_pop_roots(ctx, 1); _ret_27; }) + 1); mph_gc_pop_roots(ctx, 1); });
	({ mph_lexer_Lexer* _obj_29 = l; mph_gc_push_root(ctx, (void**)&_obj_29); _obj_29->column = 0; mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ mph_lexer_Lexer* _obj_32 = l; mph_gc_push_root(ctx, (void**)&_obj_32); _obj_32->column = (({ mph_lexer_Lexer* _obj_30 = l; mph_gc_push_root(ctx, (void**)&_obj_30); mph_int _ret_31 = _obj_30->column; mph_gc_pop_roots(ctx, 1); _ret_31; }) + 1); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_lexer_char_to_ascii(MorphContext* ctx, void* _env_void, MorphString* char_str) {
	mph_gc_push_root(ctx, (void**)&char_str);
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, " "))) {
{
	return 32;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "!"))) {
{
	return 33;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "\""))) {
{
	return 34;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "#"))) {
{
	return 35;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "$"))) {
{
	return 36;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "%"))) {
{
	return 37;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "&"))) {
{
	return 38;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "'"))) {
{
	return 39;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "("))) {
{
	return 40;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, ")"))) {
{
	return 41;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "*"))) {
{
	return 42;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "+"))) {
{
	return 43;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, ","))) {
{
	return 44;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "-"))) {
{
	return 45;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "."))) {
{
	return 46;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "/"))) {
{
	return 47;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "0"))) {
{
	return 48;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "1"))) {
{
	return 49;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "2"))) {
{
	return 50;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "3"))) {
{
	return 51;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "4"))) {
{
	return 52;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "5"))) {
{
	return 53;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "6"))) {
{
	return 54;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "7"))) {
{
	return 55;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "8"))) {
{
	return 56;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "9"))) {
{
	return 57;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, ":"))) {
{
	return 58;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, ";"))) {
{
	return 59;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "<"))) {
{
	return 60;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "="))) {
{
	return 61;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, ">"))) {
{
	return 62;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "?"))) {
{
	return 63;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "@"))) {
{
	return 64;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "A"))) {
{
	return 65;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "B"))) {
{
	return 66;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "C"))) {
{
	return 67;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "D"))) {
{
	return 68;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "E"))) {
{
	return 69;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "F"))) {
{
	return 70;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "G"))) {
{
	return 71;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "H"))) {
{
	return 72;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "I"))) {
{
	return 73;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "J"))) {
{
	return 74;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "K"))) {
{
	return 75;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "L"))) {
{
	return 76;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "M"))) {
{
	return 77;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "N"))) {
{
	return 78;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "O"))) {
{
	return 79;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "P"))) {
{
	return 80;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "Q"))) {
{
	return 81;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "R"))) {
{
	return 82;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "S"))) {
{
	return 83;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "T"))) {
{
	return 84;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "U"))) {
{
	return 85;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "V"))) {
{
	return 86;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "W"))) {
{
	return 87;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "X"))) {
{
	return 88;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "Y"))) {
{
	return 89;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "Z"))) {
{
	return 90;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "["))) {
{
	return 91;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "\\"))) {
{
	return 92;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "]"))) {
{
	return 93;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "^"))) {
{
	return 94;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "_"))) {
{
	return 95;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "`"))) {
{
	return 96;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "a"))) {
{
	return 97;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "b"))) {
{
	return 98;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "c"))) {
{
	return 99;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "d"))) {
{
	return 100;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "e"))) {
{
	return 101;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "f"))) {
{
	return 102;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "g"))) {
{
	return 103;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "h"))) {
{
	return 104;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "i"))) {
{
	return 105;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "j"))) {
{
	return 106;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "k"))) {
{
	return 107;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "l"))) {
{
	return 108;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "m"))) {
{
	return 109;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "n"))) {
{
	return 110;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "o"))) {
{
	return 111;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "p"))) {
{
	return 112;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "q"))) {
{
	return 113;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "r"))) {
{
	return 114;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "s"))) {
{
	return 115;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "t"))) {
{
	return 116;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "u"))) {
{
	return 117;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "v"))) {
{
	return 118;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "w"))) {
{
	return 119;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "x"))) {
{
	return 120;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "y"))) {
{
	return 121;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "z"))) {
{
	return 122;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "{"))) {
{
	return 123;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "|"))) {
{
	return 124;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "}"))) {
{
	return 125;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "~"))) {
{
	return 126;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "\n"))) {
{
	return 10;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "\t"))) {
{
	return 9;
}
	}
	if (mph_string_eq(ctx, char_str, mph_string_new(ctx, "\r"))) {
{
	return 13;
}
	}
	return 0;
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_lexer_is_letter(MorphContext* ctx, void* _env_void, mph_int ch) {
	if ((ch >= 97)) {
{
	if ((ch <= 122)) {
{
	return 1;
}
	}
}
	}
	if ((ch >= 65)) {
{
	if ((ch <= 90)) {
{
	return 1;
}
	}
}
	}
	if ((ch == 95)) {
{
	return 1;
}
	}
	return 0;
}

mph_bool mph_lexer_is_digit(MorphContext* ctx, void* _env_void, mph_int ch) {
	if ((ch >= 48)) {
{
	if ((ch <= 57)) {
{
	return 1;
}
	}
}
	}
	return 0;
}

mph_bool mph_lexer_is_whitespace(MorphContext* ctx, void* _env_void, mph_int ch) {
	if ((ch == 32)) {
{
	return 1;
}
	}
	if ((ch == 9)) {
{
	return 1;
}
	}
	if ((ch == 10)) {
{
	return 1;
}
	}
	if ((ch == 13)) {
{
	return 1;
}
	}
	return 0;
}

mph_int mph_lexer_lexer_peek_char(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	if ((({ mph_lexer_Lexer* _obj_33 = l; mph_gc_push_root(ctx, (void**)&_obj_33); mph_int _ret_34 = _obj_33->read_position; mph_gc_pop_roots(ctx, 1); _ret_34; }) >= ({ MorphString* _len_arg_37 = ({ mph_lexer_Lexer* _obj_35 = l; mph_gc_push_root(ctx, (void**)&_obj_35); MorphString* _ret_36 = _obj_35->input; mph_gc_pop_roots(ctx, 1); _ret_36; }); mph_gc_push_root(ctx, (void**)&_len_arg_37); mph_int _ret_38 = ((MorphString*)_len_arg_37)->length; mph_gc_pop_roots(ctx, 1); _ret_38; }))) {
{
	return 0;
}
	} else {
{
	MorphString* char_str = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_39 = l; mph_gc_push_root(ctx, (void**)&_obj_39); MorphString* _ret_40 = _obj_39->input; mph_gc_pop_roots(ctx, 1); _ret_40; }), ({ mph_lexer_Lexer* _obj_41 = l; mph_gc_push_root(ctx, (void**)&_obj_41); mph_int _ret_42 = _obj_41->read_position; mph_gc_pop_roots(ctx, 1); _ret_42; }), (({ mph_lexer_Lexer* _obj_43 = l; mph_gc_push_root(ctx, (void**)&_obj_43); mph_int _ret_44 = _obj_43->read_position; mph_gc_pop_roots(ctx, 1); _ret_44; }) + 1));
	mph_gc_push_root(ctx, (void**)&char_str);
	return ({ MorphString* _arg_45 = char_str; mph_gc_push_root(ctx, (void**)&_arg_45); mph_int _ret_46 = mph_lexer_char_to_ascii(ctx, NULL, _arg_45); mph_gc_pop_roots(ctx, 1); _ret_46; });
	mph_gc_pop_roots(ctx, 1);
}
	}
	mph_gc_pop_roots(ctx, 1);
}

void mph_lexer_lexer_skip_whitespace(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	while (mph_lexer_is_whitespace(ctx, NULL, ({ mph_lexer_Lexer* _obj_47 = l; mph_gc_push_root(ctx, (void**)&_obj_47); mph_int _ret_48 = _obj_47->ch; mph_gc_pop_roots(ctx, 1); _ret_48; }))) {
{
	({ mph_lexer_Lexer* _arg_49 = l; mph_gc_push_root(ctx, (void**)&_arg_49); mph_lexer_lexer_read_char(ctx, NULL, _arg_49); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_lexer_read_identifier(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = ({ mph_lexer_Lexer* _obj_50 = l; mph_gc_push_root(ctx, (void**)&_obj_50); mph_int _ret_51 = _obj_50->position; mph_gc_pop_roots(ctx, 1); _ret_51; });
	mph_bool done = 0;
	while ((done == 0)) {
{
	if (mph_lexer_is_letter(ctx, NULL, ({ mph_lexer_Lexer* _obj_52 = l; mph_gc_push_root(ctx, (void**)&_obj_52); mph_int _ret_53 = _obj_52->ch; mph_gc_pop_roots(ctx, 1); _ret_53; }))) {
{
	({ mph_lexer_Lexer* _arg_54 = l; mph_gc_push_root(ctx, (void**)&_arg_54); mph_lexer_lexer_read_char(ctx, NULL, _arg_54); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	if (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _obj_55 = l; mph_gc_push_root(ctx, (void**)&_obj_55); mph_int _ret_56 = _obj_55->ch; mph_gc_pop_roots(ctx, 1); _ret_56; }))) {
{
	({ mph_lexer_Lexer* _arg_57 = l; mph_gc_push_root(ctx, (void**)&_arg_57); mph_lexer_lexer_read_char(ctx, NULL, _arg_57); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	done = 1;
}
	}
}
	}
}
	}
	return mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_58 = l; mph_gc_push_root(ctx, (void**)&_obj_58); MorphString* _ret_59 = _obj_58->input; mph_gc_pop_roots(ctx, 1); _ret_59; }), position, ({ mph_lexer_Lexer* _obj_60 = l; mph_gc_push_root(ctx, (void**)&_obj_60); mph_int _ret_61 = _obj_60->position; mph_gc_pop_roots(ctx, 1); _ret_61; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_lexer_read_number(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = ({ mph_lexer_Lexer* _obj_62 = l; mph_gc_push_root(ctx, (void**)&_obj_62); mph_int _ret_63 = _obj_62->position; mph_gc_pop_roots(ctx, 1); _ret_63; });
	while (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _obj_64 = l; mph_gc_push_root(ctx, (void**)&_obj_64); mph_int _ret_65 = _obj_64->ch; mph_gc_pop_roots(ctx, 1); _ret_65; }))) {
{
	({ mph_lexer_Lexer* _arg_66 = l; mph_gc_push_root(ctx, (void**)&_arg_66); mph_lexer_lexer_read_char(ctx, NULL, _arg_66); mph_gc_pop_roots(ctx, 1); });
}
	}
	return mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_67 = l; mph_gc_push_root(ctx, (void**)&_obj_67); MorphString* _ret_68 = _obj_67->input; mph_gc_pop_roots(ctx, 1); _ret_68; }), position, ({ mph_lexer_Lexer* _obj_69 = l; mph_gc_push_root(ctx, (void**)&_obj_69); mph_int _ret_70 = _obj_69->position; mph_gc_pop_roots(ctx, 1); _ret_70; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_lexer_read_string(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = (({ mph_lexer_Lexer* _obj_71 = l; mph_gc_push_root(ctx, (void**)&_obj_71); mph_int _ret_72 = _obj_71->position; mph_gc_pop_roots(ctx, 1); _ret_72; }) + 1);
	({ mph_lexer_Lexer* _arg_73 = l; mph_gc_push_root(ctx, (void**)&_arg_73); mph_lexer_lexer_read_char(ctx, NULL, _arg_73); mph_gc_pop_roots(ctx, 1); });
	mph_bool should_continue = 1;
	while (should_continue) {
{
	if ((({ mph_lexer_Lexer* _obj_74 = l; mph_gc_push_root(ctx, (void**)&_obj_74); mph_int _ret_75 = _obj_74->ch; mph_gc_pop_roots(ctx, 1); _ret_75; }) == 34)) {
{
	should_continue = 0;
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_76 = l; mph_gc_push_root(ctx, (void**)&_obj_76); mph_int _ret_77 = _obj_76->ch; mph_gc_pop_roots(ctx, 1); _ret_77; }) == 0)) {
{
	should_continue = 0;
}
	} else {
{
	({ mph_lexer_Lexer* _arg_78 = l; mph_gc_push_root(ctx, (void**)&_arg_78); mph_lexer_lexer_read_char(ctx, NULL, _arg_78); mph_gc_pop_roots(ctx, 1); });
}
	}
}
	}
}
	}
	return mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_79 = l; mph_gc_push_root(ctx, (void**)&_obj_79); MorphString* _ret_80 = _obj_79->input; mph_gc_pop_roots(ctx, 1); _ret_80; }), position, ({ mph_lexer_Lexer* _obj_81 = l; mph_gc_push_root(ctx, (void**)&_obj_81); mph_int _ret_82 = _obj_81->position; mph_gc_pop_roots(ctx, 1); _ret_82; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_lexer_Lexer* mph_lexer_NewLexer(MorphContext* ctx, void* _env_void, MorphString* input) {
	mph_gc_push_root(ctx, (void**)&input);
	return ({ MorphString* _arg_83 = input; mph_gc_push_root(ctx, (void**)&_arg_83); mph_lexer_Lexer* _ret_84 = mph_lexer_new_lexer(ctx, NULL, _arg_83); mph_gc_pop_roots(ctx, 1); _ret_84; });
	mph_gc_pop_roots(ctx, 1);
}

mph_token_Token* mph_lexer_LexerNextToken(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_lexer_Lexer* _arg_85 = l; mph_gc_push_root(ctx, (void**)&_arg_85); mph_lexer_lexer_skip_whitespace(ctx, NULL, _arg_85); mph_gc_pop_roots(ctx, 1); });
	mph_token_Token* tok = ({ MorphString* _arg_86 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_86); mph_token_Token* _ret_91 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ILLEGAL, _arg_86, ({ mph_lexer_Lexer* _obj_87 = l; mph_gc_push_root(ctx, (void**)&_obj_87); mph_int _ret_88 = _obj_87->line; mph_gc_pop_roots(ctx, 1); _ret_88; }), ({ mph_lexer_Lexer* _obj_89 = l; mph_gc_push_root(ctx, (void**)&_obj_89); mph_int _ret_90 = _obj_89->column; mph_gc_pop_roots(ctx, 1); _ret_90; })); mph_gc_pop_roots(ctx, 1); _ret_91; });
	mph_gc_push_root(ctx, (void**)&tok);
	if ((({ mph_lexer_Lexer* _obj_92 = l; mph_gc_push_root(ctx, (void**)&_obj_92); mph_int _ret_93 = _obj_92->ch; mph_gc_pop_roots(ctx, 1); _ret_93; }) == 61)) {
{
	if ((({ mph_lexer_Lexer* _arg_94 = l; mph_gc_push_root(ctx, (void**)&_arg_94); mph_int _ret_95 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_94); mph_gc_pop_roots(ctx, 1); _ret_95; }) == 61)) {
{
	mph_int ch = ({ mph_lexer_Lexer* _obj_96 = l; mph_gc_push_root(ctx, (void**)&_obj_96); mph_int _ret_97 = _obj_96->ch; mph_gc_pop_roots(ctx, 1); _ret_97; });
	({ mph_lexer_Lexer* _arg_98 = l; mph_gc_push_root(ctx, (void**)&_arg_98); mph_lexer_lexer_read_char(ctx, NULL, _arg_98); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_99 = mph_string_new(ctx, "=="); mph_gc_push_root(ctx, (void**)&_arg_99); mph_token_Token* _ret_104 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_EQ, _arg_99, ({ mph_lexer_Lexer* _obj_100 = l; mph_gc_push_root(ctx, (void**)&_obj_100); mph_int _ret_101 = _obj_100->line; mph_gc_pop_roots(ctx, 1); _ret_101; }), ({ mph_lexer_Lexer* _obj_102 = l; mph_gc_push_root(ctx, (void**)&_obj_102); mph_int _ret_103 = _obj_102->column; mph_gc_pop_roots(ctx, 1); _ret_103; })); mph_gc_pop_roots(ctx, 1); _ret_104; });
}
	} else {
{
	tok = ({ MorphString* _arg_105 = mph_string_new(ctx, "="); mph_gc_push_root(ctx, (void**)&_arg_105); mph_token_Token* _ret_110 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ASSIGN, _arg_105, ({ mph_lexer_Lexer* _obj_106 = l; mph_gc_push_root(ctx, (void**)&_obj_106); mph_int _ret_107 = _obj_106->line; mph_gc_pop_roots(ctx, 1); _ret_107; }), ({ mph_lexer_Lexer* _obj_108 = l; mph_gc_push_root(ctx, (void**)&_obj_108); mph_int _ret_109 = _obj_108->column; mph_gc_pop_roots(ctx, 1); _ret_109; })); mph_gc_pop_roots(ctx, 1); _ret_110; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_111 = l; mph_gc_push_root(ctx, (void**)&_obj_111); mph_int _ret_112 = _obj_111->ch; mph_gc_pop_roots(ctx, 1); _ret_112; }) == 43)) {
{
	tok = ({ MorphString* _arg_113 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_113); mph_token_Token* _ret_118 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_PLUS, _arg_113, ({ mph_lexer_Lexer* _obj_114 = l; mph_gc_push_root(ctx, (void**)&_obj_114); mph_int _ret_115 = _obj_114->line; mph_gc_pop_roots(ctx, 1); _ret_115; }), ({ mph_lexer_Lexer* _obj_116 = l; mph_gc_push_root(ctx, (void**)&_obj_116); mph_int _ret_117 = _obj_116->column; mph_gc_pop_roots(ctx, 1); _ret_117; })); mph_gc_pop_roots(ctx, 1); _ret_118; });
}
	} else if ((({ mph_lexer_Lexer* _obj_119 = l; mph_gc_push_root(ctx, (void**)&_obj_119); mph_int _ret_120 = _obj_119->ch; mph_gc_pop_roots(ctx, 1); _ret_120; }) == 45)) {
{
	if ((({ mph_lexer_Lexer* _arg_121 = l; mph_gc_push_root(ctx, (void**)&_arg_121); mph_int _ret_122 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_121); mph_gc_pop_roots(ctx, 1); _ret_122; }) == 62)) {
{
	({ mph_lexer_Lexer* _arg_123 = l; mph_gc_push_root(ctx, (void**)&_arg_123); mph_lexer_lexer_read_char(ctx, NULL, _arg_123); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_124 = mph_string_new(ctx, "->"); mph_gc_push_root(ctx, (void**)&_arg_124); mph_token_Token* _ret_129 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ARROW, _arg_124, ({ mph_lexer_Lexer* _obj_125 = l; mph_gc_push_root(ctx, (void**)&_obj_125); mph_int _ret_126 = _obj_125->line; mph_gc_pop_roots(ctx, 1); _ret_126; }), ({ mph_lexer_Lexer* _obj_127 = l; mph_gc_push_root(ctx, (void**)&_obj_127); mph_int _ret_128 = _obj_127->column; mph_gc_pop_roots(ctx, 1); _ret_128; })); mph_gc_pop_roots(ctx, 1); _ret_129; });
}
	} else {
{
	tok = ({ MorphString* _arg_130 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_130); mph_token_Token* _ret_135 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_MINUS, _arg_130, ({ mph_lexer_Lexer* _obj_131 = l; mph_gc_push_root(ctx, (void**)&_obj_131); mph_int _ret_132 = _obj_131->line; mph_gc_pop_roots(ctx, 1); _ret_132; }), ({ mph_lexer_Lexer* _obj_133 = l; mph_gc_push_root(ctx, (void**)&_obj_133); mph_int _ret_134 = _obj_133->column; mph_gc_pop_roots(ctx, 1); _ret_134; })); mph_gc_pop_roots(ctx, 1); _ret_135; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_136 = l; mph_gc_push_root(ctx, (void**)&_obj_136); mph_int _ret_137 = _obj_136->ch; mph_gc_pop_roots(ctx, 1); _ret_137; }) == 33)) {
{
	if ((({ mph_lexer_Lexer* _arg_138 = l; mph_gc_push_root(ctx, (void**)&_arg_138); mph_int _ret_139 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_138); mph_gc_pop_roots(ctx, 1); _ret_139; }) == 61)) {
{
	({ mph_lexer_Lexer* _arg_140 = l; mph_gc_push_root(ctx, (void**)&_arg_140); mph_lexer_lexer_read_char(ctx, NULL, _arg_140); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_141 = mph_string_new(ctx, "!="); mph_gc_push_root(ctx, (void**)&_arg_141); mph_token_Token* _ret_146 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_NOT_EQ, _arg_141, ({ mph_lexer_Lexer* _obj_142 = l; mph_gc_push_root(ctx, (void**)&_obj_142); mph_int _ret_143 = _obj_142->line; mph_gc_pop_roots(ctx, 1); _ret_143; }), ({ mph_lexer_Lexer* _obj_144 = l; mph_gc_push_root(ctx, (void**)&_obj_144); mph_int _ret_145 = _obj_144->column; mph_gc_pop_roots(ctx, 1); _ret_145; })); mph_gc_pop_roots(ctx, 1); _ret_146; });
}
	} else {
{
	tok = ({ MorphString* _arg_147 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_147); mph_token_Token* _ret_152 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BANG, _arg_147, ({ mph_lexer_Lexer* _obj_148 = l; mph_gc_push_root(ctx, (void**)&_obj_148); mph_int _ret_149 = _obj_148->line; mph_gc_pop_roots(ctx, 1); _ret_149; }), ({ mph_lexer_Lexer* _obj_150 = l; mph_gc_push_root(ctx, (void**)&_obj_150); mph_int _ret_151 = _obj_150->column; mph_gc_pop_roots(ctx, 1); _ret_151; })); mph_gc_pop_roots(ctx, 1); _ret_152; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_153 = l; mph_gc_push_root(ctx, (void**)&_obj_153); mph_int _ret_154 = _obj_153->ch; mph_gc_pop_roots(ctx, 1); _ret_154; }) == 42)) {
{
	tok = ({ MorphString* _arg_155 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_arg_155); mph_token_Token* _ret_160 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ASTERISK, _arg_155, ({ mph_lexer_Lexer* _obj_156 = l; mph_gc_push_root(ctx, (void**)&_obj_156); mph_int _ret_157 = _obj_156->line; mph_gc_pop_roots(ctx, 1); _ret_157; }), ({ mph_lexer_Lexer* _obj_158 = l; mph_gc_push_root(ctx, (void**)&_obj_158); mph_int _ret_159 = _obj_158->column; mph_gc_pop_roots(ctx, 1); _ret_159; })); mph_gc_pop_roots(ctx, 1); _ret_160; });
}
	} else if ((({ mph_lexer_Lexer* _obj_161 = l; mph_gc_push_root(ctx, (void**)&_obj_161); mph_int _ret_162 = _obj_161->ch; mph_gc_pop_roots(ctx, 1); _ret_162; }) == 47)) {
{
	tok = ({ MorphString* _arg_163 = mph_string_new(ctx, "/"); mph_gc_push_root(ctx, (void**)&_arg_163); mph_token_Token* _ret_168 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_SLASH, _arg_163, ({ mph_lexer_Lexer* _obj_164 = l; mph_gc_push_root(ctx, (void**)&_obj_164); mph_int _ret_165 = _obj_164->line; mph_gc_pop_roots(ctx, 1); _ret_165; }), ({ mph_lexer_Lexer* _obj_166 = l; mph_gc_push_root(ctx, (void**)&_obj_166); mph_int _ret_167 = _obj_166->column; mph_gc_pop_roots(ctx, 1); _ret_167; })); mph_gc_pop_roots(ctx, 1); _ret_168; });
}
	} else if ((({ mph_lexer_Lexer* _obj_169 = l; mph_gc_push_root(ctx, (void**)&_obj_169); mph_int _ret_170 = _obj_169->ch; mph_gc_pop_roots(ctx, 1); _ret_170; }) == 37)) {
{
	tok = ({ MorphString* _arg_171 = mph_string_new(ctx, "%"); mph_gc_push_root(ctx, (void**)&_arg_171); mph_token_Token* _ret_176 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_PERCENT, _arg_171, ({ mph_lexer_Lexer* _obj_172 = l; mph_gc_push_root(ctx, (void**)&_obj_172); mph_int _ret_173 = _obj_172->line; mph_gc_pop_roots(ctx, 1); _ret_173; }), ({ mph_lexer_Lexer* _obj_174 = l; mph_gc_push_root(ctx, (void**)&_obj_174); mph_int _ret_175 = _obj_174->column; mph_gc_pop_roots(ctx, 1); _ret_175; })); mph_gc_pop_roots(ctx, 1); _ret_176; });
}
	} else if ((({ mph_lexer_Lexer* _obj_177 = l; mph_gc_push_root(ctx, (void**)&_obj_177); mph_int _ret_178 = _obj_177->ch; mph_gc_pop_roots(ctx, 1); _ret_178; }) == 60)) {
{
	if ((({ mph_lexer_Lexer* _arg_179 = l; mph_gc_push_root(ctx, (void**)&_arg_179); mph_int _ret_180 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_179); mph_gc_pop_roots(ctx, 1); _ret_180; }) == 61)) {
{
	({ mph_lexer_Lexer* _arg_181 = l; mph_gc_push_root(ctx, (void**)&_arg_181); mph_lexer_lexer_read_char(ctx, NULL, _arg_181); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_182 = mph_string_new(ctx, "<="); mph_gc_push_root(ctx, (void**)&_arg_182); mph_token_Token* _ret_187 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LE, _arg_182, ({ mph_lexer_Lexer* _obj_183 = l; mph_gc_push_root(ctx, (void**)&_obj_183); mph_int _ret_184 = _obj_183->line; mph_gc_pop_roots(ctx, 1); _ret_184; }), ({ mph_lexer_Lexer* _obj_185 = l; mph_gc_push_root(ctx, (void**)&_obj_185); mph_int _ret_186 = _obj_185->column; mph_gc_pop_roots(ctx, 1); _ret_186; })); mph_gc_pop_roots(ctx, 1); _ret_187; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _arg_188 = l; mph_gc_push_root(ctx, (void**)&_arg_188); mph_int _ret_189 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_188); mph_gc_pop_roots(ctx, 1); _ret_189; }) == 60)) {
{
	({ mph_lexer_Lexer* _arg_190 = l; mph_gc_push_root(ctx, (void**)&_arg_190); mph_lexer_lexer_read_char(ctx, NULL, _arg_190); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_191 = mph_string_new(ctx, "<<"); mph_gc_push_root(ctx, (void**)&_arg_191); mph_token_Token* _ret_196 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LSHIFT, _arg_191, ({ mph_lexer_Lexer* _obj_192 = l; mph_gc_push_root(ctx, (void**)&_obj_192); mph_int _ret_193 = _obj_192->line; mph_gc_pop_roots(ctx, 1); _ret_193; }), ({ mph_lexer_Lexer* _obj_194 = l; mph_gc_push_root(ctx, (void**)&_obj_194); mph_int _ret_195 = _obj_194->column; mph_gc_pop_roots(ctx, 1); _ret_195; })); mph_gc_pop_roots(ctx, 1); _ret_196; });
}
	} else {
{
	tok = ({ MorphString* _arg_197 = mph_string_new(ctx, "<"); mph_gc_push_root(ctx, (void**)&_arg_197); mph_token_Token* _ret_202 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LT, _arg_197, ({ mph_lexer_Lexer* _obj_198 = l; mph_gc_push_root(ctx, (void**)&_obj_198); mph_int _ret_199 = _obj_198->line; mph_gc_pop_roots(ctx, 1); _ret_199; }), ({ mph_lexer_Lexer* _obj_200 = l; mph_gc_push_root(ctx, (void**)&_obj_200); mph_int _ret_201 = _obj_200->column; mph_gc_pop_roots(ctx, 1); _ret_201; })); mph_gc_pop_roots(ctx, 1); _ret_202; });
}
	}
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_203 = l; mph_gc_push_root(ctx, (void**)&_obj_203); mph_int _ret_204 = _obj_203->ch; mph_gc_pop_roots(ctx, 1); _ret_204; }) == 62)) {
{
	if ((({ mph_lexer_Lexer* _arg_205 = l; mph_gc_push_root(ctx, (void**)&_arg_205); mph_int _ret_206 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_205); mph_gc_pop_roots(ctx, 1); _ret_206; }) == 61)) {
{
	({ mph_lexer_Lexer* _arg_207 = l; mph_gc_push_root(ctx, (void**)&_arg_207); mph_lexer_lexer_read_char(ctx, NULL, _arg_207); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_208 = mph_string_new(ctx, ">="); mph_gc_push_root(ctx, (void**)&_arg_208); mph_token_Token* _ret_213 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_GE, _arg_208, ({ mph_lexer_Lexer* _obj_209 = l; mph_gc_push_root(ctx, (void**)&_obj_209); mph_int _ret_210 = _obj_209->line; mph_gc_pop_roots(ctx, 1); _ret_210; }), ({ mph_lexer_Lexer* _obj_211 = l; mph_gc_push_root(ctx, (void**)&_obj_211); mph_int _ret_212 = _obj_211->column; mph_gc_pop_roots(ctx, 1); _ret_212; })); mph_gc_pop_roots(ctx, 1); _ret_213; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _arg_214 = l; mph_gc_push_root(ctx, (void**)&_arg_214); mph_int _ret_215 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_214); mph_gc_pop_roots(ctx, 1); _ret_215; }) == 62)) {
{
	({ mph_lexer_Lexer* _arg_216 = l; mph_gc_push_root(ctx, (void**)&_arg_216); mph_lexer_lexer_read_char(ctx, NULL, _arg_216); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_217 = mph_string_new(ctx, ">>"); mph_gc_push_root(ctx, (void**)&_arg_217); mph_token_Token* _ret_222 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RSHIFT, _arg_217, ({ mph_lexer_Lexer* _obj_218 = l; mph_gc_push_root(ctx, (void**)&_obj_218); mph_int _ret_219 = _obj_218->line; mph_gc_pop_roots(ctx, 1); _ret_219; }), ({ mph_lexer_Lexer* _obj_220 = l; mph_gc_push_root(ctx, (void**)&_obj_220); mph_int _ret_221 = _obj_220->column; mph_gc_pop_roots(ctx, 1); _ret_221; })); mph_gc_pop_roots(ctx, 1); _ret_222; });
}
	} else {
{
	tok = ({ MorphString* _arg_223 = mph_string_new(ctx, ">"); mph_gc_push_root(ctx, (void**)&_arg_223); mph_token_Token* _ret_228 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_GT, _arg_223, ({ mph_lexer_Lexer* _obj_224 = l; mph_gc_push_root(ctx, (void**)&_obj_224); mph_int _ret_225 = _obj_224->line; mph_gc_pop_roots(ctx, 1); _ret_225; }), ({ mph_lexer_Lexer* _obj_226 = l; mph_gc_push_root(ctx, (void**)&_obj_226); mph_int _ret_227 = _obj_226->column; mph_gc_pop_roots(ctx, 1); _ret_227; })); mph_gc_pop_roots(ctx, 1); _ret_228; });
}
	}
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_229 = l; mph_gc_push_root(ctx, (void**)&_obj_229); mph_int _ret_230 = _obj_229->ch; mph_gc_pop_roots(ctx, 1); _ret_230; }) == 38)) {
{
	if ((({ mph_lexer_Lexer* _arg_231 = l; mph_gc_push_root(ctx, (void**)&_arg_231); mph_int _ret_232 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_231); mph_gc_pop_roots(ctx, 1); _ret_232; }) == 38)) {
{
	({ mph_lexer_Lexer* _arg_233 = l; mph_gc_push_root(ctx, (void**)&_arg_233); mph_lexer_lexer_read_char(ctx, NULL, _arg_233); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_234 = mph_string_new(ctx, "&&"); mph_gc_push_root(ctx, (void**)&_arg_234); mph_token_Token* _ret_239 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_AND, _arg_234, ({ mph_lexer_Lexer* _obj_235 = l; mph_gc_push_root(ctx, (void**)&_obj_235); mph_int _ret_236 = _obj_235->line; mph_gc_pop_roots(ctx, 1); _ret_236; }), ({ mph_lexer_Lexer* _obj_237 = l; mph_gc_push_root(ctx, (void**)&_obj_237); mph_int _ret_238 = _obj_237->column; mph_gc_pop_roots(ctx, 1); _ret_238; })); mph_gc_pop_roots(ctx, 1); _ret_239; });
}
	} else {
{
	tok = ({ MorphString* _arg_240 = mph_string_new(ctx, "&"); mph_gc_push_root(ctx, (void**)&_arg_240); mph_token_Token* _ret_245 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_AND, _arg_240, ({ mph_lexer_Lexer* _obj_241 = l; mph_gc_push_root(ctx, (void**)&_obj_241); mph_int _ret_242 = _obj_241->line; mph_gc_pop_roots(ctx, 1); _ret_242; }), ({ mph_lexer_Lexer* _obj_243 = l; mph_gc_push_root(ctx, (void**)&_obj_243); mph_int _ret_244 = _obj_243->column; mph_gc_pop_roots(ctx, 1); _ret_244; })); mph_gc_pop_roots(ctx, 1); _ret_245; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_246 = l; mph_gc_push_root(ctx, (void**)&_obj_246); mph_int _ret_247 = _obj_246->ch; mph_gc_pop_roots(ctx, 1); _ret_247; }) == 124)) {
{
	if ((({ mph_lexer_Lexer* _arg_248 = l; mph_gc_push_root(ctx, (void**)&_arg_248); mph_int _ret_249 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_248); mph_gc_pop_roots(ctx, 1); _ret_249; }) == 124)) {
{
	({ mph_lexer_Lexer* _arg_250 = l; mph_gc_push_root(ctx, (void**)&_arg_250); mph_lexer_lexer_read_char(ctx, NULL, _arg_250); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_251 = mph_string_new(ctx, "||"); mph_gc_push_root(ctx, (void**)&_arg_251); mph_token_Token* _ret_256 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_OR, _arg_251, ({ mph_lexer_Lexer* _obj_252 = l; mph_gc_push_root(ctx, (void**)&_obj_252); mph_int _ret_253 = _obj_252->line; mph_gc_pop_roots(ctx, 1); _ret_253; }), ({ mph_lexer_Lexer* _obj_254 = l; mph_gc_push_root(ctx, (void**)&_obj_254); mph_int _ret_255 = _obj_254->column; mph_gc_pop_roots(ctx, 1); _ret_255; })); mph_gc_pop_roots(ctx, 1); _ret_256; });
}
	} else {
{
	tok = ({ MorphString* _arg_257 = mph_string_new(ctx, "|"); mph_gc_push_root(ctx, (void**)&_arg_257); mph_token_Token* _ret_262 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_OR, _arg_257, ({ mph_lexer_Lexer* _obj_258 = l; mph_gc_push_root(ctx, (void**)&_obj_258); mph_int _ret_259 = _obj_258->line; mph_gc_pop_roots(ctx, 1); _ret_259; }), ({ mph_lexer_Lexer* _obj_260 = l; mph_gc_push_root(ctx, (void**)&_obj_260); mph_int _ret_261 = _obj_260->column; mph_gc_pop_roots(ctx, 1); _ret_261; })); mph_gc_pop_roots(ctx, 1); _ret_262; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_263 = l; mph_gc_push_root(ctx, (void**)&_obj_263); mph_int _ret_264 = _obj_263->ch; mph_gc_pop_roots(ctx, 1); _ret_264; }) == 94)) {
{
	tok = ({ MorphString* _arg_265 = mph_string_new(ctx, "^"); mph_gc_push_root(ctx, (void**)&_arg_265); mph_token_Token* _ret_270 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_XOR, _arg_265, ({ mph_lexer_Lexer* _obj_266 = l; mph_gc_push_root(ctx, (void**)&_obj_266); mph_int _ret_267 = _obj_266->line; mph_gc_pop_roots(ctx, 1); _ret_267; }), ({ mph_lexer_Lexer* _obj_268 = l; mph_gc_push_root(ctx, (void**)&_obj_268); mph_int _ret_269 = _obj_268->column; mph_gc_pop_roots(ctx, 1); _ret_269; })); mph_gc_pop_roots(ctx, 1); _ret_270; });
}
	} else if ((({ mph_lexer_Lexer* _obj_271 = l; mph_gc_push_root(ctx, (void**)&_obj_271); mph_int _ret_272 = _obj_271->ch; mph_gc_pop_roots(ctx, 1); _ret_272; }) == 126)) {
{
	tok = ({ MorphString* _arg_273 = mph_string_new(ctx, "~"); mph_gc_push_root(ctx, (void**)&_arg_273); mph_token_Token* _ret_278 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_NOT, _arg_273, ({ mph_lexer_Lexer* _obj_274 = l; mph_gc_push_root(ctx, (void**)&_obj_274); mph_int _ret_275 = _obj_274->line; mph_gc_pop_roots(ctx, 1); _ret_275; }), ({ mph_lexer_Lexer* _obj_276 = l; mph_gc_push_root(ctx, (void**)&_obj_276); mph_int _ret_277 = _obj_276->column; mph_gc_pop_roots(ctx, 1); _ret_277; })); mph_gc_pop_roots(ctx, 1); _ret_278; });
}
	} else if ((({ mph_lexer_Lexer* _obj_279 = l; mph_gc_push_root(ctx, (void**)&_obj_279); mph_int _ret_280 = _obj_279->ch; mph_gc_pop_roots(ctx, 1); _ret_280; }) == 44)) {
{
	tok = ({ MorphString* _arg_281 = mph_string_new(ctx, ","); mph_gc_push_root(ctx, (void**)&_arg_281); mph_token_Token* _ret_286 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_COMMA, _arg_281, ({ mph_lexer_Lexer* _obj_282 = l; mph_gc_push_root(ctx, (void**)&_obj_282); mph_int _ret_283 = _obj_282->line; mph_gc_pop_roots(ctx, 1); _ret_283; }), ({ mph_lexer_Lexer* _obj_284 = l; mph_gc_push_root(ctx, (void**)&_obj_284); mph_int _ret_285 = _obj_284->column; mph_gc_pop_roots(ctx, 1); _ret_285; })); mph_gc_pop_roots(ctx, 1); _ret_286; });
}
	} else if ((({ mph_lexer_Lexer* _obj_287 = l; mph_gc_push_root(ctx, (void**)&_obj_287); mph_int _ret_288 = _obj_287->ch; mph_gc_pop_roots(ctx, 1); _ret_288; }) == 59)) {
{
	tok = ({ MorphString* _arg_289 = mph_string_new(ctx, ";"); mph_gc_push_root(ctx, (void**)&_arg_289); mph_token_Token* _ret_294 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_SEMICOLON, _arg_289, ({ mph_lexer_Lexer* _obj_290 = l; mph_gc_push_root(ctx, (void**)&_obj_290); mph_int _ret_291 = _obj_290->line; mph_gc_pop_roots(ctx, 1); _ret_291; }), ({ mph_lexer_Lexer* _obj_292 = l; mph_gc_push_root(ctx, (void**)&_obj_292); mph_int _ret_293 = _obj_292->column; mph_gc_pop_roots(ctx, 1); _ret_293; })); mph_gc_pop_roots(ctx, 1); _ret_294; });
}
	} else if ((({ mph_lexer_Lexer* _obj_295 = l; mph_gc_push_root(ctx, (void**)&_obj_295); mph_int _ret_296 = _obj_295->ch; mph_gc_pop_roots(ctx, 1); _ret_296; }) == 58)) {
{
	tok = ({ MorphString* _arg_297 = mph_string_new(ctx, ":"); mph_gc_push_root(ctx, (void**)&_arg_297); mph_token_Token* _ret_302 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_COLON, _arg_297, ({ mph_lexer_Lexer* _obj_298 = l; mph_gc_push_root(ctx, (void**)&_obj_298); mph_int _ret_299 = _obj_298->line; mph_gc_pop_roots(ctx, 1); _ret_299; }), ({ mph_lexer_Lexer* _obj_300 = l; mph_gc_push_root(ctx, (void**)&_obj_300); mph_int _ret_301 = _obj_300->column; mph_gc_pop_roots(ctx, 1); _ret_301; })); mph_gc_pop_roots(ctx, 1); _ret_302; });
}
	} else if ((({ mph_lexer_Lexer* _obj_303 = l; mph_gc_push_root(ctx, (void**)&_obj_303); mph_int _ret_304 = _obj_303->ch; mph_gc_pop_roots(ctx, 1); _ret_304; }) == 40)) {
{
	tok = ({ MorphString* _arg_305 = mph_string_new(ctx, "("); mph_gc_push_root(ctx, (void**)&_arg_305); mph_token_Token* _ret_310 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LPAREN, _arg_305, ({ mph_lexer_Lexer* _obj_306 = l; mph_gc_push_root(ctx, (void**)&_obj_306); mph_int _ret_307 = _obj_306->line; mph_gc_pop_roots(ctx, 1); _ret_307; }), ({ mph_lexer_Lexer* _obj_308 = l; mph_gc_push_root(ctx, (void**)&_obj_308); mph_int _ret_309 = _obj_308->column; mph_gc_pop_roots(ctx, 1); _ret_309; })); mph_gc_pop_roots(ctx, 1); _ret_310; });
}
	} else if ((({ mph_lexer_Lexer* _obj_311 = l; mph_gc_push_root(ctx, (void**)&_obj_311); mph_int _ret_312 = _obj_311->ch; mph_gc_pop_roots(ctx, 1); _ret_312; }) == 41)) {
{
	tok = ({ MorphString* _arg_313 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_arg_313); mph_token_Token* _ret_318 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RPAREN, _arg_313, ({ mph_lexer_Lexer* _obj_314 = l; mph_gc_push_root(ctx, (void**)&_obj_314); mph_int _ret_315 = _obj_314->line; mph_gc_pop_roots(ctx, 1); _ret_315; }), ({ mph_lexer_Lexer* _obj_316 = l; mph_gc_push_root(ctx, (void**)&_obj_316); mph_int _ret_317 = _obj_316->column; mph_gc_pop_roots(ctx, 1); _ret_317; })); mph_gc_pop_roots(ctx, 1); _ret_318; });
}
	} else if ((({ mph_lexer_Lexer* _obj_319 = l; mph_gc_push_root(ctx, (void**)&_obj_319); mph_int _ret_320 = _obj_319->ch; mph_gc_pop_roots(ctx, 1); _ret_320; }) == 123)) {
{
	tok = ({ MorphString* _arg_321 = mph_string_new(ctx, "{"); mph_gc_push_root(ctx, (void**)&_arg_321); mph_token_Token* _ret_326 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LBRACE, _arg_321, ({ mph_lexer_Lexer* _obj_322 = l; mph_gc_push_root(ctx, (void**)&_obj_322); mph_int _ret_323 = _obj_322->line; mph_gc_pop_roots(ctx, 1); _ret_323; }), ({ mph_lexer_Lexer* _obj_324 = l; mph_gc_push_root(ctx, (void**)&_obj_324); mph_int _ret_325 = _obj_324->column; mph_gc_pop_roots(ctx, 1); _ret_325; })); mph_gc_pop_roots(ctx, 1); _ret_326; });
}
	} else if ((({ mph_lexer_Lexer* _obj_327 = l; mph_gc_push_root(ctx, (void**)&_obj_327); mph_int _ret_328 = _obj_327->ch; mph_gc_pop_roots(ctx, 1); _ret_328; }) == 125)) {
{
	tok = ({ MorphString* _arg_329 = mph_string_new(ctx, "}"); mph_gc_push_root(ctx, (void**)&_arg_329); mph_token_Token* _ret_334 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RBRACE, _arg_329, ({ mph_lexer_Lexer* _obj_330 = l; mph_gc_push_root(ctx, (void**)&_obj_330); mph_int _ret_331 = _obj_330->line; mph_gc_pop_roots(ctx, 1); _ret_331; }), ({ mph_lexer_Lexer* _obj_332 = l; mph_gc_push_root(ctx, (void**)&_obj_332); mph_int _ret_333 = _obj_332->column; mph_gc_pop_roots(ctx, 1); _ret_333; })); mph_gc_pop_roots(ctx, 1); _ret_334; });
}
	} else if ((({ mph_lexer_Lexer* _obj_335 = l; mph_gc_push_root(ctx, (void**)&_obj_335); mph_int _ret_336 = _obj_335->ch; mph_gc_pop_roots(ctx, 1); _ret_336; }) == 91)) {
{
	tok = ({ MorphString* _arg_337 = mph_string_new(ctx, "["); mph_gc_push_root(ctx, (void**)&_arg_337); mph_token_Token* _ret_342 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LBRACKET, _arg_337, ({ mph_lexer_Lexer* _obj_338 = l; mph_gc_push_root(ctx, (void**)&_obj_338); mph_int _ret_339 = _obj_338->line; mph_gc_pop_roots(ctx, 1); _ret_339; }), ({ mph_lexer_Lexer* _obj_340 = l; mph_gc_push_root(ctx, (void**)&_obj_340); mph_int _ret_341 = _obj_340->column; mph_gc_pop_roots(ctx, 1); _ret_341; })); mph_gc_pop_roots(ctx, 1); _ret_342; });
}
	} else if ((({ mph_lexer_Lexer* _obj_343 = l; mph_gc_push_root(ctx, (void**)&_obj_343); mph_int _ret_344 = _obj_343->ch; mph_gc_pop_roots(ctx, 1); _ret_344; }) == 93)) {
{
	tok = ({ MorphString* _arg_345 = mph_string_new(ctx, "]"); mph_gc_push_root(ctx, (void**)&_arg_345); mph_token_Token* _ret_350 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RBRACKET, _arg_345, ({ mph_lexer_Lexer* _obj_346 = l; mph_gc_push_root(ctx, (void**)&_obj_346); mph_int _ret_347 = _obj_346->line; mph_gc_pop_roots(ctx, 1); _ret_347; }), ({ mph_lexer_Lexer* _obj_348 = l; mph_gc_push_root(ctx, (void**)&_obj_348); mph_int _ret_349 = _obj_348->column; mph_gc_pop_roots(ctx, 1); _ret_349; })); mph_gc_pop_roots(ctx, 1); _ret_350; });
}
	} else if ((({ mph_lexer_Lexer* _obj_351 = l; mph_gc_push_root(ctx, (void**)&_obj_351); mph_int _ret_352 = _obj_351->ch; mph_gc_pop_roots(ctx, 1); _ret_352; }) == 46)) {
{
	tok = ({ MorphString* _arg_353 = mph_string_new(ctx, "."); mph_gc_push_root(ctx, (void**)&_arg_353); mph_token_Token* _ret_358 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_DOT, _arg_353, ({ mph_lexer_Lexer* _obj_354 = l; mph_gc_push_root(ctx, (void**)&_obj_354); mph_int _ret_355 = _obj_354->line; mph_gc_pop_roots(ctx, 1); _ret_355; }), ({ mph_lexer_Lexer* _obj_356 = l; mph_gc_push_root(ctx, (void**)&_obj_356); mph_int _ret_357 = _obj_356->column; mph_gc_pop_roots(ctx, 1); _ret_357; })); mph_gc_pop_roots(ctx, 1); _ret_358; });
}
	} else if ((({ mph_lexer_Lexer* _obj_359 = l; mph_gc_push_root(ctx, (void**)&_obj_359); mph_int _ret_360 = _obj_359->ch; mph_gc_pop_roots(ctx, 1); _ret_360; }) == 34)) {
{
	MorphString* str_literal = ({ mph_lexer_Lexer* _arg_361 = l; mph_gc_push_root(ctx, (void**)&_arg_361); MorphString* _ret_362 = mph_lexer_lexer_read_string(ctx, NULL, _arg_361); mph_gc_pop_roots(ctx, 1); _ret_362; });
	mph_gc_push_root(ctx, (void**)&str_literal);
	tok = ({ MorphString* _arg_363 = str_literal; mph_gc_push_root(ctx, (void**)&_arg_363); mph_token_Token* _ret_368 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_STRING, _arg_363, ({ mph_lexer_Lexer* _obj_364 = l; mph_gc_push_root(ctx, (void**)&_obj_364); mph_int _ret_365 = _obj_364->line; mph_gc_pop_roots(ctx, 1); _ret_365; }), ({ mph_lexer_Lexer* _obj_366 = l; mph_gc_push_root(ctx, (void**)&_obj_366); mph_int _ret_367 = _obj_366->column; mph_gc_pop_roots(ctx, 1); _ret_367; })); mph_gc_pop_roots(ctx, 1); _ret_368; });
	mph_gc_pop_roots(ctx, 1);
}
	} else if ((({ mph_lexer_Lexer* _obj_369 = l; mph_gc_push_root(ctx, (void**)&_obj_369); mph_int _ret_370 = _obj_369->ch; mph_gc_pop_roots(ctx, 1); _ret_370; }) == 0)) {
{
	tok = ({ MorphString* _arg_371 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_371); mph_token_Token* _ret_376 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_EOF, _arg_371, ({ mph_lexer_Lexer* _obj_372 = l; mph_gc_push_root(ctx, (void**)&_obj_372); mph_int _ret_373 = _obj_372->line; mph_gc_pop_roots(ctx, 1); _ret_373; }), ({ mph_lexer_Lexer* _obj_374 = l; mph_gc_push_root(ctx, (void**)&_obj_374); mph_int _ret_375 = _obj_374->column; mph_gc_pop_roots(ctx, 1); _ret_375; })); mph_gc_pop_roots(ctx, 1); _ret_376; });
}
	} else {
{
	if (mph_lexer_is_letter(ctx, NULL, ({ mph_lexer_Lexer* _obj_377 = l; mph_gc_push_root(ctx, (void**)&_obj_377); mph_int _ret_378 = _obj_377->ch; mph_gc_pop_roots(ctx, 1); _ret_378; }))) {
{
	MorphString* literal = ({ mph_lexer_Lexer* _arg_379 = l; mph_gc_push_root(ctx, (void**)&_arg_379); MorphString* _ret_380 = mph_lexer_lexer_read_identifier(ctx, NULL, _arg_379); mph_gc_pop_roots(ctx, 1); _ret_380; });
	mph_gc_push_root(ctx, (void**)&literal);
	mph_int token_type = ({ MorphString* _arg_381 = literal; mph_gc_push_root(ctx, (void**)&_arg_381); mph_int _ret_382 = mph_token_LookupKeyword(ctx, NULL, _arg_381); mph_gc_pop_roots(ctx, 1); _ret_382; });
	tok = ({ MorphString* _arg_383 = literal; mph_gc_push_root(ctx, (void**)&_arg_383); mph_token_Token* _ret_388 = mph_token_MakeToken(ctx, NULL, token_type, _arg_383, ({ mph_lexer_Lexer* _obj_384 = l; mph_gc_push_root(ctx, (void**)&_obj_384); mph_int _ret_385 = _obj_384->line; mph_gc_pop_roots(ctx, 1); _ret_385; }), ({ mph_lexer_Lexer* _obj_386 = l; mph_gc_push_root(ctx, (void**)&_obj_386); mph_int _ret_387 = _obj_386->column; mph_gc_pop_roots(ctx, 1); _ret_387; })); mph_gc_pop_roots(ctx, 1); _ret_388; });
	return tok;
	mph_gc_pop_roots(ctx, 1);
}
	} else {
{
	if (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _obj_389 = l; mph_gc_push_root(ctx, (void**)&_obj_389); mph_int _ret_390 = _obj_389->ch; mph_gc_pop_roots(ctx, 1); _ret_390; }))) {
{
	MorphString* literal = ({ mph_lexer_Lexer* _arg_391 = l; mph_gc_push_root(ctx, (void**)&_arg_391); MorphString* _ret_392 = mph_lexer_lexer_read_number(ctx, NULL, _arg_391); mph_gc_pop_roots(ctx, 1); _ret_392; });
	mph_gc_push_root(ctx, (void**)&literal);
	tok = ({ MorphString* _arg_393 = literal; mph_gc_push_root(ctx, (void**)&_arg_393); mph_token_Token* _ret_398 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_INT, _arg_393, ({ mph_lexer_Lexer* _obj_394 = l; mph_gc_push_root(ctx, (void**)&_obj_394); mph_int _ret_395 = _obj_394->line; mph_gc_pop_roots(ctx, 1); _ret_395; }), ({ mph_lexer_Lexer* _obj_396 = l; mph_gc_push_root(ctx, (void**)&_obj_396); mph_int _ret_397 = _obj_396->column; mph_gc_pop_roots(ctx, 1); _ret_397; })); mph_gc_pop_roots(ctx, 1); _ret_398; });
	return tok;
	mph_gc_pop_roots(ctx, 1);
}
	} else {
{
	tok = ({ MorphString* _arg_399 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_399); mph_token_Token* _ret_404 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ILLEGAL, _arg_399, ({ mph_lexer_Lexer* _obj_400 = l; mph_gc_push_root(ctx, (void**)&_obj_400); mph_int _ret_401 = _obj_400->line; mph_gc_pop_roots(ctx, 1); _ret_401; }), ({ mph_lexer_Lexer* _obj_402 = l; mph_gc_push_root(ctx, (void**)&_obj_402); mph_int _ret_403 = _obj_402->column; mph_gc_pop_roots(ctx, 1); _ret_403; })); mph_gc_pop_roots(ctx, 1); _ret_404; });
}
	}
}
	}
}
	}
	({ mph_lexer_Lexer* _arg_405 = l; mph_gc_push_root(ctx, (void**)&_arg_405); mph_lexer_lexer_read_char(ctx, NULL, _arg_405); mph_gc_pop_roots(ctx, 1); });
	return tok;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_parser_Parser* mph_parser_NewParser(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_parser_Parser* p = ({ mph_parser_Parser* _t = (mph_parser_Parser*)mph_alloc(ctx, sizeof(mph_parser_Parser), &mph_ti_mph_parser_Parser); mph_gc_push_root(ctx, (void**)&_t); _t->lexer = l; _t->errors_count = 0; _t->current_token = ({ MorphString* _arg_406 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_arg_406); mph_token_Token* _ret_407 = mph_token_MakeToken(ctx, NULL, 0, _arg_406, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_407; }); _t->peek_token = ({ MorphString* _arg_408 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_arg_408); mph_token_Token* _ret_409 = mph_token_MakeToken(ctx, NULL, 0, _arg_408, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_409; }); mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_push_root(ctx, (void**)&p);
	({ mph_parser_Parser* _arg_410 = p; mph_gc_push_root(ctx, (void**)&_arg_410); mph_parser_ParserNextToken(ctx, NULL, _arg_410); mph_gc_pop_roots(ctx, 1); });
	({ mph_parser_Parser* _arg_411 = p; mph_gc_push_root(ctx, (void**)&_arg_411); mph_parser_ParserNextToken(ctx, NULL, _arg_411); mph_gc_pop_roots(ctx, 1); });
	return p;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

void mph_parser_ParserNextToken(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	({ mph_parser_Parser* _obj_414 = p; mph_gc_push_root(ctx, (void**)&_obj_414); mph_token_Token* _val_415 = ({ mph_parser_Parser* _obj_412 = p; mph_gc_push_root(ctx, (void**)&_obj_412); mph_token_Token* _ret_413 = _obj_412->peek_token; mph_gc_pop_roots(ctx, 1); _ret_413; }); mph_gc_push_root(ctx, (void**)&_val_415); _obj_414->current_token = _val_415; mph_gc_pop_roots(ctx, 2); });
	({ mph_parser_Parser* _obj_420 = p; mph_gc_push_root(ctx, (void**)&_obj_420); mph_token_Token* _val_421 = ({ mph_lexer_Lexer* _arg_418 = ({ mph_parser_Parser* _obj_416 = p; mph_gc_push_root(ctx, (void**)&_obj_416); mph_lexer_Lexer* _ret_417 = _obj_416->lexer; mph_gc_pop_roots(ctx, 1); _ret_417; }); mph_gc_push_root(ctx, (void**)&_arg_418); mph_token_Token* _ret_419 = mph_lexer_LexerNextToken(ctx, NULL, _arg_418); mph_gc_pop_roots(ctx, 1); _ret_419; }); mph_gc_push_root(ctx, (void**)&_val_421); _obj_420->peek_token = _val_421; mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_parser_ParserCurrentTokenIs(MorphContext* ctx, void* _env_void, mph_parser_Parser* p, mph_int token_type) {
	mph_gc_push_root(ctx, (void**)&p);
	return (({ mph_token_Token* _obj_424 = ({ mph_parser_Parser* _obj_422 = p; mph_gc_push_root(ctx, (void**)&_obj_422); mph_token_Token* _ret_423 = _obj_422->current_token; mph_gc_pop_roots(ctx, 1); _ret_423; }); mph_gc_push_root(ctx, (void**)&_obj_424); mph_int _ret_425 = _obj_424->token_type; mph_gc_pop_roots(ctx, 1); _ret_425; }) == token_type);
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_parser_ParserPeekTokenIs(MorphContext* ctx, void* _env_void, mph_parser_Parser* p, mph_int token_type) {
	mph_gc_push_root(ctx, (void**)&p);
	return (({ mph_token_Token* _obj_428 = ({ mph_parser_Parser* _obj_426 = p; mph_gc_push_root(ctx, (void**)&_obj_426); mph_token_Token* _ret_427 = _obj_426->peek_token; mph_gc_pop_roots(ctx, 1); _ret_427; }); mph_gc_push_root(ctx, (void**)&_obj_428); mph_int _ret_429 = _obj_428->token_type; mph_gc_pop_roots(ctx, 1); _ret_429; }) == token_type);
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_parser_ParserExpectPeek(MorphContext* ctx, void* _env_void, mph_parser_Parser* p, mph_int token_type) {
	mph_gc_push_root(ctx, (void**)&p);
	if ((({ mph_parser_Parser* _arg_430 = p; mph_gc_push_root(ctx, (void**)&_arg_430); mph_bool _ret_431 = mph_parser_ParserPeekTokenIs(ctx, NULL, _arg_430, token_type); mph_gc_pop_roots(ctx, 1); _ret_431; }) == 1)) {
{
	({ mph_parser_Parser* _arg_432 = p; mph_gc_push_root(ctx, (void**)&_arg_432); mph_parser_ParserNextToken(ctx, NULL, _arg_432); mph_gc_pop_roots(ctx, 1); });
	return 1;
}
	} else {
{
	({ mph_parser_Parser* _obj_435 = p; mph_gc_push_root(ctx, (void**)&_obj_435); _obj_435->errors_count = (({ mph_parser_Parser* _obj_433 = p; mph_gc_push_root(ctx, (void**)&_obj_433); mph_int _ret_434 = _obj_433->errors_count; mph_gc_pop_roots(ctx, 1); _ret_434; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return 0;
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_parser_GetTokenPrecedence(MorphContext* ctx, void* _env_void, mph_int token_type) {
	if ((token_type == mph_token_TOKEN_EQ)) {
{
	return mph_parser_PRECEDENCE_EQUALS;
}
	}
	if ((token_type == mph_token_TOKEN_NOT_EQ)) {
{
	return mph_parser_PRECEDENCE_EQUALS;
}
	}
	if ((token_type == mph_token_TOKEN_LT)) {
{
	return mph_parser_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_GT)) {
{
	return mph_parser_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_LE)) {
{
	return mph_parser_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_GE)) {
{
	return mph_parser_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_PLUS)) {
{
	return mph_parser_PRECEDENCE_SUM;
}
	}
	if ((token_type == mph_token_TOKEN_MINUS)) {
{
	return mph_parser_PRECEDENCE_SUM;
}
	}
	if ((token_type == mph_token_TOKEN_SLASH)) {
{
	return mph_parser_PRECEDENCE_PRODUCT;
}
	}
	if ((token_type == mph_token_TOKEN_ASTERISK)) {
{
	return mph_parser_PRECEDENCE_PRODUCT;
}
	}
	if ((token_type == mph_token_TOKEN_PERCENT)) {
{
	return mph_parser_PRECEDENCE_PRODUCT;
}
	}
	if ((token_type == mph_token_TOKEN_LPAREN)) {
{
	return mph_parser_PRECEDENCE_CALL;
}
	}
	return mph_parser_PRECEDENCE_LOWEST;
}

mph_int mph_parser_ParserPeekPrecedence(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return mph_parser_GetTokenPrecedence(ctx, NULL, ({ mph_token_Token* _obj_438 = ({ mph_parser_Parser* _obj_436 = p; mph_gc_push_root(ctx, (void**)&_obj_436); mph_token_Token* _ret_437 = _obj_436->peek_token; mph_gc_pop_roots(ctx, 1); _ret_437; }); mph_gc_push_root(ctx, (void**)&_obj_438); mph_int _ret_439 = _obj_438->token_type; mph_gc_pop_roots(ctx, 1); _ret_439; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_parser_ParserCurrentPrecedence(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return mph_parser_GetTokenPrecedence(ctx, NULL, ({ mph_token_Token* _obj_442 = ({ mph_parser_Parser* _obj_440 = p; mph_gc_push_root(ctx, (void**)&_obj_440); mph_token_Token* _ret_441 = _obj_440->current_token; mph_gc_pop_roots(ctx, 1); _ret_441; }); mph_gc_push_root(ctx, (void**)&_obj_442); mph_int _ret_443 = _obj_442->token_type; mph_gc_pop_roots(ctx, 1); _ret_443; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Identifier* mph_parser_ParserParseIdentifier(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return ({ MorphString* _arg_448 = ({ mph_token_Token* _obj_446 = ({ mph_parser_Parser* _obj_444 = p; mph_gc_push_root(ctx, (void**)&_obj_444); mph_token_Token* _ret_445 = _obj_444->current_token; mph_gc_pop_roots(ctx, 1); _ret_445; }); mph_gc_push_root(ctx, (void**)&_obj_446); MorphString* _ret_447 = _obj_446->literal; mph_gc_pop_roots(ctx, 1); _ret_447; }); mph_gc_push_root(ctx, (void**)&_arg_448); mph_ast_Identifier* _ret_457 = mph_ast_MakeIdentifier(ctx, NULL, _arg_448, ({ mph_token_Token* _obj_451 = ({ mph_parser_Parser* _obj_449 = p; mph_gc_push_root(ctx, (void**)&_obj_449); mph_token_Token* _ret_450 = _obj_449->current_token; mph_gc_pop_roots(ctx, 1); _ret_450; }); mph_gc_push_root(ctx, (void**)&_obj_451); mph_int _ret_452 = _obj_451->line; mph_gc_pop_roots(ctx, 1); _ret_452; }), ({ mph_token_Token* _obj_455 = ({ mph_parser_Parser* _obj_453 = p; mph_gc_push_root(ctx, (void**)&_obj_453); mph_token_Token* _ret_454 = _obj_453->current_token; mph_gc_pop_roots(ctx, 1); _ret_454; }); mph_gc_push_root(ctx, (void**)&_obj_455); mph_int _ret_456 = _obj_455->column; mph_gc_pop_roots(ctx, 1); _ret_456; })); mph_gc_pop_roots(ctx, 1); _ret_457; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_IntegerLiteral* mph_parser_ParserParseIntegerLiteral(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_int value = ({ MorphString* _arg_462 = ({ mph_token_Token* _obj_460 = ({ mph_parser_Parser* _obj_458 = p; mph_gc_push_root(ctx, (void**)&_obj_458); mph_token_Token* _ret_459 = _obj_458->current_token; mph_gc_pop_roots(ctx, 1); _ret_459; }); mph_gc_push_root(ctx, (void**)&_obj_460); MorphString* _ret_461 = _obj_460->literal; mph_gc_pop_roots(ctx, 1); _ret_461; }); mph_gc_push_root(ctx, (void**)&_arg_462); mph_int _ret_463 = mph_parser_StringToInt(ctx, NULL, _arg_462); mph_gc_pop_roots(ctx, 1); _ret_463; });
	return ({ MorphString* _arg_468 = ({ mph_token_Token* _obj_466 = ({ mph_parser_Parser* _obj_464 = p; mph_gc_push_root(ctx, (void**)&_obj_464); mph_token_Token* _ret_465 = _obj_464->current_token; mph_gc_pop_roots(ctx, 1); _ret_465; }); mph_gc_push_root(ctx, (void**)&_obj_466); MorphString* _ret_467 = _obj_466->literal; mph_gc_pop_roots(ctx, 1); _ret_467; }); mph_gc_push_root(ctx, (void**)&_arg_468); mph_ast_IntegerLiteral* _ret_477 = mph_ast_MakeIntegerLiteral(ctx, NULL, value, _arg_468, ({ mph_token_Token* _obj_471 = ({ mph_parser_Parser* _obj_469 = p; mph_gc_push_root(ctx, (void**)&_obj_469); mph_token_Token* _ret_470 = _obj_469->current_token; mph_gc_pop_roots(ctx, 1); _ret_470; }); mph_gc_push_root(ctx, (void**)&_obj_471); mph_int _ret_472 = _obj_471->line; mph_gc_pop_roots(ctx, 1); _ret_472; }), ({ mph_token_Token* _obj_475 = ({ mph_parser_Parser* _obj_473 = p; mph_gc_push_root(ctx, (void**)&_obj_473); mph_token_Token* _ret_474 = _obj_473->current_token; mph_gc_pop_roots(ctx, 1); _ret_474; }); mph_gc_push_root(ctx, (void**)&_obj_475); mph_int _ret_476 = _obj_475->column; mph_gc_pop_roots(ctx, 1); _ret_476; })); mph_gc_pop_roots(ctx, 1); _ret_477; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StringLiteral* mph_parser_ParserParseStringLiteral(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return ({ MorphString* _arg_482 = ({ mph_token_Token* _obj_480 = ({ mph_parser_Parser* _obj_478 = p; mph_gc_push_root(ctx, (void**)&_obj_478); mph_token_Token* _ret_479 = _obj_478->current_token; mph_gc_pop_roots(ctx, 1); _ret_479; }); mph_gc_push_root(ctx, (void**)&_obj_480); MorphString* _ret_481 = _obj_480->literal; mph_gc_pop_roots(ctx, 1); _ret_481; }); mph_gc_push_root(ctx, (void**)&_arg_482); mph_ast_StringLiteral* _ret_491 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_482, ({ mph_token_Token* _obj_485 = ({ mph_parser_Parser* _obj_483 = p; mph_gc_push_root(ctx, (void**)&_obj_483); mph_token_Token* _ret_484 = _obj_483->current_token; mph_gc_pop_roots(ctx, 1); _ret_484; }); mph_gc_push_root(ctx, (void**)&_obj_485); mph_int _ret_486 = _obj_485->line; mph_gc_pop_roots(ctx, 1); _ret_486; }), ({ mph_token_Token* _obj_489 = ({ mph_parser_Parser* _obj_487 = p; mph_gc_push_root(ctx, (void**)&_obj_487); mph_token_Token* _ret_488 = _obj_487->current_token; mph_gc_pop_roots(ctx, 1); _ret_488; }); mph_gc_push_root(ctx, (void**)&_obj_489); mph_int _ret_490 = _obj_489->column; mph_gc_pop_roots(ctx, 1); _ret_490; })); mph_gc_pop_roots(ctx, 1); _ret_491; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BooleanLiteral* mph_parser_ParserParseBooleanLiteral(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_bool value = ({ mph_parser_Parser* _arg_492 = p; mph_gc_push_root(ctx, (void**)&_arg_492); mph_bool _ret_493 = mph_parser_ParserCurrentTokenIs(ctx, NULL, _arg_492, mph_token_TOKEN_BENAR); mph_gc_pop_roots(ctx, 1); _ret_493; });
	return ({ MorphString* _arg_498 = ({ mph_token_Token* _obj_496 = ({ mph_parser_Parser* _obj_494 = p; mph_gc_push_root(ctx, (void**)&_obj_494); mph_token_Token* _ret_495 = _obj_494->current_token; mph_gc_pop_roots(ctx, 1); _ret_495; }); mph_gc_push_root(ctx, (void**)&_obj_496); MorphString* _ret_497 = _obj_496->literal; mph_gc_pop_roots(ctx, 1); _ret_497; }); mph_gc_push_root(ctx, (void**)&_arg_498); mph_ast_BooleanLiteral* _ret_507 = mph_ast_MakeBooleanLiteral(ctx, NULL, value, _arg_498, ({ mph_token_Token* _obj_501 = ({ mph_parser_Parser* _obj_499 = p; mph_gc_push_root(ctx, (void**)&_obj_499); mph_token_Token* _ret_500 = _obj_499->current_token; mph_gc_pop_roots(ctx, 1); _ret_500; }); mph_gc_push_root(ctx, (void**)&_obj_501); mph_int _ret_502 = _obj_501->line; mph_gc_pop_roots(ctx, 1); _ret_502; }), ({ mph_token_Token* _obj_505 = ({ mph_parser_Parser* _obj_503 = p; mph_gc_push_root(ctx, (void**)&_obj_503); mph_token_Token* _ret_504 = _obj_503->current_token; mph_gc_pop_roots(ctx, 1); _ret_504; }); mph_gc_push_root(ctx, (void**)&_obj_505); mph_int _ret_506 = _obj_505->column; mph_gc_pop_roots(ctx, 1); _ret_506; })); mph_gc_pop_roots(ctx, 1); _ret_507; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_PrefixExpression* mph_parser_ParserParsePrefixExpression(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_ast_PrefixExpression* expr = ({ MorphString* _arg_512 = ({ mph_token_Token* _obj_510 = ({ mph_parser_Parser* _obj_508 = p; mph_gc_push_root(ctx, (void**)&_obj_508); mph_token_Token* _ret_509 = _obj_508->current_token; mph_gc_pop_roots(ctx, 1); _ret_509; }); mph_gc_push_root(ctx, (void**)&_obj_510); MorphString* _ret_511 = _obj_510->literal; mph_gc_pop_roots(ctx, 1); _ret_511; }); mph_gc_push_root(ctx, (void**)&_arg_512); mph_ast_PrefixExpression* _ret_521 = mph_ast_MakePrefixExpression(ctx, NULL, _arg_512, ({ mph_token_Token* _obj_515 = ({ mph_parser_Parser* _obj_513 = p; mph_gc_push_root(ctx, (void**)&_obj_513); mph_token_Token* _ret_514 = _obj_513->current_token; mph_gc_pop_roots(ctx, 1); _ret_514; }); mph_gc_push_root(ctx, (void**)&_obj_515); mph_int _ret_516 = _obj_515->line; mph_gc_pop_roots(ctx, 1); _ret_516; }), ({ mph_token_Token* _obj_519 = ({ mph_parser_Parser* _obj_517 = p; mph_gc_push_root(ctx, (void**)&_obj_517); mph_token_Token* _ret_518 = _obj_517->current_token; mph_gc_pop_roots(ctx, 1); _ret_518; }); mph_gc_push_root(ctx, (void**)&_obj_519); mph_int _ret_520 = _obj_519->column; mph_gc_pop_roots(ctx, 1); _ret_520; })); mph_gc_pop_roots(ctx, 1); _ret_521; });
	mph_gc_push_root(ctx, (void**)&expr);
	({ mph_parser_Parser* _arg_522 = p; mph_gc_push_root(ctx, (void**)&_arg_522); mph_parser_ParserNextToken(ctx, NULL, _arg_522); mph_gc_pop_roots(ctx, 1); });
	return expr;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_VarStatement* mph_parser_ParserParseVarStatement(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_int line = ({ mph_token_Token* _obj_525 = ({ mph_parser_Parser* _obj_523 = p; mph_gc_push_root(ctx, (void**)&_obj_523); mph_token_Token* _ret_524 = _obj_523->current_token; mph_gc_pop_roots(ctx, 1); _ret_524; }); mph_gc_push_root(ctx, (void**)&_obj_525); mph_int _ret_526 = _obj_525->line; mph_gc_pop_roots(ctx, 1); _ret_526; });
	mph_int column = ({ mph_token_Token* _obj_529 = ({ mph_parser_Parser* _obj_527 = p; mph_gc_push_root(ctx, (void**)&_obj_527); mph_token_Token* _ret_528 = _obj_527->current_token; mph_gc_pop_roots(ctx, 1); _ret_528; }); mph_gc_push_root(ctx, (void**)&_obj_529); mph_int _ret_530 = _obj_529->column; mph_gc_pop_roots(ctx, 1); _ret_530; });
	if ((({ mph_parser_Parser* _arg_531 = p; mph_gc_push_root(ctx, (void**)&_arg_531); mph_bool _ret_532 = mph_parser_ParserExpectPeek(ctx, NULL, _arg_531, mph_token_TOKEN_IDENT); mph_gc_pop_roots(ctx, 1); _ret_532; }) == 0)) {
{
	return ({ MorphString* _arg_533 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_533); MorphString* _arg_534 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_534); mph_ast_VarStatement* _ret_535 = mph_ast_MakeVarStatement(ctx, NULL, _arg_533, _arg_534, line, column); mph_gc_pop_roots(ctx, 2); _ret_535; });
}
	}
	MorphString* name = ({ mph_token_Token* _obj_538 = ({ mph_parser_Parser* _obj_536 = p; mph_gc_push_root(ctx, (void**)&_obj_536); mph_token_Token* _ret_537 = _obj_536->current_token; mph_gc_pop_roots(ctx, 1); _ret_537; }); mph_gc_push_root(ctx, (void**)&_obj_538); MorphString* _ret_539 = _obj_538->literal; mph_gc_pop_roots(ctx, 1); _ret_539; });
	mph_gc_push_root(ctx, (void**)&name);
	MorphString* type_str = mph_string_new(ctx, "-");
	mph_gc_push_root(ctx, (void**)&type_str);
	if ((({ mph_parser_Parser* _arg_540 = p; mph_gc_push_root(ctx, (void**)&_arg_540); mph_bool _ret_541 = mph_parser_ParserPeekTokenIs(ctx, NULL, _arg_540, mph_token_TOKEN_COLON); mph_gc_pop_roots(ctx, 1); _ret_541; }) == 1)) {
{
	({ mph_parser_Parser* _arg_542 = p; mph_gc_push_root(ctx, (void**)&_arg_542); mph_parser_ParserNextToken(ctx, NULL, _arg_542); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_parser_Parser* _arg_543 = p; mph_gc_push_root(ctx, (void**)&_arg_543); mph_bool _ret_544 = mph_parser_ParserExpectPeek(ctx, NULL, _arg_543, mph_token_TOKEN_IDENT); mph_gc_pop_roots(ctx, 1); _ret_544; }) == 1)) {
{
	type_str = ({ mph_token_Token* _obj_547 = ({ mph_parser_Parser* _obj_545 = p; mph_gc_push_root(ctx, (void**)&_obj_545); mph_token_Token* _ret_546 = _obj_545->current_token; mph_gc_pop_roots(ctx, 1); _ret_546; }); mph_gc_push_root(ctx, (void**)&_obj_547); MorphString* _ret_548 = _obj_547->literal; mph_gc_pop_roots(ctx, 1); _ret_548; });
}
	}
}
	}
	mph_ast_VarStatement* stmt = ({ MorphString* _arg_549 = name; mph_gc_push_root(ctx, (void**)&_arg_549); MorphString* _arg_550 = type_str; mph_gc_push_root(ctx, (void**)&_arg_550); mph_ast_VarStatement* _ret_551 = mph_ast_MakeVarStatement(ctx, NULL, _arg_549, _arg_550, line, column); mph_gc_pop_roots(ctx, 2); _ret_551; });
	mph_gc_push_root(ctx, (void**)&stmt);
	if ((({ mph_parser_Parser* _arg_552 = p; mph_gc_push_root(ctx, (void**)&_arg_552); mph_bool _ret_553 = mph_parser_ParserPeekTokenIs(ctx, NULL, _arg_552, mph_token_TOKEN_ASSIGN); mph_gc_pop_roots(ctx, 1); _ret_553; }) == 1)) {
{
	({ mph_parser_Parser* _arg_554 = p; mph_gc_push_root(ctx, (void**)&_arg_554); mph_parser_ParserNextToken(ctx, NULL, _arg_554); mph_gc_pop_roots(ctx, 1); });
	({ mph_parser_Parser* _arg_555 = p; mph_gc_push_root(ctx, (void**)&_arg_555); mph_parser_ParserNextToken(ctx, NULL, _arg_555); mph_gc_pop_roots(ctx, 1); });
	({ mph_ast_VarStatement* _obj_556 = stmt; mph_gc_push_root(ctx, (void**)&_obj_556); _obj_556->has_value = 1; mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_bool should_continue = 1;
	while ((should_continue == 1)) {
{
	if ((({ mph_parser_Parser* _arg_557 = p; mph_gc_push_root(ctx, (void**)&_arg_557); mph_bool _ret_558 = mph_parser_ParserCurrentTokenIs(ctx, NULL, _arg_557, mph_token_TOKEN_SEMICOLON); mph_gc_pop_roots(ctx, 1); _ret_558; }) == 1)) {
{
	should_continue = 0;
}
	} else {
{
	if ((({ mph_parser_Parser* _arg_559 = p; mph_gc_push_root(ctx, (void**)&_arg_559); mph_bool _ret_560 = mph_parser_ParserCurrentTokenIs(ctx, NULL, _arg_559, mph_token_TOKEN_EOF); mph_gc_pop_roots(ctx, 1); _ret_560; }) == 1)) {
{
	should_continue = 0;
}
	} else {
{
	({ mph_parser_Parser* _arg_561 = p; mph_gc_push_root(ctx, (void**)&_arg_561); mph_parser_ParserNextToken(ctx, NULL, _arg_561); mph_gc_pop_roots(ctx, 1); });
}
	}
}
	}
}
	}
	return stmt;
	mph_gc_pop_roots(ctx, 3);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Program* mph_parser_ParserParseProgram(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_ast_Program* program = mph_ast_MakeProgram(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&program);
	while ((({ mph_parser_Parser* _arg_562 = p; mph_gc_push_root(ctx, (void**)&_arg_562); mph_bool _ret_563 = mph_parser_ParserCurrentTokenIs(ctx, NULL, _arg_562, mph_token_TOKEN_EOF); mph_gc_pop_roots(ctx, 1); _ret_563; }) == 0)) {
{
	if ((({ mph_parser_Parser* _arg_564 = p; mph_gc_push_root(ctx, (void**)&_arg_564); mph_bool _ret_565 = mph_parser_ParserCurrentTokenIs(ctx, NULL, _arg_564, mph_token_TOKEN_VAR); mph_gc_pop_roots(ctx, 1); _ret_565; }) == 1)) {
{
	mph_ast_VarStatement* stmt = ({ mph_parser_Parser* _arg_566 = p; mph_gc_push_root(ctx, (void**)&_arg_566); mph_ast_VarStatement* _ret_567 = mph_parser_ParserParseVarStatement(ctx, NULL, _arg_566); mph_gc_pop_roots(ctx, 1); _ret_567; });
	mph_gc_push_root(ctx, (void**)&stmt);
	({ mph_ast_Program* _obj_570 = program; mph_gc_push_root(ctx, (void**)&_obj_570); _obj_570->statements_count = (({ mph_ast_Program* _obj_568 = program; mph_gc_push_root(ctx, (void**)&_obj_568); mph_int _ret_569 = _obj_568->statements_count; mph_gc_pop_roots(ctx, 1); _ret_569; }) + 1); mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Parsed VarStatement: "));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_571 = stmt; mph_gc_push_root(ctx, (void**)&_obj_571); MorphString* _ret_572 = _obj_571->name; mph_gc_pop_roots(ctx, 1); _ret_572; }));
	if ((({ mph_ast_VarStatement* _obj_573 = stmt; mph_gc_push_root(ctx, (void**)&_obj_573); MorphString* _ret_574 = _obj_573->value_type; mph_gc_pop_roots(ctx, 1); _ret_574; }) != mph_string_new(ctx, "-"))) {
{
	mph_native_print(ctx, mph_string_new(ctx, " : "));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_575 = stmt; mph_gc_push_root(ctx, (void**)&_obj_575); MorphString* _ret_576 = _obj_575->value_type; mph_gc_pop_roots(ctx, 1); _ret_576; }));
}
	}
	if ((({ mph_ast_VarStatement* _obj_577 = stmt; mph_gc_push_root(ctx, (void**)&_obj_577); mph_bool _ret_578 = _obj_577->has_value; mph_gc_pop_roots(ctx, 1); _ret_578; }) == 1)) {
{
	mph_native_print(ctx, mph_string_new(ctx, " = <expression>"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}
	}
	({ mph_parser_Parser* _arg_579 = p; mph_gc_push_root(ctx, (void**)&_arg_579); mph_parser_ParserNextToken(ctx, NULL, _arg_579); mph_gc_pop_roots(ctx, 1); });
}
	}
	return program;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_parser_StringToInt(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "0"))) {
{
	return 0;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "1"))) {
{
	return 1;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "2"))) {
{
	return 2;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "3"))) {
{
	return 3;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "4"))) {
{
	return 4;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "5"))) {
{
	return 5;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "6"))) {
{
	return 6;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "7"))) {
{
	return 7;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "8"))) {
{
	return 8;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "9"))) {
{
	return 9;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "10"))) {
{
	return 10;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "42"))) {
{
	return 42;
}
	}
	if (mph_string_eq(ctx, s, mph_string_new(ctx, "100"))) {
{
	return 100;
}
	}
	return 0;
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_parser_ParserHasErrors(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return (({ mph_parser_Parser* _obj_580 = p; mph_gc_push_root(ctx, (void**)&_obj_580); mph_int _ret_581 = _obj_580->errors_count; mph_gc_pop_roots(ctx, 1); _ret_581; }) > 0);
	mph_gc_pop_roots(ctx, 1);
}

void mph_parser_ParserPrintErrors(MorphContext* ctx, void* _env_void, mph_parser_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	if ((({ mph_parser_Parser* _obj_582 = p; mph_gc_push_root(ctx, (void**)&_obj_582); mph_int _ret_583 = _obj_582->errors_count; mph_gc_pop_roots(ctx, 1); _ret_583; }) > 0)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "Parser has "));
	mph_native_print_int(ctx, ({ mph_parser_Parser* _obj_584 = p; mph_gc_push_root(ctx, (void**)&_obj_584); mph_int _ret_585 = _obj_584->errors_count; mph_gc_pop_roots(ctx, 1); _ret_585; }));
	mph_native_print(ctx, mph_string_new(ctx, " error(s)\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "No parser errors\n"));
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_checker_Checker* mph_checker_new_checker(MorphContext* ctx, void* _env_void) {
	return ({ mph_checker_Checker* _t = (mph_checker_Checker*)mph_alloc(ctx, sizeof(mph_checker_Checker), &mph_ti_mph_checker_Checker); mph_gc_push_root(ctx, (void**)&_t); _t->errors_count = 0; _t->current_scope_level = 0; mph_gc_pop_roots(ctx, 1); _t; });
}

void mph_checker_checker_add_error(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, MorphString* message) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&message);
	({ mph_checker_Checker* _obj_588 = c; mph_gc_push_root(ctx, (void**)&_obj_588); _obj_588->errors_count = (({ mph_checker_Checker* _obj_586 = c; mph_gc_push_root(ctx, (void**)&_obj_586); mph_int _ret_587 = _obj_586->errors_count; mph_gc_pop_roots(ctx, 1); _ret_587; }) + 1); mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Type Error: "));
	mph_native_print(ctx, message);
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_checker_checker_has_errors(MorphContext* ctx, void* _env_void, mph_checker_Checker* c) {
	mph_gc_push_root(ctx, (void**)&c);
	return (({ mph_checker_Checker* _obj_589 = c; mph_gc_push_root(ctx, (void**)&_obj_589); mph_int _ret_590 = _obj_589->errors_count; mph_gc_pop_roots(ctx, 1); _ret_590; }) > 0);
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_checker_check_integer_literal(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_types_IntType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_check_string_literal(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_types_StringType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_check_boolean_literal(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_types_BoolType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_check_identifier(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&ident);
	return mph_types_IntType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_check_prefix_expression(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_PrefixExpression* expr) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&expr);
	mph_types_Type* right_type = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&right_type);
	mph_types_TypeResult* result = ({ mph_types_Type* _arg_591 = right_type; mph_gc_push_root(ctx, (void**)&_arg_591); MorphString* _arg_594 = ({ mph_ast_PrefixExpression* _obj_592 = expr; mph_gc_push_root(ctx, (void**)&_obj_592); MorphString* _ret_593 = _obj_592->operator; mph_gc_pop_roots(ctx, 1); _ret_593; }); mph_gc_push_root(ctx, (void**)&_arg_594); mph_types_TypeResult* _ret_595 = mph_types_TypePrefixOp(ctx, NULL, _arg_591, _arg_594); mph_gc_pop_roots(ctx, 2); _ret_595; });
	mph_gc_push_root(ctx, (void**)&result);
	if (({ mph_types_TypeResult* _obj_596 = result; mph_gc_push_root(ctx, (void**)&_obj_596); mph_bool _ret_597 = _obj_596->has_error; mph_gc_pop_roots(ctx, 1); _ret_597; })) {
{
	({ mph_checker_Checker* _arg_598 = c; mph_gc_push_root(ctx, (void**)&_arg_598); MorphString* _arg_601 = ({ mph_types_TypeResult* _obj_599 = result; mph_gc_push_root(ctx, (void**)&_obj_599); MorphString* _ret_600 = _obj_599->error_msg; mph_gc_pop_roots(ctx, 1); _ret_600; }); mph_gc_push_root(ctx, (void**)&_arg_601); mph_checker_checker_add_error(ctx, NULL, _arg_598, _arg_601); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
	return ({ mph_types_TypeResult* _obj_602 = result; mph_gc_push_root(ctx, (void**)&_obj_602); mph_types_Type* _ret_603 = _obj_602->result; mph_gc_pop_roots(ctx, 1); _ret_603; });
	mph_gc_pop_roots(ctx, 2);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_check_infix_expression(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_InfixExpression* expr) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&expr);
	mph_types_Type* left_type = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&left_type);
	mph_types_Type* right_type = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&right_type);
	mph_types_TypeResult* result = ({ mph_types_Type* _arg_604 = left_type; mph_gc_push_root(ctx, (void**)&_arg_604); MorphString* _arg_607 = ({ mph_ast_InfixExpression* _obj_605 = expr; mph_gc_push_root(ctx, (void**)&_obj_605); MorphString* _ret_606 = _obj_605->operator; mph_gc_pop_roots(ctx, 1); _ret_606; }); mph_gc_push_root(ctx, (void**)&_arg_607); mph_types_Type* _arg_608 = right_type; mph_gc_push_root(ctx, (void**)&_arg_608); mph_types_TypeResult* _ret_609 = mph_types_TypeBinaryOp(ctx, NULL, _arg_604, _arg_607, _arg_608); mph_gc_pop_roots(ctx, 3); _ret_609; });
	mph_gc_push_root(ctx, (void**)&result);
	if (({ mph_types_TypeResult* _obj_610 = result; mph_gc_push_root(ctx, (void**)&_obj_610); mph_bool _ret_611 = _obj_610->has_error; mph_gc_pop_roots(ctx, 1); _ret_611; })) {
{
	({ mph_checker_Checker* _arg_612 = c; mph_gc_push_root(ctx, (void**)&_arg_612); MorphString* _arg_615 = ({ mph_types_TypeResult* _obj_613 = result; mph_gc_push_root(ctx, (void**)&_obj_613); MorphString* _ret_614 = _obj_613->error_msg; mph_gc_pop_roots(ctx, 1); _ret_614; }); mph_gc_push_root(ctx, (void**)&_arg_615); mph_checker_checker_add_error(ctx, NULL, _arg_612, _arg_615); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
	return ({ mph_types_TypeResult* _obj_616 = result; mph_gc_push_root(ctx, (void**)&_obj_616); mph_types_Type* _ret_617 = _obj_616->result; mph_gc_pop_roots(ctx, 1); _ret_617; });
	mph_gc_pop_roots(ctx, 3);
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_check_var_statement(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_VarStatement* stmt) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&stmt);
	mph_types_Type* declared_type = mph_types_VoidType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&declared_type);
	if ((({ mph_ast_VarStatement* _obj_618 = stmt; mph_gc_push_root(ctx, (void**)&_obj_618); MorphString* _ret_619 = _obj_618->value_type; mph_gc_pop_roots(ctx, 1); _ret_619; }) != mph_string_new(ctx, "-"))) {
{
	if (mph_string_eq(ctx, ({ mph_ast_VarStatement* _obj_620 = stmt; mph_gc_push_root(ctx, (void**)&_obj_620); MorphString* _ret_621 = _obj_620->value_type; mph_gc_pop_roots(ctx, 1); _ret_621; }), mph_string_new(ctx, "int"))) {
{
	declared_type = mph_types_IntType(ctx, NULL);
}
	} else {
{
	if (mph_string_eq(ctx, ({ mph_ast_VarStatement* _obj_622 = stmt; mph_gc_push_root(ctx, (void**)&_obj_622); MorphString* _ret_623 = _obj_622->value_type; mph_gc_pop_roots(ctx, 1); _ret_623; }), mph_string_new(ctx, "string"))) {
{
	declared_type = mph_types_StringType(ctx, NULL);
}
	} else {
{
	if (mph_string_eq(ctx, ({ mph_ast_VarStatement* _obj_624 = stmt; mph_gc_push_root(ctx, (void**)&_obj_624); MorphString* _ret_625 = _obj_624->value_type; mph_gc_pop_roots(ctx, 1); _ret_625; }), mph_string_new(ctx, "bool"))) {
{
	declared_type = mph_types_BoolType(ctx, NULL);
}
	} else {
{
	({ mph_checker_Checker* _arg_626 = c; mph_gc_push_root(ctx, (void**)&_arg_626); MorphString* _arg_632 = ({ MorphString* _lhs_629 = mph_string_new(ctx, "Unknown type: "); MorphString* _rhs_630 = ({ mph_ast_VarStatement* _obj_627 = stmt; mph_gc_push_root(ctx, (void**)&_obj_627); MorphString* _ret_628 = _obj_627->value_type; mph_gc_pop_roots(ctx, 1); _ret_628; }); mph_gc_push_root(ctx, (void**)&_lhs_629); mph_gc_push_root(ctx, (void**)&_rhs_630); MorphString* _ret_631 = mph_string_concat(ctx, _lhs_629, _rhs_630); mph_gc_pop_roots(ctx, 2); _ret_631; }); mph_gc_push_root(ctx, (void**)&_arg_632); mph_checker_checker_add_error(ctx, NULL, _arg_626, _arg_632); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
}
	}
}
	}
}
	}
	if (({ mph_ast_VarStatement* _obj_633 = stmt; mph_gc_push_root(ctx, (void**)&_obj_633); mph_bool _ret_634 = _obj_633->has_value; mph_gc_pop_roots(ctx, 1); _ret_634; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "Variable '"));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_635 = stmt; mph_gc_push_root(ctx, (void**)&_obj_635); MorphString* _ret_636 = _obj_635->name; mph_gc_pop_roots(ctx, 1); _ret_636; }));
	mph_native_print(ctx, mph_string_new(ctx, "' declared with type "));
	mph_native_print(ctx, mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_637 = declared_type; mph_gc_push_root(ctx, (void**)&_obj_637); mph_int _ret_638 = _obj_637->kind; mph_gc_pop_roots(ctx, 1); _ret_638; })));
	mph_native_print(ctx, mph_string_new(ctx, " and has initial value\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "Variable '"));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_639 = stmt; mph_gc_push_root(ctx, (void**)&_obj_639); MorphString* _ret_640 = _obj_639->name; mph_gc_pop_roots(ctx, 1); _ret_640; }));
	mph_native_print(ctx, mph_string_new(ctx, "' declared with type "));
	mph_native_print(ctx, mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_641 = declared_type; mph_gc_push_root(ctx, (void**)&_obj_641); mph_int _ret_642 = _obj_641->kind; mph_gc_pop_roots(ctx, 1); _ret_642; })));
	mph_native_print(ctx, mph_string_new(ctx, " (no initial value)\n"));
}
	}
	return declared_type;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

void mph_checker_check_program(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_Program* program) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&program);
	mph_native_print(ctx, mph_string_new(ctx, "Type checking program with "));
	mph_native_print_int(ctx, ({ mph_ast_Program* _obj_643 = program; mph_gc_push_root(ctx, (void**)&_obj_643); mph_int _ret_644 = _obj_643->statements_count; mph_gc_pop_roots(ctx, 1); _ret_644; }));
	mph_native_print(ctx, mph_string_new(ctx, " statements\n"));
	if (({ mph_checker_Checker* _arg_645 = c; mph_gc_push_root(ctx, (void**)&_arg_645); mph_bool _ret_646 = mph_checker_checker_has_errors(ctx, NULL, _arg_645); mph_gc_pop_roots(ctx, 1); _ret_646; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "Type checking completed with "));
	mph_native_print_int(ctx, ({ mph_checker_Checker* _obj_647 = c; mph_gc_push_root(ctx, (void**)&_obj_647); mph_int _ret_648 = _obj_647->errors_count; mph_gc_pop_roots(ctx, 1); _ret_648; }));
	mph_native_print(ctx, mph_string_new(ctx, " error(s)\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "Type checking completed successfully\n"));
}
	}
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_check_builtin_function(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, MorphString* name, mph_int args_count) {
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
	({ mph_checker_Checker* _arg_649 = c; mph_gc_push_root(ctx, (void**)&_arg_649); MorphString* _arg_650 = mph_string_new(ctx, "native_print expects 1 argument"); mph_gc_push_root(ctx, (void**)&_arg_650); mph_checker_checker_add_error(ctx, NULL, _arg_649, _arg_650); mph_gc_pop_roots(ctx, 2); });
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
	({ mph_checker_Checker* _arg_651 = c; mph_gc_push_root(ctx, (void**)&_arg_651); MorphString* _arg_652 = mph_string_new(ctx, "native_print_int expects 1 argument"); mph_gc_push_root(ctx, (void**)&_arg_652); mph_checker_checker_add_error(ctx, NULL, _arg_651, _arg_652); mph_gc_pop_roots(ctx, 2); });
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
	({ mph_checker_Checker* _arg_653 = c; mph_gc_push_root(ctx, (void**)&_arg_653); MorphString* _arg_654 = mph_string_new(ctx, "panjang expects 1 argument"); mph_gc_push_root(ctx, (void**)&_arg_654); mph_checker_checker_add_error(ctx, NULL, _arg_653, _arg_654); mph_gc_pop_roots(ctx, 2); });
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
	({ mph_checker_Checker* _arg_655 = c; mph_gc_push_root(ctx, (void**)&_arg_655); MorphString* _arg_656 = mph_string_new(ctx, "substring expects 3 arguments"); mph_gc_push_root(ctx, (void**)&_arg_656); mph_checker_checker_add_error(ctx, NULL, _arg_655, _arg_656); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
}
	}
}
	}
	({ mph_checker_Checker* _arg_657 = c; mph_gc_push_root(ctx, (void**)&_arg_657); MorphString* _arg_661 = ({ MorphString* _lhs_658 = mph_string_new(ctx, "Unknown built-in function: "); MorphString* _rhs_659 = name; mph_gc_push_root(ctx, (void**)&_lhs_658); mph_gc_push_root(ctx, (void**)&_rhs_659); MorphString* _ret_660 = mph_string_concat(ctx, _lhs_658, _rhs_659); mph_gc_pop_roots(ctx, 2); _ret_660; }); mph_gc_push_root(ctx, (void**)&_arg_661); mph_checker_checker_add_error(ctx, NULL, _arg_657, _arg_661); mph_gc_pop_roots(ctx, 2); });
	return mph_types_ErrorType(ctx, NULL);
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_checker_check_assignment_compatibility(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&target_type);
	mph_gc_push_root(ctx, (void**)&value_type);
	if (({ mph_types_Type* _arg_662 = value_type; mph_gc_push_root(ctx, (void**)&_arg_662); mph_types_Type* _arg_663 = target_type; mph_gc_push_root(ctx, (void**)&_arg_663); mph_bool _ret_664 = mph_types_TypeAssignableTo(ctx, NULL, _arg_662, _arg_663); mph_gc_pop_roots(ctx, 2); _ret_664; })) {
{
	return 1;
}
	} else {
{
	({ mph_checker_Checker* _arg_665 = c; mph_gc_push_root(ctx, (void**)&_arg_665); MorphString* _arg_679 = ({ MorphString* _lhs_676 = ({ MorphString* _lhs_671 = ({ MorphString* _lhs_668 = mph_string_new(ctx, "Cannot assign "); MorphString* _rhs_669 = mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_666 = value_type; mph_gc_push_root(ctx, (void**)&_obj_666); mph_int _ret_667 = _obj_666->kind; mph_gc_pop_roots(ctx, 1); _ret_667; })); mph_gc_push_root(ctx, (void**)&_lhs_668); mph_gc_push_root(ctx, (void**)&_rhs_669); MorphString* _ret_670 = mph_string_concat(ctx, _lhs_668, _rhs_669); mph_gc_pop_roots(ctx, 2); _ret_670; }); MorphString* _rhs_672 = mph_string_new(ctx, " to "); mph_gc_push_root(ctx, (void**)&_lhs_671); mph_gc_push_root(ctx, (void**)&_rhs_672); MorphString* _ret_673 = mph_string_concat(ctx, _lhs_671, _rhs_672); mph_gc_pop_roots(ctx, 2); _ret_673; }); MorphString* _rhs_677 = mph_types_KindToString(ctx, NULL, ({ mph_types_Type* _obj_674 = target_type; mph_gc_push_root(ctx, (void**)&_obj_674); mph_int _ret_675 = _obj_674->kind; mph_gc_pop_roots(ctx, 1); _ret_675; })); mph_gc_push_root(ctx, (void**)&_lhs_676); mph_gc_push_root(ctx, (void**)&_rhs_677); MorphString* _ret_678 = mph_string_concat(ctx, _lhs_676, _rhs_677); mph_gc_pop_roots(ctx, 2); _ret_678; }); mph_gc_push_root(ctx, (void**)&_arg_679); mph_checker_checker_add_error(ctx, NULL, _arg_665, _arg_679); mph_gc_pop_roots(ctx, 2); });
	return 0;
}
	}
	mph_gc_pop_roots(ctx, 3);
}

void mph_checker_checker_enter_scope(MorphContext* ctx, void* _env_void, mph_checker_Checker* c) {
	mph_gc_push_root(ctx, (void**)&c);
	({ mph_checker_Checker* _obj_682 = c; mph_gc_push_root(ctx, (void**)&_obj_682); _obj_682->current_scope_level = (({ mph_checker_Checker* _obj_680 = c; mph_gc_push_root(ctx, (void**)&_obj_680); mph_int _ret_681 = _obj_680->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_681; }) + 1); mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Entered scope level "));
	mph_native_print_int(ctx, ({ mph_checker_Checker* _obj_683 = c; mph_gc_push_root(ctx, (void**)&_obj_683); mph_int _ret_684 = _obj_683->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_684; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_checker_checker_exit_scope(MorphContext* ctx, void* _env_void, mph_checker_Checker* c) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_checker_Checker* _obj_685 = c; mph_gc_push_root(ctx, (void**)&_obj_685); mph_int _ret_686 = _obj_685->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_686; }) > 0)) {
{
	({ mph_checker_Checker* _obj_689 = c; mph_gc_push_root(ctx, (void**)&_obj_689); _obj_689->current_scope_level = (({ mph_checker_Checker* _obj_687 = c; mph_gc_push_root(ctx, (void**)&_obj_687); mph_int _ret_688 = _obj_687->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_688; }) - 1); mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Exited to scope level "));
	mph_native_print_int(ctx, ({ mph_checker_Checker* _obj_690 = c; mph_gc_push_root(ctx, (void**)&_obj_690); mph_int _ret_691 = _obj_690->current_scope_level; mph_gc_pop_roots(ctx, 1); _ret_691; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_checker_infer_type_from_literal(MorphContext* ctx, void* _env_void, MorphString* literal, mph_int token_type) {
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

mph_checker_Checker* mph_checker_NewChecker(MorphContext* ctx, void* _env_void) {
	return mph_checker_new_checker(ctx, NULL);
}

mph_types_Type* mph_checker_CheckIntegerLiteral(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_checker_Checker* _arg_692 = c; mph_gc_push_root(ctx, (void**)&_arg_692); mph_ast_IntegerLiteral* _arg_693 = lit; mph_gc_push_root(ctx, (void**)&_arg_693); mph_types_Type* _ret_694 = mph_checker_check_integer_literal(ctx, NULL, _arg_692, _arg_693); mph_gc_pop_roots(ctx, 2); _ret_694; });
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_CheckStringLiteral(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_checker_Checker* _arg_695 = c; mph_gc_push_root(ctx, (void**)&_arg_695); mph_ast_StringLiteral* _arg_696 = lit; mph_gc_push_root(ctx, (void**)&_arg_696); mph_types_Type* _ret_697 = mph_checker_check_string_literal(ctx, NULL, _arg_695, _arg_696); mph_gc_pop_roots(ctx, 2); _ret_697; });
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_CheckBooleanLiteral(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_checker_Checker* _arg_698 = c; mph_gc_push_root(ctx, (void**)&_arg_698); mph_ast_BooleanLiteral* _arg_699 = lit; mph_gc_push_root(ctx, (void**)&_arg_699); mph_types_Type* _ret_700 = mph_checker_check_boolean_literal(ctx, NULL, _arg_698, _arg_699); mph_gc_pop_roots(ctx, 2); _ret_700; });
	mph_gc_pop_roots(ctx, 2);
}

mph_types_Type* mph_checker_CheckBuiltinFunction(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, MorphString* name, mph_int args_count) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&name);
	return ({ mph_checker_Checker* _arg_701 = c; mph_gc_push_root(ctx, (void**)&_arg_701); MorphString* _arg_702 = name; mph_gc_push_root(ctx, (void**)&_arg_702); mph_types_Type* _ret_703 = mph_checker_check_builtin_function(ctx, NULL, _arg_701, _arg_702, args_count); mph_gc_pop_roots(ctx, 2); _ret_703; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_checker_CheckAssignmentCompatibility(MorphContext* ctx, void* _env_void, mph_checker_Checker* c, mph_types_Type* target_type, mph_types_Type* value_type) {
	mph_gc_push_root(ctx, (void**)&c);
	mph_gc_push_root(ctx, (void**)&target_type);
	mph_gc_push_root(ctx, (void**)&value_type);
	return ({ mph_checker_Checker* _arg_704 = c; mph_gc_push_root(ctx, (void**)&_arg_704); mph_types_Type* _arg_705 = target_type; mph_gc_push_root(ctx, (void**)&_arg_705); mph_types_Type* _arg_706 = value_type; mph_gc_push_root(ctx, (void**)&_arg_706); mph_bool _ret_707 = mph_checker_check_assignment_compatibility(ctx, NULL, _arg_704, _arg_705, _arg_706); mph_gc_pop_roots(ctx, 3); _ret_707; });
	mph_gc_pop_roots(ctx, 3);
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

mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_ast_Node* _t = (mph_ast_Node*)mph_alloc(ctx, sizeof(mph_ast_Node), &mph_ti_mph_ast_Node); mph_gc_push_root(ctx, (void**)&_t); _t->token_literal = literal; _t->line = line; _t->column = column; _t->node_type = node_type; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void) {
	mph_ast_Node* base = ({ MorphString* _arg_708 = mph_string_new(ctx, "program"); mph_gc_push_root(ctx, (void**)&_arg_708); mph_ast_Node* _ret_709 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PROGRAM, _arg_708, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_709; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_Program* _t = (mph_ast_Program*)mph_alloc(ctx, sizeof(mph_ast_Program), &mph_ti_mph_ast_Program); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->statements_count = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Identifier* mph_ast_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_710 = name; mph_gc_push_root(ctx, (void**)&_arg_710); mph_ast_Node* _ret_711 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IDENTIFIER, _arg_710, line, column); mph_gc_pop_roots(ctx, 1); _ret_711; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_Identifier* _t = (mph_ast_Identifier*)mph_alloc(ctx, sizeof(mph_ast_Identifier), &mph_ti_mph_ast_Identifier); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = name; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_IntegerLiteral* mph_ast_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_712 = literal; mph_gc_push_root(ctx, (void**)&_arg_712); mph_ast_Node* _ret_713 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INTEGER_LITERAL, _arg_712, line, column); mph_gc_pop_roots(ctx, 1); _ret_713; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_IntegerLiteral* _t = (mph_ast_IntegerLiteral*)mph_alloc(ctx, sizeof(mph_ast_IntegerLiteral), &mph_ti_mph_ast_IntegerLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StringLiteral* mph_ast_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value);
	mph_ast_Node* base = ({ MorphString* _arg_714 = value; mph_gc_push_root(ctx, (void**)&_arg_714); mph_ast_Node* _ret_715 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRING_LITERAL, _arg_714, line, column); mph_gc_pop_roots(ctx, 1); _ret_715; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StringLiteral* _t = (mph_ast_StringLiteral*)mph_alloc(ctx, sizeof(mph_ast_StringLiteral), &mph_ti_mph_ast_StringLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BooleanLiteral* mph_ast_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_716 = literal; mph_gc_push_root(ctx, (void**)&_arg_716); mph_ast_Node* _ret_717 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BOOLEAN_LITERAL, _arg_716, line, column); mph_gc_pop_roots(ctx, 1); _ret_717; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BooleanLiteral* _t = (mph_ast_BooleanLiteral*)mph_alloc(ctx, sizeof(mph_ast_BooleanLiteral), &mph_ti_mph_ast_BooleanLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->value = value; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_VarStatement* mph_ast_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&type_str);
	mph_ast_Node* base = ({ MorphString* _arg_718 = mph_string_new(ctx, "var"); mph_gc_push_root(ctx, (void**)&_arg_718); mph_ast_Node* _ret_719 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_VAR_STATEMENT, _arg_718, line, column); mph_gc_pop_roots(ctx, 1); _ret_719; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_VarStatement* _t = (mph_ast_VarStatement*)mph_alloc(ctx, sizeof(mph_ast_VarStatement), &mph_ti_mph_ast_VarStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->value_type = type_str; _t->has_value = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_PrefixExpression* mph_ast_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_720 = operator; mph_gc_push_root(ctx, (void**)&_arg_720); mph_ast_Node* _ret_721 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PREFIX_EXPRESSION, _arg_720, line, column); mph_gc_pop_roots(ctx, 1); _ret_721; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_PrefixExpression* _t = (mph_ast_PrefixExpression*)mph_alloc(ctx, sizeof(mph_ast_PrefixExpression), &mph_ti_mph_ast_PrefixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_InfixExpression* mph_ast_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_722 = operator; mph_gc_push_root(ctx, (void**)&_arg_722); mph_ast_Node* _ret_723 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INFIX_EXPRESSION, _arg_722, line, column); mph_gc_pop_roots(ctx, 1); _ret_723; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_InfixExpression* _t = (mph_ast_InfixExpression*)mph_alloc(ctx, sizeof(mph_ast_InfixExpression), &mph_ti_mph_ast_InfixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_724 = mph_string_new(ctx, "kasus"); mph_gc_push_root(ctx, (void**)&_arg_724); mph_ast_Node* _ret_725 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CASE_CLAUSE, _arg_724, line, column); mph_gc_pop_roots(ctx, 1); _ret_725; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CaseClause* _t = (mph_ast_CaseClause*)mph_alloc(ctx, sizeof(mph_ast_CaseClause), &mph_ti_mph_ast_CaseClause); mph_gc_push_root(ctx, (void**)&_t); _t->v3 = 0; _t->has_body = 0; _t->base = base; _t->values_count = 0; _t->v0 = 0; _t->v1 = 0; _t->v2 = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_case_add_value(MorphContext* ctx, void* _env_void, mph_ast_CaseClause* c, mph_int val) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_ast_CaseClause* _obj_726 = c; mph_gc_push_root(ctx, (void**)&_obj_726); mph_int _ret_727 = _obj_726->values_count; mph_gc_pop_roots(ctx, 1); _ret_727; }) == 0)) {
{
	({ mph_ast_CaseClause* _obj_728 = c; mph_gc_push_root(ctx, (void**)&_obj_728); _obj_728->v0 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_729 = c; mph_gc_push_root(ctx, (void**)&_obj_729); mph_int _ret_730 = _obj_729->values_count; mph_gc_pop_roots(ctx, 1); _ret_730; }) == 1)) {
{
	({ mph_ast_CaseClause* _obj_731 = c; mph_gc_push_root(ctx, (void**)&_obj_731); _obj_731->v1 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_732 = c; mph_gc_push_root(ctx, (void**)&_obj_732); mph_int _ret_733 = _obj_732->values_count; mph_gc_pop_roots(ctx, 1); _ret_733; }) == 2)) {
{
	({ mph_ast_CaseClause* _obj_734 = c; mph_gc_push_root(ctx, (void**)&_obj_734); _obj_734->v2 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_735 = c; mph_gc_push_root(ctx, (void**)&_obj_735); mph_int _ret_736 = _obj_735->values_count; mph_gc_pop_roots(ctx, 1); _ret_736; }) == 3)) {
{
	({ mph_ast_CaseClause* _obj_737 = c; mph_gc_push_root(ctx, (void**)&_obj_737); _obj_737->v3 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	({ mph_ast_CaseClause* _obj_740 = c; mph_gc_push_root(ctx, (void**)&_obj_740); _obj_740->values_count = (({ mph_ast_CaseClause* _obj_738 = c; mph_gc_push_root(ctx, (void**)&_obj_738); mph_int _ret_739 = _obj_738->values_count; mph_gc_pop_roots(ctx, 1); _ret_739; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return c;
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_SwitchStatement* mph_ast_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_741 = mph_string_new(ctx, "pilih"); mph_gc_push_root(ctx, (void**)&_arg_741); mph_ast_Node* _ret_742 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_SWITCH_STATEMENT, _arg_741, line, column); mph_gc_pop_roots(ctx, 1); _ret_742; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_SwitchStatement* _t = (mph_ast_SwitchStatement*)mph_alloc(ctx, sizeof(mph_ast_SwitchStatement), &mph_ti_mph_ast_SwitchStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->cases_count = 0; _t->has_default = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_WhileStatement* mph_ast_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_743 = mph_string_new(ctx, "selama"); mph_gc_push_root(ctx, (void**)&_arg_743); mph_ast_Node* _ret_744 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_WHILE_STATEMENT, _arg_743, line, column); mph_gc_pop_roots(ctx, 1); _ret_744; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_WhileStatement* _t = (mph_ast_WhileStatement*)mph_alloc(ctx, sizeof(mph_ast_WhileStatement), &mph_ti_mph_ast_WhileStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->has_body = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StructStatement* mph_ast_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_745 = mph_string_new(ctx, "struktur"); mph_gc_push_root(ctx, (void**)&_arg_745); mph_ast_Node* _ret_746 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRUCT_STATEMENT, _arg_745, line, column); mph_gc_pop_roots(ctx, 1); _ret_746; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StructStatement* _t = (mph_ast_StructStatement*)mph_alloc(ctx, sizeof(mph_ast_StructStatement), &mph_ti_mph_ast_StructStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->fields_count = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ImportStatement* mph_ast_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&path);
	mph_ast_Node* base = ({ MorphString* _arg_747 = mph_string_new(ctx, "ambil"); mph_gc_push_root(ctx, (void**)&_arg_747); mph_ast_Node* _ret_748 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IMPORT_STATEMENT, _arg_747, line, column); mph_gc_pop_roots(ctx, 1); _ret_748; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_ImportStatement* _t = (mph_ast_ImportStatement*)mph_alloc(ctx, sizeof(mph_ast_ImportStatement), &mph_ti_mph_ast_ImportStatement); mph_gc_push_root(ctx, (void**)&_t); _t->path = path; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BreakStatement* mph_ast_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_749 = mph_string_new(ctx, "putus"); mph_gc_push_root(ctx, (void**)&_arg_749); mph_ast_Node* _ret_750 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BREAK_STATEMENT, _arg_749, line, column); mph_gc_pop_roots(ctx, 1); _ret_750; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BreakStatement* _t = (mph_ast_BreakStatement*)mph_alloc(ctx, sizeof(mph_ast_BreakStatement), &mph_ti_mph_ast_BreakStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ContinueStatement* mph_ast_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_751 = mph_string_new(ctx, "lanjut"); mph_gc_push_root(ctx, (void**)&_arg_751); mph_ast_Node* _ret_752 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CONTINUE_STATEMENT, _arg_751, line, column); mph_gc_pop_roots(ctx, 1); _ret_752; });
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
	mph_native_print(ctx, mph_ast_node_type_string(ctx, NULL, ({ mph_ast_Node* _obj_753 = node; mph_gc_push_root(ctx, (void**)&_obj_753); mph_int _ret_754 = _obj_753->node_type; mph_gc_pop_roots(ctx, 1); _ret_754; })));
	mph_native_print(ctx, mph_string_new(ctx, " at line "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_755 = node; mph_gc_push_root(ctx, (void**)&_obj_755); mph_int _ret_756 = _obj_755->line; mph_gc_pop_roots(ctx, 1); _ret_756; }));
	mph_native_print(ctx, mph_string_new(ctx, ", column "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_757 = node; mph_gc_push_root(ctx, (void**)&_obj_757); mph_int _ret_758 = _obj_757->column; mph_gc_pop_roots(ctx, 1); _ret_758; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	mph_native_print(ctx, mph_string_new(ctx, "Identifier: "));
	mph_native_print(ctx, ({ mph_ast_Identifier* _obj_759 = ident; mph_gc_push_root(ctx, (void**)&_obj_759); MorphString* _ret_760 = _obj_759->value; mph_gc_pop_roots(ctx, 1); _ret_760; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_763 = ({ mph_ast_Identifier* _obj_761 = ident; mph_gc_push_root(ctx, (void**)&_obj_761); mph_ast_Node* _ret_762 = _obj_761->base; mph_gc_pop_roots(ctx, 1); _ret_762; }); mph_gc_push_root(ctx, (void**)&_obj_763); mph_int _ret_764 = _obj_763->line; mph_gc_pop_roots(ctx, 1); _ret_764; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_767 = ({ mph_ast_Identifier* _obj_765 = ident; mph_gc_push_root(ctx, (void**)&_obj_765); mph_ast_Node* _ret_766 = _obj_765->base; mph_gc_pop_roots(ctx, 1); _ret_766; }); mph_gc_push_root(ctx, (void**)&_obj_767); mph_int _ret_768 = _obj_767->column; mph_gc_pop_roots(ctx, 1); _ret_768; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "IntegerLiteral: "));
	mph_native_print_int(ctx, ({ mph_ast_IntegerLiteral* _obj_769 = lit; mph_gc_push_root(ctx, (void**)&_obj_769); mph_int _ret_770 = _obj_769->value; mph_gc_pop_roots(ctx, 1); _ret_770; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_773 = ({ mph_ast_IntegerLiteral* _obj_771 = lit; mph_gc_push_root(ctx, (void**)&_obj_771); mph_ast_Node* _ret_772 = _obj_771->base; mph_gc_pop_roots(ctx, 1); _ret_772; }); mph_gc_push_root(ctx, (void**)&_obj_773); mph_int _ret_774 = _obj_773->line; mph_gc_pop_roots(ctx, 1); _ret_774; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_777 = ({ mph_ast_IntegerLiteral* _obj_775 = lit; mph_gc_push_root(ctx, (void**)&_obj_775); mph_ast_Node* _ret_776 = _obj_775->base; mph_gc_pop_roots(ctx, 1); _ret_776; }); mph_gc_push_root(ctx, (void**)&_obj_777); mph_int _ret_778 = _obj_777->column; mph_gc_pop_roots(ctx, 1); _ret_778; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "StringLiteral: \""));
	mph_native_print(ctx, ({ mph_ast_StringLiteral* _obj_779 = lit; mph_gc_push_root(ctx, (void**)&_obj_779); MorphString* _ret_780 = _obj_779->value; mph_gc_pop_roots(ctx, 1); _ret_780; }));
	mph_native_print(ctx, mph_string_new(ctx, "\" ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_783 = ({ mph_ast_StringLiteral* _obj_781 = lit; mph_gc_push_root(ctx, (void**)&_obj_781); mph_ast_Node* _ret_782 = _obj_781->base; mph_gc_pop_roots(ctx, 1); _ret_782; }); mph_gc_push_root(ctx, (void**)&_obj_783); mph_int _ret_784 = _obj_783->line; mph_gc_pop_roots(ctx, 1); _ret_784; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_787 = ({ mph_ast_StringLiteral* _obj_785 = lit; mph_gc_push_root(ctx, (void**)&_obj_785); mph_ast_Node* _ret_786 = _obj_785->base; mph_gc_pop_roots(ctx, 1); _ret_786; }); mph_gc_push_root(ctx, (void**)&_obj_787); mph_int _ret_788 = _obj_787->column; mph_gc_pop_roots(ctx, 1); _ret_788; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "BooleanLiteral: "));
	if (({ mph_ast_BooleanLiteral* _obj_789 = lit; mph_gc_push_root(ctx, (void**)&_obj_789); mph_bool _ret_790 = _obj_789->value; mph_gc_pop_roots(ctx, 1); _ret_790; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "benar"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "salah"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_793 = ({ mph_ast_BooleanLiteral* _obj_791 = lit; mph_gc_push_root(ctx, (void**)&_obj_791); mph_ast_Node* _ret_792 = _obj_791->base; mph_gc_pop_roots(ctx, 1); _ret_792; }); mph_gc_push_root(ctx, (void**)&_obj_793); mph_int _ret_794 = _obj_793->line; mph_gc_pop_roots(ctx, 1); _ret_794; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_797 = ({ mph_ast_BooleanLiteral* _obj_795 = lit; mph_gc_push_root(ctx, (void**)&_obj_795); mph_ast_Node* _ret_796 = _obj_795->base; mph_gc_pop_roots(ctx, 1); _ret_796; }); mph_gc_push_root(ctx, (void**)&_obj_797); mph_int _ret_798 = _obj_797->column; mph_gc_pop_roots(ctx, 1); _ret_798; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_make_type(MorphContext* ctx, void* _env_void, mph_int k, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ mph_types_Type* _t = (mph_types_Type*)mph_alloc(ctx, sizeof(mph_types_Type), &mph_ti_mph_types_Type); mph_gc_push_root(ctx, (void**)&_t); _t->kind = k; _t->name = n; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_int_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_799 = mph_string_new(ctx, "int"); mph_gc_push_root(ctx, (void**)&_arg_799); mph_types_Type* _ret_800 = mph_types_make_type(ctx, NULL, mph_types_KIND_INT, _arg_799); mph_gc_pop_roots(ctx, 1); _ret_800; });
}

mph_types_Type* mph_types_float_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_801 = mph_string_new(ctx, "float"); mph_gc_push_root(ctx, (void**)&_arg_801); mph_types_Type* _ret_802 = mph_types_make_type(ctx, NULL, mph_types_KIND_FLOAT, _arg_801); mph_gc_pop_roots(ctx, 1); _ret_802; });
}

mph_types_Type* mph_types_string_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_803 = mph_string_new(ctx, "string"); mph_gc_push_root(ctx, (void**)&_arg_803); mph_types_Type* _ret_804 = mph_types_make_type(ctx, NULL, mph_types_KIND_STRING, _arg_803); mph_gc_pop_roots(ctx, 1); _ret_804; });
}

mph_types_Type* mph_types_bool_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_805 = mph_string_new(ctx, "bool"); mph_gc_push_root(ctx, (void**)&_arg_805); mph_types_Type* _ret_806 = mph_types_make_type(ctx, NULL, mph_types_KIND_BOOL, _arg_805); mph_gc_pop_roots(ctx, 1); _ret_806; });
}

mph_types_Type* mph_types_void_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_807 = mph_string_new(ctx, "void"); mph_gc_push_root(ctx, (void**)&_arg_807); mph_types_Type* _ret_808 = mph_types_make_type(ctx, NULL, mph_types_KIND_VOID, _arg_807); mph_gc_pop_roots(ctx, 1); _ret_808; });
}

mph_types_Type* mph_types_null_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_809 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_809); mph_types_Type* _ret_810 = mph_types_make_type(ctx, NULL, mph_types_KIND_NULL, _arg_809); mph_gc_pop_roots(ctx, 1); _ret_810; });
}

mph_types_Type* mph_types_unknown_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_811 = mph_string_new(ctx, "unknown"); mph_gc_push_root(ctx, (void**)&_arg_811); mph_types_Type* _ret_812 = mph_types_make_type(ctx, NULL, mph_types_KIND_UNKNOWN, _arg_811); mph_gc_pop_roots(ctx, 1); _ret_812; });
}

mph_types_Type* mph_types_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_813 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_813); mph_types_Type* _ret_814 = mph_types_make_type(ctx, NULL, mph_types_KIND_ERROR, _arg_813); mph_gc_pop_roots(ctx, 1); _ret_814; });
}

mph_types_Type* mph_types_user_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_815 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_815); mph_types_Type* _ret_816 = mph_types_make_type(ctx, NULL, mph_types_KIND_USER_ERROR, _arg_815); mph_gc_pop_roots(ctx, 1); _ret_816; });
}

mph_types_Type* mph_types_channel_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_817 = mph_string_new(ctx, "channel"); mph_gc_push_root(ctx, (void**)&_arg_817); mph_types_Type* _ret_818 = mph_types_make_type(ctx, NULL, mph_types_KIND_CHANNEL, _arg_817); mph_gc_pop_roots(ctx, 1); _ret_818; });
}

mph_types_Type* mph_types_array_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_819 = mph_string_new(ctx, "array"); mph_gc_push_root(ctx, (void**)&_arg_819); mph_types_Type* _ret_820 = mph_types_make_type(ctx, NULL, mph_types_KIND_ARRAY, _arg_819); mph_gc_pop_roots(ctx, 1); _ret_820; });
}

mph_types_Type* mph_types_map_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_821 = mph_string_new(ctx, "map"); mph_gc_push_root(ctx, (void**)&_arg_821); mph_types_Type* _ret_822 = mph_types_make_type(ctx, NULL, mph_types_KIND_MAP, _arg_821); mph_gc_pop_roots(ctx, 1); _ret_822; });
}

mph_types_Type* mph_types_struct_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_823 = n; mph_gc_push_root(ctx, (void**)&_arg_823); mph_types_Type* _ret_824 = mph_types_make_type(ctx, NULL, mph_types_KIND_STRUCT, _arg_823); mph_gc_pop_roots(ctx, 1); _ret_824; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_interface_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_825 = n; mph_gc_push_root(ctx, (void**)&_arg_825); mph_types_Type* _ret_826 = mph_types_make_type(ctx, NULL, mph_types_KIND_INTERFACE, _arg_825); mph_gc_pop_roots(ctx, 1); _ret_826; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_function_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_827 = mph_string_new(ctx, "function"); mph_gc_push_root(ctx, (void**)&_arg_827); mph_types_Type* _ret_828 = mph_types_make_type(ctx, NULL, mph_types_KIND_FUNCTION, _arg_827); mph_gc_pop_roots(ctx, 1); _ret_828; });
}

mph_types_Type* mph_types_pointer_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_829 = mph_string_new(ctx, "pointer"); mph_gc_push_root(ctx, (void**)&_arg_829); mph_types_Type* _ret_830 = mph_types_make_type(ctx, NULL, mph_types_KIND_POINTER, _arg_829); mph_gc_pop_roots(ctx, 1); _ret_830; });
}

mph_types_Type* mph_types_multi_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_831 = mph_string_new(ctx, "multi"); mph_gc_push_root(ctx, (void**)&_arg_831); mph_types_Type* _ret_832 = mph_types_make_type(ctx, NULL, mph_types_KIND_MULTI, _arg_831); mph_gc_pop_roots(ctx, 1); _ret_832; });
}

mph_types_Type* mph_types_module_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_833 = n; mph_gc_push_root(ctx, (void**)&_arg_833); mph_types_Type* _ret_834 = mph_types_make_type(ctx, NULL, mph_types_KIND_MODULE, _arg_833); mph_gc_pop_roots(ctx, 1); _ret_834; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_types_type_equals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return (({ mph_types_Type* _obj_835 = t1; mph_gc_push_root(ctx, (void**)&_obj_835); mph_int _ret_836 = _obj_835->kind; mph_gc_pop_roots(ctx, 1); _ret_836; }) == ({ mph_types_Type* _obj_837 = t2; mph_gc_push_root(ctx, (void**)&_obj_837); mph_int _ret_838 = _obj_837->kind; mph_gc_pop_roots(ctx, 1); _ret_838; }));
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_type_assignable_to(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	if ((({ mph_types_Type* _obj_839 = source; mph_gc_push_root(ctx, (void**)&_obj_839); mph_int _ret_840 = _obj_839->kind; mph_gc_pop_roots(ctx, 1); _ret_840; }) == mph_types_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_841 = target; mph_gc_push_root(ctx, (void**)&_obj_841); mph_int _ret_842 = _obj_841->kind; mph_gc_pop_roots(ctx, 1); _ret_842; }) == mph_types_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_843 = source; mph_gc_push_root(ctx, (void**)&_obj_843); mph_int _ret_844 = _obj_843->kind; mph_gc_pop_roots(ctx, 1); _ret_844; }) == mph_types_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_845 = target; mph_gc_push_root(ctx, (void**)&_obj_845); mph_int _ret_846 = _obj_845->kind; mph_gc_pop_roots(ctx, 1); _ret_846; }) == mph_types_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_847 = source; mph_gc_push_root(ctx, (void**)&_obj_847); mph_int _ret_848 = _obj_847->kind; mph_gc_pop_roots(ctx, 1); _ret_848; }) == mph_types_KIND_NULL)) {
{
	if ((({ mph_types_Type* _obj_849 = target; mph_gc_push_root(ctx, (void**)&_obj_849); mph_int _ret_850 = _obj_849->kind; mph_gc_pop_roots(ctx, 1); _ret_850; }) == mph_types_KIND_ARRAY)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_851 = target; mph_gc_push_root(ctx, (void**)&_obj_851); mph_int _ret_852 = _obj_851->kind; mph_gc_pop_roots(ctx, 1); _ret_852; }) == mph_types_KIND_MAP)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_853 = target; mph_gc_push_root(ctx, (void**)&_obj_853); mph_int _ret_854 = _obj_853->kind; mph_gc_pop_roots(ctx, 1); _ret_854; }) == mph_types_KIND_POINTER)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_855 = target; mph_gc_push_root(ctx, (void**)&_obj_855); mph_int _ret_856 = _obj_855->kind; mph_gc_pop_roots(ctx, 1); _ret_856; }) == mph_types_KIND_INTERFACE)) {
{
	return 1;
}
	}
	return 0;
}
	}
	return ({ mph_types_Type* _arg_857 = source; mph_gc_push_root(ctx, (void**)&_arg_857); mph_types_Type* _arg_858 = target; mph_gc_push_root(ctx, (void**)&_arg_858); mph_bool _ret_859 = mph_types_type_equals(ctx, NULL, _arg_857, _arg_858); mph_gc_pop_roots(ctx, 2); _ret_859; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_type_is_comparable(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	if ((({ mph_types_Type* _obj_860 = t; mph_gc_push_root(ctx, (void**)&_obj_860); mph_int _ret_861 = _obj_860->kind; mph_gc_pop_roots(ctx, 1); _ret_861; }) == mph_types_KIND_INT)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_862 = t; mph_gc_push_root(ctx, (void**)&_obj_862); mph_int _ret_863 = _obj_862->kind; mph_gc_pop_roots(ctx, 1); _ret_863; }) == mph_types_KIND_FLOAT)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_864 = t; mph_gc_push_root(ctx, (void**)&_obj_864); mph_int _ret_865 = _obj_864->kind; mph_gc_pop_roots(ctx, 1); _ret_865; }) == mph_types_KIND_STRING)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_866 = t; mph_gc_push_root(ctx, (void**)&_obj_866); mph_int _ret_867 = _obj_866->kind; mph_gc_pop_roots(ctx, 1); _ret_867; }) == mph_types_KIND_BOOL)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_868 = t; mph_gc_push_root(ctx, (void**)&_obj_868); mph_int _ret_869 = _obj_868->kind; mph_gc_pop_roots(ctx, 1); _ret_869; }) == mph_types_KIND_NULL)) {
{
	return 1;
}
	}
	if ((({ mph_types_Type* _obj_870 = t; mph_gc_push_root(ctx, (void**)&_obj_870); mph_int _ret_871 = _obj_870->kind; mph_gc_pop_roots(ctx, 1); _ret_871; }) == mph_types_KIND_USER_ERROR)) {
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
	if ((({ mph_types_Type* _obj_872 = left; mph_gc_push_root(ctx, (void**)&_obj_872); mph_int _ret_873 = _obj_872->kind; mph_gc_pop_roots(ctx, 1); _ret_873; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_874 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_874); mph_types_TypeResult* _ret_875 = mph_types_make_type_result(ctx, NULL, _arg_874); mph_gc_pop_roots(ctx, 1); _ret_875; });
}
	}
	if ((({ mph_types_Type* _obj_876 = right; mph_gc_push_root(ctx, (void**)&_obj_876); mph_int _ret_877 = _obj_876->kind; mph_gc_pop_roots(ctx, 1); _ret_877; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_878 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_878); mph_types_TypeResult* _ret_879 = mph_types_make_type_result(ctx, NULL, _arg_878); mph_gc_pop_roots(ctx, 1); _ret_879; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "+"))) {
{
	if ((({ mph_types_Type* _obj_880 = left; mph_gc_push_root(ctx, (void**)&_obj_880); mph_int _ret_881 = _obj_880->kind; mph_gc_pop_roots(ctx, 1); _ret_881; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_882 = right; mph_gc_push_root(ctx, (void**)&_obj_882); mph_int _ret_883 = _obj_882->kind; mph_gc_pop_roots(ctx, 1); _ret_883; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_884 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_884); mph_types_TypeResult* _ret_885 = mph_types_make_type_result(ctx, NULL, _arg_884); mph_gc_pop_roots(ctx, 1); _ret_885; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_886 = left; mph_gc_push_root(ctx, (void**)&_obj_886); mph_int _ret_887 = _obj_886->kind; mph_gc_pop_roots(ctx, 1); _ret_887; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_888 = right; mph_gc_push_root(ctx, (void**)&_obj_888); mph_int _ret_889 = _obj_888->kind; mph_gc_pop_roots(ctx, 1); _ret_889; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_890 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_890); mph_types_TypeResult* _ret_891 = mph_types_make_type_result(ctx, NULL, _arg_890); mph_gc_pop_roots(ctx, 1); _ret_891; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_892 = left; mph_gc_push_root(ctx, (void**)&_obj_892); mph_int _ret_893 = _obj_892->kind; mph_gc_pop_roots(ctx, 1); _ret_893; }) == mph_types_KIND_STRING)) {
{
	if ((({ mph_types_Type* _obj_894 = right; mph_gc_push_root(ctx, (void**)&_obj_894); mph_int _ret_895 = _obj_894->kind; mph_gc_pop_roots(ctx, 1); _ret_895; }) == mph_types_KIND_STRING)) {
{
	return ({ mph_types_Type* _arg_896 = mph_types_string_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_896); mph_types_TypeResult* _ret_897 = mph_types_make_type_result(ctx, NULL, _arg_896); mph_gc_pop_roots(ctx, 1); _ret_897; });
}
	}
}
	}
	return ({ MorphString* _arg_898 = mph_string_new(ctx, "+ tidak didukung untuk tipe ini"); mph_gc_push_root(ctx, (void**)&_arg_898); mph_types_TypeResult* _ret_899 = mph_types_make_type_error(ctx, NULL, _arg_898); mph_gc_pop_roots(ctx, 1); _ret_899; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_types_Type* _obj_900 = left; mph_gc_push_root(ctx, (void**)&_obj_900); mph_int _ret_901 = _obj_900->kind; mph_gc_pop_roots(ctx, 1); _ret_901; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_902 = right; mph_gc_push_root(ctx, (void**)&_obj_902); mph_int _ret_903 = _obj_902->kind; mph_gc_pop_roots(ctx, 1); _ret_903; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_904 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_904); mph_types_TypeResult* _ret_905 = mph_types_make_type_result(ctx, NULL, _arg_904); mph_gc_pop_roots(ctx, 1); _ret_905; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_906 = left; mph_gc_push_root(ctx, (void**)&_obj_906); mph_int _ret_907 = _obj_906->kind; mph_gc_pop_roots(ctx, 1); _ret_907; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_908 = right; mph_gc_push_root(ctx, (void**)&_obj_908); mph_int _ret_909 = _obj_908->kind; mph_gc_pop_roots(ctx, 1); _ret_909; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_910 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_910); mph_types_TypeResult* _ret_911 = mph_types_make_type_result(ctx, NULL, _arg_910); mph_gc_pop_roots(ctx, 1); _ret_911; });
}
	}
}
	}
	return ({ MorphString* _arg_912 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_912); mph_types_TypeResult* _ret_913 = mph_types_make_type_error(ctx, NULL, _arg_912); mph_gc_pop_roots(ctx, 1); _ret_913; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "*"))) {
{
	if ((({ mph_types_Type* _obj_914 = left; mph_gc_push_root(ctx, (void**)&_obj_914); mph_int _ret_915 = _obj_914->kind; mph_gc_pop_roots(ctx, 1); _ret_915; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_916 = right; mph_gc_push_root(ctx, (void**)&_obj_916); mph_int _ret_917 = _obj_916->kind; mph_gc_pop_roots(ctx, 1); _ret_917; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_918 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_918); mph_types_TypeResult* _ret_919 = mph_types_make_type_result(ctx, NULL, _arg_918); mph_gc_pop_roots(ctx, 1); _ret_919; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_920 = left; mph_gc_push_root(ctx, (void**)&_obj_920); mph_int _ret_921 = _obj_920->kind; mph_gc_pop_roots(ctx, 1); _ret_921; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_922 = right; mph_gc_push_root(ctx, (void**)&_obj_922); mph_int _ret_923 = _obj_922->kind; mph_gc_pop_roots(ctx, 1); _ret_923; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_924 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_924); mph_types_TypeResult* _ret_925 = mph_types_make_type_result(ctx, NULL, _arg_924); mph_gc_pop_roots(ctx, 1); _ret_925; });
}
	}
}
	}
	return ({ MorphString* _arg_926 = mph_string_new(ctx, "* memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_926); mph_types_TypeResult* _ret_927 = mph_types_make_type_error(ctx, NULL, _arg_926); mph_gc_pop_roots(ctx, 1); _ret_927; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "/"))) {
{
	if ((({ mph_types_Type* _obj_928 = left; mph_gc_push_root(ctx, (void**)&_obj_928); mph_int _ret_929 = _obj_928->kind; mph_gc_pop_roots(ctx, 1); _ret_929; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_930 = right; mph_gc_push_root(ctx, (void**)&_obj_930); mph_int _ret_931 = _obj_930->kind; mph_gc_pop_roots(ctx, 1); _ret_931; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_932 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_932); mph_types_TypeResult* _ret_933 = mph_types_make_type_result(ctx, NULL, _arg_932); mph_gc_pop_roots(ctx, 1); _ret_933; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_934 = left; mph_gc_push_root(ctx, (void**)&_obj_934); mph_int _ret_935 = _obj_934->kind; mph_gc_pop_roots(ctx, 1); _ret_935; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_936 = right; mph_gc_push_root(ctx, (void**)&_obj_936); mph_int _ret_937 = _obj_936->kind; mph_gc_pop_roots(ctx, 1); _ret_937; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_938 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_938); mph_types_TypeResult* _ret_939 = mph_types_make_type_result(ctx, NULL, _arg_938); mph_gc_pop_roots(ctx, 1); _ret_939; });
}
	}
}
	}
	return ({ MorphString* _arg_940 = mph_string_new(ctx, "/ memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_940); mph_types_TypeResult* _ret_941 = mph_types_make_type_error(ctx, NULL, _arg_940); mph_gc_pop_roots(ctx, 1); _ret_941; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "%"))) {
{
	if ((({ mph_types_Type* _obj_942 = left; mph_gc_push_root(ctx, (void**)&_obj_942); mph_int _ret_943 = _obj_942->kind; mph_gc_pop_roots(ctx, 1); _ret_943; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_944 = right; mph_gc_push_root(ctx, (void**)&_obj_944); mph_int _ret_945 = _obj_944->kind; mph_gc_pop_roots(ctx, 1); _ret_945; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_946 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_946); mph_types_TypeResult* _ret_947 = mph_types_make_type_result(ctx, NULL, _arg_946); mph_gc_pop_roots(ctx, 1); _ret_947; });
}
	}
}
	}
	return ({ MorphString* _arg_948 = mph_string_new(ctx, "% memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_948); mph_types_TypeResult* _ret_949 = mph_types_make_type_error(ctx, NULL, _arg_948); mph_gc_pop_roots(ctx, 1); _ret_949; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "=="))) {
{
	if (({ mph_types_Type* _arg_950 = left; mph_gc_push_root(ctx, (void**)&_arg_950); mph_types_Type* _arg_951 = right; mph_gc_push_root(ctx, (void**)&_arg_951); mph_bool _ret_952 = mph_types_type_equals(ctx, NULL, _arg_950, _arg_951); mph_gc_pop_roots(ctx, 2); _ret_952; })) {
{
	return ({ mph_types_Type* _arg_953 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_953); mph_types_TypeResult* _ret_954 = mph_types_make_type_result(ctx, NULL, _arg_953); mph_gc_pop_roots(ctx, 1); _ret_954; });
}
	}
	if ((({ mph_types_Type* _obj_955 = left; mph_gc_push_root(ctx, (void**)&_obj_955); mph_int _ret_956 = _obj_955->kind; mph_gc_pop_roots(ctx, 1); _ret_956; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_957 = left; mph_gc_push_root(ctx, (void**)&_arg_957); mph_types_Type* _arg_958 = right; mph_gc_push_root(ctx, (void**)&_arg_958); mph_bool _ret_959 = mph_types_type_assignable_to(ctx, NULL, _arg_957, _arg_958); mph_gc_pop_roots(ctx, 2); _ret_959; })) {
{
	return ({ mph_types_Type* _arg_960 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_960); mph_types_TypeResult* _ret_961 = mph_types_make_type_result(ctx, NULL, _arg_960); mph_gc_pop_roots(ctx, 1); _ret_961; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_962 = right; mph_gc_push_root(ctx, (void**)&_obj_962); mph_int _ret_963 = _obj_962->kind; mph_gc_pop_roots(ctx, 1); _ret_963; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_964 = right; mph_gc_push_root(ctx, (void**)&_arg_964); mph_types_Type* _arg_965 = left; mph_gc_push_root(ctx, (void**)&_arg_965); mph_bool _ret_966 = mph_types_type_assignable_to(ctx, NULL, _arg_964, _arg_965); mph_gc_pop_roots(ctx, 2); _ret_966; })) {
{
	return ({ mph_types_Type* _arg_967 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_967); mph_types_TypeResult* _ret_968 = mph_types_make_type_result(ctx, NULL, _arg_967); mph_gc_pop_roots(ctx, 1); _ret_968; });
}
	}
}
	}
	return ({ MorphString* _arg_969 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_969); mph_types_TypeResult* _ret_970 = mph_types_make_type_error(ctx, NULL, _arg_969); mph_gc_pop_roots(ctx, 1); _ret_970; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!="))) {
{
	if (({ mph_types_Type* _arg_971 = left; mph_gc_push_root(ctx, (void**)&_arg_971); mph_types_Type* _arg_972 = right; mph_gc_push_root(ctx, (void**)&_arg_972); mph_bool _ret_973 = mph_types_type_equals(ctx, NULL, _arg_971, _arg_972); mph_gc_pop_roots(ctx, 2); _ret_973; })) {
{
	return ({ mph_types_Type* _arg_974 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_974); mph_types_TypeResult* _ret_975 = mph_types_make_type_result(ctx, NULL, _arg_974); mph_gc_pop_roots(ctx, 1); _ret_975; });
}
	}
	if ((({ mph_types_Type* _obj_976 = left; mph_gc_push_root(ctx, (void**)&_obj_976); mph_int _ret_977 = _obj_976->kind; mph_gc_pop_roots(ctx, 1); _ret_977; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_978 = left; mph_gc_push_root(ctx, (void**)&_arg_978); mph_types_Type* _arg_979 = right; mph_gc_push_root(ctx, (void**)&_arg_979); mph_bool _ret_980 = mph_types_type_assignable_to(ctx, NULL, _arg_978, _arg_979); mph_gc_pop_roots(ctx, 2); _ret_980; })) {
{
	return ({ mph_types_Type* _arg_981 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_981); mph_types_TypeResult* _ret_982 = mph_types_make_type_result(ctx, NULL, _arg_981); mph_gc_pop_roots(ctx, 1); _ret_982; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_983 = right; mph_gc_push_root(ctx, (void**)&_obj_983); mph_int _ret_984 = _obj_983->kind; mph_gc_pop_roots(ctx, 1); _ret_984; }) == mph_types_KIND_NULL)) {
{
	if (({ mph_types_Type* _arg_985 = right; mph_gc_push_root(ctx, (void**)&_arg_985); mph_types_Type* _arg_986 = left; mph_gc_push_root(ctx, (void**)&_arg_986); mph_bool _ret_987 = mph_types_type_assignable_to(ctx, NULL, _arg_985, _arg_986); mph_gc_pop_roots(ctx, 2); _ret_987; })) {
{
	return ({ mph_types_Type* _arg_988 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_988); mph_types_TypeResult* _ret_989 = mph_types_make_type_result(ctx, NULL, _arg_988); mph_gc_pop_roots(ctx, 1); _ret_989; });
}
	}
}
	}
	return ({ MorphString* _arg_990 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_990); mph_types_TypeResult* _ret_991 = mph_types_make_type_error(ctx, NULL, _arg_990); mph_gc_pop_roots(ctx, 1); _ret_991; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&&"))) {
{
	if ((({ mph_types_Type* _obj_992 = left; mph_gc_push_root(ctx, (void**)&_obj_992); mph_int _ret_993 = _obj_992->kind; mph_gc_pop_roots(ctx, 1); _ret_993; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_994 = right; mph_gc_push_root(ctx, (void**)&_obj_994); mph_int _ret_995 = _obj_994->kind; mph_gc_pop_roots(ctx, 1); _ret_995; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_996 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_996); mph_types_TypeResult* _ret_997 = mph_types_make_type_result(ctx, NULL, _arg_996); mph_gc_pop_roots(ctx, 1); _ret_997; });
}
	}
}
	}
	return ({ MorphString* _arg_998 = mph_string_new(ctx, "&& memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_998); mph_types_TypeResult* _ret_999 = mph_types_make_type_error(ctx, NULL, _arg_998); mph_gc_pop_roots(ctx, 1); _ret_999; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "||"))) {
{
	if ((({ mph_types_Type* _obj_1000 = left; mph_gc_push_root(ctx, (void**)&_obj_1000); mph_int _ret_1001 = _obj_1000->kind; mph_gc_pop_roots(ctx, 1); _ret_1001; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_1002 = right; mph_gc_push_root(ctx, (void**)&_obj_1002); mph_int _ret_1003 = _obj_1002->kind; mph_gc_pop_roots(ctx, 1); _ret_1003; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_1004 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1004); mph_types_TypeResult* _ret_1005 = mph_types_make_type_result(ctx, NULL, _arg_1004); mph_gc_pop_roots(ctx, 1); _ret_1005; });
}
	}
}
	}
	return ({ MorphString* _arg_1006 = mph_string_new(ctx, "|| memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_1006); mph_types_TypeResult* _ret_1007 = mph_types_make_type_error(ctx, NULL, _arg_1006); mph_gc_pop_roots(ctx, 1); _ret_1007; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "dan"))) {
{
	if ((({ mph_types_Type* _obj_1008 = left; mph_gc_push_root(ctx, (void**)&_obj_1008); mph_int _ret_1009 = _obj_1008->kind; mph_gc_pop_roots(ctx, 1); _ret_1009; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_1010 = right; mph_gc_push_root(ctx, (void**)&_obj_1010); mph_int _ret_1011 = _obj_1010->kind; mph_gc_pop_roots(ctx, 1); _ret_1011; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_1012 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1012); mph_types_TypeResult* _ret_1013 = mph_types_make_type_result(ctx, NULL, _arg_1012); mph_gc_pop_roots(ctx, 1); _ret_1013; });
}
	}
}
	}
	return ({ MorphString* _arg_1014 = mph_string_new(ctx, "dan memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_1014); mph_types_TypeResult* _ret_1015 = mph_types_make_type_error(ctx, NULL, _arg_1014); mph_gc_pop_roots(ctx, 1); _ret_1015; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "atau"))) {
{
	if ((({ mph_types_Type* _obj_1016 = left; mph_gc_push_root(ctx, (void**)&_obj_1016); mph_int _ret_1017 = _obj_1016->kind; mph_gc_pop_roots(ctx, 1); _ret_1017; }) == mph_types_KIND_BOOL)) {
{
	if ((({ mph_types_Type* _obj_1018 = right; mph_gc_push_root(ctx, (void**)&_obj_1018); mph_int _ret_1019 = _obj_1018->kind; mph_gc_pop_roots(ctx, 1); _ret_1019; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_1020 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1020); mph_types_TypeResult* _ret_1021 = mph_types_make_type_result(ctx, NULL, _arg_1020); mph_gc_pop_roots(ctx, 1); _ret_1021; });
}
	}
}
	}
	return ({ MorphString* _arg_1022 = mph_string_new(ctx, "atau memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_1022); mph_types_TypeResult* _ret_1023 = mph_types_make_type_error(ctx, NULL, _arg_1022); mph_gc_pop_roots(ctx, 1); _ret_1023; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<"))) {
{
	if ((({ mph_types_Type* _obj_1024 = left; mph_gc_push_root(ctx, (void**)&_obj_1024); mph_int _ret_1025 = _obj_1024->kind; mph_gc_pop_roots(ctx, 1); _ret_1025; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1026 = right; mph_gc_push_root(ctx, (void**)&_obj_1026); mph_int _ret_1027 = _obj_1026->kind; mph_gc_pop_roots(ctx, 1); _ret_1027; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1028 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1028); mph_types_TypeResult* _ret_1029 = mph_types_make_type_result(ctx, NULL, _arg_1028); mph_gc_pop_roots(ctx, 1); _ret_1029; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_1030 = left; mph_gc_push_root(ctx, (void**)&_obj_1030); mph_int _ret_1031 = _obj_1030->kind; mph_gc_pop_roots(ctx, 1); _ret_1031; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_1032 = right; mph_gc_push_root(ctx, (void**)&_obj_1032); mph_int _ret_1033 = _obj_1032->kind; mph_gc_pop_roots(ctx, 1); _ret_1033; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_1034 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1034); mph_types_TypeResult* _ret_1035 = mph_types_make_type_result(ctx, NULL, _arg_1034); mph_gc_pop_roots(ctx, 1); _ret_1035; });
}
	}
}
	}
	return ({ MorphString* _arg_1036 = mph_string_new(ctx, "< memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_1036); mph_types_TypeResult* _ret_1037 = mph_types_make_type_error(ctx, NULL, _arg_1036); mph_gc_pop_roots(ctx, 1); _ret_1037; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">"))) {
{
	if ((({ mph_types_Type* _obj_1038 = left; mph_gc_push_root(ctx, (void**)&_obj_1038); mph_int _ret_1039 = _obj_1038->kind; mph_gc_pop_roots(ctx, 1); _ret_1039; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1040 = right; mph_gc_push_root(ctx, (void**)&_obj_1040); mph_int _ret_1041 = _obj_1040->kind; mph_gc_pop_roots(ctx, 1); _ret_1041; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1042 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1042); mph_types_TypeResult* _ret_1043 = mph_types_make_type_result(ctx, NULL, _arg_1042); mph_gc_pop_roots(ctx, 1); _ret_1043; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_1044 = left; mph_gc_push_root(ctx, (void**)&_obj_1044); mph_int _ret_1045 = _obj_1044->kind; mph_gc_pop_roots(ctx, 1); _ret_1045; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_1046 = right; mph_gc_push_root(ctx, (void**)&_obj_1046); mph_int _ret_1047 = _obj_1046->kind; mph_gc_pop_roots(ctx, 1); _ret_1047; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_1048 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1048); mph_types_TypeResult* _ret_1049 = mph_types_make_type_result(ctx, NULL, _arg_1048); mph_gc_pop_roots(ctx, 1); _ret_1049; });
}
	}
}
	}
	return ({ MorphString* _arg_1050 = mph_string_new(ctx, "> memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_1050); mph_types_TypeResult* _ret_1051 = mph_types_make_type_error(ctx, NULL, _arg_1050); mph_gc_pop_roots(ctx, 1); _ret_1051; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<="))) {
{
	if ((({ mph_types_Type* _obj_1052 = left; mph_gc_push_root(ctx, (void**)&_obj_1052); mph_int _ret_1053 = _obj_1052->kind; mph_gc_pop_roots(ctx, 1); _ret_1053; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1054 = right; mph_gc_push_root(ctx, (void**)&_obj_1054); mph_int _ret_1055 = _obj_1054->kind; mph_gc_pop_roots(ctx, 1); _ret_1055; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1056 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1056); mph_types_TypeResult* _ret_1057 = mph_types_make_type_result(ctx, NULL, _arg_1056); mph_gc_pop_roots(ctx, 1); _ret_1057; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_1058 = left; mph_gc_push_root(ctx, (void**)&_obj_1058); mph_int _ret_1059 = _obj_1058->kind; mph_gc_pop_roots(ctx, 1); _ret_1059; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_1060 = right; mph_gc_push_root(ctx, (void**)&_obj_1060); mph_int _ret_1061 = _obj_1060->kind; mph_gc_pop_roots(ctx, 1); _ret_1061; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_1062 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1062); mph_types_TypeResult* _ret_1063 = mph_types_make_type_result(ctx, NULL, _arg_1062); mph_gc_pop_roots(ctx, 1); _ret_1063; });
}
	}
}
	}
	return ({ MorphString* _arg_1064 = mph_string_new(ctx, "<= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_1064); mph_types_TypeResult* _ret_1065 = mph_types_make_type_error(ctx, NULL, _arg_1064); mph_gc_pop_roots(ctx, 1); _ret_1065; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">="))) {
{
	if ((({ mph_types_Type* _obj_1066 = left; mph_gc_push_root(ctx, (void**)&_obj_1066); mph_int _ret_1067 = _obj_1066->kind; mph_gc_pop_roots(ctx, 1); _ret_1067; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1068 = right; mph_gc_push_root(ctx, (void**)&_obj_1068); mph_int _ret_1069 = _obj_1068->kind; mph_gc_pop_roots(ctx, 1); _ret_1069; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1070 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1070); mph_types_TypeResult* _ret_1071 = mph_types_make_type_result(ctx, NULL, _arg_1070); mph_gc_pop_roots(ctx, 1); _ret_1071; });
}
	}
}
	}
	if ((({ mph_types_Type* _obj_1072 = left; mph_gc_push_root(ctx, (void**)&_obj_1072); mph_int _ret_1073 = _obj_1072->kind; mph_gc_pop_roots(ctx, 1); _ret_1073; }) == mph_types_KIND_FLOAT)) {
{
	if ((({ mph_types_Type* _obj_1074 = right; mph_gc_push_root(ctx, (void**)&_obj_1074); mph_int _ret_1075 = _obj_1074->kind; mph_gc_pop_roots(ctx, 1); _ret_1075; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_1076 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1076); mph_types_TypeResult* _ret_1077 = mph_types_make_type_result(ctx, NULL, _arg_1076); mph_gc_pop_roots(ctx, 1); _ret_1077; });
}
	}
}
	}
	return ({ MorphString* _arg_1078 = mph_string_new(ctx, ">= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_1078); mph_types_TypeResult* _ret_1079 = mph_types_make_type_error(ctx, NULL, _arg_1078); mph_gc_pop_roots(ctx, 1); _ret_1079; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&"))) {
{
	if ((({ mph_types_Type* _obj_1080 = left; mph_gc_push_root(ctx, (void**)&_obj_1080); mph_int _ret_1081 = _obj_1080->kind; mph_gc_pop_roots(ctx, 1); _ret_1081; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1082 = right; mph_gc_push_root(ctx, (void**)&_obj_1082); mph_int _ret_1083 = _obj_1082->kind; mph_gc_pop_roots(ctx, 1); _ret_1083; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1084 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1084); mph_types_TypeResult* _ret_1085 = mph_types_make_type_result(ctx, NULL, _arg_1084); mph_gc_pop_roots(ctx, 1); _ret_1085; });
}
	}
}
	}
	return ({ MorphString* _arg_1086 = mph_string_new(ctx, "& memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_1086); mph_types_TypeResult* _ret_1087 = mph_types_make_type_error(ctx, NULL, _arg_1086); mph_gc_pop_roots(ctx, 1); _ret_1087; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "|"))) {
{
	if ((({ mph_types_Type* _obj_1088 = left; mph_gc_push_root(ctx, (void**)&_obj_1088); mph_int _ret_1089 = _obj_1088->kind; mph_gc_pop_roots(ctx, 1); _ret_1089; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1090 = right; mph_gc_push_root(ctx, (void**)&_obj_1090); mph_int _ret_1091 = _obj_1090->kind; mph_gc_pop_roots(ctx, 1); _ret_1091; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1092 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1092); mph_types_TypeResult* _ret_1093 = mph_types_make_type_result(ctx, NULL, _arg_1092); mph_gc_pop_roots(ctx, 1); _ret_1093; });
}
	}
}
	}
	return ({ MorphString* _arg_1094 = mph_string_new(ctx, "| memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_1094); mph_types_TypeResult* _ret_1095 = mph_types_make_type_error(ctx, NULL, _arg_1094); mph_gc_pop_roots(ctx, 1); _ret_1095; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "^"))) {
{
	if ((({ mph_types_Type* _obj_1096 = left; mph_gc_push_root(ctx, (void**)&_obj_1096); mph_int _ret_1097 = _obj_1096->kind; mph_gc_pop_roots(ctx, 1); _ret_1097; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1098 = right; mph_gc_push_root(ctx, (void**)&_obj_1098); mph_int _ret_1099 = _obj_1098->kind; mph_gc_pop_roots(ctx, 1); _ret_1099; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1100 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1100); mph_types_TypeResult* _ret_1101 = mph_types_make_type_result(ctx, NULL, _arg_1100); mph_gc_pop_roots(ctx, 1); _ret_1101; });
}
	}
}
	}
	return ({ MorphString* _arg_1102 = mph_string_new(ctx, "^ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_1102); mph_types_TypeResult* _ret_1103 = mph_types_make_type_error(ctx, NULL, _arg_1102); mph_gc_pop_roots(ctx, 1); _ret_1103; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<<"))) {
{
	if ((({ mph_types_Type* _obj_1104 = left; mph_gc_push_root(ctx, (void**)&_obj_1104); mph_int _ret_1105 = _obj_1104->kind; mph_gc_pop_roots(ctx, 1); _ret_1105; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1106 = right; mph_gc_push_root(ctx, (void**)&_obj_1106); mph_int _ret_1107 = _obj_1106->kind; mph_gc_pop_roots(ctx, 1); _ret_1107; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1108 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1108); mph_types_TypeResult* _ret_1109 = mph_types_make_type_result(ctx, NULL, _arg_1108); mph_gc_pop_roots(ctx, 1); _ret_1109; });
}
	}
}
	}
	return ({ MorphString* _arg_1110 = mph_string_new(ctx, "<< memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_1110); mph_types_TypeResult* _ret_1111 = mph_types_make_type_error(ctx, NULL, _arg_1110); mph_gc_pop_roots(ctx, 1); _ret_1111; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">>"))) {
{
	if ((({ mph_types_Type* _obj_1112 = left; mph_gc_push_root(ctx, (void**)&_obj_1112); mph_int _ret_1113 = _obj_1112->kind; mph_gc_pop_roots(ctx, 1); _ret_1113; }) == mph_types_KIND_INT)) {
{
	if ((({ mph_types_Type* _obj_1114 = right; mph_gc_push_root(ctx, (void**)&_obj_1114); mph_int _ret_1115 = _obj_1114->kind; mph_gc_pop_roots(ctx, 1); _ret_1115; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1116 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1116); mph_types_TypeResult* _ret_1117 = mph_types_make_type_result(ctx, NULL, _arg_1116); mph_gc_pop_roots(ctx, 1); _ret_1117; });
}
	}
}
	}
	return ({ MorphString* _arg_1118 = mph_string_new(ctx, ">> memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_1118); mph_types_TypeResult* _ret_1119 = mph_types_make_type_error(ctx, NULL, _arg_1118); mph_gc_pop_roots(ctx, 1); _ret_1119; });
}
	}
	return ({ MorphString* _arg_1120 = mph_string_new(ctx, "operator tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_1120); mph_types_TypeResult* _ret_1121 = mph_types_make_type_error(ctx, NULL, _arg_1120); mph_gc_pop_roots(ctx, 1); _ret_1121; });
	mph_gc_pop_roots(ctx, 3);
}

mph_types_TypeResult* mph_types_type_prefix_op(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	if ((({ mph_types_Type* _obj_1122 = t; mph_gc_push_root(ctx, (void**)&_obj_1122); mph_int _ret_1123 = _obj_1122->kind; mph_gc_pop_roots(ctx, 1); _ret_1123; }) == mph_types_KIND_UNKNOWN)) {
{
	return ({ mph_types_Type* _arg_1124 = mph_types_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1124); mph_types_TypeResult* _ret_1125 = mph_types_make_type_result(ctx, NULL, _arg_1124); mph_gc_pop_roots(ctx, 1); _ret_1125; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!"))) {
{
	if ((({ mph_types_Type* _obj_1126 = t; mph_gc_push_root(ctx, (void**)&_obj_1126); mph_int _ret_1127 = _obj_1126->kind; mph_gc_pop_roots(ctx, 1); _ret_1127; }) == mph_types_KIND_BOOL)) {
{
	return ({ mph_types_Type* _arg_1128 = mph_types_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1128); mph_types_TypeResult* _ret_1129 = mph_types_make_type_result(ctx, NULL, _arg_1128); mph_gc_pop_roots(ctx, 1); _ret_1129; });
}
	}
	return ({ MorphString* _arg_1130 = mph_string_new(ctx, "! memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_1130); mph_types_TypeResult* _ret_1131 = mph_types_make_type_error(ctx, NULL, _arg_1130); mph_gc_pop_roots(ctx, 1); _ret_1131; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_types_Type* _obj_1132 = t; mph_gc_push_root(ctx, (void**)&_obj_1132); mph_int _ret_1133 = _obj_1132->kind; mph_gc_pop_roots(ctx, 1); _ret_1133; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1134 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1134); mph_types_TypeResult* _ret_1135 = mph_types_make_type_result(ctx, NULL, _arg_1134); mph_gc_pop_roots(ctx, 1); _ret_1135; });
}
	}
	if ((({ mph_types_Type* _obj_1136 = t; mph_gc_push_root(ctx, (void**)&_obj_1136); mph_int _ret_1137 = _obj_1136->kind; mph_gc_pop_roots(ctx, 1); _ret_1137; }) == mph_types_KIND_FLOAT)) {
{
	return ({ mph_types_Type* _arg_1138 = mph_types_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1138); mph_types_TypeResult* _ret_1139 = mph_types_make_type_result(ctx, NULL, _arg_1138); mph_gc_pop_roots(ctx, 1); _ret_1139; });
}
	}
	return ({ MorphString* _arg_1140 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_1140); mph_types_TypeResult* _ret_1141 = mph_types_make_type_error(ctx, NULL, _arg_1140); mph_gc_pop_roots(ctx, 1); _ret_1141; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "~"))) {
{
	if ((({ mph_types_Type* _obj_1142 = t; mph_gc_push_root(ctx, (void**)&_obj_1142); mph_int _ret_1143 = _obj_1142->kind; mph_gc_pop_roots(ctx, 1); _ret_1143; }) == mph_types_KIND_INT)) {
{
	return ({ mph_types_Type* _arg_1144 = mph_types_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_1144); mph_types_TypeResult* _ret_1145 = mph_types_make_type_result(ctx, NULL, _arg_1144); mph_gc_pop_roots(ctx, 1); _ret_1145; });
}
	}
	return ({ MorphString* _arg_1146 = mph_string_new(ctx, "~ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_1146); mph_types_TypeResult* _ret_1147 = mph_types_make_type_error(ctx, NULL, _arg_1146); mph_gc_pop_roots(ctx, 1); _ret_1147; });
}
	}
	return ({ MorphString* _arg_1148 = mph_string_new(ctx, "prefix tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_1148); mph_types_TypeResult* _ret_1149 = mph_types_make_type_error(ctx, NULL, _arg_1148); mph_gc_pop_roots(ctx, 1); _ret_1149; });
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
	return ({ MorphString* _arg_1150 = n; mph_gc_push_root(ctx, (void**)&_arg_1150); mph_types_Type* _ret_1151 = mph_types_struct_type(ctx, NULL, _arg_1150); mph_gc_pop_roots(ctx, 1); _ret_1151; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_Type* mph_types_InterfaceType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_1152 = n; mph_gc_push_root(ctx, (void**)&_arg_1152); mph_types_Type* _ret_1153 = mph_types_interface_type(ctx, NULL, _arg_1152); mph_gc_pop_roots(ctx, 1); _ret_1153; });
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
	return ({ MorphString* _arg_1154 = n; mph_gc_push_root(ctx, (void**)&_arg_1154); mph_types_Type* _ret_1155 = mph_types_module_type(ctx, NULL, _arg_1154); mph_gc_pop_roots(ctx, 1); _ret_1155; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_types_TypeEquals(MorphContext* ctx, void* _env_void, mph_types_Type* t1, mph_types_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return ({ mph_types_Type* _arg_1156 = t1; mph_gc_push_root(ctx, (void**)&_arg_1156); mph_types_Type* _arg_1157 = t2; mph_gc_push_root(ctx, (void**)&_arg_1157); mph_bool _ret_1158 = mph_types_type_equals(ctx, NULL, _arg_1156, _arg_1157); mph_gc_pop_roots(ctx, 2); _ret_1158; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_TypeAssignableTo(MorphContext* ctx, void* _env_void, mph_types_Type* source, mph_types_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	return ({ mph_types_Type* _arg_1159 = source; mph_gc_push_root(ctx, (void**)&_arg_1159); mph_types_Type* _arg_1160 = target; mph_gc_push_root(ctx, (void**)&_arg_1160); mph_bool _ret_1161 = mph_types_type_assignable_to(ctx, NULL, _arg_1159, _arg_1160); mph_gc_pop_roots(ctx, 2); _ret_1161; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_types_TypeIsComparable(MorphContext* ctx, void* _env_void, mph_types_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_types_Type* _arg_1162 = t; mph_gc_push_root(ctx, (void**)&_arg_1162); mph_bool _ret_1163 = mph_types_type_is_comparable(ctx, NULL, _arg_1162); mph_gc_pop_roots(ctx, 1); _ret_1163; });
	mph_gc_pop_roots(ctx, 1);
}

mph_types_TypeResult* mph_types_TypeBinaryOp(MorphContext* ctx, void* _env_void, mph_types_Type* left, MorphString* op, mph_types_Type* right) {
	mph_gc_push_root(ctx, (void**)&left);
	mph_gc_push_root(ctx, (void**)&op);
	mph_gc_push_root(ctx, (void**)&right);
	return ({ mph_types_Type* _arg_1164 = left; mph_gc_push_root(ctx, (void**)&_arg_1164); MorphString* _arg_1165 = op; mph_gc_push_root(ctx, (void**)&_arg_1165); mph_types_Type* _arg_1166 = right; mph_gc_push_root(ctx, (void**)&_arg_1166); mph_types_TypeResult* _ret_1167 = mph_types_type_binary_op(ctx, NULL, _arg_1164, _arg_1165, _arg_1166); mph_gc_pop_roots(ctx, 3); _ret_1167; });
	mph_gc_pop_roots(ctx, 3);
}

mph_types_TypeResult* mph_types_TypePrefixOp(MorphContext* ctx, void* _env_void, mph_types_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	return ({ mph_types_Type* _arg_1168 = t; mph_gc_push_root(ctx, (void**)&_arg_1168); MorphString* _arg_1169 = op; mph_gc_push_root(ctx, (void**)&_arg_1169); mph_types_TypeResult* _ret_1170 = mph_types_type_prefix_op(ctx, NULL, _arg_1168, _arg_1169); mph_gc_pop_roots(ctx, 2); _ret_1170; });
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
	if ((({ mph_types_Type* _obj_1171 = t_int; mph_gc_push_root(ctx, (void**)&_obj_1171); mph_int _ret_1172 = _obj_1171->kind; mph_gc_pop_roots(ctx, 1); _ret_1172; }) == mph_types_KIND_INT)) {
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
	if (({ mph_types_Type* _arg_1173 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1173); mph_types_Type* _arg_1174 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1174); mph_bool _ret_1175 = mph_types_type_equals(ctx, NULL, _arg_1173, _arg_1174); mph_gc_pop_roots(ctx, 2); _ret_1175; })) {
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
	if (({ mph_types_Type* _arg_1176 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1176); mph_types_Type* _arg_1177 = t_float; mph_gc_push_root(ctx, (void**)&_arg_1177); mph_bool _ret_1178 = mph_types_type_equals(ctx, NULL, _arg_1176, _arg_1177); mph_gc_pop_roots(ctx, 2); _ret_1178; })) {
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
	if (({ mph_types_Type* _arg_1179 = t_null; mph_gc_push_root(ctx, (void**)&_arg_1179); mph_types_Type* _arg_1180 = t_array; mph_gc_push_root(ctx, (void**)&_arg_1180); mph_bool _ret_1181 = mph_types_type_assignable_to(ctx, NULL, _arg_1179, _arg_1180); mph_gc_pop_roots(ctx, 2); _ret_1181; })) {
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
	if (({ mph_types_Type* _arg_1182 = t_null; mph_gc_push_root(ctx, (void**)&_arg_1182); mph_types_Type* _arg_1183 = t_map; mph_gc_push_root(ctx, (void**)&_arg_1183); mph_bool _ret_1184 = mph_types_type_assignable_to(ctx, NULL, _arg_1182, _arg_1183); mph_gc_pop_roots(ctx, 2); _ret_1184; })) {
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
	if (({ mph_types_Type* _arg_1185 = t_null; mph_gc_push_root(ctx, (void**)&_arg_1185); mph_types_Type* _arg_1186 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1186); mph_bool _ret_1187 = mph_types_type_assignable_to(ctx, NULL, _arg_1185, _arg_1186); mph_gc_pop_roots(ctx, 2); _ret_1187; })) {
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
	if (({ mph_types_Type* _arg_1188 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1188); mph_bool _ret_1189 = mph_types_type_is_comparable(ctx, NULL, _arg_1188); mph_gc_pop_roots(ctx, 1); _ret_1189; })) {
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
	if (({ mph_types_Type* _arg_1190 = t_void; mph_gc_push_root(ctx, (void**)&_arg_1190); mph_bool _ret_1191 = mph_types_type_is_comparable(ctx, NULL, _arg_1190); mph_gc_pop_roots(ctx, 1); _ret_1191; })) {
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
	mph_types_TypeResult* r1 = ({ mph_types_Type* _arg_1192 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1192); MorphString* _arg_1193 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_1193); mph_types_Type* _arg_1194 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1194); mph_types_TypeResult* _ret_1195 = mph_types_type_binary_op(ctx, NULL, _arg_1192, _arg_1193, _arg_1194); mph_gc_pop_roots(ctx, 3); _ret_1195; });
	mph_gc_push_root(ctx, (void**)&r1);
	if (({ mph_types_TypeResult* _obj_1196 = r1; mph_gc_push_root(ctx, (void**)&_obj_1196); mph_bool _ret_1197 = _obj_1196->has_error; mph_gc_pop_roots(ctx, 1); _ret_1197; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1200 = ({ mph_types_TypeResult* _obj_1198 = r1; mph_gc_push_root(ctx, (void**)&_obj_1198); mph_types_Type* _ret_1199 = _obj_1198->result; mph_gc_pop_roots(ctx, 1); _ret_1199; }); mph_gc_push_root(ctx, (void**)&_obj_1200); mph_int _ret_1201 = _obj_1200->kind; mph_gc_pop_roots(ctx, 1); _ret_1201; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r2 = ({ mph_types_Type* _arg_1202 = t_string; mph_gc_push_root(ctx, (void**)&_arg_1202); MorphString* _arg_1203 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_1203); mph_types_Type* _arg_1204 = t_string; mph_gc_push_root(ctx, (void**)&_arg_1204); mph_types_TypeResult* _ret_1205 = mph_types_type_binary_op(ctx, NULL, _arg_1202, _arg_1203, _arg_1204); mph_gc_pop_roots(ctx, 3); _ret_1205; });
	mph_gc_push_root(ctx, (void**)&r2);
	if (({ mph_types_TypeResult* _obj_1206 = r2; mph_gc_push_root(ctx, (void**)&_obj_1206); mph_bool _ret_1207 = _obj_1206->has_error; mph_gc_pop_roots(ctx, 1); _ret_1207; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string + string FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1210 = ({ mph_types_TypeResult* _obj_1208 = r2; mph_gc_push_root(ctx, (void**)&_obj_1208); mph_types_Type* _ret_1209 = _obj_1208->result; mph_gc_pop_roots(ctx, 1); _ret_1209; }); mph_gc_push_root(ctx, (void**)&_obj_1210); mph_int _ret_1211 = _obj_1210->kind; mph_gc_pop_roots(ctx, 1); _ret_1211; }) == mph_types_KIND_STRING)) {
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
	mph_types_TypeResult* r3 = ({ mph_types_Type* _arg_1212 = t_float; mph_gc_push_root(ctx, (void**)&_arg_1212); MorphString* _arg_1213 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_arg_1213); mph_types_Type* _arg_1214 = t_float; mph_gc_push_root(ctx, (void**)&_arg_1214); mph_types_TypeResult* _ret_1215 = mph_types_type_binary_op(ctx, NULL, _arg_1212, _arg_1213, _arg_1214); mph_gc_pop_roots(ctx, 3); _ret_1215; });
	mph_gc_push_root(ctx, (void**)&r3);
	if (({ mph_types_TypeResult* _obj_1216 = r3; mph_gc_push_root(ctx, (void**)&_obj_1216); mph_bool _ret_1217 = _obj_1216->has_error; mph_gc_pop_roots(ctx, 1); _ret_1217; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â float * float FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1220 = ({ mph_types_TypeResult* _obj_1218 = r3; mph_gc_push_root(ctx, (void**)&_obj_1218); mph_types_Type* _ret_1219 = _obj_1218->result; mph_gc_pop_roots(ctx, 1); _ret_1219; }); mph_gc_push_root(ctx, (void**)&_obj_1220); mph_int _ret_1221 = _obj_1220->kind; mph_gc_pop_roots(ctx, 1); _ret_1221; }) == mph_types_KIND_FLOAT)) {
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
	mph_types_TypeResult* r4 = ({ mph_types_Type* _arg_1222 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1222); MorphString* _arg_1223 = mph_string_new(ctx, "<"); mph_gc_push_root(ctx, (void**)&_arg_1223); mph_types_Type* _arg_1224 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1224); mph_types_TypeResult* _ret_1225 = mph_types_type_binary_op(ctx, NULL, _arg_1222, _arg_1223, _arg_1224); mph_gc_pop_roots(ctx, 3); _ret_1225; });
	mph_gc_push_root(ctx, (void**)&r4);
	if (({ mph_types_TypeResult* _obj_1226 = r4; mph_gc_push_root(ctx, (void**)&_obj_1226); mph_bool _ret_1227 = _obj_1226->has_error; mph_gc_pop_roots(ctx, 1); _ret_1227; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int < int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1230 = ({ mph_types_TypeResult* _obj_1228 = r4; mph_gc_push_root(ctx, (void**)&_obj_1228); mph_types_Type* _ret_1229 = _obj_1228->result; mph_gc_pop_roots(ctx, 1); _ret_1229; }); mph_gc_push_root(ctx, (void**)&_obj_1230); mph_int _ret_1231 = _obj_1230->kind; mph_gc_pop_roots(ctx, 1); _ret_1231; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r5 = ({ mph_types_Type* _arg_1232 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1232); MorphString* _arg_1233 = mph_string_new(ctx, "=="); mph_gc_push_root(ctx, (void**)&_arg_1233); mph_types_Type* _arg_1234 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1234); mph_types_TypeResult* _ret_1235 = mph_types_type_binary_op(ctx, NULL, _arg_1232, _arg_1233, _arg_1234); mph_gc_pop_roots(ctx, 3); _ret_1235; });
	mph_gc_push_root(ctx, (void**)&r5);
	if (({ mph_types_TypeResult* _obj_1236 = r5; mph_gc_push_root(ctx, (void**)&_obj_1236); mph_bool _ret_1237 = _obj_1236->has_error; mph_gc_pop_roots(ctx, 1); _ret_1237; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1240 = ({ mph_types_TypeResult* _obj_1238 = r5; mph_gc_push_root(ctx, (void**)&_obj_1238); mph_types_Type* _ret_1239 = _obj_1238->result; mph_gc_pop_roots(ctx, 1); _ret_1239; }); mph_gc_push_root(ctx, (void**)&_obj_1240); mph_int _ret_1241 = _obj_1240->kind; mph_gc_pop_roots(ctx, 1); _ret_1241; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r6 = ({ mph_types_Type* _arg_1242 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_1242); MorphString* _arg_1243 = mph_string_new(ctx, "dan"); mph_gc_push_root(ctx, (void**)&_arg_1243); mph_types_Type* _arg_1244 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_1244); mph_types_TypeResult* _ret_1245 = mph_types_type_binary_op(ctx, NULL, _arg_1242, _arg_1243, _arg_1244); mph_gc_pop_roots(ctx, 3); _ret_1245; });
	mph_gc_push_root(ctx, (void**)&r6);
	if (({ mph_types_TypeResult* _obj_1246 = r6; mph_gc_push_root(ctx, (void**)&_obj_1246); mph_bool _ret_1247 = _obj_1246->has_error; mph_gc_pop_roots(ctx, 1); _ret_1247; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool dan bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1250 = ({ mph_types_TypeResult* _obj_1248 = r6; mph_gc_push_root(ctx, (void**)&_obj_1248); mph_types_Type* _ret_1249 = _obj_1248->result; mph_gc_pop_roots(ctx, 1); _ret_1249; }); mph_gc_push_root(ctx, (void**)&_obj_1250); mph_int _ret_1251 = _obj_1250->kind; mph_gc_pop_roots(ctx, 1); _ret_1251; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r7 = ({ mph_types_Type* _arg_1252 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_1252); MorphString* _arg_1253 = mph_string_new(ctx, "||"); mph_gc_push_root(ctx, (void**)&_arg_1253); mph_types_Type* _arg_1254 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_1254); mph_types_TypeResult* _ret_1255 = mph_types_type_binary_op(ctx, NULL, _arg_1252, _arg_1253, _arg_1254); mph_gc_pop_roots(ctx, 3); _ret_1255; });
	mph_gc_push_root(ctx, (void**)&r7);
	if (({ mph_types_TypeResult* _obj_1256 = r7; mph_gc_push_root(ctx, (void**)&_obj_1256); mph_bool _ret_1257 = _obj_1256->has_error; mph_gc_pop_roots(ctx, 1); _ret_1257; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool || bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1260 = ({ mph_types_TypeResult* _obj_1258 = r7; mph_gc_push_root(ctx, (void**)&_obj_1258); mph_types_Type* _ret_1259 = _obj_1258->result; mph_gc_pop_roots(ctx, 1); _ret_1259; }); mph_gc_push_root(ctx, (void**)&_obj_1260); mph_int _ret_1261 = _obj_1260->kind; mph_gc_pop_roots(ctx, 1); _ret_1261; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r8 = ({ mph_types_Type* _arg_1262 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1262); MorphString* _arg_1263 = mph_string_new(ctx, "&"); mph_gc_push_root(ctx, (void**)&_arg_1263); mph_types_Type* _arg_1264 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1264); mph_types_TypeResult* _ret_1265 = mph_types_type_binary_op(ctx, NULL, _arg_1262, _arg_1263, _arg_1264); mph_gc_pop_roots(ctx, 3); _ret_1265; });
	mph_gc_push_root(ctx, (void**)&r8);
	if (({ mph_types_TypeResult* _obj_1266 = r8; mph_gc_push_root(ctx, (void**)&_obj_1266); mph_bool _ret_1267 = _obj_1266->has_error; mph_gc_pop_roots(ctx, 1); _ret_1267; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int & int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1270 = ({ mph_types_TypeResult* _obj_1268 = r8; mph_gc_push_root(ctx, (void**)&_obj_1268); mph_types_Type* _ret_1269 = _obj_1268->result; mph_gc_pop_roots(ctx, 1); _ret_1269; }); mph_gc_push_root(ctx, (void**)&_obj_1270); mph_int _ret_1271 = _obj_1270->kind; mph_gc_pop_roots(ctx, 1); _ret_1271; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r9 = ({ mph_types_Type* _arg_1272 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1272); MorphString* _arg_1273 = mph_string_new(ctx, "<<"); mph_gc_push_root(ctx, (void**)&_arg_1273); mph_types_Type* _arg_1274 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1274); mph_types_TypeResult* _ret_1275 = mph_types_type_binary_op(ctx, NULL, _arg_1272, _arg_1273, _arg_1274); mph_gc_pop_roots(ctx, 3); _ret_1275; });
	mph_gc_push_root(ctx, (void**)&r9);
	if (({ mph_types_TypeResult* _obj_1276 = r9; mph_gc_push_root(ctx, (void**)&_obj_1276); mph_bool _ret_1277 = _obj_1276->has_error; mph_gc_pop_roots(ctx, 1); _ret_1277; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int << int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1280 = ({ mph_types_TypeResult* _obj_1278 = r9; mph_gc_push_root(ctx, (void**)&_obj_1278); mph_types_Type* _ret_1279 = _obj_1278->result; mph_gc_pop_roots(ctx, 1); _ret_1279; }); mph_gc_push_root(ctx, (void**)&_obj_1280); mph_int _ret_1281 = _obj_1280->kind; mph_gc_pop_roots(ctx, 1); _ret_1281; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r10 = ({ mph_types_Type* _arg_1282 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1282); MorphString* _arg_1283 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_1283); mph_types_Type* _arg_1284 = t_string; mph_gc_push_root(ctx, (void**)&_arg_1284); mph_types_TypeResult* _ret_1285 = mph_types_type_binary_op(ctx, NULL, _arg_1282, _arg_1283, _arg_1284); mph_gc_pop_roots(ctx, 3); _ret_1285; });
	mph_gc_push_root(ctx, (void**)&r10);
	if (({ mph_types_TypeResult* _obj_1286 = r10; mph_gc_push_root(ctx, (void**)&_obj_1286); mph_bool _ret_1287 = _obj_1286->has_error; mph_gc_pop_roots(ctx, 1); _ret_1287; })) {
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
	mph_types_TypeResult* r11 = ({ mph_types_Type* _arg_1288 = t_string; mph_gc_push_root(ctx, (void**)&_arg_1288); MorphString* _arg_1289 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_1289); mph_types_Type* _arg_1290 = t_string; mph_gc_push_root(ctx, (void**)&_arg_1290); mph_types_TypeResult* _ret_1291 = mph_types_type_binary_op(ctx, NULL, _arg_1288, _arg_1289, _arg_1290); mph_gc_pop_roots(ctx, 3); _ret_1291; });
	mph_gc_push_root(ctx, (void**)&r11);
	if (({ mph_types_TypeResult* _obj_1292 = r11; mph_gc_push_root(ctx, (void**)&_obj_1292); mph_bool _ret_1293 = _obj_1292->has_error; mph_gc_pop_roots(ctx, 1); _ret_1293; })) {
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
	mph_types_TypeResult* r12 = ({ mph_types_Type* _arg_1294 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_1294); MorphString* _arg_1295 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_1295); mph_types_TypeResult* _ret_1296 = mph_types_type_prefix_op(ctx, NULL, _arg_1294, _arg_1295); mph_gc_pop_roots(ctx, 2); _ret_1296; });
	mph_gc_push_root(ctx, (void**)&r12);
	if (({ mph_types_TypeResult* _obj_1297 = r12; mph_gc_push_root(ctx, (void**)&_obj_1297); mph_bool _ret_1298 = _obj_1297->has_error; mph_gc_pop_roots(ctx, 1); _ret_1298; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1301 = ({ mph_types_TypeResult* _obj_1299 = r12; mph_gc_push_root(ctx, (void**)&_obj_1299); mph_types_Type* _ret_1300 = _obj_1299->result; mph_gc_pop_roots(ctx, 1); _ret_1300; }); mph_gc_push_root(ctx, (void**)&_obj_1301); mph_int _ret_1302 = _obj_1301->kind; mph_gc_pop_roots(ctx, 1); _ret_1302; }) == mph_types_KIND_BOOL)) {
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
	mph_types_TypeResult* r13 = ({ mph_types_Type* _arg_1303 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1303); MorphString* _arg_1304 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_1304); mph_types_TypeResult* _ret_1305 = mph_types_type_prefix_op(ctx, NULL, _arg_1303, _arg_1304); mph_gc_pop_roots(ctx, 2); _ret_1305; });
	mph_gc_push_root(ctx, (void**)&r13);
	if (({ mph_types_TypeResult* _obj_1306 = r13; mph_gc_push_root(ctx, (void**)&_obj_1306); mph_bool _ret_1307 = _obj_1306->has_error; mph_gc_pop_roots(ctx, 1); _ret_1307; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â -int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1310 = ({ mph_types_TypeResult* _obj_1308 = r13; mph_gc_push_root(ctx, (void**)&_obj_1308); mph_types_Type* _ret_1309 = _obj_1308->result; mph_gc_pop_roots(ctx, 1); _ret_1309; }); mph_gc_push_root(ctx, (void**)&_obj_1310); mph_int _ret_1311 = _obj_1310->kind; mph_gc_pop_roots(ctx, 1); _ret_1311; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r14 = ({ mph_types_Type* _arg_1312 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1312); MorphString* _arg_1313 = mph_string_new(ctx, "~"); mph_gc_push_root(ctx, (void**)&_arg_1313); mph_types_TypeResult* _ret_1314 = mph_types_type_prefix_op(ctx, NULL, _arg_1312, _arg_1313); mph_gc_pop_roots(ctx, 2); _ret_1314; });
	mph_gc_push_root(ctx, (void**)&r14);
	if (({ mph_types_TypeResult* _obj_1315 = r14; mph_gc_push_root(ctx, (void**)&_obj_1315); mph_bool _ret_1316 = _obj_1315->has_error; mph_gc_pop_roots(ctx, 1); _ret_1316; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â ~int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_types_Type* _obj_1319 = ({ mph_types_TypeResult* _obj_1317 = r14; mph_gc_push_root(ctx, (void**)&_obj_1317); mph_types_Type* _ret_1318 = _obj_1317->result; mph_gc_pop_roots(ctx, 1); _ret_1318; }); mph_gc_push_root(ctx, (void**)&_obj_1319); mph_int _ret_1320 = _obj_1319->kind; mph_gc_pop_roots(ctx, 1); _ret_1320; }) == mph_types_KIND_INT)) {
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
	mph_types_TypeResult* r15 = ({ mph_types_Type* _arg_1321 = t_string; mph_gc_push_root(ctx, (void**)&_arg_1321); MorphString* _arg_1322 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_1322); mph_types_TypeResult* _ret_1323 = mph_types_type_prefix_op(ctx, NULL, _arg_1321, _arg_1322); mph_gc_pop_roots(ctx, 2); _ret_1323; });
	mph_gc_push_root(ctx, (void**)&r15);
	if (({ mph_types_TypeResult* _obj_1324 = r15; mph_gc_push_root(ctx, (void**)&_obj_1324); mph_bool _ret_1325 = _obj_1324->has_error; mph_gc_pop_roots(ctx, 1); _ret_1325; })) {
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

void mph_test_pass(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_total_tests = (mph_total_tests + 1);
	mph_passed_tests = (mph_passed_tests + 1);
	mph_native_print(ctx, mph_string_new(ctx, "  â "));
	mph_native_print(ctx, name);
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_test_fail(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_total_tests = (mph_total_tests + 1);
	mph_failed_tests = (mph_failed_tests + 1);
	mph_native_print(ctx, mph_string_new(ctx, "  â "));
	mph_native_print(ctx, name);
	mph_native_print(ctx, mph_string_new(ctx, " FAILED\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_test_token_module(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 1] Token Module Import\n"));
	mph_int int_token = mph_token_TOKEN_INT;
	mph_int string_token = mph_token_TOKEN_STRING;
	if ((int_token == 3)) {
{
	({ MorphString* _arg_1326 = mph_string_new(ctx, "TOKEN_INT accessible"); mph_gc_push_root(ctx, (void**)&_arg_1326); mph_test_pass(ctx, NULL, _arg_1326); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1327 = mph_string_new(ctx, "TOKEN_INT not accessible"); mph_gc_push_root(ctx, (void**)&_arg_1327); mph_test_fail(ctx, NULL, _arg_1327); mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((string_token == 5)) {
{
	({ MorphString* _arg_1328 = mph_string_new(ctx, "TOKEN_STRING accessible"); mph_gc_push_root(ctx, (void**)&_arg_1328); mph_test_pass(ctx, NULL, _arg_1328); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1329 = mph_string_new(ctx, "TOKEN_STRING not accessible"); mph_gc_push_root(ctx, (void**)&_arg_1329); mph_test_fail(ctx, NULL, _arg_1329); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_token_Token* tok = ({ MorphString* _arg_1330 = mph_string_new(ctx, "42"); mph_gc_push_root(ctx, (void**)&_arg_1330); mph_token_Token* _ret_1331 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_INT, _arg_1330, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_1331; });
	mph_gc_push_root(ctx, (void**)&tok);
	if ((({ mph_token_Token* _obj_1332 = tok; mph_gc_push_root(ctx, (void**)&_obj_1332); mph_int _ret_1333 = _obj_1332->token_type; mph_gc_pop_roots(ctx, 1); _ret_1333; }) == mph_token_TOKEN_INT)) {
{
	({ MorphString* _arg_1334 = mph_string_new(ctx, "token.MakeToken() works"); mph_gc_push_root(ctx, (void**)&_arg_1334); mph_test_pass(ctx, NULL, _arg_1334); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1335 = mph_string_new(ctx, "token.MakeToken() failed"); mph_gc_push_root(ctx, (void**)&_arg_1335); mph_test_fail(ctx, NULL, _arg_1335); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 1);
}

void mph_test_types_module(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 2] Types Module Import\n"));
	mph_types_Type* t_int = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_int);
	mph_types_Type* t_string = mph_types_StringType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_string);
	mph_types_Type* t_bool = mph_types_BoolType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_bool);
	if ((({ mph_types_Type* _obj_1336 = t_int; mph_gc_push_root(ctx, (void**)&_obj_1336); mph_int _ret_1337 = _obj_1336->kind; mph_gc_pop_roots(ctx, 1); _ret_1337; }) == mph_types_KIND_INT)) {
{
	({ MorphString* _arg_1338 = mph_string_new(ctx, "types.IntType() works"); mph_gc_push_root(ctx, (void**)&_arg_1338); mph_test_pass(ctx, NULL, _arg_1338); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1339 = mph_string_new(ctx, "types.IntType() failed"); mph_gc_push_root(ctx, (void**)&_arg_1339); mph_test_fail(ctx, NULL, _arg_1339); mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_types_Type* _obj_1340 = t_string; mph_gc_push_root(ctx, (void**)&_obj_1340); mph_int _ret_1341 = _obj_1340->kind; mph_gc_pop_roots(ctx, 1); _ret_1341; }) == mph_types_KIND_STRING)) {
{
	({ MorphString* _arg_1342 = mph_string_new(ctx, "types.StringType() works"); mph_gc_push_root(ctx, (void**)&_arg_1342); mph_test_pass(ctx, NULL, _arg_1342); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1343 = mph_string_new(ctx, "types.StringType() failed"); mph_gc_push_root(ctx, (void**)&_arg_1343); mph_test_fail(ctx, NULL, _arg_1343); mph_gc_pop_roots(ctx, 1); });
}
	}
	if (({ mph_types_Type* _arg_1344 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1344); mph_types_Type* _arg_1345 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1345); mph_bool _ret_1346 = mph_types_TypeEquals(ctx, NULL, _arg_1344, _arg_1345); mph_gc_pop_roots(ctx, 2); _ret_1346; })) {
{
	({ MorphString* _arg_1347 = mph_string_new(ctx, "types.TypeEquals() works"); mph_gc_push_root(ctx, (void**)&_arg_1347); mph_test_pass(ctx, NULL, _arg_1347); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1348 = mph_string_new(ctx, "types.TypeEquals() failed"); mph_gc_push_root(ctx, (void**)&_arg_1348); mph_test_fail(ctx, NULL, _arg_1348); mph_gc_pop_roots(ctx, 1); });
}
	}
	if (({ mph_types_Type* _arg_1349 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1349); mph_types_Type* _arg_1350 = t_int; mph_gc_push_root(ctx, (void**)&_arg_1350); mph_bool _ret_1351 = mph_types_TypeAssignableTo(ctx, NULL, _arg_1349, _arg_1350); mph_gc_pop_roots(ctx, 2); _ret_1351; })) {
{
	({ MorphString* _arg_1352 = mph_string_new(ctx, "types.TypeAssignableTo() works"); mph_gc_push_root(ctx, (void**)&_arg_1352); mph_test_pass(ctx, NULL, _arg_1352); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1353 = mph_string_new(ctx, "types.TypeAssignableTo() failed"); mph_gc_push_root(ctx, (void**)&_arg_1353); mph_test_fail(ctx, NULL, _arg_1353); mph_gc_pop_roots(ctx, 1); });
}
	}
	MorphString* kind_str = mph_types_KindToString(ctx, NULL, mph_types_KIND_INT);
	mph_gc_push_root(ctx, (void**)&kind_str);
	if (mph_string_eq(ctx, kind_str, mph_string_new(ctx, "int"))) {
{
	({ MorphString* _arg_1354 = mph_string_new(ctx, "types.KindToString() works"); mph_gc_push_root(ctx, (void**)&_arg_1354); mph_test_pass(ctx, NULL, _arg_1354); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1355 = mph_string_new(ctx, "types.KindToString() failed"); mph_gc_push_root(ctx, (void**)&_arg_1355); mph_test_fail(ctx, NULL, _arg_1355); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 4);
}

void mph_test_ast_module(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 3] AST Module Import\n"));
	mph_int node_int = mph_ast_NODE_INTEGER_LITERAL;
	if ((node_int == 8)) {
{
	({ MorphString* _arg_1356 = mph_string_new(ctx, "ast.NODE_INTEGER_LITERAL accessible"); mph_gc_push_root(ctx, (void**)&_arg_1356); mph_test_pass(ctx, NULL, _arg_1356); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1357 = mph_string_new(ctx, "ast.NODE_INTEGER_LITERAL not accessible"); mph_gc_push_root(ctx, (void**)&_arg_1357); mph_test_fail(ctx, NULL, _arg_1357); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_ast_Identifier* ident = ({ MorphString* _arg_1358 = mph_string_new(ctx, "x"); mph_gc_push_root(ctx, (void**)&_arg_1358); mph_ast_Identifier* _ret_1359 = mph_ast_MakeIdentifier(ctx, NULL, _arg_1358, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_1359; });
	mph_gc_push_root(ctx, (void**)&ident);
	if ((({ mph_ast_Node* _obj_1362 = ({ mph_ast_Identifier* _obj_1360 = ident; mph_gc_push_root(ctx, (void**)&_obj_1360); mph_ast_Node* _ret_1361 = _obj_1360->base; mph_gc_pop_roots(ctx, 1); _ret_1361; }); mph_gc_push_root(ctx, (void**)&_obj_1362); mph_int _ret_1363 = _obj_1362->node_type; mph_gc_pop_roots(ctx, 1); _ret_1363; }) == mph_ast_NODE_IDENTIFIER)) {
{
	({ MorphString* _arg_1364 = mph_string_new(ctx, "ast.MakeIdentifier() works"); mph_gc_push_root(ctx, (void**)&_arg_1364); mph_test_pass(ctx, NULL, _arg_1364); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1365 = mph_string_new(ctx, "ast.MakeIdentifier() failed"); mph_gc_push_root(ctx, (void**)&_arg_1365); mph_test_fail(ctx, NULL, _arg_1365); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_ast_IntegerLiteral* int_lit = ({ MorphString* _arg_1366 = mph_string_new(ctx, "42"); mph_gc_push_root(ctx, (void**)&_arg_1366); mph_ast_IntegerLiteral* _ret_1367 = mph_ast_MakeIntegerLiteral(ctx, NULL, 42, _arg_1366, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_1367; });
	mph_gc_push_root(ctx, (void**)&int_lit);
	if ((({ mph_ast_IntegerLiteral* _obj_1368 = int_lit; mph_gc_push_root(ctx, (void**)&_obj_1368); mph_int _ret_1369 = _obj_1368->value; mph_gc_pop_roots(ctx, 1); _ret_1369; }) == 42)) {
{
	({ MorphString* _arg_1370 = mph_string_new(ctx, "ast.MakeIntegerLiteral() works"); mph_gc_push_root(ctx, (void**)&_arg_1370); mph_test_pass(ctx, NULL, _arg_1370); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1371 = mph_string_new(ctx, "ast.MakeIntegerLiteral() failed"); mph_gc_push_root(ctx, (void**)&_arg_1371); mph_test_fail(ctx, NULL, _arg_1371); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_ast_StringLiteral* str_lit = ({ MorphString* _arg_1372 = mph_string_new(ctx, "hello"); mph_gc_push_root(ctx, (void**)&_arg_1372); mph_ast_StringLiteral* _ret_1373 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_1372, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_1373; });
	mph_gc_push_root(ctx, (void**)&str_lit);
	if ((({ mph_ast_Node* _obj_1376 = ({ mph_ast_StringLiteral* _obj_1374 = str_lit; mph_gc_push_root(ctx, (void**)&_obj_1374); mph_ast_Node* _ret_1375 = _obj_1374->base; mph_gc_pop_roots(ctx, 1); _ret_1375; }); mph_gc_push_root(ctx, (void**)&_obj_1376); mph_int _ret_1377 = _obj_1376->node_type; mph_gc_pop_roots(ctx, 1); _ret_1377; }) == mph_ast_NODE_STRING_LITERAL)) {
{
	({ MorphString* _arg_1378 = mph_string_new(ctx, "ast.MakeStringLiteral() works"); mph_gc_push_root(ctx, (void**)&_arg_1378); mph_test_pass(ctx, NULL, _arg_1378); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1379 = mph_string_new(ctx, "ast.MakeStringLiteral() failed"); mph_gc_push_root(ctx, (void**)&_arg_1379); mph_test_fail(ctx, NULL, _arg_1379); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 3);
}

void mph_test_lexer_module(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 4] Lexer Module Import\n"));
	mph_lexer_Lexer* lex = ({ MorphString* _arg_1380 = mph_string_new(ctx, "var x = 42"); mph_gc_push_root(ctx, (void**)&_arg_1380); mph_lexer_Lexer* _ret_1381 = mph_lexer_NewLexer(ctx, NULL, _arg_1380); mph_gc_pop_roots(ctx, 1); _ret_1381; });
	mph_gc_push_root(ctx, (void**)&lex);
	mph_token_Token* tok1 = ({ mph_lexer_Lexer* _arg_1382 = lex; mph_gc_push_root(ctx, (void**)&_arg_1382); mph_token_Token* _ret_1383 = mph_lexer_LexerNextToken(ctx, NULL, _arg_1382); mph_gc_pop_roots(ctx, 1); _ret_1383; });
	mph_gc_push_root(ctx, (void**)&tok1);
	if ((({ mph_token_Token* _obj_1384 = tok1; mph_gc_push_root(ctx, (void**)&_obj_1384); mph_int _ret_1385 = _obj_1384->token_type; mph_gc_pop_roots(ctx, 1); _ret_1385; }) == mph_token_TOKEN_VAR)) {
{
	({ MorphString* _arg_1386 = mph_string_new(ctx, "lexer.LexerNextToken() works - TOKEN_VAR"); mph_gc_push_root(ctx, (void**)&_arg_1386); mph_test_pass(ctx, NULL, _arg_1386); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1387 = mph_string_new(ctx, "lexer.LexerNextToken() failed - expected TOKEN_VAR"); mph_gc_push_root(ctx, (void**)&_arg_1387); mph_test_fail(ctx, NULL, _arg_1387); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_token_Token* tok2 = ({ mph_lexer_Lexer* _arg_1388 = lex; mph_gc_push_root(ctx, (void**)&_arg_1388); mph_token_Token* _ret_1389 = mph_lexer_LexerNextToken(ctx, NULL, _arg_1388); mph_gc_pop_roots(ctx, 1); _ret_1389; });
	mph_gc_push_root(ctx, (void**)&tok2);
	if ((({ mph_token_Token* _obj_1390 = tok2; mph_gc_push_root(ctx, (void**)&_obj_1390); mph_int _ret_1391 = _obj_1390->token_type; mph_gc_pop_roots(ctx, 1); _ret_1391; }) == mph_token_TOKEN_IDENT)) {
{
	({ MorphString* _arg_1392 = mph_string_new(ctx, "lexer.LexerNextToken() works - TOKEN_IDENT"); mph_gc_push_root(ctx, (void**)&_arg_1392); mph_test_pass(ctx, NULL, _arg_1392); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1393 = mph_string_new(ctx, "lexer.LexerNextToken() failed - expected TOKEN_IDENT"); mph_gc_push_root(ctx, (void**)&_arg_1393); mph_test_fail(ctx, NULL, _arg_1393); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 3);
}

void mph_test_parser_module(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 5] Parser Module Import\n"));
	mph_int lowest = mph_parser_PRECEDENCE_LOWEST;
	mph_int sum = mph_parser_PRECEDENCE_SUM;
	mph_int prod = mph_parser_PRECEDENCE_PRODUCT;
	if ((lowest == 1)) {
{
	({ MorphString* _arg_1394 = mph_string_new(ctx, "parser.PRECEDENCE_LOWEST accessible"); mph_gc_push_root(ctx, (void**)&_arg_1394); mph_test_pass(ctx, NULL, _arg_1394); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1395 = mph_string_new(ctx, "parser.PRECEDENCE_LOWEST not accessible"); mph_gc_push_root(ctx, (void**)&_arg_1395); mph_test_fail(ctx, NULL, _arg_1395); mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((sum == 4)) {
{
	({ MorphString* _arg_1396 = mph_string_new(ctx, "parser.PRECEDENCE_SUM accessible"); mph_gc_push_root(ctx, (void**)&_arg_1396); mph_test_pass(ctx, NULL, _arg_1396); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1397 = mph_string_new(ctx, "parser.PRECEDENCE_SUM not accessible"); mph_gc_push_root(ctx, (void**)&_arg_1397); mph_test_fail(ctx, NULL, _arg_1397); mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((prod == 5)) {
{
	({ MorphString* _arg_1398 = mph_string_new(ctx, "parser.PRECEDENCE_PRODUCT accessible"); mph_gc_push_root(ctx, (void**)&_arg_1398); mph_test_pass(ctx, NULL, _arg_1398); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1399 = mph_string_new(ctx, "parser.PRECEDENCE_PRODUCT not accessible"); mph_gc_push_root(ctx, (void**)&_arg_1399); mph_test_fail(ctx, NULL, _arg_1399); mph_gc_pop_roots(ctx, 1); });
}
	}
	({ MorphString* _arg_1400 = mph_string_new(ctx, "parser module imports successfully"); mph_gc_push_root(ctx, (void**)&_arg_1400); mph_test_pass(ctx, NULL, _arg_1400); mph_gc_pop_roots(ctx, 1); });
}

void mph_test_checker_module(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 6] Checker Module Import\n"));
	mph_checker_Checker* c = mph_checker_NewChecker(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_checker_Checker* _obj_1401 = c; mph_gc_push_root(ctx, (void**)&_obj_1401); mph_int _ret_1402 = _obj_1401->errors_count; mph_gc_pop_roots(ctx, 1); _ret_1402; }) == 0)) {
{
	({ MorphString* _arg_1403 = mph_string_new(ctx, "checker.NewChecker() works"); mph_gc_push_root(ctx, (void**)&_arg_1403); mph_test_pass(ctx, NULL, _arg_1403); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1404 = mph_string_new(ctx, "checker.NewChecker() failed"); mph_gc_push_root(ctx, (void**)&_arg_1404); mph_test_fail(ctx, NULL, _arg_1404); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_ast_IntegerLiteral* int_lit = ({ MorphString* _arg_1405 = mph_string_new(ctx, "42"); mph_gc_push_root(ctx, (void**)&_arg_1405); mph_ast_IntegerLiteral* _ret_1406 = mph_ast_MakeIntegerLiteral(ctx, NULL, 42, _arg_1405, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_1406; });
	mph_gc_push_root(ctx, (void**)&int_lit);
	mph_types_Type* checked_type = ({ mph_checker_Checker* _arg_1407 = c; mph_gc_push_root(ctx, (void**)&_arg_1407); mph_ast_IntegerLiteral* _arg_1408 = int_lit; mph_gc_push_root(ctx, (void**)&_arg_1408); mph_types_Type* _ret_1409 = mph_checker_CheckIntegerLiteral(ctx, NULL, _arg_1407, _arg_1408); mph_gc_pop_roots(ctx, 2); _ret_1409; });
	mph_gc_push_root(ctx, (void**)&checked_type);
	if ((({ mph_types_Type* _obj_1410 = checked_type; mph_gc_push_root(ctx, (void**)&_obj_1410); mph_int _ret_1411 = _obj_1410->kind; mph_gc_pop_roots(ctx, 1); _ret_1411; }) == mph_types_KIND_INT)) {
{
	({ MorphString* _arg_1412 = mph_string_new(ctx, "checker.CheckIntegerLiteral() works"); mph_gc_push_root(ctx, (void**)&_arg_1412); mph_test_pass(ctx, NULL, _arg_1412); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1413 = mph_string_new(ctx, "checker.CheckIntegerLiteral() failed"); mph_gc_push_root(ctx, (void**)&_arg_1413); mph_test_fail(ctx, NULL, _arg_1413); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_types_Type* builtin_type = ({ mph_checker_Checker* _arg_1414 = c; mph_gc_push_root(ctx, (void**)&_arg_1414); MorphString* _arg_1415 = mph_string_new(ctx, "panjang"); mph_gc_push_root(ctx, (void**)&_arg_1415); mph_types_Type* _ret_1416 = mph_checker_CheckBuiltinFunction(ctx, NULL, _arg_1414, _arg_1415, 1); mph_gc_pop_roots(ctx, 2); _ret_1416; });
	mph_gc_push_root(ctx, (void**)&builtin_type);
	if ((({ mph_types_Type* _obj_1417 = builtin_type; mph_gc_push_root(ctx, (void**)&_obj_1417); mph_int _ret_1418 = _obj_1417->kind; mph_gc_pop_roots(ctx, 1); _ret_1418; }) == mph_types_KIND_INT)) {
{
	({ MorphString* _arg_1419 = mph_string_new(ctx, "checker.CheckBuiltinFunction() works"); mph_gc_push_root(ctx, (void**)&_arg_1419); mph_test_pass(ctx, NULL, _arg_1419); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1420 = mph_string_new(ctx, "checker.CheckBuiltinFunction() failed"); mph_gc_push_root(ctx, (void**)&_arg_1420); mph_test_fail(ctx, NULL, _arg_1420); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 4);
}

void mph_test_integration(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 7] Cross-Module Integration\n"));
	mph_lexer_Lexer* lex = ({ MorphString* _arg_1421 = mph_string_new(ctx, "var x int = 42"); mph_gc_push_root(ctx, (void**)&_arg_1421); mph_lexer_Lexer* _ret_1422 = mph_lexer_NewLexer(ctx, NULL, _arg_1421); mph_gc_pop_roots(ctx, 1); _ret_1422; });
	mph_gc_push_root(ctx, (void**)&lex);
	mph_token_Token* tok = ({ mph_lexer_Lexer* _arg_1423 = lex; mph_gc_push_root(ctx, (void**)&_arg_1423); mph_token_Token* _ret_1424 = mph_lexer_LexerNextToken(ctx, NULL, _arg_1423); mph_gc_pop_roots(ctx, 1); _ret_1424; });
	mph_gc_push_root(ctx, (void**)&tok);
	if ((({ mph_token_Token* _obj_1425 = tok; mph_gc_push_root(ctx, (void**)&_obj_1425); mph_int _ret_1426 = _obj_1425->token_type; mph_gc_pop_roots(ctx, 1); _ret_1426; }) == mph_token_TOKEN_VAR)) {
{
	({ MorphString* _arg_1427 = mph_string_new(ctx, "Lexer module integration works"); mph_gc_push_root(ctx, (void**)&_arg_1427); mph_test_pass(ctx, NULL, _arg_1427); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1428 = mph_string_new(ctx, "Lexer module integration failed"); mph_gc_push_root(ctx, (void**)&_arg_1428); mph_test_fail(ctx, NULL, _arg_1428); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_types_Type* t = mph_types_IntType(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t);
	mph_bool assignable = ({ mph_types_Type* _arg_1429 = t; mph_gc_push_root(ctx, (void**)&_arg_1429); mph_types_Type* _arg_1430 = t; mph_gc_push_root(ctx, (void**)&_arg_1430); mph_bool _ret_1431 = mph_types_TypeAssignableTo(ctx, NULL, _arg_1429, _arg_1430); mph_gc_pop_roots(ctx, 2); _ret_1431; });
	if (assignable) {
{
	({ MorphString* _arg_1432 = mph_string_new(ctx, "Types â Checker integration works"); mph_gc_push_root(ctx, (void**)&_arg_1432); mph_test_pass(ctx, NULL, _arg_1432); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1433 = mph_string_new(ctx, "Types â Checker integration failed"); mph_gc_push_root(ctx, (void**)&_arg_1433); mph_test_fail(ctx, NULL, _arg_1433); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_ast_Program* prog = mph_ast_MakeProgram(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&prog);
	if ((({ mph_ast_Node* _obj_1436 = ({ mph_ast_Program* _obj_1434 = prog; mph_gc_push_root(ctx, (void**)&_obj_1434); mph_ast_Node* _ret_1435 = _obj_1434->base; mph_gc_pop_roots(ctx, 1); _ret_1435; }); mph_gc_push_root(ctx, (void**)&_obj_1436); mph_int _ret_1437 = _obj_1436->node_type; mph_gc_pop_roots(ctx, 1); _ret_1437; }) == mph_ast_NODE_PROGRAM)) {
{
	({ MorphString* _arg_1438 = mph_string_new(ctx, "AST integration works"); mph_gc_push_root(ctx, (void**)&_arg_1438); mph_test_pass(ctx, NULL, _arg_1438); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ MorphString* _arg_1439 = mph_string_new(ctx, "AST integration failed"); mph_gc_push_root(ctx, (void**)&_arg_1439); mph_test_fail(ctx, NULL, _arg_1439); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 4);
}

void mph_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â  N1 Module Import Test - Integration Suite  â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_test_token_module(ctx, NULL);
	mph_test_types_module(ctx, NULL);
	mph_test_ast_module(ctx, NULL);
	mph_test_lexer_module(ctx, NULL);
	mph_test_parser_module(ctx, NULL);
	mph_test_checker_module(ctx, NULL);
	mph_test_integration(ctx, NULL);
	mph_native_print(ctx, mph_string_new(ctx, "\nââââââââââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â              TEST SUMMARY                    â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  Total Tests:  "));
	mph_native_print_int(ctx, mph_total_tests);
	mph_native_print(ctx, mph_string_new(ctx, "\n  Passed:       "));
	mph_native_print_int(ctx, mph_passed_tests);
	mph_native_print(ctx, mph_string_new(ctx, "\n  Failed:       "));
	mph_native_print_int(ctx, mph_failed_tests);
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	if ((mph_failed_tests == 0)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "\n  â ALL MODULE IMPORTS WORKING! â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  N1 integration verified â\n\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "\n  â SOME TESTS FAILED\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  Module import issues detected â ï¸\n\n"));
}
	}
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_parser_PRECEDENCE_LOWEST = 1;
	mph_parser_PRECEDENCE_EQUALS = 2;
	mph_parser_PRECEDENCE_LESSGREATER = 3;
	mph_parser_PRECEDENCE_SUM = 4;
	mph_parser_PRECEDENCE_PRODUCT = 5;
	mph_parser_PRECEDENCE_PREFIX = 6;
	mph_parser_PRECEDENCE_CALL = 7;
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
	mph_total_tests = 0;
	mph_passed_tests = 0;
	mph_failed_tests = 0;
	mph_main(ctx, NULL);
}
