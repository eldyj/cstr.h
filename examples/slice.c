#include <cstr.h>
#include <stdio.h>
#include <stdlib.h>

int
main(argc, argv)
	int argc;
	char *argv[argc];
{
	if (argc-1 < 3)
		return 1;

	size_t o = atoi(argv[2]);
	size_t l = atoi(argv[3]);
	char *s = cstr_bashslice(argv[1], o, l);
	puts(s);
	cstr_free(s);
	
	return 0;
}
