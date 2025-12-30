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
#define MPH_TYPE_mph_Token 1
#define MPH_TYPE_mph_Lexer 2

// Struct Definitions (Env & Types)
typedef struct mph_Token mph_Token;
typedef struct mph_Lexer mph_Lexer;
struct mph_Token {
	mph_int token_type;
	MorphString* literal;
	mph_int line;
	mph_int column;
	mph_bool has_leading_space;
};

struct mph_Lexer {
	MorphString* input;
	mph_int position;
	mph_int read_position;
	mph_int ch;
	mph_int line;
	mph_int column;
	MorphArray* states;
	MorphArray* brace_counts;
};

MorphTypeInfo mph_ti_mph_Token = { "Token", sizeof(mph_Token), 1, (size_t[]){offsetof(mph_Token, literal)} };
MorphTypeInfo mph_ti_mph_Lexer = { "Lexer", sizeof(mph_Lexer), 3, (size_t[]){offsetof(mph_Lexer, input), offsetof(mph_Lexer, states), offsetof(mph_Lexer, brace_counts)} };

// Global Variables
mph_int mph_TOKEN_ILLEGAL;
mph_int mph_TOKEN_EOF;
mph_int mph_TOKEN_IDENT;
mph_int mph_TOKEN_INT;
mph_int mph_TOKEN_FLOAT;
mph_int mph_TOKEN_STRING;
mph_int mph_TOKEN_CHAR;
mph_int mph_TOKEN_ASSIGN;
mph_int mph_TOKEN_PLUS;
mph_int mph_TOKEN_MINUS;
mph_int mph_TOKEN_BANG;
mph_int mph_TOKEN_ASTERISK;
mph_int mph_TOKEN_SLASH;
mph_int mph_TOKEN_PERCENT;
mph_int mph_TOKEN_EQ;
mph_int mph_TOKEN_NOT_EQ;
mph_int mph_TOKEN_LT;
mph_int mph_TOKEN_GT;
mph_int mph_TOKEN_LE;
mph_int mph_TOKEN_GE;
mph_int mph_TOKEN_AND;
mph_int mph_TOKEN_OR;
mph_int mph_TOKEN_BIT_AND;
mph_int mph_TOKEN_BIT_OR;
mph_int mph_TOKEN_BIT_XOR;
mph_int mph_TOKEN_BIT_NOT;
mph_int mph_TOKEN_LSHIFT;
mph_int mph_TOKEN_RSHIFT;
mph_int mph_TOKEN_COMMA;
mph_int mph_TOKEN_SEMICOLON;
mph_int mph_TOKEN_COLON;
mph_int mph_TOKEN_DOT;
mph_int mph_TOKEN_ARROW;
mph_int mph_TOKEN_LPAREN;
mph_int mph_TOKEN_RPAREN;
mph_int mph_TOKEN_LBRACE;
mph_int mph_TOKEN_RBRACE;
mph_int mph_TOKEN_LBRACKET;
mph_int mph_TOKEN_RBRACKET;
mph_int mph_TOKEN_FUNGSI;
mph_int mph_TOKEN_NATIVE;
mph_int mph_TOKEN_JIKA;
mph_int mph_TOKEN_ATAU_JIKA;
mph_int mph_TOKEN_LAINNYA;
mph_int mph_TOKEN_KEMBALIKAN;
mph_int mph_TOKEN_BENAR;
mph_int mph_TOKEN_SALAH;
mph_int mph_TOKEN_KOSONG;
mph_int mph_TOKEN_AKHIR;
mph_int mph_TOKEN_SELAMA;
mph_int mph_TOKEN_DAN;
mph_int mph_TOKEN_ATAU;
mph_int mph_TOKEN_AMBIL;
mph_int mph_TOKEN_DARI;
mph_int mph_TOKEN_BERHENTI;
mph_int mph_TOKEN_LANJUT;
mph_int mph_TOKEN_STRUKTUR;
mph_int mph_TOKEN_INTERFACE;
mph_int mph_TOKEN_VAR;
mph_int mph_TOKEN_TETAPAN;
mph_int mph_TOKEN_MAP;
mph_int mph_TOKEN_PILIH;
mph_int mph_TOKEN_KASUS;
mph_int mph_STATE_CODE;
mph_int mph_STATE_STRING;

// Function Prototypes
mph_Token* mph_new_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal, mph_int line, mph_int column);
mph_int mph_lookup_ident(MorphContext* ctx, void* _env_void, MorphString* ident);
mph_Lexer* mph_NewLexer(MorphContext* ctx, void* _env_void, MorphString* input);
mph_int mph_lexer_current_state(MorphContext* ctx, void* _env_void, mph_Lexer* l);
void mph_lexer_read_char(MorphContext* ctx, void* _env_void, mph_Lexer* l);
mph_int mph_lexer_peek_char(MorphContext* ctx, void* _env_void, mph_Lexer* l);
void mph_lexer_skip_whitespace(MorphContext* ctx, void* _env_void, mph_Lexer* l);
MorphString* mph_lexer_read_identifier(MorphContext* ctx, void* _env_void, mph_Lexer* l);
mph_Token* mph_lexer_read_number_token(MorphContext* ctx, void* _env_void, mph_Lexer* l, mph_int line, mph_int column);
MorphString* mph_lexer_read_string(MorphContext* ctx, void* _env_void, mph_Lexer* l);
MorphString* mph_lexer_read_char_literal(MorphContext* ctx, void* _env_void, mph_Lexer* l);
mph_Token* mph_lexer_read_char_token(MorphContext* ctx, void* _env_void, mph_Lexer* l, mph_int line, mph_int column);
mph_bool mph_is_letter(MorphContext* ctx, void* _env_void, mph_int ch);
mph_bool mph_is_digit(MorphContext* ctx, void* _env_void, mph_int ch);
mph_bool mph_is_whitespace(MorphContext* ctx, void* _env_void, mph_int ch);
mph_int mph_char_at(MorphContext* ctx, void* _env_void, MorphString* s, mph_int pos);
MorphString* mph_char_to_string(MorphContext* ctx, void* _env_void, mph_int ch);
mph_int mph_char_to_ascii(MorphContext* ctx, void* _env_void, MorphString* char_str);
mph_int mph_CharToAscii(MorphContext* ctx, void* _env_void, MorphString* char_str);
mph_Token* mph_LexerNextToken(MorphContext* ctx, void* _env_void, mph_Lexer* l);

// Function Definitions
mph_Token* mph_new_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_Token* _t = (mph_Token*)mph_alloc(ctx, sizeof(mph_Token), &mph_ti_mph_Token); mph_gc_push_root(ctx, (void**)&_t); _t->has_leading_space = 0; _t->token_type = token_type; _t->literal = literal; _t->line = line; _t->column = column; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_lookup_ident(MorphContext* ctx, void* _env_void, MorphString* ident) {
	mph_gc_push_root(ctx, (void**)&ident);
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "fungsi"))) {
{
	return mph_TOKEN_FUNGSI;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "native"))) {
{
	return mph_TOKEN_NATIVE;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "jika"))) {
{
	return mph_TOKEN_JIKA;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "atau_jika"))) {
{
	return mph_TOKEN_ATAU_JIKA;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "lainnya"))) {
{
	return mph_TOKEN_LAINNYA;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "kembalikan"))) {
{
	return mph_TOKEN_KEMBALIKAN;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "benar"))) {
{
	return mph_TOKEN_BENAR;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "salah"))) {
{
	return mph_TOKEN_SALAH;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "kosong"))) {
{
	return mph_TOKEN_KOSONG;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "akhir"))) {
{
	return mph_TOKEN_AKHIR;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "selama"))) {
{
	return mph_TOKEN_SELAMA;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "dan"))) {
{
	return mph_TOKEN_DAN;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "atau"))) {
{
	return mph_TOKEN_ATAU;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "ambil"))) {
{
	return mph_TOKEN_AMBIL;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "dari"))) {
{
	return mph_TOKEN_DARI;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "berhenti"))) {
{
	return mph_TOKEN_BERHENTI;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "lanjut"))) {
{
	return mph_TOKEN_LANJUT;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "struktur"))) {
{
	return mph_TOKEN_STRUKTUR;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "interface"))) {
{
	return mph_TOKEN_INTERFACE;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "var"))) {
{
	return mph_TOKEN_VAR;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "tetapan"))) {
{
	return mph_TOKEN_TETAPAN;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "map"))) {
{
	return mph_TOKEN_MAP;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "pilih"))) {
{
	return mph_TOKEN_PILIH;
}
	} else {
{
	if (mph_string_eq(ctx, ident, mph_string_new(ctx, "kasus"))) {
{
	return mph_TOKEN_KASUS;
}
	} else {
{
	return mph_TOKEN_IDENT;
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
}
	}
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_Lexer* mph_NewLexer(MorphContext* ctx, void* _env_void, MorphString* input) {
	mph_gc_push_root(ctx, (void**)&input);
	mph_Lexer* l = ({ mph_Lexer* _t = (mph_Lexer*)mph_alloc(ctx, sizeof(mph_Lexer), &mph_ti_mph_Lexer); mph_gc_push_root(ctx, (void**)&_t); _t->read_position = 0; _t->ch = 0; _t->line = 1; _t->column = 0; _t->states = ({ MorphArray* _a = mph_array_new(ctx, 1, sizeof(mph_int), 0); mph_gc_push_root(ctx, (void**)&_a); ((mph_int*)_a->data)[0] = mph_STATE_CODE; mph_gc_pop_roots(ctx, 1); _a; }); _t->brace_counts = ({ MorphArray* _a = mph_array_new(ctx, 1, sizeof(mph_int), 0); mph_gc_push_root(ctx, (void**)&_a); ((mph_int*)_a->data)[0] = 0; mph_gc_pop_roots(ctx, 1); _a; }); _t->input = input; _t->position = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_Lexer* _arg_1 = l; mph_gc_push_root(ctx, (void**)&_arg_1); mph_lexer_read_char(ctx, NULL, _arg_1); mph_gc_pop_roots(ctx, 1); });
	return l;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_lexer_current_state(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	if ((({ MorphArray* _len_arg_4 = ({ mph_Lexer* _obj_2 = l; mph_gc_push_root(ctx, (void**)&_obj_2); MorphArray* _ret_3 = _obj_2->states; mph_gc_pop_roots(ctx, 1); _ret_3; }); mph_gc_push_root(ctx, (void**)&_len_arg_4); mph_int _ret_5 = ((MorphArray*)_len_arg_4)->length; mph_gc_pop_roots(ctx, 1); _ret_5; }) == 0)) {
{
	return mph_STATE_CODE;
}
	}
	return ({ MorphArray* _lhs_12 = ({ mph_Lexer* _obj_6 = l; mph_gc_push_root(ctx, (void**)&_obj_6); MorphArray* _ret_7 = _obj_6->states; mph_gc_pop_roots(ctx, 1); _ret_7; }); mph_gc_push_root(ctx, (void**)&_lhs_12); mph_int _ret_13 = (*(mph_int*)mph_array_at(ctx, _lhs_12, (({ MorphArray* _len_arg_10 = ({ mph_Lexer* _obj_8 = l; mph_gc_push_root(ctx, (void**)&_obj_8); MorphArray* _ret_9 = _obj_8->states; mph_gc_pop_roots(ctx, 1); _ret_9; }); mph_gc_push_root(ctx, (void**)&_len_arg_10); mph_int _ret_11 = ((MorphArray*)_len_arg_10)->length; mph_gc_pop_roots(ctx, 1); _ret_11; }) - 1))); mph_gc_pop_roots(ctx, 1); _ret_13; });
	mph_gc_pop_roots(ctx, 1);
}

void mph_lexer_read_char(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	if ((({ mph_Lexer* _obj_14 = l; mph_gc_push_root(ctx, (void**)&_obj_14); mph_int _ret_15 = _obj_14->read_position; mph_gc_pop_roots(ctx, 1); _ret_15; }) >= ({ MorphString* _len_arg_18 = ({ mph_Lexer* _obj_16 = l; mph_gc_push_root(ctx, (void**)&_obj_16); MorphString* _ret_17 = _obj_16->input; mph_gc_pop_roots(ctx, 1); _ret_17; }); mph_gc_push_root(ctx, (void**)&_len_arg_18); mph_int _ret_19 = ((MorphString*)_len_arg_18)->length; mph_gc_pop_roots(ctx, 1); _ret_19; }))) {
{
	({ mph_Lexer* _obj_20 = l; mph_gc_push_root(ctx, (void**)&_obj_20); _obj_20->ch = 0; mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ mph_Lexer* _obj_27 = l; mph_gc_push_root(ctx, (void**)&_obj_27); _obj_27->ch = ({ MorphString* _arg_23 = ({ mph_Lexer* _obj_21 = l; mph_gc_push_root(ctx, (void**)&_obj_21); MorphString* _ret_22 = _obj_21->input; mph_gc_pop_roots(ctx, 1); _ret_22; }); mph_gc_push_root(ctx, (void**)&_arg_23); mph_int _ret_26 = mph_char_at(ctx, NULL, _arg_23, ({ mph_Lexer* _obj_24 = l; mph_gc_push_root(ctx, (void**)&_obj_24); mph_int _ret_25 = _obj_24->read_position; mph_gc_pop_roots(ctx, 1); _ret_25; })); mph_gc_pop_roots(ctx, 1); _ret_26; }); mph_gc_pop_roots(ctx, 1); });
}
	}
	({ mph_Lexer* _obj_30 = l; mph_gc_push_root(ctx, (void**)&_obj_30); _obj_30->position = ({ mph_Lexer* _obj_28 = l; mph_gc_push_root(ctx, (void**)&_obj_28); mph_int _ret_29 = _obj_28->read_position; mph_gc_pop_roots(ctx, 1); _ret_29; }); mph_gc_pop_roots(ctx, 1); });
	({ mph_Lexer* _obj_33 = l; mph_gc_push_root(ctx, (void**)&_obj_33); _obj_33->read_position = (({ mph_Lexer* _obj_31 = l; mph_gc_push_root(ctx, (void**)&_obj_31); mph_int _ret_32 = _obj_31->read_position; mph_gc_pop_roots(ctx, 1); _ret_32; }) + 1); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_Lexer* _obj_34 = l; mph_gc_push_root(ctx, (void**)&_obj_34); mph_int _ret_35 = _obj_34->ch; mph_gc_pop_roots(ctx, 1); _ret_35; }) == 10)) {
{
	({ mph_Lexer* _obj_38 = l; mph_gc_push_root(ctx, (void**)&_obj_38); _obj_38->line = (({ mph_Lexer* _obj_36 = l; mph_gc_push_root(ctx, (void**)&_obj_36); mph_int _ret_37 = _obj_36->line; mph_gc_pop_roots(ctx, 1); _ret_37; }) + 1); mph_gc_pop_roots(ctx, 1); });
	({ mph_Lexer* _obj_39 = l; mph_gc_push_root(ctx, (void**)&_obj_39); _obj_39->column = 0; mph_gc_pop_roots(ctx, 1); });
}
	} else {
{
	({ mph_Lexer* _obj_42 = l; mph_gc_push_root(ctx, (void**)&_obj_42); _obj_42->column = (({ mph_Lexer* _obj_40 = l; mph_gc_push_root(ctx, (void**)&_obj_40); mph_int _ret_41 = _obj_40->column; mph_gc_pop_roots(ctx, 1); _ret_41; }) + 1); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_lexer_peek_char(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	if ((({ mph_Lexer* _obj_43 = l; mph_gc_push_root(ctx, (void**)&_obj_43); mph_int _ret_44 = _obj_43->read_position; mph_gc_pop_roots(ctx, 1); _ret_44; }) >= ({ MorphString* _len_arg_47 = ({ mph_Lexer* _obj_45 = l; mph_gc_push_root(ctx, (void**)&_obj_45); MorphString* _ret_46 = _obj_45->input; mph_gc_pop_roots(ctx, 1); _ret_46; }); mph_gc_push_root(ctx, (void**)&_len_arg_47); mph_int _ret_48 = ((MorphString*)_len_arg_47)->length; mph_gc_pop_roots(ctx, 1); _ret_48; }))) {
{
	return 0;
}
	} else {
{
	return ({ MorphString* _arg_51 = ({ mph_Lexer* _obj_49 = l; mph_gc_push_root(ctx, (void**)&_obj_49); MorphString* _ret_50 = _obj_49->input; mph_gc_pop_roots(ctx, 1); _ret_50; }); mph_gc_push_root(ctx, (void**)&_arg_51); mph_int _ret_54 = mph_char_at(ctx, NULL, _arg_51, ({ mph_Lexer* _obj_52 = l; mph_gc_push_root(ctx, (void**)&_obj_52); mph_int _ret_53 = _obj_52->read_position; mph_gc_pop_roots(ctx, 1); _ret_53; })); mph_gc_pop_roots(ctx, 1); _ret_54; });
}
	}
	mph_gc_pop_roots(ctx, 1);
}

void mph_lexer_skip_whitespace(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	while (((((({ mph_Lexer* _obj_55 = l; mph_gc_push_root(ctx, (void**)&_obj_55); mph_int _ret_56 = _obj_55->ch; mph_gc_pop_roots(ctx, 1); _ret_56; }) == 32) || (({ mph_Lexer* _obj_57 = l; mph_gc_push_root(ctx, (void**)&_obj_57); mph_int _ret_58 = _obj_57->ch; mph_gc_pop_roots(ctx, 1); _ret_58; }) == 9)) || (({ mph_Lexer* _obj_59 = l; mph_gc_push_root(ctx, (void**)&_obj_59); mph_int _ret_60 = _obj_59->ch; mph_gc_pop_roots(ctx, 1); _ret_60; }) == 10)) || (({ mph_Lexer* _obj_61 = l; mph_gc_push_root(ctx, (void**)&_obj_61); mph_int _ret_62 = _obj_61->ch; mph_gc_pop_roots(ctx, 1); _ret_62; }) == 13))) {
{
	({ mph_Lexer* _arg_63 = l; mph_gc_push_root(ctx, (void**)&_arg_63); mph_lexer_read_char(ctx, NULL, _arg_63); mph_gc_pop_roots(ctx, 1); });
}
	}
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_read_identifier(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = ({ mph_Lexer* _obj_64 = l; mph_gc_push_root(ctx, (void**)&_obj_64); mph_int _ret_65 = _obj_64->position; mph_gc_pop_roots(ctx, 1); _ret_65; });
	while ((mph_is_letter(ctx, NULL, ({ mph_Lexer* _obj_66 = l; mph_gc_push_root(ctx, (void**)&_obj_66); mph_int _ret_67 = _obj_66->ch; mph_gc_pop_roots(ctx, 1); _ret_67; })) || mph_is_digit(ctx, NULL, ({ mph_Lexer* _obj_68 = l; mph_gc_push_root(ctx, (void**)&_obj_68); mph_int _ret_69 = _obj_68->ch; mph_gc_pop_roots(ctx, 1); _ret_69; })))) {
{
	({ mph_Lexer* _arg_70 = l; mph_gc_push_root(ctx, (void**)&_arg_70); mph_lexer_read_char(ctx, NULL, _arg_70); mph_gc_pop_roots(ctx, 1); });
}
	}
	return mph_string_substring(ctx, ({ mph_Lexer* _obj_71 = l; mph_gc_push_root(ctx, (void**)&_obj_71); MorphString* _ret_72 = _obj_71->input; mph_gc_pop_roots(ctx, 1); _ret_72; }), position, ({ mph_Lexer* _obj_73 = l; mph_gc_push_root(ctx, (void**)&_obj_73); mph_int _ret_74 = _obj_73->position; mph_gc_pop_roots(ctx, 1); _ret_74; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_Token* mph_lexer_read_number_token(MorphContext* ctx, void* _env_void, mph_Lexer* l, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = ({ mph_Lexer* _obj_75 = l; mph_gc_push_root(ctx, (void**)&_obj_75); mph_int _ret_76 = _obj_75->position; mph_gc_pop_roots(ctx, 1); _ret_76; });
	mph_int token_type = mph_TOKEN_INT;
	while (mph_is_digit(ctx, NULL, ({ mph_Lexer* _obj_77 = l; mph_gc_push_root(ctx, (void**)&_obj_77); mph_int _ret_78 = _obj_77->ch; mph_gc_pop_roots(ctx, 1); _ret_78; }))) {
{
	({ mph_Lexer* _arg_79 = l; mph_gc_push_root(ctx, (void**)&_arg_79); mph_lexer_read_char(ctx, NULL, _arg_79); mph_gc_pop_roots(ctx, 1); });
}
	}
	if (((({ mph_Lexer* _obj_80 = l; mph_gc_push_root(ctx, (void**)&_obj_80); mph_int _ret_81 = _obj_80->ch; mph_gc_pop_roots(ctx, 1); _ret_81; }) == 46) && mph_is_digit(ctx, NULL, ({ mph_Lexer* _arg_82 = l; mph_gc_push_root(ctx, (void**)&_arg_82); mph_int _ret_83 = mph_lexer_peek_char(ctx, NULL, _arg_82); mph_gc_pop_roots(ctx, 1); _ret_83; })))) {
{
	token_type = mph_TOKEN_FLOAT;
	({ mph_Lexer* _arg_84 = l; mph_gc_push_root(ctx, (void**)&_arg_84); mph_lexer_read_char(ctx, NULL, _arg_84); mph_gc_pop_roots(ctx, 1); });
	while (mph_is_digit(ctx, NULL, ({ mph_Lexer* _obj_85 = l; mph_gc_push_root(ctx, (void**)&_obj_85); mph_int _ret_86 = _obj_85->ch; mph_gc_pop_roots(ctx, 1); _ret_86; }))) {
{
	({ mph_Lexer* _arg_87 = l; mph_gc_push_root(ctx, (void**)&_arg_87); mph_lexer_read_char(ctx, NULL, _arg_87); mph_gc_pop_roots(ctx, 1); });
}
	}
}
	}
	MorphString* literal = mph_string_substring(ctx, ({ mph_Lexer* _obj_88 = l; mph_gc_push_root(ctx, (void**)&_obj_88); MorphString* _ret_89 = _obj_88->input; mph_gc_pop_roots(ctx, 1); _ret_89; }), position, ({ mph_Lexer* _obj_90 = l; mph_gc_push_root(ctx, (void**)&_obj_90); mph_int _ret_91 = _obj_90->position; mph_gc_pop_roots(ctx, 1); _ret_91; }));
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ MorphString* _arg_92 = literal; mph_gc_push_root(ctx, (void**)&_arg_92); mph_Token* _ret_93 = mph_new_token(ctx, NULL, token_type, _arg_92, line, column); mph_gc_pop_roots(ctx, 1); _ret_93; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_read_string(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = (({ mph_Lexer* _obj_94 = l; mph_gc_push_root(ctx, (void**)&_obj_94); mph_int _ret_95 = _obj_94->position; mph_gc_pop_roots(ctx, 1); _ret_95; }) + 1);
	while (1) {
{
	({ mph_Lexer* _arg_96 = l; mph_gc_push_root(ctx, (void**)&_arg_96); mph_lexer_read_char(ctx, NULL, _arg_96); mph_gc_pop_roots(ctx, 1); });
	if (((({ mph_Lexer* _obj_97 = l; mph_gc_push_root(ctx, (void**)&_obj_97); mph_int _ret_98 = _obj_97->ch; mph_gc_pop_roots(ctx, 1); _ret_98; }) == 34) || (({ mph_Lexer* _obj_99 = l; mph_gc_push_root(ctx, (void**)&_obj_99); mph_int _ret_100 = _obj_99->ch; mph_gc_pop_roots(ctx, 1); _ret_100; }) == 0))) {
{
}
	}
}
	}
	return mph_string_substring(ctx, ({ mph_Lexer* _obj_101 = l; mph_gc_push_root(ctx, (void**)&_obj_101); MorphString* _ret_102 = _obj_101->input; mph_gc_pop_roots(ctx, 1); _ret_102; }), position, ({ mph_Lexer* _obj_103 = l; mph_gc_push_root(ctx, (void**)&_obj_103); mph_int _ret_104 = _obj_103->position; mph_gc_pop_roots(ctx, 1); _ret_104; }));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_lexer_read_char_literal(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	mph_int position = (({ mph_Lexer* _obj_105 = l; mph_gc_push_root(ctx, (void**)&_obj_105); mph_int _ret_106 = _obj_105->position; mph_gc_pop_roots(ctx, 1); _ret_106; }) + 1);
	({ mph_Lexer* _arg_107 = l; mph_gc_push_root(ctx, (void**)&_arg_107); mph_lexer_read_char(ctx, NULL, _arg_107); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_Lexer* _obj_108 = l; mph_gc_push_root(ctx, (void**)&_obj_108); mph_int _ret_109 = _obj_108->ch; mph_gc_pop_roots(ctx, 1); _ret_109; }) == 92)) {
{
	({ mph_Lexer* _arg_110 = l; mph_gc_push_root(ctx, (void**)&_arg_110); mph_lexer_read_char(ctx, NULL, _arg_110); mph_gc_pop_roots(ctx, 1); });
}
	}
	MorphString* literal = mph_string_substring(ctx, ({ mph_Lexer* _obj_111 = l; mph_gc_push_root(ctx, (void**)&_obj_111); MorphString* _ret_112 = _obj_111->input; mph_gc_pop_roots(ctx, 1); _ret_112; }), position, ({ mph_Lexer* _obj_113 = l; mph_gc_push_root(ctx, (void**)&_obj_113); mph_int _ret_114 = _obj_113->position; mph_gc_pop_roots(ctx, 1); _ret_114; }));
	mph_gc_push_root(ctx, (void**)&literal);
	({ mph_Lexer* _arg_115 = l; mph_gc_push_root(ctx, (void**)&_arg_115); mph_lexer_read_char(ctx, NULL, _arg_115); mph_gc_pop_roots(ctx, 1); });
	return literal;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_Token* mph_lexer_read_char_token(MorphContext* ctx, void* _env_void, mph_Lexer* l, mph_int line, mph_int column) {
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_Lexer* _arg_116 = l; mph_gc_push_root(ctx, (void**)&_arg_116); mph_lexer_read_char(ctx, NULL, _arg_116); mph_gc_pop_roots(ctx, 1); });
	MorphString* literal = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&literal);
	if ((({ mph_Lexer* _obj_117 = l; mph_gc_push_root(ctx, (void**)&_obj_117); mph_int _ret_118 = _obj_117->ch; mph_gc_pop_roots(ctx, 1); _ret_118; }) == 92)) {
{
	({ mph_Lexer* _arg_119 = l; mph_gc_push_root(ctx, (void**)&_arg_119); mph_lexer_read_char(ctx, NULL, _arg_119); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_Lexer* _obj_120 = l; mph_gc_push_root(ctx, (void**)&_obj_120); mph_int _ret_121 = _obj_120->ch; mph_gc_pop_roots(ctx, 1); _ret_121; }) == 110)) {
{
	literal = mph_string_new(ctx, "\n");
}
	} else {
{
	if ((({ mph_Lexer* _obj_122 = l; mph_gc_push_root(ctx, (void**)&_obj_122); mph_int _ret_123 = _obj_122->ch; mph_gc_pop_roots(ctx, 1); _ret_123; }) == 116)) {
{
	literal = mph_string_new(ctx, "\t");
}
	} else {
{
	if ((({ mph_Lexer* _obj_124 = l; mph_gc_push_root(ctx, (void**)&_obj_124); mph_int _ret_125 = _obj_124->ch; mph_gc_pop_roots(ctx, 1); _ret_125; }) == 114)) {
{
	literal = mph_string_new(ctx, "\r");
}
	} else {
{
	if ((({ mph_Lexer* _obj_126 = l; mph_gc_push_root(ctx, (void**)&_obj_126); mph_int _ret_127 = _obj_126->ch; mph_gc_pop_roots(ctx, 1); _ret_127; }) == 39)) {
{
	literal = mph_string_new(ctx, "'");
}
	} else {
{
	if ((({ mph_Lexer* _obj_128 = l; mph_gc_push_root(ctx, (void**)&_obj_128); mph_int _ret_129 = _obj_128->ch; mph_gc_pop_roots(ctx, 1); _ret_129; }) == 92)) {
{
	literal = mph_string_new(ctx, "\\");
}
	} else {
{
	literal = mph_string_substring(ctx, ({ mph_Lexer* _obj_130 = l; mph_gc_push_root(ctx, (void**)&_obj_130); MorphString* _ret_131 = _obj_130->input; mph_gc_pop_roots(ctx, 1); _ret_131; }), ({ mph_Lexer* _obj_132 = l; mph_gc_push_root(ctx, (void**)&_obj_132); mph_int _ret_133 = _obj_132->position; mph_gc_pop_roots(ctx, 1); _ret_133; }), (({ mph_Lexer* _obj_134 = l; mph_gc_push_root(ctx, (void**)&_obj_134); mph_int _ret_135 = _obj_134->position; mph_gc_pop_roots(ctx, 1); _ret_135; }) + 1));
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
	literal = mph_string_substring(ctx, ({ mph_Lexer* _obj_136 = l; mph_gc_push_root(ctx, (void**)&_obj_136); MorphString* _ret_137 = _obj_136->input; mph_gc_pop_roots(ctx, 1); _ret_137; }), ({ mph_Lexer* _obj_138 = l; mph_gc_push_root(ctx, (void**)&_obj_138); mph_int _ret_139 = _obj_138->position; mph_gc_pop_roots(ctx, 1); _ret_139; }), (({ mph_Lexer* _obj_140 = l; mph_gc_push_root(ctx, (void**)&_obj_140); mph_int _ret_141 = _obj_140->position; mph_gc_pop_roots(ctx, 1); _ret_141; }) + 1));
}
	}
	({ mph_Lexer* _arg_142 = l; mph_gc_push_root(ctx, (void**)&_arg_142); mph_lexer_read_char(ctx, NULL, _arg_142); mph_gc_pop_roots(ctx, 1); });
	if ((({ mph_Lexer* _obj_143 = l; mph_gc_push_root(ctx, (void**)&_obj_143); mph_int _ret_144 = _obj_143->ch; mph_gc_pop_roots(ctx, 1); _ret_144; }) != 39)) {
{
	return ({ MorphString* _arg_145 = mph_string_new(ctx, "Unterminated char literal"); mph_gc_push_root(ctx, (void**)&_arg_145); mph_Token* _ret_146 = mph_new_token(ctx, NULL, mph_TOKEN_ILLEGAL, _arg_145, line, column); mph_gc_pop_roots(ctx, 1); _ret_146; });
}
	}
	({ mph_Lexer* _arg_147 = l; mph_gc_push_root(ctx, (void**)&_arg_147); mph_lexer_read_char(ctx, NULL, _arg_147); mph_gc_pop_roots(ctx, 1); });
	return ({ MorphString* _arg_148 = literal; mph_gc_push_root(ctx, (void**)&_arg_148); mph_Token* _ret_149 = mph_new_token(ctx, NULL, mph_TOKEN_CHAR, _arg_148, line, column); mph_gc_pop_roots(ctx, 1); _ret_149; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_is_letter(MorphContext* ctx, void* _env_void, mph_int ch) {
	return ((((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <= 122))) || (ch == 95));
}

mph_bool mph_is_digit(MorphContext* ctx, void* _env_void, mph_int ch) {
	return ((ch >= 48) && (ch <= 57));
}

mph_bool mph_is_whitespace(MorphContext* ctx, void* _env_void, mph_int ch) {
	return ((((ch == 32) || (ch == 9)) || (ch == 10)) || (ch == 13));
}

mph_int mph_char_at(MorphContext* ctx, void* _env_void, MorphString* s, mph_int pos) {
	mph_gc_push_root(ctx, (void**)&s);
	if ((pos >= ({ MorphString* _len_arg_150 = s; mph_gc_push_root(ctx, (void**)&_len_arg_150); mph_int _ret_151 = ((MorphString*)_len_arg_150)->length; mph_gc_pop_roots(ctx, 1); _ret_151; }))) {
{
	return 0;
}
	}
	MorphString* c = mph_string_substring(ctx, s, pos, (pos + 1));
	mph_gc_push_root(ctx, (void**)&c);
	return ({ MorphString* _arg_152 = c; mph_gc_push_root(ctx, (void**)&_arg_152); mph_int _ret_153 = mph_char_to_ascii(ctx, NULL, _arg_152); mph_gc_pop_roots(ctx, 1); _ret_153; });
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_char_to_string(MorphContext* ctx, void* _env_void, mph_int ch) {
	return mph_string_new(ctx, "");
}

mph_int mph_char_to_ascii(MorphContext* ctx, void* _env_void, MorphString* char_str) {
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

mph_int mph_CharToAscii(MorphContext* ctx, void* _env_void, MorphString* char_str) {
	mph_gc_push_root(ctx, (void**)&char_str);
	return ({ MorphString* _arg_154 = char_str; mph_gc_push_root(ctx, (void**)&_arg_154); mph_int _ret_155 = mph_char_to_ascii(ctx, NULL, _arg_154); mph_gc_pop_roots(ctx, 1); _ret_155; });
	mph_gc_pop_roots(ctx, 1);
}

mph_Token* mph_LexerNextToken(MorphContext* ctx, void* _env_void, mph_Lexer* l) {
	mph_gc_push_root(ctx, (void**)&l);
	({ mph_Lexer* _arg_156 = l; mph_gc_push_root(ctx, (void**)&_arg_156); mph_lexer_skip_whitespace(ctx, NULL, _arg_156); mph_gc_pop_roots(ctx, 1); });
	mph_Token* tok = ({ MorphString* _arg_157 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_157); mph_Token* _ret_162 = mph_new_token(ctx, NULL, mph_TOKEN_ILLEGAL, _arg_157, ({ mph_Lexer* _obj_158 = l; mph_gc_push_root(ctx, (void**)&_obj_158); mph_int _ret_159 = _obj_158->line; mph_gc_pop_roots(ctx, 1); _ret_159; }), ({ mph_Lexer* _obj_160 = l; mph_gc_push_root(ctx, (void**)&_obj_160); mph_int _ret_161 = _obj_160->column; mph_gc_pop_roots(ctx, 1); _ret_161; })); mph_gc_pop_roots(ctx, 1); _ret_162; });
	mph_gc_push_root(ctx, (void**)&tok);
	if ((({ mph_Lexer* _obj_163 = l; mph_gc_push_root(ctx, (void**)&_obj_163); mph_int _ret_164 = _obj_163->ch; mph_gc_pop_roots(ctx, 1); _ret_164; }) == 61)) {
{
	if ((({ mph_Lexer* _arg_165 = l; mph_gc_push_root(ctx, (void**)&_arg_165); mph_int _ret_166 = mph_lexer_peek_char(ctx, NULL, _arg_165); mph_gc_pop_roots(ctx, 1); _ret_166; }) == 61)) {
{
	mph_int ch = ({ mph_Lexer* _obj_167 = l; mph_gc_push_root(ctx, (void**)&_obj_167); mph_int _ret_168 = _obj_167->ch; mph_gc_pop_roots(ctx, 1); _ret_168; });
	({ mph_Lexer* _arg_169 = l; mph_gc_push_root(ctx, (void**)&_arg_169); mph_lexer_read_char(ctx, NULL, _arg_169); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_170 = mph_string_new(ctx, "=="); mph_gc_push_root(ctx, (void**)&_arg_170); mph_Token* _ret_175 = mph_new_token(ctx, NULL, mph_TOKEN_EQ, _arg_170, ({ mph_Lexer* _obj_171 = l; mph_gc_push_root(ctx, (void**)&_obj_171); mph_int _ret_172 = _obj_171->line; mph_gc_pop_roots(ctx, 1); _ret_172; }), ({ mph_Lexer* _obj_173 = l; mph_gc_push_root(ctx, (void**)&_obj_173); mph_int _ret_174 = _obj_173->column; mph_gc_pop_roots(ctx, 1); _ret_174; })); mph_gc_pop_roots(ctx, 1); _ret_175; });
}
	} else {
{
	tok = ({ MorphString* _arg_176 = mph_string_new(ctx, "="); mph_gc_push_root(ctx, (void**)&_arg_176); mph_Token* _ret_181 = mph_new_token(ctx, NULL, mph_TOKEN_ASSIGN, _arg_176, ({ mph_Lexer* _obj_177 = l; mph_gc_push_root(ctx, (void**)&_obj_177); mph_int _ret_178 = _obj_177->line; mph_gc_pop_roots(ctx, 1); _ret_178; }), ({ mph_Lexer* _obj_179 = l; mph_gc_push_root(ctx, (void**)&_obj_179); mph_int _ret_180 = _obj_179->column; mph_gc_pop_roots(ctx, 1); _ret_180; })); mph_gc_pop_roots(ctx, 1); _ret_181; });
}
	}
}
	} else if ((({ mph_Lexer* _obj_182 = l; mph_gc_push_root(ctx, (void**)&_obj_182); mph_int _ret_183 = _obj_182->ch; mph_gc_pop_roots(ctx, 1); _ret_183; }) == 43)) {
{
	tok = ({ MorphString* _arg_184 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_184); mph_Token* _ret_189 = mph_new_token(ctx, NULL, mph_TOKEN_PLUS, _arg_184, ({ mph_Lexer* _obj_185 = l; mph_gc_push_root(ctx, (void**)&_obj_185); mph_int _ret_186 = _obj_185->line; mph_gc_pop_roots(ctx, 1); _ret_186; }), ({ mph_Lexer* _obj_187 = l; mph_gc_push_root(ctx, (void**)&_obj_187); mph_int _ret_188 = _obj_187->column; mph_gc_pop_roots(ctx, 1); _ret_188; })); mph_gc_pop_roots(ctx, 1); _ret_189; });
}
	} else if ((({ mph_Lexer* _obj_190 = l; mph_gc_push_root(ctx, (void**)&_obj_190); mph_int _ret_191 = _obj_190->ch; mph_gc_pop_roots(ctx, 1); _ret_191; }) == 45)) {
{
	if ((({ mph_Lexer* _arg_192 = l; mph_gc_push_root(ctx, (void**)&_arg_192); mph_int _ret_193 = mph_lexer_peek_char(ctx, NULL, _arg_192); mph_gc_pop_roots(ctx, 1); _ret_193; }) == 62)) {
{
	({ mph_Lexer* _arg_194 = l; mph_gc_push_root(ctx, (void**)&_arg_194); mph_lexer_read_char(ctx, NULL, _arg_194); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_195 = mph_string_new(ctx, "->"); mph_gc_push_root(ctx, (void**)&_arg_195); mph_Token* _ret_200 = mph_new_token(ctx, NULL, mph_TOKEN_ARROW, _arg_195, ({ mph_Lexer* _obj_196 = l; mph_gc_push_root(ctx, (void**)&_obj_196); mph_int _ret_197 = _obj_196->line; mph_gc_pop_roots(ctx, 1); _ret_197; }), ({ mph_Lexer* _obj_198 = l; mph_gc_push_root(ctx, (void**)&_obj_198); mph_int _ret_199 = _obj_198->column; mph_gc_pop_roots(ctx, 1); _ret_199; })); mph_gc_pop_roots(ctx, 1); _ret_200; });
}
	} else {
{
	tok = ({ MorphString* _arg_201 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_201); mph_Token* _ret_206 = mph_new_token(ctx, NULL, mph_TOKEN_MINUS, _arg_201, ({ mph_Lexer* _obj_202 = l; mph_gc_push_root(ctx, (void**)&_obj_202); mph_int _ret_203 = _obj_202->line; mph_gc_pop_roots(ctx, 1); _ret_203; }), ({ mph_Lexer* _obj_204 = l; mph_gc_push_root(ctx, (void**)&_obj_204); mph_int _ret_205 = _obj_204->column; mph_gc_pop_roots(ctx, 1); _ret_205; })); mph_gc_pop_roots(ctx, 1); _ret_206; });
}
	}
}
	} else if ((({ mph_Lexer* _obj_207 = l; mph_gc_push_root(ctx, (void**)&_obj_207); mph_int _ret_208 = _obj_207->ch; mph_gc_pop_roots(ctx, 1); _ret_208; }) == 33)) {
{
	if ((({ mph_Lexer* _arg_209 = l; mph_gc_push_root(ctx, (void**)&_arg_209); mph_int _ret_210 = mph_lexer_peek_char(ctx, NULL, _arg_209); mph_gc_pop_roots(ctx, 1); _ret_210; }) == 61)) {
{
	({ mph_Lexer* _arg_211 = l; mph_gc_push_root(ctx, (void**)&_arg_211); mph_lexer_read_char(ctx, NULL, _arg_211); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_212 = mph_string_new(ctx, "!="); mph_gc_push_root(ctx, (void**)&_arg_212); mph_Token* _ret_217 = mph_new_token(ctx, NULL, mph_TOKEN_NOT_EQ, _arg_212, ({ mph_Lexer* _obj_213 = l; mph_gc_push_root(ctx, (void**)&_obj_213); mph_int _ret_214 = _obj_213->line; mph_gc_pop_roots(ctx, 1); _ret_214; }), ({ mph_Lexer* _obj_215 = l; mph_gc_push_root(ctx, (void**)&_obj_215); mph_int _ret_216 = _obj_215->column; mph_gc_pop_roots(ctx, 1); _ret_216; })); mph_gc_pop_roots(ctx, 1); _ret_217; });
}
	} else {
{
	tok = ({ MorphString* _arg_218 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_218); mph_Token* _ret_223 = mph_new_token(ctx, NULL, mph_TOKEN_BANG, _arg_218, ({ mph_Lexer* _obj_219 = l; mph_gc_push_root(ctx, (void**)&_obj_219); mph_int _ret_220 = _obj_219->line; mph_gc_pop_roots(ctx, 1); _ret_220; }), ({ mph_Lexer* _obj_221 = l; mph_gc_push_root(ctx, (void**)&_obj_221); mph_int _ret_222 = _obj_221->column; mph_gc_pop_roots(ctx, 1); _ret_222; })); mph_gc_pop_roots(ctx, 1); _ret_223; });
}
	}
}
	} else if ((({ mph_Lexer* _obj_224 = l; mph_gc_push_root(ctx, (void**)&_obj_224); mph_int _ret_225 = _obj_224->ch; mph_gc_pop_roots(ctx, 1); _ret_225; }) == 42)) {
{
	tok = ({ MorphString* _arg_226 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_arg_226); mph_Token* _ret_231 = mph_new_token(ctx, NULL, mph_TOKEN_ASTERISK, _arg_226, ({ mph_Lexer* _obj_227 = l; mph_gc_push_root(ctx, (void**)&_obj_227); mph_int _ret_228 = _obj_227->line; mph_gc_pop_roots(ctx, 1); _ret_228; }), ({ mph_Lexer* _obj_229 = l; mph_gc_push_root(ctx, (void**)&_obj_229); mph_int _ret_230 = _obj_229->column; mph_gc_pop_roots(ctx, 1); _ret_230; })); mph_gc_pop_roots(ctx, 1); _ret_231; });
}
	} else if ((({ mph_Lexer* _obj_232 = l; mph_gc_push_root(ctx, (void**)&_obj_232); mph_int _ret_233 = _obj_232->ch; mph_gc_pop_roots(ctx, 1); _ret_233; }) == 47)) {
{
	tok = ({ MorphString* _arg_234 = mph_string_new(ctx, "/"); mph_gc_push_root(ctx, (void**)&_arg_234); mph_Token* _ret_239 = mph_new_token(ctx, NULL, mph_TOKEN_SLASH, _arg_234, ({ mph_Lexer* _obj_235 = l; mph_gc_push_root(ctx, (void**)&_obj_235); mph_int _ret_236 = _obj_235->line; mph_gc_pop_roots(ctx, 1); _ret_236; }), ({ mph_Lexer* _obj_237 = l; mph_gc_push_root(ctx, (void**)&_obj_237); mph_int _ret_238 = _obj_237->column; mph_gc_pop_roots(ctx, 1); _ret_238; })); mph_gc_pop_roots(ctx, 1); _ret_239; });
}
	} else if ((({ mph_Lexer* _obj_240 = l; mph_gc_push_root(ctx, (void**)&_obj_240); mph_int _ret_241 = _obj_240->ch; mph_gc_pop_roots(ctx, 1); _ret_241; }) == 37)) {
{
	tok = ({ MorphString* _arg_242 = mph_string_new(ctx, "%"); mph_gc_push_root(ctx, (void**)&_arg_242); mph_Token* _ret_247 = mph_new_token(ctx, NULL, mph_TOKEN_PERCENT, _arg_242, ({ mph_Lexer* _obj_243 = l; mph_gc_push_root(ctx, (void**)&_obj_243); mph_int _ret_244 = _obj_243->line; mph_gc_pop_roots(ctx, 1); _ret_244; }), ({ mph_Lexer* _obj_245 = l; mph_gc_push_root(ctx, (void**)&_obj_245); mph_int _ret_246 = _obj_245->column; mph_gc_pop_roots(ctx, 1); _ret_246; })); mph_gc_pop_roots(ctx, 1); _ret_247; });
}
	} else if ((({ mph_Lexer* _obj_248 = l; mph_gc_push_root(ctx, (void**)&_obj_248); mph_int _ret_249 = _obj_248->ch; mph_gc_pop_roots(ctx, 1); _ret_249; }) == 60)) {
{
	if ((({ mph_Lexer* _arg_250 = l; mph_gc_push_root(ctx, (void**)&_arg_250); mph_int _ret_251 = mph_lexer_peek_char(ctx, NULL, _arg_250); mph_gc_pop_roots(ctx, 1); _ret_251; }) == 61)) {
{
	({ mph_Lexer* _arg_252 = l; mph_gc_push_root(ctx, (void**)&_arg_252); mph_lexer_read_char(ctx, NULL, _arg_252); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_253 = mph_string_new(ctx, "<="); mph_gc_push_root(ctx, (void**)&_arg_253); mph_Token* _ret_258 = mph_new_token(ctx, NULL, mph_TOKEN_LE, _arg_253, ({ mph_Lexer* _obj_254 = l; mph_gc_push_root(ctx, (void**)&_obj_254); mph_int _ret_255 = _obj_254->line; mph_gc_pop_roots(ctx, 1); _ret_255; }), ({ mph_Lexer* _obj_256 = l; mph_gc_push_root(ctx, (void**)&_obj_256); mph_int _ret_257 = _obj_256->column; mph_gc_pop_roots(ctx, 1); _ret_257; })); mph_gc_pop_roots(ctx, 1); _ret_258; });
}
	} else {
{
	if ((({ mph_Lexer* _arg_259 = l; mph_gc_push_root(ctx, (void**)&_arg_259); mph_int _ret_260 = mph_lexer_peek_char(ctx, NULL, _arg_259); mph_gc_pop_roots(ctx, 1); _ret_260; }) == 60)) {
{
	({ mph_Lexer* _arg_261 = l; mph_gc_push_root(ctx, (void**)&_arg_261); mph_lexer_read_char(ctx, NULL, _arg_261); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_262 = mph_string_new(ctx, "<<"); mph_gc_push_root(ctx, (void**)&_arg_262); mph_Token* _ret_267 = mph_new_token(ctx, NULL, mph_TOKEN_LSHIFT, _arg_262, ({ mph_Lexer* _obj_263 = l; mph_gc_push_root(ctx, (void**)&_obj_263); mph_int _ret_264 = _obj_263->line; mph_gc_pop_roots(ctx, 1); _ret_264; }), ({ mph_Lexer* _obj_265 = l; mph_gc_push_root(ctx, (void**)&_obj_265); mph_int _ret_266 = _obj_265->column; mph_gc_pop_roots(ctx, 1); _ret_266; })); mph_gc_pop_roots(ctx, 1); _ret_267; });
}
	} else {
{
	tok = ({ MorphString* _arg_268 = mph_string_new(ctx, "<"); mph_gc_push_root(ctx, (void**)&_arg_268); mph_Token* _ret_273 = mph_new_token(ctx, NULL, mph_TOKEN_LT, _arg_268, ({ mph_Lexer* _obj_269 = l; mph_gc_push_root(ctx, (void**)&_obj_269); mph_int _ret_270 = _obj_269->line; mph_gc_pop_roots(ctx, 1); _ret_270; }), ({ mph_Lexer* _obj_271 = l; mph_gc_push_root(ctx, (void**)&_obj_271); mph_int _ret_272 = _obj_271->column; mph_gc_pop_roots(ctx, 1); _ret_272; })); mph_gc_pop_roots(ctx, 1); _ret_273; });
}
	}
}
	}
}
	} else if ((({ mph_Lexer* _obj_274 = l; mph_gc_push_root(ctx, (void**)&_obj_274); mph_int _ret_275 = _obj_274->ch; mph_gc_pop_roots(ctx, 1); _ret_275; }) == 62)) {
{
	if ((({ mph_Lexer* _arg_276 = l; mph_gc_push_root(ctx, (void**)&_arg_276); mph_int _ret_277 = mph_lexer_peek_char(ctx, NULL, _arg_276); mph_gc_pop_roots(ctx, 1); _ret_277; }) == 61)) {
{
	({ mph_Lexer* _arg_278 = l; mph_gc_push_root(ctx, (void**)&_arg_278); mph_lexer_read_char(ctx, NULL, _arg_278); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_279 = mph_string_new(ctx, ">="); mph_gc_push_root(ctx, (void**)&_arg_279); mph_Token* _ret_284 = mph_new_token(ctx, NULL, mph_TOKEN_GE, _arg_279, ({ mph_Lexer* _obj_280 = l; mph_gc_push_root(ctx, (void**)&_obj_280); mph_int _ret_281 = _obj_280->line; mph_gc_pop_roots(ctx, 1); _ret_281; }), ({ mph_Lexer* _obj_282 = l; mph_gc_push_root(ctx, (void**)&_obj_282); mph_int _ret_283 = _obj_282->column; mph_gc_pop_roots(ctx, 1); _ret_283; })); mph_gc_pop_roots(ctx, 1); _ret_284; });
}
	} else {
{
	if ((({ mph_Lexer* _arg_285 = l; mph_gc_push_root(ctx, (void**)&_arg_285); mph_int _ret_286 = mph_lexer_peek_char(ctx, NULL, _arg_285); mph_gc_pop_roots(ctx, 1); _ret_286; }) == 62)) {
{
	({ mph_Lexer* _arg_287 = l; mph_gc_push_root(ctx, (void**)&_arg_287); mph_lexer_read_char(ctx, NULL, _arg_287); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_288 = mph_string_new(ctx, ">>"); mph_gc_push_root(ctx, (void**)&_arg_288); mph_Token* _ret_293 = mph_new_token(ctx, NULL, mph_TOKEN_RSHIFT, _arg_288, ({ mph_Lexer* _obj_289 = l; mph_gc_push_root(ctx, (void**)&_obj_289); mph_int _ret_290 = _obj_289->line; mph_gc_pop_roots(ctx, 1); _ret_290; }), ({ mph_Lexer* _obj_291 = l; mph_gc_push_root(ctx, (void**)&_obj_291); mph_int _ret_292 = _obj_291->column; mph_gc_pop_roots(ctx, 1); _ret_292; })); mph_gc_pop_roots(ctx, 1); _ret_293; });
}
	} else {
{
	tok = ({ MorphString* _arg_294 = mph_string_new(ctx, ">"); mph_gc_push_root(ctx, (void**)&_arg_294); mph_Token* _ret_299 = mph_new_token(ctx, NULL, mph_TOKEN_GT, _arg_294, ({ mph_Lexer* _obj_295 = l; mph_gc_push_root(ctx, (void**)&_obj_295); mph_int _ret_296 = _obj_295->line; mph_gc_pop_roots(ctx, 1); _ret_296; }), ({ mph_Lexer* _obj_297 = l; mph_gc_push_root(ctx, (void**)&_obj_297); mph_int _ret_298 = _obj_297->column; mph_gc_pop_roots(ctx, 1); _ret_298; })); mph_gc_pop_roots(ctx, 1); _ret_299; });
}
	}
}
	}
}
	} else if ((({ mph_Lexer* _obj_300 = l; mph_gc_push_root(ctx, (void**)&_obj_300); mph_int _ret_301 = _obj_300->ch; mph_gc_pop_roots(ctx, 1); _ret_301; }) == 38)) {
{
	if ((({ mph_Lexer* _arg_302 = l; mph_gc_push_root(ctx, (void**)&_arg_302); mph_int _ret_303 = mph_lexer_peek_char(ctx, NULL, _arg_302); mph_gc_pop_roots(ctx, 1); _ret_303; }) == 38)) {
{
	({ mph_Lexer* _arg_304 = l; mph_gc_push_root(ctx, (void**)&_arg_304); mph_lexer_read_char(ctx, NULL, _arg_304); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_305 = mph_string_new(ctx, "&&"); mph_gc_push_root(ctx, (void**)&_arg_305); mph_Token* _ret_310 = mph_new_token(ctx, NULL, mph_TOKEN_AND, _arg_305, ({ mph_Lexer* _obj_306 = l; mph_gc_push_root(ctx, (void**)&_obj_306); mph_int _ret_307 = _obj_306->line; mph_gc_pop_roots(ctx, 1); _ret_307; }), ({ mph_Lexer* _obj_308 = l; mph_gc_push_root(ctx, (void**)&_obj_308); mph_int _ret_309 = _obj_308->column; mph_gc_pop_roots(ctx, 1); _ret_309; })); mph_gc_pop_roots(ctx, 1); _ret_310; });
}
	} else {
{
	tok = ({ MorphString* _arg_311 = mph_string_new(ctx, "&"); mph_gc_push_root(ctx, (void**)&_arg_311); mph_Token* _ret_316 = mph_new_token(ctx, NULL, mph_TOKEN_BIT_AND, _arg_311, ({ mph_Lexer* _obj_312 = l; mph_gc_push_root(ctx, (void**)&_obj_312); mph_int _ret_313 = _obj_312->line; mph_gc_pop_roots(ctx, 1); _ret_313; }), ({ mph_Lexer* _obj_314 = l; mph_gc_push_root(ctx, (void**)&_obj_314); mph_int _ret_315 = _obj_314->column; mph_gc_pop_roots(ctx, 1); _ret_315; })); mph_gc_pop_roots(ctx, 1); _ret_316; });
}
	}
}
	} else if ((({ mph_Lexer* _obj_317 = l; mph_gc_push_root(ctx, (void**)&_obj_317); mph_int _ret_318 = _obj_317->ch; mph_gc_pop_roots(ctx, 1); _ret_318; }) == 124)) {
{
	if ((({ mph_Lexer* _arg_319 = l; mph_gc_push_root(ctx, (void**)&_arg_319); mph_int _ret_320 = mph_lexer_peek_char(ctx, NULL, _arg_319); mph_gc_pop_roots(ctx, 1); _ret_320; }) == 124)) {
{
	({ mph_Lexer* _arg_321 = l; mph_gc_push_root(ctx, (void**)&_arg_321); mph_lexer_read_char(ctx, NULL, _arg_321); mph_gc_pop_roots(ctx, 1); });
	tok = ({ MorphString* _arg_322 = mph_string_new(ctx, "||"); mph_gc_push_root(ctx, (void**)&_arg_322); mph_Token* _ret_327 = mph_new_token(ctx, NULL, mph_TOKEN_OR, _arg_322, ({ mph_Lexer* _obj_323 = l; mph_gc_push_root(ctx, (void**)&_obj_323); mph_int _ret_324 = _obj_323->line; mph_gc_pop_roots(ctx, 1); _ret_324; }), ({ mph_Lexer* _obj_325 = l; mph_gc_push_root(ctx, (void**)&_obj_325); mph_int _ret_326 = _obj_325->column; mph_gc_pop_roots(ctx, 1); _ret_326; })); mph_gc_pop_roots(ctx, 1); _ret_327; });
}
	} else {
{
	tok = ({ MorphString* _arg_328 = mph_string_new(ctx, "|"); mph_gc_push_root(ctx, (void**)&_arg_328); mph_Token* _ret_333 = mph_new_token(ctx, NULL, mph_TOKEN_BIT_OR, _arg_328, ({ mph_Lexer* _obj_329 = l; mph_gc_push_root(ctx, (void**)&_obj_329); mph_int _ret_330 = _obj_329->line; mph_gc_pop_roots(ctx, 1); _ret_330; }), ({ mph_Lexer* _obj_331 = l; mph_gc_push_root(ctx, (void**)&_obj_331); mph_int _ret_332 = _obj_331->column; mph_gc_pop_roots(ctx, 1); _ret_332; })); mph_gc_pop_roots(ctx, 1); _ret_333; });
}
	}
}
	} else if ((({ mph_Lexer* _obj_334 = l; mph_gc_push_root(ctx, (void**)&_obj_334); mph_int _ret_335 = _obj_334->ch; mph_gc_pop_roots(ctx, 1); _ret_335; }) == 94)) {
{
	tok = ({ MorphString* _arg_336 = mph_string_new(ctx, "^"); mph_gc_push_root(ctx, (void**)&_arg_336); mph_Token* _ret_341 = mph_new_token(ctx, NULL, mph_TOKEN_BIT_XOR, _arg_336, ({ mph_Lexer* _obj_337 = l; mph_gc_push_root(ctx, (void**)&_obj_337); mph_int _ret_338 = _obj_337->line; mph_gc_pop_roots(ctx, 1); _ret_338; }), ({ mph_Lexer* _obj_339 = l; mph_gc_push_root(ctx, (void**)&_obj_339); mph_int _ret_340 = _obj_339->column; mph_gc_pop_roots(ctx, 1); _ret_340; })); mph_gc_pop_roots(ctx, 1); _ret_341; });
}
	} else if ((({ mph_Lexer* _obj_342 = l; mph_gc_push_root(ctx, (void**)&_obj_342); mph_int _ret_343 = _obj_342->ch; mph_gc_pop_roots(ctx, 1); _ret_343; }) == 126)) {
{
	tok = ({ MorphString* _arg_344 = mph_string_new(ctx, "~"); mph_gc_push_root(ctx, (void**)&_arg_344); mph_Token* _ret_349 = mph_new_token(ctx, NULL, mph_TOKEN_BIT_NOT, _arg_344, ({ mph_Lexer* _obj_345 = l; mph_gc_push_root(ctx, (void**)&_obj_345); mph_int _ret_346 = _obj_345->line; mph_gc_pop_roots(ctx, 1); _ret_346; }), ({ mph_Lexer* _obj_347 = l; mph_gc_push_root(ctx, (void**)&_obj_347); mph_int _ret_348 = _obj_347->column; mph_gc_pop_roots(ctx, 1); _ret_348; })); mph_gc_pop_roots(ctx, 1); _ret_349; });
}
	} else if ((({ mph_Lexer* _obj_350 = l; mph_gc_push_root(ctx, (void**)&_obj_350); mph_int _ret_351 = _obj_350->ch; mph_gc_pop_roots(ctx, 1); _ret_351; }) == 44)) {
{
	tok = ({ MorphString* _arg_352 = mph_string_new(ctx, ","); mph_gc_push_root(ctx, (void**)&_arg_352); mph_Token* _ret_357 = mph_new_token(ctx, NULL, mph_TOKEN_COMMA, _arg_352, ({ mph_Lexer* _obj_353 = l; mph_gc_push_root(ctx, (void**)&_obj_353); mph_int _ret_354 = _obj_353->line; mph_gc_pop_roots(ctx, 1); _ret_354; }), ({ mph_Lexer* _obj_355 = l; mph_gc_push_root(ctx, (void**)&_obj_355); mph_int _ret_356 = _obj_355->column; mph_gc_pop_roots(ctx, 1); _ret_356; })); mph_gc_pop_roots(ctx, 1); _ret_357; });
}
	} else if ((({ mph_Lexer* _obj_358 = l; mph_gc_push_root(ctx, (void**)&_obj_358); mph_int _ret_359 = _obj_358->ch; mph_gc_pop_roots(ctx, 1); _ret_359; }) == 59)) {
{
	tok = ({ MorphString* _arg_360 = mph_string_new(ctx, ";"); mph_gc_push_root(ctx, (void**)&_arg_360); mph_Token* _ret_365 = mph_new_token(ctx, NULL, mph_TOKEN_SEMICOLON, _arg_360, ({ mph_Lexer* _obj_361 = l; mph_gc_push_root(ctx, (void**)&_obj_361); mph_int _ret_362 = _obj_361->line; mph_gc_pop_roots(ctx, 1); _ret_362; }), ({ mph_Lexer* _obj_363 = l; mph_gc_push_root(ctx, (void**)&_obj_363); mph_int _ret_364 = _obj_363->column; mph_gc_pop_roots(ctx, 1); _ret_364; })); mph_gc_pop_roots(ctx, 1); _ret_365; });
}
	} else if ((({ mph_Lexer* _obj_366 = l; mph_gc_push_root(ctx, (void**)&_obj_366); mph_int _ret_367 = _obj_366->ch; mph_gc_pop_roots(ctx, 1); _ret_367; }) == 58)) {
{
	tok = ({ MorphString* _arg_368 = mph_string_new(ctx, ":"); mph_gc_push_root(ctx, (void**)&_arg_368); mph_Token* _ret_373 = mph_new_token(ctx, NULL, mph_TOKEN_COLON, _arg_368, ({ mph_Lexer* _obj_369 = l; mph_gc_push_root(ctx, (void**)&_obj_369); mph_int _ret_370 = _obj_369->line; mph_gc_pop_roots(ctx, 1); _ret_370; }), ({ mph_Lexer* _obj_371 = l; mph_gc_push_root(ctx, (void**)&_obj_371); mph_int _ret_372 = _obj_371->column; mph_gc_pop_roots(ctx, 1); _ret_372; })); mph_gc_pop_roots(ctx, 1); _ret_373; });
}
	} else if ((({ mph_Lexer* _obj_374 = l; mph_gc_push_root(ctx, (void**)&_obj_374); mph_int _ret_375 = _obj_374->ch; mph_gc_pop_roots(ctx, 1); _ret_375; }) == 40)) {
{
	tok = ({ MorphString* _arg_376 = mph_string_new(ctx, "("); mph_gc_push_root(ctx, (void**)&_arg_376); mph_Token* _ret_381 = mph_new_token(ctx, NULL, mph_TOKEN_LPAREN, _arg_376, ({ mph_Lexer* _obj_377 = l; mph_gc_push_root(ctx, (void**)&_obj_377); mph_int _ret_378 = _obj_377->line; mph_gc_pop_roots(ctx, 1); _ret_378; }), ({ mph_Lexer* _obj_379 = l; mph_gc_push_root(ctx, (void**)&_obj_379); mph_int _ret_380 = _obj_379->column; mph_gc_pop_roots(ctx, 1); _ret_380; })); mph_gc_pop_roots(ctx, 1); _ret_381; });
}
	} else if ((({ mph_Lexer* _obj_382 = l; mph_gc_push_root(ctx, (void**)&_obj_382); mph_int _ret_383 = _obj_382->ch; mph_gc_pop_roots(ctx, 1); _ret_383; }) == 41)) {
{
	tok = ({ MorphString* _arg_384 = mph_string_new(ctx, ")"); mph_gc_push_root(ctx, (void**)&_arg_384); mph_Token* _ret_389 = mph_new_token(ctx, NULL, mph_TOKEN_RPAREN, _arg_384, ({ mph_Lexer* _obj_385 = l; mph_gc_push_root(ctx, (void**)&_obj_385); mph_int _ret_386 = _obj_385->line; mph_gc_pop_roots(ctx, 1); _ret_386; }), ({ mph_Lexer* _obj_387 = l; mph_gc_push_root(ctx, (void**)&_obj_387); mph_int _ret_388 = _obj_387->column; mph_gc_pop_roots(ctx, 1); _ret_388; })); mph_gc_pop_roots(ctx, 1); _ret_389; });
}
	} else if ((({ mph_Lexer* _obj_390 = l; mph_gc_push_root(ctx, (void**)&_obj_390); mph_int _ret_391 = _obj_390->ch; mph_gc_pop_roots(ctx, 1); _ret_391; }) == 123)) {
{
	tok = ({ MorphString* _arg_392 = mph_string_new(ctx, "{"); mph_gc_push_root(ctx, (void**)&_arg_392); mph_Token* _ret_397 = mph_new_token(ctx, NULL, mph_TOKEN_LBRACE, _arg_392, ({ mph_Lexer* _obj_393 = l; mph_gc_push_root(ctx, (void**)&_obj_393); mph_int _ret_394 = _obj_393->line; mph_gc_pop_roots(ctx, 1); _ret_394; }), ({ mph_Lexer* _obj_395 = l; mph_gc_push_root(ctx, (void**)&_obj_395); mph_int _ret_396 = _obj_395->column; mph_gc_pop_roots(ctx, 1); _ret_396; })); mph_gc_pop_roots(ctx, 1); _ret_397; });
}
	} else if ((({ mph_Lexer* _obj_398 = l; mph_gc_push_root(ctx, (void**)&_obj_398); mph_int _ret_399 = _obj_398->ch; mph_gc_pop_roots(ctx, 1); _ret_399; }) == 125)) {
{
	tok = ({ MorphString* _arg_400 = mph_string_new(ctx, "}"); mph_gc_push_root(ctx, (void**)&_arg_400); mph_Token* _ret_405 = mph_new_token(ctx, NULL, mph_TOKEN_RBRACE, _arg_400, ({ mph_Lexer* _obj_401 = l; mph_gc_push_root(ctx, (void**)&_obj_401); mph_int _ret_402 = _obj_401->line; mph_gc_pop_roots(ctx, 1); _ret_402; }), ({ mph_Lexer* _obj_403 = l; mph_gc_push_root(ctx, (void**)&_obj_403); mph_int _ret_404 = _obj_403->column; mph_gc_pop_roots(ctx, 1); _ret_404; })); mph_gc_pop_roots(ctx, 1); _ret_405; });
}
	} else if ((({ mph_Lexer* _obj_406 = l; mph_gc_push_root(ctx, (void**)&_obj_406); mph_int _ret_407 = _obj_406->ch; mph_gc_pop_roots(ctx, 1); _ret_407; }) == 91)) {
{
	tok = ({ MorphString* _arg_408 = mph_string_new(ctx, "["); mph_gc_push_root(ctx, (void**)&_arg_408); mph_Token* _ret_413 = mph_new_token(ctx, NULL, mph_TOKEN_LBRACKET, _arg_408, ({ mph_Lexer* _obj_409 = l; mph_gc_push_root(ctx, (void**)&_obj_409); mph_int _ret_410 = _obj_409->line; mph_gc_pop_roots(ctx, 1); _ret_410; }), ({ mph_Lexer* _obj_411 = l; mph_gc_push_root(ctx, (void**)&_obj_411); mph_int _ret_412 = _obj_411->column; mph_gc_pop_roots(ctx, 1); _ret_412; })); mph_gc_pop_roots(ctx, 1); _ret_413; });
}
	} else if ((({ mph_Lexer* _obj_414 = l; mph_gc_push_root(ctx, (void**)&_obj_414); mph_int _ret_415 = _obj_414->ch; mph_gc_pop_roots(ctx, 1); _ret_415; }) == 93)) {
{
	tok = ({ MorphString* _arg_416 = mph_string_new(ctx, "]"); mph_gc_push_root(ctx, (void**)&_arg_416); mph_Token* _ret_421 = mph_new_token(ctx, NULL, mph_TOKEN_RBRACKET, _arg_416, ({ mph_Lexer* _obj_417 = l; mph_gc_push_root(ctx, (void**)&_obj_417); mph_int _ret_418 = _obj_417->line; mph_gc_pop_roots(ctx, 1); _ret_418; }), ({ mph_Lexer* _obj_419 = l; mph_gc_push_root(ctx, (void**)&_obj_419); mph_int _ret_420 = _obj_419->column; mph_gc_pop_roots(ctx, 1); _ret_420; })); mph_gc_pop_roots(ctx, 1); _ret_421; });
}
	} else if ((({ mph_Lexer* _obj_422 = l; mph_gc_push_root(ctx, (void**)&_obj_422); mph_int _ret_423 = _obj_422->ch; mph_gc_pop_roots(ctx, 1); _ret_423; }) == 46)) {
{
	tok = ({ MorphString* _arg_424 = mph_string_new(ctx, "."); mph_gc_push_root(ctx, (void**)&_arg_424); mph_Token* _ret_429 = mph_new_token(ctx, NULL, mph_TOKEN_DOT, _arg_424, ({ mph_Lexer* _obj_425 = l; mph_gc_push_root(ctx, (void**)&_obj_425); mph_int _ret_426 = _obj_425->line; mph_gc_pop_roots(ctx, 1); _ret_426; }), ({ mph_Lexer* _obj_427 = l; mph_gc_push_root(ctx, (void**)&_obj_427); mph_int _ret_428 = _obj_427->column; mph_gc_pop_roots(ctx, 1); _ret_428; })); mph_gc_pop_roots(ctx, 1); _ret_429; });
}
	} else if ((({ mph_Lexer* _obj_430 = l; mph_gc_push_root(ctx, (void**)&_obj_430); mph_int _ret_431 = _obj_430->ch; mph_gc_pop_roots(ctx, 1); _ret_431; }) == 34)) {
{
	MorphString* str_literal = ({ mph_Lexer* _arg_432 = l; mph_gc_push_root(ctx, (void**)&_arg_432); MorphString* _ret_433 = mph_lexer_read_string(ctx, NULL, _arg_432); mph_gc_pop_roots(ctx, 1); _ret_433; });
	mph_gc_push_root(ctx, (void**)&str_literal);
	tok = ({ MorphString* _arg_434 = str_literal; mph_gc_push_root(ctx, (void**)&_arg_434); mph_Token* _ret_439 = mph_new_token(ctx, NULL, mph_TOKEN_STRING, _arg_434, ({ mph_Lexer* _obj_435 = l; mph_gc_push_root(ctx, (void**)&_obj_435); mph_int _ret_436 = _obj_435->line; mph_gc_pop_roots(ctx, 1); _ret_436; }), ({ mph_Lexer* _obj_437 = l; mph_gc_push_root(ctx, (void**)&_obj_437); mph_int _ret_438 = _obj_437->column; mph_gc_pop_roots(ctx, 1); _ret_438; })); mph_gc_pop_roots(ctx, 1); _ret_439; });
	mph_gc_pop_roots(ctx, 1);
}
	} else if ((({ mph_Lexer* _obj_440 = l; mph_gc_push_root(ctx, (void**)&_obj_440); mph_int _ret_441 = _obj_440->ch; mph_gc_pop_roots(ctx, 1); _ret_441; }) == 39)) {
{
	tok = ({ mph_Lexer* _arg_442 = l; mph_gc_push_root(ctx, (void**)&_arg_442); mph_Token* _ret_447 = mph_lexer_read_char_token(ctx, NULL, _arg_442, ({ mph_Lexer* _obj_443 = l; mph_gc_push_root(ctx, (void**)&_obj_443); mph_int _ret_444 = _obj_443->line; mph_gc_pop_roots(ctx, 1); _ret_444; }), ({ mph_Lexer* _obj_445 = l; mph_gc_push_root(ctx, (void**)&_obj_445); mph_int _ret_446 = _obj_445->column; mph_gc_pop_roots(ctx, 1); _ret_446; })); mph_gc_pop_roots(ctx, 1); _ret_447; });
	return tok;
}
	} else if ((({ mph_Lexer* _obj_448 = l; mph_gc_push_root(ctx, (void**)&_obj_448); mph_int _ret_449 = _obj_448->ch; mph_gc_pop_roots(ctx, 1); _ret_449; }) == 0)) {
{
	tok = ({ MorphString* _arg_450 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_450); mph_Token* _ret_455 = mph_new_token(ctx, NULL, mph_TOKEN_EOF, _arg_450, ({ mph_Lexer* _obj_451 = l; mph_gc_push_root(ctx, (void**)&_obj_451); mph_int _ret_452 = _obj_451->line; mph_gc_pop_roots(ctx, 1); _ret_452; }), ({ mph_Lexer* _obj_453 = l; mph_gc_push_root(ctx, (void**)&_obj_453); mph_int _ret_454 = _obj_453->column; mph_gc_pop_roots(ctx, 1); _ret_454; })); mph_gc_pop_roots(ctx, 1); _ret_455; });
}
	} else {
{
	if (mph_is_letter(ctx, NULL, ({ mph_Lexer* _obj_456 = l; mph_gc_push_root(ctx, (void**)&_obj_456); mph_int _ret_457 = _obj_456->ch; mph_gc_pop_roots(ctx, 1); _ret_457; }))) {
{
	MorphString* literal = ({ mph_Lexer* _arg_458 = l; mph_gc_push_root(ctx, (void**)&_arg_458); MorphString* _ret_459 = mph_lexer_read_identifier(ctx, NULL, _arg_458); mph_gc_pop_roots(ctx, 1); _ret_459; });
	mph_gc_push_root(ctx, (void**)&literal);
	mph_int token_type = ({ MorphString* _arg_460 = literal; mph_gc_push_root(ctx, (void**)&_arg_460); mph_int _ret_461 = mph_lookup_ident(ctx, NULL, _arg_460); mph_gc_pop_roots(ctx, 1); _ret_461; });
	tok = ({ MorphString* _arg_462 = literal; mph_gc_push_root(ctx, (void**)&_arg_462); mph_Token* _ret_467 = mph_new_token(ctx, NULL, token_type, _arg_462, ({ mph_Lexer* _obj_463 = l; mph_gc_push_root(ctx, (void**)&_obj_463); mph_int _ret_464 = _obj_463->line; mph_gc_pop_roots(ctx, 1); _ret_464; }), ({ mph_Lexer* _obj_465 = l; mph_gc_push_root(ctx, (void**)&_obj_465); mph_int _ret_466 = _obj_465->column; mph_gc_pop_roots(ctx, 1); _ret_466; })); mph_gc_pop_roots(ctx, 1); _ret_467; });
	return tok;
	mph_gc_pop_roots(ctx, 1);
}
	} else {
{
	if (mph_is_digit(ctx, NULL, ({ mph_Lexer* _obj_468 = l; mph_gc_push_root(ctx, (void**)&_obj_468); mph_int _ret_469 = _obj_468->ch; mph_gc_pop_roots(ctx, 1); _ret_469; }))) {
{
	tok = ({ mph_Lexer* _arg_470 = l; mph_gc_push_root(ctx, (void**)&_arg_470); mph_Token* _ret_475 = mph_lexer_read_number_token(ctx, NULL, _arg_470, ({ mph_Lexer* _obj_471 = l; mph_gc_push_root(ctx, (void**)&_obj_471); mph_int _ret_472 = _obj_471->line; mph_gc_pop_roots(ctx, 1); _ret_472; }), ({ mph_Lexer* _obj_473 = l; mph_gc_push_root(ctx, (void**)&_obj_473); mph_int _ret_474 = _obj_473->column; mph_gc_pop_roots(ctx, 1); _ret_474; })); mph_gc_pop_roots(ctx, 1); _ret_475; });
	return tok;
}
	} else {
{
	tok = ({ MorphString* _arg_476 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_476); mph_Token* _ret_481 = mph_new_token(ctx, NULL, mph_TOKEN_ILLEGAL, _arg_476, ({ mph_Lexer* _obj_477 = l; mph_gc_push_root(ctx, (void**)&_obj_477); mph_int _ret_478 = _obj_477->line; mph_gc_pop_roots(ctx, 1); _ret_478; }), ({ mph_Lexer* _obj_479 = l; mph_gc_push_root(ctx, (void**)&_obj_479); mph_int _ret_480 = _obj_479->column; mph_gc_pop_roots(ctx, 1); _ret_480; })); mph_gc_pop_roots(ctx, 1); _ret_481; });
}
	}
}
	}
}
	}
	({ mph_Lexer* _arg_482 = l; mph_gc_push_root(ctx, (void**)&_arg_482); mph_lexer_read_char(ctx, NULL, _arg_482); mph_gc_pop_roots(ctx, 1); });
	return tok;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_TOKEN_ILLEGAL = 0;
	mph_TOKEN_EOF = 1;
	mph_TOKEN_IDENT = 2;
	mph_TOKEN_INT = 3;
	mph_TOKEN_FLOAT = 4;
	mph_TOKEN_STRING = 5;
	mph_TOKEN_CHAR = 6;
	mph_TOKEN_ASSIGN = 7;
	mph_TOKEN_PLUS = 8;
	mph_TOKEN_MINUS = 9;
	mph_TOKEN_BANG = 10;
	mph_TOKEN_ASTERISK = 11;
	mph_TOKEN_SLASH = 12;
	mph_TOKEN_PERCENT = 13;
	mph_TOKEN_EQ = 14;
	mph_TOKEN_NOT_EQ = 15;
	mph_TOKEN_LT = 16;
	mph_TOKEN_GT = 17;
	mph_TOKEN_LE = 18;
	mph_TOKEN_GE = 19;
	mph_TOKEN_AND = 20;
	mph_TOKEN_OR = 21;
	mph_TOKEN_BIT_AND = 22;
	mph_TOKEN_BIT_OR = 23;
	mph_TOKEN_BIT_XOR = 24;
	mph_TOKEN_BIT_NOT = 25;
	mph_TOKEN_LSHIFT = 26;
	mph_TOKEN_RSHIFT = 27;
	mph_TOKEN_COMMA = 28;
	mph_TOKEN_SEMICOLON = 29;
	mph_TOKEN_COLON = 30;
	mph_TOKEN_DOT = 31;
	mph_TOKEN_ARROW = 32;
	mph_TOKEN_LPAREN = 33;
	mph_TOKEN_RPAREN = 34;
	mph_TOKEN_LBRACE = 35;
	mph_TOKEN_RBRACE = 36;
	mph_TOKEN_LBRACKET = 37;
	mph_TOKEN_RBRACKET = 38;
	mph_TOKEN_FUNGSI = 39;
	mph_TOKEN_NATIVE = 40;
	mph_TOKEN_JIKA = 41;
	mph_TOKEN_ATAU_JIKA = 42;
	mph_TOKEN_LAINNYA = 43;
	mph_TOKEN_KEMBALIKAN = 44;
	mph_TOKEN_BENAR = 45;
	mph_TOKEN_SALAH = 46;
	mph_TOKEN_KOSONG = 47;
	mph_TOKEN_AKHIR = 48;
	mph_TOKEN_SELAMA = 49;
	mph_TOKEN_DAN = 50;
	mph_TOKEN_ATAU = 51;
	mph_TOKEN_AMBIL = 52;
	mph_TOKEN_DARI = 53;
	mph_TOKEN_BERHENTI = 54;
	mph_TOKEN_LANJUT = 55;
	mph_TOKEN_STRUKTUR = 56;
	mph_TOKEN_INTERFACE = 57;
	mph_TOKEN_VAR = 58;
	mph_TOKEN_TETAPAN = 59;
	mph_TOKEN_MAP = 60;
	mph_TOKEN_PILIH = 61;
	mph_TOKEN_KASUS = 62;
	mph_STATE_CODE = 0;
	mph_STATE_STRING = 1;
}
