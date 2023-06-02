#ifndef CSTR_C
#	define CSTR_C

#	include <stddef.h>
#	include <stdint.h>
#	include <stdlib.h>

char
*cstr_alloc(l)
	const size_t l;
{
	return malloc(sizeof(char) * (l+1));
}

char
*cstr_realloc(s, l)
	char *const s;
	const size_t l;
{
	return realloc(s, sizeof(char) * (l+1));
}

void
cstr_free(s)
	char *const s;
{
	free(s);
}

size_t
cstr_len(s)
	const char *const s;
{
	size_t i = 0;
	while (s[i++])
		/* VOID */;

	return i-1;
}

uint8_t
cstr_ncopy(s, b, n)
	const char *const s;
	char *const b;
	const size_t n;
{
	size_t i = 0;
	while (i < n) {
		if ((b[i] = s[i]) != s[i])
			return 1;
		
		++i;
	}

	return 0;
}


uint8_t
cstr_rncopy(s, b, n)
	const char *const s;
	char *const b;
	const size_t n;
{
	size_t i = n;
	
	while (i--)
		if ((b[i] = s[i]) != s[i])
			return 1;

	return 0;
}

uint8_t
cstr_copy(s, b)
	const char *const s;
	char *const b;
{
	return cstr_ncopy(s, b, cstr_len(s)+1);
}

uint8_t
cstr_rcopy(s, b)
	const char *const s;
	char *const b;
{
	return cstr_rncopy(s, b, cstr_len(s));
}

char
*cstr_dup(s)
	const char *const s;
{
	char *r = cstr_alloc(cstr_len(s));
	cstr_copy(s, r);
	return r;
}

uint8_t
cstr_put(s, c, p)
	char **const s;
	const char c;
	const size_t p;
{
	const size_t l = cstr_len(*s)+1;

	if (l-1 < p)
		return 1;
	
	*s = cstr_realloc(*s, l);
	
	if (cstr_rncopy(*s+p-1, *s+p, l-p))
		return 1;

	if (((*s)[p] = c) != c)
		return 1;

	return (*s)[l] = 0;
}

uint8_t
cstr_add(s, c)
	char **const s;
	const char c;
{
	const size_t l = cstr_len(*s)+1;
	*s = cstr_realloc(*s, l);
	
	if (((*s)[l-1] = c) != c)
		return 1;
	
	return (*s)[l] = 0;
}

uint8_t
cstr_prep(s, c)
	char **const s;
	const char c;
{
	const size_t l = cstr_len(*s)+1;
	*s = cstr_realloc(*s, l);
	
	if (cstr_rncopy(*s, *s+1, l))
		return 1;

	if ((**s = c) != c)
		return 1;
	
	return (*s)[l] = 0;
}

uint8_t
cstr_insert(s0, s1, p)
	char **const s0;
	const char *const s1;
	const size_t p;
{
	const size_t l0 = cstr_len(*s0);
	const size_t l1 = cstr_len(s1);
	const size_t nl = l0 + l1;

	*s0 = cstr_realloc(*s0, nl);
	if (cstr_rncopy(*s0+p, *s0+p+l1, l0-p+1))
		return 1;
	
	return cstr_ncopy(s1, *s0+p, l1);
}

uint8_t
cstr_append(s0, s1)
	char **const s0;
	const char *const s1;
{
	const size_t l0 = cstr_len(*s0);
	const size_t l1 = cstr_len(s1);
	const size_t nl = l0 + l1;

	*s0 = cstr_realloc(*s0, nl);
	return cstr_ncopy(s1, *s0+l0, l1);
}

uint8_t
cstr_prepend(s0, s1)
	char **const s0;
	const char *const s1;
{
	const size_t l0 = cstr_len(*s0);
	const size_t l1 = cstr_len(s1);
	const size_t nl = l0 + l1;

	*s0 = cstr_realloc(*s0, nl);
	if (cstr_rncopy(*s0, *s0+l1, l0+1))
		return 1;
	
	return cstr_ncopy(s1, *s0, l1);
}

uint8_t
cstr_rem(s, p)
	char **const s;
	const size_t p;
{
	const size_t l = cstr_len(*s);

	if (l < p)
		return 1;

	if (cstr_ncopy(*s+p+1, *s+p, l-p))
		return 1;

	*s = cstr_realloc(*s, l-1);
	return (*s)[l-1] = 0;
}

uint8_t
cstr_nrem(s, p, n)
	char **const s;
	const size_t p, n;
{
	const size_t l = cstr_len(*s);

	if (l < p+n)
		return 1;

	if (cstr_ncopy(*s+p+n, *s+p, l-p))
		return 1;

	*s = cstr_realloc(*s, l-n);
	return (*s)[l-n] = 0;
}

uint8_t
cstr_rshift(s, n)
	char **const s;
	const size_t n;
{
	const size_t l = cstr_len(*s);

	if (l < n)
		return 1;

	*s = cstr_realloc(*s, l-n);
	return (*s)[l-n] = 0;
}

uint8_t
cstr_lshift(s, n)
	char **const s;
	const size_t n;
{
	const size_t l = cstr_len(*s);
	const size_t nl = l-n; 

	if (l < n)
		return 1;

	if (cstr_ncopy(*s+n, *s, nl))
		return 1;

	*s = cstr_realloc(*s, nl);
	return (*s)[nl] = 0;
}

uint8_t
cstr_nequals(s0, s1, n)
	const char *const s0, *const s1;
	const size_t n;
{
	size_t i = n;
	while (i--)
		if (s0[i] != s1[i])
			return 0;

	return 1;
}

uint8_t
cstr_equals(s0, s1)
	const char *const s0, *const s1;
{
	size_t l0 = cstr_len(s0);
	if (l0 != cstr_len(s1))
		return 0;

	return cstr_nequals(s0, s1, l0);
}

uint8_t
cstr_startswith(s0, s1)
	const char *const s0, *const s1;
{
	size_t l1 = cstr_len(s1);
	if (l1 > cstr_len(s0))
		return 0;

	return cstr_nequals(s0, s1, l1);
}

uint8_t
cstr_endswith(s0, s1)
	const char *const s0, *const s1;
{
	size_t l0 = cstr_len(s0);
	size_t l1 = cstr_len(s1);
	if (l1 > l0)
		return 0;

	return cstr_nequals(s0+l0-l1, s1, l1);
}

size_t
cstr_contains(s0, s1)
	const char *const s0, *const s1;
{
	size_t l0 = cstr_len(s0);
	size_t l1 = cstr_len(s1);
	if (l1 > l0)
		return 0;

	size_t i = 0;
	size_t m = l0 - l1;
	while (i <= m)
		if (s0[i++] == *s1)
			if (cstr_nequals(s0+i-1, s1, l1))
				return i;

	return 0;
}

uint8_t
cstr_replace(s0, s1, s2)
	char **const s0;
	const char *const s1, *const s2;
{
	const size_t l1 = cstr_len(s1);
	const size_t l2 = cstr_len(s2);
	size_t i = 0;
	size_t o = 0;
	
	while ((i = cstr_contains(*s0+o, s1))) {
		if (cstr_nrem(s0, i-1+o, l1))
			return 1;
		
		if (cstr_insert(s0, s2, i-1+o))
			return 1;
		
		o += i-1+l2;
	}

	return 0;
}

uint8_t
cstr_bashslice_to(s, o, l, b)
	const char *const s;
	const size_t o, l;
	char *const b;
{
	return cstr_ncopy(s+o, b, l);
}

uint8_t
cstr_substr_to(s, p0, p1, b)
	const char *const s;
	const size_t p0, p1;
	char *const b;
{
	return cstr_ncopy(s+p0, b, p0-p1);
}

char
*cstr_bashslice(s, o, l)
	const char *const s;
	const size_t o, l;
{
	char *r = cstr_alloc(l);
	
	if (!cstr_bashslice_to(s, o, l, r))
		return r;
	
	cstr_free(r);
	return NULL;
}

char
*cstr_substr(s, p0, p1)
	const char *const s;
	const size_t p0, p1;
{
	char *r = cstr_alloc(p0-p1);
	
	if (!cstr_substr_to(s, p0, p1, r))
		return r;
	
	cstr_free(r);
	return NULL;
}

uint8_t
char_is_space(c)
	const char c;
{
	return c == ' ' || c == '\t' || c == '\n';
}

size_t
cstr_find_space_after(s, p)
	const char *const s;
	const size_t p;
{
	size_t i = p+1;
	size_t m = cstr_len(s);

	if (!s[p] || !s[i])
		return p;

	while (s[i] && !char_is_space(s[i]))
		++i;

	while (s[i] && char_is_space(s[i]))
		++i;

	if (i > m)
		return m;

	return i;
}

size_t
cstr_find_space_before(s, p)
	const char *const s;
	const size_t p;
{
	if (!p)
		return 0;

	size_t i = p-1;

	while (!char_is_space(s[i]) && i)
		--i;

	while (char_is_space(s[i]) && i)
		--i;

	if (!i)
		return 0;

	return ++i;
}

uint8_t
cstr_reverse(s)
	char *const s;
{
	size_t j = cstr_len(s) - 1;
	size_t i = 0;
	
	while (j > i) {
		const char t = s[j];
		if ((s[j] = s[i]) != s[i])
			return 1;

		if ((s[i] = t) != t)
			return 1;
		
		--j;
		++i;
	}

	return 0;
}

char
*cstr_reversed(s)
	const char *const s;
{
	char *const r = cstr_dup(s);
	if (!cstr_reverse(r))
		return r;

	cstr_free(r);
	return NULL;
}

char
*cstr_mul(s, n)
	const char *const s;
	const size_t n;
{
	char *r = cstr_dup(s);
	size_t i = 0;
	while (++i < n) {
		if (cstr_append(&r, s)) {
			free(r);
			return NULL;
		}
	}

	return r;
}

size_t
cstr_leading_spaces(s)
	const char *const s;
{
	size_t i = 0;
	while (char_is_space(s[i]))
		++i;

	return i;
}

size_t
cstr_trailing_spaces(s)
	const char *const s;
{
	const size_t l = cstr_len(s);
	const size_t m = l - 1;
	size_t i = 0;

	if (!l || !m)
		return 0;

	while (char_is_space(s[m-i]))
		++i;

	return i;
}

uint8_t
cstr_ltrim(s)
	char **const s;
{
	return cstr_lshift(s, cstr_leading_spaces(*s));
}

uint8_t
cstr_rtrim(s)
	char **const s;
{
	return cstr_rshift(s, cstr_trailing_spaces(*s));
}

uint8_t
cstr_trim(s)
	char **const s;
{
	if (!cstr_ltrim(s))
		return cstr_rtrim(s);

	return 1;
}

#endif /* !CSTR_C */
