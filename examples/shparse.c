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
	size_t o = 0;

	char **a = malloc(sizeof(char*) * 1);
	*a = NULL;
	
	while ((i = cstr_find_space(t0))) {
		if (*t0 == '"') {
			o = 1;
			i = cstr_find_char(t0+o, '"');
		}
	
		cstrarr_append(&a, cstr_bashslice(t0+o, 0, i-1));
		t1 = cstr_ltrim(t0+i+o);
		free(t0);
		t0 = t1;
		o = 0;
	}

	if (t0 != NULL && *t0)
		cstrarr_append(&a, t0);
	else
		free(t0);
	
	return a;
}

int
main(void)
	/* VOID */
{
	char **t = shparse("./hello  69 \"   6969  \" \"  123 \" 96 \" text \"");
	const size_t l = cstrarr_len((const char *const *const) t);

	size_t i = 0;
	while (i < l) {
		printf("'%s'\n", t[i]);
		free(t[i++]);
	}

	free(t);
}
