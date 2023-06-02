#include <cstr.h>
#include <stdio.h>

int
main(argc, argv)
	int argc;
	char *argv[argc];
{
	if (argc-1 < 3)
		return 1;

	char *s = cstr_dup(argv[1]);
	int r = cstr_replace(&s, argv[2], argv[3]);
	puts(s);
	cstr_free(s);
	return r;
}
