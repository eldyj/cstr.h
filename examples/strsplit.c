#include "../src/cstr.h"
#include <stdio.h>
#include <stdlib.h>

int
main(void)
	/* VOID */
{
	char **a = cstr_split("justXDtextXDforXDtest", "XD");
	const size_t l = cstrarr_len((const char *const *const) a);

	size_t i = 0;
	while (i < l) {
		puts(a[i]);
		free(a[i++]);
	}
}
