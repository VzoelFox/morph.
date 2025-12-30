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

// Struct Definitions (Env & Types)
typedef struct mph_Token mph_Token;
struct mph_Token {
	mph_int token_type;
	MorphString* literal;
};

MorphTypeInfo mph_ti_mph_Token = { "Token", sizeof(mph_Token), 1, (size_t[]){offsetof(mph_Token, literal)} };

// Global Variables
mph_int mph_TOKEN_IDENT;
mph_int mph_TOKEN_INT;

// Function Prototypes
mph_Token* mph_new_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal);
void mph_main(MorphContext* ctx, void* _env_void);

// Function Definitions
mph_Token* mph_new_token(MorphContext* ctx, void* _env_void, mph_int token_type, MorphString* literal) {
	mph_gc_push_root(ctx, (void**)&literal);
	return ({ mph_Token* _t = (mph_Token*)mph_alloc(ctx, sizeof(mph_Token), &mph_ti_mph_Token); mph_gc_push_root(ctx, (void**)&_t); _t->token_type = token_type; _t->literal = literal; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

void mph_main(MorphContext* ctx, void* _env_void) {
	mph_Token* tok = ({ MorphString* _arg_1 = mph_string_new(ctx, "test"); mph_gc_push_root(ctx, (void**)&_arg_1); mph_Token* _ret_2 = mph_new_token(ctx, NULL, mph_TOKEN_IDENT, _arg_1); mph_gc_pop_roots(ctx, 1); _ret_2; });
	mph_gc_push_root(ctx, (void**)&tok);
	mph_native_print(ctx, mph_string_new(ctx, "Token created\n"));
	mph_gc_pop_roots(ctx, 1);
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_TOKEN_IDENT = 1;
	mph_TOKEN_INT = 2;
	mph_main(ctx, NULL);
}
