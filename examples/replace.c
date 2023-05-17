#include "../src/cstr.h"
#include <stdio.h>
#include <stdlib.h>

int
main(void)
	/* VOID */
{
	char *s = cstr_replace("69,69;69,69;", "69", "96");
	puts(s);
	free(s);
}
