
#include "bsq.h"

/*
** Subject rule:
**   "When your program receives more than one map in argument,
**    each solution or 'map error' must be followed by a line break."
**
** So the extra blank line is only required when argc > 2.
** For a single file or stdin, no trailing blank line is added.
**
** BUG in the original: the condition checked (i < argc - 1) AFTER
** incrementing i, which skipped the blank line after the second-to-last
** file.  The fix: always print '\n' after each result when multi-file.
*/

static void run_file(char *path, int multi)
{
	FILE *fp;

	fp = fopen(path, "r");
	if (!fp || bsq(fp) == -1)
		fprintf(stderr, "map error\n");
	if (fp)
		fclose(fp);
	if (multi)
		fprintf(stdout, "\n");
}

int main(int argc, char *argv[])
{
	int i;

	if (argc == 1)
	{
		/* No arguments: read from standard input */
		if (bsq(stdin) == -1)
			fprintf(stderr, "map error\n");
	}
	else if (argc == 2)
	{
		/* Single file: no trailing blank line */
		run_file(argv[1], 0);
	}
	else
	{
		/* Multiple files: every result is followed by a blank line */
		i = 1;
		while (i < argc)
			run_file(argv[i++], 1);
	}
	return (0);
}
