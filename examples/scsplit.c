// sc means semicolon

#include "../src/cstr.h"
#include <stdio.h>
#include <stdlib.h>

char
**scsplit(s)
	const char *const s;
{
	char *t0 = cstr_trim(s);
	char *t1 = NULL;
	char *const tp = t0;

	size_t i = 0;
	char **r = malloc(sizeof(char*) * 1);
	*r = NULL;

	while ((i = cstr_find_char(t0, ';'))) {
		t1 = cstr_substr(t0, 0, i-1);
		cstrarr_append(&r, t1);
		t0 += i;
	}

	free(tp);

	return r;
}

int
main(void)
	/* VOID */
{
	char **a = scsplit("1;123;32;123;43;64;45;345453;");
	const size_t l = cstrarr_len((const char *const *const) a);
	size_t i = 0;

	while (i < l) {
		puts(a[i]);
		free(a[i++]);
	}

	free(a);
}
