#include "../src/cstr.h"
#include <stdio.h>
#include <stdlib.h>

int
main(void)
	/* VOID */
{
	char **a = cstr_split("a,b,c,d,e", ",");
	cstrarr_reverse((const char **const *const) &a);
	char *s = cstrarr_join((const char *const *const) a, "\n");
	cstrarr_free(&a);
	puts(s);
	free(s);
}
