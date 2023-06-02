#include <cstr.h>
#include <stdio.h>

int
main(argc, argv)
	int argc;
	char *argv[argc];
{
	if (argc <= 1)
		return 1;

	cstr_reverse(argv[1]);
	puts(argv[1]);
	return 0;
}
