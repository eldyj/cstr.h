#ifndef CSTR_H
#	define CSTR_H

#	include <stddef.h>
#	include <stdint.h>

#	ifndef CSTR_C
#		define CSTR_DEF extern
CSTR_DEF const uint8_t char_case_offset;
#	else
#		define CSTR_DEF
#	endif /* CSTR_C*/

CSTR_DEF size_t cstr_len(const char *const s);
CSTR_DEF void cstr_ncopy(char *const *const b, const char *const s, size_t n);
CSTR_DEF void cstr_copy(char *const *const b, const char *const s);
CSTR_DEF char *cstr_dup(const char *const s);
CSTR_DEF void cstr_append(char **const s0, const char *const s1);
CSTR_DEF char *cstr_concat(const char *const s0, const char *const s1);
CSTR_DEF char *cstr_bashslice(const char *const s, const size_t o, const size_t l);
CSTR_DEF char *cstr_substr(const char *const s, const size_t s1, const size_t e);
CSTR_DEF char *cstr_lcut(const char *const s, const size_t n);
CSTR_DEF char *cstr_rcut(const char *const s, const size_t n);
CSTR_DEF uint8_t cstr_nequals(const char *const s0, const char *const s1, size_t n);
CSTR_DEF uint8_t cstr_equals(const char *const s0, const char *const s1);
CSTR_DEF void cstr_to_reversed(char *const *const s);
CSTR_DEF char *cstr_reverse(const char *const s);
CSTR_DEF size_t cstr_contains(const char *const s0, const char *const s1);
CSTR_DEF uint8_t cstr_startswith(const char *const s0, const char *const s1);
CSTR_DEF uint8_t cstr_endsswith(const char *const s0, const char *const s1);
CSTR_DEF char *cstr_replace_once(const char *const s0, const char *const s1, const char *const s2);
CSTR_DEF char *cstr_replace(const char *const s0, const char *const s1, const char *const s2);
CSTR_DEF uint8_t char_is_upcase(const char c);
CSTR_DEF uint8_t char_is_downcase(const char c);
CSTR_DEF uint8_t char_is_space(const char c);
CSTR_DEF uint8_t char_is_alpha(const char c);
CSTR_DEF uint8_t char_is_digit(const char c);
CSTR_DEF uint8_t char_is_uphex(const char c);
CSTR_DEF uint8_t char_is_downhex(const char c);
CSTR_DEF uint8_t char_is_hex(const char c);
CSTR_DEF uint8_t char_is_octal(const char c);
CSTR_DEF uint8_t char_is_binary(const char c);
CSTR_DEF uint8_t char_is_pental(const char c);
CSTR_DEF char char_to_upcase(const char c);
CSTR_DEF char char_to_downcase(const char c);
CSTR_DEF uint8_t char_to_digit(const char c);
CSTR_DEF uint8_t char_to_uphex(const char c);
CSTR_DEF uint8_t char_to_downhex(const char c);
CSTR_DEF uint8_t char_to_hex(const char c);
CSTR_DEF uint8_t char_to_octal(const char c);
CSTR_DEF uint8_t char_to_binary(const char c);
CSTR_DEF uint8_t char_to_pental(const char c);
CSTR_DEF void cstr_to_upcase(char *const *const s);
CSTR_DEF void cstr_to_downcase(char *const *const s);
CSTR_DEF char *cstr_upcase(const char *const s);
CSTR_DEF char *cstr_downcase(const char *const s);
CSTR_DEF uint8_t cstr_is_upcase(const char *const s);
CSTR_DEF uint8_t cstr_is_downcase(const char *const s);
CSTR_DEF char *cstr_mul(const char *const s, size_t t);
CSTR_DEF uint8_t cstr_is_digit(const char *const s);
CSTR_DEF char *cstr_ltrim(const char *const s);
CSTR_DEF char *cstr_rtrim(const char *const s);
CSTR_DEF char *cstr_trim(const char *const s);
CSTR_DEF char *cstr_lpad(const char *const s, const size_t n);
CSTR_DEF char *cstr_rpad(const char *const s, const size_t n);
CSTR_DEF char *cstr_pad(const char *const s, const size_t n0, const size_t n1);
CSTR_DEF uint8_t cstr_is_digit(const char *const s);
CSTR_DEF uint8_t cstr_is_uphex(const char *const s);
CSTR_DEF uint8_t cstr_is_downhex(const char *const s);
CSTR_DEF uint8_t cstr_is_hex(const char *const s);
CSTR_DEF uint8_t cstr_is_octal(const char *const s);
CSTR_DEF uint8_t cstr_is_binary(const char *const s);
CSTR_DEF uint8_t cstr_is_pental(const char *const s);
CSTR_DEF uint64_t cstr_to_uint(const char *const s);
CSTR_DEF int64_t cstr_to_int(const char *const s);
CSTR_DEF uint64_t cstr_to_uphex(const char *const s);
CSTR_DEF uint64_t cstr_to_downhex(const char *const s);
CSTR_DEF uint64_t cstr_to_hex(const char *const s);
CSTR_DEF uint64_t cstr_to_octal(const char *const s);
CSTR_DEF uint64_t cstr_to_binary(const char *const s);
CSTR_DEF uint64_t cstr_to_pental(const char *const s);
CSTR_DEF size_t cstrarr_len(const char *const *const a);
CSTR_DEF void cstrarr_append(char ***const a, char *const s);
CSTR_DEF void cstrarr_prepend(char ***const a, char *const s);
CSTR_DEF void cstrarr_push(char ***const a, const char *const s);
CSTR_DEF void cstrarr_pushb(char ***const a, const char *const s);
CSTR_DEF void cstrarr_append_cstrarr(char ***const a0, char ** const a1);
CSTR_DEF char *cstrarr_pop(char ***const a);
CSTR_DEF char *cstrarr_shift(char ***const a);
CSTR_DEF size_t cstr_find_char(const char *const s, const char c);
CSTR_DEF size_t cstr_find_space(const char *const s);
CSTR_DEF void cstr_ltrim_self(char **const s);
CSTR_DEF void cstr_rtrim_self(char **const s);
CSTR_DEF void cstr_trim_self(char **const s);
CSTR_DEF char **cstr_split_char(const char *const s, const char c);
CSTR_DEF char **cstr_split(const char *const s0, const char *const s1);
CSTR_DEF char *cstrarr_join(const char *const *const a, const char *const s);
CSTR_DEF void cstrarr_free(char ***const a);
#endif /* !CSTR_H */
