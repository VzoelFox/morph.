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
#define MPH_TYPE_mph_ast_Node 3
#define MPH_TYPE_mph_ast_ReturnStatement 6
#define MPH_TYPE_mph_ast_BooleanLiteral 14
#define MPH_TYPE_mph_ast_CharLiteral 15
#define MPH_TYPE_mph_ast_WhileStatement 25
#define MPH_TYPE_mph_ast_ExpressionStatement 7
#define MPH_TYPE_mph_ast_InfixExpression 18
#define MPH_TYPE_mph_ast_ContinueStatement 29
#define MPH_TYPE_mph_Parser 30
#define MPH_TYPE_mph_ast_IntegerLiteral 11
#define MPH_TYPE_mph_ast_BreakStatement 28
#define MPH_TYPE_mph_lexer_Lexer 2
#define MPH_TYPE_mph_ast_FunctionStatement 5
#define MPH_TYPE_mph_ast_Program 9
#define MPH_TYPE_mph_ast_PrefixExpression 17
#define MPH_TYPE_mph_ast_ImportStatement 27
#define MPH_TYPE_mph_ast_FloatLiteral 12
#define MPH_TYPE_mph_ast_IfExpression 19
#define MPH_TYPE_mph_ast_CallExpression 20
#define MPH_TYPE_mph_ast_CaseClause 23
#define MPH_TYPE_mph_ast_StructStatement 26
#define MPH_TYPE_mph_ast_Identifier 10
#define MPH_TYPE_mph_token_Token 1
#define MPH_TYPE_mph_ast_VarStatement 4
#define MPH_TYPE_mph_ast_BlockStatement 8
#define MPH_TYPE_mph_ast_StringLiteral 13
#define MPH_TYPE_mph_ast_NullLiteral 16
#define MPH_TYPE_mph_ast_IndexExpression 21
#define MPH_TYPE_mph_ast_MemberExpression 22
#define MPH_TYPE_mph_ast_SwitchStatement 24

// Struct Definitions (Env & Types)
typedef struct mph_token_Token mph_token_Token;
struct mph_token_Token {
	mph_int token_type;
	MorphString* literal;
	mph_int line;
	mph_int column;
};

typedef struct mph_lexer_Lexer mph_lexer_Lexer;
struct mph_lexer_Lexer {
	MorphString* input;
	mph_int position;
	mph_int read_position;
	mph_int ch;
	mph_int line;
	mph_int column;
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

typedef struct mph_Parser mph_Parser;
struct mph_Parser {
	mph_lexer_Lexer* lexer;
	mph_token_Token* current_token;
	mph_token_Token* peek_token;
	mph_int errors_count;
};

MorphTypeInfo mph_ti_mph_token_Token = { "Token", sizeof(mph_token_Token), 1, (size_t[]){offsetof(mph_token_Token, literal)} };
MorphTypeInfo mph_ti_mph_lexer_Lexer = { "Lexer", sizeof(mph_lexer_Lexer), 1, (size_t[]){offsetof(mph_lexer_Lexer, input)} };
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
MorphTypeInfo mph_ti_mph_Parser = { "Parser", sizeof(mph_Parser), 3, (size_t[]){offsetof(mph_Parser, lexer), offsetof(mph_Parser, current_token), offsetof(mph_Parser, peek_token)} };

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
mph_int mph_PRECEDENCE_LOWEST;
mph_int mph_PRECEDENCE_EQUALS;
mph_int mph_PRECEDENCE_LESSGREATER;
mph_int mph_PRECEDENCE_SUM;
mph_int mph_PRECEDENCE_PRODUCT;
mph_int mph_PRECEDENCE_PREFIX;
mph_int mph_PRECEDENCE_CALL;

// Function Prototypes
mph_Parser* mph_NewParser(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
void mph_ParserNextToken(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_bool mph_ParserCurrentTokenIs(MorphContext* ctx, void* _env_void, mph_Parser* p, mph_int token_type);
mph_bool mph_ParserPeekTokenIs(MorphContext* ctx, void* _env_void, mph_Parser* p, mph_int token_type);
mph_bool mph_ParserExpectPeek(MorphContext* ctx, void* _env_void, mph_Parser* p, mph_int token_type);
mph_int mph_GetTokenPrecedence(MorphContext* ctx, void* _env_void, mph_int token_type);
mph_int mph_ParserPeekPrecedence(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_int mph_ParserCurrentPrecedence(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_Identifier* mph_ParseIdentifier(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_IntegerLiteral* mph_ParseIntegerLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_StringLiteral* mph_ParseStringLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_BooleanLiteral* mph_ParseBooleanLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_FloatLiteral* mph_ParseFloatLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_CharLiteral* mph_ParseCharLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_NullLiteral* mph_ParseNullLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_PrefixExpression* mph_ParsePrefixExpression(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_VarStatement* mph_ParseVarStatement(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_ast_Program* mph_ParseProgram(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_int mph_StringToInt(MorphContext* ctx, void* _env_void, MorphString* s);
mph_bool mph_ParserHasErrors(MorphContext* ctx, void* _env_void, mph_Parser* p);
void mph_ParserPrintErrors(MorphContext* ctx, void* _env_void, mph_Parser* p);
mph_token_Token* mph_token_MakeToken(MorphContext* ctx, void* _env_void, mph_int t_type, MorphString* lit, mph_int ln, mph_int col);
MorphString* mph_token_TokenTypeString(MorphContext* ctx, void* _env_void, mph_int t_type);
mph_int mph_token_LookupKeyword(MorphContext* ctx, void* _env_void, MorphString* ident);
mph_lexer_Lexer* mph_lexer_new_lexer(MorphContext* ctx, void* _env_void, MorphString* input);
void mph_lexer_lexer_read_char(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
mph_int mph_lexer_char_to_ascii(MorphContext* ctx, void* _env_void, MorphString* char_str);
mph_int mph_lexer_CharToAscii(MorphContext* ctx, void* _env_void, MorphString* char_str);
mph_bool mph_lexer_is_letter(MorphContext* ctx, void* _env_void, mph_int ch);
mph_bool mph_lexer_is_digit(MorphContext* ctx, void* _env_void, mph_int ch);
mph_bool mph_lexer_is_whitespace(MorphContext* ctx, void* _env_void, mph_int ch);
mph_int mph_lexer_lexer_peek_char(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
void mph_lexer_lexer_skip_whitespace(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
MorphString* mph_lexer_lexer_read_identifier(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
mph_token_Token* mph_lexer_lexer_read_number_token(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l, mph_int line, mph_int column);
MorphString* mph_lexer_lexer_read_string(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
mph_token_Token* mph_lexer_lexer_read_char_token(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l, mph_int line, mph_int column);
mph_lexer_Lexer* mph_lexer_NewLexer(MorphContext* ctx, void* _env_void, MorphString* input);
mph_token_Token* mph_lexer_LexerNextToken(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l);
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

// Function Definitions
mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_ast_Node* _t = (mph_ast_Node*)mph_alloc(ctx, sizeof(mph_ast_Node), &mph_ti_mph_ast_Node); mph_gc_push_root(ctx, (void**)&_t); _t->line = line; _t->column = column; _t->node_type = node_type; _t->token_literal = literal; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void) {
	mph_ast_Node* base = ({ MorphString* _arg_1 = mph_string_new(ctx, "program"); mph_gc_push_root(ctx, (void**)&_arg_1); mph_ast_Node* _ret_2 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PROGRAM, _arg_1, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_2; });
	mph_gc_push_root(ctx, (void**)&base);
	mph_ast_VarStatement* stmt = ({ MorphString* _arg_3 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_3); MorphString* _arg_4 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_4); mph_ast_VarStatement* _ret_5 = mph_ast_MakeVarStatement(ctx, NULL, _arg_3, _arg_4, 1, 1); mph_gc_pop_roots(ctx, 2); _ret_5; });
	mph_gc_push_root(ctx, (void**)&stmt);
	return ({ mph_ast_Program* _t = (mph_ast_Program*)mph_alloc(ctx, sizeof(mph_ast_Program), &mph_ti_mph_ast_Program); mph_gc_push_root(ctx, (void**)&_t); _t->has_var_statement = 0; _t->base = base; _t->statements_count = 0; _t->var_statements_count = 0; _t->var_statement = stmt; mph_gc_pop_roots(ctx, 1); _t; });
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
	return ({ mph_ast_IntegerLiteral* _t = (mph_ast_IntegerLiteral*)mph_alloc(ctx, sizeof(mph_ast_IntegerLiteral), &mph_ti_mph_ast_IntegerLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->value = value; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_FloatLiteral* mph_ast_MakeFloatLiteral(MorphContext* ctx, void* _env_void, MorphString* value_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value_str);
	mph_ast_Node* base = ({ MorphString* _arg_10 = value_str; mph_gc_push_root(ctx, (void**)&_arg_10); mph_ast_Node* _ret_11 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_FLOAT_LITERAL, _arg_10, line, column); mph_gc_pop_roots(ctx, 1); _ret_11; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_FloatLiteral* _t = (mph_ast_FloatLiteral*)mph_alloc(ctx, sizeof(mph_ast_FloatLiteral), &mph_ti_mph_ast_FloatLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->value_str = value_str; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
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
	return ({ mph_ast_BooleanLiteral* _t = (mph_ast_BooleanLiteral*)mph_alloc(ctx, sizeof(mph_ast_BooleanLiteral), &mph_ti_mph_ast_BooleanLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->value = value; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
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
	return ({ mph_ast_VarStatement* _t = (mph_ast_VarStatement*)mph_alloc(ctx, sizeof(mph_ast_VarStatement), &mph_ti_mph_ast_VarStatement); mph_gc_push_root(ctx, (void**)&_t); _t->has_value = 0; _t->value_literal = mph_string_new(ctx, "-"); _t->value_token_type = 0; _t->base = base; _t->name = name; _t->value_type = type_str; mph_gc_pop_roots(ctx, 1); _t; });
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

mph_lexer_Lexer* mph_lexer_new_lexer(MorphContext* ctx, void* _env_void, MorphString* input) {
	mph_gc_push_root(ctx, (void**)&input);
	mph_lexer_Lexer* l = ({ mph_lexer_Lexer* _t = (mph_lexer_Lexer*)mph_alloc(ctx, sizeof(mph_lexer_Lexer), &mph_ti_mph_lexer_Lexer); mph_gc_push_root(ctx, (void**)&_t); _t->input = input; _t->position = 0; _t->read_position = 0; _t->ch = 0; _t->line = 1; _t->column = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_lexer_Lexer* _arg_101 = l; mph_gc_push_root(ctx, (void**)&_arg_101); mph_lexer_lexer_read_char(ctx, NULL, _arg_101); mph_gc_pop_roots(ctx, 1); });
	return l;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

void mph_lexer_lexer_read_char(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	if ((({ mph_lexer_Lexer* _obj_102 = l; mph_gc_push_root(ctx, (void**)&_obj_102); mph_int _ret_103 = _obj_102->read_position; mph_gc_pop_roots(ctx, 1); _ret_103; }) >= ({ MorphString* _len_arg_106 = ({ mph_lexer_Lexer* _obj_104 = l; mph_gc_push_root(ctx, (void**)&_obj_104); MorphString* _ret_105 = _obj_104->input; mph_gc_pop_roots(ctx, 1); _ret_105; }); mph_gc_push_root(ctx, (void**)&_len_arg_106); mph_int _ret_107 = ((MorphString*)_len_arg_106)->length; mph_gc_pop_roots(ctx, 1); _ret_107; }))) {
{
	({ mph_lexer_Lexer* _obj_108 = l; mph_gc_push_root(ctx, (void**)&_obj_108); _obj_108->ch = 0; mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	MorphString* char_str = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_109 = l; mph_gc_push_root(ctx, (void**)&_obj_109); MorphString* _ret_110 = _obj_109->input; mph_gc_pop_roots(ctx, 1); _ret_110; }), ({ mph_lexer_Lexer* _obj_111 = l; mph_gc_push_root(ctx, (void**)&_obj_111); mph_int _ret_112 = _obj_111->read_position; mph_gc_pop_roots(ctx, 1); _ret_112; }), (({ mph_lexer_Lexer* _obj_113 = l; mph_gc_push_root(ctx, (void**)&_obj_113); mph_int _ret_114 = _obj_113->read_position; mph_gc_pop_roots(ctx, 1); _ret_114; }) + 1));
	mph_gc_push_root(ctx, (void**)&char_str);
	({ mph_lexer_Lexer* _obj_117 = l; mph_gc_push_root(ctx, (void**)&_obj_117); _obj_117->ch = ({ MorphString* _arg_115 = char_str; mph_gc_push_root(ctx, (void**)&_arg_115); mph_int _ret_116 = mph_lexer_char_to_ascii(ctx, NULL, _arg_115); mph_gc_pop_roots(ctx, 1); _ret_116; }); mph_gc_pop_roots(ctx, 1); });
	mph_gc_pop_roots(ctx, 1);
}
	}
	({ mph_lexer_Lexer* _obj_120 = l; mph_gc_push_root(ctx, (void**)&_obj_120); _obj_120->position = ({ mph_lexer_Lexer* _obj_118 = l; mph_gc_push_root(ctx, (void**)&_obj_118); mph_int _ret_119 = _obj_118->read_position; mph_gc_pop_roots(ctx, 1); _ret_119; }); mph_gc_pop_roots(ctx, 1); });
	({ mph_lexer_Lexer* _obj_123 = l; mph_gc_push_root(ctx, (void**)&_obj_123); _obj_123->read_position = (({ mph_lexer_Lexer* _obj_121 = l; mph_gc_push_root(ctx, (void**)&_obj_121); mph_int _ret_122 = _obj_121->read_position; mph_gc_pop_roots(ctx, 1); _ret_122; }) + 1); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_lexer_Lexer* _obj_124 = l; mph_gc_push_root(ctx, (void**)&_obj_124); mph_int _ret_125 = _obj_124->ch; mph_gc_pop_roots(ctx, 1); _ret_125; }) == 10)) {
{
	({ mph_lexer_Lexer* _obj_128 = l; mph_gc_push_root(ctx, (void**)&_obj_128); _obj_128->line = (({ mph_lexer_Lexer* _obj_126 = l; mph_gc_push_root(ctx, (void**)&_obj_126); mph_int _ret_127 = _obj_126->line; mph_gc_pop_roots(ctx, 1); _ret_127; }) + 1); mph_gc_pop_roots(ctx, 1); });
	({ mph_lexer_Lexer* _obj_129 = l; mph_gc_push_root(ctx, (void**)&_obj_129); _obj_129->column = 0; mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ mph_lexer_Lexer* _obj_132 = l; mph_gc_push_root(ctx, (void**)&_obj_132); _obj_132->column = (({ mph_lexer_Lexer* _obj_130 = l; mph_gc_push_root(ctx, (void**)&_obj_130); mph_int _ret_131 = _obj_130->column; mph_gc_pop_roots(ctx, 1); _ret_131; }) + 1); mph_gc_pop_roots(ctx, 1); });
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

mph_int mph_lexer_CharToAscii(MorphContext* ctx, void* _env_void, MorphString* char_str) {
	mph_gc_push_root(ctx, (void**)&char_str);
	return ({ MorphString* _arg_133 = char_str; mph_gc_push_root(ctx, (void**)&_arg_133); mph_int _ret_134 = mph_lexer_char_to_ascii(ctx, NULL, _arg_133); mph_gc_pop_roots(ctx, 1); _ret_134; });
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
	if ((({ mph_lexer_Lexer* _obj_135 = l; mph_gc_push_root(ctx, (void**)&_obj_135); mph_int _ret_136 = _obj_135->read_position; mph_gc_pop_roots(ctx, 1); _ret_136; }) >= ({ MorphString* _len_arg_139 = ({ mph_lexer_Lexer* _obj_137 = l; mph_gc_push_root(ctx, (void**)&_obj_137); MorphString* _ret_138 = _obj_137->input; mph_gc_pop_roots(ctx, 1); _ret_138; }); mph_gc_push_root(ctx, (void**)&_len_arg_139); mph_int _ret_140 = ((MorphString*)_len_arg_139)->length; mph_gc_pop_roots(ctx, 1); _ret_140; }))) {
{
	return 0;
}
	} else {
{
	MorphString* char_str = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_141 = l; mph_gc_push_root(ctx, (void**)&_obj_141); MorphString* _ret_142 = _obj_141->input; mph_gc_pop_roots(ctx, 1); _ret_142; }), ({ mph_lexer_Lexer* _obj_143 = l; mph_gc_push_root(ctx, (void**)&_obj_143); mph_int _ret_144 = _obj_143->read_position; mph_gc_pop_roots(ctx, 1); _ret_144; }), (({ mph_lexer_Lexer* _obj_145 = l; mph_gc_push_root(ctx, (void**)&_obj_145); mph_int _ret_146 = _obj_145->read_position; mph_gc_pop_roots(ctx, 1); _ret_146; }) + 1));
	mph_gc_push_root(ctx, (void**)&char_str);
	return ({ MorphString* _arg_147 = char_str; mph_gc_push_root(ctx, (void**)&_arg_147); mph_int _ret_148 = mph_lexer_char_to_ascii(ctx, NULL, _arg_147); mph_gc_pop_roots(ctx, 1); _ret_148; });
	mph_gc_pop_roots(ctx, 1);
}
	}
	mph_gc_pop_roots(ctx, 1);
}

void mph_lexer_lexer_skip_whitespace(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	while (mph_lexer_is_whitespace(ctx, NULL, ({ mph_lexer_Lexer* _obj_149 = l; mph_gc_push_root(ctx, (void**)&_obj_149); mph_int _ret_150 = _obj_149->ch; mph_gc_pop_roots(ctx, 1); _ret_150; }))) {
{
	({ mph_lexer_Lexer* _arg_151 = l; mph_gc_push_root(ctx, (void**)&_arg_151); mph_lexer_lexer_read_char(ctx, NULL, _arg_151); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_lexer_read_identifier(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = ({ mph_lexer_Lexer* _obj_152 = l; mph_gc_push_root(ctx, (void**)&_obj_152); mph_int _ret_153 = _obj_152->position; mph_gc_pop_roots(ctx, 1); _ret_153; });
	mph_bool done = 0;
	while ((done == 0)) {
{
	if (mph_lexer_is_letter(ctx, NULL, ({ mph_lexer_Lexer* _obj_154 = l; mph_gc_push_root(ctx, (void**)&_obj_154); mph_int _ret_155 = _obj_154->ch; mph_gc_pop_roots(ctx, 1); _ret_155; }))) {
{
	({ mph_lexer_Lexer* _arg_156 = l; mph_gc_push_root(ctx, (void**)&_arg_156); mph_lexer_lexer_read_char(ctx, NULL, _arg_156); mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	if (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _obj_157 = l; mph_gc_push_root(ctx, (void**)&_obj_157); mph_int _ret_158 = _obj_157->ch; mph_gc_pop_roots(ctx, 1); _ret_158; }))) {
{
	({ mph_lexer_Lexer* _arg_159 = l; mph_gc_push_root(ctx, (void**)&_arg_159); mph_lexer_lexer_read_char(ctx, NULL, _arg_159); mph_gc_pop_roots(ctx, 1); });
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
	return mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_160 = l; mph_gc_push_root(ctx, (void**)&_obj_160); MorphString* _ret_161 = _obj_160->input; mph_gc_pop_roots(ctx, 1); _ret_161; }), position, ({ mph_lexer_Lexer* _obj_162 = l; mph_gc_push_root(ctx, (void**)&_obj_162); mph_int _ret_163 = _obj_162->position; mph_gc_pop_roots(ctx, 1); _ret_163; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_token_Token* mph_lexer_lexer_read_number_token(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = ({ mph_lexer_Lexer* _obj_164 = l; mph_gc_push_root(ctx, (void**)&_obj_164); mph_int _ret_165 = _obj_164->position; mph_gc_pop_roots(ctx, 1); _ret_165; });
	mph_int token_type = mph_token_TOKEN_INT;
	while (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _obj_166 = l; mph_gc_push_root(ctx, (void**)&_obj_166); mph_int _ret_167 = _obj_166->ch; mph_gc_pop_roots(ctx, 1); _ret_167; }))) {
{
	({ mph_lexer_Lexer* _arg_168 = l; mph_gc_push_root(ctx, (void**)&_arg_168); mph_lexer_lexer_read_char(ctx, NULL, _arg_168); mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_lexer_Lexer* _obj_169 = l; mph_gc_push_root(ctx, (void**)&_obj_169); mph_int _ret_170 = _obj_169->ch; mph_gc_pop_roots(ctx, 1); _ret_170; }) == 46)) {
{
	if (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _arg_171 = l; mph_gc_push_root(ctx, (void**)&_arg_171); mph_int _ret_172 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_171); mph_gc_pop_roots(ctx, 1); _ret_172; }))) {
{
	token_type = mph_token_TOKEN_FLOAT;
	({ mph_lexer_Lexer* _arg_173 = l; mph_gc_push_root(ctx, (void**)&_arg_173); mph_lexer_lexer_read_char(ctx, NULL, _arg_173); mph_gc_pop_roots(ctx, 1); });
	while (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _obj_174 = l; mph_gc_push_root(ctx, (void**)&_obj_174); mph_int _ret_175 = _obj_174->ch; mph_gc_pop_roots(ctx, 1); _ret_175; }))) {
{
	({ mph_lexer_Lexer* _arg_176 = l; mph_gc_push_root(ctx, (void**)&_arg_176); mph_lexer_lexer_read_char(ctx, NULL, _arg_176); mph_gc_pop_roots(ctx, 1); });
}
	}
}
	}
}
	}
	MorphString* literal = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_177 = l; mph_gc_push_root(ctx, (void**)&_obj_177); MorphString* _ret_178 = _obj_177->input; mph_gc_pop_roots(ctx, 1); _ret_178; }), position, ({ mph_lexer_Lexer* _obj_179 = l; mph_gc_push_root(ctx, (void**)&_obj_179); mph_int _ret_180 = _obj_179->position; mph_gc_pop_roots(ctx, 1); _ret_180; }));
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ MorphString* _arg_181 = literal; mph_gc_push_root(ctx, (void**)&_arg_181); mph_token_Token* _ret_182 = mph_token_MakeToken(ctx, NULL, token_type, _arg_181, line, column); mph_gc_pop_roots(ctx, 1); _ret_182; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_lexer_read_string(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_lexer_Lexer* _arg_183 = l; mph_gc_push_root(ctx, (void**)&_arg_183); mph_lexer_lexer_read_char(ctx, NULL, _arg_183); mph_gc_pop_roots(ctx, 1); });
	MorphString* output = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&output);
	mph_bool should_continue = 1;
	while (should_continue) {
{
	if ((({ mph_lexer_Lexer* _obj_184 = l; mph_gc_push_root(ctx, (void**)&_obj_184); mph_int _ret_185 = _obj_184->ch; mph_gc_pop_roots(ctx, 1); _ret_185; }) == 34)) {
{
	should_continue = 0;
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_186 = l; mph_gc_push_root(ctx, (void**)&_obj_186); mph_int _ret_187 = _obj_186->ch; mph_gc_pop_roots(ctx, 1); _ret_187; }) == 0)) {
{
	should_continue = 0;
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_188 = l; mph_gc_push_root(ctx, (void**)&_obj_188); mph_int _ret_189 = _obj_188->ch; mph_gc_pop_roots(ctx, 1); _ret_189; }) == 92)) {
{
	({ mph_lexer_Lexer* _arg_190 = l; mph_gc_push_root(ctx, (void**)&_arg_190); mph_lexer_lexer_read_char(ctx, NULL, _arg_190); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_lexer_Lexer* _obj_191 = l; mph_gc_push_root(ctx, (void**)&_obj_191); mph_int _ret_192 = _obj_191->ch; mph_gc_pop_roots(ctx, 1); _ret_192; }) == 110)) {
{
	output = ({ MorphString* _lhs_193 = output; MorphString* _rhs_194 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_193); mph_gc_push_root(ctx, (void**)&_rhs_194); MorphString* _ret_195 = mph_string_concat(ctx, _lhs_193, _rhs_194); mph_gc_pop_roots(ctx, 2); _ret_195; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_196 = l; mph_gc_push_root(ctx, (void**)&_obj_196); mph_int _ret_197 = _obj_196->ch; mph_gc_pop_roots(ctx, 1); _ret_197; }) == 116)) {
{
	output = ({ MorphString* _lhs_198 = output; MorphString* _rhs_199 = mph_string_new(ctx, "\t"); mph_gc_push_root(ctx, (void**)&_lhs_198); mph_gc_push_root(ctx, (void**)&_rhs_199); MorphString* _ret_200 = mph_string_concat(ctx, _lhs_198, _rhs_199); mph_gc_pop_roots(ctx, 2); _ret_200; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_201 = l; mph_gc_push_root(ctx, (void**)&_obj_201); mph_int _ret_202 = _obj_201->ch; mph_gc_pop_roots(ctx, 1); _ret_202; }) == 114)) {
{
	output = ({ MorphString* _lhs_203 = output; MorphString* _rhs_204 = mph_string_new(ctx, "\r"); mph_gc_push_root(ctx, (void**)&_lhs_203); mph_gc_push_root(ctx, (void**)&_rhs_204); MorphString* _ret_205 = mph_string_concat(ctx, _lhs_203, _rhs_204); mph_gc_pop_roots(ctx, 2); _ret_205; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_206 = l; mph_gc_push_root(ctx, (void**)&_obj_206); mph_int _ret_207 = _obj_206->ch; mph_gc_pop_roots(ctx, 1); _ret_207; }) == 34)) {
{
	output = ({ MorphString* _lhs_208 = output; MorphString* _rhs_209 = mph_string_new(ctx, "\""); mph_gc_push_root(ctx, (void**)&_lhs_208); mph_gc_push_root(ctx, (void**)&_rhs_209); MorphString* _ret_210 = mph_string_concat(ctx, _lhs_208, _rhs_209); mph_gc_pop_roots(ctx, 2); _ret_210; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_211 = l; mph_gc_push_root(ctx, (void**)&_obj_211); mph_int _ret_212 = _obj_211->ch; mph_gc_pop_roots(ctx, 1); _ret_212; }) == 92)) {
{
	output = ({ MorphString* _lhs_213 = output; MorphString* _rhs_214 = mph_string_new(ctx, "\\"); mph_gc_push_root(ctx, (void**)&_lhs_213); mph_gc_push_root(ctx, (void**)&_rhs_214); MorphString* _ret_215 = mph_string_concat(ctx, _lhs_213, _rhs_214); mph_gc_pop_roots(ctx, 2); _ret_215; });
}
	} else {
{
	output = ({ MorphString* _lhs_222 = output; MorphString* _rhs_223 = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_216 = l; mph_gc_push_root(ctx, (void**)&_obj_216); MorphString* _ret_217 = _obj_216->input; mph_gc_pop_roots(ctx, 1); _ret_217; }), ({ mph_lexer_Lexer* _obj_218 = l; mph_gc_push_root(ctx, (void**)&_obj_218); mph_int _ret_219 = _obj_218->position; mph_gc_pop_roots(ctx, 1); _ret_219; }), (({ mph_lexer_Lexer* _obj_220 = l; mph_gc_push_root(ctx, (void**)&_obj_220); mph_int _ret_221 = _obj_220->position; mph_gc_pop_roots(ctx, 1); _ret_221; }) + 1)); mph_gc_push_root(ctx, (void**)&_lhs_222); mph_gc_push_root(ctx, (void**)&_rhs_223); MorphString* _ret_224 = mph_string_concat(ctx, _lhs_222, _rhs_223); mph_gc_pop_roots(ctx, 2); _ret_224; });
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
}
	} else {
{
	output = ({ MorphString* _lhs_231 = output; MorphString* _rhs_232 = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_225 = l; mph_gc_push_root(ctx, (void**)&_obj_225); MorphString* _ret_226 = _obj_225->input; mph_gc_pop_roots(ctx, 1); _ret_226; }), ({ mph_lexer_Lexer* _obj_227 = l; mph_gc_push_root(ctx, (void**)&_obj_227); mph_int _ret_228 = _obj_227->position; mph_gc_pop_roots(ctx, 1); _ret_228; }), (({ mph_lexer_Lexer* _obj_229 = l; mph_gc_push_root(ctx, (void**)&_obj_229); mph_int _ret_230 = _obj_229->position; mph_gc_pop_roots(ctx, 1); _ret_230; }) + 1)); mph_gc_push_root(ctx, (void**)&_lhs_231); mph_gc_push_root(ctx, (void**)&_rhs_232); MorphString* _ret_233 = mph_string_concat(ctx, _lhs_231, _rhs_232); mph_gc_pop_roots(ctx, 2); _ret_233; });
}
	}
	({ mph_lexer_Lexer* _arg_234 = l; mph_gc_push_root(ctx, (void**)&_arg_234); mph_lexer_lexer_read_char(ctx, NULL, _arg_234); mph_gc_pop_roots(ctx, 1); });
}
	}
}
	}
}
	}
	return output;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_token_Token* mph_lexer_lexer_read_char_token(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_lexer_Lexer* _arg_235 = l; mph_gc_push_root(ctx, (void**)&_arg_235); mph_lexer_lexer_read_char(ctx, NULL, _arg_235); mph_gc_pop_roots(ctx, 1); });
	MorphString* literal = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&literal);
	if ((({ mph_lexer_Lexer* _obj_236 = l; mph_gc_push_root(ctx, (void**)&_obj_236); mph_int _ret_237 = _obj_236->ch; mph_gc_pop_roots(ctx, 1); _ret_237; }) == 92)) {
{
	({ mph_lexer_Lexer* _arg_238 = l; mph_gc_push_root(ctx, (void**)&_arg_238); mph_lexer_lexer_read_char(ctx, NULL, _arg_238); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_lexer_Lexer* _obj_239 = l; mph_gc_push_root(ctx, (void**)&_obj_239); mph_int _ret_240 = _obj_239->ch; mph_gc_pop_roots(ctx, 1); _ret_240; }) == 110)) {
{
	literal = mph_string_new(ctx, "\n");
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_241 = l; mph_gc_push_root(ctx, (void**)&_obj_241); mph_int _ret_242 = _obj_241->ch; mph_gc_pop_roots(ctx, 1); _ret_242; }) == 116)) {
{
	literal = mph_string_new(ctx, "\t");
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_243 = l; mph_gc_push_root(ctx, (void**)&_obj_243); mph_int _ret_244 = _obj_243->ch; mph_gc_pop_roots(ctx, 1); _ret_244; }) == 114)) {
{
	literal = mph_string_new(ctx, "\r");
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_245 = l; mph_gc_push_root(ctx, (void**)&_obj_245); mph_int _ret_246 = _obj_245->ch; mph_gc_pop_roots(ctx, 1); _ret_246; }) == 39)) {
{
	literal = mph_string_new(ctx, "'");
}
	} else {
{
	if ((({ mph_lexer_Lexer* _obj_247 = l; mph_gc_push_root(ctx, (void**)&_obj_247); mph_int _ret_248 = _obj_247->ch; mph_gc_pop_roots(ctx, 1); _ret_248; }) == 92)) {
{
	literal = mph_string_new(ctx, "\\");
}
	} else {
{
	literal = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_249 = l; mph_gc_push_root(ctx, (void**)&_obj_249); MorphString* _ret_250 = _obj_249->input; mph_gc_pop_roots(ctx, 1); _ret_250; }), ({ mph_lexer_Lexer* _obj_251 = l; mph_gc_push_root(ctx, (void**)&_obj_251); mph_int _ret_252 = _obj_251->position; mph_gc_pop_roots(ctx, 1); _ret_252; }), (({ mph_lexer_Lexer* _obj_253 = l; mph_gc_push_root(ctx, (void**)&_obj_253); mph_int _ret_254 = _obj_253->position; mph_gc_pop_roots(ctx, 1); _ret_254; }) + 1));
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
}
	} else {
{
	literal = mph_string_substring(ctx, ({ mph_lexer_Lexer* _obj_255 = l; mph_gc_push_root(ctx, (void**)&_obj_255); MorphString* _ret_256 = _obj_255->input; mph_gc_pop_roots(ctx, 1); _ret_256; }), ({ mph_lexer_Lexer* _obj_257 = l; mph_gc_push_root(ctx, (void**)&_obj_257); mph_int _ret_258 = _obj_257->position; mph_gc_pop_roots(ctx, 1); _ret_258; }), (({ mph_lexer_Lexer* _obj_259 = l; mph_gc_push_root(ctx, (void**)&_obj_259); mph_int _ret_260 = _obj_259->position; mph_gc_pop_roots(ctx, 1); _ret_260; }) + 1));
}
	}
	({ mph_lexer_Lexer* _arg_261 = l; mph_gc_push_root(ctx, (void**)&_arg_261); mph_lexer_lexer_read_char(ctx, NULL, _arg_261); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_lexer_Lexer* _obj_262 = l; mph_gc_push_root(ctx, (void**)&_obj_262); mph_int _ret_263 = _obj_262->ch; mph_gc_pop_roots(ctx, 1); _ret_263; }) != 39)) {
{
	return ({ MorphString* _arg_264 = mph_string_new(ctx, "Unterminated char literal"); mph_gc_push_root(ctx, (void**)&_arg_264); mph_token_Token* _ret_265 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ILLEGAL, _arg_264, line, column); mph_gc_pop_roots(ctx, 1); _ret_265; });
}
	}
	({ mph_lexer_Lexer* _arg_266 = l; mph_gc_push_root(ctx, (void**)&_arg_266); mph_lexer_lexer_read_char(ctx, NULL, _arg_266); mph_gc_pop_roots(ctx, 1); });
	return ({ MorphString* _arg_267 = literal; mph_gc_push_root(ctx, (void**)&_arg_267); mph_token_Token* _ret_268 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_CHAR, _arg_267, line, column); mph_gc_pop_roots(ctx, 1); _ret_268; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_lexer_Lexer* mph_lexer_NewLexer(MorphContext* ctx, void* _env_void, MorphString* input) {
	mph_gc_push_root(ctx, (void**)&input);
	return ({ MorphString* _arg_269 = input; mph_gc_push_root(ctx, (void**)&_arg_269); mph_lexer_Lexer* _ret_270 = mph_lexer_new_lexer(ctx, NULL, _arg_269); mph_gc_pop_roots(ctx, 1); _ret_270; });
	mph_gc_pop_roots(ctx, 1);
}

mph_token_Token* mph_lexer_LexerNextToken(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_lexer_Lexer* _arg_271 = l; mph_gc_push_root(ctx, (void**)&_arg_271); mph_lexer_lexer_skip_whitespace(ctx, NULL, _arg_271); mph_gc_pop_roots(ctx, 1); });
	mph_token_Token* tok = ({ MorphString* _arg_272 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_272); mph_token_Token* _ret_277 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ILLEGAL, _arg_272, ({ mph_lexer_Lexer* _obj_273 = l; mph_gc_push_root(ctx, (void**)&_obj_273); mph_int _ret_274 = _obj_273->line; mph_gc_pop_roots(ctx, 1); _ret_274; }), ({ mph_lexer_Lexer* _obj_275 = l; mph_gc_push_root(ctx, (void**)&_obj_275); mph_int _ret_276 = _obj_275->column; mph_gc_pop_roots(ctx, 1); _ret_276; })); mph_gc_pop_roots(ctx, 1); _ret_277; });
	mph_gc_push_root(ctx, (void**)&tok);
	if ((({ mph_lexer_Lexer* _obj_278 = l; mph_gc_push_root(ctx, (void**)&_obj_278); mph_int _ret_279 = _obj_278->ch; mph_gc_pop_roots(ctx, 1); _ret_279; }) == 61)) {
{
	if ((({ mph_lexer_Lexer* _arg_280 = l; mph_gc_push_root(ctx, (void**)&_arg_280); mph_int _ret_281 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_280); mph_gc_pop_roots(ctx, 1); _ret_281; }) == 61)) {
{
	mph_int ch = ({ mph_lexer_Lexer* _obj_282 = l; mph_gc_push_root(ctx, (void**)&_obj_282); mph_int _ret_283 = _obj_282->ch; mph_gc_pop_roots(ctx, 1); _ret_283; });
	({ mph_lexer_Lexer* _arg_284 = l; mph_gc_push_root(ctx, (void**)&_arg_284); mph_lexer_lexer_read_char(ctx, NULL, _arg_284); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_285 = mph_string_new(ctx, "=="); mph_gc_push_root(ctx, (void**)&_arg_285); mph_token_Token* _ret_290 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_EQ, _arg_285, ({ mph_lexer_Lexer* _obj_286 = l; mph_gc_push_root(ctx, (void**)&_obj_286); mph_int _ret_287 = _obj_286->line; mph_gc_pop_roots(ctx, 1); _ret_287; }), ({ mph_lexer_Lexer* _obj_288 = l; mph_gc_push_root(ctx, (void**)&_obj_288); mph_int _ret_289 = _obj_288->column; mph_gc_pop_roots(ctx, 1); _ret_289; })); mph_gc_pop_roots(ctx, 1); _ret_290; });
}
	} else {
{
	tok = ({ MorphString* _arg_291 = mph_string_new(ctx, "="); mph_gc_push_root(ctx, (void**)&_arg_291); mph_token_Token* _ret_296 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ASSIGN, _arg_291, ({ mph_lexer_Lexer* _obj_292 = l; mph_gc_push_root(ctx, (void**)&_obj_292); mph_int _ret_293 = _obj_292->line; mph_gc_pop_roots(ctx, 1); _ret_293; }), ({ mph_lexer_Lexer* _obj_294 = l; mph_gc_push_root(ctx, (void**)&_obj_294); mph_int _ret_295 = _obj_294->column; mph_gc_pop_roots(ctx, 1); _ret_295; })); mph_gc_pop_roots(ctx, 1); _ret_296; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_297 = l; mph_gc_push_root(ctx, (void**)&_obj_297); mph_int _ret_298 = _obj_297->ch; mph_gc_pop_roots(ctx, 1); _ret_298; }) == 43)) {
{
	tok = ({ MorphString* _arg_299 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_299); mph_token_Token* _ret_304 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_PLUS, _arg_299, ({ mph_lexer_Lexer* _obj_300 = l; mph_gc_push_root(ctx, (void**)&_obj_300); mph_int _ret_301 = _obj_300->line; mph_gc_pop_roots(ctx, 1); _ret_301; }), ({ mph_lexer_Lexer* _obj_302 = l; mph_gc_push_root(ctx, (void**)&_obj_302); mph_int _ret_303 = _obj_302->column; mph_gc_pop_roots(ctx, 1); _ret_303; })); mph_gc_pop_roots(ctx, 1); _ret_304; });
}
	} else if ((({ mph_lexer_Lexer* _obj_305 = l; mph_gc_push_root(ctx, (void**)&_obj_305); mph_int _ret_306 = _obj_305->ch; mph_gc_pop_roots(ctx, 1); _ret_306; }) == 45)) {
{
	if ((({ mph_lexer_Lexer* _arg_307 = l; mph_gc_push_root(ctx, (void**)&_arg_307); mph_int _ret_308 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_307); mph_gc_pop_roots(ctx, 1); _ret_308; }) == 62)) {
{
	({ mph_lexer_Lexer* _arg_309 = l; mph_gc_push_root(ctx, (void**)&_arg_309); mph_lexer_lexer_read_char(ctx, NULL, _arg_309); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_310 = mph_string_new(ctx, "->"); mph_gc_push_root(ctx, (void**)&_arg_310); mph_token_Token* _ret_315 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ARROW, _arg_310, ({ mph_lexer_Lexer* _obj_311 = l; mph_gc_push_root(ctx, (void**)&_obj_311); mph_int _ret_312 = _obj_311->line; mph_gc_pop_roots(ctx, 1); _ret_312; }), ({ mph_lexer_Lexer* _obj_313 = l; mph_gc_push_root(ctx, (void**)&_obj_313); mph_int _ret_314 = _obj_313->column; mph_gc_pop_roots(ctx, 1); _ret_314; })); mph_gc_pop_roots(ctx, 1); _ret_315; });
}
	} else {
{
	tok = ({ MorphString* _arg_316 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_316); mph_token_Token* _ret_321 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_MINUS, _arg_316, ({ mph_lexer_Lexer* _obj_317 = l; mph_gc_push_root(ctx, (void**)&_obj_317); mph_int _ret_318 = _obj_317->line; mph_gc_pop_roots(ctx, 1); _ret_318; }), ({ mph_lexer_Lexer* _obj_319 = l; mph_gc_push_root(ctx, (void**)&_obj_319); mph_int _ret_320 = _obj_319->column; mph_gc_pop_roots(ctx, 1); _ret_320; })); mph_gc_pop_roots(ctx, 1); _ret_321; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_322 = l; mph_gc_push_root(ctx, (void**)&_obj_322); mph_int _ret_323 = _obj_322->ch; mph_gc_pop_roots(ctx, 1); _ret_323; }) == 33)) {
{
	if ((({ mph_lexer_Lexer* _arg_324 = l; mph_gc_push_root(ctx, (void**)&_arg_324); mph_int _ret_325 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_324); mph_gc_pop_roots(ctx, 1); _ret_325; }) == 61)) {
{
	({ mph_lexer_Lexer* _arg_326 = l; mph_gc_push_root(ctx, (void**)&_arg_326); mph_lexer_lexer_read_char(ctx, NULL, _arg_326); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_327 = mph_string_new(ctx, "!="); mph_gc_push_root(ctx, (void**)&_arg_327); mph_token_Token* _ret_332 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_NOT_EQ, _arg_327, ({ mph_lexer_Lexer* _obj_328 = l; mph_gc_push_root(ctx, (void**)&_obj_328); mph_int _ret_329 = _obj_328->line; mph_gc_pop_roots(ctx, 1); _ret_329; }), ({ mph_lexer_Lexer* _obj_330 = l; mph_gc_push_root(ctx, (void**)&_obj_330); mph_int _ret_331 = _obj_330->column; mph_gc_pop_roots(ctx, 1); _ret_331; })); mph_gc_pop_roots(ctx, 1); _ret_332; });
}
	} else {
{
	tok = ({ MorphString* _arg_333 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_333); mph_token_Token* _ret_338 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BANG, _arg_333, ({ mph_lexer_Lexer* _obj_334 = l; mph_gc_push_root(ctx, (void**)&_obj_334); mph_int _ret_335 = _obj_334->line; mph_gc_pop_roots(ctx, 1); _ret_335; }), ({ mph_lexer_Lexer* _obj_336 = l; mph_gc_push_root(ctx, (void**)&_obj_336); mph_int _ret_337 = _obj_336->column; mph_gc_pop_roots(ctx, 1); _ret_337; })); mph_gc_pop_roots(ctx, 1); _ret_338; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_339 = l; mph_gc_push_root(ctx, (void**)&_obj_339); mph_int _ret_340 = _obj_339->ch; mph_gc_pop_roots(ctx, 1); _ret_340; }) == 42)) {
{
	tok = ({ MorphString* _arg_341 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_arg_341); mph_token_Token* _ret_346 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ASTERISK, _arg_341, ({ mph_lexer_Lexer* _obj_342 = l; mph_gc_push_root(ctx, (void**)&_obj_342); mph_int _ret_343 = _obj_342->line; mph_gc_pop_roots(ctx, 1); _ret_343; }), ({ mph_lexer_Lexer* _obj_344 = l; mph_gc_push_root(ctx, (void**)&_obj_344); mph_int _ret_345 = _obj_344->column; mph_gc_pop_roots(ctx, 1); _ret_345; })); mph_gc_pop_roots(ctx, 1); _ret_346; });
}
	} else if ((({ mph_lexer_Lexer* _obj_347 = l; mph_gc_push_root(ctx, (void**)&_obj_347); mph_int _ret_348 = _obj_347->ch; mph_gc_pop_roots(ctx, 1); _ret_348; }) == 47)) {
{
	tok = ({ MorphString* _arg_349 = mph_string_new(ctx, "/"); mph_gc_push_root(ctx, (void**)&_arg_349); mph_token_Token* _ret_354 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_SLASH, _arg_349, ({ mph_lexer_Lexer* _obj_350 = l; mph_gc_push_root(ctx, (void**)&_obj_350); mph_int _ret_351 = _obj_350->line; mph_gc_pop_roots(ctx, 1); _ret_351; }), ({ mph_lexer_Lexer* _obj_352 = l; mph_gc_push_root(ctx, (void**)&_obj_352); mph_int _ret_353 = _obj_352->column; mph_gc_pop_roots(ctx, 1); _ret_353; })); mph_gc_pop_roots(ctx, 1); _ret_354; });
}
	} else if ((({ mph_lexer_Lexer* _obj_355 = l; mph_gc_push_root(ctx, (void**)&_obj_355); mph_int _ret_356 = _obj_355->ch; mph_gc_pop_roots(ctx, 1); _ret_356; }) == 37)) {
{
	tok = ({ MorphString* _arg_357 = mph_string_new(ctx, "%"); mph_gc_push_root(ctx, (void**)&_arg_357); mph_token_Token* _ret_362 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_PERCENT, _arg_357, ({ mph_lexer_Lexer* _obj_358 = l; mph_gc_push_root(ctx, (void**)&_obj_358); mph_int _ret_359 = _obj_358->line; mph_gc_pop_roots(ctx, 1); _ret_359; }), ({ mph_lexer_Lexer* _obj_360 = l; mph_gc_push_root(ctx, (void**)&_obj_360); mph_int _ret_361 = _obj_360->column; mph_gc_pop_roots(ctx, 1); _ret_361; })); mph_gc_pop_roots(ctx, 1); _ret_362; });
}
	} else if ((({ mph_lexer_Lexer* _obj_363 = l; mph_gc_push_root(ctx, (void**)&_obj_363); mph_int _ret_364 = _obj_363->ch; mph_gc_pop_roots(ctx, 1); _ret_364; }) == 60)) {
{
	if ((({ mph_lexer_Lexer* _arg_365 = l; mph_gc_push_root(ctx, (void**)&_arg_365); mph_int _ret_366 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_365); mph_gc_pop_roots(ctx, 1); _ret_366; }) == 61)) {
{
	({ mph_lexer_Lexer* _arg_367 = l; mph_gc_push_root(ctx, (void**)&_arg_367); mph_lexer_lexer_read_char(ctx, NULL, _arg_367); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_368 = mph_string_new(ctx, "<="); mph_gc_push_root(ctx, (void**)&_arg_368); mph_token_Token* _ret_373 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LE, _arg_368, ({ mph_lexer_Lexer* _obj_369 = l; mph_gc_push_root(ctx, (void**)&_obj_369); mph_int _ret_370 = _obj_369->line; mph_gc_pop_roots(ctx, 1); _ret_370; }), ({ mph_lexer_Lexer* _obj_371 = l; mph_gc_push_root(ctx, (void**)&_obj_371); mph_int _ret_372 = _obj_371->column; mph_gc_pop_roots(ctx, 1); _ret_372; })); mph_gc_pop_roots(ctx, 1); _ret_373; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _arg_374 = l; mph_gc_push_root(ctx, (void**)&_arg_374); mph_int _ret_375 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_374); mph_gc_pop_roots(ctx, 1); _ret_375; }) == 60)) {
{
	({ mph_lexer_Lexer* _arg_376 = l; mph_gc_push_root(ctx, (void**)&_arg_376); mph_lexer_lexer_read_char(ctx, NULL, _arg_376); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_377 = mph_string_new(ctx, "<<"); mph_gc_push_root(ctx, (void**)&_arg_377); mph_token_Token* _ret_382 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LSHIFT, _arg_377, ({ mph_lexer_Lexer* _obj_378 = l; mph_gc_push_root(ctx, (void**)&_obj_378); mph_int _ret_379 = _obj_378->line; mph_gc_pop_roots(ctx, 1); _ret_379; }), ({ mph_lexer_Lexer* _obj_380 = l; mph_gc_push_root(ctx, (void**)&_obj_380); mph_int _ret_381 = _obj_380->column; mph_gc_pop_roots(ctx, 1); _ret_381; })); mph_gc_pop_roots(ctx, 1); _ret_382; });
}
	} else {
{
	tok = ({ MorphString* _arg_383 = mph_string_new(ctx, "<"); mph_gc_push_root(ctx, (void**)&_arg_383); mph_token_Token* _ret_388 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LT, _arg_383, ({ mph_lexer_Lexer* _obj_384 = l; mph_gc_push_root(ctx, (void**)&_obj_384); mph_int _ret_385 = _obj_384->line; mph_gc_pop_roots(ctx, 1); _ret_385; }), ({ mph_lexer_Lexer* _obj_386 = l; mph_gc_push_root(ctx, (void**)&_obj_386); mph_int _ret_387 = _obj_386->column; mph_gc_pop_roots(ctx, 1); _ret_387; })); mph_gc_pop_roots(ctx, 1); _ret_388; });
}
	}
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_389 = l; mph_gc_push_root(ctx, (void**)&_obj_389); mph_int _ret_390 = _obj_389->ch; mph_gc_pop_roots(ctx, 1); _ret_390; }) == 62)) {
{
	if ((({ mph_lexer_Lexer* _arg_391 = l; mph_gc_push_root(ctx, (void**)&_arg_391); mph_int _ret_392 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_391); mph_gc_pop_roots(ctx, 1); _ret_392; }) == 61)) {
{
	({ mph_lexer_Lexer* _arg_393 = l; mph_gc_push_root(ctx, (void**)&_arg_393); mph_lexer_lexer_read_char(ctx, NULL, _arg_393); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_394 = mph_string_new(ctx, ">="); mph_gc_push_root(ctx, (void**)&_arg_394); mph_token_Token* _ret_399 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_GE, _arg_394, ({ mph_lexer_Lexer* _obj_395 = l; mph_gc_push_root(ctx, (void**)&_obj_395); mph_int _ret_396 = _obj_395->line; mph_gc_pop_roots(ctx, 1); _ret_396; }), ({ mph_lexer_Lexer* _obj_397 = l; mph_gc_push_root(ctx, (void**)&_obj_397); mph_int _ret_398 = _obj_397->column; mph_gc_pop_roots(ctx, 1); _ret_398; })); mph_gc_pop_roots(ctx, 1); _ret_399; });
}
	} else {
{
	if ((({ mph_lexer_Lexer* _arg_400 = l; mph_gc_push_root(ctx, (void**)&_arg_400); mph_int _ret_401 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_400); mph_gc_pop_roots(ctx, 1); _ret_401; }) == 62)) {
{
	({ mph_lexer_Lexer* _arg_402 = l; mph_gc_push_root(ctx, (void**)&_arg_402); mph_lexer_lexer_read_char(ctx, NULL, _arg_402); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_403 = mph_string_new(ctx, ">>"); mph_gc_push_root(ctx, (void**)&_arg_403); mph_token_Token* _ret_408 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RSHIFT, _arg_403, ({ mph_lexer_Lexer* _obj_404 = l; mph_gc_push_root(ctx, (void**)&_obj_404); mph_int _ret_405 = _obj_404->line; mph_gc_pop_roots(ctx, 1); _ret_405; }), ({ mph_lexer_Lexer* _obj_406 = l; mph_gc_push_root(ctx, (void**)&_obj_406); mph_int _ret_407 = _obj_406->column; mph_gc_pop_roots(ctx, 1); _ret_407; })); mph_gc_pop_roots(ctx, 1); _ret_408; });
}
	} else {
{
	tok = ({ MorphString* _arg_409 = mph_string_new(ctx, ">"); mph_gc_push_root(ctx, (void**)&_arg_409); mph_token_Token* _ret_414 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_GT, _arg_409, ({ mph_lexer_Lexer* _obj_410 = l; mph_gc_push_root(ctx, (void**)&_obj_410); mph_int _ret_411 = _obj_410->line; mph_gc_pop_roots(ctx, 1); _ret_411; }), ({ mph_lexer_Lexer* _obj_412 = l; mph_gc_push_root(ctx, (void**)&_obj_412); mph_int _ret_413 = _obj_412->column; mph_gc_pop_roots(ctx, 1); _ret_413; })); mph_gc_pop_roots(ctx, 1); _ret_414; });
}
	}
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_415 = l; mph_gc_push_root(ctx, (void**)&_obj_415); mph_int _ret_416 = _obj_415->ch; mph_gc_pop_roots(ctx, 1); _ret_416; }) == 38)) {
{
	if ((({ mph_lexer_Lexer* _arg_417 = l; mph_gc_push_root(ctx, (void**)&_arg_417); mph_int _ret_418 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_417); mph_gc_pop_roots(ctx, 1); _ret_418; }) == 38)) {
{
	({ mph_lexer_Lexer* _arg_419 = l; mph_gc_push_root(ctx, (void**)&_arg_419); mph_lexer_lexer_read_char(ctx, NULL, _arg_419); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_420 = mph_string_new(ctx, "&&"); mph_gc_push_root(ctx, (void**)&_arg_420); mph_token_Token* _ret_425 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_AND, _arg_420, ({ mph_lexer_Lexer* _obj_421 = l; mph_gc_push_root(ctx, (void**)&_obj_421); mph_int _ret_422 = _obj_421->line; mph_gc_pop_roots(ctx, 1); _ret_422; }), ({ mph_lexer_Lexer* _obj_423 = l; mph_gc_push_root(ctx, (void**)&_obj_423); mph_int _ret_424 = _obj_423->column; mph_gc_pop_roots(ctx, 1); _ret_424; })); mph_gc_pop_roots(ctx, 1); _ret_425; });
}
	} else {
{
	tok = ({ MorphString* _arg_426 = mph_string_new(ctx, "&"); mph_gc_push_root(ctx, (void**)&_arg_426); mph_token_Token* _ret_431 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_AND, _arg_426, ({ mph_lexer_Lexer* _obj_427 = l; mph_gc_push_root(ctx, (void**)&_obj_427); mph_int _ret_428 = _obj_427->line; mph_gc_pop_roots(ctx, 1); _ret_428; }), ({ mph_lexer_Lexer* _obj_429 = l; mph_gc_push_root(ctx, (void**)&_obj_429); mph_int _ret_430 = _obj_429->column; mph_gc_pop_roots(ctx, 1); _ret_430; })); mph_gc_pop_roots(ctx, 1); _ret_431; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_432 = l; mph_gc_push_root(ctx, (void**)&_obj_432); mph_int _ret_433 = _obj_432->ch; mph_gc_pop_roots(ctx, 1); _ret_433; }) == 124)) {
{
	if ((({ mph_lexer_Lexer* _arg_434 = l; mph_gc_push_root(ctx, (void**)&_arg_434); mph_int _ret_435 = mph_lexer_lexer_peek_char(ctx, NULL, _arg_434); mph_gc_pop_roots(ctx, 1); _ret_435; }) == 124)) {
{
	({ mph_lexer_Lexer* _arg_436 = l; mph_gc_push_root(ctx, (void**)&_arg_436); mph_lexer_lexer_read_char(ctx, NULL, _arg_436); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_437 = mph_string_new(ctx, "||"); mph_gc_push_root(ctx, (void**)&_arg_437); mph_token_Token* _ret_442 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_OR, _arg_437, ({ mph_lexer_Lexer* _obj_438 = l; mph_gc_push_root(ctx, (void**)&_obj_438); mph_int _ret_439 = _obj_438->line; mph_gc_pop_roots(ctx, 1); _ret_439; }), ({ mph_lexer_Lexer* _obj_440 = l; mph_gc_push_root(ctx, (void**)&_obj_440); mph_int _ret_441 = _obj_440->column; mph_gc_pop_roots(ctx, 1); _ret_441; })); mph_gc_pop_roots(ctx, 1); _ret_442; });
}
	} else {
{
	tok = ({ MorphString* _arg_443 = mph_string_new(ctx, "|"); mph_gc_push_root(ctx, (void**)&_arg_443); mph_token_Token* _ret_448 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_OR, _arg_443, ({ mph_lexer_Lexer* _obj_444 = l; mph_gc_push_root(ctx, (void**)&_obj_444); mph_int _ret_445 = _obj_444->line; mph_gc_pop_roots(ctx, 1); _ret_445; }), ({ mph_lexer_Lexer* _obj_446 = l; mph_gc_push_root(ctx, (void**)&_obj_446); mph_int _ret_447 = _obj_446->column; mph_gc_pop_roots(ctx, 1); _ret_447; })); mph_gc_pop_roots(ctx, 1); _ret_448; });
}
	}
}
	} else if ((({ mph_lexer_Lexer* _obj_449 = l; mph_gc_push_root(ctx, (void**)&_obj_449); mph_int _ret_450 = _obj_449->ch; mph_gc_pop_roots(ctx, 1); _ret_450; }) == 94)) {
{
	tok = ({ MorphString* _arg_451 = mph_string_new(ctx, "^"); mph_gc_push_root(ctx, (void**)&_arg_451); mph_token_Token* _ret_456 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_XOR, _arg_451, ({ mph_lexer_Lexer* _obj_452 = l; mph_gc_push_root(ctx, (void**)&_obj_452); mph_int _ret_453 = _obj_452->line; mph_gc_pop_roots(ctx, 1); _ret_453; }), ({ mph_lexer_Lexer* _obj_454 = l; mph_gc_push_root(ctx, (void**)&_obj_454); mph_int _ret_455 = _obj_454->column; mph_gc_pop_roots(ctx, 1); _ret_455; })); mph_gc_pop_roots(ctx, 1); _ret_456; });
}
	} else if ((({ mph_lexer_Lexer* _obj_457 = l; mph_gc_push_root(ctx, (void**)&_obj_457); mph_int _ret_458 = _obj_457->ch; mph_gc_pop_roots(ctx, 1); _ret_458; }) == 126)) {
{
	tok = ({ MorphString* _arg_459 = mph_string_new(ctx, "~"); mph_gc_push_root(ctx, (void**)&_arg_459); mph_token_Token* _ret_464 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_BIT_NOT, _arg_459, ({ mph_lexer_Lexer* _obj_460 = l; mph_gc_push_root(ctx, (void**)&_obj_460); mph_int _ret_461 = _obj_460->line; mph_gc_pop_roots(ctx, 1); _ret_461; }), ({ mph_lexer_Lexer* _obj_462 = l; mph_gc_push_root(ctx, (void**)&_obj_462); mph_int _ret_463 = _obj_462->column; mph_gc_pop_roots(ctx, 1); _ret_463; })); mph_gc_pop_roots(ctx, 1); _ret_464; });
}
	} else if ((({ mph_lexer_Lexer* _obj_465 = l; mph_gc_push_root(ctx, (void**)&_obj_465); mph_int _ret_466 = _obj_465->ch; mph_gc_pop_roots(ctx, 1); _ret_466; }) == 44)) {
{
	tok = ({ MorphString* _arg_467 = mph_string_new(ctx, ","); mph_gc_push_root(ctx, (void**)&_arg_467); mph_token_Token* _ret_472 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_COMMA, _arg_467, ({ mph_lexer_Lexer* _obj_468 = l; mph_gc_push_root(ctx, (void**)&_obj_468); mph_int _ret_469 = _obj_468->line; mph_gc_pop_roots(ctx, 1); _ret_469; }), ({ mph_lexer_Lexer* _obj_470 = l; mph_gc_push_root(ctx, (void**)&_obj_470); mph_int _ret_471 = _obj_470->column; mph_gc_pop_roots(ctx, 1); _ret_471; })); mph_gc_pop_roots(ctx, 1); _ret_472; });
}
	} else if ((({ mph_lexer_Lexer* _obj_473 = l; mph_gc_push_root(ctx, (void**)&_obj_473); mph_int _ret_474 = _obj_473->ch; mph_gc_pop_roots(ctx, 1); _ret_474; }) == 59)) {
{
	tok = ({ MorphString* _arg_475 = mph_string_new(ctx, ";"); mph_gc_push_root(ctx, (void**)&_arg_475); mph_token_Token* _ret_480 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_SEMICOLON, _arg_475, ({ mph_lexer_Lexer* _obj_476 = l; mph_gc_push_root(ctx, (void**)&_obj_476); mph_int _ret_477 = _obj_476->line; mph_gc_pop_roots(ctx, 1); _ret_477; }), ({ mph_lexer_Lexer* _obj_478 = l; mph_gc_push_root(ctx, (void**)&_obj_478); mph_int _ret_479 = _obj_478->column; mph_gc_pop_roots(ctx, 1); _ret_479; })); mph_gc_pop_roots(ctx, 1); _ret_480; });
}
	} else if ((({ mph_lexer_Lexer* _obj_481 = l; mph_gc_push_root(ctx, (void**)&_obj_481); mph_int _ret_482 = _obj_481->ch; mph_gc_pop_roots(ctx, 1); _ret_482; }) == 58)) {
{
	tok = ({ MorphString* _arg_483 = mph_string_new(ctx, ":"); mph_gc_push_root(ctx, (void**)&_arg_483); mph_token_Token* _ret_488 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_COLON, _arg_483, ({ mph_lexer_Lexer* _obj_484 = l; mph_gc_push_root(ctx, (void**)&_obj_484); mph_int _ret_485 = _obj_484->line; mph_gc_pop_roots(ctx, 1); _ret_485; }), ({ mph_lexer_Lexer* _obj_486 = l; mph_gc_push_root(ctx, (void**)&_obj_486); mph_int _ret_487 = _obj_486->column; mph_gc_pop_roots(ctx, 1); _ret_487; })); mph_gc_pop_roots(ctx, 1); _ret_488; });
}
	} else if ((({ mph_lexer_Lexer* _obj_489 = l; mph_gc_push_root(ctx, (void**)&_obj_489); mph_int _ret_490 = _obj_489->ch; mph_gc_pop_roots(ctx, 1); _ret_490; }) == 40)) {
{
	tok = ({ MorphString* _arg_491 = mph_string_new(ctx, "("); mph_gc_push_root(ctx, (void**)&_arg_491); mph_token_Token* _ret_496 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LPAREN, _arg_491, ({ mph_lexer_Lexer* _obj_492 = l; mph_gc_push_root(ctx, (void**)&_obj_492); mph_int _ret_493 = _obj_492->line; mph_gc_pop_roots(ctx, 1); _ret_493; }), ({ mph_lexer_Lexer* _obj_494 = l; mph_gc_push_root(ctx, (void**)&_obj_494); mph_int _ret_495 = _obj_494->column; mph_gc_pop_roots(ctx, 1); _ret_495; })); mph_gc_pop_roots(ctx, 1); _ret_496; });
}
	} else if ((({ mph_lexer_Lexer* _obj_497 = l; mph_gc_push_root(ctx, (void**)&_obj_497); mph_int _ret_498 = _obj_497->ch; mph_gc_pop_roots(ctx, 1); _ret_498; }) == 41)) {
{
	tok = ({ MorphString* _arg_499 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_arg_499); mph_token_Token* _ret_504 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RPAREN, _arg_499, ({ mph_lexer_Lexer* _obj_500 = l; mph_gc_push_root(ctx, (void**)&_obj_500); mph_int _ret_501 = _obj_500->line; mph_gc_pop_roots(ctx, 1); _ret_501; }), ({ mph_lexer_Lexer* _obj_502 = l; mph_gc_push_root(ctx, (void**)&_obj_502); mph_int _ret_503 = _obj_502->column; mph_gc_pop_roots(ctx, 1); _ret_503; })); mph_gc_pop_roots(ctx, 1); _ret_504; });
}
	} else if ((({ mph_lexer_Lexer* _obj_505 = l; mph_gc_push_root(ctx, (void**)&_obj_505); mph_int _ret_506 = _obj_505->ch; mph_gc_pop_roots(ctx, 1); _ret_506; }) == 123)) {
{
	tok = ({ MorphString* _arg_507 = mph_string_new(ctx, "{"); mph_gc_push_root(ctx, (void**)&_arg_507); mph_token_Token* _ret_512 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LBRACE, _arg_507, ({ mph_lexer_Lexer* _obj_508 = l; mph_gc_push_root(ctx, (void**)&_obj_508); mph_int _ret_509 = _obj_508->line; mph_gc_pop_roots(ctx, 1); _ret_509; }), ({ mph_lexer_Lexer* _obj_510 = l; mph_gc_push_root(ctx, (void**)&_obj_510); mph_int _ret_511 = _obj_510->column; mph_gc_pop_roots(ctx, 1); _ret_511; })); mph_gc_pop_roots(ctx, 1); _ret_512; });
}
	} else if ((({ mph_lexer_Lexer* _obj_513 = l; mph_gc_push_root(ctx, (void**)&_obj_513); mph_int _ret_514 = _obj_513->ch; mph_gc_pop_roots(ctx, 1); _ret_514; }) == 125)) {
{
	tok = ({ MorphString* _arg_515 = mph_string_new(ctx, "}"); mph_gc_push_root(ctx, (void**)&_arg_515); mph_token_Token* _ret_520 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RBRACE, _arg_515, ({ mph_lexer_Lexer* _obj_516 = l; mph_gc_push_root(ctx, (void**)&_obj_516); mph_int _ret_517 = _obj_516->line; mph_gc_pop_roots(ctx, 1); _ret_517; }), ({ mph_lexer_Lexer* _obj_518 = l; mph_gc_push_root(ctx, (void**)&_obj_518); mph_int _ret_519 = _obj_518->column; mph_gc_pop_roots(ctx, 1); _ret_519; })); mph_gc_pop_roots(ctx, 1); _ret_520; });
}
	} else if ((({ mph_lexer_Lexer* _obj_521 = l; mph_gc_push_root(ctx, (void**)&_obj_521); mph_int _ret_522 = _obj_521->ch; mph_gc_pop_roots(ctx, 1); _ret_522; }) == 91)) {
{
	tok = ({ MorphString* _arg_523 = mph_string_new(ctx, "["); mph_gc_push_root(ctx, (void**)&_arg_523); mph_token_Token* _ret_528 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_LBRACKET, _arg_523, ({ mph_lexer_Lexer* _obj_524 = l; mph_gc_push_root(ctx, (void**)&_obj_524); mph_int _ret_525 = _obj_524->line; mph_gc_pop_roots(ctx, 1); _ret_525; }), ({ mph_lexer_Lexer* _obj_526 = l; mph_gc_push_root(ctx, (void**)&_obj_526); mph_int _ret_527 = _obj_526->column; mph_gc_pop_roots(ctx, 1); _ret_527; })); mph_gc_pop_roots(ctx, 1); _ret_528; });
}
	} else if ((({ mph_lexer_Lexer* _obj_529 = l; mph_gc_push_root(ctx, (void**)&_obj_529); mph_int _ret_530 = _obj_529->ch; mph_gc_pop_roots(ctx, 1); _ret_530; }) == 93)) {
{
	tok = ({ MorphString* _arg_531 = mph_string_new(ctx, "]"); mph_gc_push_root(ctx, (void**)&_arg_531); mph_token_Token* _ret_536 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_RBRACKET, _arg_531, ({ mph_lexer_Lexer* _obj_532 = l; mph_gc_push_root(ctx, (void**)&_obj_532); mph_int _ret_533 = _obj_532->line; mph_gc_pop_roots(ctx, 1); _ret_533; }), ({ mph_lexer_Lexer* _obj_534 = l; mph_gc_push_root(ctx, (void**)&_obj_534); mph_int _ret_535 = _obj_534->column; mph_gc_pop_roots(ctx, 1); _ret_535; })); mph_gc_pop_roots(ctx, 1); _ret_536; });
}
	} else if ((({ mph_lexer_Lexer* _obj_537 = l; mph_gc_push_root(ctx, (void**)&_obj_537); mph_int _ret_538 = _obj_537->ch; mph_gc_pop_roots(ctx, 1); _ret_538; }) == 46)) {
{
	tok = ({ MorphString* _arg_539 = mph_string_new(ctx, "."); mph_gc_push_root(ctx, (void**)&_arg_539); mph_token_Token* _ret_544 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_DOT, _arg_539, ({ mph_lexer_Lexer* _obj_540 = l; mph_gc_push_root(ctx, (void**)&_obj_540); mph_int _ret_541 = _obj_540->line; mph_gc_pop_roots(ctx, 1); _ret_541; }), ({ mph_lexer_Lexer* _obj_542 = l; mph_gc_push_root(ctx, (void**)&_obj_542); mph_int _ret_543 = _obj_542->column; mph_gc_pop_roots(ctx, 1); _ret_543; })); mph_gc_pop_roots(ctx, 1); _ret_544; });
}
	} else if ((({ mph_lexer_Lexer* _obj_545 = l; mph_gc_push_root(ctx, (void**)&_obj_545); mph_int _ret_546 = _obj_545->ch; mph_gc_pop_roots(ctx, 1); _ret_546; }) == 34)) {
{
	MorphString* str_literal = ({ mph_lexer_Lexer* _arg_547 = l; mph_gc_push_root(ctx, (void**)&_arg_547); MorphString* _ret_548 = mph_lexer_lexer_read_string(ctx, NULL, _arg_547); mph_gc_pop_roots(ctx, 1); _ret_548; });
	mph_gc_push_root(ctx, (void**)&str_literal);
	tok = ({ MorphString* _arg_549 = str_literal; mph_gc_push_root(ctx, (void**)&_arg_549); mph_token_Token* _ret_554 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_STRING, _arg_549, ({ mph_lexer_Lexer* _obj_550 = l; mph_gc_push_root(ctx, (void**)&_obj_550); mph_int _ret_551 = _obj_550->line; mph_gc_pop_roots(ctx, 1); _ret_551; }), ({ mph_lexer_Lexer* _obj_552 = l; mph_gc_push_root(ctx, (void**)&_obj_552); mph_int _ret_553 = _obj_552->column; mph_gc_pop_roots(ctx, 1); _ret_553; })); mph_gc_pop_roots(ctx, 1); _ret_554; });
	mph_gc_pop_roots(ctx, 1);
}
	} else if ((({ mph_lexer_Lexer* _obj_555 = l; mph_gc_push_root(ctx, (void**)&_obj_555); mph_int _ret_556 = _obj_555->ch; mph_gc_pop_roots(ctx, 1); _ret_556; }) == 39)) {
{
	tok = ({ mph_lexer_Lexer* _arg_557 = l; mph_gc_push_root(ctx, (void**)&_arg_557); mph_token_Token* _ret_562 = mph_lexer_lexer_read_char_token(ctx, NULL, _arg_557, ({ mph_lexer_Lexer* _obj_558 = l; mph_gc_push_root(ctx, (void**)&_obj_558); mph_int _ret_559 = _obj_558->line; mph_gc_pop_roots(ctx, 1); _ret_559; }), ({ mph_lexer_Lexer* _obj_560 = l; mph_gc_push_root(ctx, (void**)&_obj_560); mph_int _ret_561 = _obj_560->column; mph_gc_pop_roots(ctx, 1); _ret_561; })); mph_gc_pop_roots(ctx, 1); _ret_562; });
	return tok;
}
	} else if ((({ mph_lexer_Lexer* _obj_563 = l; mph_gc_push_root(ctx, (void**)&_obj_563); mph_int _ret_564 = _obj_563->ch; mph_gc_pop_roots(ctx, 1); _ret_564; }) == 0)) {
{
	tok = ({ MorphString* _arg_565 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_565); mph_token_Token* _ret_570 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_EOF, _arg_565, ({ mph_lexer_Lexer* _obj_566 = l; mph_gc_push_root(ctx, (void**)&_obj_566); mph_int _ret_567 = _obj_566->line; mph_gc_pop_roots(ctx, 1); _ret_567; }), ({ mph_lexer_Lexer* _obj_568 = l; mph_gc_push_root(ctx, (void**)&_obj_568); mph_int _ret_569 = _obj_568->column; mph_gc_pop_roots(ctx, 1); _ret_569; })); mph_gc_pop_roots(ctx, 1); _ret_570; });
}
	} else {
{
	if (mph_lexer_is_letter(ctx, NULL, ({ mph_lexer_Lexer* _obj_571 = l; mph_gc_push_root(ctx, (void**)&_obj_571); mph_int _ret_572 = _obj_571->ch; mph_gc_pop_roots(ctx, 1); _ret_572; }))) {
{
	MorphString* literal = ({ mph_lexer_Lexer* _arg_573 = l; mph_gc_push_root(ctx, (void**)&_arg_573); MorphString* _ret_574 = mph_lexer_lexer_read_identifier(ctx, NULL, _arg_573); mph_gc_pop_roots(ctx, 1); _ret_574; });
	mph_gc_push_root(ctx, (void**)&literal);
	mph_int token_type = ({ MorphString* _arg_575 = literal; mph_gc_push_root(ctx, (void**)&_arg_575); mph_int _ret_576 = mph_token_LookupKeyword(ctx, NULL, _arg_575); mph_gc_pop_roots(ctx, 1); _ret_576; });
	tok = ({ MorphString* _arg_577 = literal; mph_gc_push_root(ctx, (void**)&_arg_577); mph_token_Token* _ret_582 = mph_token_MakeToken(ctx, NULL, token_type, _arg_577, ({ mph_lexer_Lexer* _obj_578 = l; mph_gc_push_root(ctx, (void**)&_obj_578); mph_int _ret_579 = _obj_578->line; mph_gc_pop_roots(ctx, 1); _ret_579; }), ({ mph_lexer_Lexer* _obj_580 = l; mph_gc_push_root(ctx, (void**)&_obj_580); mph_int _ret_581 = _obj_580->column; mph_gc_pop_roots(ctx, 1); _ret_581; })); mph_gc_pop_roots(ctx, 1); _ret_582; });
	return tok;
	mph_gc_pop_roots(ctx, 1);
}
	} else {
{
	if (mph_lexer_is_digit(ctx, NULL, ({ mph_lexer_Lexer* _obj_583 = l; mph_gc_push_root(ctx, (void**)&_obj_583); mph_int _ret_584 = _obj_583->ch; mph_gc_pop_roots(ctx, 1); _ret_584; }))) {
{
	tok = ({ mph_lexer_Lexer* _arg_585 = l; mph_gc_push_root(ctx, (void**)&_arg_585); mph_token_Token* _ret_590 = mph_lexer_lexer_read_number_token(ctx, NULL, _arg_585, ({ mph_lexer_Lexer* _obj_586 = l; mph_gc_push_root(ctx, (void**)&_obj_586); mph_int _ret_587 = _obj_586->line; mph_gc_pop_roots(ctx, 1); _ret_587; }), ({ mph_lexer_Lexer* _obj_588 = l; mph_gc_push_root(ctx, (void**)&_obj_588); mph_int _ret_589 = _obj_588->column; mph_gc_pop_roots(ctx, 1); _ret_589; })); mph_gc_pop_roots(ctx, 1); _ret_590; });
	return tok;
}
	} else {
{
	tok = ({ MorphString* _arg_591 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_591); mph_token_Token* _ret_596 = mph_token_MakeToken(ctx, NULL, mph_token_TOKEN_ILLEGAL, _arg_591, ({ mph_lexer_Lexer* _obj_592 = l; mph_gc_push_root(ctx, (void**)&_obj_592); mph_int _ret_593 = _obj_592->line; mph_gc_pop_roots(ctx, 1); _ret_593; }), ({ mph_lexer_Lexer* _obj_594 = l; mph_gc_push_root(ctx, (void**)&_obj_594); mph_int _ret_595 = _obj_594->column; mph_gc_pop_roots(ctx, 1); _ret_595; })); mph_gc_pop_roots(ctx, 1); _ret_596; });
}
	}
}
	}
}
	}
	({ mph_lexer_Lexer* _arg_597 = l; mph_gc_push_root(ctx, (void**)&_arg_597); mph_lexer_lexer_read_char(ctx, NULL, _arg_597); mph_gc_pop_roots(ctx, 1); });
	return tok;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_Parser* mph_NewParser(MorphContext* ctx, void* _env_void, mph_lexer_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_Parser* p = ({ mph_Parser* _t = (mph_Parser*)mph_alloc(ctx, sizeof(mph_Parser), &mph_ti_mph_Parser); mph_gc_push_root(ctx, (void**)&_t); _t->lexer = l; _t->errors_count = 0; _t->current_token = ({ MorphString* _arg_598 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_arg_598); mph_token_Token* _ret_599 = mph_token_MakeToken(ctx, NULL, 0, _arg_598, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_599; }); _t->peek_token = ({ MorphString* _arg_600 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_arg_600); mph_token_Token* _ret_601 = mph_token_MakeToken(ctx, NULL, 0, _arg_600, 0, 0); mph_gc_pop_roots(ctx, 1); _ret_601; }); mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_push_root(ctx, (void**)&p);
	({ mph_Parser* _arg_602 = p; mph_gc_push_root(ctx, (void**)&_arg_602); mph_ParserNextToken(ctx, NULL, _arg_602); mph_gc_pop_roots(ctx, 1); });
	({ mph_Parser* _arg_603 = p; mph_gc_push_root(ctx, (void**)&_arg_603); mph_ParserNextToken(ctx, NULL, _arg_603); mph_gc_pop_roots(ctx, 1); });
	return p;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

void mph_ParserNextToken(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	({ mph_Parser* _obj_606 = p; mph_gc_push_root(ctx, (void**)&_obj_606); mph_token_Token* _val_607 = ({ mph_Parser* _obj_604 = p; mph_gc_push_root(ctx, (void**)&_obj_604); mph_token_Token* _ret_605 = _obj_604->peek_token; mph_gc_pop_roots(ctx, 1); _ret_605; }); mph_gc_push_root(ctx, (void**)&_val_607); _obj_606->current_token = _val_607; mph_gc_pop_roots(ctx, 2); });
	({ mph_Parser* _obj_612 = p; mph_gc_push_root(ctx, (void**)&_obj_612); mph_token_Token* _val_613 = ({ mph_lexer_Lexer* _arg_610 = ({ mph_Parser* _obj_608 = p; mph_gc_push_root(ctx, (void**)&_obj_608); mph_lexer_Lexer* _ret_609 = _obj_608->lexer; mph_gc_pop_roots(ctx, 1); _ret_609; }); mph_gc_push_root(ctx, (void**)&_arg_610); mph_token_Token* _ret_611 = mph_lexer_LexerNextToken(ctx, NULL, _arg_610); mph_gc_pop_roots(ctx, 1); _ret_611; }); mph_gc_push_root(ctx, (void**)&_val_613); _obj_612->peek_token = _val_613; mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_ParserCurrentTokenIs(MorphContext* ctx, void* _env_void, mph_Parser* p, mph_int token_type) {
	mph_gc_push_root(ctx, (void**)&p);
	return (({ mph_token_Token* _obj_616 = ({ mph_Parser* _obj_614 = p; mph_gc_push_root(ctx, (void**)&_obj_614); mph_token_Token* _ret_615 = _obj_614->current_token; mph_gc_pop_roots(ctx, 1); _ret_615; }); mph_gc_push_root(ctx, (void**)&_obj_616); mph_int _ret_617 = _obj_616->token_type; mph_gc_pop_roots(ctx, 1); _ret_617; }) == token_type);
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_ParserPeekTokenIs(MorphContext* ctx, void* _env_void, mph_Parser* p, mph_int token_type) {
	mph_gc_push_root(ctx, (void**)&p);
	return (({ mph_token_Token* _obj_620 = ({ mph_Parser* _obj_618 = p; mph_gc_push_root(ctx, (void**)&_obj_618); mph_token_Token* _ret_619 = _obj_618->peek_token; mph_gc_pop_roots(ctx, 1); _ret_619; }); mph_gc_push_root(ctx, (void**)&_obj_620); mph_int _ret_621 = _obj_620->token_type; mph_gc_pop_roots(ctx, 1); _ret_621; }) == token_type);
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_ParserExpectPeek(MorphContext* ctx, void* _env_void, mph_Parser* p, mph_int token_type) {
	mph_gc_push_root(ctx, (void**)&p);
	if ((({ mph_Parser* _arg_622 = p; mph_gc_push_root(ctx, (void**)&_arg_622); mph_bool _ret_623 = mph_ParserPeekTokenIs(ctx, NULL, _arg_622, token_type); mph_gc_pop_roots(ctx, 1); _ret_623; }) == 1)) {
{
	({ mph_Parser* _arg_624 = p; mph_gc_push_root(ctx, (void**)&_arg_624); mph_ParserNextToken(ctx, NULL, _arg_624); mph_gc_pop_roots(ctx, 1); });
	return 1;
}
	} else {
{
	({ mph_Parser* _obj_627 = p; mph_gc_push_root(ctx, (void**)&_obj_627); _obj_627->errors_count = (({ mph_Parser* _obj_625 = p; mph_gc_push_root(ctx, (void**)&_obj_625); mph_int _ret_626 = _obj_625->errors_count; mph_gc_pop_roots(ctx, 1); _ret_626; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return 0;
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_GetTokenPrecedence(MorphContext* ctx, void* _env_void, mph_int token_type) {
	if ((token_type == mph_token_TOKEN_EQ)) {
{
	return mph_PRECEDENCE_EQUALS;
}
	}
	if ((token_type == mph_token_TOKEN_NOT_EQ)) {
{
	return mph_PRECEDENCE_EQUALS;
}
	}
	if ((token_type == mph_token_TOKEN_LT)) {
{
	return mph_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_GT)) {
{
	return mph_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_LE)) {
{
	return mph_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_GE)) {
{
	return mph_PRECEDENCE_LESSGREATER;
}
	}
	if ((token_type == mph_token_TOKEN_PLUS)) {
{
	return mph_PRECEDENCE_SUM;
}
	}
	if ((token_type == mph_token_TOKEN_MINUS)) {
{
	return mph_PRECEDENCE_SUM;
}
	}
	if ((token_type == mph_token_TOKEN_SLASH)) {
{
	return mph_PRECEDENCE_PRODUCT;
}
	}
	if ((token_type == mph_token_TOKEN_ASTERISK)) {
{
	return mph_PRECEDENCE_PRODUCT;
}
	}
	if ((token_type == mph_token_TOKEN_PERCENT)) {
{
	return mph_PRECEDENCE_PRODUCT;
}
	}
	if ((token_type == mph_token_TOKEN_LPAREN)) {
{
	return mph_PRECEDENCE_CALL;
}
	}
	return mph_PRECEDENCE_LOWEST;
}

mph_int mph_ParserPeekPrecedence(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return mph_GetTokenPrecedence(ctx, NULL, ({ mph_token_Token* _obj_630 = ({ mph_Parser* _obj_628 = p; mph_gc_push_root(ctx, (void**)&_obj_628); mph_token_Token* _ret_629 = _obj_628->peek_token; mph_gc_pop_roots(ctx, 1); _ret_629; }); mph_gc_push_root(ctx, (void**)&_obj_630); mph_int _ret_631 = _obj_630->token_type; mph_gc_pop_roots(ctx, 1); _ret_631; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_ParserCurrentPrecedence(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return mph_GetTokenPrecedence(ctx, NULL, ({ mph_token_Token* _obj_634 = ({ mph_Parser* _obj_632 = p; mph_gc_push_root(ctx, (void**)&_obj_632); mph_token_Token* _ret_633 = _obj_632->current_token; mph_gc_pop_roots(ctx, 1); _ret_633; }); mph_gc_push_root(ctx, (void**)&_obj_634); mph_int _ret_635 = _obj_634->token_type; mph_gc_pop_roots(ctx, 1); _ret_635; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Identifier* mph_ParseIdentifier(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return ({ MorphString* _arg_640 = ({ mph_token_Token* _obj_638 = ({ mph_Parser* _obj_636 = p; mph_gc_push_root(ctx, (void**)&_obj_636); mph_token_Token* _ret_637 = _obj_636->current_token; mph_gc_pop_roots(ctx, 1); _ret_637; }); mph_gc_push_root(ctx, (void**)&_obj_638); MorphString* _ret_639 = _obj_638->literal; mph_gc_pop_roots(ctx, 1); _ret_639; }); mph_gc_push_root(ctx, (void**)&_arg_640); mph_ast_Identifier* _ret_649 = mph_ast_MakeIdentifier(ctx, NULL, _arg_640, ({ mph_token_Token* _obj_643 = ({ mph_Parser* _obj_641 = p; mph_gc_push_root(ctx, (void**)&_obj_641); mph_token_Token* _ret_642 = _obj_641->current_token; mph_gc_pop_roots(ctx, 1); _ret_642; }); mph_gc_push_root(ctx, (void**)&_obj_643); mph_int _ret_644 = _obj_643->line; mph_gc_pop_roots(ctx, 1); _ret_644; }), ({ mph_token_Token* _obj_647 = ({ mph_Parser* _obj_645 = p; mph_gc_push_root(ctx, (void**)&_obj_645); mph_token_Token* _ret_646 = _obj_645->current_token; mph_gc_pop_roots(ctx, 1); _ret_646; }); mph_gc_push_root(ctx, (void**)&_obj_647); mph_int _ret_648 = _obj_647->column; mph_gc_pop_roots(ctx, 1); _ret_648; })); mph_gc_pop_roots(ctx, 1); _ret_649; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_IntegerLiteral* mph_ParseIntegerLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_int value = ({ MorphString* _arg_654 = ({ mph_token_Token* _obj_652 = ({ mph_Parser* _obj_650 = p; mph_gc_push_root(ctx, (void**)&_obj_650); mph_token_Token* _ret_651 = _obj_650->current_token; mph_gc_pop_roots(ctx, 1); _ret_651; }); mph_gc_push_root(ctx, (void**)&_obj_652); MorphString* _ret_653 = _obj_652->literal; mph_gc_pop_roots(ctx, 1); _ret_653; }); mph_gc_push_root(ctx, (void**)&_arg_654); mph_int _ret_655 = mph_StringToInt(ctx, NULL, _arg_654); mph_gc_pop_roots(ctx, 1); _ret_655; });
	return ({ MorphString* _arg_660 = ({ mph_token_Token* _obj_658 = ({ mph_Parser* _obj_656 = p; mph_gc_push_root(ctx, (void**)&_obj_656); mph_token_Token* _ret_657 = _obj_656->current_token; mph_gc_pop_roots(ctx, 1); _ret_657; }); mph_gc_push_root(ctx, (void**)&_obj_658); MorphString* _ret_659 = _obj_658->literal; mph_gc_pop_roots(ctx, 1); _ret_659; }); mph_gc_push_root(ctx, (void**)&_arg_660); mph_ast_IntegerLiteral* _ret_669 = mph_ast_MakeIntegerLiteral(ctx, NULL, value, _arg_660, ({ mph_token_Token* _obj_663 = ({ mph_Parser* _obj_661 = p; mph_gc_push_root(ctx, (void**)&_obj_661); mph_token_Token* _ret_662 = _obj_661->current_token; mph_gc_pop_roots(ctx, 1); _ret_662; }); mph_gc_push_root(ctx, (void**)&_obj_663); mph_int _ret_664 = _obj_663->line; mph_gc_pop_roots(ctx, 1); _ret_664; }), ({ mph_token_Token* _obj_667 = ({ mph_Parser* _obj_665 = p; mph_gc_push_root(ctx, (void**)&_obj_665); mph_token_Token* _ret_666 = _obj_665->current_token; mph_gc_pop_roots(ctx, 1); _ret_666; }); mph_gc_push_root(ctx, (void**)&_obj_667); mph_int _ret_668 = _obj_667->column; mph_gc_pop_roots(ctx, 1); _ret_668; })); mph_gc_pop_roots(ctx, 1); _ret_669; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StringLiteral* mph_ParseStringLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return ({ MorphString* _arg_674 = ({ mph_token_Token* _obj_672 = ({ mph_Parser* _obj_670 = p; mph_gc_push_root(ctx, (void**)&_obj_670); mph_token_Token* _ret_671 = _obj_670->current_token; mph_gc_pop_roots(ctx, 1); _ret_671; }); mph_gc_push_root(ctx, (void**)&_obj_672); MorphString* _ret_673 = _obj_672->literal; mph_gc_pop_roots(ctx, 1); _ret_673; }); mph_gc_push_root(ctx, (void**)&_arg_674); mph_ast_StringLiteral* _ret_683 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_674, ({ mph_token_Token* _obj_677 = ({ mph_Parser* _obj_675 = p; mph_gc_push_root(ctx, (void**)&_obj_675); mph_token_Token* _ret_676 = _obj_675->current_token; mph_gc_pop_roots(ctx, 1); _ret_676; }); mph_gc_push_root(ctx, (void**)&_obj_677); mph_int _ret_678 = _obj_677->line; mph_gc_pop_roots(ctx, 1); _ret_678; }), ({ mph_token_Token* _obj_681 = ({ mph_Parser* _obj_679 = p; mph_gc_push_root(ctx, (void**)&_obj_679); mph_token_Token* _ret_680 = _obj_679->current_token; mph_gc_pop_roots(ctx, 1); _ret_680; }); mph_gc_push_root(ctx, (void**)&_obj_681); mph_int _ret_682 = _obj_681->column; mph_gc_pop_roots(ctx, 1); _ret_682; })); mph_gc_pop_roots(ctx, 1); _ret_683; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BooleanLiteral* mph_ParseBooleanLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_bool value = ({ mph_Parser* _arg_684 = p; mph_gc_push_root(ctx, (void**)&_arg_684); mph_bool _ret_685 = mph_ParserCurrentTokenIs(ctx, NULL, _arg_684, mph_token_TOKEN_BENAR); mph_gc_pop_roots(ctx, 1); _ret_685; });
	return ({ MorphString* _arg_690 = ({ mph_token_Token* _obj_688 = ({ mph_Parser* _obj_686 = p; mph_gc_push_root(ctx, (void**)&_obj_686); mph_token_Token* _ret_687 = _obj_686->current_token; mph_gc_pop_roots(ctx, 1); _ret_687; }); mph_gc_push_root(ctx, (void**)&_obj_688); MorphString* _ret_689 = _obj_688->literal; mph_gc_pop_roots(ctx, 1); _ret_689; }); mph_gc_push_root(ctx, (void**)&_arg_690); mph_ast_BooleanLiteral* _ret_699 = mph_ast_MakeBooleanLiteral(ctx, NULL, value, _arg_690, ({ mph_token_Token* _obj_693 = ({ mph_Parser* _obj_691 = p; mph_gc_push_root(ctx, (void**)&_obj_691); mph_token_Token* _ret_692 = _obj_691->current_token; mph_gc_pop_roots(ctx, 1); _ret_692; }); mph_gc_push_root(ctx, (void**)&_obj_693); mph_int _ret_694 = _obj_693->line; mph_gc_pop_roots(ctx, 1); _ret_694; }), ({ mph_token_Token* _obj_697 = ({ mph_Parser* _obj_695 = p; mph_gc_push_root(ctx, (void**)&_obj_695); mph_token_Token* _ret_696 = _obj_695->current_token; mph_gc_pop_roots(ctx, 1); _ret_696; }); mph_gc_push_root(ctx, (void**)&_obj_697); mph_int _ret_698 = _obj_697->column; mph_gc_pop_roots(ctx, 1); _ret_698; })); mph_gc_pop_roots(ctx, 1); _ret_699; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_FloatLiteral* mph_ParseFloatLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return ({ MorphString* _arg_704 = ({ mph_token_Token* _obj_702 = ({ mph_Parser* _obj_700 = p; mph_gc_push_root(ctx, (void**)&_obj_700); mph_token_Token* _ret_701 = _obj_700->current_token; mph_gc_pop_roots(ctx, 1); _ret_701; }); mph_gc_push_root(ctx, (void**)&_obj_702); MorphString* _ret_703 = _obj_702->literal; mph_gc_pop_roots(ctx, 1); _ret_703; }); mph_gc_push_root(ctx, (void**)&_arg_704); mph_ast_FloatLiteral* _ret_713 = mph_ast_MakeFloatLiteral(ctx, NULL, _arg_704, ({ mph_token_Token* _obj_707 = ({ mph_Parser* _obj_705 = p; mph_gc_push_root(ctx, (void**)&_obj_705); mph_token_Token* _ret_706 = _obj_705->current_token; mph_gc_pop_roots(ctx, 1); _ret_706; }); mph_gc_push_root(ctx, (void**)&_obj_707); mph_int _ret_708 = _obj_707->line; mph_gc_pop_roots(ctx, 1); _ret_708; }), ({ mph_token_Token* _obj_711 = ({ mph_Parser* _obj_709 = p; mph_gc_push_root(ctx, (void**)&_obj_709); mph_token_Token* _ret_710 = _obj_709->current_token; mph_gc_pop_roots(ctx, 1); _ret_710; }); mph_gc_push_root(ctx, (void**)&_obj_711); mph_int _ret_712 = _obj_711->column; mph_gc_pop_roots(ctx, 1); _ret_712; })); mph_gc_pop_roots(ctx, 1); _ret_713; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CharLiteral* mph_ParseCharLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_int value = ({ MorphString* _arg_718 = ({ mph_token_Token* _obj_716 = ({ mph_Parser* _obj_714 = p; mph_gc_push_root(ctx, (void**)&_obj_714); mph_token_Token* _ret_715 = _obj_714->current_token; mph_gc_pop_roots(ctx, 1); _ret_715; }); mph_gc_push_root(ctx, (void**)&_obj_716); MorphString* _ret_717 = _obj_716->literal; mph_gc_pop_roots(ctx, 1); _ret_717; }); mph_gc_push_root(ctx, (void**)&_arg_718); mph_int _ret_719 = mph_lexer_CharToAscii(ctx, NULL, _arg_718); mph_gc_pop_roots(ctx, 1); _ret_719; });
	return ({ MorphString* _arg_724 = ({ mph_token_Token* _obj_722 = ({ mph_Parser* _obj_720 = p; mph_gc_push_root(ctx, (void**)&_obj_720); mph_token_Token* _ret_721 = _obj_720->current_token; mph_gc_pop_roots(ctx, 1); _ret_721; }); mph_gc_push_root(ctx, (void**)&_obj_722); MorphString* _ret_723 = _obj_722->literal; mph_gc_pop_roots(ctx, 1); _ret_723; }); mph_gc_push_root(ctx, (void**)&_arg_724); mph_ast_CharLiteral* _ret_733 = mph_ast_MakeCharLiteral(ctx, NULL, value, _arg_724, ({ mph_token_Token* _obj_727 = ({ mph_Parser* _obj_725 = p; mph_gc_push_root(ctx, (void**)&_obj_725); mph_token_Token* _ret_726 = _obj_725->current_token; mph_gc_pop_roots(ctx, 1); _ret_726; }); mph_gc_push_root(ctx, (void**)&_obj_727); mph_int _ret_728 = _obj_727->line; mph_gc_pop_roots(ctx, 1); _ret_728; }), ({ mph_token_Token* _obj_731 = ({ mph_Parser* _obj_729 = p; mph_gc_push_root(ctx, (void**)&_obj_729); mph_token_Token* _ret_730 = _obj_729->current_token; mph_gc_pop_roots(ctx, 1); _ret_730; }); mph_gc_push_root(ctx, (void**)&_obj_731); mph_int _ret_732 = _obj_731->column; mph_gc_pop_roots(ctx, 1); _ret_732; })); mph_gc_pop_roots(ctx, 1); _ret_733; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_NullLiteral* mph_ParseNullLiteral(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return mph_ast_MakeNullLiteral(ctx, NULL, ({ mph_token_Token* _obj_736 = ({ mph_Parser* _obj_734 = p; mph_gc_push_root(ctx, (void**)&_obj_734); mph_token_Token* _ret_735 = _obj_734->current_token; mph_gc_pop_roots(ctx, 1); _ret_735; }); mph_gc_push_root(ctx, (void**)&_obj_736); mph_int _ret_737 = _obj_736->line; mph_gc_pop_roots(ctx, 1); _ret_737; }), ({ mph_token_Token* _obj_740 = ({ mph_Parser* _obj_738 = p; mph_gc_push_root(ctx, (void**)&_obj_738); mph_token_Token* _ret_739 = _obj_738->current_token; mph_gc_pop_roots(ctx, 1); _ret_739; }); mph_gc_push_root(ctx, (void**)&_obj_740); mph_int _ret_741 = _obj_740->column; mph_gc_pop_roots(ctx, 1); _ret_741; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_PrefixExpression* mph_ParsePrefixExpression(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_ast_PrefixExpression* expr = ({ MorphString* _arg_746 = ({ mph_token_Token* _obj_744 = ({ mph_Parser* _obj_742 = p; mph_gc_push_root(ctx, (void**)&_obj_742); mph_token_Token* _ret_743 = _obj_742->current_token; mph_gc_pop_roots(ctx, 1); _ret_743; }); mph_gc_push_root(ctx, (void**)&_obj_744); MorphString* _ret_745 = _obj_744->literal; mph_gc_pop_roots(ctx, 1); _ret_745; }); mph_gc_push_root(ctx, (void**)&_arg_746); mph_ast_PrefixExpression* _ret_755 = mph_ast_MakePrefixExpression(ctx, NULL, _arg_746, ({ mph_token_Token* _obj_749 = ({ mph_Parser* _obj_747 = p; mph_gc_push_root(ctx, (void**)&_obj_747); mph_token_Token* _ret_748 = _obj_747->current_token; mph_gc_pop_roots(ctx, 1); _ret_748; }); mph_gc_push_root(ctx, (void**)&_obj_749); mph_int _ret_750 = _obj_749->line; mph_gc_pop_roots(ctx, 1); _ret_750; }), ({ mph_token_Token* _obj_753 = ({ mph_Parser* _obj_751 = p; mph_gc_push_root(ctx, (void**)&_obj_751); mph_token_Token* _ret_752 = _obj_751->current_token; mph_gc_pop_roots(ctx, 1); _ret_752; }); mph_gc_push_root(ctx, (void**)&_obj_753); mph_int _ret_754 = _obj_753->column; mph_gc_pop_roots(ctx, 1); _ret_754; })); mph_gc_pop_roots(ctx, 1); _ret_755; });
	mph_gc_push_root(ctx, (void**)&expr);
	({ mph_Parser* _arg_756 = p; mph_gc_push_root(ctx, (void**)&_arg_756); mph_ParserNextToken(ctx, NULL, _arg_756); mph_gc_pop_roots(ctx, 1); });
	return expr;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_VarStatement* mph_ParseVarStatement(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_int line = ({ mph_token_Token* _obj_759 = ({ mph_Parser* _obj_757 = p; mph_gc_push_root(ctx, (void**)&_obj_757); mph_token_Token* _ret_758 = _obj_757->current_token; mph_gc_pop_roots(ctx, 1); _ret_758; }); mph_gc_push_root(ctx, (void**)&_obj_759); mph_int _ret_760 = _obj_759->line; mph_gc_pop_roots(ctx, 1); _ret_760; });
	mph_int column = ({ mph_token_Token* _obj_763 = ({ mph_Parser* _obj_761 = p; mph_gc_push_root(ctx, (void**)&_obj_761); mph_token_Token* _ret_762 = _obj_761->current_token; mph_gc_pop_roots(ctx, 1); _ret_762; }); mph_gc_push_root(ctx, (void**)&_obj_763); mph_int _ret_764 = _obj_763->column; mph_gc_pop_roots(ctx, 1); _ret_764; });
	if ((({ mph_Parser* _arg_765 = p; mph_gc_push_root(ctx, (void**)&_arg_765); mph_bool _ret_766 = mph_ParserExpectPeek(ctx, NULL, _arg_765, mph_token_TOKEN_IDENT); mph_gc_pop_roots(ctx, 1); _ret_766; }) == 0)) {
{
	return ({ MorphString* _arg_767 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_767); MorphString* _arg_768 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_768); mph_ast_VarStatement* _ret_769 = mph_ast_MakeVarStatement(ctx, NULL, _arg_767, _arg_768, line, column); mph_gc_pop_roots(ctx, 2); _ret_769; });
}
	}
	MorphString* name = ({ mph_token_Token* _obj_772 = ({ mph_Parser* _obj_770 = p; mph_gc_push_root(ctx, (void**)&_obj_770); mph_token_Token* _ret_771 = _obj_770->current_token; mph_gc_pop_roots(ctx, 1); _ret_771; }); mph_gc_push_root(ctx, (void**)&_obj_772); MorphString* _ret_773 = _obj_772->literal; mph_gc_pop_roots(ctx, 1); _ret_773; });
	mph_gc_push_root(ctx, (void**)&name);
	MorphString* type_str = mph_string_new(ctx, "-");
	mph_gc_push_root(ctx, (void**)&type_str);
	if ((({ mph_Parser* _arg_774 = p; mph_gc_push_root(ctx, (void**)&_arg_774); mph_bool _ret_775 = mph_ParserPeekTokenIs(ctx, NULL, _arg_774, mph_token_TOKEN_COLON); mph_gc_pop_roots(ctx, 1); _ret_775; }) == 1)) {
{
	({ mph_Parser* _arg_776 = p; mph_gc_push_root(ctx, (void**)&_arg_776); mph_ParserNextToken(ctx, NULL, _arg_776); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_Parser* _arg_777 = p; mph_gc_push_root(ctx, (void**)&_arg_777); mph_bool _ret_778 = mph_ParserExpectPeek(ctx, NULL, _arg_777, mph_token_TOKEN_IDENT); mph_gc_pop_roots(ctx, 1); _ret_778; }) == 1)) {
{
	type_str = ({ mph_token_Token* _obj_781 = ({ mph_Parser* _obj_779 = p; mph_gc_push_root(ctx, (void**)&_obj_779); mph_token_Token* _ret_780 = _obj_779->current_token; mph_gc_pop_roots(ctx, 1); _ret_780; }); mph_gc_push_root(ctx, (void**)&_obj_781); MorphString* _ret_782 = _obj_781->literal; mph_gc_pop_roots(ctx, 1); _ret_782; });
}
	}
}
	}
	mph_ast_VarStatement* stmt = ({ MorphString* _arg_783 = name; mph_gc_push_root(ctx, (void**)&_arg_783); MorphString* _arg_784 = type_str; mph_gc_push_root(ctx, (void**)&_arg_784); mph_ast_VarStatement* _ret_785 = mph_ast_MakeVarStatement(ctx, NULL, _arg_783, _arg_784, line, column); mph_gc_pop_roots(ctx, 2); _ret_785; });
	mph_gc_push_root(ctx, (void**)&stmt);
	if ((({ mph_Parser* _arg_786 = p; mph_gc_push_root(ctx, (void**)&_arg_786); mph_bool _ret_787 = mph_ParserPeekTokenIs(ctx, NULL, _arg_786, mph_token_TOKEN_ASSIGN); mph_gc_pop_roots(ctx, 1); _ret_787; }) == 1)) {
{
	({ mph_Parser* _arg_788 = p; mph_gc_push_root(ctx, (void**)&_arg_788); mph_ParserNextToken(ctx, NULL, _arg_788); mph_gc_pop_roots(ctx, 1); });
	({ mph_Parser* _arg_789 = p; mph_gc_push_root(ctx, (void**)&_arg_789); mph_ParserNextToken(ctx, NULL, _arg_789); mph_gc_pop_roots(ctx, 1); });
	({ mph_ast_VarStatement* _obj_790 = stmt; mph_gc_push_root(ctx, (void**)&_obj_790); _obj_790->has_value = 1; mph_gc_pop_roots(ctx, 1); });
	({ mph_ast_VarStatement* _obj_795 = stmt; mph_gc_push_root(ctx, (void**)&_obj_795); MorphString* _val_796 = ({ mph_token_Token* _obj_793 = ({ mph_Parser* _obj_791 = p; mph_gc_push_root(ctx, (void**)&_obj_791); mph_token_Token* _ret_792 = _obj_791->current_token; mph_gc_pop_roots(ctx, 1); _ret_792; }); mph_gc_push_root(ctx, (void**)&_obj_793); MorphString* _ret_794 = _obj_793->literal; mph_gc_pop_roots(ctx, 1); _ret_794; }); mph_gc_push_root(ctx, (void**)&_val_796); _obj_795->value_literal = _val_796; mph_gc_pop_roots(ctx, 2); });
	({ mph_ast_VarStatement* _obj_801 = stmt; mph_gc_push_root(ctx, (void**)&_obj_801); _obj_801->value_token_type = ({ mph_token_Token* _obj_799 = ({ mph_Parser* _obj_797 = p; mph_gc_push_root(ctx, (void**)&_obj_797); mph_token_Token* _ret_798 = _obj_797->current_token; mph_gc_pop_roots(ctx, 1); _ret_798; }); mph_gc_push_root(ctx, (void**)&_obj_799); mph_int _ret_800 = _obj_799->token_type; mph_gc_pop_roots(ctx, 1); _ret_800; }); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_bool should_continue = 1;
	while ((should_continue == 1)) {
{
	if ((({ mph_Parser* _arg_802 = p; mph_gc_push_root(ctx, (void**)&_arg_802); mph_bool _ret_803 = mph_ParserCurrentTokenIs(ctx, NULL, _arg_802, mph_token_TOKEN_SEMICOLON); mph_gc_pop_roots(ctx, 1); _ret_803; }) == 1)) {
{
	should_continue = 0;
}
	} else {
{
	if ((({ mph_Parser* _arg_804 = p; mph_gc_push_root(ctx, (void**)&_arg_804); mph_bool _ret_805 = mph_ParserCurrentTokenIs(ctx, NULL, _arg_804, mph_token_TOKEN_EOF); mph_gc_pop_roots(ctx, 1); _ret_805; }) == 1)) {
{
	should_continue = 0;
}
	} else {
{
	({ mph_Parser* _arg_806 = p; mph_gc_push_root(ctx, (void**)&_arg_806); mph_ParserNextToken(ctx, NULL, _arg_806); mph_gc_pop_roots(ctx, 1); });
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

mph_ast_Program* mph_ParseProgram(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	mph_ast_Program* program = mph_ast_MakeProgram(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&program);
	while ((({ mph_Parser* _arg_807 = p; mph_gc_push_root(ctx, (void**)&_arg_807); mph_bool _ret_808 = mph_ParserCurrentTokenIs(ctx, NULL, _arg_807, mph_token_TOKEN_EOF); mph_gc_pop_roots(ctx, 1); _ret_808; }) == 0)) {
{
	if ((({ mph_Parser* _arg_809 = p; mph_gc_push_root(ctx, (void**)&_arg_809); mph_bool _ret_810 = mph_ParserCurrentTokenIs(ctx, NULL, _arg_809, mph_token_TOKEN_VAR); mph_gc_pop_roots(ctx, 1); _ret_810; }) == 1)) {
{
	mph_ast_VarStatement* stmt = ({ mph_Parser* _arg_811 = p; mph_gc_push_root(ctx, (void**)&_arg_811); mph_ast_VarStatement* _ret_812 = mph_ParseVarStatement(ctx, NULL, _arg_811); mph_gc_pop_roots(ctx, 1); _ret_812; });
	mph_gc_push_root(ctx, (void**)&stmt);
	({ mph_ast_Program* _obj_815 = program; mph_gc_push_root(ctx, (void**)&_obj_815); _obj_815->statements_count = (({ mph_ast_Program* _obj_813 = program; mph_gc_push_root(ctx, (void**)&_obj_813); mph_int _ret_814 = _obj_813->statements_count; mph_gc_pop_roots(ctx, 1); _ret_814; }) + 1); mph_gc_pop_roots(ctx, 1); });
	({ mph_ast_Program* _obj_818 = program; mph_gc_push_root(ctx, (void**)&_obj_818); _obj_818->var_statements_count = (({ mph_ast_Program* _obj_816 = program; mph_gc_push_root(ctx, (void**)&_obj_816); mph_int _ret_817 = _obj_816->var_statements_count; mph_gc_pop_roots(ctx, 1); _ret_817; }) + 1); mph_gc_pop_roots(ctx, 1); });
	({ mph_ast_Program* _obj_819 = program; mph_gc_push_root(ctx, (void**)&_obj_819); mph_ast_VarStatement* _val_820 = stmt; mph_gc_push_root(ctx, (void**)&_val_820); _obj_819->var_statement = _val_820; mph_gc_pop_roots(ctx, 2); });
	({ mph_ast_Program* _obj_821 = program; mph_gc_push_root(ctx, (void**)&_obj_821); _obj_821->has_var_statement = 1; mph_gc_pop_roots(ctx, 1); });
	mph_native_print(ctx, mph_string_new(ctx, "Parsed VarStatement: "));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_822 = stmt; mph_gc_push_root(ctx, (void**)&_obj_822); MorphString* _ret_823 = _obj_822->name; mph_gc_pop_roots(ctx, 1); _ret_823; }));
	if ((({ mph_ast_VarStatement* _obj_824 = stmt; mph_gc_push_root(ctx, (void**)&_obj_824); MorphString* _ret_825 = _obj_824->value_type; mph_gc_pop_roots(ctx, 1); _ret_825; }) != mph_string_new(ctx, "-"))) {
{
	mph_native_print(ctx, mph_string_new(ctx, " : "));
	mph_native_print(ctx, ({ mph_ast_VarStatement* _obj_826 = stmt; mph_gc_push_root(ctx, (void**)&_obj_826); MorphString* _ret_827 = _obj_826->value_type; mph_gc_pop_roots(ctx, 1); _ret_827; }));
}
	}
	if ((({ mph_ast_VarStatement* _obj_828 = stmt; mph_gc_push_root(ctx, (void**)&_obj_828); mph_bool _ret_829 = _obj_828->has_value; mph_gc_pop_roots(ctx, 1); _ret_829; }) == 1)) {
{
	mph_native_print(ctx, mph_string_new(ctx, " = <expression>"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}
	}
	({ mph_Parser* _arg_830 = p; mph_gc_push_root(ctx, (void**)&_arg_830); mph_ParserNextToken(ctx, NULL, _arg_830); mph_gc_pop_roots(ctx, 1); });
}
	}
	return program;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_StringToInt(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	mph_int length = ({ MorphString* _len_arg_831 = s; mph_gc_push_root(ctx, (void**)&_len_arg_831); mph_int _ret_832 = ((MorphString*)_len_arg_831)->length; mph_gc_pop_roots(ctx, 1); _ret_832; });
	if ((length == 0)) {
{
	return 0;
}
	}
	mph_int i = 0;
	mph_int sign = 1;
	if (mph_string_eq(ctx, mph_string_substring(ctx, s, 0, 1), mph_string_new(ctx, "-"))) {
{
	sign = (-1);
	i = 1;
}
	}
	mph_int result = 0;
	while ((i < length)) {
{
	MorphString* ch = mph_string_substring(ctx, s, i, (i + 1));
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "0"))) {
{
	result = ((result * 10) + 0);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "1"))) {
{
	result = ((result * 10) + 1);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "2"))) {
{
	result = ((result * 10) + 2);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "3"))) {
{
	result = ((result * 10) + 3);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "4"))) {
{
	result = ((result * 10) + 4);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "5"))) {
{
	result = ((result * 10) + 5);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "6"))) {
{
	result = ((result * 10) + 6);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "7"))) {
{
	result = ((result * 10) + 7);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "8"))) {
{
	result = ((result * 10) + 8);
}
	} else if (mph_string_eq(ctx, ch, mph_string_new(ctx, "9"))) {
{
	result = ((result * 10) + 9);
}
	} else {
{
	return 0;
}
	}
	i = (i + 1);
	mph_gc_pop_roots(ctx, 1);
}
	}
	return (result * sign);
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_ParserHasErrors(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	return (({ mph_Parser* _obj_833 = p; mph_gc_push_root(ctx, (void**)&_obj_833); mph_int _ret_834 = _obj_833->errors_count; mph_gc_pop_roots(ctx, 1); _ret_834; }) > 0);
	mph_gc_pop_roots(ctx, 1);
}

void mph_ParserPrintErrors(MorphContext* ctx, void* _env_void, mph_Parser* p) {
	mph_gc_push_root(ctx, (void**)&p);
	if ((({ mph_Parser* _obj_835 = p; mph_gc_push_root(ctx, (void**)&_obj_835); mph_int _ret_836 = _obj_835->errors_count; mph_gc_pop_roots(ctx, 1); _ret_836; }) > 0)) {
{
	mph_native_print(ctx, mph_string_new(ctx, "Parser has "));
	mph_native_print_int(ctx, ({ mph_Parser* _obj_837 = p; mph_gc_push_root(ctx, (void**)&_obj_837); mph_int _ret_838 = _obj_837->errors_count; mph_gc_pop_roots(ctx, 1); _ret_838; }));
	mph_native_print(ctx, mph_string_new(ctx, " error(s)\n"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "No parser errors\n"));
}
	}
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
	mph_PRECEDENCE_LOWEST = 1;
	mph_PRECEDENCE_EQUALS = 2;
	mph_PRECEDENCE_LESSGREATER = 3;
	mph_PRECEDENCE_SUM = 4;
	mph_PRECEDENCE_PRODUCT = 5;
	mph_PRECEDENCE_PREFIX = 6;
	mph_PRECEDENCE_CALL = 7;
}
