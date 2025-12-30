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
#define MPH_TYPE_mph_TypeResult 2

// Struct Definitions (Env & Types)
typedef struct mph_Type mph_Type;
typedef struct mph_TypeResult mph_TypeResult;
struct mph_Type {
	mph_int kind;
	MorphString* name;
};

struct mph_TypeResult {
	mph_Type* result;
	MorphString* error_msg;
	mph_bool has_error;
};

MorphTypeInfo mph_ti_mph_Type = { "Type", sizeof(mph_Type), 1, (size_t[]){offsetof(mph_Type, name)} };
MorphTypeInfo mph_ti_mph_TypeResult = { "TypeResult", sizeof(mph_TypeResult), 2, (size_t[]){offsetof(mph_TypeResult, result), offsetof(mph_TypeResult, error_msg)} };

// Global Variables
mph_int mph_KIND_INT;
mph_int mph_KIND_FLOAT;
mph_int mph_KIND_STRING;
mph_int mph_KIND_BOOL;
mph_int mph_KIND_VOID;
mph_int mph_KIND_FUNCTION;
mph_int mph_KIND_STRUCT;
mph_int mph_KIND_INTERFACE;
mph_int mph_KIND_ARRAY;
mph_int mph_KIND_MAP;
mph_int mph_KIND_POINTER;
mph_int mph_KIND_MULTI;
mph_int mph_KIND_UNKNOWN;
mph_int mph_KIND_ERROR;
mph_int mph_KIND_NULL;
mph_int mph_KIND_USER_ERROR;
mph_int mph_KIND_MODULE;
mph_int mph_KIND_CHANNEL;

// Function Prototypes
mph_Type* mph_make_type(MorphContext* ctx, void* _env_void, mph_int k, MorphString* n);
mph_Type* mph_int_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_float_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_string_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_bool_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_void_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_null_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_unknown_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_error_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_user_error_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_channel_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_array_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_map_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_struct_type(MorphContext* ctx, void* _env_void, MorphString* n);
mph_Type* mph_interface_type(MorphContext* ctx, void* _env_void, MorphString* n);
mph_Type* mph_function_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_pointer_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_multi_type(MorphContext* ctx, void* _env_void);
mph_Type* mph_module_type(MorphContext* ctx, void* _env_void, MorphString* n);
mph_bool mph_type_equals(MorphContext* ctx, void* _env_void, mph_Type* t1, mph_Type* t2);
mph_bool mph_type_assignable_to(MorphContext* ctx, void* _env_void, mph_Type* source, mph_Type* target);
mph_bool mph_type_is_comparable(MorphContext* ctx, void* _env_void, mph_Type* t);
mph_TypeResult* mph_make_type_result(MorphContext* ctx, void* _env_void, mph_Type* t);
mph_TypeResult* mph_make_type_error(MorphContext* ctx, void* _env_void, MorphString* msg);
mph_TypeResult* mph_type_binary_op(MorphContext* ctx, void* _env_void, mph_Type* left, MorphString* op, mph_Type* right);
mph_TypeResult* mph_type_prefix_op(MorphContext* ctx, void* _env_void, mph_Type* t, MorphString* op);
MorphString* mph_kind_to_string(MorphContext* ctx, void* _env_void, mph_int k);
mph_Type* mph_IntType(MorphContext* ctx, void* _env_void);
mph_Type* mph_FloatType(MorphContext* ctx, void* _env_void);
mph_Type* mph_StringType(MorphContext* ctx, void* _env_void);
mph_Type* mph_BoolType(MorphContext* ctx, void* _env_void);
mph_Type* mph_VoidType(MorphContext* ctx, void* _env_void);
mph_Type* mph_NullType(MorphContext* ctx, void* _env_void);
mph_Type* mph_UnknownType(MorphContext* ctx, void* _env_void);
mph_Type* mph_ErrorType(MorphContext* ctx, void* _env_void);
mph_Type* mph_UserErrorType(MorphContext* ctx, void* _env_void);
mph_Type* mph_ChannelType(MorphContext* ctx, void* _env_void);
mph_Type* mph_ArrayType(MorphContext* ctx, void* _env_void);
mph_Type* mph_MapType(MorphContext* ctx, void* _env_void);
mph_Type* mph_StructType(MorphContext* ctx, void* _env_void, MorphString* n);
mph_Type* mph_InterfaceType(MorphContext* ctx, void* _env_void, MorphString* n);
mph_Type* mph_FunctionType(MorphContext* ctx, void* _env_void);
mph_Type* mph_PointerType(MorphContext* ctx, void* _env_void);
mph_Type* mph_MultiType(MorphContext* ctx, void* _env_void);
mph_Type* mph_ModuleType(MorphContext* ctx, void* _env_void, MorphString* n);
mph_bool mph_TypeEquals(MorphContext* ctx, void* _env_void, mph_Type* t1, mph_Type* t2);
mph_bool mph_TypeAssignableTo(MorphContext* ctx, void* _env_void, mph_Type* source, mph_Type* target);
mph_bool mph_TypeIsComparable(MorphContext* ctx, void* _env_void, mph_Type* t);
mph_TypeResult* mph_TypeBinaryOp(MorphContext* ctx, void* _env_void, mph_Type* left, MorphString* op, mph_Type* right);
mph_TypeResult* mph_TypePrefixOp(MorphContext* ctx, void* _env_void, mph_Type* t, MorphString* op);
MorphString* mph_KindToString(MorphContext* ctx, void* _env_void, mph_int k);
void mph_main(MorphContext* ctx, void* _env_void);

// Function Definitions
mph_Type* mph_make_type(MorphContext* ctx, void* _env_void, mph_int k, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ mph_Type* _t = (mph_Type*)mph_alloc(ctx, sizeof(mph_Type), &mph_ti_mph_Type); mph_gc_push_root(ctx, (void**)&_t); _t->kind = k; _t->name = n; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_Type* mph_int_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_1 = mph_string_new(ctx, "int"); mph_gc_push_root(ctx, (void**)&_arg_1); mph_Type* _ret_2 = mph_make_type(ctx, NULL, mph_KIND_INT, _arg_1); mph_gc_pop_roots(ctx, 1); _ret_2; });
}

mph_Type* mph_float_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_3 = mph_string_new(ctx, "float"); mph_gc_push_root(ctx, (void**)&_arg_3); mph_Type* _ret_4 = mph_make_type(ctx, NULL, mph_KIND_FLOAT, _arg_3); mph_gc_pop_roots(ctx, 1); _ret_4; });
}

mph_Type* mph_string_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_5 = mph_string_new(ctx, "string"); mph_gc_push_root(ctx, (void**)&_arg_5); mph_Type* _ret_6 = mph_make_type(ctx, NULL, mph_KIND_STRING, _arg_5); mph_gc_pop_roots(ctx, 1); _ret_6; });
}

mph_Type* mph_bool_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_7 = mph_string_new(ctx, "bool"); mph_gc_push_root(ctx, (void**)&_arg_7); mph_Type* _ret_8 = mph_make_type(ctx, NULL, mph_KIND_BOOL, _arg_7); mph_gc_pop_roots(ctx, 1); _ret_8; });
}

mph_Type* mph_void_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_9 = mph_string_new(ctx, "void"); mph_gc_push_root(ctx, (void**)&_arg_9); mph_Type* _ret_10 = mph_make_type(ctx, NULL, mph_KIND_VOID, _arg_9); mph_gc_pop_roots(ctx, 1); _ret_10; });
}

mph_Type* mph_null_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_11 = mph_string_new(ctx, "null"); mph_gc_push_root(ctx, (void**)&_arg_11); mph_Type* _ret_12 = mph_make_type(ctx, NULL, mph_KIND_NULL, _arg_11); mph_gc_pop_roots(ctx, 1); _ret_12; });
}

mph_Type* mph_unknown_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_13 = mph_string_new(ctx, "unknown"); mph_gc_push_root(ctx, (void**)&_arg_13); mph_Type* _ret_14 = mph_make_type(ctx, NULL, mph_KIND_UNKNOWN, _arg_13); mph_gc_pop_roots(ctx, 1); _ret_14; });
}

mph_Type* mph_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_15 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_15); mph_Type* _ret_16 = mph_make_type(ctx, NULL, mph_KIND_ERROR, _arg_15); mph_gc_pop_roots(ctx, 1); _ret_16; });
}

mph_Type* mph_user_error_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_17 = mph_string_new(ctx, "error"); mph_gc_push_root(ctx, (void**)&_arg_17); mph_Type* _ret_18 = mph_make_type(ctx, NULL, mph_KIND_USER_ERROR, _arg_17); mph_gc_pop_roots(ctx, 1); _ret_18; });
}

mph_Type* mph_channel_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_19 = mph_string_new(ctx, "channel"); mph_gc_push_root(ctx, (void**)&_arg_19); mph_Type* _ret_20 = mph_make_type(ctx, NULL, mph_KIND_CHANNEL, _arg_19); mph_gc_pop_roots(ctx, 1); _ret_20; });
}

mph_Type* mph_array_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_21 = mph_string_new(ctx, "array"); mph_gc_push_root(ctx, (void**)&_arg_21); mph_Type* _ret_22 = mph_make_type(ctx, NULL, mph_KIND_ARRAY, _arg_21); mph_gc_pop_roots(ctx, 1); _ret_22; });
}

mph_Type* mph_map_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_23 = mph_string_new(ctx, "map"); mph_gc_push_root(ctx, (void**)&_arg_23); mph_Type* _ret_24 = mph_make_type(ctx, NULL, mph_KIND_MAP, _arg_23); mph_gc_pop_roots(ctx, 1); _ret_24; });
}

mph_Type* mph_struct_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_25 = n; mph_gc_push_root(ctx, (void**)&_arg_25); mph_Type* _ret_26 = mph_make_type(ctx, NULL, mph_KIND_STRUCT, _arg_25); mph_gc_pop_roots(ctx, 1); _ret_26; });
	mph_gc_pop_roots(ctx, 1);
}

mph_Type* mph_interface_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_27 = n; mph_gc_push_root(ctx, (void**)&_arg_27); mph_Type* _ret_28 = mph_make_type(ctx, NULL, mph_KIND_INTERFACE, _arg_27); mph_gc_pop_roots(ctx, 1); _ret_28; });
	mph_gc_pop_roots(ctx, 1);
}

mph_Type* mph_function_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_29 = mph_string_new(ctx, "function"); mph_gc_push_root(ctx, (void**)&_arg_29); mph_Type* _ret_30 = mph_make_type(ctx, NULL, mph_KIND_FUNCTION, _arg_29); mph_gc_pop_roots(ctx, 1); _ret_30; });
}

mph_Type* mph_pointer_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_31 = mph_string_new(ctx, "pointer"); mph_gc_push_root(ctx, (void**)&_arg_31); mph_Type* _ret_32 = mph_make_type(ctx, NULL, mph_KIND_POINTER, _arg_31); mph_gc_pop_roots(ctx, 1); _ret_32; });
}

mph_Type* mph_multi_type(MorphContext* ctx, void* _env_void) {
	return ({ MorphString* _arg_33 = mph_string_new(ctx, "multi"); mph_gc_push_root(ctx, (void**)&_arg_33); mph_Type* _ret_34 = mph_make_type(ctx, NULL, mph_KIND_MULTI, _arg_33); mph_gc_pop_roots(ctx, 1); _ret_34; });
}

mph_Type* mph_module_type(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_35 = n; mph_gc_push_root(ctx, (void**)&_arg_35); mph_Type* _ret_36 = mph_make_type(ctx, NULL, mph_KIND_MODULE, _arg_35); mph_gc_pop_roots(ctx, 1); _ret_36; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_type_equals(MorphContext* ctx, void* _env_void, mph_Type* t1, mph_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return (({ mph_Type* _obj_37 = t1; mph_gc_push_root(ctx, (void**)&_obj_37); mph_int _ret_38 = _obj_37->kind; mph_gc_pop_roots(ctx, 1); _ret_38; }) == ({ mph_Type* _obj_39 = t2; mph_gc_push_root(ctx, (void**)&_obj_39); mph_int _ret_40 = _obj_39->kind; mph_gc_pop_roots(ctx, 1); _ret_40; }));
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_type_assignable_to(MorphContext* ctx, void* _env_void, mph_Type* source, mph_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	if ((({ mph_Type* _obj_41 = source; mph_gc_push_root(ctx, (void**)&_obj_41); mph_int _ret_42 = _obj_41->kind; mph_gc_pop_roots(ctx, 1); _ret_42; }) == mph_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_43 = target; mph_gc_push_root(ctx, (void**)&_obj_43); mph_int _ret_44 = _obj_43->kind; mph_gc_pop_roots(ctx, 1); _ret_44; }) == mph_KIND_UNKNOWN)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_45 = source; mph_gc_push_root(ctx, (void**)&_obj_45); mph_int _ret_46 = _obj_45->kind; mph_gc_pop_roots(ctx, 1); _ret_46; }) == mph_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_47 = target; mph_gc_push_root(ctx, (void**)&_obj_47); mph_int _ret_48 = _obj_47->kind; mph_gc_pop_roots(ctx, 1); _ret_48; }) == mph_KIND_ERROR)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_49 = source; mph_gc_push_root(ctx, (void**)&_obj_49); mph_int _ret_50 = _obj_49->kind; mph_gc_pop_roots(ctx, 1); _ret_50; }) == mph_KIND_NULL)) {
{
	if ((({ mph_Type* _obj_51 = target; mph_gc_push_root(ctx, (void**)&_obj_51); mph_int _ret_52 = _obj_51->kind; mph_gc_pop_roots(ctx, 1); _ret_52; }) == mph_KIND_ARRAY)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_53 = target; mph_gc_push_root(ctx, (void**)&_obj_53); mph_int _ret_54 = _obj_53->kind; mph_gc_pop_roots(ctx, 1); _ret_54; }) == mph_KIND_MAP)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_55 = target; mph_gc_push_root(ctx, (void**)&_obj_55); mph_int _ret_56 = _obj_55->kind; mph_gc_pop_roots(ctx, 1); _ret_56; }) == mph_KIND_POINTER)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_57 = target; mph_gc_push_root(ctx, (void**)&_obj_57); mph_int _ret_58 = _obj_57->kind; mph_gc_pop_roots(ctx, 1); _ret_58; }) == mph_KIND_INTERFACE)) {
{
	return 1;
}
	}
	return 0;
}
	}
	return ({ mph_Type* _arg_59 = source; mph_gc_push_root(ctx, (void**)&_arg_59); mph_Type* _arg_60 = target; mph_gc_push_root(ctx, (void**)&_arg_60); mph_bool _ret_61 = mph_type_equals(ctx, NULL, _arg_59, _arg_60); mph_gc_pop_roots(ctx, 2); _ret_61; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_type_is_comparable(MorphContext* ctx, void* _env_void, mph_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	if ((({ mph_Type* _obj_62 = t; mph_gc_push_root(ctx, (void**)&_obj_62); mph_int _ret_63 = _obj_62->kind; mph_gc_pop_roots(ctx, 1); _ret_63; }) == mph_KIND_INT)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_64 = t; mph_gc_push_root(ctx, (void**)&_obj_64); mph_int _ret_65 = _obj_64->kind; mph_gc_pop_roots(ctx, 1); _ret_65; }) == mph_KIND_FLOAT)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_66 = t; mph_gc_push_root(ctx, (void**)&_obj_66); mph_int _ret_67 = _obj_66->kind; mph_gc_pop_roots(ctx, 1); _ret_67; }) == mph_KIND_STRING)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_68 = t; mph_gc_push_root(ctx, (void**)&_obj_68); mph_int _ret_69 = _obj_68->kind; mph_gc_pop_roots(ctx, 1); _ret_69; }) == mph_KIND_BOOL)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_70 = t; mph_gc_push_root(ctx, (void**)&_obj_70); mph_int _ret_71 = _obj_70->kind; mph_gc_pop_roots(ctx, 1); _ret_71; }) == mph_KIND_NULL)) {
{
	return 1;
}
	}
	if ((({ mph_Type* _obj_72 = t; mph_gc_push_root(ctx, (void**)&_obj_72); mph_int _ret_73 = _obj_72->kind; mph_gc_pop_roots(ctx, 1); _ret_73; }) == mph_KIND_USER_ERROR)) {
{
	return 1;
}
	}
	return 0;
	mph_gc_pop_roots(ctx, 1);
}

mph_TypeResult* mph_make_type_result(MorphContext* ctx, void* _env_void, mph_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_TypeResult* _t = (mph_TypeResult*)mph_alloc(ctx, sizeof(mph_TypeResult), &mph_ti_mph_TypeResult); mph_gc_push_root(ctx, (void**)&_t); _t->result = t; _t->error_msg = mph_string_new(ctx, "ok"); _t->has_error = 0; mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_TypeResult* mph_make_type_error(MorphContext* ctx, void* _env_void, MorphString* msg) {
	mph_gc_push_root(ctx, (void**)&msg);
	return ({ mph_TypeResult* _t = (mph_TypeResult*)mph_alloc(ctx, sizeof(mph_TypeResult), &mph_ti_mph_TypeResult); mph_gc_push_root(ctx, (void**)&_t); _t->error_msg = msg; _t->has_error = 1; _t->result = mph_error_type(ctx, NULL); mph_gc_pop_roots(ctx, 1); _t; });
	mph_gc_pop_roots(ctx, 1);
}

mph_TypeResult* mph_type_binary_op(MorphContext* ctx, void* _env_void, mph_Type* left, MorphString* op, mph_Type* right) {
	mph_gc_push_root(ctx, (void**)&left);
	mph_gc_push_root(ctx, (void**)&op);
	mph_gc_push_root(ctx, (void**)&right);
	if ((({ mph_Type* _obj_74 = left; mph_gc_push_root(ctx, (void**)&_obj_74); mph_int _ret_75 = _obj_74->kind; mph_gc_pop_roots(ctx, 1); _ret_75; }) == mph_KIND_UNKNOWN)) {
{
	return ({ mph_Type* _arg_76 = mph_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_76); mph_TypeResult* _ret_77 = mph_make_type_result(ctx, NULL, _arg_76); mph_gc_pop_roots(ctx, 1); _ret_77; });
}
	}
	if ((({ mph_Type* _obj_78 = right; mph_gc_push_root(ctx, (void**)&_obj_78); mph_int _ret_79 = _obj_78->kind; mph_gc_pop_roots(ctx, 1); _ret_79; }) == mph_KIND_UNKNOWN)) {
{
	return ({ mph_Type* _arg_80 = mph_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_80); mph_TypeResult* _ret_81 = mph_make_type_result(ctx, NULL, _arg_80); mph_gc_pop_roots(ctx, 1); _ret_81; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "+"))) {
{
	if ((({ mph_Type* _obj_82 = left; mph_gc_push_root(ctx, (void**)&_obj_82); mph_int _ret_83 = _obj_82->kind; mph_gc_pop_roots(ctx, 1); _ret_83; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_84 = right; mph_gc_push_root(ctx, (void**)&_obj_84); mph_int _ret_85 = _obj_84->kind; mph_gc_pop_roots(ctx, 1); _ret_85; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_86 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_86); mph_TypeResult* _ret_87 = mph_make_type_result(ctx, NULL, _arg_86); mph_gc_pop_roots(ctx, 1); _ret_87; });
}
	}
}
	}
	if ((({ mph_Type* _obj_88 = left; mph_gc_push_root(ctx, (void**)&_obj_88); mph_int _ret_89 = _obj_88->kind; mph_gc_pop_roots(ctx, 1); _ret_89; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_90 = right; mph_gc_push_root(ctx, (void**)&_obj_90); mph_int _ret_91 = _obj_90->kind; mph_gc_pop_roots(ctx, 1); _ret_91; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_92 = mph_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_92); mph_TypeResult* _ret_93 = mph_make_type_result(ctx, NULL, _arg_92); mph_gc_pop_roots(ctx, 1); _ret_93; });
}
	}
}
	}
	if ((({ mph_Type* _obj_94 = left; mph_gc_push_root(ctx, (void**)&_obj_94); mph_int _ret_95 = _obj_94->kind; mph_gc_pop_roots(ctx, 1); _ret_95; }) == mph_KIND_STRING)) {
{
	if ((({ mph_Type* _obj_96 = right; mph_gc_push_root(ctx, (void**)&_obj_96); mph_int _ret_97 = _obj_96->kind; mph_gc_pop_roots(ctx, 1); _ret_97; }) == mph_KIND_STRING)) {
{
	return ({ mph_Type* _arg_98 = mph_string_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_98); mph_TypeResult* _ret_99 = mph_make_type_result(ctx, NULL, _arg_98); mph_gc_pop_roots(ctx, 1); _ret_99; });
}
	}
}
	}
	return ({ MorphString* _arg_100 = mph_string_new(ctx, "+ tidak didukung untuk tipe ini"); mph_gc_push_root(ctx, (void**)&_arg_100); mph_TypeResult* _ret_101 = mph_make_type_error(ctx, NULL, _arg_100); mph_gc_pop_roots(ctx, 1); _ret_101; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_Type* _obj_102 = left; mph_gc_push_root(ctx, (void**)&_obj_102); mph_int _ret_103 = _obj_102->kind; mph_gc_pop_roots(ctx, 1); _ret_103; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_104 = right; mph_gc_push_root(ctx, (void**)&_obj_104); mph_int _ret_105 = _obj_104->kind; mph_gc_pop_roots(ctx, 1); _ret_105; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_106 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_106); mph_TypeResult* _ret_107 = mph_make_type_result(ctx, NULL, _arg_106); mph_gc_pop_roots(ctx, 1); _ret_107; });
}
	}
}
	}
	if ((({ mph_Type* _obj_108 = left; mph_gc_push_root(ctx, (void**)&_obj_108); mph_int _ret_109 = _obj_108->kind; mph_gc_pop_roots(ctx, 1); _ret_109; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_110 = right; mph_gc_push_root(ctx, (void**)&_obj_110); mph_int _ret_111 = _obj_110->kind; mph_gc_pop_roots(ctx, 1); _ret_111; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_112 = mph_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_112); mph_TypeResult* _ret_113 = mph_make_type_result(ctx, NULL, _arg_112); mph_gc_pop_roots(ctx, 1); _ret_113; });
}
	}
}
	}
	return ({ MorphString* _arg_114 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_114); mph_TypeResult* _ret_115 = mph_make_type_error(ctx, NULL, _arg_114); mph_gc_pop_roots(ctx, 1); _ret_115; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "*"))) {
{
	if ((({ mph_Type* _obj_116 = left; mph_gc_push_root(ctx, (void**)&_obj_116); mph_int _ret_117 = _obj_116->kind; mph_gc_pop_roots(ctx, 1); _ret_117; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_118 = right; mph_gc_push_root(ctx, (void**)&_obj_118); mph_int _ret_119 = _obj_118->kind; mph_gc_pop_roots(ctx, 1); _ret_119; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_120 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_120); mph_TypeResult* _ret_121 = mph_make_type_result(ctx, NULL, _arg_120); mph_gc_pop_roots(ctx, 1); _ret_121; });
}
	}
}
	}
	if ((({ mph_Type* _obj_122 = left; mph_gc_push_root(ctx, (void**)&_obj_122); mph_int _ret_123 = _obj_122->kind; mph_gc_pop_roots(ctx, 1); _ret_123; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_124 = right; mph_gc_push_root(ctx, (void**)&_obj_124); mph_int _ret_125 = _obj_124->kind; mph_gc_pop_roots(ctx, 1); _ret_125; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_126 = mph_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_126); mph_TypeResult* _ret_127 = mph_make_type_result(ctx, NULL, _arg_126); mph_gc_pop_roots(ctx, 1); _ret_127; });
}
	}
}
	}
	return ({ MorphString* _arg_128 = mph_string_new(ctx, "* memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_128); mph_TypeResult* _ret_129 = mph_make_type_error(ctx, NULL, _arg_128); mph_gc_pop_roots(ctx, 1); _ret_129; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "/"))) {
{
	if ((({ mph_Type* _obj_130 = left; mph_gc_push_root(ctx, (void**)&_obj_130); mph_int _ret_131 = _obj_130->kind; mph_gc_pop_roots(ctx, 1); _ret_131; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_132 = right; mph_gc_push_root(ctx, (void**)&_obj_132); mph_int _ret_133 = _obj_132->kind; mph_gc_pop_roots(ctx, 1); _ret_133; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_134 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_134); mph_TypeResult* _ret_135 = mph_make_type_result(ctx, NULL, _arg_134); mph_gc_pop_roots(ctx, 1); _ret_135; });
}
	}
}
	}
	if ((({ mph_Type* _obj_136 = left; mph_gc_push_root(ctx, (void**)&_obj_136); mph_int _ret_137 = _obj_136->kind; mph_gc_pop_roots(ctx, 1); _ret_137; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_138 = right; mph_gc_push_root(ctx, (void**)&_obj_138); mph_int _ret_139 = _obj_138->kind; mph_gc_pop_roots(ctx, 1); _ret_139; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_140 = mph_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_140); mph_TypeResult* _ret_141 = mph_make_type_result(ctx, NULL, _arg_140); mph_gc_pop_roots(ctx, 1); _ret_141; });
}
	}
}
	}
	return ({ MorphString* _arg_142 = mph_string_new(ctx, "/ memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_142); mph_TypeResult* _ret_143 = mph_make_type_error(ctx, NULL, _arg_142); mph_gc_pop_roots(ctx, 1); _ret_143; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "%"))) {
{
	if ((({ mph_Type* _obj_144 = left; mph_gc_push_root(ctx, (void**)&_obj_144); mph_int _ret_145 = _obj_144->kind; mph_gc_pop_roots(ctx, 1); _ret_145; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_146 = right; mph_gc_push_root(ctx, (void**)&_obj_146); mph_int _ret_147 = _obj_146->kind; mph_gc_pop_roots(ctx, 1); _ret_147; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_148 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_148); mph_TypeResult* _ret_149 = mph_make_type_result(ctx, NULL, _arg_148); mph_gc_pop_roots(ctx, 1); _ret_149; });
}
	}
}
	}
	return ({ MorphString* _arg_150 = mph_string_new(ctx, "% memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_150); mph_TypeResult* _ret_151 = mph_make_type_error(ctx, NULL, _arg_150); mph_gc_pop_roots(ctx, 1); _ret_151; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "=="))) {
{
	if (({ mph_Type* _arg_152 = left; mph_gc_push_root(ctx, (void**)&_arg_152); mph_Type* _arg_153 = right; mph_gc_push_root(ctx, (void**)&_arg_153); mph_bool _ret_154 = mph_type_equals(ctx, NULL, _arg_152, _arg_153); mph_gc_pop_roots(ctx, 2); _ret_154; })) {
{
	return ({ mph_Type* _arg_155 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_155); mph_TypeResult* _ret_156 = mph_make_type_result(ctx, NULL, _arg_155); mph_gc_pop_roots(ctx, 1); _ret_156; });
}
	}
	if ((({ mph_Type* _obj_157 = left; mph_gc_push_root(ctx, (void**)&_obj_157); mph_int _ret_158 = _obj_157->kind; mph_gc_pop_roots(ctx, 1); _ret_158; }) == mph_KIND_NULL)) {
{
	if (({ mph_Type* _arg_159 = left; mph_gc_push_root(ctx, (void**)&_arg_159); mph_Type* _arg_160 = right; mph_gc_push_root(ctx, (void**)&_arg_160); mph_bool _ret_161 = mph_type_assignable_to(ctx, NULL, _arg_159, _arg_160); mph_gc_pop_roots(ctx, 2); _ret_161; })) {
{
	return ({ mph_Type* _arg_162 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_162); mph_TypeResult* _ret_163 = mph_make_type_result(ctx, NULL, _arg_162); mph_gc_pop_roots(ctx, 1); _ret_163; });
}
	}
}
	}
	if ((({ mph_Type* _obj_164 = right; mph_gc_push_root(ctx, (void**)&_obj_164); mph_int _ret_165 = _obj_164->kind; mph_gc_pop_roots(ctx, 1); _ret_165; }) == mph_KIND_NULL)) {
{
	if (({ mph_Type* _arg_166 = right; mph_gc_push_root(ctx, (void**)&_arg_166); mph_Type* _arg_167 = left; mph_gc_push_root(ctx, (void**)&_arg_167); mph_bool _ret_168 = mph_type_assignable_to(ctx, NULL, _arg_166, _arg_167); mph_gc_pop_roots(ctx, 2); _ret_168; })) {
{
	return ({ mph_Type* _arg_169 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_169); mph_TypeResult* _ret_170 = mph_make_type_result(ctx, NULL, _arg_169); mph_gc_pop_roots(ctx, 1); _ret_170; });
}
	}
}
	}
	return ({ MorphString* _arg_171 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_171); mph_TypeResult* _ret_172 = mph_make_type_error(ctx, NULL, _arg_171); mph_gc_pop_roots(ctx, 1); _ret_172; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!="))) {
{
	if (({ mph_Type* _arg_173 = left; mph_gc_push_root(ctx, (void**)&_arg_173); mph_Type* _arg_174 = right; mph_gc_push_root(ctx, (void**)&_arg_174); mph_bool _ret_175 = mph_type_equals(ctx, NULL, _arg_173, _arg_174); mph_gc_pop_roots(ctx, 2); _ret_175; })) {
{
	return ({ mph_Type* _arg_176 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_176); mph_TypeResult* _ret_177 = mph_make_type_result(ctx, NULL, _arg_176); mph_gc_pop_roots(ctx, 1); _ret_177; });
}
	}
	if ((({ mph_Type* _obj_178 = left; mph_gc_push_root(ctx, (void**)&_obj_178); mph_int _ret_179 = _obj_178->kind; mph_gc_pop_roots(ctx, 1); _ret_179; }) == mph_KIND_NULL)) {
{
	if (({ mph_Type* _arg_180 = left; mph_gc_push_root(ctx, (void**)&_arg_180); mph_Type* _arg_181 = right; mph_gc_push_root(ctx, (void**)&_arg_181); mph_bool _ret_182 = mph_type_assignable_to(ctx, NULL, _arg_180, _arg_181); mph_gc_pop_roots(ctx, 2); _ret_182; })) {
{
	return ({ mph_Type* _arg_183 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_183); mph_TypeResult* _ret_184 = mph_make_type_result(ctx, NULL, _arg_183); mph_gc_pop_roots(ctx, 1); _ret_184; });
}
	}
}
	}
	if ((({ mph_Type* _obj_185 = right; mph_gc_push_root(ctx, (void**)&_obj_185); mph_int _ret_186 = _obj_185->kind; mph_gc_pop_roots(ctx, 1); _ret_186; }) == mph_KIND_NULL)) {
{
	if (({ mph_Type* _arg_187 = right; mph_gc_push_root(ctx, (void**)&_arg_187); mph_Type* _arg_188 = left; mph_gc_push_root(ctx, (void**)&_arg_188); mph_bool _ret_189 = mph_type_assignable_to(ctx, NULL, _arg_187, _arg_188); mph_gc_pop_roots(ctx, 2); _ret_189; })) {
{
	return ({ mph_Type* _arg_190 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_190); mph_TypeResult* _ret_191 = mph_make_type_result(ctx, NULL, _arg_190); mph_gc_pop_roots(ctx, 1); _ret_191; });
}
	}
}
	}
	return ({ MorphString* _arg_192 = mph_string_new(ctx, "tidak dapat membandingkan tipe berbeda"); mph_gc_push_root(ctx, (void**)&_arg_192); mph_TypeResult* _ret_193 = mph_make_type_error(ctx, NULL, _arg_192); mph_gc_pop_roots(ctx, 1); _ret_193; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&&"))) {
{
	if ((({ mph_Type* _obj_194 = left; mph_gc_push_root(ctx, (void**)&_obj_194); mph_int _ret_195 = _obj_194->kind; mph_gc_pop_roots(ctx, 1); _ret_195; }) == mph_KIND_BOOL)) {
{
	if ((({ mph_Type* _obj_196 = right; mph_gc_push_root(ctx, (void**)&_obj_196); mph_int _ret_197 = _obj_196->kind; mph_gc_pop_roots(ctx, 1); _ret_197; }) == mph_KIND_BOOL)) {
{
	return ({ mph_Type* _arg_198 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_198); mph_TypeResult* _ret_199 = mph_make_type_result(ctx, NULL, _arg_198); mph_gc_pop_roots(ctx, 1); _ret_199; });
}
	}
}
	}
	return ({ MorphString* _arg_200 = mph_string_new(ctx, "&& memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_200); mph_TypeResult* _ret_201 = mph_make_type_error(ctx, NULL, _arg_200); mph_gc_pop_roots(ctx, 1); _ret_201; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "||"))) {
{
	if ((({ mph_Type* _obj_202 = left; mph_gc_push_root(ctx, (void**)&_obj_202); mph_int _ret_203 = _obj_202->kind; mph_gc_pop_roots(ctx, 1); _ret_203; }) == mph_KIND_BOOL)) {
{
	if ((({ mph_Type* _obj_204 = right; mph_gc_push_root(ctx, (void**)&_obj_204); mph_int _ret_205 = _obj_204->kind; mph_gc_pop_roots(ctx, 1); _ret_205; }) == mph_KIND_BOOL)) {
{
	return ({ mph_Type* _arg_206 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_206); mph_TypeResult* _ret_207 = mph_make_type_result(ctx, NULL, _arg_206); mph_gc_pop_roots(ctx, 1); _ret_207; });
}
	}
}
	}
	return ({ MorphString* _arg_208 = mph_string_new(ctx, "|| memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_208); mph_TypeResult* _ret_209 = mph_make_type_error(ctx, NULL, _arg_208); mph_gc_pop_roots(ctx, 1); _ret_209; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "dan"))) {
{
	if ((({ mph_Type* _obj_210 = left; mph_gc_push_root(ctx, (void**)&_obj_210); mph_int _ret_211 = _obj_210->kind; mph_gc_pop_roots(ctx, 1); _ret_211; }) == mph_KIND_BOOL)) {
{
	if ((({ mph_Type* _obj_212 = right; mph_gc_push_root(ctx, (void**)&_obj_212); mph_int _ret_213 = _obj_212->kind; mph_gc_pop_roots(ctx, 1); _ret_213; }) == mph_KIND_BOOL)) {
{
	return ({ mph_Type* _arg_214 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_214); mph_TypeResult* _ret_215 = mph_make_type_result(ctx, NULL, _arg_214); mph_gc_pop_roots(ctx, 1); _ret_215; });
}
	}
}
	}
	return ({ MorphString* _arg_216 = mph_string_new(ctx, "dan memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_216); mph_TypeResult* _ret_217 = mph_make_type_error(ctx, NULL, _arg_216); mph_gc_pop_roots(ctx, 1); _ret_217; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "atau"))) {
{
	if ((({ mph_Type* _obj_218 = left; mph_gc_push_root(ctx, (void**)&_obj_218); mph_int _ret_219 = _obj_218->kind; mph_gc_pop_roots(ctx, 1); _ret_219; }) == mph_KIND_BOOL)) {
{
	if ((({ mph_Type* _obj_220 = right; mph_gc_push_root(ctx, (void**)&_obj_220); mph_int _ret_221 = _obj_220->kind; mph_gc_pop_roots(ctx, 1); _ret_221; }) == mph_KIND_BOOL)) {
{
	return ({ mph_Type* _arg_222 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_222); mph_TypeResult* _ret_223 = mph_make_type_result(ctx, NULL, _arg_222); mph_gc_pop_roots(ctx, 1); _ret_223; });
}
	}
}
	}
	return ({ MorphString* _arg_224 = mph_string_new(ctx, "atau memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_224); mph_TypeResult* _ret_225 = mph_make_type_error(ctx, NULL, _arg_224); mph_gc_pop_roots(ctx, 1); _ret_225; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<"))) {
{
	if ((({ mph_Type* _obj_226 = left; mph_gc_push_root(ctx, (void**)&_obj_226); mph_int _ret_227 = _obj_226->kind; mph_gc_pop_roots(ctx, 1); _ret_227; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_228 = right; mph_gc_push_root(ctx, (void**)&_obj_228); mph_int _ret_229 = _obj_228->kind; mph_gc_pop_roots(ctx, 1); _ret_229; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_230 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_230); mph_TypeResult* _ret_231 = mph_make_type_result(ctx, NULL, _arg_230); mph_gc_pop_roots(ctx, 1); _ret_231; });
}
	}
}
	}
	if ((({ mph_Type* _obj_232 = left; mph_gc_push_root(ctx, (void**)&_obj_232); mph_int _ret_233 = _obj_232->kind; mph_gc_pop_roots(ctx, 1); _ret_233; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_234 = right; mph_gc_push_root(ctx, (void**)&_obj_234); mph_int _ret_235 = _obj_234->kind; mph_gc_pop_roots(ctx, 1); _ret_235; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_236 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_236); mph_TypeResult* _ret_237 = mph_make_type_result(ctx, NULL, _arg_236); mph_gc_pop_roots(ctx, 1); _ret_237; });
}
	}
}
	}
	return ({ MorphString* _arg_238 = mph_string_new(ctx, "< memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_238); mph_TypeResult* _ret_239 = mph_make_type_error(ctx, NULL, _arg_238); mph_gc_pop_roots(ctx, 1); _ret_239; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">"))) {
{
	if ((({ mph_Type* _obj_240 = left; mph_gc_push_root(ctx, (void**)&_obj_240); mph_int _ret_241 = _obj_240->kind; mph_gc_pop_roots(ctx, 1); _ret_241; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_242 = right; mph_gc_push_root(ctx, (void**)&_obj_242); mph_int _ret_243 = _obj_242->kind; mph_gc_pop_roots(ctx, 1); _ret_243; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_244 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_244); mph_TypeResult* _ret_245 = mph_make_type_result(ctx, NULL, _arg_244); mph_gc_pop_roots(ctx, 1); _ret_245; });
}
	}
}
	}
	if ((({ mph_Type* _obj_246 = left; mph_gc_push_root(ctx, (void**)&_obj_246); mph_int _ret_247 = _obj_246->kind; mph_gc_pop_roots(ctx, 1); _ret_247; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_248 = right; mph_gc_push_root(ctx, (void**)&_obj_248); mph_int _ret_249 = _obj_248->kind; mph_gc_pop_roots(ctx, 1); _ret_249; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_250 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_250); mph_TypeResult* _ret_251 = mph_make_type_result(ctx, NULL, _arg_250); mph_gc_pop_roots(ctx, 1); _ret_251; });
}
	}
}
	}
	return ({ MorphString* _arg_252 = mph_string_new(ctx, "> memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_252); mph_TypeResult* _ret_253 = mph_make_type_error(ctx, NULL, _arg_252); mph_gc_pop_roots(ctx, 1); _ret_253; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<="))) {
{
	if ((({ mph_Type* _obj_254 = left; mph_gc_push_root(ctx, (void**)&_obj_254); mph_int _ret_255 = _obj_254->kind; mph_gc_pop_roots(ctx, 1); _ret_255; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_256 = right; mph_gc_push_root(ctx, (void**)&_obj_256); mph_int _ret_257 = _obj_256->kind; mph_gc_pop_roots(ctx, 1); _ret_257; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_258 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_258); mph_TypeResult* _ret_259 = mph_make_type_result(ctx, NULL, _arg_258); mph_gc_pop_roots(ctx, 1); _ret_259; });
}
	}
}
	}
	if ((({ mph_Type* _obj_260 = left; mph_gc_push_root(ctx, (void**)&_obj_260); mph_int _ret_261 = _obj_260->kind; mph_gc_pop_roots(ctx, 1); _ret_261; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_262 = right; mph_gc_push_root(ctx, (void**)&_obj_262); mph_int _ret_263 = _obj_262->kind; mph_gc_pop_roots(ctx, 1); _ret_263; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_264 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_264); mph_TypeResult* _ret_265 = mph_make_type_result(ctx, NULL, _arg_264); mph_gc_pop_roots(ctx, 1); _ret_265; });
}
	}
}
	}
	return ({ MorphString* _arg_266 = mph_string_new(ctx, "<= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_266); mph_TypeResult* _ret_267 = mph_make_type_error(ctx, NULL, _arg_266); mph_gc_pop_roots(ctx, 1); _ret_267; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">="))) {
{
	if ((({ mph_Type* _obj_268 = left; mph_gc_push_root(ctx, (void**)&_obj_268); mph_int _ret_269 = _obj_268->kind; mph_gc_pop_roots(ctx, 1); _ret_269; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_270 = right; mph_gc_push_root(ctx, (void**)&_obj_270); mph_int _ret_271 = _obj_270->kind; mph_gc_pop_roots(ctx, 1); _ret_271; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_272 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_272); mph_TypeResult* _ret_273 = mph_make_type_result(ctx, NULL, _arg_272); mph_gc_pop_roots(ctx, 1); _ret_273; });
}
	}
}
	}
	if ((({ mph_Type* _obj_274 = left; mph_gc_push_root(ctx, (void**)&_obj_274); mph_int _ret_275 = _obj_274->kind; mph_gc_pop_roots(ctx, 1); _ret_275; }) == mph_KIND_FLOAT)) {
{
	if ((({ mph_Type* _obj_276 = right; mph_gc_push_root(ctx, (void**)&_obj_276); mph_int _ret_277 = _obj_276->kind; mph_gc_pop_roots(ctx, 1); _ret_277; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_278 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_278); mph_TypeResult* _ret_279 = mph_make_type_result(ctx, NULL, _arg_278); mph_gc_pop_roots(ctx, 1); _ret_279; });
}
	}
}
	}
	return ({ MorphString* _arg_280 = mph_string_new(ctx, ">= memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_280); mph_TypeResult* _ret_281 = mph_make_type_error(ctx, NULL, _arg_280); mph_gc_pop_roots(ctx, 1); _ret_281; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "&"))) {
{
	if ((({ mph_Type* _obj_282 = left; mph_gc_push_root(ctx, (void**)&_obj_282); mph_int _ret_283 = _obj_282->kind; mph_gc_pop_roots(ctx, 1); _ret_283; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_284 = right; mph_gc_push_root(ctx, (void**)&_obj_284); mph_int _ret_285 = _obj_284->kind; mph_gc_pop_roots(ctx, 1); _ret_285; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_286 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_286); mph_TypeResult* _ret_287 = mph_make_type_result(ctx, NULL, _arg_286); mph_gc_pop_roots(ctx, 1); _ret_287; });
}
	}
}
	}
	return ({ MorphString* _arg_288 = mph_string_new(ctx, "& memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_288); mph_TypeResult* _ret_289 = mph_make_type_error(ctx, NULL, _arg_288); mph_gc_pop_roots(ctx, 1); _ret_289; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "|"))) {
{
	if ((({ mph_Type* _obj_290 = left; mph_gc_push_root(ctx, (void**)&_obj_290); mph_int _ret_291 = _obj_290->kind; mph_gc_pop_roots(ctx, 1); _ret_291; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_292 = right; mph_gc_push_root(ctx, (void**)&_obj_292); mph_int _ret_293 = _obj_292->kind; mph_gc_pop_roots(ctx, 1); _ret_293; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_294 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_294); mph_TypeResult* _ret_295 = mph_make_type_result(ctx, NULL, _arg_294); mph_gc_pop_roots(ctx, 1); _ret_295; });
}
	}
}
	}
	return ({ MorphString* _arg_296 = mph_string_new(ctx, "| memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_296); mph_TypeResult* _ret_297 = mph_make_type_error(ctx, NULL, _arg_296); mph_gc_pop_roots(ctx, 1); _ret_297; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "^"))) {
{
	if ((({ mph_Type* _obj_298 = left; mph_gc_push_root(ctx, (void**)&_obj_298); mph_int _ret_299 = _obj_298->kind; mph_gc_pop_roots(ctx, 1); _ret_299; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_300 = right; mph_gc_push_root(ctx, (void**)&_obj_300); mph_int _ret_301 = _obj_300->kind; mph_gc_pop_roots(ctx, 1); _ret_301; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_302 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_302); mph_TypeResult* _ret_303 = mph_make_type_result(ctx, NULL, _arg_302); mph_gc_pop_roots(ctx, 1); _ret_303; });
}
	}
}
	}
	return ({ MorphString* _arg_304 = mph_string_new(ctx, "^ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_304); mph_TypeResult* _ret_305 = mph_make_type_error(ctx, NULL, _arg_304); mph_gc_pop_roots(ctx, 1); _ret_305; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "<<"))) {
{
	if ((({ mph_Type* _obj_306 = left; mph_gc_push_root(ctx, (void**)&_obj_306); mph_int _ret_307 = _obj_306->kind; mph_gc_pop_roots(ctx, 1); _ret_307; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_308 = right; mph_gc_push_root(ctx, (void**)&_obj_308); mph_int _ret_309 = _obj_308->kind; mph_gc_pop_roots(ctx, 1); _ret_309; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_310 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_310); mph_TypeResult* _ret_311 = mph_make_type_result(ctx, NULL, _arg_310); mph_gc_pop_roots(ctx, 1); _ret_311; });
}
	}
}
	}
	return ({ MorphString* _arg_312 = mph_string_new(ctx, "<< memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_312); mph_TypeResult* _ret_313 = mph_make_type_error(ctx, NULL, _arg_312); mph_gc_pop_roots(ctx, 1); _ret_313; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, ">>"))) {
{
	if ((({ mph_Type* _obj_314 = left; mph_gc_push_root(ctx, (void**)&_obj_314); mph_int _ret_315 = _obj_314->kind; mph_gc_pop_roots(ctx, 1); _ret_315; }) == mph_KIND_INT)) {
{
	if ((({ mph_Type* _obj_316 = right; mph_gc_push_root(ctx, (void**)&_obj_316); mph_int _ret_317 = _obj_316->kind; mph_gc_pop_roots(ctx, 1); _ret_317; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_318 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_318); mph_TypeResult* _ret_319 = mph_make_type_result(ctx, NULL, _arg_318); mph_gc_pop_roots(ctx, 1); _ret_319; });
}
	}
}
	}
	return ({ MorphString* _arg_320 = mph_string_new(ctx, ">> memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_320); mph_TypeResult* _ret_321 = mph_make_type_error(ctx, NULL, _arg_320); mph_gc_pop_roots(ctx, 1); _ret_321; });
}
	}
	return ({ MorphString* _arg_322 = mph_string_new(ctx, "operator tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_322); mph_TypeResult* _ret_323 = mph_make_type_error(ctx, NULL, _arg_322); mph_gc_pop_roots(ctx, 1); _ret_323; });
	mph_gc_pop_roots(ctx, 3);
}

mph_TypeResult* mph_type_prefix_op(MorphContext* ctx, void* _env_void, mph_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	if ((({ mph_Type* _obj_324 = t; mph_gc_push_root(ctx, (void**)&_obj_324); mph_int _ret_325 = _obj_324->kind; mph_gc_pop_roots(ctx, 1); _ret_325; }) == mph_KIND_UNKNOWN)) {
{
	return ({ mph_Type* _arg_326 = mph_unknown_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_326); mph_TypeResult* _ret_327 = mph_make_type_result(ctx, NULL, _arg_326); mph_gc_pop_roots(ctx, 1); _ret_327; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "!"))) {
{
	if ((({ mph_Type* _obj_328 = t; mph_gc_push_root(ctx, (void**)&_obj_328); mph_int _ret_329 = _obj_328->kind; mph_gc_pop_roots(ctx, 1); _ret_329; }) == mph_KIND_BOOL)) {
{
	return ({ mph_Type* _arg_330 = mph_bool_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_330); mph_TypeResult* _ret_331 = mph_make_type_result(ctx, NULL, _arg_330); mph_gc_pop_roots(ctx, 1); _ret_331; });
}
	}
	return ({ MorphString* _arg_332 = mph_string_new(ctx, "! memerlukan bool"); mph_gc_push_root(ctx, (void**)&_arg_332); mph_TypeResult* _ret_333 = mph_make_type_error(ctx, NULL, _arg_332); mph_gc_pop_roots(ctx, 1); _ret_333; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "-"))) {
{
	if ((({ mph_Type* _obj_334 = t; mph_gc_push_root(ctx, (void**)&_obj_334); mph_int _ret_335 = _obj_334->kind; mph_gc_pop_roots(ctx, 1); _ret_335; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_336 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_336); mph_TypeResult* _ret_337 = mph_make_type_result(ctx, NULL, _arg_336); mph_gc_pop_roots(ctx, 1); _ret_337; });
}
	}
	if ((({ mph_Type* _obj_338 = t; mph_gc_push_root(ctx, (void**)&_obj_338); mph_int _ret_339 = _obj_338->kind; mph_gc_pop_roots(ctx, 1); _ret_339; }) == mph_KIND_FLOAT)) {
{
	return ({ mph_Type* _arg_340 = mph_float_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_340); mph_TypeResult* _ret_341 = mph_make_type_result(ctx, NULL, _arg_340); mph_gc_pop_roots(ctx, 1); _ret_341; });
}
	}
	return ({ MorphString* _arg_342 = mph_string_new(ctx, "- memerlukan numeric"); mph_gc_push_root(ctx, (void**)&_arg_342); mph_TypeResult* _ret_343 = mph_make_type_error(ctx, NULL, _arg_342); mph_gc_pop_roots(ctx, 1); _ret_343; });
}
	}
	if (mph_string_eq(ctx, op, mph_string_new(ctx, "~"))) {
{
	if ((({ mph_Type* _obj_344 = t; mph_gc_push_root(ctx, (void**)&_obj_344); mph_int _ret_345 = _obj_344->kind; mph_gc_pop_roots(ctx, 1); _ret_345; }) == mph_KIND_INT)) {
{
	return ({ mph_Type* _arg_346 = mph_int_type(ctx, NULL); mph_gc_push_root(ctx, (void**)&_arg_346); mph_TypeResult* _ret_347 = mph_make_type_result(ctx, NULL, _arg_346); mph_gc_pop_roots(ctx, 1); _ret_347; });
}
	}
	return ({ MorphString* _arg_348 = mph_string_new(ctx, "~ memerlukan int"); mph_gc_push_root(ctx, (void**)&_arg_348); mph_TypeResult* _ret_349 = mph_make_type_error(ctx, NULL, _arg_348); mph_gc_pop_roots(ctx, 1); _ret_349; });
}
	}
	return ({ MorphString* _arg_350 = mph_string_new(ctx, "prefix tidak dikenal"); mph_gc_push_root(ctx, (void**)&_arg_350); mph_TypeResult* _ret_351 = mph_make_type_error(ctx, NULL, _arg_350); mph_gc_pop_roots(ctx, 1); _ret_351; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_kind_to_string(MorphContext* ctx, void* _env_void, mph_int k) {
	if ((k == mph_KIND_INT)) {
{
	return mph_string_new(ctx, "int");
}
	}
	if ((k == mph_KIND_FLOAT)) {
{
	return mph_string_new(ctx, "float");
}
	}
	if ((k == mph_KIND_STRING)) {
{
	return mph_string_new(ctx, "string");
}
	}
	if ((k == mph_KIND_BOOL)) {
{
	return mph_string_new(ctx, "bool");
}
	}
	if ((k == mph_KIND_VOID)) {
{
	return mph_string_new(ctx, "void");
}
	}
	if ((k == mph_KIND_FUNCTION)) {
{
	return mph_string_new(ctx, "function");
}
	}
	if ((k == mph_KIND_STRUCT)) {
{
	return mph_string_new(ctx, "struct");
}
	}
	if ((k == mph_KIND_INTERFACE)) {
{
	return mph_string_new(ctx, "interface");
}
	}
	if ((k == mph_KIND_ARRAY)) {
{
	return mph_string_new(ctx, "array");
}
	}
	if ((k == mph_KIND_MAP)) {
{
	return mph_string_new(ctx, "map");
}
	}
	if ((k == mph_KIND_POINTER)) {
{
	return mph_string_new(ctx, "pointer");
}
	}
	if ((k == mph_KIND_MULTI)) {
{
	return mph_string_new(ctx, "multi");
}
	}
	if ((k == mph_KIND_UNKNOWN)) {
{
	return mph_string_new(ctx, "unknown");
}
	}
	if ((k == mph_KIND_ERROR)) {
{
	return mph_string_new(ctx, "error");
}
	}
	if ((k == mph_KIND_NULL)) {
{
	return mph_string_new(ctx, "null");
}
	}
	if ((k == mph_KIND_USER_ERROR)) {
{
	return mph_string_new(ctx, "user_error");
}
	}
	if ((k == mph_KIND_MODULE)) {
{
	return mph_string_new(ctx, "module");
}
	}
	if ((k == mph_KIND_CHANNEL)) {
{
	return mph_string_new(ctx, "channel");
}
	}
	return mph_string_new(ctx, "unknown");
}

mph_Type* mph_IntType(MorphContext* ctx, void* _env_void) {
	return mph_int_type(ctx, NULL);
}

mph_Type* mph_FloatType(MorphContext* ctx, void* _env_void) {
	return mph_float_type(ctx, NULL);
}

mph_Type* mph_StringType(MorphContext* ctx, void* _env_void) {
	return mph_string_type(ctx, NULL);
}

mph_Type* mph_BoolType(MorphContext* ctx, void* _env_void) {
	return mph_bool_type(ctx, NULL);
}

mph_Type* mph_VoidType(MorphContext* ctx, void* _env_void) {
	return mph_void_type(ctx, NULL);
}

mph_Type* mph_NullType(MorphContext* ctx, void* _env_void) {
	return mph_null_type(ctx, NULL);
}

mph_Type* mph_UnknownType(MorphContext* ctx, void* _env_void) {
	return mph_unknown_type(ctx, NULL);
}

mph_Type* mph_ErrorType(MorphContext* ctx, void* _env_void) {
	return mph_error_type(ctx, NULL);
}

mph_Type* mph_UserErrorType(MorphContext* ctx, void* _env_void) {
	return mph_user_error_type(ctx, NULL);
}

mph_Type* mph_ChannelType(MorphContext* ctx, void* _env_void) {
	return mph_channel_type(ctx, NULL);
}

mph_Type* mph_ArrayType(MorphContext* ctx, void* _env_void) {
	return mph_array_type(ctx, NULL);
}

mph_Type* mph_MapType(MorphContext* ctx, void* _env_void) {
	return mph_map_type(ctx, NULL);
}

mph_Type* mph_StructType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_352 = n; mph_gc_push_root(ctx, (void**)&_arg_352); mph_Type* _ret_353 = mph_struct_type(ctx, NULL, _arg_352); mph_gc_pop_roots(ctx, 1); _ret_353; });
	mph_gc_pop_roots(ctx, 1);
}

mph_Type* mph_InterfaceType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_354 = n; mph_gc_push_root(ctx, (void**)&_arg_354); mph_Type* _ret_355 = mph_interface_type(ctx, NULL, _arg_354); mph_gc_pop_roots(ctx, 1); _ret_355; });
	mph_gc_pop_roots(ctx, 1);
}

mph_Type* mph_FunctionType(MorphContext* ctx, void* _env_void) {
	return mph_function_type(ctx, NULL);
}

mph_Type* mph_PointerType(MorphContext* ctx, void* _env_void) {
	return mph_pointer_type(ctx, NULL);
}

mph_Type* mph_MultiType(MorphContext* ctx, void* _env_void) {
	return mph_multi_type(ctx, NULL);
}

mph_Type* mph_ModuleType(MorphContext* ctx, void* _env_void, MorphString* n) {
	mph_gc_push_root(ctx, (void**)&n);
	return ({ MorphString* _arg_356 = n; mph_gc_push_root(ctx, (void**)&_arg_356); mph_Type* _ret_357 = mph_module_type(ctx, NULL, _arg_356); mph_gc_pop_roots(ctx, 1); _ret_357; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_TypeEquals(MorphContext* ctx, void* _env_void, mph_Type* t1, mph_Type* t2) {
	mph_gc_push_root(ctx, (void**)&t1);
	mph_gc_push_root(ctx, (void**)&t2);
	return ({ mph_Type* _arg_358 = t1; mph_gc_push_root(ctx, (void**)&_arg_358); mph_Type* _arg_359 = t2; mph_gc_push_root(ctx, (void**)&_arg_359); mph_bool _ret_360 = mph_type_equals(ctx, NULL, _arg_358, _arg_359); mph_gc_pop_roots(ctx, 2); _ret_360; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_TypeAssignableTo(MorphContext* ctx, void* _env_void, mph_Type* source, mph_Type* target) {
	mph_gc_push_root(ctx, (void**)&source);
	mph_gc_push_root(ctx, (void**)&target);
	return ({ mph_Type* _arg_361 = source; mph_gc_push_root(ctx, (void**)&_arg_361); mph_Type* _arg_362 = target; mph_gc_push_root(ctx, (void**)&_arg_362); mph_bool _ret_363 = mph_type_assignable_to(ctx, NULL, _arg_361, _arg_362); mph_gc_pop_roots(ctx, 2); _ret_363; });
	mph_gc_pop_roots(ctx, 2);
}

mph_bool mph_TypeIsComparable(MorphContext* ctx, void* _env_void, mph_Type* t) {
	mph_gc_push_root(ctx, (void**)&t);
	return ({ mph_Type* _arg_364 = t; mph_gc_push_root(ctx, (void**)&_arg_364); mph_bool _ret_365 = mph_type_is_comparable(ctx, NULL, _arg_364); mph_gc_pop_roots(ctx, 1); _ret_365; });
	mph_gc_pop_roots(ctx, 1);
}

mph_TypeResult* mph_TypeBinaryOp(MorphContext* ctx, void* _env_void, mph_Type* left, MorphString* op, mph_Type* right) {
	mph_gc_push_root(ctx, (void**)&left);
	mph_gc_push_root(ctx, (void**)&op);
	mph_gc_push_root(ctx, (void**)&right);
	return ({ mph_Type* _arg_366 = left; mph_gc_push_root(ctx, (void**)&_arg_366); MorphString* _arg_367 = op; mph_gc_push_root(ctx, (void**)&_arg_367); mph_Type* _arg_368 = right; mph_gc_push_root(ctx, (void**)&_arg_368); mph_TypeResult* _ret_369 = mph_type_binary_op(ctx, NULL, _arg_366, _arg_367, _arg_368); mph_gc_pop_roots(ctx, 3); _ret_369; });
	mph_gc_pop_roots(ctx, 3);
}

mph_TypeResult* mph_TypePrefixOp(MorphContext* ctx, void* _env_void, mph_Type* t, MorphString* op) {
	mph_gc_push_root(ctx, (void**)&t);
	mph_gc_push_root(ctx, (void**)&op);
	return ({ mph_Type* _arg_370 = t; mph_gc_push_root(ctx, (void**)&_arg_370); MorphString* _arg_371 = op; mph_gc_push_root(ctx, (void**)&_arg_371); mph_TypeResult* _ret_372 = mph_type_prefix_op(ctx, NULL, _arg_370, _arg_371); mph_gc_pop_roots(ctx, 2); _ret_372; });
	mph_gc_pop_roots(ctx, 2);
}

MorphString* mph_KindToString(MorphContext* ctx, void* _env_void, mph_int k) {
	return mph_kind_to_string(ctx, NULL, k);
}

void mph_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â   N1 Type System - Full Test Suite   â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n\n"));
	mph_int passed = 0;
	mph_int failed = 0;
	mph_native_print(ctx, mph_string_new(ctx, "[Test 1] Type Creation\n"));
	mph_Type* t_int = mph_int_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_int);
	mph_Type* t_float = mph_float_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_float);
	mph_Type* t_string = mph_string_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_string);
	mph_Type* t_bool = mph_bool_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_bool);
	if ((({ mph_Type* _obj_373 = t_int; mph_gc_push_root(ctx, (void**)&_obj_373); mph_int _ret_374 = _obj_373->kind; mph_gc_pop_roots(ctx, 1); _ret_374; }) == mph_KIND_INT)) {
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
	if (({ mph_Type* _arg_375 = t_int; mph_gc_push_root(ctx, (void**)&_arg_375); mph_Type* _arg_376 = t_int; mph_gc_push_root(ctx, (void**)&_arg_376); mph_bool _ret_377 = mph_type_equals(ctx, NULL, _arg_375, _arg_376); mph_gc_pop_roots(ctx, 2); _ret_377; })) {
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
	if (({ mph_Type* _arg_378 = t_int; mph_gc_push_root(ctx, (void**)&_arg_378); mph_Type* _arg_379 = t_float; mph_gc_push_root(ctx, (void**)&_arg_379); mph_bool _ret_380 = mph_type_equals(ctx, NULL, _arg_378, _arg_379); mph_gc_pop_roots(ctx, 2); _ret_380; })) {
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
	mph_Type* t_null = mph_null_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_null);
	mph_Type* t_array = mph_array_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_array);
	mph_Type* t_map = mph_map_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_map);
	if (({ mph_Type* _arg_381 = t_null; mph_gc_push_root(ctx, (void**)&_arg_381); mph_Type* _arg_382 = t_array; mph_gc_push_root(ctx, (void**)&_arg_382); mph_bool _ret_383 = mph_type_assignable_to(ctx, NULL, _arg_381, _arg_382); mph_gc_pop_roots(ctx, 2); _ret_383; })) {
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
	if (({ mph_Type* _arg_384 = t_null; mph_gc_push_root(ctx, (void**)&_arg_384); mph_Type* _arg_385 = t_map; mph_gc_push_root(ctx, (void**)&_arg_385); mph_bool _ret_386 = mph_type_assignable_to(ctx, NULL, _arg_384, _arg_385); mph_gc_pop_roots(ctx, 2); _ret_386; })) {
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
	if (({ mph_Type* _arg_387 = t_null; mph_gc_push_root(ctx, (void**)&_arg_387); mph_Type* _arg_388 = t_int; mph_gc_push_root(ctx, (void**)&_arg_388); mph_bool _ret_389 = mph_type_assignable_to(ctx, NULL, _arg_387, _arg_388); mph_gc_pop_roots(ctx, 2); _ret_389; })) {
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
	if (({ mph_Type* _arg_390 = t_int; mph_gc_push_root(ctx, (void**)&_arg_390); mph_bool _ret_391 = mph_type_is_comparable(ctx, NULL, _arg_390); mph_gc_pop_roots(ctx, 1); _ret_391; })) {
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
	mph_Type* t_void = mph_void_type(ctx, NULL);
	mph_gc_push_root(ctx, (void**)&t_void);
	if (({ mph_Type* _arg_392 = t_void; mph_gc_push_root(ctx, (void**)&_arg_392); mph_bool _ret_393 = mph_type_is_comparable(ctx, NULL, _arg_392); mph_gc_pop_roots(ctx, 1); _ret_393; })) {
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
	mph_TypeResult* r1 = ({ mph_Type* _arg_394 = t_int; mph_gc_push_root(ctx, (void**)&_arg_394); MorphString* _arg_395 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_395); mph_Type* _arg_396 = t_int; mph_gc_push_root(ctx, (void**)&_arg_396); mph_TypeResult* _ret_397 = mph_type_binary_op(ctx, NULL, _arg_394, _arg_395, _arg_396); mph_gc_pop_roots(ctx, 3); _ret_397; });
	mph_gc_push_root(ctx, (void**)&r1);
	if (({ mph_TypeResult* _obj_398 = r1; mph_gc_push_root(ctx, (void**)&_obj_398); mph_bool _ret_399 = _obj_398->has_error; mph_gc_pop_roots(ctx, 1); _ret_399; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int + int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_402 = ({ mph_TypeResult* _obj_400 = r1; mph_gc_push_root(ctx, (void**)&_obj_400); mph_Type* _ret_401 = _obj_400->result; mph_gc_pop_roots(ctx, 1); _ret_401; }); mph_gc_push_root(ctx, (void**)&_obj_402); mph_int _ret_403 = _obj_402->kind; mph_gc_pop_roots(ctx, 1); _ret_403; }) == mph_KIND_INT)) {
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
	mph_TypeResult* r2 = ({ mph_Type* _arg_404 = t_string; mph_gc_push_root(ctx, (void**)&_arg_404); MorphString* _arg_405 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_405); mph_Type* _arg_406 = t_string; mph_gc_push_root(ctx, (void**)&_arg_406); mph_TypeResult* _ret_407 = mph_type_binary_op(ctx, NULL, _arg_404, _arg_405, _arg_406); mph_gc_pop_roots(ctx, 3); _ret_407; });
	mph_gc_push_root(ctx, (void**)&r2);
	if (({ mph_TypeResult* _obj_408 = r2; mph_gc_push_root(ctx, (void**)&_obj_408); mph_bool _ret_409 = _obj_408->has_error; mph_gc_pop_roots(ctx, 1); _ret_409; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â string + string FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_412 = ({ mph_TypeResult* _obj_410 = r2; mph_gc_push_root(ctx, (void**)&_obj_410); mph_Type* _ret_411 = _obj_410->result; mph_gc_pop_roots(ctx, 1); _ret_411; }); mph_gc_push_root(ctx, (void**)&_obj_412); mph_int _ret_413 = _obj_412->kind; mph_gc_pop_roots(ctx, 1); _ret_413; }) == mph_KIND_STRING)) {
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
	mph_TypeResult* r3 = ({ mph_Type* _arg_414 = t_float; mph_gc_push_root(ctx, (void**)&_arg_414); MorphString* _arg_415 = mph_string_new(ctx, "*"); mph_gc_push_root(ctx, (void**)&_arg_415); mph_Type* _arg_416 = t_float; mph_gc_push_root(ctx, (void**)&_arg_416); mph_TypeResult* _ret_417 = mph_type_binary_op(ctx, NULL, _arg_414, _arg_415, _arg_416); mph_gc_pop_roots(ctx, 3); _ret_417; });
	mph_gc_push_root(ctx, (void**)&r3);
	if (({ mph_TypeResult* _obj_418 = r3; mph_gc_push_root(ctx, (void**)&_obj_418); mph_bool _ret_419 = _obj_418->has_error; mph_gc_pop_roots(ctx, 1); _ret_419; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â float * float FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_422 = ({ mph_TypeResult* _obj_420 = r3; mph_gc_push_root(ctx, (void**)&_obj_420); mph_Type* _ret_421 = _obj_420->result; mph_gc_pop_roots(ctx, 1); _ret_421; }); mph_gc_push_root(ctx, (void**)&_obj_422); mph_int _ret_423 = _obj_422->kind; mph_gc_pop_roots(ctx, 1); _ret_423; }) == mph_KIND_FLOAT)) {
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
	mph_TypeResult* r4 = ({ mph_Type* _arg_424 = t_int; mph_gc_push_root(ctx, (void**)&_arg_424); MorphString* _arg_425 = mph_string_new(ctx, "<"); mph_gc_push_root(ctx, (void**)&_arg_425); mph_Type* _arg_426 = t_int; mph_gc_push_root(ctx, (void**)&_arg_426); mph_TypeResult* _ret_427 = mph_type_binary_op(ctx, NULL, _arg_424, _arg_425, _arg_426); mph_gc_pop_roots(ctx, 3); _ret_427; });
	mph_gc_push_root(ctx, (void**)&r4);
	if (({ mph_TypeResult* _obj_428 = r4; mph_gc_push_root(ctx, (void**)&_obj_428); mph_bool _ret_429 = _obj_428->has_error; mph_gc_pop_roots(ctx, 1); _ret_429; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int < int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_432 = ({ mph_TypeResult* _obj_430 = r4; mph_gc_push_root(ctx, (void**)&_obj_430); mph_Type* _ret_431 = _obj_430->result; mph_gc_pop_roots(ctx, 1); _ret_431; }); mph_gc_push_root(ctx, (void**)&_obj_432); mph_int _ret_433 = _obj_432->kind; mph_gc_pop_roots(ctx, 1); _ret_433; }) == mph_KIND_BOOL)) {
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
	mph_TypeResult* r5 = ({ mph_Type* _arg_434 = t_int; mph_gc_push_root(ctx, (void**)&_arg_434); MorphString* _arg_435 = mph_string_new(ctx, "=="); mph_gc_push_root(ctx, (void**)&_arg_435); mph_Type* _arg_436 = t_int; mph_gc_push_root(ctx, (void**)&_arg_436); mph_TypeResult* _ret_437 = mph_type_binary_op(ctx, NULL, _arg_434, _arg_435, _arg_436); mph_gc_pop_roots(ctx, 3); _ret_437; });
	mph_gc_push_root(ctx, (void**)&r5);
	if (({ mph_TypeResult* _obj_438 = r5; mph_gc_push_root(ctx, (void**)&_obj_438); mph_bool _ret_439 = _obj_438->has_error; mph_gc_pop_roots(ctx, 1); _ret_439; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int == int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_442 = ({ mph_TypeResult* _obj_440 = r5; mph_gc_push_root(ctx, (void**)&_obj_440); mph_Type* _ret_441 = _obj_440->result; mph_gc_pop_roots(ctx, 1); _ret_441; }); mph_gc_push_root(ctx, (void**)&_obj_442); mph_int _ret_443 = _obj_442->kind; mph_gc_pop_roots(ctx, 1); _ret_443; }) == mph_KIND_BOOL)) {
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
	mph_TypeResult* r6 = ({ mph_Type* _arg_444 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_444); MorphString* _arg_445 = mph_string_new(ctx, "dan"); mph_gc_push_root(ctx, (void**)&_arg_445); mph_Type* _arg_446 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_446); mph_TypeResult* _ret_447 = mph_type_binary_op(ctx, NULL, _arg_444, _arg_445, _arg_446); mph_gc_pop_roots(ctx, 3); _ret_447; });
	mph_gc_push_root(ctx, (void**)&r6);
	if (({ mph_TypeResult* _obj_448 = r6; mph_gc_push_root(ctx, (void**)&_obj_448); mph_bool _ret_449 = _obj_448->has_error; mph_gc_pop_roots(ctx, 1); _ret_449; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool dan bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_452 = ({ mph_TypeResult* _obj_450 = r6; mph_gc_push_root(ctx, (void**)&_obj_450); mph_Type* _ret_451 = _obj_450->result; mph_gc_pop_roots(ctx, 1); _ret_451; }); mph_gc_push_root(ctx, (void**)&_obj_452); mph_int _ret_453 = _obj_452->kind; mph_gc_pop_roots(ctx, 1); _ret_453; }) == mph_KIND_BOOL)) {
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
	mph_TypeResult* r7 = ({ mph_Type* _arg_454 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_454); MorphString* _arg_455 = mph_string_new(ctx, "||"); mph_gc_push_root(ctx, (void**)&_arg_455); mph_Type* _arg_456 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_456); mph_TypeResult* _ret_457 = mph_type_binary_op(ctx, NULL, _arg_454, _arg_455, _arg_456); mph_gc_pop_roots(ctx, 3); _ret_457; });
	mph_gc_push_root(ctx, (void**)&r7);
	if (({ mph_TypeResult* _obj_458 = r7; mph_gc_push_root(ctx, (void**)&_obj_458); mph_bool _ret_459 = _obj_458->has_error; mph_gc_pop_roots(ctx, 1); _ret_459; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â bool || bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_462 = ({ mph_TypeResult* _obj_460 = r7; mph_gc_push_root(ctx, (void**)&_obj_460); mph_Type* _ret_461 = _obj_460->result; mph_gc_pop_roots(ctx, 1); _ret_461; }); mph_gc_push_root(ctx, (void**)&_obj_462); mph_int _ret_463 = _obj_462->kind; mph_gc_pop_roots(ctx, 1); _ret_463; }) == mph_KIND_BOOL)) {
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
	mph_TypeResult* r8 = ({ mph_Type* _arg_464 = t_int; mph_gc_push_root(ctx, (void**)&_arg_464); MorphString* _arg_465 = mph_string_new(ctx, "&"); mph_gc_push_root(ctx, (void**)&_arg_465); mph_Type* _arg_466 = t_int; mph_gc_push_root(ctx, (void**)&_arg_466); mph_TypeResult* _ret_467 = mph_type_binary_op(ctx, NULL, _arg_464, _arg_465, _arg_466); mph_gc_pop_roots(ctx, 3); _ret_467; });
	mph_gc_push_root(ctx, (void**)&r8);
	if (({ mph_TypeResult* _obj_468 = r8; mph_gc_push_root(ctx, (void**)&_obj_468); mph_bool _ret_469 = _obj_468->has_error; mph_gc_pop_roots(ctx, 1); _ret_469; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int & int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_472 = ({ mph_TypeResult* _obj_470 = r8; mph_gc_push_root(ctx, (void**)&_obj_470); mph_Type* _ret_471 = _obj_470->result; mph_gc_pop_roots(ctx, 1); _ret_471; }); mph_gc_push_root(ctx, (void**)&_obj_472); mph_int _ret_473 = _obj_472->kind; mph_gc_pop_roots(ctx, 1); _ret_473; }) == mph_KIND_INT)) {
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
	mph_TypeResult* r9 = ({ mph_Type* _arg_474 = t_int; mph_gc_push_root(ctx, (void**)&_arg_474); MorphString* _arg_475 = mph_string_new(ctx, "<<"); mph_gc_push_root(ctx, (void**)&_arg_475); mph_Type* _arg_476 = t_int; mph_gc_push_root(ctx, (void**)&_arg_476); mph_TypeResult* _ret_477 = mph_type_binary_op(ctx, NULL, _arg_474, _arg_475, _arg_476); mph_gc_pop_roots(ctx, 3); _ret_477; });
	mph_gc_push_root(ctx, (void**)&r9);
	if (({ mph_TypeResult* _obj_478 = r9; mph_gc_push_root(ctx, (void**)&_obj_478); mph_bool _ret_479 = _obj_478->has_error; mph_gc_pop_roots(ctx, 1); _ret_479; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â int << int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_482 = ({ mph_TypeResult* _obj_480 = r9; mph_gc_push_root(ctx, (void**)&_obj_480); mph_Type* _ret_481 = _obj_480->result; mph_gc_pop_roots(ctx, 1); _ret_481; }); mph_gc_push_root(ctx, (void**)&_obj_482); mph_int _ret_483 = _obj_482->kind; mph_gc_pop_roots(ctx, 1); _ret_483; }) == mph_KIND_INT)) {
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
	mph_TypeResult* r10 = ({ mph_Type* _arg_484 = t_int; mph_gc_push_root(ctx, (void**)&_arg_484); MorphString* _arg_485 = mph_string_new(ctx, "+"); mph_gc_push_root(ctx, (void**)&_arg_485); mph_Type* _arg_486 = t_string; mph_gc_push_root(ctx, (void**)&_arg_486); mph_TypeResult* _ret_487 = mph_type_binary_op(ctx, NULL, _arg_484, _arg_485, _arg_486); mph_gc_pop_roots(ctx, 3); _ret_487; });
	mph_gc_push_root(ctx, (void**)&r10);
	if (({ mph_TypeResult* _obj_488 = r10; mph_gc_push_root(ctx, (void**)&_obj_488); mph_bool _ret_489 = _obj_488->has_error; mph_gc_pop_roots(ctx, 1); _ret_489; })) {
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
	mph_TypeResult* r11 = ({ mph_Type* _arg_490 = t_string; mph_gc_push_root(ctx, (void**)&_arg_490); MorphString* _arg_491 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_491); mph_Type* _arg_492 = t_string; mph_gc_push_root(ctx, (void**)&_arg_492); mph_TypeResult* _ret_493 = mph_type_binary_op(ctx, NULL, _arg_490, _arg_491, _arg_492); mph_gc_pop_roots(ctx, 3); _ret_493; });
	mph_gc_push_root(ctx, (void**)&r11);
	if (({ mph_TypeResult* _obj_494 = r11; mph_gc_push_root(ctx, (void**)&_obj_494); mph_bool _ret_495 = _obj_494->has_error; mph_gc_pop_roots(ctx, 1); _ret_495; })) {
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
	mph_TypeResult* r12 = ({ mph_Type* _arg_496 = t_bool; mph_gc_push_root(ctx, (void**)&_arg_496); MorphString* _arg_497 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_497); mph_TypeResult* _ret_498 = mph_type_prefix_op(ctx, NULL, _arg_496, _arg_497); mph_gc_pop_roots(ctx, 2); _ret_498; });
	mph_gc_push_root(ctx, (void**)&r12);
	if (({ mph_TypeResult* _obj_499 = r12; mph_gc_push_root(ctx, (void**)&_obj_499); mph_bool _ret_500 = _obj_499->has_error; mph_gc_pop_roots(ctx, 1); _ret_500; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â !bool FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_503 = ({ mph_TypeResult* _obj_501 = r12; mph_gc_push_root(ctx, (void**)&_obj_501); mph_Type* _ret_502 = _obj_501->result; mph_gc_pop_roots(ctx, 1); _ret_502; }); mph_gc_push_root(ctx, (void**)&_obj_503); mph_int _ret_504 = _obj_503->kind; mph_gc_pop_roots(ctx, 1); _ret_504; }) == mph_KIND_BOOL)) {
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
	mph_TypeResult* r13 = ({ mph_Type* _arg_505 = t_int; mph_gc_push_root(ctx, (void**)&_arg_505); MorphString* _arg_506 = mph_string_new(ctx, "-"); mph_gc_push_root(ctx, (void**)&_arg_506); mph_TypeResult* _ret_507 = mph_type_prefix_op(ctx, NULL, _arg_505, _arg_506); mph_gc_pop_roots(ctx, 2); _ret_507; });
	mph_gc_push_root(ctx, (void**)&r13);
	if (({ mph_TypeResult* _obj_508 = r13; mph_gc_push_root(ctx, (void**)&_obj_508); mph_bool _ret_509 = _obj_508->has_error; mph_gc_pop_roots(ctx, 1); _ret_509; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â -int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_512 = ({ mph_TypeResult* _obj_510 = r13; mph_gc_push_root(ctx, (void**)&_obj_510); mph_Type* _ret_511 = _obj_510->result; mph_gc_pop_roots(ctx, 1); _ret_511; }); mph_gc_push_root(ctx, (void**)&_obj_512); mph_int _ret_513 = _obj_512->kind; mph_gc_pop_roots(ctx, 1); _ret_513; }) == mph_KIND_INT)) {
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
	mph_TypeResult* r14 = ({ mph_Type* _arg_514 = t_int; mph_gc_push_root(ctx, (void**)&_arg_514); MorphString* _arg_515 = mph_string_new(ctx, "~"); mph_gc_push_root(ctx, (void**)&_arg_515); mph_TypeResult* _ret_516 = mph_type_prefix_op(ctx, NULL, _arg_514, _arg_515); mph_gc_pop_roots(ctx, 2); _ret_516; });
	mph_gc_push_root(ctx, (void**)&r14);
	if (({ mph_TypeResult* _obj_517 = r14; mph_gc_push_root(ctx, (void**)&_obj_517); mph_bool _ret_518 = _obj_517->has_error; mph_gc_pop_roots(ctx, 1); _ret_518; })) {
{
	mph_native_print(ctx, mph_string_new(ctx, "  â ~int FAILED\n"));
	failed = (failed + 1);
}
	} else {
{
	if ((({ mph_Type* _obj_521 = ({ mph_TypeResult* _obj_519 = r14; mph_gc_push_root(ctx, (void**)&_obj_519); mph_Type* _ret_520 = _obj_519->result; mph_gc_pop_roots(ctx, 1); _ret_520; }); mph_gc_push_root(ctx, (void**)&_obj_521); mph_int _ret_522 = _obj_521->kind; mph_gc_pop_roots(ctx, 1); _ret_522; }) == mph_KIND_INT)) {
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
	mph_TypeResult* r15 = ({ mph_Type* _arg_523 = t_string; mph_gc_push_root(ctx, (void**)&_arg_523); MorphString* _arg_524 = mph_string_new(ctx, "!"); mph_gc_push_root(ctx, (void**)&_arg_524); mph_TypeResult* _ret_525 = mph_type_prefix_op(ctx, NULL, _arg_523, _arg_524); mph_gc_pop_roots(ctx, 2); _ret_525; });
	mph_gc_push_root(ctx, (void**)&r15);
	if (({ mph_TypeResult* _obj_526 = r15; mph_gc_push_root(ctx, (void**)&_obj_526); mph_bool _ret_527 = _obj_526->has_error; mph_gc_pop_roots(ctx, 1); _ret_527; })) {
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
	MorphString* s1 = mph_kind_to_string(ctx, NULL, mph_KIND_INT);
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
	MorphString* s2 = mph_kind_to_string(ctx, NULL, mph_KIND_CHANNEL);
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


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_KIND_INT = 0;
	mph_KIND_FLOAT = 1;
	mph_KIND_STRING = 2;
	mph_KIND_BOOL = 3;
	mph_KIND_VOID = 4;
	mph_KIND_FUNCTION = 5;
	mph_KIND_STRUCT = 6;
	mph_KIND_INTERFACE = 7;
	mph_KIND_ARRAY = 8;
	mph_KIND_MAP = 9;
	mph_KIND_POINTER = 10;
	mph_KIND_MULTI = 11;
	mph_KIND_UNKNOWN = 12;
	mph_KIND_ERROR = 13;
	mph_KIND_NULL = 14;
	mph_KIND_USER_ERROR = 15;
	mph_KIND_MODULE = 16;
	mph_KIND_CHANNEL = 17;
	mph_main(ctx, NULL);
}
