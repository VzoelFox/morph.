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
#define MPH_TYPE_mph_HashMap 1

// Struct Definitions (Env & Types)
typedef struct mph_HashMap mph_HashMap;
struct mph_HashMap {
	mph_int ptr;
	mph_int kind;
	mph_bool is_ptr;
};

MorphTypeInfo mph_ti_mph_HashMap = { "HashMap", sizeof(mph_HashMap), 0, NULL };

// Global Variables

// Function Prototypes
mph_HashMap* mph_HashMapNew(MorphContext* ctx, void* _env_void, mph_int kind, mph_bool is_ptr);
void mph_HashMapSet(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key, mph_int value);
mph_int mph_HashMapGet(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key);
mph_int mph_HashMapLen(MorphContext* ctx, void* _env_void, mph_HashMap* m);
mph_bool mph_HashMapHasKey(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key);
void mph_HashMapDelete(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key);
void mph_HashMapSetInt(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key, mph_int value);
mph_int mph_HashMapGetInt(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key);
mph_int mph_native_hashmap_new(MorphContext* ctx, void* _env_void, mph_int kind, mph_int val_is_ptr);
void mph_native_hashmap_set(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key, mph_int value);
mph_int mph_native_hashmap_get(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key);
mph_int mph_native_hashmap_len(MorphContext* ctx, void* _env_void, mph_int map_ptr);
mph_int mph_native_hashmap_has_key(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key);
void mph_native_hashmap_delete(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key);
mph_int mph_native_bool_to_int(MorphContext* ctx, void* _env_void, mph_bool b);

// Function Definitions
mph_HashMap* mph_HashMapNew(MorphContext* ctx, void* _env_void, mph_int kind, mph_bool is_ptr) {
	mph_int ptr = mph_native_hashmap_new(ctx, NULL, kind, mph_native_bool_to_int(ctx, NULL, is_ptr));
	return ({ mph_HashMap* _t = (mph_HashMap*)mph_alloc(ctx, sizeof(mph_HashMap), &mph_ti_mph_HashMap); mph_gc_push_root(ctx, (void**)&_t); _t->is_ptr = is_ptr; _t->ptr = ptr; _t->kind = kind; mph_gc_pop_roots(ctx, 1); _t; });
}

void mph_HashMapSet(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key, mph_int value) {
	mph_gc_push_root(ctx, (void**)&m);
	mph_gc_push_root(ctx, (void**)&key);
	({ MorphString* _arg_3 = key; mph_gc_push_root(ctx, (void**)&_arg_3); mph_native_hashmap_set(ctx, NULL, ({ mph_HashMap* _obj_1 = m; mph_gc_push_root(ctx, (void**)&_obj_1); mph_int _ret_2 = _obj_1->ptr; mph_gc_pop_roots(ctx, 1); _ret_2; }), _arg_3, value); mph_gc_pop_roots(ctx, 1); });
	mph_gc_pop_roots(ctx, 2);
}

mph_int mph_HashMapGet(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key) {
	mph_gc_push_root(ctx, (void**)&m);
	mph_gc_push_root(ctx, (void**)&key);
	return ({ MorphString* _arg_6 = key; mph_gc_push_root(ctx, (void**)&_arg_6); mph_int _ret_7 = mph_native_hashmap_get(ctx, NULL, ({ mph_HashMap* _obj_4 = m; mph_gc_push_root(ctx, (void**)&_obj_4); mph_int _ret_5 = _obj_4->ptr; mph_gc_pop_roots(ctx, 1); _ret_5; }), _arg_6); mph_gc_pop_roots(ctx, 1); _ret_7; });
	mph_gc_pop_roots(ctx, 2);
}

mph_int mph_HashMapLen(MorphContext* ctx, void* _env_void, mph_HashMap* m) {
	mph_gc_push_root(ctx, (void**)&m);
	return mph_native_hashmap_len(ctx, NULL, ({ mph_HashMap* _obj_8 = m; mph_gc_push_root(ctx, (void**)&_obj_8); mph_int _ret_9 = _obj_8->ptr; mph_gc_pop_roots(ctx, 1); _ret_9; }));
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_HashMapHasKey(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key) {
	mph_gc_push_root(ctx, (void**)&m);
	mph_gc_push_root(ctx, (void**)&key);
	mph_int result = ({ MorphString* _arg_12 = key; mph_gc_push_root(ctx, (void**)&_arg_12); mph_int _ret_13 = mph_native_hashmap_has_key(ctx, NULL, ({ mph_HashMap* _obj_10 = m; mph_gc_push_root(ctx, (void**)&_obj_10); mph_int _ret_11 = _obj_10->ptr; mph_gc_pop_roots(ctx, 1); _ret_11; }), _arg_12); mph_gc_pop_roots(ctx, 1); _ret_13; });
	if ((result == 1)) {
{
	return 1;
}
	}
	return 0;
	mph_gc_pop_roots(ctx, 2);
}

void mph_HashMapDelete(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key) {
	mph_gc_push_root(ctx, (void**)&m);
	mph_gc_push_root(ctx, (void**)&key);
	({ MorphString* _arg_16 = key; mph_gc_push_root(ctx, (void**)&_arg_16); mph_native_hashmap_delete(ctx, NULL, ({ mph_HashMap* _obj_14 = m; mph_gc_push_root(ctx, (void**)&_obj_14); mph_int _ret_15 = _obj_14->ptr; mph_gc_pop_roots(ctx, 1); _ret_15; }), _arg_16); mph_gc_pop_roots(ctx, 1); });
	mph_gc_pop_roots(ctx, 2);
}

void mph_HashMapSetInt(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key, mph_int value) {
	mph_gc_push_root(ctx, (void**)&m);
	mph_gc_push_root(ctx, (void**)&key);
	({ mph_HashMap* _arg_17 = m; mph_gc_push_root(ctx, (void**)&_arg_17); MorphString* _arg_18 = key; mph_gc_push_root(ctx, (void**)&_arg_18); mph_HashMapSet(ctx, NULL, _arg_17, _arg_18, value); mph_gc_pop_roots(ctx, 2); });
	mph_gc_pop_roots(ctx, 2);
}

mph_int mph_HashMapGetInt(MorphContext* ctx, void* _env_void, mph_HashMap* m, MorphString* key) {
	mph_gc_push_root(ctx, (void**)&m);
	mph_gc_push_root(ctx, (void**)&key);
	return ({ mph_HashMap* _arg_19 = m; mph_gc_push_root(ctx, (void**)&_arg_19); MorphString* _arg_20 = key; mph_gc_push_root(ctx, (void**)&_arg_20); mph_int _ret_21 = mph_HashMapGet(ctx, NULL, _arg_19, _arg_20); mph_gc_pop_roots(ctx, 2); _ret_21; });
	mph_gc_pop_roots(ctx, 2);
}

mph_int mph_native_hashmap_new(MorphContext* ctx, void* _env_void, mph_int kind, mph_int val_is_ptr) {
	return 0;
}

void mph_native_hashmap_set(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key, mph_int value) {
	mph_gc_push_root(ctx, (void**)&key);
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_native_hashmap_get(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key) {
	mph_gc_push_root(ctx, (void**)&key);
	return 0;
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_native_hashmap_len(MorphContext* ctx, void* _env_void, mph_int map_ptr) {
	return 0;
}

mph_int mph_native_hashmap_has_key(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key) {
	mph_gc_push_root(ctx, (void**)&key);
	return 0;
	mph_gc_pop_roots(ctx, 1);
}

void mph_native_hashmap_delete(MorphContext* ctx, void* _env_void, mph_int map_ptr, MorphString* key) {
	mph_gc_push_root(ctx, (void**)&key);
	mph_gc_pop_roots(ctx, 1);
}

mph_int mph_native_bool_to_int(MorphContext* ctx, void* _env_void, mph_bool b) {
	if (b) {
{
	return 1;
}
	}
	return 0;
}


// Entry Point
void morph_entry_point(MorphContext* ctx) {
}
