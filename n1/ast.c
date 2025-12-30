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
#define MPH_TYPE_mph_SwitchStatement 22
#define MPH_TYPE_mph_StructStatement 24
#define MPH_TYPE_mph_ContinueStatement 27
#define MPH_TYPE_mph_Identifier 8
#define MPH_TYPE_mph_IfExpression 17
#define MPH_TYPE_mph_WhileStatement 23
#define MPH_TYPE_mph_ImportStatement 25
#define MPH_TYPE_mph_BreakStatement 26
#define MPH_TYPE_mph_VarStatement 2
#define MPH_TYPE_mph_FunctionStatement 3
#define MPH_TYPE_mph_ReturnStatement 4
#define MPH_TYPE_mph_BlockStatement 6
#define MPH_TYPE_mph_Program 7
#define MPH_TYPE_mph_IntegerLiteral 9
#define MPH_TYPE_mph_InfixExpression 16
#define MPH_TYPE_mph_IndexExpression 19
#define MPH_TYPE_mph_Node 1
#define MPH_TYPE_mph_ExpressionStatement 5
#define MPH_TYPE_mph_StringLiteral 11
#define MPH_TYPE_mph_BooleanLiteral 12
#define MPH_TYPE_mph_CharLiteral 13
#define MPH_TYPE_mph_NullLiteral 14
#define MPH_TYPE_mph_CallExpression 18
#define MPH_TYPE_mph_CaseClause 21
#define MPH_TYPE_mph_FloatLiteral 10
#define MPH_TYPE_mph_PrefixExpression 15
#define MPH_TYPE_mph_MemberExpression 20

// Struct Definitions (Env & Types)
typedef struct mph_Node mph_Node;
typedef struct mph_VarStatement mph_VarStatement;
typedef struct mph_FunctionStatement mph_FunctionStatement;
typedef struct mph_ReturnStatement mph_ReturnStatement;
typedef struct mph_ExpressionStatement mph_ExpressionStatement;
typedef struct mph_BlockStatement mph_BlockStatement;
typedef struct mph_Program mph_Program;
typedef struct mph_Identifier mph_Identifier;
typedef struct mph_IntegerLiteral mph_IntegerLiteral;
typedef struct mph_FloatLiteral mph_FloatLiteral;
typedef struct mph_StringLiteral mph_StringLiteral;
typedef struct mph_BooleanLiteral mph_BooleanLiteral;
typedef struct mph_CharLiteral mph_CharLiteral;
typedef struct mph_NullLiteral mph_NullLiteral;
typedef struct mph_PrefixExpression mph_PrefixExpression;
typedef struct mph_InfixExpression mph_InfixExpression;
typedef struct mph_IfExpression mph_IfExpression;
typedef struct mph_CallExpression mph_CallExpression;
typedef struct mph_IndexExpression mph_IndexExpression;
typedef struct mph_MemberExpression mph_MemberExpression;
typedef struct mph_CaseClause mph_CaseClause;
typedef struct mph_SwitchStatement mph_SwitchStatement;
typedef struct mph_WhileStatement mph_WhileStatement;
typedef struct mph_StructStatement mph_StructStatement;
typedef struct mph_ImportStatement mph_ImportStatement;
typedef struct mph_BreakStatement mph_BreakStatement;
typedef struct mph_ContinueStatement mph_ContinueStatement;
struct mph_Node {
	mph_int node_type;
	MorphString* token_literal;
	mph_int line;
	mph_int column;
};

struct mph_VarStatement {
	mph_Node* base;
	MorphString* name;
	MorphString* value_type;
	mph_bool has_value;
	MorphString* value_literal;
	mph_int value_token_type;
};

struct mph_FunctionStatement {
	mph_Node* base;
	MorphString* name;
	mph_int parameters_count;
	MorphString* return_type;
};

struct mph_ReturnStatement {
	mph_Node* base;
	mph_bool has_value;
};

struct mph_ExpressionStatement {
	mph_Node* base;
};

struct mph_BlockStatement {
	mph_Node* base;
	mph_int statements_count;
};

struct mph_Program {
	mph_Node* base;
	mph_int statements_count;
	mph_int var_statements_count;
	mph_VarStatement* var_statement;
	mph_bool has_var_statement;
};

struct mph_Identifier {
	mph_Node* base;
	MorphString* value;
};

struct mph_IntegerLiteral {
	mph_Node* base;
	mph_int value;
};

struct mph_FloatLiteral {
	mph_Node* base;
	MorphString* value_str;
};

struct mph_StringLiteral {
	mph_Node* base;
	MorphString* value;
};

struct mph_BooleanLiteral {
	mph_Node* base;
	mph_bool value;
};

struct mph_CharLiteral {
	mph_Node* base;
	mph_int value;
};

struct mph_NullLiteral {
	mph_Node* base;
};

struct mph_PrefixExpression {
	mph_Node* base;
	MorphString* operator;
};

struct mph_InfixExpression {
	mph_Node* base;
	MorphString* operator;
};

struct mph_IfExpression {
	mph_Node* base;
	mph_bool has_alternative;
};

struct mph_CallExpression {
	mph_Node* base;
	mph_int arguments_count;
};

struct mph_IndexExpression {
	mph_Node* base;
};

struct mph_MemberExpression {
	mph_Node* base;
	MorphString* member_name;
};

struct mph_CaseClause {
	mph_Node* base;
	mph_int values_count;
	mph_int v0;
	mph_int v1;
	mph_int v2;
	mph_int v3;
	mph_bool has_body;
};

struct mph_SwitchStatement {
	mph_Node* base;
	mph_int cases_count;
	mph_bool has_default;
};

struct mph_WhileStatement {
	mph_Node* base;
	mph_bool has_body;
};

struct mph_StructStatement {
	mph_Node* base;
	MorphString* name;
	mph_int fields_count;
};

struct mph_ImportStatement {
	mph_Node* base;
	MorphString* path;
};

struct mph_BreakStatement {
	mph_Node* base;
};

struct mph_ContinueStatement {
	mph_Node* base;
};

MorphTypeInfo mph_ti_mph_Node = { "Node", sizeof(mph_Node), 1, (size_t[]){offsetof(mph_Node, token_literal)} };
MorphTypeInfo mph_ti_mph_VarStatement = { "VarStatement", sizeof(mph_VarStatement), 4, (size_t[]){offsetof(mph_VarStatement, base), offsetof(mph_VarStatement, name), offsetof(mph_VarStatement, value_type), offsetof(mph_VarStatement, value_literal)} };
MorphTypeInfo mph_ti_mph_FunctionStatement = { "FunctionStatement", sizeof(mph_FunctionStatement), 3, (size_t[]){offsetof(mph_FunctionStatement, base), offsetof(mph_FunctionStatement, name), offsetof(mph_FunctionStatement, return_type)} };
MorphTypeInfo mph_ti_mph_ReturnStatement = { "ReturnStatement", sizeof(mph_ReturnStatement), 1, (size_t[]){offsetof(mph_ReturnStatement, base)} };
MorphTypeInfo mph_ti_mph_ExpressionStatement = { "ExpressionStatement", sizeof(mph_ExpressionStatement), 1, (size_t[]){offsetof(mph_ExpressionStatement, base)} };
MorphTypeInfo mph_ti_mph_BlockStatement = { "BlockStatement", sizeof(mph_BlockStatement), 1, (size_t[]){offsetof(mph_BlockStatement, base)} };
MorphTypeInfo mph_ti_mph_Program = { "Program", sizeof(mph_Program), 2, (size_t[]){offsetof(mph_Program, base), offsetof(mph_Program, var_statement)} };
MorphTypeInfo mph_ti_mph_Identifier = { "Identifier", sizeof(mph_Identifier), 2, (size_t[]){offsetof(mph_Identifier, base), offsetof(mph_Identifier, value)} };
MorphTypeInfo mph_ti_mph_IntegerLiteral = { "IntegerLiteral", sizeof(mph_IntegerLiteral), 1, (size_t[]){offsetof(mph_IntegerLiteral, base)} };
MorphTypeInfo mph_ti_mph_FloatLiteral = { "FloatLiteral", sizeof(mph_FloatLiteral), 2, (size_t[]){offsetof(mph_FloatLiteral, base), offsetof(mph_FloatLiteral, value_str)} };
MorphTypeInfo mph_ti_mph_StringLiteral = { "StringLiteral", sizeof(mph_StringLiteral), 2, (size_t[]){offsetof(mph_StringLiteral, base), offsetof(mph_StringLiteral, value)} };
MorphTypeInfo mph_ti_mph_BooleanLiteral = { "BooleanLiteral", sizeof(mph_BooleanLiteral), 1, (size_t[]){offsetof(mph_BooleanLiteral, base)} };
MorphTypeInfo mph_ti_mph_CharLiteral = { "CharLiteral", sizeof(mph_CharLiteral), 1, (size_t[]){offsetof(mph_CharLiteral, base)} };
MorphTypeInfo mph_ti_mph_NullLiteral = { "NullLiteral", sizeof(mph_NullLiteral), 1, (size_t[]){offsetof(mph_NullLiteral, base)} };
MorphTypeInfo mph_ti_mph_PrefixExpression = { "PrefixExpression", sizeof(mph_PrefixExpression), 2, (size_t[]){offsetof(mph_PrefixExpression, base), offsetof(mph_PrefixExpression, operator)} };
MorphTypeInfo mph_ti_mph_InfixExpression = { "InfixExpression", sizeof(mph_InfixExpression), 2, (size_t[]){offsetof(mph_InfixExpression, base), offsetof(mph_InfixExpression, operator)} };
MorphTypeInfo mph_ti_mph_IfExpression = { "IfExpression", sizeof(mph_IfExpression), 1, (size_t[]){offsetof(mph_IfExpression, base)} };
MorphTypeInfo mph_ti_mph_CallExpression = { "CallExpression", sizeof(mph_CallExpression), 1, (size_t[]){offsetof(mph_CallExpression, base)} };
MorphTypeInfo mph_ti_mph_IndexExpression = { "IndexExpression", sizeof(mph_IndexExpression), 1, (size_t[]){offsetof(mph_IndexExpression, base)} };
MorphTypeInfo mph_ti_mph_MemberExpression = { "MemberExpression", sizeof(mph_MemberExpression), 2, (size_t[]){offsetof(mph_MemberExpression, base), offsetof(mph_MemberExpression, member_name)} };
MorphTypeInfo mph_ti_mph_CaseClause = { "CaseClause", sizeof(mph_CaseClause), 1, (size_t[]){offsetof(mph_CaseClause, base)} };
MorphTypeInfo mph_ti_mph_SwitchStatement = { "SwitchStatement", sizeof(mph_SwitchStatement), 1, (size_t[]){offsetof(mph_SwitchStatement, base)} };
MorphTypeInfo mph_ti_mph_WhileStatement = { "WhileStatement", sizeof(mph_WhileStatement), 1, (size_t[]){offsetof(mph_WhileStatement, base)} };
MorphTypeInfo mph_ti_mph_StructStatement = { "StructStatement", sizeof(mph_StructStatement), 2, (size_t[]){offsetof(mph_StructStatement, base), offsetof(mph_StructStatement, name)} };
MorphTypeInfo mph_ti_mph_ImportStatement = { "ImportStatement", sizeof(mph_ImportStatement), 2, (size_t[]){offsetof(mph_ImportStatement, base), offsetof(mph_ImportStatement, path)} };
MorphTypeInfo mph_ti_mph_BreakStatement = { "BreakStatement", sizeof(mph_BreakStatement), 1, (size_t[]){offsetof(mph_BreakStatement, base)} };
MorphTypeInfo mph_ti_mph_ContinueStatement = { "ContinueStatement", sizeof(mph_ContinueStatement), 1, (size_t[]){offsetof(mph_ContinueStatement, base)} };

// Global Variables
mph_int mph_NODE_PROGRAM;
mph_int mph_NODE_VAR_STATEMENT;
mph_int mph_NODE_FUNCTION_STATEMENT;
mph_int mph_NODE_RETURN_STATEMENT;
mph_int mph_NODE_EXPRESSION_STATEMENT;
mph_int mph_NODE_BLOCK_STATEMENT;
mph_int mph_NODE_IF_EXPRESSION;
mph_int mph_NODE_IDENTIFIER;
mph_int mph_NODE_INTEGER_LITERAL;
mph_int mph_NODE_FLOAT_LITERAL;
mph_int mph_NODE_STRING_LITERAL;
mph_int mph_NODE_BOOLEAN_LITERAL;
mph_int mph_NODE_ARRAY_LITERAL;
mph_int mph_NODE_HASH_LITERAL;
mph_int mph_NODE_FUNCTION_LITERAL;
mph_int mph_NODE_PREFIX_EXPRESSION;
mph_int mph_NODE_INFIX_EXPRESSION;
mph_int mph_NODE_CALL_EXPRESSION;
mph_int mph_NODE_INDEX_EXPRESSION;
mph_int mph_NODE_MEMBER_EXPRESSION;
mph_int mph_NODE_ASSIGNMENT_EXPRESSION;
mph_int mph_NODE_SWITCH_STATEMENT;
mph_int mph_NODE_CASE_CLAUSE;
mph_int mph_NODE_WHILE_STATEMENT;
mph_int mph_NODE_STRUCT_STATEMENT;
mph_int mph_NODE_STRUCT_LITERAL;
mph_int mph_NODE_IMPORT_STATEMENT;
mph_int mph_NODE_INTERFACE_STATEMENT;
mph_int mph_NODE_BREAK_STATEMENT;
mph_int mph_NODE_CONTINUE_STATEMENT;
mph_int mph_NODE_CHAR_LITERAL;
mph_int mph_NODE_NULL_LITERAL;

// Function Prototypes
mph_Node* mph_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column);
mph_Program* mph_MakeProgram(MorphContext* ctx, void* _env_void);
mph_Identifier* mph_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column);
mph_IntegerLiteral* mph_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column);
mph_FloatLiteral* mph_MakeFloatLiteral(MorphContext* ctx, void* _env_void, MorphString* value_str, mph_int line, mph_int column);
mph_StringLiteral* mph_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column);
mph_BooleanLiteral* mph_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column);
mph_CharLiteral* mph_MakeCharLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column);
mph_NullLiteral* mph_MakeNullLiteral(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_VarStatement* mph_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column);
mph_PrefixExpression* mph_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column);
mph_InfixExpression* mph_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column);
mph_CaseClause* mph_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_CaseClause* mph_case_add_value(MorphContext* ctx, void* _env_void, mph_CaseClause* c, mph_int val);
mph_SwitchStatement* mph_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_WhileStatement* mph_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_StructStatement* mph_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column);
mph_ImportStatement* mph_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column);
mph_BreakStatement* mph_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
mph_ContinueStatement* mph_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column);
MorphString* mph_node_type_string(MorphContext* ctx, void* _env_void, mph_int node_type);
void mph_visit_node(MorphContext* ctx, void* _env_void, mph_Node* node);
void mph_print_identifier(MorphContext* ctx, void* _env_void, mph_Identifier* ident);
void mph_print_integer_literal(MorphContext* ctx, void* _env_void, mph_IntegerLiteral* lit);
void mph_print_string_literal(MorphContext* ctx, void* _env_void, mph_StringLiteral* lit);
void mph_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_BooleanLiteral* lit);

// Function Definitions
mph_Node* mph_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_Node* _t = (mph_Node*)mph_alloc(ctx, sizeof(mph_Node), &mph_ti_mph_Node); mph_gc_push_root(ctx, (void**)&_t); _t->node_type = node_type; _t->token_literal = literal; _t->line = line; _t->column = column; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_Program* mph_MakeProgram(MorphContext* ctx, void* _env_void) {
	mph_Node* base = ({ MorphString* _arg_1 = mph_string_new(ctx, "program"); mph_gc_push_root(ctx, (void**)&_arg_1); mph_Node* _ret_2 = mph_MakeNode(ctx, NULL, mph_NODE_PROGRAM, _arg_1, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_2; });
	mph_gc_push_root(ctx, (void**)&base);
	mph_VarStatement* stmt = ({ MorphString* _arg_3 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_3); MorphString* _arg_4 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_4); mph_VarStatement* _ret_5 = mph_MakeVarStatement(ctx, NULL, _arg_3, _arg_4, 1, 1); mph_gc_pop_roots(ctx, 2); _ret_5; });
	mph_gc_push_root(ctx, (void**)&stmt);
	return ({ mph_Program* _t = (mph_Program*)mph_alloc(ctx, sizeof(mph_Program), &mph_ti_mph_Program); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->statements_count = 0; _t->var_statements_count = 0; _t->var_statement = stmt; _t->has_var_statement = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 2);
}

mph_Identifier* mph_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_Node* base = ({ MorphString* _arg_6 = name; mph_gc_push_root(ctx, (void**)&_arg_6); mph_Node* _ret_7 = mph_MakeNode(ctx, NULL, mph_NODE_IDENTIFIER, _arg_6, line, column); mph_gc_pop_roots(ctx, 1); _ret_7; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_Identifier* _t = (mph_Identifier*)mph_alloc(ctx, sizeof(mph_Identifier), &mph_ti_mph_Identifier); mph_gc_push_root(ctx, (void**)&_t); _t->value = name; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_IntegerLiteral* mph_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_Node* base = ({ MorphString* _arg_8 = literal; mph_gc_push_root(ctx, (void**)&_arg_8); mph_Node* _ret_9 = mph_MakeNode(ctx, NULL, mph_NODE_INTEGER_LITERAL, _arg_8, line, column); mph_gc_pop_roots(ctx, 1); _ret_9; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_IntegerLiteral* _t = (mph_IntegerLiteral*)mph_alloc(ctx, sizeof(mph_IntegerLiteral), &mph_ti_mph_IntegerLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_FloatLiteral* mph_MakeFloatLiteral(MorphContext* ctx, void* _env_void, MorphString* value_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value_str);
	mph_Node* base = ({ MorphString* _arg_10 = value_str; mph_gc_push_root(ctx, (void**)&_arg_10); mph_Node* _ret_11 = mph_MakeNode(ctx, NULL, mph_NODE_FLOAT_LITERAL, _arg_10, line, column); mph_gc_pop_roots(ctx, 1); _ret_11; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_FloatLiteral* _t = (mph_FloatLiteral*)mph_alloc(ctx, sizeof(mph_FloatLiteral), &mph_ti_mph_FloatLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value_str = value_str; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_StringLiteral* mph_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value);
	mph_Node* base = ({ MorphString* _arg_12 = value; mph_gc_push_root(ctx, (void**)&_arg_12); mph_Node* _ret_13 = mph_MakeNode(ctx, NULL, mph_NODE_STRING_LITERAL, _arg_12, line, column); mph_gc_pop_roots(ctx, 1); _ret_13; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_StringLiteral* _t = (mph_StringLiteral*)mph_alloc(ctx, sizeof(mph_StringLiteral), &mph_ti_mph_StringLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->value = value; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_BooleanLiteral* mph_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_Node* base = ({ MorphString* _arg_14 = literal; mph_gc_push_root(ctx, (void**)&_arg_14); mph_Node* _ret_15 = mph_MakeNode(ctx, NULL, mph_NODE_BOOLEAN_LITERAL, _arg_14, line, column); mph_gc_pop_roots(ctx, 1); _ret_15; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_BooleanLiteral* _t = (mph_BooleanLiteral*)mph_alloc(ctx, sizeof(mph_BooleanLiteral), &mph_ti_mph_BooleanLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_CharLiteral* mph_MakeCharLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_Node* base = ({ MorphString* _arg_16 = literal; mph_gc_push_root(ctx, (void**)&_arg_16); mph_Node* _ret_17 = mph_MakeNode(ctx, NULL, mph_NODE_CHAR_LITERAL, _arg_16, line, column); mph_gc_pop_roots(ctx, 1); _ret_17; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_CharLiteral* _t = (mph_CharLiteral*)mph_alloc(ctx, sizeof(mph_CharLiteral), &mph_ti_mph_CharLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_NullLiteral* mph_MakeNullLiteral(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_Node* base = ({ MorphString* _arg_18 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_18); mph_Node* _ret_19 = mph_MakeNode(ctx, NULL, mph_NODE_NULL_LITERAL, _arg_18, line, column); mph_gc_pop_roots(ctx, 1); _ret_19; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_NullLiteral* _t = (mph_NullLiteral*)mph_alloc(ctx, sizeof(mph_NullLiteral), &mph_ti_mph_NullLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_VarStatement* mph_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&type_str);
	mph_Node* base = ({ MorphString* _arg_20 = mph_string_new(ctx, "var"); mph_gc_push_root(ctx, (void**)&_arg_20); mph_Node* _ret_21 = mph_MakeNode(ctx, NULL, mph_NODE_VAR_STATEMENT, _arg_20, line, column); mph_gc_pop_roots(ctx, 1); _ret_21; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_VarStatement* _t = (mph_VarStatement*)mph_alloc(ctx, sizeof(mph_VarStatement), &mph_ti_mph_VarStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->value_type = type_str; _t->has_value = 0; _t->value_literal = mph_string_new(ctx, "-"); _t->value_token_type = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

mph_PrefixExpression* mph_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_Node* base = ({ MorphString* _arg_22 = operator; mph_gc_push_root(ctx, (void**)&_arg_22); mph_Node* _ret_23 = mph_MakeNode(ctx, NULL, mph_NODE_PREFIX_EXPRESSION, _arg_22, line, column); mph_gc_pop_roots(ctx, 1); _ret_23; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_PrefixExpression* _t = (mph_PrefixExpression*)mph_alloc(ctx, sizeof(mph_PrefixExpression), &mph_ti_mph_PrefixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_InfixExpression* mph_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_Node* base = ({ MorphString* _arg_24 = operator; mph_gc_push_root(ctx, (void**)&_arg_24); mph_Node* _ret_25 = mph_MakeNode(ctx, NULL, mph_NODE_INFIX_EXPRESSION, _arg_24, line, column); mph_gc_pop_roots(ctx, 1); _ret_25; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_InfixExpression* _t = (mph_InfixExpression*)mph_alloc(ctx, sizeof(mph_InfixExpression), &mph_ti_mph_InfixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_CaseClause* mph_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_Node* base = ({ MorphString* _arg_26 = mph_string_new(ctx, "kasus"); mph_gc_push_root(ctx, (void**)&_arg_26); mph_Node* _ret_27 = mph_MakeNode(ctx, NULL, mph_NODE_CASE_CLAUSE, _arg_26, line, column); mph_gc_pop_roots(ctx, 1); _ret_27; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_CaseClause* _t = (mph_CaseClause*)mph_alloc(ctx, sizeof(mph_CaseClause), &mph_ti_mph_CaseClause); mph_gc_push_root(ctx, (void**)&_t); _t->has_body = 0; _t->base = base; _t->values_count = 0; _t->v0 = 0; _t->v1 = 0; _t->v2 = 0; _t->v3 = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_CaseClause* mph_case_add_value(MorphContext* ctx, void* _env_void, mph_CaseClause* c, mph_int val) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_CaseClause* _obj_28 = c; mph_gc_push_root(ctx, (void**)&_obj_28); mph_int _ret_29 = _obj_28->values_count; mph_gc_pop_roots(ctx, 1); _ret_29; }) == 0)) {
{
	({ mph_CaseClause* _obj_30 = c; mph_gc_push_root(ctx, (void**)&_obj_30); _obj_30->v0 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_CaseClause* _obj_31 = c; mph_gc_push_root(ctx, (void**)&_obj_31); mph_int _ret_32 = _obj_31->values_count; mph_gc_pop_roots(ctx, 1); _ret_32; }) == 1)) {
{
	({ mph_CaseClause* _obj_33 = c; mph_gc_push_root(ctx, (void**)&_obj_33); _obj_33->v1 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_CaseClause* _obj_34 = c; mph_gc_push_root(ctx, (void**)&_obj_34); mph_int _ret_35 = _obj_34->values_count; mph_gc_pop_roots(ctx, 1); _ret_35; }) == 2)) {
{
	({ mph_CaseClause* _obj_36 = c; mph_gc_push_root(ctx, (void**)&_obj_36); _obj_36->v2 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_CaseClause* _obj_37 = c; mph_gc_push_root(ctx, (void**)&_obj_37); mph_int _ret_38 = _obj_37->values_count; mph_gc_pop_roots(ctx, 1); _ret_38; }) == 3)) {
{
	({ mph_CaseClause* _obj_39 = c; mph_gc_push_root(ctx, (void**)&_obj_39); _obj_39->v3 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	({ mph_CaseClause* _obj_42 = c; mph_gc_push_root(ctx, (void**)&_obj_42); _obj_42->values_count = (({ mph_CaseClause* _obj_40 = c; mph_gc_push_root(ctx, (void**)&_obj_40); mph_int _ret_41 = _obj_40->values_count; mph_gc_pop_roots(ctx, 1); _ret_41; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return c;
	mph_gc_pop_roots(ctx, 1);
}

mph_SwitchStatement* mph_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_Node* base = ({ MorphString* _arg_43 = mph_string_new(ctx, "pilih"); mph_gc_push_root(ctx, (void**)&_arg_43); mph_Node* _ret_44 = mph_MakeNode(ctx, NULL, mph_NODE_SWITCH_STATEMENT, _arg_43, line, column); mph_gc_pop_roots(ctx, 1); _ret_44; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_SwitchStatement* _t = (mph_SwitchStatement*)mph_alloc(ctx, sizeof(mph_SwitchStatement), &mph_ti_mph_SwitchStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->cases_count = 0; _t->has_default = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_WhileStatement* mph_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_Node* base = ({ MorphString* _arg_45 = mph_string_new(ctx, "selama"); mph_gc_push_root(ctx, (void**)&_arg_45); mph_Node* _ret_46 = mph_MakeNode(ctx, NULL, mph_NODE_WHILE_STATEMENT, _arg_45, line, column); mph_gc_pop_roots(ctx, 1); _ret_46; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_WhileStatement* _t = (mph_WhileStatement*)mph_alloc(ctx, sizeof(mph_WhileStatement), &mph_ti_mph_WhileStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->has_body = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_StructStatement* mph_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_Node* base = ({ MorphString* _arg_47 = mph_string_new(ctx, "struktur"); mph_gc_push_root(ctx, (void**)&_arg_47); mph_Node* _ret_48 = mph_MakeNode(ctx, NULL, mph_NODE_STRUCT_STATEMENT, _arg_47, line, column); mph_gc_pop_roots(ctx, 1); _ret_48; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_StructStatement* _t = (mph_StructStatement*)mph_alloc(ctx, sizeof(mph_StructStatement), &mph_ti_mph_StructStatement); mph_gc_push_root(ctx, (void**)&_t); _t->name = name; _t->fields_count = 0; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ImportStatement* mph_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&path);
	mph_Node* base = ({ MorphString* _arg_49 = mph_string_new(ctx, "ambil"); mph_gc_push_root(ctx, (void**)&_arg_49); mph_Node* _ret_50 = mph_MakeNode(ctx, NULL, mph_NODE_IMPORT_STATEMENT, _arg_49, line, column); mph_gc_pop_roots(ctx, 1); _ret_50; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ImportStatement* _t = (mph_ImportStatement*)mph_alloc(ctx, sizeof(mph_ImportStatement), &mph_ti_mph_ImportStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->path = path; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_BreakStatement* mph_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_Node* base = ({ MorphString* _arg_51 = mph_string_new(ctx, "putus"); mph_gc_push_root(ctx, (void**)&_arg_51); mph_Node* _ret_52 = mph_MakeNode(ctx, NULL, mph_NODE_BREAK_STATEMENT, _arg_51, line, column); mph_gc_pop_roots(ctx, 1); _ret_52; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_BreakStatement* _t = (mph_BreakStatement*)mph_alloc(ctx, sizeof(mph_BreakStatement), &mph_ti_mph_BreakStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ContinueStatement* mph_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_Node* base = ({ MorphString* _arg_53 = mph_string_new(ctx, "lanjut"); mph_gc_push_root(ctx, (void**)&_arg_53); mph_Node* _ret_54 = mph_MakeNode(ctx, NULL, mph_NODE_CONTINUE_STATEMENT, _arg_53, line, column); mph_gc_pop_roots(ctx, 1); _ret_54; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ContinueStatement* _t = (mph_ContinueStatement*)mph_alloc(ctx, sizeof(mph_ContinueStatement), &mph_ti_mph_ContinueStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_node_type_string(MorphContext* ctx, void* _env_void, mph_int node_type) {
	if ((node_type == mph_NODE_PROGRAM)) {
{
	return mph_string_new(ctx, "Program");
}
	}
	if ((node_type == mph_NODE_VAR_STATEMENT)) {
{
	return mph_string_new(ctx, "VarStatement");
}
	}
	if ((node_type == mph_NODE_FUNCTION_STATEMENT)) {
{
	return mph_string_new(ctx, "FunctionStatement");
}
	}
	if ((node_type == mph_NODE_RETURN_STATEMENT)) {
{
	return mph_string_new(ctx, "ReturnStatement");
}
	}
	if ((node_type == mph_NODE_EXPRESSION_STATEMENT)) {
{
	return mph_string_new(ctx, "ExpressionStatement");
}
	}
	if ((node_type == mph_NODE_BLOCK_STATEMENT)) {
{
	return mph_string_new(ctx, "BlockStatement");
}
	}
	if ((node_type == mph_NODE_IF_EXPRESSION)) {
{
	return mph_string_new(ctx, "IfExpression");
}
	}
	if ((node_type == mph_NODE_IDENTIFIER)) {
{
	return mph_string_new(ctx, "Identifier");
}
	}
	if ((node_type == mph_NODE_INTEGER_LITERAL)) {
{
	return mph_string_new(ctx, "IntegerLiteral");
}
	}
	if ((node_type == mph_NODE_FLOAT_LITERAL)) {
{
	return mph_string_new(ctx, "FloatLiteral");
}
	}
	if ((node_type == mph_NODE_STRING_LITERAL)) {
{
	return mph_string_new(ctx, "StringLiteral");
}
	}
	if ((node_type == mph_NODE_BOOLEAN_LITERAL)) {
{
	return mph_string_new(ctx, "BooleanLiteral");
}
	}
	if ((node_type == mph_NODE_CHAR_LITERAL)) {
{
	return mph_string_new(ctx, "CharLiteral");
}
	}
	if ((node_type == mph_NODE_NULL_LITERAL)) {
{
	return mph_string_new(ctx, "NullLiteral");
}
	}
	if ((node_type == mph_NODE_ARRAY_LITERAL)) {
{
	return mph_string_new(ctx, "ArrayLiteral");
}
	}
	if ((node_type == mph_NODE_HASH_LITERAL)) {
{
	return mph_string_new(ctx, "HashLiteral");
}
	}
	if ((node_type == mph_NODE_FUNCTION_LITERAL)) {
{
	return mph_string_new(ctx, "FunctionLiteral");
}
	}
	if ((node_type == mph_NODE_PREFIX_EXPRESSION)) {
{
	return mph_string_new(ctx, "PrefixExpression");
}
	}
	if ((node_type == mph_NODE_INFIX_EXPRESSION)) {
{
	return mph_string_new(ctx, "InfixExpression");
}
	}
	if ((node_type == mph_NODE_CALL_EXPRESSION)) {
{
	return mph_string_new(ctx, "CallExpression");
}
	}
	if ((node_type == mph_NODE_INDEX_EXPRESSION)) {
{
	return mph_string_new(ctx, "IndexExpression");
}
	}
	if ((node_type == mph_NODE_MEMBER_EXPRESSION)) {
{
	return mph_string_new(ctx, "MemberExpression");
}
	}
	if ((node_type == mph_NODE_ASSIGNMENT_EXPRESSION)) {
{
	return mph_string_new(ctx, "AssignmentExpression");
}
	}
	return mph_string_new(ctx, "Unknown");
}

void mph_visit_node(MorphContext* ctx, void* _env_void, mph_Node* node) {
	mph_gc_push_root(ctx, (void**)&node);
	mph_native_print(ctx, mph_string_new(ctx, "Visiting "));
	mph_native_print(ctx, mph_node_type_string(ctx, NULL, ({ mph_Node* _obj_55 = node; mph_gc_push_root(ctx, (void**)&_obj_55); mph_int _ret_56 = _obj_55->node_type; mph_gc_pop_roots(ctx, 1); _ret_56; })));
	mph_native_print(ctx, mph_string_new(ctx, " at line "));
	mph_native_print_int(ctx, ({ mph_Node* _obj_57 = node; mph_gc_push_root(ctx, (void**)&_obj_57); mph_int _ret_58 = _obj_57->line; mph_gc_pop_roots(ctx, 1); _ret_58; }));
	mph_native_print(ctx, mph_string_new(ctx, ", column "));
	mph_native_print_int(ctx, ({ mph_Node* _obj_59 = node; mph_gc_push_root(ctx, (void**)&_obj_59); mph_int _ret_60 = _obj_59->column; mph_gc_pop_roots(ctx, 1); _ret_60; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_print_identifier(MorphContext* ctx, void* _env_void, mph_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	mph_native_print(ctx, mph_string_new(ctx, "Identifier: "));
	mph_native_print(ctx, ({ mph_Identifier* _obj_61 = ident; mph_gc_push_root(ctx, (void**)&_obj_61); MorphString* _ret_62 = _obj_61->value; mph_gc_pop_roots(ctx, 1); _ret_62; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_Node* _obj_65 = ({ mph_Identifier* _obj_63 = ident; mph_gc_push_root(ctx, (void**)&_obj_63); mph_Node* _ret_64 = _obj_63->base; mph_gc_pop_roots(ctx, 1); _ret_64; }); mph_gc_push_root(ctx, (void**)&_obj_65); mph_int _ret_66 = _obj_65->line; mph_gc_pop_roots(ctx, 1); _ret_66; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_Node* _obj_69 = ({ mph_Identifier* _obj_67 = ident; mph_gc_push_root(ctx, (void**)&_obj_67); mph_Node* _ret_68 = _obj_67->base; mph_gc_pop_roots(ctx, 1); _ret_68; }); mph_gc_push_root(ctx, (void**)&_obj_69); mph_int _ret_70 = _obj_69->column; mph_gc_pop_roots(ctx, 1); _ret_70; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_print_integer_literal(MorphContext* ctx, void* _env_void, mph_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "IntegerLiteral: "));
	mph_native_print_int(ctx, ({ mph_IntegerLiteral* _obj_71 = lit; mph_gc_push_root(ctx, (void**)&_obj_71); mph_int _ret_72 = _obj_71->value; mph_gc_pop_roots(ctx, 1); _ret_72; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_Node* _obj_75 = ({ mph_IntegerLiteral* _obj_73 = lit; mph_gc_push_root(ctx, (void**)&_obj_73); mph_Node* _ret_74 = _obj_73->base; mph_gc_pop_roots(ctx, 1); _ret_74; }); mph_gc_push_root(ctx, (void**)&_obj_75); mph_int _ret_76 = _obj_75->line; mph_gc_pop_roots(ctx, 1); _ret_76; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_Node* _obj_79 = ({ mph_IntegerLiteral* _obj_77 = lit; mph_gc_push_root(ctx, (void**)&_obj_77); mph_Node* _ret_78 = _obj_77->base; mph_gc_pop_roots(ctx, 1); _ret_78; }); mph_gc_push_root(ctx, (void**)&_obj_79); mph_int _ret_80 = _obj_79->column; mph_gc_pop_roots(ctx, 1); _ret_80; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_print_string_literal(MorphContext* ctx, void* _env_void, mph_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "StringLiteral: \""));
	mph_native_print(ctx, ({ mph_StringLiteral* _obj_81 = lit; mph_gc_push_root(ctx, (void**)&_obj_81); MorphString* _ret_82 = _obj_81->value; mph_gc_pop_roots(ctx, 1); _ret_82; }));
	mph_native_print(ctx, mph_string_new(ctx, "\" ("));
	mph_native_print_int(ctx, ({ mph_Node* _obj_85 = ({ mph_StringLiteral* _obj_83 = lit; mph_gc_push_root(ctx, (void**)&_obj_83); mph_Node* _ret_84 = _obj_83->base; mph_gc_pop_roots(ctx, 1); _ret_84; }); mph_gc_push_root(ctx, (void**)&_obj_85); mph_int _ret_86 = _obj_85->line; mph_gc_pop_roots(ctx, 1); _ret_86; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_Node* _obj_89 = ({ mph_StringLiteral* _obj_87 = lit; mph_gc_push_root(ctx, (void**)&_obj_87); mph_Node* _ret_88 = _obj_87->base; mph_gc_pop_roots(ctx, 1); _ret_88; }); mph_gc_push_root(ctx, (void**)&_obj_89); mph_int _ret_90 = _obj_89->column; mph_gc_pop_roots(ctx, 1); _ret_90; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "BooleanLiteral: "));
	if (({ mph_BooleanLiteral* _obj_91 = lit; mph_gc_push_root(ctx, (void**)&_obj_91); mph_bool _ret_92 = _obj_91->value; mph_gc_pop_roots(ctx, 1); _ret_92; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "benar"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "salah"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_Node* _obj_95 = ({ mph_BooleanLiteral* _obj_93 = lit; mph_gc_push_root(ctx, (void**)&_obj_93); mph_Node* _ret_94 = _obj_93->base; mph_gc_pop_roots(ctx, 1); _ret_94; }); mph_gc_push_root(ctx, (void**)&_obj_95); mph_int _ret_96 = _obj_95->line; mph_gc_pop_roots(ctx, 1); _ret_96; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_Node* _obj_99 = ({ mph_BooleanLiteral* _obj_97 = lit; mph_gc_push_root(ctx, (void**)&_obj_97); mph_Node* _ret_98 = _obj_97->base; mph_gc_pop_roots(ctx, 1); _ret_98; }); mph_gc_push_root(ctx, (void**)&_obj_99); mph_int _ret_100 = _obj_99->column; mph_gc_pop_roots(ctx, 1); _ret_100; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_NODE_PROGRAM = 0;
	mph_NODE_VAR_STATEMENT = 1;
	mph_NODE_FUNCTION_STATEMENT = 2;
	mph_NODE_RETURN_STATEMENT = 3;
	mph_NODE_EXPRESSION_STATEMENT = 4;
	mph_NODE_BLOCK_STATEMENT = 5;
	mph_NODE_IF_EXPRESSION = 6;
	mph_NODE_IDENTIFIER = 7;
	mph_NODE_INTEGER_LITERAL = 8;
	mph_NODE_FLOAT_LITERAL = 9;
	mph_NODE_STRING_LITERAL = 10;
	mph_NODE_BOOLEAN_LITERAL = 11;
	mph_NODE_ARRAY_LITERAL = 12;
	mph_NODE_HASH_LITERAL = 13;
	mph_NODE_FUNCTION_LITERAL = 14;
	mph_NODE_PREFIX_EXPRESSION = 15;
	mph_NODE_INFIX_EXPRESSION = 16;
	mph_NODE_CALL_EXPRESSION = 17;
	mph_NODE_INDEX_EXPRESSION = 18;
	mph_NODE_MEMBER_EXPRESSION = 19;
	mph_NODE_ASSIGNMENT_EXPRESSION = 20;
	mph_NODE_SWITCH_STATEMENT = 21;
	mph_NODE_CASE_CLAUSE = 22;
	mph_NODE_WHILE_STATEMENT = 23;
	mph_NODE_STRUCT_STATEMENT = 24;
	mph_NODE_STRUCT_LITERAL = 25;
	mph_NODE_IMPORT_STATEMENT = 26;
	mph_NODE_INTERFACE_STATEMENT = 27;
	mph_NODE_BREAK_STATEMENT = 28;
	mph_NODE_CONTINUE_STATEMENT = 29;
	mph_NODE_CHAR_LITERAL = 30;
	mph_NODE_NULL_LITERAL = 31;
}
