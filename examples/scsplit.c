#include "../src/cstr.h"
#include <stdio.h>
#include <stdlib.h>

int
main(void)
	/* VOID */
{
	char **a = cstr_split_char("1;123;32;123;43;64;45;345453", ';');
	char *s = cstrarr_join((const char *const *const) a, "\n");
	cstrarr_free(&a);
	puts(s);
	free(s);
}
