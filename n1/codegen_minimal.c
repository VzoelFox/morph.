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
#define MPH_TYPE_mph_Codegen 1

// Struct Definitions (Env & Types)
typedef struct mph_Codegen mph_Codegen;
struct mph_Codegen {
	MorphString* output;
	mph_int temp_index;
};

MorphTypeInfo mph_ti_mph_Codegen = { "Codegen", sizeof(mph_Codegen), 1, (size_t[]){offsetof(mph_Codegen, output)} };

// Global Variables

// Function Prototypes
mph_Codegen* mph_new_codegen(MorphContext* ctx, void* _env_void);
void mph_test_void_with_while(MorphContext* ctx, void* _env_void);
void mph_main(MorphContext* ctx, void* _env_void);

// Function Definitions
mph_Codegen* mph_new_codegen(MorphContext* ctx, void* _env_void) {
	return ({ mph_Codegen* _t = (mph_Codegen*)mph_alloc(ctx, sizeof(mph_Codegen), &mph_ti_mph_Codegen); mph_gc_push_root(ctx, (void**)&_t); _t->output = mph_string_new(ctx, ""); _t->temp_index = 0; mph_gc_pop_roots(ctx, 1); _t; });
}

void mph_test_void_with_while(MorphContext* ctx, void* _env_void) {
	mph_int i = 0;
	while ((i < 5)) {
{
	i = (i + 1);
}
	}
}

void mph_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "Codegen minimal test\n"));
	mph_test_void_with_while(ctx, NULL);
	mph_Codegen* cg = mph_new_codegen(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&cg);
	mph_native_print(ctx, mph_string_new(ctx, "OK\n"));
	mph_gc_pop_roots(ctx, 1);
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_main(ctx, NULL);
}
