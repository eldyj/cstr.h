// sc means semicolon

#include "../src/cstr.h"
#include <stdio.h>
#include <stdlib.h>

char
**scsplit(s)
	const char *const s;
{
	char *t = cstr_trim(s);
	char *const tp = t;
	size_t i = 0;
	char **r = malloc(sizeof(char*) * 1);
	*r = NULL;

	while ((i = cstr_find_char(t, ';'))) {
		cstrarr_append(&r, cstr_substr(t, 0, i-1));
		t += i;
	}

	if (*t)
		cstrarr_append(&r, cstr_dup(t));
	
	free(tp);
	return r;
}

int
main(void)
	/* VOID */
{
	char **a = scsplit("1;123;32;123;43;64;45;345453");
	const size_t l = cstrarr_len((const char *const *const) a);
	size_t i = 0;

	while (i < l) {
		puts(a[i]);
		free(a[i++]);
	}

	free(a);
}
