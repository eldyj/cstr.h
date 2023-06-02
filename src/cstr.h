#ifndef CSTR_H
#	define CSTR_H
#	include <stddef.h>
# include <stdint.h>

char *cstr_alloc(const size_t l);
char *cstr_realloc(char *const s, const size_t l);
void cstr_free(char *const s);
size_t cstr_len(const char *const s);
uint8_t cstr_ncopy(const char *const s, char *const b, const size_t n);
uint8_t cstr_rncopy(const char *const s, char *const b, const size_t n);
uint8_t cstr_copy(const char *const s, char *const b);
uint8_t cstr_rcopy(const char *const s, char *const b);
char *cstr_dup(const char *const s);
uint8_t cstr_put(char **const s, const char c, const size_t p);
uint8_t cstr_add(char **const s, const char c);
uint8_t cstr_prep(char **const s, const char c);
uint8_t cstr_insert(char **const s0, const char *const s1, const size_t p);
uint8_t cstr_append(char **const s0, const char *const s1);
uint8_t cstr_prepend(char **const s0, const char *const s1);
uint8_t cstr_rem(char **const s, const size_t p);
uint8_t cstr_nrem(char **const s, const size_t p, const size_t n);
uint8_t cstr_rshift(char **const s, const size_t n);
uint8_t cstr_lshift(char **const s, const size_t n);
uint8_t cstr_nequals(const char *const s0, const char *const s1, const size_t n);
uint8_t cstr_equals(const char *const s0, const char *const s1);
uint8_t cstr_startswith(const char *const s0, const char *const s1);
uint8_t cstr_endswith(const char *const s0, const char *const s1);
size_t cstr_contains(const char *const s0, const char *const s1);
uint8_t cstr_replace(char **const s0, const char *const s1, const char *const s2);
uint8_t cstr_bashslice_to(const char *const s, const size_t o, const size_t l, char *const b);
uint8_t cstr_substr_to(const char *const s, const size_t p0, const size_t p1, char *const b);
char *cstr_bashslice(const char *const s, const size_t o, const size_t l);
char *cstr_substr(const char *const s, const size_t p0, const size_t p1);
uint8_t char_is_space(const char c);
size_t cstr_find_space_after(const char *const s, const size_t p);
size_t cstr_find_space_before(const char *const s, const size_t p);
uint8_t cstr_reverse(char *const s);
char *cstr_reversed(const char *const s);
char *cstr_mul(const char *const s, const size_t n);
size_t cstr_leading_spaces(const char *const s);
size_t cstr_trailing_spaces(const char *const s);
uint8_t cstr_ltrim(char **const s);
uint8_t cstr_rtrim(char **const s);
uint8_t cstr_trim(char **const s);
#endif /* !CSTR_H */
