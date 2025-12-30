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
#define MPH_TYPE_mph_Type 1

// Struct Definitions (Env & Types)
typedef struct mph_Type mph_Type;
struct mph_Type {
	mph_int kind;
	MorphString* name;
};

MorphTypeInfo mph_ti_mph_Type = { "Type", sizeof(mph_Type), 1, (size_t[]){offsetof(mph_Type, name)} };

// Global Variables
mph_int mph_KIND_INT;

// Function Prototypes
mph_Type* mph_int_type(MorphContext* ctx, void* _env_void);
mph_int mph_main(MorphContext* ctx, void* _env_void);

// Function Definitions
mph_Type* mph_int_type(MorphContext* ctx, void* _env_void) {
	return ({ mph_Type* _t = (mph_Type*)mph_alloc(ctx, sizeof(mph_Type), &mph_ti_mph_Type); mph_gc_push_root(ctx, (void**)&_t); _t->kind = mph_KIND_INT; _t->name = mph_string_new(ctx, "int"); mph_gc_pop_roots(ctx, 1); _t; });
}

mph_int mph_main(MorphContext* ctx, void* _env_void) {
	mph_Type* t = mph_int_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t);
	return 42;
	mph_gc_pop_roots(ctx, 1);
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_KIND_INT = 0;
	mph_main(ctx, NULL);
}
