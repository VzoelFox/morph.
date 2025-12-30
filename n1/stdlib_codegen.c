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

// Struct Definitions (Env & Types)

// Global Variables

// Function Prototypes
MorphString* mph_int_to_string(MorphContext* ctx, void* _env_void, mph_int n);
MorphString* mph_char_at(MorphContext* ctx, void* _env_void, MorphString* s, mph_int index);
MorphString* mph_string_escape(MorphContext* ctx, void* _env_void, MorphString* s);
mph_bool mph_is_alpha(MorphContext* ctx, void* _env_void, MorphString* ch);
mph_bool mph_is_digit(MorphContext* ctx, void* _env_void, MorphString* ch);
mph_bool mph_is_valid_c_ident(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_module_to_prefix(MorphContext* ctx, void* _env_void, MorphString* path);
MorphString* mph_IntToString(MorphContext* ctx, void* _env_void, mph_int n);
MorphString* mph_StringEscape(MorphContext* ctx, void* _env_void, MorphString* s);
mph_bool mph_IsValidCIdent(MorphContext* ctx, void* _env_void, MorphString* name);
MorphString* mph_ModuleToPrefix(MorphContext* ctx, void* _env_void, MorphString* path);
void mph_main(MorphContext* ctx, void* _env_void);

// Function Definitions
MorphString* mph_int_to_string(MorphContext* ctx, void* _env_void, mph_int n) {
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
	result = ({ MorphString* _lhs_1 = mph_string_new(ctx, "0"); MorphString* _rhs_2 = result; mph_gc_push_root(ctx, (void**)&_lhs_1); mph_gc_push_root(ctx, (void**)&_rhs_2); MorphString* _ret_3 = mph_string_concat(ctx, _lhs_1, _rhs_2); mph_gc_pop_roots(ctx, 2); _ret_3; });
}
	}
	if ((digit == 1)) {
{
	result = ({ MorphString* _lhs_4 = mph_string_new(ctx, "1"); MorphString* _rhs_5 = result; mph_gc_push_root(ctx, (void**)&_lhs_4); mph_gc_push_root(ctx, (void**)&_rhs_5); MorphString* _ret_6 = mph_string_concat(ctx, _lhs_4, _rhs_5); mph_gc_pop_roots(ctx, 2); _ret_6; });
}
	}
	if ((digit == 2)) {
{
	result = ({ MorphString* _lhs_7 = mph_string_new(ctx, "2"); MorphString* _rhs_8 = result; mph_gc_push_root(ctx, (void**)&_lhs_7); mph_gc_push_root(ctx, (void**)&_rhs_8); MorphString* _ret_9 = mph_string_concat(ctx, _lhs_7, _rhs_8); mph_gc_pop_roots(ctx, 2); _ret_9; });
}
	}
	if ((digit == 3)) {
{
	result = ({ MorphString* _lhs_10 = mph_string_new(ctx, "3"); MorphString* _rhs_11 = result; mph_gc_push_root(ctx, (void**)&_lhs_10); mph_gc_push_root(ctx, (void**)&_rhs_11); MorphString* _ret_12 = mph_string_concat(ctx, _lhs_10, _rhs_11); mph_gc_pop_roots(ctx, 2); _ret_12; });
}
	}
	if ((digit == 4)) {
{
	result = ({ MorphString* _lhs_13 = mph_string_new(ctx, "4"); MorphString* _rhs_14 = result; mph_gc_push_root(ctx, (void**)&_lhs_13); mph_gc_push_root(ctx, (void**)&_rhs_14); MorphString* _ret_15 = mph_string_concat(ctx, _lhs_13, _rhs_14); mph_gc_pop_roots(ctx, 2); _ret_15; });
}
	}
	if ((digit == 5)) {
{
	result = ({ MorphString* _lhs_16 = mph_string_new(ctx, "5"); MorphString* _rhs_17 = result; mph_gc_push_root(ctx, (void**)&_lhs_16); mph_gc_push_root(ctx, (void**)&_rhs_17); MorphString* _ret_18 = mph_string_concat(ctx, _lhs_16, _rhs_17); mph_gc_pop_roots(ctx, 2); _ret_18; });
}
	}
	if ((digit == 6)) {
{
	result = ({ MorphString* _lhs_19 = mph_string_new(ctx, "6"); MorphString* _rhs_20 = result; mph_gc_push_root(ctx, (void**)&_lhs_19); mph_gc_push_root(ctx, (void**)&_rhs_20); MorphString* _ret_21 = mph_string_concat(ctx, _lhs_19, _rhs_20); mph_gc_pop_roots(ctx, 2); _ret_21; });
}
	}
	if ((digit == 7)) {
{
	result = ({ MorphString* _lhs_22 = mph_string_new(ctx, "7"); MorphString* _rhs_23 = result; mph_gc_push_root(ctx, (void**)&_lhs_22); mph_gc_push_root(ctx, (void**)&_rhs_23); MorphString* _ret_24 = mph_string_concat(ctx, _lhs_22, _rhs_23); mph_gc_pop_roots(ctx, 2); _ret_24; });
}
	}
	if ((digit == 8)) {
{
	result = ({ MorphString* _lhs_25 = mph_string_new(ctx, "8"); MorphString* _rhs_26 = result; mph_gc_push_root(ctx, (void**)&_lhs_25); mph_gc_push_root(ctx, (void**)&_rhs_26); MorphString* _ret_27 = mph_string_concat(ctx, _lhs_25, _rhs_26); mph_gc_pop_roots(ctx, 2); _ret_27; });
}
	}
	if ((digit == 9)) {
{
	result = ({ MorphString* _lhs_28 = mph_string_new(ctx, "9"); MorphString* _rhs_29 = result; mph_gc_push_root(ctx, (void**)&_lhs_28); mph_gc_push_root(ctx, (void**)&_rhs_29); MorphString* _ret_30 = mph_string_concat(ctx, _lhs_28, _rhs_29); mph_gc_pop_roots(ctx, 2); _ret_30; });
}
	}
}
	}
	if (is_negative) {
{
	result = ({ MorphString* _lhs_31 = mph_string_new(ctx, "-"); MorphString* _rhs_32 = result; mph_gc_push_root(ctx, (void**)&_lhs_31); mph_gc_push_root(ctx, (void**)&_rhs_32); MorphString* _ret_33 = mph_string_concat(ctx, _lhs_31, _rhs_32); mph_gc_pop_roots(ctx, 2); _ret_33; });
}
	}
	return result;
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_char_at(MorphContext* ctx, void* _env_void, MorphString* s, mph_int index) {
	mph_gc_push_root(ctx, (void**)&s);
	return mph_string_substring(ctx, s, index, (index + 1));
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_string_escape(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	MorphString* result = mph_string_new(ctx, "");
	mph_gc_push_root(ctx, (void**)&result);
	mph_int i = 0;
	mph_int len = ({ MorphString* _len_arg_34 = s; mph_gc_push_root(ctx, (void**)&_len_arg_34); mph_int _ret_35 = ((MorphString*)_len_arg_34)->length; mph_gc_pop_roots(ctx, 1); _ret_35; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_36 = s; mph_gc_push_root(ctx, (void**)&_arg_36); MorphString* _ret_37 = mph_char_at(ctx, NULL, _arg_36, i); mph_gc_pop_roots(ctx, 1); _ret_37; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\\"))) {
{
	result = ({ MorphString* _lhs_38 = result; MorphString* _rhs_39 = mph_string_new(ctx, "\\\\"); mph_gc_push_root(ctx, (void**)&_lhs_38); mph_gc_push_root(ctx, (void**)&_rhs_39); MorphString* _ret_40 = mph_string_concat(ctx, _lhs_38, _rhs_39); mph_gc_pop_roots(ctx, 2); _ret_40; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\""))) {
{
	result = ({ MorphString* _lhs_41 = result; MorphString* _rhs_42 = mph_string_new(ctx, "\\\""); mph_gc_push_root(ctx, (void**)&_lhs_41); mph_gc_push_root(ctx, (void**)&_rhs_42); MorphString* _ret_43 = mph_string_concat(ctx, _lhs_41, _rhs_42); mph_gc_pop_roots(ctx, 2); _ret_43; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\n"))) {
{
	result = ({ MorphString* _lhs_44 = result; MorphString* _rhs_45 = mph_string_new(ctx, "\\n"); mph_gc_push_root(ctx, (void**)&_lhs_44); mph_gc_push_root(ctx, (void**)&_rhs_45); MorphString* _ret_46 = mph_string_concat(ctx, _lhs_44, _rhs_45); mph_gc_pop_roots(ctx, 2); _ret_46; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\r"))) {
{
	result = ({ MorphString* _lhs_47 = result; MorphString* _rhs_48 = mph_string_new(ctx, "\\r"); mph_gc_push_root(ctx, (void**)&_lhs_47); mph_gc_push_root(ctx, (void**)&_rhs_48); MorphString* _ret_49 = mph_string_concat(ctx, _lhs_47, _rhs_48); mph_gc_pop_roots(ctx, 2); _ret_49; });
}
	} else {
{
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "\t"))) {
{
	result = ({ MorphString* _lhs_50 = result; MorphString* _rhs_51 = mph_string_new(ctx, "\\t"); mph_gc_push_root(ctx, (void**)&_lhs_50); mph_gc_push_root(ctx, (void**)&_rhs_51); MorphString* _ret_52 = mph_string_concat(ctx, _lhs_50, _rhs_51); mph_gc_pop_roots(ctx, 2); _ret_52; });
}
	} else {
{
	result = ({ MorphString* _lhs_53 = result; MorphString* _rhs_54 = ch; mph_gc_push_root(ctx, (void**)&_lhs_53); mph_gc_push_root(ctx, (void**)&_rhs_54); MorphString* _ret_55 = mph_string_concat(ctx, _lhs_53, _rhs_54); mph_gc_pop_roots(ctx, 2); _ret_55; });
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

mph_bool mph_is_alpha(MorphContext* ctx, void* _env_void, MorphString* ch) {
	mph_gc_push_root(ctx, (void**)&ch);
	return (((((((((((((((((((((((((((((((((((((((((((((((((((mph_string_eq(ctx, ch, mph_string_new(ctx, "a")) || mph_string_eq(ctx, ch, mph_string_new(ctx, "b"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "c"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "d"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "e"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "f"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "g"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "h"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "i"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "j"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "k"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "l"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "m"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "n"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "o"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "p"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "q"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "r"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "s"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "t"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "u"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "v"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "w"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "x"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "y"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "z"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "A"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "B"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "C"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "D"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "E"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "F"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "G"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "H"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "I"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "J"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "K"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "L"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "M"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "N"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "O"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "P"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "Q"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "R"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "S"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "T"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "U"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "V"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "W"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "X"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "Y"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "Z")));
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_is_digit(MorphContext* ctx, void* _env_void, MorphString* ch) {
	mph_gc_push_root(ctx, (void**)&ch);
	return (((((((((mph_string_eq(ctx, ch, mph_string_new(ctx, "0")) || mph_string_eq(ctx, ch, mph_string_new(ctx, "1"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "2"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "3"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "4"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "5"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "6"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "7"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "8"))) || mph_string_eq(ctx, ch, mph_string_new(ctx, "9")));
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_is_valid_c_ident(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	mph_int len = ({ MorphString* _len_arg_56 = name; mph_gc_push_root(ctx, (void**)&_len_arg_56); mph_int _ret_57 = ((MorphString*)_len_arg_56)->length; mph_gc_pop_roots(ctx, 1); _ret_57; });
	if ((len == 0)) {
{
	return 0;
}
	}
	MorphString* first = ({ MorphString* _arg_58 = name; mph_gc_push_root(ctx, (void**)&_arg_58); MorphString* _ret_59 = mph_char_at(ctx, NULL, _arg_58, 0); mph_gc_pop_roots(ctx, 1); _ret_59; });
	mph_gc_push_root(ctx, (void**)&first);
	if (((first != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_60 = first; mph_gc_push_root(ctx, (void**)&_arg_60); mph_bool _ret_61 = mph_is_alpha(ctx, NULL, _arg_60); mph_gc_pop_roots(ctx, 1); _ret_61; })))) {
{
	return 0;
}
	}
	mph_int i = 1;
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_62 = name; mph_gc_push_root(ctx, (void**)&_arg_62); MorphString* _ret_63 = mph_char_at(ctx, NULL, _arg_62, i); mph_gc_pop_roots(ctx, 1); _ret_63; });
	mph_gc_push_root(ctx, (void**)&ch);
	if ((((ch != mph_string_new(ctx, "_")) && (!({ MorphString* _arg_64 = ch; mph_gc_push_root(ctx, (void**)&_arg_64); mph_bool _ret_65 = mph_is_alpha(ctx, NULL, _arg_64); mph_gc_pop_roots(ctx, 1); _ret_65; }))) && (!({ MorphString* _arg_66 = ch; mph_gc_push_root(ctx, (void**)&_arg_66); mph_bool _ret_67 = mph_is_digit(ctx, NULL, _arg_66); mph_gc_pop_roots(ctx, 1); _ret_67; })))) {
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

MorphString* mph_module_to_prefix(MorphContext* ctx, void* _env_void, MorphString* path) {
	mph_gc_push_root(ctx, (void**)&path);
	MorphString* result = mph_string_new(ctx, "mph_");
	mph_gc_push_root(ctx, (void**)&result);
	mph_int i = 0;
	mph_int len = ({ MorphString* _len_arg_68 = path; mph_gc_push_root(ctx, (void**)&_len_arg_68); mph_int _ret_69 = ((MorphString*)_len_arg_68)->length; mph_gc_pop_roots(ctx, 1); _ret_69; });
	while ((i < len)) {
{
	MorphString* ch = ({ MorphString* _arg_70 = path; mph_gc_push_root(ctx, (void**)&_arg_70); MorphString* _ret_71 = mph_char_at(ctx, NULL, _arg_70, i); mph_gc_pop_roots(ctx, 1); _ret_71; });
	mph_gc_push_root(ctx, (void**)&ch);
	if (mph_string_eq(ctx, ch, mph_string_new(ctx, "/"))) {
{
	result = ({ MorphString* _lhs_72 = result; MorphString* _rhs_73 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_72); mph_gc_push_root(ctx, (void**)&_rhs_73); MorphString* _ret_74 = mph_string_concat(ctx, _lhs_72, _rhs_73); mph_gc_pop_roots(ctx, 2); _ret_74; });
}
	} else {
{
	if (((({ MorphString* _arg_75 = ch; mph_gc_push_root(ctx, (void**)&_arg_75); mph_bool _ret_76 = mph_is_alpha(ctx, NULL, _arg_75); mph_gc_pop_roots(ctx, 1); _ret_76; }) || ({ MorphString* _arg_77 = ch; mph_gc_push_root(ctx, (void**)&_arg_77); mph_bool _ret_78 = mph_is_digit(ctx, NULL, _arg_77); mph_gc_pop_roots(ctx, 1); _ret_78; })) || mph_string_eq(ctx, ch, mph_string_new(ctx, "_")))) {
{
	result = ({ MorphString* _lhs_79 = result; MorphString* _rhs_80 = ch; mph_gc_push_root(ctx, (void**)&_lhs_79); mph_gc_push_root(ctx, (void**)&_rhs_80); MorphString* _ret_81 = mph_string_concat(ctx, _lhs_79, _rhs_80); mph_gc_pop_roots(ctx, 2); _ret_81; });
}
	} else {
{
	result = ({ MorphString* _lhs_82 = result; MorphString* _rhs_83 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_82); mph_gc_push_root(ctx, (void**)&_rhs_83); MorphString* _ret_84 = mph_string_concat(ctx, _lhs_82, _rhs_83); mph_gc_pop_roots(ctx, 2); _ret_84; });
}
	}
}
	}
	i = (i + 1);
	mph_gc_pop_roots(ctx, 1);
}
	}
	result = ({ MorphString* _lhs_85 = result; MorphString* _rhs_86 = mph_string_new(ctx, "_"); mph_gc_push_root(ctx, (void**)&_lhs_85); mph_gc_push_root(ctx, (void**)&_rhs_86); MorphString* _ret_87 = mph_string_concat(ctx, _lhs_85, _rhs_86); mph_gc_pop_roots(ctx, 2); _ret_87; });
	return result;
	mph_gc_pop_roots(ctx, 1);
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_IntToString(MorphContext* ctx, void* _env_void, mph_int n) {
	return mph_int_to_string(ctx, NULL, n);
}

MorphString* mph_StringEscape(MorphContext* ctx, void* _env_void, MorphString* s) {
	mph_gc_push_root(ctx, (void**)&s);
	return ({ MorphString* _arg_88 = s; mph_gc_push_root(ctx, (void**)&_arg_88); MorphString* _ret_89 = mph_string_escape(ctx, NULL, _arg_88); mph_gc_pop_roots(ctx, 1); _ret_89; });
	mph_gc_pop_roots(ctx, 1);
}

mph_bool mph_IsValidCIdent(MorphContext* ctx, void* _env_void, MorphString* name) {
	mph_gc_push_root(ctx, (void**)&name);
	return ({ MorphString* _arg_90 = name; mph_gc_push_root(ctx, (void**)&_arg_90); mph_bool _ret_91 = mph_is_valid_c_ident(ctx, NULL, _arg_90); mph_gc_pop_roots(ctx, 1); _ret_91; });
	mph_gc_pop_roots(ctx, 1);
}

MorphString* mph_ModuleToPrefix(MorphContext* ctx, void* _env_void, MorphString* path) {
	mph_gc_push_root(ctx, (void**)&path);
	return ({ MorphString* _arg_92 = path; mph_gc_push_root(ctx, (void**)&_arg_92); MorphString* _ret_93 = mph_module_to_prefix(ctx, NULL, _arg_92); mph_gc_pop_roots(ctx, 1); _ret_93; });
	mph_gc_pop_roots(ctx, 1);
}

void mph_main(MorphContext* ctx, void* _env_void) {
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n"));
	mph_native_print(ctx, mph_string_new(ctx, "â  Stdlib Codegen Utilities Test      â\n"));
	mph_native_print(ctx, mph_string_new(ctx, "ââââââââââââââââââââââââââââââââââââââââ\n\n"));
	mph_native_print(ctx, mph_string_new(ctx, "[Test 1] int_to_string()\n"));
	MorphString* s1 = mph_int_to_string(ctx, NULL, 0);
	mph_gc_push_root(ctx, (void**)&s1);
	mph_native_print(ctx, mph_string_new(ctx, "  0 â \""));
	mph_native_print(ctx, s1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* s2 = mph_int_to_string(ctx, NULL, 42);
	mph_gc_push_root(ctx, (void**)&s2);
	mph_native_print(ctx, mph_string_new(ctx, "  42 â \""));
	mph_native_print(ctx, s2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* s3 = mph_int_to_string(ctx, NULL, (-123));
	mph_gc_push_root(ctx, (void**)&s3);
	mph_native_print(ctx, mph_string_new(ctx, "  -123 â \""));
	mph_native_print(ctx, s3);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* s4 = mph_int_to_string(ctx, NULL, 9876);
	mph_gc_push_root(ctx, (void**)&s4);
	mph_native_print(ctx, mph_string_new(ctx, "  9876 â \""));
	mph_native_print(ctx, s4);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n\n"));
	mph_native_print(ctx, mph_string_new(ctx, "[Test 2] string_escape()\n"));
	MorphString* e1 = ({ MorphString* _arg_94 = mph_string_new(ctx, "hello"); mph_gc_push_root(ctx, (void**)&_arg_94); MorphString* _ret_95 = mph_string_escape(ctx, NULL, _arg_94); mph_gc_pop_roots(ctx, 1); _ret_95; });
	mph_gc_push_root(ctx, (void**)&e1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\" â \""));
	mph_native_print(ctx, e1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* e2 = ({ MorphString* _arg_96 = mph_string_new(ctx, "hello\nworld"); mph_gc_push_root(ctx, (void**)&_arg_96); MorphString* _ret_97 = mph_string_escape(ctx, NULL, _arg_96); mph_gc_pop_roots(ctx, 1); _ret_97; });
	mph_gc_push_root(ctx, (void**)&e2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"hello\\nworld\" â \""));
	mph_native_print(ctx, e2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 3] module_to_prefix()\n"));
	MorphString* p1 = ({ MorphString* _arg_98 = mph_string_new(ctx, "token"); mph_gc_push_root(ctx, (void**)&_arg_98); MorphString* _ret_99 = mph_module_to_prefix(ctx, NULL, _arg_98); mph_gc_pop_roots(ctx, 1); _ret_99; });
	mph_gc_push_root(ctx, (void**)&p1);
	mph_native_print(ctx, mph_string_new(ctx, "  \"token\" â \""));
	mph_native_print(ctx, p1);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	MorphString* p2 = ({ MorphString* _arg_100 = mph_string_new(ctx, "std/string"); mph_gc_push_root(ctx, (void**)&_arg_100); MorphString* _ret_101 = mph_module_to_prefix(ctx, NULL, _arg_100); mph_gc_pop_roots(ctx, 1); _ret_101; });
	mph_gc_push_root(ctx, (void**)&p2);
	mph_native_print(ctx, mph_string_new(ctx, "  \"std/string\" â \""));
	mph_native_print(ctx, p2);
	mph_native_print(ctx, mph_string_new(ctx, "\"\n"));
	mph_native_print(ctx, mph_string_new(ctx, "\n[Test 4] is_valid_c_ident()\n"));
	mph_bool v1 = ({ MorphString* _arg_102 = mph_string_new(ctx, "foo"); mph_gc_push_root(ctx, (void**)&_arg_102); mph_bool _ret_103 = mph_is_valid_c_ident(ctx, NULL, _arg_102); mph_gc_pop_roots(ctx, 1); _ret_103; });
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
	mph_bool v2 = ({ MorphString* _arg_104 = mph_string_new(ctx, "_bar123"); mph_gc_push_root(ctx, (void**)&_arg_104); mph_bool _ret_105 = mph_is_valid_c_ident(ctx, NULL, _arg_104); mph_gc_pop_roots(ctx, 1); _ret_105; });
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
	mph_bool v3 = ({ MorphString* _arg_106 = mph_string_new(ctx, "123bad"); mph_gc_push_root(ctx, (void**)&_arg_106); mph_bool _ret_107 = mph_is_valid_c_ident(ctx, NULL, _arg_106); mph_gc_pop_roots(ctx, 1); _ret_107; });
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


// Entry Point
void morph_entry_point(MorphContext* ctx) {
	mph_main(ctx, NULL);
}
