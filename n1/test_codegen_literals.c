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
#define MPH_TYPE_mph_ast_Node 1
#define MPH_TYPE_mph_ast_FunctionStatement 4
#define MPH_TYPE_mph_ast_BlockStatement 7
#define MPH_TYPE_mph_ast_IntegerLiteral 9
#define MPH_TYPE_mph_ast_StructStatement 22
#define MPH_TYPE_mph_ast_VarStatement 3
#define MPH_TYPE_mph_ast_Identifier 8
#define MPH_TYPE_mph_ast_InfixExpression 14
#define MPH_TYPE_mph_ast_IfExpression 15
#define MPH_TYPE_mph_ast_CallExpression 16
#define MPH_TYPE_mph_ast_IndexExpression 17
#define MPH_TYPE_mph_ast_CaseClause 19
#define MPH_TYPE_mph_ast_BreakStatement 24
#define MPH_TYPE_mph_ast_Program 2
#define MPH_TYPE_mph_ast_ExpressionStatement 6
#define MPH_TYPE_mph_ast_FloatLiteral 10
#define MPH_TYPE_mph_ast_StringLiteral 11
#define MPH_TYPE_mph_ast_WhileStatement 21
#define MPH_TYPE_mph_ast_ImportStatement 23
#define MPH_TYPE_mph_ast_ContinueStatement 25
#define MPH_TYPE_mph_codegen_Codegen 26
#define MPH_TYPE_mph_ast_ReturnStatement 5
#define MPH_TYPE_mph_ast_BooleanLiteral 12
#define MPH_TYPE_mph_ast_PrefixExpression 13
#define MPH_TYPE_mph_ast_MemberExpression 18
#define MPH_TYPE_mph_ast_SwitchStatement 20

// Struct Definitions (Env & Types)
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

typedef struct mph_codegen_Codegen mph_codegen_Codegen;
struct mph_codegen_Codegen {
	MorphString* output;
	MorphString* type_defs;
	MorphString* global_defs;
	MorphString* prototypes;
	MorphString* func_defs;
	MorphString* entry_body;
	mph_int temp_index;
	mph_bool has_main;
	mph_int indent_level;
	MorphString* current_prefix;
};

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
MorphTypeInfo mph_ti_mph_codegen_Codegen = { "Codegen", sizeof(mph_codegen_Codegen), 7, (size_t[]){offsetof(mph_codegen_Codegen, output), offsetof(mph_codegen_Codegen, type_defs), offsetof(mph_codegen_Codegen, global_defs), offsetof(mph_codegen_Codegen, prototypes), offsetof(mph_codegen_Codegen, func_defs), offsetof(mph_codegen_Codegen, entry_body), offsetof(mph_codegen_Codegen, current_prefix)} };

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

// Function Prototypes
void mph_test_integer_literal(MorphContext* ctx, void* _env_void);
void mph_test_string_literal(MorphContext* ctx, void* _env_void);
void mph_test_boolean_literal(MorphContext* ctx, void* _env_void);
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
void mph_codegen_codegen_compile_program(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog, MorphString* prefix);
MorphString* mph_codegen_codegen_next_temp(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, MorphString* prefix);
MorphString* mph_codegen_codegen_append(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text);
MorphString* mph_codegen_codegen_append_line(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text);
MorphString* mph_codegen_codegen_append_indent(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text, mph_int level);
MorphString* mph_codegen_codegen_compile_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit);
MorphString* mph_codegen_codegen_compile_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit);
MorphString* mph_codegen_codegen_compile_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit);
MorphString* mph_codegen_codegen_compile_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident);
MorphString* mph_codegen_codegen_compile_infix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_codegen_compile_var_statement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code);
mph_codegen_Codegen* mph_codegen_NewCodegen(MorphContext* ctx, void* _env_void);
MorphString* mph_codegen_CodegenCompile(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog);
MorphString* mph_codegen_CompileIntegerLiteral(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit);
MorphString* mph_codegen_CompileStringLiteral(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit);
MorphString* mph_codegen_CompileBooleanLiteral(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit);
MorphString* mph_codegen_CompileIdentifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident);
MorphString* mph_codegen_CompileInfix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code);
MorphString* mph_codegen_CompileVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code);

// Function Definitions
mph_codegen_Codegen* mph_codegen_new_codegen(MorphContext* ctx, void* _env_void) {
	return ({ mph_codegen_Codegen* _t = (mph_codegen_Codegen*)mph_alloc(ctx, sizeof(mph_codegen_Codegen), &mph_ti_mph_codegen_Codegen); mph_gc_push_root(ctx, (void**)&_t); _t->output = mph_string_new(ctx, ""); _t->type_defs = mph_string_new(ctx, ""); _t->global_defs = mph_string_new(ctx, ""); _t->func_defs = mph_string_new(ctx, ""); _t->entry_body = mph_string_new(ctx, ""); _t->prototypes = mph_string_new(ctx, ""); _t->temp_index = 0; _t->has_main = 0; _t->indent_level = 0; _t->current_prefix = mph_string_new(ctx, "mph_"); mph_gc_pop_roots(ctx, 1); _t; });
}

MorphString* mph_codegen_codegen_compile(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	({ mph_codegen_Codegen* _obj_1 = cg; mph_gc_push_root(ctx, (void**)&_obj_1); MorphString* _val_2 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_2); _obj_1->output = _val_2; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_3 = cg; mph_gc_push_root(ctx, (void**)&_obj_3); MorphString* _val_4 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_4); _obj_3->type_defs = _val_4; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_5 = cg; mph_gc_push_root(ctx, (void**)&_obj_5); MorphString* _val_6 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_6); _obj_5->global_defs = _val_6; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_7 = cg; mph_gc_push_root(ctx, (void**)&_obj_7); MorphString* _val_8 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_8); _obj_7->prototypes = _val_8; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_9 = cg; mph_gc_push_root(ctx, (void**)&_obj_9); MorphString* _val_10 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_10); _obj_9->func_defs = _val_10; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_11 = cg; mph_gc_push_root(ctx, (void**)&_obj_11); MorphString* _val_12 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_val_12); _obj_11->entry_body = _val_12; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_13 = cg; mph_gc_push_root(ctx, (void**)&_obj_13); _obj_13->temp_index = 0; mph_gc_pop_roots(ctx, 1); });
	({ mph_codegen_Codegen* _obj_14 = cg; mph_gc_push_root(ctx, (void**)&_obj_14); _obj_14->has_main = 0; mph_gc_pop_roots(ctx, 1); });
	({ mph_codegen_Codegen* _obj_20 = cg; mph_gc_push_root(ctx, (void**)&_obj_20); MorphString* _val_21 = ({ MorphString* _lhs_17 = ({ mph_codegen_Codegen* _obj_15 = cg; mph_gc_push_root(ctx, (void**)&_obj_15); MorphString* _ret_16 = _obj_15->output; mph_gc_pop_roots(ctx, 1); _ret_16; }); MorphString* _rhs_18 = mph_string_new(ctx, "#include \"morph.h\"\n\n"); mph_gc_push_root(ctx, (void**)&_lhs_17); mph_gc_push_root(ctx, (void**)&_rhs_18); MorphString* _ret_19 = mph_string_concat(ctx, _lhs_17, _rhs_18); mph_gc_pop_roots(ctx, 2); _ret_19; }); mph_gc_push_root(ctx, (void**)&_val_21); _obj_20->output = _val_21; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_27 = cg; mph_gc_push_root(ctx, (void**)&_obj_27); MorphString* _val_28 = ({ MorphString* _lhs_24 = ({ mph_codegen_Codegen* _obj_22 = cg; mph_gc_push_root(ctx, (void**)&_obj_22); MorphString* _ret_23 = _obj_22->output; mph_gc_pop_roots(ctx, 1); _ret_23; }); MorphString* _rhs_25 = mph_string_new(ctx, "// Native bindings\n"); mph_gc_push_root(ctx, (void**)&_lhs_24); mph_gc_push_root(ctx, (void**)&_rhs_25); MorphString* _ret_26 = mph_string_concat(ctx, _lhs_24, _rhs_25); mph_gc_pop_roots(ctx, 2); _ret_26; }); mph_gc_push_root(ctx, (void**)&_val_28); _obj_27->output = _val_28; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_34 = cg; mph_gc_push_root(ctx, (void**)&_obj_34); MorphString* _val_35 = ({ MorphString* _lhs_31 = ({ mph_codegen_Codegen* _obj_29 = cg; mph_gc_push_root(ctx, (void**)&_obj_29); MorphString* _ret_30 = _obj_29->output; mph_gc_pop_roots(ctx, 1); _ret_30; }); MorphString* _rhs_32 = mph_string_new(ctx, "void mph_native_print(MorphContext* ctx, MorphString* s);\n"); mph_gc_push_root(ctx, (void**)&_lhs_31); mph_gc_push_root(ctx, (void**)&_rhs_32); MorphString* _ret_33 = mph_string_concat(ctx, _lhs_31, _rhs_32); mph_gc_pop_roots(ctx, 2); _ret_33; }); mph_gc_push_root(ctx, (void**)&_val_35); _obj_34->output = _val_35; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_41 = cg; mph_gc_push_root(ctx, (void**)&_obj_41); MorphString* _val_42 = ({ MorphString* _lhs_38 = ({ mph_codegen_Codegen* _obj_36 = cg; mph_gc_push_root(ctx, (void**)&_obj_36); MorphString* _ret_37 = _obj_36->output; mph_gc_pop_roots(ctx, 1); _ret_37; }); MorphString* _rhs_39 = mph_string_new(ctx, "void mph_native_print_int(MorphContext* ctx, mph_int n);\n\n"); mph_gc_push_root(ctx, (void**)&_lhs_38); mph_gc_push_root(ctx, (void**)&_rhs_39); MorphString* _ret_40 = mph_string_concat(ctx, _lhs_38, _rhs_39); mph_gc_pop_roots(ctx, 2); _ret_40; }); mph_gc_push_root(ctx, (void**)&_val_42); _obj_41->output = _val_42; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _arg_43 = cg; mph_gc_push_root(ctx, (void**)&_arg_43); mph_ast_Program* _arg_44 = prog; mph_gc_push_root(ctx, (void**)&_arg_44); MorphString* _arg_45 = mph_string_new(ctx, "mph_"); mph_gc_push_root(ctx, (void**)&_arg_45); mph_codegen_codegen_compile_program(ctx, NULL, _arg_43, _arg_44, _arg_45); mph_gc_pop_roots(ctx, 3); });
	({ mph_codegen_Codegen* _obj_51 = cg; mph_gc_push_root(ctx, (void**)&_obj_51); MorphString* _val_52 = ({ MorphString* _lhs_48 = ({ mph_codegen_Codegen* _obj_46 = cg; mph_gc_push_root(ctx, (void**)&_obj_46); MorphString* _ret_47 = _obj_46->output; mph_gc_pop_roots(ctx, 1); _ret_47; }); MorphString* _rhs_49 = mph_string_new(ctx, "// Type Definitions\n"); mph_gc_push_root(ctx, (void**)&_lhs_48); mph_gc_push_root(ctx, (void**)&_rhs_49); MorphString* _ret_50 = mph_string_concat(ctx, _lhs_48, _rhs_49); mph_gc_pop_roots(ctx, 2); _ret_50; }); mph_gc_push_root(ctx, (void**)&_val_52); _obj_51->output = _val_52; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_60 = cg; mph_gc_push_root(ctx, (void**)&_obj_60); MorphString* _val_61 = ({ MorphString* _lhs_57 = ({ mph_codegen_Codegen* _obj_53 = cg; mph_gc_push_root(ctx, (void**)&_obj_53); MorphString* _ret_54 = _obj_53->output; mph_gc_pop_roots(ctx, 1); _ret_54; }); MorphString* _rhs_58 = ({ mph_codegen_Codegen* _obj_55 = cg; mph_gc_push_root(ctx, (void**)&_obj_55); MorphString* _ret_56 = _obj_55->type_defs; mph_gc_pop_roots(ctx, 1); _ret_56; }); mph_gc_push_root(ctx, (void**)&_lhs_57); mph_gc_push_root(ctx, (void**)&_rhs_58); MorphString* _ret_59 = mph_string_concat(ctx, _lhs_57, _rhs_58); mph_gc_pop_roots(ctx, 2); _ret_59; }); mph_gc_push_root(ctx, (void**)&_val_61); _obj_60->output = _val_61; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_67 = cg; mph_gc_push_root(ctx, (void**)&_obj_67); MorphString* _val_68 = ({ MorphString* _lhs_64 = ({ mph_codegen_Codegen* _obj_62 = cg; mph_gc_push_root(ctx, (void**)&_obj_62); MorphString* _ret_63 = _obj_62->output; mph_gc_pop_roots(ctx, 1); _ret_63; }); MorphString* _rhs_65 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_64); mph_gc_push_root(ctx, (void**)&_rhs_65); MorphString* _ret_66 = mph_string_concat(ctx, _lhs_64, _rhs_65); mph_gc_pop_roots(ctx, 2); _ret_66; }); mph_gc_push_root(ctx, (void**)&_val_68); _obj_67->output = _val_68; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_74 = cg; mph_gc_push_root(ctx, (void**)&_obj_74); MorphString* _val_75 = ({ MorphString* _lhs_71 = ({ mph_codegen_Codegen* _obj_69 = cg; mph_gc_push_root(ctx, (void**)&_obj_69); MorphString* _ret_70 = _obj_69->output; mph_gc_pop_roots(ctx, 1); _ret_70; }); MorphString* _rhs_72 = mph_string_new(ctx, "// Global Variables\n"); mph_gc_push_root(ctx, (void**)&_lhs_71); mph_gc_push_root(ctx, (void**)&_rhs_72); MorphString* _ret_73 = mph_string_concat(ctx, _lhs_71, _rhs_72); mph_gc_pop_roots(ctx, 2); _ret_73; }); mph_gc_push_root(ctx, (void**)&_val_75); _obj_74->output = _val_75; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_83 = cg; mph_gc_push_root(ctx, (void**)&_obj_83); MorphString* _val_84 = ({ MorphString* _lhs_80 = ({ mph_codegen_Codegen* _obj_76 = cg; mph_gc_push_root(ctx, (void**)&_obj_76); MorphString* _ret_77 = _obj_76->output; mph_gc_pop_roots(ctx, 1); _ret_77; }); MorphString* _rhs_81 = ({ mph_codegen_Codegen* _obj_78 = cg; mph_gc_push_root(ctx, (void**)&_obj_78); MorphString* _ret_79 = _obj_78->global_defs; mph_gc_pop_roots(ctx, 1); _ret_79; }); mph_gc_push_root(ctx, (void**)&_lhs_80); mph_gc_push_root(ctx, (void**)&_rhs_81); MorphString* _ret_82 = mph_string_concat(ctx, _lhs_80, _rhs_81); mph_gc_pop_roots(ctx, 2); _ret_82; }); mph_gc_push_root(ctx, (void**)&_val_84); _obj_83->output = _val_84; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_90 = cg; mph_gc_push_root(ctx, (void**)&_obj_90); MorphString* _val_91 = ({ MorphString* _lhs_87 = ({ mph_codegen_Codegen* _obj_85 = cg; mph_gc_push_root(ctx, (void**)&_obj_85); MorphString* _ret_86 = _obj_85->output; mph_gc_pop_roots(ctx, 1); _ret_86; }); MorphString* _rhs_88 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_87); mph_gc_push_root(ctx, (void**)&_rhs_88); MorphString* _ret_89 = mph_string_concat(ctx, _lhs_87, _rhs_88); mph_gc_pop_roots(ctx, 2); _ret_89; }); mph_gc_push_root(ctx, (void**)&_val_91); _obj_90->output = _val_91; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_97 = cg; mph_gc_push_root(ctx, (void**)&_obj_97); MorphString* _val_98 = ({ MorphString* _lhs_94 = ({ mph_codegen_Codegen* _obj_92 = cg; mph_gc_push_root(ctx, (void**)&_obj_92); MorphString* _ret_93 = _obj_92->output; mph_gc_pop_roots(ctx, 1); _ret_93; }); MorphString* _rhs_95 = mph_string_new(ctx, "// Function Prototypes\n"); mph_gc_push_root(ctx, (void**)&_lhs_94); mph_gc_push_root(ctx, (void**)&_rhs_95); MorphString* _ret_96 = mph_string_concat(ctx, _lhs_94, _rhs_95); mph_gc_pop_roots(ctx, 2); _ret_96; }); mph_gc_push_root(ctx, (void**)&_val_98); _obj_97->output = _val_98; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_106 = cg; mph_gc_push_root(ctx, (void**)&_obj_106); MorphString* _val_107 = ({ MorphString* _lhs_103 = ({ mph_codegen_Codegen* _obj_99 = cg; mph_gc_push_root(ctx, (void**)&_obj_99); MorphString* _ret_100 = _obj_99->output; mph_gc_pop_roots(ctx, 1); _ret_100; }); MorphString* _rhs_104 = ({ mph_codegen_Codegen* _obj_101 = cg; mph_gc_push_root(ctx, (void**)&_obj_101); MorphString* _ret_102 = _obj_101->prototypes; mph_gc_pop_roots(ctx, 1); _ret_102; }); mph_gc_push_root(ctx, (void**)&_lhs_103); mph_gc_push_root(ctx, (void**)&_rhs_104); MorphString* _ret_105 = mph_string_concat(ctx, _lhs_103, _rhs_104); mph_gc_pop_roots(ctx, 2); _ret_105; }); mph_gc_push_root(ctx, (void**)&_val_107); _obj_106->output = _val_107; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_113 = cg; mph_gc_push_root(ctx, (void**)&_obj_113); MorphString* _val_114 = ({ MorphString* _lhs_110 = ({ mph_codegen_Codegen* _obj_108 = cg; mph_gc_push_root(ctx, (void**)&_obj_108); MorphString* _ret_109 = _obj_108->output; mph_gc_pop_roots(ctx, 1); _ret_109; }); MorphString* _rhs_111 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_110); mph_gc_push_root(ctx, (void**)&_rhs_111); MorphString* _ret_112 = mph_string_concat(ctx, _lhs_110, _rhs_111); mph_gc_pop_roots(ctx, 2); _ret_112; }); mph_gc_push_root(ctx, (void**)&_val_114); _obj_113->output = _val_114; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_120 = cg; mph_gc_push_root(ctx, (void**)&_obj_120); MorphString* _val_121 = ({ MorphString* _lhs_117 = ({ mph_codegen_Codegen* _obj_115 = cg; mph_gc_push_root(ctx, (void**)&_obj_115); MorphString* _ret_116 = _obj_115->output; mph_gc_pop_roots(ctx, 1); _ret_116; }); MorphString* _rhs_118 = mph_string_new(ctx, "// Function Definitions\n"); mph_gc_push_root(ctx, (void**)&_lhs_117); mph_gc_push_root(ctx, (void**)&_rhs_118); MorphString* _ret_119 = mph_string_concat(ctx, _lhs_117, _rhs_118); mph_gc_pop_roots(ctx, 2); _ret_119; }); mph_gc_push_root(ctx, (void**)&_val_121); _obj_120->output = _val_121; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_129 = cg; mph_gc_push_root(ctx, (void**)&_obj_129); MorphString* _val_130 = ({ MorphString* _lhs_126 = ({ mph_codegen_Codegen* _obj_122 = cg; mph_gc_push_root(ctx, (void**)&_obj_122); MorphString* _ret_123 = _obj_122->output; mph_gc_pop_roots(ctx, 1); _ret_123; }); MorphString* _rhs_127 = ({ mph_codegen_Codegen* _obj_124 = cg; mph_gc_push_root(ctx, (void**)&_obj_124); MorphString* _ret_125 = _obj_124->func_defs; mph_gc_pop_roots(ctx, 1); _ret_125; }); mph_gc_push_root(ctx, (void**)&_lhs_126); mph_gc_push_root(ctx, (void**)&_rhs_127); MorphString* _ret_128 = mph_string_concat(ctx, _lhs_126, _rhs_127); mph_gc_pop_roots(ctx, 2); _ret_128; }); mph_gc_push_root(ctx, (void**)&_val_130); _obj_129->output = _val_130; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_136 = cg; mph_gc_push_root(ctx, (void**)&_obj_136); MorphString* _val_137 = ({ MorphString* _lhs_133 = ({ mph_codegen_Codegen* _obj_131 = cg; mph_gc_push_root(ctx, (void**)&_obj_131); MorphString* _ret_132 = _obj_131->output; mph_gc_pop_roots(ctx, 1); _ret_132; }); MorphString* _rhs_134 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_133); mph_gc_push_root(ctx, (void**)&_rhs_134); MorphString* _ret_135 = mph_string_concat(ctx, _lhs_133, _rhs_134); mph_gc_pop_roots(ctx, 2); _ret_135; }); mph_gc_push_root(ctx, (void**)&_val_137); _obj_136->output = _val_137; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_143 = cg; mph_gc_push_root(ctx, (void**)&_obj_143); MorphString* _val_144 = ({ MorphString* _lhs_140 = ({ mph_codegen_Codegen* _obj_138 = cg; mph_gc_push_root(ctx, (void**)&_obj_138); MorphString* _ret_139 = _obj_138->output; mph_gc_pop_roots(ctx, 1); _ret_139; }); MorphString* _rhs_141 = mph_string_new(ctx, "// Entry Point\n"); mph_gc_push_root(ctx, (void**)&_lhs_140); mph_gc_push_root(ctx, (void**)&_rhs_141); MorphString* _ret_142 = mph_string_concat(ctx, _lhs_140, _rhs_141); mph_gc_pop_roots(ctx, 2); _ret_142; }); mph_gc_push_root(ctx, (void**)&_val_144); _obj_143->output = _val_144; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_150 = cg; mph_gc_push_root(ctx, (void**)&_obj_150); MorphString* _val_151 = ({ MorphString* _lhs_147 = ({ mph_codegen_Codegen* _obj_145 = cg; mph_gc_push_root(ctx, (void**)&_obj_145); MorphString* _ret_146 = _obj_145->output; mph_gc_pop_roots(ctx, 1); _ret_146; }); MorphString* _rhs_148 = mph_string_new(ctx, "void morph_entry_point(MorphContext* ctx) {\n"); mph_gc_push_root(ctx, (void**)&_lhs_147); mph_gc_push_root(ctx, (void**)&_rhs_148); MorphString* _ret_149 = mph_string_concat(ctx, _lhs_147, _rhs_148); mph_gc_pop_roots(ctx, 2); _ret_149; }); mph_gc_push_root(ctx, (void**)&_val_151); _obj_150->output = _val_151; mph_gc_pop_roots(ctx, 2); });
	({ mph_codegen_Codegen* _obj_159 = cg; mph_gc_push_root(ctx, (void**)&_obj_159); MorphString* _val_160 = ({ MorphString* _lhs_156 = ({ mph_codegen_Codegen* _obj_152 = cg; mph_gc_push_root(ctx, (void**)&_obj_152); MorphString* _ret_153 = _obj_152->output; mph_gc_pop_roots(ctx, 1); _ret_153; }); MorphString* _rhs_157 = ({ mph_codegen_Codegen* _obj_154 = cg; mph_gc_push_root(ctx, (void**)&_obj_154); MorphString* _ret_155 = _obj_154->entry_body; mph_gc_pop_roots(ctx, 1); _ret_155; }); mph_gc_push_root(ctx, (void**)&_lhs_156); mph_gc_push_root(ctx, (void**)&_rhs_157); MorphString* _ret_158 = mph_string_concat(ctx, _lhs_156, _rhs_157); mph_gc_pop_roots(ctx, 2); _ret_158; }); mph_gc_push_root(ctx, (void**)&_val_160); _obj_159->output = _val_160; mph_gc_pop_roots(ctx, 2); });
	if (({ mph_codegen_Codegen* _obj_161 = cg; mph_gc_push_root(ctx, (void**)&_obj_161); mph_bool _ret_162 = _obj_161->has_main; mph_gc_pop_roots(ctx, 1); _ret_162; })) {
{
	({ mph_codegen_Codegen* _obj_168 = cg; mph_gc_push_root(ctx, (void**)&_obj_168); MorphString* _val_169 = ({ MorphString* _lhs_165 = ({ mph_codegen_Codegen* _obj_163 = cg; mph_gc_push_root(ctx, (void**)&_obj_163); MorphString* _ret_164 = _obj_163->output; mph_gc_pop_roots(ctx, 1); _ret_164; }); MorphString* _rhs_166 = mph_string_new(ctx, "\tmph_main(ctx, NULL);\n"); mph_gc_push_root(ctx, (void**)&_lhs_165); mph_gc_push_root(ctx, (void**)&_rhs_166); MorphString* _ret_167 = mph_string_concat(ctx, _lhs_165, _rhs_166); mph_gc_pop_roots(ctx, 2); _ret_167; }); mph_gc_push_root(ctx, (void**)&_val_169); _obj_168->output = _val_169; mph_gc_pop_roots(ctx, 2); });
}
	}
	({ mph_codegen_Codegen* _obj_175 = cg; mph_gc_push_root(ctx, (void**)&_obj_175); MorphString* _val_176 = ({ MorphString* _lhs_172 = ({ mph_codegen_Codegen* _obj_170 = cg; mph_gc_push_root(ctx, (void**)&_obj_170); MorphString* _ret_171 = _obj_170->output; mph_gc_pop_roots(ctx, 1); _ret_171; }); MorphString* _rhs_173 = mph_string_new(ctx, "}\n"); mph_gc_push_root(ctx, (void**)&_lhs_172); mph_gc_push_root(ctx, (void**)&_rhs_173); MorphString* _ret_174 = mph_string_concat(ctx, _lhs_172, _rhs_173); mph_gc_pop_roots(ctx, 2); _ret_174; }); mph_gc_push_root(ctx, (void**)&_val_176); _obj_175->output = _val_176; mph_gc_pop_roots(ctx, 2); });
	return ({ mph_codegen_Codegen* _obj_177 = cg; mph_gc_push_root(ctx, (void**)&_obj_177); MorphString* _ret_178 = _obj_177->output; mph_gc_pop_roots(ctx, 1); _ret_178; });
	mph_gc_pop_roots(ctx, 2);
}

void mph_codegen_codegen_compile_program(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_codegen_Codegen* _obj_179 = cg; mph_gc_push_root(ctx, (void**)&_obj_179); MorphString* _val_180 = prefix; mph_gc_push_root(ctx, (void**)&_val_180); _obj_179->current_prefix = _val_180; mph_gc_pop_roots(ctx, 2); });
	mph_int i = 0;
	while ((i < ({ mph_ast_Program* _obj_181 = prog; mph_gc_push_root(ctx, (void**)&_obj_181); mph_int _ret_182 = _obj_181->statements_count; mph_gc_pop_roots(ctx, 1); _ret_182; }))) {
{
	i = (i + 1);
}
	}
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_codegen_next_temp(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, MorphString* prefix) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prefix);
	({ mph_codegen_Codegen* _obj_185 = cg; mph_gc_push_root(ctx, (void**)&_obj_185); _obj_185->temp_index = (({ mph_codegen_Codegen* _obj_183 = cg; mph_gc_push_root(ctx, (void**)&_obj_183); mph_int _ret_184 = _obj_183->temp_index; mph_gc_pop_roots(ctx, 1); _ret_184; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return mph_string_new(ctx, "_tmp_1");
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_append(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	return ({ MorphString* _lhs_186 = buf; MorphString* _rhs_187 = text; mph_gc_push_root(ctx, (void**)&_lhs_186); mph_gc_push_root(ctx, (void**)&_rhs_187); MorphString* _ret_188 = mph_string_concat(ctx, _lhs_186, _rhs_187); mph_gc_pop_roots(ctx, 2); _ret_188; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_append_line(MorphContext* ctx, void* _env_void, MorphString* buf, MorphString* text) {
	mph_gc_push_root(ctx, (void**)&buf);
	mph_gc_push_root(ctx, (void**)&text);
	return ({ MorphString* _lhs_192 = ({ MorphString* _lhs_189 = buf; MorphString* _rhs_190 = text; mph_gc_push_root(ctx, (void**)&_lhs_189); mph_gc_push_root(ctx, (void**)&_rhs_190); MorphString* _ret_191 = mph_string_concat(ctx, _lhs_189, _rhs_190); mph_gc_pop_roots(ctx, 2); _ret_191; }); MorphString* _rhs_193 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_192); mph_gc_push_root(ctx, (void**)&_rhs_193); MorphString* _ret_194 = mph_string_concat(ctx, _lhs_192, _rhs_193); mph_gc_pop_roots(ctx, 2); _ret_194; });
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
	indent = ({ MorphString* _lhs_195 = indent; MorphString* _rhs_196 = mph_string_new(ctx, "\t"); mph_gc_push_root(ctx, (void**)&_lhs_195); mph_gc_push_root(ctx, (void**)&_rhs_196); MorphString* _ret_197 = mph_string_concat(ctx, _lhs_195, _rhs_196); mph_gc_pop_roots(ctx, 2); _ret_197; });
	i = (i + 1);
}
	}
	return ({ MorphString* _lhs_204 = ({ MorphString* _lhs_201 = ({ MorphString* _lhs_198 = buf; MorphString* _rhs_199 = indent; mph_gc_push_root(ctx, (void**)&_lhs_198); mph_gc_push_root(ctx, (void**)&_rhs_199); MorphString* _ret_200 = mph_string_concat(ctx, _lhs_198, _rhs_199); mph_gc_pop_roots(ctx, 2); _ret_200; }); MorphString* _rhs_202 = text; mph_gc_push_root(ctx, (void**)&_lhs_201); mph_gc_push_root(ctx, (void**)&_rhs_202); MorphString* _ret_203 = mph_string_concat(ctx, _lhs_201, _rhs_202); mph_gc_pop_roots(ctx, 2); _ret_203; }); MorphString* _rhs_205 = mph_string_new(ctx, "\n"); mph_gc_push_root(ctx, (void**)&_lhs_204); mph_gc_push_root(ctx, (void**)&_rhs_205); MorphString* _ret_206 = mph_string_concat(ctx, _lhs_204, _rhs_205); mph_gc_pop_roots(ctx, 2); _ret_206; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_codegen_compile_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return mph_stdlib_codegen_IntToString(ctx, NULL, ({ mph_ast_IntegerLiteral* _obj_207 = lit; mph_gc_push_root(ctx, (void**)&_obj_207); mph_int _ret_208 = _obj_207->value; mph_gc_pop_roots(ctx, 1); _ret_208; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	MorphString* escaped = ({ MorphString* _arg_211 = ({ mph_ast_StringLiteral* _obj_209 = lit; mph_gc_push_root(ctx, (void**)&_obj_209); MorphString* _ret_210 = _obj_209->value; mph_gc_pop_roots(ctx, 1); _ret_210; }); mph_gc_push_root(ctx, (void**)&_arg_211); MorphString* _ret_212 = mph_stdlib_codegen_StringEscape(ctx, NULL, _arg_211); mph_gc_pop_roots(ctx, 1); _ret_212; });
	mph_gc_push_root(ctx, (void**)&escaped);
	return ({ MorphString* _lhs_216 = ({ MorphString* _lhs_213 = mph_string_new(ctx, "mph_string_new(ctx, \""); MorphString* _rhs_214 = escaped; mph_gc_push_root(ctx, (void**)&_lhs_213); mph_gc_push_root(ctx, (void**)&_rhs_214); MorphString* _ret_215 = mph_string_concat(ctx, _lhs_213, _rhs_214); mph_gc_pop_roots(ctx, 2); _ret_215; }); MorphString* _rhs_217 = mph_string_new(ctx, "\")"); mph_gc_push_root(ctx, (void**)&_lhs_216); mph_gc_push_root(ctx, (void**)&_rhs_217); MorphString* _ret_218 = mph_string_concat(ctx, _lhs_216, _rhs_217); mph_gc_pop_roots(ctx, 2); _ret_218; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	if (({ mph_ast_BooleanLiteral* _obj_219 = lit; mph_gc_push_root(ctx, (void**)&_obj_219); mph_bool _ret_220 = _obj_219->value; mph_gc_pop_roots(ctx, 1); _ret_220; })) {
{
	return mph_string_new(ctx, "1");
}
	}
	return mph_string_new(ctx, "0");
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_codegen_compile_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	return ({ mph_ast_Identifier* _obj_221 = ident; mph_gc_push_root(ctx, (void**)&_obj_221); MorphString* _ret_222 = _obj_221->value; mph_gc_pop_roots(ctx, 1); _ret_222; });
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
	return ({ MorphString* _lhs_238 = ({ MorphString* _lhs_235 = ({ MorphString* _lhs_232 = ({ MorphString* _lhs_229 = ({ MorphString* _lhs_226 = ({ MorphString* _lhs_223 = mph_string_new(ctx, "("); MorphString* _rhs_224 = left_code; mph_gc_push_root(ctx, (void**)&_lhs_223); mph_gc_push_root(ctx, (void**)&_rhs_224); MorphString* _ret_225 = mph_string_concat(ctx, _lhs_223, _rhs_224); mph_gc_pop_roots(ctx, 2); _ret_225; }); MorphString* _rhs_227 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_226); mph_gc_push_root(ctx, (void**)&_rhs_227); MorphString* _ret_228 = mph_string_concat(ctx, _lhs_226, _rhs_227); mph_gc_pop_roots(ctx, 2); _ret_228; }); MorphString* _rhs_230 = c_operator; mph_gc_push_root(ctx, (void**)&_lhs_229); mph_gc_push_root(ctx, (void**)&_rhs_230); MorphString* _ret_231 = mph_string_concat(ctx, _lhs_229, _rhs_230); mph_gc_pop_roots(ctx, 2); _ret_231; }); MorphString* _rhs_233 = mph_string_new(ctx, " "); mph_gc_push_root(ctx, (void**)&_lhs_232); mph_gc_push_root(ctx, (void**)&_rhs_233); MorphString* _ret_234 = mph_string_concat(ctx, _lhs_232, _rhs_233); mph_gc_pop_roots(ctx, 2); _ret_234; }); MorphString* _rhs_236 = right_code; mph_gc_push_root(ctx, (void**)&_lhs_235); mph_gc_push_root(ctx, (void**)&_rhs_236); MorphString* _ret_237 = mph_string_concat(ctx, _lhs_235, _rhs_236); mph_gc_pop_roots(ctx, 2); _ret_237; }); MorphString* _rhs_239 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_lhs_238); mph_gc_push_root(ctx, (void**)&_rhs_239); MorphString* _ret_240 = mph_string_concat(ctx, _lhs_238, _rhs_239); mph_gc_pop_roots(ctx, 2); _ret_240; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_codegen_compile_var_statement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _lhs_250 = ({ MorphString* _lhs_247 = ({ MorphString* _lhs_244 = ({ MorphString* _lhs_241 = mph_string_new(ctx, "\tmph_int "); MorphString* _rhs_242 = name; mph_gc_push_root(ctx, (void**)&_lhs_241); mph_gc_push_root(ctx, (void**)&_rhs_242); MorphString* _ret_243 = mph_string_concat(ctx, _lhs_241, _rhs_242); mph_gc_pop_roots(ctx, 2); _ret_243; }); MorphString* _rhs_245 = mph_string_new(ctx, " = "); mph_gc_push_root(ctx, (void**)&_lhs_244); mph_gc_push_root(ctx, (void**)&_rhs_245); MorphString* _ret_246 = mph_string_concat(ctx, _lhs_244, _rhs_245); mph_gc_pop_roots(ctx, 2); _ret_246; }); MorphString* _rhs_248 = value_code; mph_gc_push_root(ctx, (void**)&_lhs_247); mph_gc_push_root(ctx, (void**)&_rhs_248); MorphString* _ret_249 = mph_string_concat(ctx, _lhs_247, _rhs_248); mph_gc_pop_roots(ctx, 2); _ret_249; }); MorphString* _rhs_251 = mph_string_new(ctx, ";\n"); mph_gc_push_root(ctx, (void**)&_lhs_250); mph_gc_push_root(ctx, (void**)&_rhs_251); MorphString* _ret_252 = mph_string_concat(ctx, _lhs_250, _rhs_251); mph_gc_pop_roots(ctx, 2); _ret_252; });
	mph_gc_pop_roots(ctx, 2);
}

mph_codegen_Codegen* mph_codegen_NewCodegen(MorphContext* ctx, void* _env_void) {
	return mph_codegen_new_codegen(ctx, NULL);
}

MorphString* mph_codegen_CodegenCompile(MorphContext* ctx, void* _env_void, mph_codegen_Codegen* cg, mph_ast_Program* prog) {
	mph_gc_push_root(ctx, (void**)&cg);
	mph_gc_push_root(ctx, (void**)&prog);
	return ({ mph_codegen_Codegen* _arg_253 = cg; mph_gc_push_root(ctx, (void**)&_arg_253); mph_ast_Program* _arg_254 = prog; mph_gc_push_root(ctx, (void**)&_arg_254); MorphString* _ret_255 = mph_codegen_codegen_compile(ctx, NULL, _arg_253, _arg_254); mph_gc_pop_roots(ctx, 2); _ret_255; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_codegen_CompileIntegerLiteral(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_IntegerLiteral* _arg_256 = lit; mph_gc_push_root(ctx, (void**)&_arg_256); MorphString* _ret_257 = mph_codegen_codegen_compile_integer_literal(ctx, NULL, _arg_256); mph_gc_pop_roots(ctx, 1); _ret_257; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileStringLiteral(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_StringLiteral* _arg_258 = lit; mph_gc_push_root(ctx, (void**)&_arg_258); MorphString* _ret_259 = mph_codegen_codegen_compile_string_literal(ctx, NULL, _arg_258); mph_gc_pop_roots(ctx, 1); _ret_259; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileBooleanLiteral(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	return ({ mph_ast_BooleanLiteral* _arg_260 = lit; mph_gc_push_root(ctx, (void**)&_arg_260); MorphString* _ret_261 = mph_codegen_codegen_compile_boolean_literal(ctx, NULL, _arg_260); mph_gc_pop_roots(ctx, 1); _ret_261; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileIdentifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	return ({ mph_ast_Identifier* _arg_262 = ident; mph_gc_push_root(ctx, (void**)&_arg_262); MorphString* _ret_263 = mph_codegen_codegen_compile_identifier(ctx, NULL, _arg_262); mph_gc_pop_roots(ctx, 1); _ret_263; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_codegen_CompileInfix(MorphContext* ctx, void* _env_void, MorphString* left_code, MorphString* operator, MorphString* right_code) {
	mph_gc_push_root(ctx, (void**)&left_code);
	mph_gc_push_root(ctx, (void**)&operator);
	mph_gc_push_root(ctx, (void**)&right_code);
	return ({ MorphString* _arg_264 = left_code; mph_gc_push_root(ctx, (void**)&_arg_264); MorphString* _arg_265 = operator; mph_gc_push_root(ctx, (void**)&_arg_265); MorphString* _arg_266 = right_code; mph_gc_push_root(ctx, (void**)&_arg_266); MorphString* _ret_267 = mph_codegen_codegen_compile_infix(ctx, NULL, _arg_264, _arg_265, _arg_266); mph_gc_pop_roots(ctx, 3); _ret_267; });
	mph_gc_pop_roots(ctx, 3);
}

MorphString* mph_codegen_CompileVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* value_code) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&value_code);
	return ({ MorphString* _arg_268 = name; mph_gc_push_root(ctx, (void**)&_arg_268); MorphString* _arg_269 = value_code; mph_gc_push_root(ctx, (void**)&_arg_269); MorphString* _ret_270 = mph_codegen_codegen_compile_var_statement(ctx, NULL, _arg_268, _arg_269); mph_gc_pop_roots(ctx, 2); _ret_270; });
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_Node* mph_ast_MakeNode(MorphContext* ctx, void* _env_void, mph_int node_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_ast_Node* _t = (mph_ast_Node*)mph_alloc(ctx, sizeof(mph_ast_Node), &mph_ti_mph_ast_Node); mph_gc_push_root(ctx, (void**)&_t); _t->node_type = node_type; _t->token_literal = literal; _t->line = line; _t->column = column; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Program* mph_ast_MakeProgram(MorphContext* ctx, void* _env_void) {
	mph_ast_Node* base = ({ MorphString* _arg_271 = mph_string_new(ctx, "program"); mph_gc_push_root(ctx, (void**)&_arg_271); mph_ast_Node* _ret_272 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PROGRAM, _arg_271, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_272; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_Program* _t = (mph_ast_Program*)mph_alloc(ctx, sizeof(mph_ast_Program), &mph_ti_mph_ast_Program); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->statements_count = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_Identifier* mph_ast_MakeIdentifier(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_273 = name; mph_gc_push_root(ctx, (void**)&_arg_273); mph_ast_Node* _ret_274 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IDENTIFIER, _arg_273, line, column); mph_gc_pop_roots(ctx, 1); _ret_274; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_Identifier* _t = (mph_ast_Identifier*)mph_alloc(ctx, sizeof(mph_ast_Identifier), &mph_ti_mph_ast_Identifier); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = name; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_IntegerLiteral* mph_ast_MakeIntegerLiteral(MorphContext* ctx, void* _env_void, mph_int value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_275 = literal; mph_gc_push_root(ctx, (void**)&_arg_275); mph_ast_Node* _ret_276 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INTEGER_LITERAL, _arg_275, line, column); mph_gc_pop_roots(ctx, 1); _ret_276; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_IntegerLiteral* _t = (mph_ast_IntegerLiteral*)mph_alloc(ctx, sizeof(mph_ast_IntegerLiteral), &mph_ti_mph_ast_IntegerLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StringLiteral* mph_ast_MakeStringLiteral(MorphContext* ctx, void* _env_void, MorphString* value, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&value);
	mph_ast_Node* base = ({ MorphString* _arg_277 = value; mph_gc_push_root(ctx, (void**)&_arg_277); mph_ast_Node* _ret_278 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRING_LITERAL, _arg_277, line, column); mph_gc_pop_roots(ctx, 1); _ret_278; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StringLiteral* _t = (mph_ast_StringLiteral*)mph_alloc(ctx, sizeof(mph_ast_StringLiteral), &mph_ti_mph_ast_StringLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->value = value; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BooleanLiteral* mph_ast_MakeBooleanLiteral(MorphContext* ctx, void* _env_void, mph_bool value, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	mph_ast_Node* base = ({ MorphString* _arg_279 = literal; mph_gc_push_root(ctx, (void**)&_arg_279); mph_ast_Node* _ret_280 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BOOLEAN_LITERAL, _arg_279, line, column); mph_gc_pop_roots(ctx, 1); _ret_280; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BooleanLiteral* _t = (mph_ast_BooleanLiteral*)mph_alloc(ctx, sizeof(mph_ast_BooleanLiteral), &mph_ti_mph_ast_BooleanLiteral); mph_gc_push_root(ctx, (void**)&_t); _t->value = value; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_VarStatement* mph_ast_MakeVarStatement(MorphContext* ctx, void* _env_void, MorphString* name, MorphString* type_str, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_gc_push_root(ctx, (void**)&type_str);
	mph_ast_Node* base = ({ MorphString* _arg_281 = mph_string_new(ctx, "var"); mph_gc_push_root(ctx, (void**)&_arg_281); mph_ast_Node* _ret_282 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_VAR_STATEMENT, _arg_281, line, column); mph_gc_pop_roots(ctx, 1); _ret_282; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_VarStatement* _t = (mph_ast_VarStatement*)mph_alloc(ctx, sizeof(mph_ast_VarStatement), &mph_ti_mph_ast_VarStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->name = name; _t->value_type = type_str; _t->has_value = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 2);
}

mph_ast_PrefixExpression* mph_ast_MakePrefixExpression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_283 = operator; mph_gc_push_root(ctx, (void**)&_arg_283); mph_ast_Node* _ret_284 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_PREFIX_EXPRESSION, _arg_283, line, column); mph_gc_pop_roots(ctx, 1); _ret_284; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_PrefixExpression* _t = (mph_ast_PrefixExpression*)mph_alloc(ctx, sizeof(mph_ast_PrefixExpression), &mph_ti_mph_ast_PrefixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_InfixExpression* mph_ast_make_infix_expression(MorphContext* ctx, void* _env_void, MorphString* operator, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&operator);
	mph_ast_Node* base = ({ MorphString* _arg_285 = operator; mph_gc_push_root(ctx, (void**)&_arg_285); mph_ast_Node* _ret_286 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_INFIX_EXPRESSION, _arg_285, line, column); mph_gc_pop_roots(ctx, 1); _ret_286; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_InfixExpression* _t = (mph_ast_InfixExpression*)mph_alloc(ctx, sizeof(mph_ast_InfixExpression), &mph_ti_mph_ast_InfixExpression); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->operator = operator; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_make_case_clause(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_287 = mph_string_new(ctx, "kasus"); mph_gc_push_root(ctx, (void**)&_arg_287); mph_ast_Node* _ret_288 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CASE_CLAUSE, _arg_287, line, column); mph_gc_pop_roots(ctx, 1); _ret_288; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_CaseClause* _t = (mph_ast_CaseClause*)mph_alloc(ctx, sizeof(mph_ast_CaseClause), &mph_ti_mph_ast_CaseClause); mph_gc_push_root(ctx, (void**)&_t); _t->v2 = 0; _t->v3 = 0; _t->has_body = 0; _t->base = base; _t->values_count = 0; _t->v0 = 0; _t->v1 = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_CaseClause* mph_ast_case_add_value(MorphContext* ctx, void* _env_void, mph_ast_CaseClause* c, mph_int val) {
	mph_gc_push_root(ctx, (void**)&c);
	if ((({ mph_ast_CaseClause* _obj_289 = c; mph_gc_push_root(ctx, (void**)&_obj_289); mph_int _ret_290 = _obj_289->values_count; mph_gc_pop_roots(ctx, 1); _ret_290; }) == 0)) {
{
	({ mph_ast_CaseClause* _obj_291 = c; mph_gc_push_root(ctx, (void**)&_obj_291); _obj_291->v0 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_292 = c; mph_gc_push_root(ctx, (void**)&_obj_292); mph_int _ret_293 = _obj_292->values_count; mph_gc_pop_roots(ctx, 1); _ret_293; }) == 1)) {
{
	({ mph_ast_CaseClause* _obj_294 = c; mph_gc_push_root(ctx, (void**)&_obj_294); _obj_294->v1 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_295 = c; mph_gc_push_root(ctx, (void**)&_obj_295); mph_int _ret_296 = _obj_295->values_count; mph_gc_pop_roots(ctx, 1); _ret_296; }) == 2)) {
{
	({ mph_ast_CaseClause* _obj_297 = c; mph_gc_push_root(ctx, (void**)&_obj_297); _obj_297->v2 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	if ((({ mph_ast_CaseClause* _obj_298 = c; mph_gc_push_root(ctx, (void**)&_obj_298); mph_int _ret_299 = _obj_298->values_count; mph_gc_pop_roots(ctx, 1); _ret_299; }) == 3)) {
{
	({ mph_ast_CaseClause* _obj_300 = c; mph_gc_push_root(ctx, (void**)&_obj_300); _obj_300->v3 = val; mph_gc_pop_roots(ctx, 1); });
}
	}
	({ mph_ast_CaseClause* _obj_303 = c; mph_gc_push_root(ctx, (void**)&_obj_303); _obj_303->values_count = (({ mph_ast_CaseClause* _obj_301 = c; mph_gc_push_root(ctx, (void**)&_obj_301); mph_int _ret_302 = _obj_301->values_count; mph_gc_pop_roots(ctx, 1); _ret_302; }) + 1); mph_gc_pop_roots(ctx, 1); });
	return c;
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_SwitchStatement* mph_ast_make_switch_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_304 = mph_string_new(ctx, "pilih"); mph_gc_push_root(ctx, (void**)&_arg_304); mph_ast_Node* _ret_305 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_SWITCH_STATEMENT, _arg_304, line, column); mph_gc_pop_roots(ctx, 1); _ret_305; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_SwitchStatement* _t = (mph_ast_SwitchStatement*)mph_alloc(ctx, sizeof(mph_ast_SwitchStatement), &mph_ti_mph_ast_SwitchStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->cases_count = 0; _t->has_default = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_WhileStatement* mph_ast_make_while_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_306 = mph_string_new(ctx, "selama"); mph_gc_push_root(ctx, (void**)&_arg_306); mph_ast_Node* _ret_307 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_WHILE_STATEMENT, _arg_306, line, column); mph_gc_pop_roots(ctx, 1); _ret_307; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_WhileStatement* _t = (mph_ast_WhileStatement*)mph_alloc(ctx, sizeof(mph_ast_WhileStatement), &mph_ti_mph_ast_WhileStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; _t->has_body = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_StructStatement* mph_ast_make_struct_statement(MorphContext* ctx, void* _env_void, MorphString* name, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_ast_Node* base = ({ MorphString* _arg_308 = mph_string_new(ctx, "struktur"); mph_gc_push_root(ctx, (void**)&_arg_308); mph_ast_Node* _ret_309 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_STRUCT_STATEMENT, _arg_308, line, column); mph_gc_pop_roots(ctx, 1); _ret_309; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_StructStatement* _t = (mph_ast_StructStatement*)mph_alloc(ctx, sizeof(mph_ast_StructStatement), &mph_ti_mph_ast_StructStatement); mph_gc_push_root(ctx, (void**)&_t); _t->name = name; _t->fields_count = 0; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ImportStatement* mph_ast_make_import_statement(MorphContext* ctx, void* _env_void, MorphString* path, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&path);
	mph_ast_Node* base = ({ MorphString* _arg_310 = mph_string_new(ctx, "ambil"); mph_gc_push_root(ctx, (void**)&_arg_310); mph_ast_Node* _ret_311 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_IMPORT_STATEMENT, _arg_310, line, column); mph_gc_pop_roots(ctx, 1); _ret_311; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_ImportStatement* _t = (mph_ast_ImportStatement*)mph_alloc(ctx, sizeof(mph_ast_ImportStatement), &mph_ti_mph_ast_ImportStatement); mph_gc_push_root(ctx, (void**)&_t); _t->path = path; _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_BreakStatement* mph_ast_make_break_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_312 = mph_string_new(ctx, "putus"); mph_gc_push_root(ctx, (void**)&_arg_312); mph_ast_Node* _ret_313 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_BREAK_STATEMENT, _arg_312, line, column); mph_gc_pop_roots(ctx, 1); _ret_313; });
	mph_gc_push_root(ctx, (void**)&base);
	return ({ mph_ast_BreakStatement* _t = (mph_ast_BreakStatement*)mph_alloc(ctx, sizeof(mph_ast_BreakStatement), &mph_ti_mph_ast_BreakStatement); mph_gc_push_root(ctx, (void**)&_t); _t->base = base; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_ast_ContinueStatement* mph_ast_make_continue_statement(MorphContext* ctx, void* _env_void, mph_int line, mph_int column) {
	mph_ast_Node* base = ({ MorphString* _arg_314 = mph_string_new(ctx, "lanjut"); mph_gc_push_root(ctx, (void**)&_arg_314); mph_ast_Node* _ret_315 = mph_ast_MakeNode(ctx, NULL, mph_ast_NODE_CONTINUE_STATEMENT, _arg_314, line, column); mph_gc_pop_roots(ctx, 1); _ret_315; });
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
	mph_native_print(ctx, mph_ast_node_type_string(ctx, NULL, ({ mph_ast_Node* _obj_316 = node; mph_gc_push_root(ctx, (void**)&_obj_316); mph_int _ret_317 = _obj_316->node_type; mph_gc_pop_roots(ctx, 1); _ret_317; })));
	mph_native_print(ctx, mph_string_new(ctx, " at line "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_318 = node; mph_gc_push_root(ctx, (void**)&_obj_318); mph_int _ret_319 = _obj_318->line; mph_gc_pop_roots(ctx, 1); _ret_319; }));
	mph_native_print(ctx, mph_string_new(ctx, ", column "));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_320 = node; mph_gc_push_root(ctx, (void**)&_obj_320); mph_int _ret_321 = _obj_320->column; mph_gc_pop_roots(ctx, 1); _ret_321; }));
	mph_native_print(ctx, mph_string_new(ctx, "\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_identifier(MorphContext* ctx, void* _env_void, mph_ast_Identifier* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	mph_native_print(ctx, mph_string_new(ctx, "Identifier: "));
	mph_native_print(ctx, ({ mph_ast_Identifier* _obj_322 = ident; mph_gc_push_root(ctx, (void**)&_obj_322); MorphString* _ret_323 = _obj_322->value; mph_gc_pop_roots(ctx, 1); _ret_323; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_326 = ({ mph_ast_Identifier* _obj_324 = ident; mph_gc_push_root(ctx, (void**)&_obj_324); mph_ast_Node* _ret_325 = _obj_324->base; mph_gc_pop_roots(ctx, 1); _ret_325; }); mph_gc_push_root(ctx, (void**)&_obj_326); mph_int _ret_327 = _obj_326->line; mph_gc_pop_roots(ctx, 1); _ret_327; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_330 = ({ mph_ast_Identifier* _obj_328 = ident; mph_gc_push_root(ctx, (void**)&_obj_328); mph_ast_Node* _ret_329 = _obj_328->base; mph_gc_pop_roots(ctx, 1); _ret_329; }); mph_gc_push_root(ctx, (void**)&_obj_330); mph_int _ret_331 = _obj_330->column; mph_gc_pop_roots(ctx, 1); _ret_331; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_integer_literal(MorphContext* ctx, void* _env_void, mph_ast_IntegerLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "IntegerLiteral: "));
	mph_native_print_int(ctx, ({ mph_ast_IntegerLiteral* _obj_332 = lit; mph_gc_push_root(ctx, (void**)&_obj_332); mph_int _ret_333 = _obj_332->value; mph_gc_pop_roots(ctx, 1); _ret_333; }));
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_336 = ({ mph_ast_IntegerLiteral* _obj_334 = lit; mph_gc_push_root(ctx, (void**)&_obj_334); mph_ast_Node* _ret_335 = _obj_334->base; mph_gc_pop_roots(ctx, 1); _ret_335; }); mph_gc_push_root(ctx, (void**)&_obj_336); mph_int _ret_337 = _obj_336->line; mph_gc_pop_roots(ctx, 1); _ret_337; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_340 = ({ mph_ast_IntegerLiteral* _obj_338 = lit; mph_gc_push_root(ctx, (void**)&_obj_338); mph_ast_Node* _ret_339 = _obj_338->base; mph_gc_pop_roots(ctx, 1); _ret_339; }); mph_gc_push_root(ctx, (void**)&_obj_340); mph_int _ret_341 = _obj_340->column; mph_gc_pop_roots(ctx, 1); _ret_341; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_string_literal(MorphContext* ctx, void* _env_void, mph_ast_StringLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "StringLiteral: \""));
	mph_native_print(ctx, ({ mph_ast_StringLiteral* _obj_342 = lit; mph_gc_push_root(ctx, (void**)&_obj_342); MorphString* _ret_343 = _obj_342->value; mph_gc_pop_roots(ctx, 1); _ret_343; }));
	mph_native_print(ctx, mph_string_new(ctx, "\" ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_346 = ({ mph_ast_StringLiteral* _obj_344 = lit; mph_gc_push_root(ctx, (void**)&_obj_344); mph_ast_Node* _ret_345 = _obj_344->base; mph_gc_pop_roots(ctx, 1); _ret_345; }); mph_gc_push_root(ctx, (void**)&_obj_346); mph_int _ret_347 = _obj_346->line; mph_gc_pop_roots(ctx, 1); _ret_347; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_350 = ({ mph_ast_StringLiteral* _obj_348 = lit; mph_gc_push_root(ctx, (void**)&_obj_348); mph_ast_Node* _ret_349 = _obj_348->base; mph_gc_pop_roots(ctx, 1); _ret_349; }); mph_gc_push_root(ctx, (void**)&_obj_350); mph_int _ret_351 = _obj_350->column; mph_gc_pop_roots(ctx, 1); _ret_351; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
}

void mph_ast_print_boolean_literal(MorphContext* ctx, void* _env_void, mph_ast_BooleanLiteral* lit) {
	mph_gc_push_root(ctx, (void**)&lit);
	mph_native_print(ctx, mph_string_new(ctx, "BooleanLiteral: "));
	if (({ mph_ast_BooleanLiteral* _obj_352 = lit; mph_gc_push_root(ctx, (void**)&_obj_352); mph_bool _ret_353 = _obj_352->value; mph_gc_pop_roots(ctx, 1); _ret_353; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "benar"));
}
	} else {
{
	mph_native_print(ctx, mph_string_new(ctx, "salah"));
}
	}
	mph_native_print(ctx, mph_string_new(ctx, " ("));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_356 = ({ mph_ast_BooleanLiteral* _obj_354 = lit; mph_gc_push_root(ctx, (void**)&_obj_354); mph_ast_Node* _ret_355 = _obj_354->base; mph_gc_pop_roots(ctx, 1); _ret_355; }); mph_gc_push_root(ctx, (void**)&_obj_356); mph_int _ret_357 = _obj_356->line; mph_gc_pop_roots(ctx, 1); _ret_357; }));
	mph_native_print(ctx, mph_string_new(ctx, ":"));
	mph_native_print_int(ctx, ({ mph_ast_Node* _obj_360 = ({ mph_ast_BooleanLiteral* _obj_358 = lit; mph_gc_push_root(ctx, (void**)&_obj_358); mph_ast_Node* _ret_359 = _obj_358->base; mph_gc_pop_roots(ctx, 1); _ret_359; }); mph_gc_push_root(ctx, (void**)&_obj_360); mph_int _ret_361 = _obj_360->column; mph_gc_pop_roots(ctx, 1); _ret_361; }));
	mph_native_print(ctx, mph_string_new(ctx, ")\n"));
	mph_gc_pop_roots(ctx, 1);
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
	result = ({ MorphString* _lhs_362 = mph_string_new(ctx, "0"); MorphString* _rhs_363 = result; mph_gc_push_root(ctx, (void**)&_lhs_362); mph_gc_push_root(ctx, (void**)&_rhs_363); MorphString* _ret_364 = mph_string_concat(ctx, _lhs_362, _rhs_363); mph_gc_pop_roots(ctx, 2); _ret_364; });
}
	}
	if ((digit == 1)) {
{
	result = ({ MorphString* _lhs_365 = mph_string_new(ctx, "1"); MorphString* _rhs_366 = result; mph_gc_push_root(ctx, (void**)&_lhs_365); mph_gc_push_root(ctx, (void**)&_rhs_366); MorphString* _ret_367 = mph_string_concat(ctx, _lhs_365, _rhs_366); mph_gc_pop_roots(ctx, 2); _ret_367; });
}
	}
	if ((digit == 2)) {
{
	result = ({ MorphString* _lhs_368 = mph_string_new(ctx, "2"); MorphString* _rhs_369 = result; mph_gc_push_root(ctx, (void**)&_lhs_368); mph_gc_push_root(ctx, (void**)&_rhs_369); MorphString* _ret_370 = mph_string_concat(ctx, _lhs_368, _rhs_369); mph_gc_pop_roots(ctx, 2); _ret_370; });
}
	}
	if ((digit == 3)) {
{
	result = ({ MorphString* _lhs_371 = mph_string_new(ctx, "3"); MorphString* _rhs_372 = result; mph_gc_push_root(ctx, (void**)&_lhs_371); mph_gc_push_root(ctx, (void**)&_rhs_372); MorphString* _ret_373 = mph_string_concat(ctx, _lhs_371, _rhs_372); mph_gc_pop_roots(ctx, 2); _ret_373; });
}
	}
	if ((digit == 4)) {
{
	result = ({ MorphString* _lhs_374 = mph_string_new(ctx, "4"); MorphString* _rhs_375 = result; mph_gc_push_root(ctx, (void**)&_lhs_374); mph_gc_push_root(ctx, (void**)&_rhs_375); MorphString* _ret_376 = mph_string_concat(ctx, _lhs_374, _rhs_375); mph_gc_pop_roots(ctx, 2); _ret_376; });
}
	}
	if ((digit == 5)) {
{
	result = ({ MorphString* _lhs_377 = mph_string_new(ctx, "5"); MorphString* _rhs_378 = result; mph_gc_push_root(ctx, (void**)&_lhs_377); mph_gc_push_root(ctx, (void**)&_rhs_378); MorphString* _ret_379 = mph_string_concat(ctx, _lhs_377, _rhs_378); mph_gc_pop_roots(ctx, 2); _ret_379; });
}
	}
	if ((digit == 6)) {
{
	result = ({ MorphString* _lhs_380 = mph_string_new(ctx, "6"); MorphString* _rhs_381 = result; mph_gc_push_root(ctx, (void**)&_lhs_380); mph_gc_push_root(ctx, (void**)&_rhs_381); MorphString* _ret_382 = mph_string_concat(ctx, _lhs_380, _rhs_381); mph_gc_pop_roots(ctx, 2); _ret_382; });
}
	}
	if ((digit == 7)) {
{
	result = ({ MorphString* _lhs_383 = mph_string_new(ctx, "7"); MorphString* _rhs_384 = result; mph_gc_push_root(ctx, (void**)&_lhs_383); mph_gc_push_root(ctx, (void**)&_rhs_384); MorphString* _ret_385 = mph_string_concat(ctx, _lhs_383, _rhs_384); mph_gc_pop_roots(ctx, 2); _ret_385; });
}
	}
	if ((digit == 8)) {
{
	result = ({ MorphString* _lhs_386 = mph_string_new(ctx, "8"); MorphString* _rhs_387 = result; mph_gc_push_root(ctx, (void**)&_lhs_386); mph_gc_push_root(ctx, (void**)&_rhs_387); MorphString* _ret_388 = mph_string_concat(ctx, _lhs_386, _rhs_387); mph_gc_pop_roots(ctx, 2); _ret_388; });
}
	}
	if ((digit == 9)) {
{
	result = ({ MorphString* _lhs_389 = mph_string_new(ctx, "9"); MorphString* _rhs_390 = result; mph_gc_push_root(ctx, (void**)&_lhs_389); mph_gc_push_root(ctx, (void**)&_rhs_390); MorphString* _ret_391 = mph_string_concat(ctx, _lhs_389, _rhs_390); mph_gc_pop_roots(ctx, 2); _ret_391; });
}
	}
}
	}
	if (is_negative) {
{
	result = ({ MorphString* _lhs_392 = mph_string_new(ctx, "-"); MorphString* _rhs_393 = result; mph_gc_push_root(ctx, (void**)&_lhs_392); mph_gc_push_root(ctx, (void**)&_rhs_393); MorphString* _ret_394 = mph_string_concat(ctx, _lhs_392, _rhs_393); mph_gc_pop_roots(ctx, 2); _ret_394; });
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
	mph_int len = ({ MorphString* _len_arg_395 = s; mph_gc_push_root(ctx, (void**)&_len_arg_395); mph_int _ret_396 = ((MorphString*)_len_arg_395)->length; mph_gc_pop_roots(ctx, 1); _ret_396; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_397 = s; mph_gc_push_root(ctx, (void**)&_arg_397); MorphString* _ret_398 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_397, i); mph_gc_pop_roots(ctx, 1); _ret_398; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\\"))) {
{
	result = ({ MorphString* _lhs_399 = result; MorphString* _rhs_400 = mph_string_new(ctx, "\\\\"); mph_gc_push_root(ctx, (void**)&_lhs_399); mph_gc_push_root(ctx, (void**)&_rhs_400); MorphString* _ret_401 = mph_string_concat(ctx, _lhs_399, _rhs_400); mph_gc_pop_roots(ctx, 2); _ret_401; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\""))) {
{
	result = ({ MorphString* _lhs_402 = result; MorphString* _rhs_403 = mph_string_new(ctx, "\\\""); mph_gc_push_root(ctx, (void**)&_lhs_402); mph_gc_push_root(ctx, (void**)&_rhs_403); MorphString* _ret_404 = mph_string_concat(ctx, _lhs_402, _rhs_403); mph_gc_pop_roots(ctx, 2); _ret_404; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\n"))) {
{
	result = ({ MorphString* _lhs_405 = result; MorphString* _rhs_406 = mph_string_new(ctx, "\\n"); mph_gc_push_root(ctx, (void**)&_lhs_405); mph_gc_push_root(ctx, (void**)&_rhs_406); MorphString* _ret_407 = mph_string_concat(ctx, _lhs_405, _rhs_406); mph_gc_pop_roots(ctx, 2); _ret_407; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\r"))) {
{
	result = ({ MorphString* _lhs_408 = result; MorphString* _rhs_409 = mph_string_new(ctx, "\\r"); mph_gc_push_root(ctx, (void**)&_lhs_408); mph_gc_push_root(ctx, (void**)&_rhs_409); MorphString* _ret_410 = mph_string_concat(ctx, _lhs_408, _rhs_409); mph_gc_pop_roots(ctx, 2); _ret_410; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\t"))) {
{
	result = ({ MorphString* _lhs_411 = result; MorphString* _rhs_412 = mph_string_new(ctx, "\\t"); mph_gc_push_root(ctx, (void**)&_lhs_411); mph_gc_push_root(ctx, (void**)&_rhs_412); MorphString* _ret_413 = mph_string_concat(ctx, _lhs_411, _rhs_412); mph_gc_pop_roots(ctx, 2); _ret_413; });
}
	} else {
{
	result = ({ MorphString* _lhs_414 = result; MorphString* _rhs_415 = ch; mph_gc_push_root(ctx, (void**)&_lhs_414); mph_gc_push_root(ctx, (void**)&_rhs_415); MorphString* _ret_416 = mph_string_concat(ctx, _lhs_414, _rhs_415); mph_gc_pop_roots(ctx, 2); _ret_416; });
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
	mph_int len = ({ MorphString* _len_arg_417 = name; mph_gc_push_root(ctx, (void**)&_len_arg_417); mph_int _ret_418 = ((MorphString*)_len_arg_417)->length; mph_gc_pop_roots(ctx, 1); _ret_418; });
	if ((len == 0)) {
{
	return 0;
}
	}
	MorphString* first = ({ MorphString* _arg_419 = name; mph_gc_push_root(ctx, (void**)&_arg_419); MorphString* _ret_420 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_419, 0); mph_gc_pop_roots(ctx, 1); _ret_420; });
	mph_gc_push_root(ctx, (void**)&first);
	if (((first != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_421 = first; mph_gc_push_root(ctx, (void**)&_arg_421); mph_bool _ret_422 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_421); mph_gc_pop_roots(ctx, 1); _ret_422; })))) {
{
	return 0;
}
	}
	mph_int i = 1;
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_423 = name; mph_gc_push_root(ctx, (void**)&_arg_423); MorphString* _ret_424 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_423, i); mph_gc_pop_roots(ctx, 1); _ret_424; });
	mph_gc_push_root(ctx, (void**)&ch);
	if ((((ch != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_425 = ch; mph_gc_push_root(ctx, (void**)&_arg_425); mph_bool _ret_426 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_425); mph_gc_pop_roots(ctx, 1); _ret_426; }))) && (!({ MorphString* _arg_427 = ch; mph_gc_push_root(ctx, (void**)&_arg_427); mph_bool _ret_428 = mph_stdlib_codegen_is_digit(ctx, NULL, _arg_427); mph_gc_pop_roots(ctx, 1); _ret_428; })))) {
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
	mph_int len = ({ MorphString* _len_arg_429 = path; mph_gc_push_root(ctx, (void**)&_len_arg_429); mph_int _ret_430 = ((MorphString*)_len_arg_429)->length; mph_gc_pop_roots(ctx, 1); _ret_430; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_431 = path; mph_gc_push_root(ctx, (void**)&_arg_431); MorphString* _ret_432 = mph_stdlib_codegen_char_at(ctx, NULL, _arg_431, i); mph_gc_pop_roots(ctx, 1); _ret_432; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "/"))) {
{
	result = ({ MorphString* _lhs_433 = result; MorphString* _rhs_434 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_433); mph_gc_push_root(ctx, (void**)&_rhs_434); MorphString* _ret_435 = mph_string_concat(ctx, _lhs_433, _rhs_434); mph_gc_pop_roots(ctx, 2); _ret_435; });
}
	} else {
{
	if (((({ MorphString* _arg_436 = ch; mph_gc_push_root(ctx, (void**)&_arg_436); mph_bool _ret_437 = mph_stdlib_codegen_is_alpha(ctx, NULL, _arg_436); mph_gc_pop_roots(ctx, 1); _ret_437; }) || ({ MorphString* _arg_438 = ch; mph_gc_push_root(ctx, (void**)&_arg_438); mph_bool _ret_439 = mph_stdlib_codegen_is_digit(ctx, NULL, _arg_438); mph_gc_pop_roots(ctx, 1); _ret_439; })) || mph_string_eq(ctx, ch, mph_string_new(ctx, "_")))) {
{
	result = ({ MorphString* _lhs_440 = result; MorphString* _rhs_441 = ch; mph_gc_push_root(ctx, (void**)&_lhs_440); mph_gc_push_root(ctx, (void**)&_rhs_441); MorphString* _ret_442 = mph_string_concat(ctx, _lhs_440, _rhs_441); mph_gc_pop_roots(ctx, 2); _ret_442; });
}
	} else {
{
	result = ({ MorphString* _lhs_443 = result; MorphString* _rhs_444 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_443); mph_gc_push_root(ctx, (void**)&_rhs_444); MorphString* _ret_445 = mph_string_concat(ctx, _lhs_443, _rhs_444); mph_gc_pop_roots(ctx, 2); _ret_445; });
}
	}
}
	}
	i = (i + 1);
	mph_gc_pop_roots(ctx, 1);
}
	}
	result = ({ MorphString* _lhs_446 = result; MorphString* _rhs_447 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_446); mph_gc_push_root(ctx, (void**)&_rhs_447); MorphString* _ret_448 = mph_string_concat(ctx, _lhs_446, _rhs_447); mph_gc_pop_roots(ctx, 2); _ret_448; });
	return result;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_IntToString(MorphContext* ctx, void* _env_void, mph_int n) {
	return mph_stdlib_codegen_int_to_string(ctx, NULL, n);
}

MorphString* mph_stdlib_codegen_StringEscape(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	return ({ MorphString* _arg_449 = s; mph_gc_push_root(ctx, (void**)&_arg_449); MorphString* _ret_450 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_449); mph_gc_pop_roots(ctx, 1); _ret_450; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_stdlib_codegen_IsValidCIdent(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	return ({ MorphString* _arg_451 = name; mph_gc_push_root(ctx, (void**)&_arg_451); mph_bool _ret_452 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_451); mph_gc_pop_roots(ctx, 1); _ret_452; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_stdlib_codegen_ModuleToPrefix(MorphContext* ctx, void* _env_void, MorphString* path) {
	mph_gc_push_root(ctx, (void**)&path);
	return ({ MorphString* _arg_453 = path; mph_gc_push_root(ctx, (void**)&_arg_453); MorphString* _ret_454 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_453); mph_gc_pop_roots(ctx, 1); _ret_454; });
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
	MorphString* e1 = ({ MorphString* _arg_455 = mph_string_new(ctx, "hello"); mph_gc_push_root(ctx, (void**)&_arg_455); MorphString* _ret_456 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_455); mph_gc_pop_roots(ctx, 1); _ret_456; });
	mph_gc_push_root(ctx, (void**)&e1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\" â \""));
	mph_native_print(ctx, e1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* e2 = ({ MorphString* _arg_457 = mph_string_new(ctx, "hello\nworld"); mph_gc_push_root(ctx, (void**)&_arg_457); MorphString* _ret_458 = mph_stdlib_codegen_string_escape(ctx, NULL, _arg_457); mph_gc_pop_roots(ctx, 1); _ret_458; });
	mph_gc_push_root(ctx, (void**)&e2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\\nworld\" â \""));
	mph_native_print(ctx, e2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 3] module_to_prefix()\n"));
	MorphString* p1 = ({ MorphString* _arg_459 = mph_string_new(ctx, "token"); mph_gc_push_root(ctx, (void**)&_arg_459); MorphString* _ret_460 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_459); mph_gc_pop_roots(ctx, 1); _ret_460; });
	mph_gc_push_root(ctx, (void**)&p1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"token\" â \""));
	mph_native_print(ctx, p1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* p2 = ({ MorphString* _arg_461 = mph_string_new(ctx, "std/string"); mph_gc_push_root(ctx, (void**)&_arg_461); MorphString* _ret_462 = mph_stdlib_codegen_module_to_prefix(ctx, NULL, _arg_461); mph_gc_pop_roots(ctx, 1); _ret_462; });
	mph_gc_push_root(ctx, (void**)&p2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"std/string\" â \""));
	mph_native_print(ctx, p2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 4] is_valid_c_ident()\n"));
	mph_bool v1 = ({ MorphString* _arg_463 = mph_string_new(ctx, "foo"); mph_gc_push_root(ctx, (void**)&_arg_463); mph_bool _ret_464 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_463); mph_gc_pop_roots(ctx, 1); _ret_464; });
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
	mph_bool v2 = ({ MorphString* _arg_465 = mph_string_new(ctx, "_bar123"); mph_gc_push_root(ctx, (void**)&_arg_465); mph_bool _ret_466 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_465); mph_gc_pop_roots(ctx, 1); _ret_466; });
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
	mph_bool v3 = ({ MorphString* _arg_467 = mph_string_new(ctx, "123bad"); mph_gc_push_root(ctx, (void**)&_arg_467); mph_bool _ret_468 = mph_stdlib_codegen_is_valid_c_ident(ctx, NULL, _arg_467); mph_gc_pop_roots(ctx, 1); _ret_468; });
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

void mph_test_integer_literal(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 1] Integer Literal Compilation\n"));
	mph_ast_IntegerLiteral* lit1 = ({ MorphString* _arg_469 = mph_string_new(ctx, "42"); mph_gc_push_root(ctx, (void**)&_arg_469); mph_ast_IntegerLiteral* _ret_470 = mph_ast_MakeIntegerLiteral(ctx, NULL, 42, _arg_469, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_470; });
	mph_gc_push_root(ctx, (void**)&lit1);
	MorphString* result1 = ({ mph_ast_IntegerLiteral* _arg_471 = lit1; mph_gc_push_root(ctx, (void**)&_arg_471); MorphString* _ret_472 = mph_codegen_CompileIntegerLiteral(ctx, NULL, _arg_471); mph_gc_pop_roots(ctx, 1); _ret_472; });
	mph_gc_push_root(ctx, (void**)&result1);
	mph_native_print(ctx, mph_string_new(ctx, "  42 â \""));
	mph_native_print(ctx, result1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_ast_IntegerLiteral* lit2 = ({ MorphString* _arg_473 = mph_string_new(ctx, "0"); mph_gc_push_root(ctx, (void**)&_arg_473); mph_ast_IntegerLiteral* _ret_474 = mph_ast_MakeIntegerLiteral(ctx, NULL, 0, _arg_473, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_474; });
	mph_gc_push_root(ctx, (void**)&lit2);
	MorphString* result2 = ({ mph_ast_IntegerLiteral* _arg_475 = lit2; mph_gc_push_root(ctx, (void**)&_arg_475); MorphString* _ret_476 = mph_codegen_CompileIntegerLiteral(ctx, NULL, _arg_475); mph_gc_pop_roots(ctx, 1); _ret_476; });
	mph_gc_push_root(ctx, (void**)&result2);
	mph_native_print(ctx, mph_string_new(ctx, "  0 â \""));
	mph_native_print(ctx, result2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_ast_IntegerLiteral* lit3 = ({ MorphString* _arg_477 = mph_string_new(ctx, "-123"); mph_gc_push_root(ctx, (void**)&_arg_477); mph_ast_IntegerLiteral* _ret_478 = mph_ast_MakeIntegerLiteral(ctx, NULL, (-123), _arg_477, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_478; });
	mph_gc_push_root(ctx, (void**)&lit3);
	MorphString* result3 = ({ mph_ast_IntegerLiteral* _arg_479 = lit3; mph_gc_push_root(ctx, (void**)&_arg_479); MorphString* _ret_480 = mph_codegen_CompileIntegerLiteral(ctx, NULL, _arg_479); mph_gc_pop_roots(ctx, 1); _ret_480; });
	mph_gc_push_root(ctx, (void**)&result3);
	mph_native_print(ctx, mph_string_new(ctx, "  -123 â \""));
	mph_native_print(ctx, result3);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_ast_IntegerLiteral* lit4 = ({ MorphString* _arg_481 = mph_string_new(ctx, "9876"); mph_gc_push_root(ctx, (void**)&_arg_481); mph_ast_IntegerLiteral* _ret_482 = mph_ast_MakeIntegerLiteral(ctx, NULL, 9876, _arg_481, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_482; });
	mph_gc_push_root(ctx, (void**)&lit4);
	MorphString* result4 = ({ mph_ast_IntegerLiteral* _arg_483 = lit4; mph_gc_push_root(ctx, (void**)&_arg_483); MorphString* _ret_484 = mph_codegen_CompileIntegerLiteral(ctx, NULL, _arg_483); mph_gc_pop_roots(ctx, 1); _ret_484; });
	mph_gc_push_root(ctx, (void**)&result4);
	mph_native_print(ctx, mph_string_new(ctx, "  9876 â \""));
	mph_native_print(ctx, result4);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â Integer literal tests passed\n\n"));
	mph_gc_pop_roots(ctx, 8);
}

void mph_test_string_literal(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 2] String Literal Compilation\n"));
	mph_ast_StringLiteral* lit1 = ({ MorphString* _arg_485 = mph_string_new(ctx, "hello"); mph_gc_push_root(ctx, (void**)&_arg_485); mph_ast_StringLiteral* _ret_486 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_485, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_486; });
	mph_gc_push_root(ctx, (void**)&lit1);
	MorphString* result1 = ({ mph_ast_StringLiteral* _arg_487 = lit1; mph_gc_push_root(ctx, (void**)&_arg_487); MorphString* _ret_488 = mph_codegen_CompileStringLiteral(ctx, NULL, _arg_487); mph_gc_pop_roots(ctx, 1); _ret_488; });
	mph_gc_push_root(ctx, (void**)&result1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\" â \""));
	mph_native_print(ctx, result1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_ast_StringLiteral* lit2 = ({ MorphString* _arg_489 = mph_string_new(ctx, "hello\nworld"); mph_gc_push_root(ctx, (void**)&_arg_489); mph_ast_StringLiteral* _ret_490 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_489, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_490; });
	mph_gc_push_root(ctx, (void**)&lit2);
	MorphString* result2 = ({ mph_ast_StringLiteral* _arg_491 = lit2; mph_gc_push_root(ctx, (void**)&_arg_491); MorphString* _ret_492 = mph_codegen_CompileStringLiteral(ctx, NULL, _arg_491); mph_gc_pop_roots(ctx, 1); _ret_492; });
	mph_gc_push_root(ctx, (void**)&result2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\\nworld\" â \""));
	mph_native_print(ctx, result2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_ast_StringLiteral* lit3 = ({ MorphString* _arg_493 = mph_string_new(ctx, ""); mph_gc_push_root(ctx, (void**)&_arg_493); mph_ast_StringLiteral* _ret_494 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_493, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_494; });
	mph_gc_push_root(ctx, (void**)&lit3);
	MorphString* result3 = ({ mph_ast_StringLiteral* _arg_495 = lit3; mph_gc_push_root(ctx, (void**)&_arg_495); MorphString* _ret_496 = mph_codegen_CompileStringLiteral(ctx, NULL, _arg_495); mph_gc_pop_roots(ctx, 1); _ret_496; });
	mph_gc_push_root(ctx, (void**)&result3);
	mph_native_print(ctx, mph_string_new(ctx, "  \"\" â \""));
	mph_native_print(ctx, result3);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_ast_StringLiteral* lit4 = ({ MorphString* _arg_497 = mph_string_new(ctx, "say \"hi\""); mph_gc_push_root(ctx, (void**)&_arg_497); mph_ast_StringLiteral* _ret_498 = mph_ast_MakeStringLiteral(ctx, NULL, _arg_497, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_498; });
	mph_gc_push_root(ctx, (void**)&lit4);
	MorphString* result4 = ({ mph_ast_StringLiteral* _arg_499 = lit4; mph_gc_push_root(ctx, (void**)&_arg_499); MorphString* _ret_500 = mph_codegen_CompileStringLiteral(ctx, NULL, _arg_499); mph_gc_pop_roots(ctx, 1); _ret_500; });
	mph_gc_push_root(ctx, (void**)&result4);
	mph_native_print(ctx, mph_string_new(ctx, "  \"say \\\"hi\\\"\" â \""));
	mph_native_print(ctx, result4);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â String literal tests passed\n\n"));
	mph_gc_pop_roots(ctx, 8);
}

void mph_test_boolean_literal(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "[Test 3] Boolean Literal Compilation\n"));
	mph_ast_BooleanLiteral* lit_true = ({ MorphString* _arg_501 = mph_string_new(ctx, "benar"); mph_gc_push_root(ctx, (void**)&_arg_501); mph_ast_BooleanLiteral* _ret_502 = mph_ast_MakeBooleanLiteral(ctx, NULL, 1, _arg_501, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_502; });
	mph_gc_push_root(ctx, (void**)&lit_true);
	MorphString* result_true = ({ mph_ast_BooleanLiteral* _arg_503 = lit_true; mph_gc_push_root(ctx, (void**)&_arg_503); MorphString* _ret_504 = mph_codegen_CompileBooleanLiteral(ctx, NULL, _arg_503); mph_gc_pop_roots(ctx, 1); _ret_504; });
	mph_gc_push_root(ctx, (void**)&result_true);
	mph_native_print(ctx, mph_string_new(ctx, "  benar â \""));
	mph_native_print(ctx, result_true);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_ast_BooleanLiteral* lit_false = ({ MorphString* _arg_505 = mph_string_new(ctx, "salah"); mph_gc_push_root(ctx, (void**)&_arg_505); mph_ast_BooleanLiteral* _ret_506 = mph_ast_MakeBooleanLiteral(ctx, NULL, 0, _arg_505, 1, 1); mph_gc_pop_roots(ctx, 1); _ret_506; });
	mph_gc_push_root(ctx, (void**)&lit_false);
	MorphString* result_false = ({ mph_ast_BooleanLiteral* _arg_507 = lit_false; mph_gc_push_root(ctx, (void**)&_arg_507); MorphString* _ret_508 = mph_codegen_CompileBooleanLiteral(ctx, NULL, _arg_507); mph_gc_pop_roots(ctx, 1); _ret_508; });
	mph_gc_push_root(ctx, (void**)&result_false);
	mph_native_print(ctx, mph_string_new(ctx, "  salah â \""));
	mph_native_print(ctx, result_false);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "  â Boolean literal tests passed\n\n"));
	mph_gc_pop_roots(ctx, 4);
}

void mph_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â  N1 Codegen Phase 1: Literals Test  â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n\n"));
	mph_test_integer_literal(ctx, NULL);
	mph_test_string_literal(ctx, NULL);
	mph_test_boolean_literal(ctx, NULL);
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â  â All Literal Tests Passed        â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
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
	mph_main(ctx, NULL);
}
