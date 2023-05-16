#include "../src/cstr.h"
#include <stdio.h>
#include <stdlib.h>

char
**shparse(s)
	const char *const s;
{
	char *t0 = cstr_trim(s);
	char *t1 = NULL;
	size_t i = 0;

	char **a = malloc(sizeof(char*) * 1);
	*a = NULL;
	
	while ((i = cstr_find_space(t0))) {
		t1 = cstr_ltrim(t0+i);
		cstrarr_append(&a, cstr_bashslice(t0, 0, i));
		free(t0);
		t0 = t1;
	}

	cstrarr_append(&a, t0);
	return a;
}

int
main(void)
	/* VOID */
{
	char **t = shparse("./hello   69   96     10");
	const size_t l = cstrarr_len((const char *const *const) t);

	size_t i = 0;
	while (i < l) {
		puts(t[i]);
		free(t[i++]);
	}

	free(t);
}
