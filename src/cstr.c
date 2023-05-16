#ifndef CSTR_C
#	define CSTR_C

# include "cstr.h"
#	include <stdlib.h>

const uint8_t char_case_offset = 'A' - 'a';

size_t
cstr_len(s)
	const char *const s;
{
	const char *sp = (const char *)s;
	
	while (*sp++)
		/* VOID */;

	return sp - s - 1;
}

void
cstr_ncopy(b, s, n)
	char *const *const b;
	const char *const s;
	size_t n;
{
	if (*b == s)
		return;

	while (n--)
		(*b)[n] = s[n];
}

void
cstr_copy(b, s)
	char *const *const b;
	const char *const s;
{
	if (*b == s)
		return;

	const size_t l = cstr_len(s);
	cstr_ncopy(b, s, l);
	(*b)[l] = 0;
}

char
*cstr_dup(s)
	const char *const s;
{
	char *const r = malloc(sizeof(char) * (cstr_len(s)+1));
	cstr_copy(&r, s);
	return r;
}

void
cstr_append(s0, s1)
	char **const s0;
	const char *const s1;
{
	const uint8_t is_same = *s0 == s1;
	char *p = (char *) s1;

	if (is_same)
		p = cstr_dup(s1);
	
	const size_t l0 = cstr_len(*s0);
	const size_t l1 = cstr_len(p);
	
	*s0 = realloc(*s0, sizeof(char) * (l0+l1+1));
	
	char *const t = (*s0)+l0;
	cstr_ncopy(&t, p, l1);

	if (is_same)
		free(p);
}

char
*cstr_concat(s0, s1)
	const char *const s0, *const s1;
{
	char *r = cstr_dup(s0);
	cstr_append(&r, s1);
	return r;
}

char
*cstr_bashslice(s, o, l)
	const char *const s;
	const size_t o, l;
{
	char *const r = malloc(sizeof(char) * (l+1));
	cstr_ncopy(&r, s+o, l);
	r[l] = 0;

	return r;
}

char
*cstr_substr(s0, s1, e)
	const char *const s0;
	const size_t s1, e;
{
	return cstr_bashslice(s0, s1, e-s1);
}

char
*cstr_lcut(s, n)
	const char *const s;
	const size_t n;
{
	return cstr_substr(s, n, cstr_len(s));
}

char
*cstr_rcut(s, n)
	const char *const s;
	const size_t n;
{
	return cstr_substr(s, 0, n);
}

uint8_t
cstr_nequals(s0, s1, n)
	const char *const s0, *const s1;
	size_t n;
{
	while (n--)
		if (s0[n] != s1[n])
			return 0;

	return 1;
}

uint8_t
cstr_equals(s0, s1)
	const char *const s0, *const s1;
{
	const size_t l0 = cstr_len(s0);
	
	if (l0 != cstr_len(s1))
		return 0;

	return cstr_nequals(s0, s1, l0);
}

void
cstr_to_reversed(s)
	char *const *const s;
{
	size_t i0 = 0;
	size_t i1 = cstr_len(*s)-1;

	while (i0 < i1) {
		const char c = (*s)[i0];
		(*s)[i0] = (*s)[i1];
		(*s)[i1] = c;
		++i0;
		--i1;
	}
}

char
*cstr_reverse(s)
	const char *const s;
{
	char *const r = cstr_dup(s);
	cstr_to_reversed(&r);
	return r;
}

uint8_t
cstr_contains(s0, s1)
	const char *const s0, *const s1;
{
	const size_t l0 = cstr_len(s0);
	const size_t l1 = cstr_len(s1);

	if (l0 < l1)
		return 0;

	const size_t e = l0 - l1;
	size_t i = 0;

	while (i <= e) {
		if (s0[i] == s1[0])
			if (cstr_nequals(s0+i, s1, l1))
				return 1;
				
		++i;
	}

	return 0;
}

uint8_t
cstr_startswith(s0, s1)
	const char *const s0, *const s1;
{
	const size_t l1 = cstr_len(s1);

	if (cstr_len(s0) < l1)
		return 0;
	
	return cstr_nequals(s0, s1, l1);
}

uint8_t
cstr_endswith(s0, s1)
	const char *const s0, *const s1;
{
	const size_t l0 = cstr_len(s0);
	const size_t l1 = cstr_len(s1);

	if (l0 < l1)
		return 0;

	return cstr_equals(s0+(l0-l1), s1);
}

char
*cstr_replace_once(s0, s1, s2)
	const char *const s0, *const s1, *const s2;
{
	if (!cstr_contains(s0, s1))
		return NULL;

	const size_t l0 = cstr_len(s0);
	const size_t l1 = cstr_len(s1);

	if (l0 < l1)
		return NULL;
	
	if (cstr_startswith(s0, s1))
		return cstr_concat(s2, s0+l1);

	if (cstr_endswith(s0, s1)) {
		char *t0 = cstr_substr(s0, 0, l0-l1);
		cstr_append(&t0, s2);
		return t0;
	}

	size_t i = 0;
	const size_t e = l0 - l1;

	while (i <= e) {
		if (s0[i] == s1[0]) {
			if (cstr_nequals(s0+i, s1, l1)) {
				char *t0 = cstr_substr(s0, 0, i);
				cstr_append(&t0, s2);
				cstr_append(&t0, s0+i+l1);
				return t0;
			}
		}
		++i;
	}

	return NULL;
}

char
*cstr_replace(s0, s1, s2)
	const char *const s0, *const s1, *const s2;
{
	char *r0 = cstr_replace_once(s0, s1, s2);

	while (cstr_contains(r0, s1)) {
		char *r1 = cstr_replace_once(r0, s1, s2);
		free(r0);
		r0 = r1;
	}

	return r0;
}

uint8_t
char_is_upcase(c)
	const char c;
{
	return c >= 'A' && c <= 'Z';
}

uint8_t
char_is_downcase(c)
	const char c;
{
	return c >= 'a' && c <= 'z';
}

uint8_t
char_is_space(c)
	const char c;
{
	return c == ' ' || c == '\t' || c == '\n';
}

uint8_t
char_is_alpha(c)
	const char c;
{
	return char_is_upcase(c) || char_is_downcase(c);
}

uint8_t
char_is_digit(c)
	const char c;
{
	return c >= '0' && c <= '9';
}

uint8_t
char_is_uphex(c)
	const char c;
{
	return char_is_digit(c) || (c >= 'A' && c <= 'F');
}

uint8_t
char_is_downhex(c)
	const char c;
{
	return char_is_digit(c) || (c >= 'a' && c <= 'f');
}

uint8_t
char_is_hex(c)
	const char c;
{
	return char_is_uphex(c) || char_is_downhex(c);
}

uint8_t
char_is_octal(c)
	const char c;
{
	return c >= '0' && c <= '7';
}

uint8_t
char_is_binary(c)
	const char c;
{
	return c == '0' || c == '1';
}

uint8_t
char_is_pental(c)
	const char c;
{
	return c >= '0' && c <= '4';
}

char
char_to_upcase(c)
	const char c;
{
	if (char_is_downcase(c))
		return c + char_case_offset;

	return c;
}

char
char_to_downcase(c)
	const char c;
{
	if (char_is_upcase(c))
		return c - char_case_offset;

	return c;
}

uint8_t
char_to_digit(c)
	const char c;
{
	if (!char_is_digit(c))
		return 0;

	return c-'0';
}

uint8_t
char_to_uphex(c)
	const char c;
{
	if (!char_is_uphex(c))
		return 0;

	if (char_is_digit(c))
		return char_to_digit(c);

	return c - 'A' + 10;
}

uint8_t
char_to_downhex(c)
	const char c;
{
	if (!char_is_downhex(c))
		return 0;

	if (char_is_digit(c))
		return char_to_digit(c);

	return c - 'a' + 10;
}

uint8_t
char_to_hex(c)
	const char c;
{
	if (!char_is_hex(c))
		return 0;

	if (char_is_digit(c))
		return char_to_digit(c);

	if (char_is_uphex(c))
		return char_to_uphex(c);

	return char_to_downhex(c);
}

uint8_t
char_to_octal(c)
	const char c;
{
	if (!char_is_octal(c))
		return 0;

	return char_to_digit(c);
}

uint8_t
char_to_binary(c)
	const char c;
{
	if (!char_is_binary(c))
		return 0;

	return c == '1';
}

uint8_t
char_to_pental(c)
	const char c;
{
	if (!char_is_pental(c))
		return 0;

	return char_to_digit(c);
}

void
cstr_to_upcase(s)
	char *const *const s;
{
	size_t l = cstr_len(*s);

	while (l--)
		(*s)[l] = char_to_upcase((*s)[l]);
}

void
cstr_to_downcase(s)
	char *const *const s;
{
	size_t l = cstr_len(*s);

	while (l--)
		(*s)[l] -= char_to_downcase((*s)[l]);
}

char
*cstr_upcase(s)
	const char *const s;
{
	char *const r = cstr_dup(s);
	cstr_to_upcase(&r);
	return r;
}

char
*cstr_downcase(s)
	const char *const s;
{
	char *const r = cstr_dup(s);
	cstr_to_downcase(&r);
	return r;
}

uint8_t
cstr_is_upcase(s)
	const char *const s;
{
	char *const t = cstr_upcase(s);
	const uint8_t r = cstr_equals(s, t);
	free(t);
	return r;
}

uint8_t
cstr_is_downcase(s)
	const char *const s;
{
	char *const t = cstr_downcase(s);
	const uint8_t r = cstr_equals(s, t);
	free(t);
	return r;
}

char
*cstr_mul(s, t)
	const char *const s;
	size_t t;
{
	char *r = malloc(sizeof(char)*0);
	char *unit = cstr_dup(s);
	
	while (t) {
		while (t%2 == 0 && t) {
			cstr_append(&unit, unit);
			t /= 2;
		}
		
		cstr_append(&r, unit);
		--t;
	}

	free(unit);

	return r;
}

char
*cstr_ltrim(s)
	const char *const s;
{
	const char *p = (const char*)s;
	
	while (char_is_space(*p++))
		/* VOID */;

	return cstr_lcut(s, p - s - 1);
}

char
*cstr_rtrim(s)
	const char *const s;
{
	const size_t l = cstr_len(s);
	const char *p = (const char*)s + l;
	
	while (char_is_space(*p--))
		/* VOID */;

	return cstr_rcut(s, l - (p - s - 1));
}

char
*cstr_trim(s)
	const char *const s;
{
	const char *p0 = (const char*)s;
	const size_t l = cstr_len(s);
	
	while (char_is_space(*p0++))
		/* VOID */;

	const size_t i0 = p0 - s - 1;
	const char *p1 = (const char*)s + l - 1;
	
	while (char_is_space(*p1--))
		/* VOID */;

	const size_t i1 = p1 - s + 2;
	return cstr_substr(s, i0, i1);
}

char
*cstr_lpad(s, n)
	const char *const s;
	const size_t n;
{
	char *t = cstr_mul(" ", n);
	cstr_append(&t, s);
	return t;
}

char
*cstr_rpad(s, n)
	const char *const s;
	const size_t n;
{
	char *const t = cstr_mul(" ", n);
	char *const r = cstr_concat(s, t);
	free(t);
	return r;
}

char
*cstr_pad(s, n0, n1)
	const char *const s;
	const size_t n0, n1;
{
	char *r = cstr_lpad(s, n0);
	char *const t = cstr_mul(" ", n1);
	cstr_append(&r, t);
	free(t);
	return r;
}

uint8_t
cstr_is_digit(s)
	const char *const s;
{
	size_t l = cstr_len(s);

	while (l--)
		if (!char_is_digit(s[l]))
			return 0;

	return 1;
}

uint8_t
cstr_is_uphex(s)
	const char *const s;
{
	size_t l = cstr_len(s);

	while (l--)
		if (!char_is_uphex(s[l]))
			return 0;

	return 1;
}

uint8_t
cstr_is_downhex(s)
	const char *const s;
{
	size_t l = cstr_len(s);

	while (l--)
		if (!char_is_downhex(s[l]))
			return 0;

	return 1;
}

uint8_t
cstr_is_hex(s)
	const char *const s;
{
	size_t l = cstr_len(s);

	while (l--)
		if (!char_is_hex(s[l]))
			return 0;

	return 1;
}

uint8_t
cstr_is_octal(s)
	const char *const s;
{
	size_t l = cstr_len(s);

	while (l--)
		if (!char_is_octal(s[l]))
			return 0;

	return 1;
}

uint8_t
cstr_is_binary(s)
	const char *const s;
{
	size_t l = cstr_len(s);

	while (l--)
		if (!char_is_binary(s[l]))
			return 0;

	return 1;
}

uint8_t
cstr_is_pental(s)
	const char *const s;
{
	size_t l = cstr_len(s);

	while (l--)
		if (!char_is_pental(s[l]))
			return 0;

	return 1;
}

uint64_t
cstr_to_uint(s)
	const char *const s;
{
	if (!cstr_is_digit(s))
		return 0;

	uint64_t r = 0;
  uint64_t m = 1;
	size_t l = cstr_len(s);

  while (l--) {
  	r += m * (s[l]-'0');
  	m *= 10;
  }

  return r;
}

int64_t
cstr_to_int(s)
	const char *const s;
{
	const char *p = (const char *)s;
	uint64_t m = 1;
	uint64_t r = 0;

	if (*p == '-') {
		++p;
		m = -1;
	}

	if (!cstr_is_digit(p))
		return 0;

	size_t l = cstr_len(p);

  while (l--) {
  	r += m * char_to_digit(p[l]);
  	m *= 10;
  }

  return r;
}

uint64_t
cstr_to_uphex(s)
	const char *const s;
{
	if (!cstr_is_uphex(s))
		return 0;
		
	uint64_t r = 0;
	uint64_t m = 1;
	size_t l = cstr_len(s);

	while (l--) {
		r += m * char_to_uphex(s[l]);
		m *= 16;
	}

	return r;
}

uint64_t
cstr_to_downhex(s)
	const char *const s;
{
	if (!cstr_is_uphex(s))
		return 0;
		
	uint64_t r = 0;
	uint64_t m = 1;
	size_t l = cstr_len(s);

	while (l--) {
		r += m * char_to_downhex(s[l]);
		m *= 16;
	}

	return r;
}

uint64_t
cstr_to_hex(s)
	const char *const s;
{
	if (!cstr_is_hex(s))
		return 0;
		
	uint64_t r = 0;
	uint64_t m = 1;
	size_t l = cstr_len(s);

	while (l--) {
		r += m * char_to_hex(s[l]);
		m *= 16;
	}

	return r;
}

uint64_t
cstr_to_octal(s)
	const char *const s;
{
	if (!cstr_is_octal(s))
		return 0;
		
	uint64_t r = 0;
	uint64_t m = 1;
	size_t l = cstr_len(s);

	while (l--) {
		r += m * char_to_octal(s[l]);
		m *= 8;
	}

	return r;
}

uint64_t
cstr_to_binary(s)
	const char *const s;
{
	if (!cstr_is_binary(s))
		return 0;
		
	uint64_t r = 0;
	uint64_t m = 1;
	size_t l = cstr_len(s);

	while (l--) {
		r += m * char_to_binary(s[l]);
		m *= 2;
	}

	return r;
}

uint64_t
cstr_to_pental(s)
	const char *const s;
{
	if (!cstr_is_pental(s))
		return 0;
		
	uint64_t r = 0;
	uint64_t m = 1;
	size_t l = cstr_len(s);

	while (l--) {
		r += m * char_to_pental(s[l]);
		m *= 2;
	}

	return r;
}

size_t
cstrarr_len(a)
	const char *const *const a;
{
	const char *const *p = (const char *const *)a;

	while (*p++ != NULL)
		/* VOID */;

	return p - a - 1;
}

void
cstrarr_append(a, s)
	char ***const a, *const s;
{
	const size_t l = cstrarr_len((const char *const *const) *a);
	*a = realloc(*a, sizeof(char*) * (l+2));
	(*a)[l] = s;
	(*a)[l+1] = NULL;
}

void
cstrarr_prepend(a, s)
	char ***const a, *const s;
{
	const size_t l = cstrarr_len((const char *const *const) *a);
	*a = realloc(*a, sizeof(char*) * (l+2));

	size_t i = 0;

	while (i < l) {
		(*a)[i+1] = (*a)[i];
		++i;
	}
	
	(*a)[0] = s;
	(*a)[l+1] = NULL;
}

void
cstrarr_push(a, s)
	char ***const a;
	const char *const s;
{
	cstrarr_append(a, cstr_dup(s));
}

void
cstrarr_pushb(a, s)
	char ***const a;
	const char *const s;
{
	cstrarr_prepend(a, cstr_dup(s));
}

void
cstrarr_append_cstrarr(a0, a1)
	char ***const a0, **const a1;
{
	const size_t l0 = cstrarr_len((const char *const *const) *a0);
	const size_t l1 = cstrarr_len((const char *const *const) a1);
	const size_t l2 = l0 + l1;

	*a0 = realloc(*a0, sizeof(char*) * (l2+1));

	size_t i = 0;

	while (i < l1) {
		(*a0)[i+l0] = a1[i];
		++i;
	}

	(*a0)[l2] = NULL;
}

void
cstrarr_push_cstrarr(a0, a1)
	char ***const a0, **const a1;
{
	const size_t l0 = cstrarr_len((const char *const *const) *a0);
	const size_t l1 = cstrarr_len((const char *const *const) a1);
	const size_t l2 = l0 + l1;

	*a0 = realloc(*a0, sizeof(char*) * (l2+1));

	size_t i = 0;

	while (i < l1) {
		(*a0)[i+l0] = cstr_dup(a1[i]);
		++i;
	}

	(*a0)[l2] = NULL;
}

char
*cstrarr_pop(a)
	char ***const a;
{
	const size_t l = cstrarr_len((const char *const *const)*a);
	char *r = (*a)[l-1];
	*a = realloc(*a, sizeof(char*) * l);
	(*a)[l-1] = NULL;
	return r;
}

char
*cstrarr_shift(a)
	char ***const a;
{
	const size_t l = cstrarr_len((const char *const *const)*a);
	char *r = (*a)[0];

	size_t i = 1;

	while (i < l) {
		(*a)[i-1] = (*a)[i];
		++i;
	}
	
	*a = realloc(*a, sizeof(char*) * l);
	(*a)[l-1] = NULL;
	return r;
}

size_t
cstr_find_char(s, c)
	const char *const s, c;
{
	const size_t l = cstr_len(s);
	size_t i = 0;

	while (i < l)
		if (s[i++] == c)
			return i;

	return 0;
}

size_t
cstr_find_space(s)
	const char *const s;
{
	const size_t l = cstr_len(s);
	size_t i = 0;

	while (i < l)
		if (char_is_space(s[i++]))
			return i;

	return 0;
}

#endif /* !CSTR_C */
