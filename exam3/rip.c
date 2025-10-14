#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Step 1: Count minimum removals needed for balance
void count_removals(const char *s, int *rem_open, int *rem_close)
{
	int open = 0;
	*rem_open = 0;
	*rem_close = 0;
	int i = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				(*rem_close)++;
		}
		i++;
	}
	*rem_open = open;
}

// Step 2: Backtracking to generate all solutions
void solve(const char *s, int i, int open, int rem_open, int rem_close,
	char *out, int out_pos)
{
	if (s[i] == '\0')
	{
		if (open == 0 && rem_open == 0 && rem_close == 0)
		{
			out[out_pos] = '\0';
			puts(out);
		}
		return;
	}
	if (s[i] == '(')
	{
		// Option 1: Remove this '('
		if (rem_open > 0)
		{
			out[out_pos] = ' ';
			solve(s, i + 1, open, rem_open - 1, rem_close, out, out_pos + 1);
		}
		// Option 2: Keep this '('
		out[out_pos] = '(';
		solve(s, i + 1, open + 1, rem_open, rem_close, out, out_pos + 1);
	}
	else if (s[i] == ')')
	{
		// Option 1: Remove this ')'
		if (rem_close > 0)
		{
			out[out_pos] = ' ';
			solve(s, i + 1, open, rem_open, rem_close - 1, out, out_pos + 1);
		}
		// Option 2: Keep this ')', only if there's an unmatched '('
		if (open > 0)
		{
			out[out_pos] = ')';
			solve(s, i + 1, open - 1, rem_open, rem_close, out, out_pos + 1);
		}
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	const char *s = argv[1];
	int rem_open, rem_close;
	count_removals(s, &rem_open, &rem_close);
	int len = strlen(s);
	char *out = malloc(len + 1);
	if (!out)
		return 1;
	solve(s, 0, 0, rem_open, rem_close, out, 0);
	free(out);
	return 0;
}
