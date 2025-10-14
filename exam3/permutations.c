#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Sorts the string in-place (bubble sort, allowed functions only)
void sort_str(char *s)
{
	int n = 0;
	while (s[n])
		n++;
	int i = 0;
	while (i < n - 1)
	{
		int j = 0;
		while (j < n - i - 1)
		{
			if (s[j] > s[j + 1])
			{
				char tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

// Backtracking to generate permutations
void permute(char *str, int len, char *perm, int *used)
{
	if (len == 0)
	{
		puts(perm);
		return;
	}
	int i = 0;
	while (str[i])
	{
		if (!used[i])
		{
			used[i] = 1;
			perm[len - 1] = str[i];
			permute(str, len - 1, perm, used);
			used[i] = 0;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	int len = 0;
	while (argv[1][len])
		len++;
	char *str = malloc(len + 1);
	if (!str)
		return 1;
	int i = 0;
	while (i < len)
	{
		str[i] = argv[1][i];
		i++;
	}
	str[len] = '\0';
	sort_str(str);
	char *perm = malloc(len + 1);
	int *used = calloc(len, sizeof(int));
	if (!perm || !used)
	{
		free(str);
		free(perm);
		free(used);
		return 1;
	}
	perm[len] = '\0';
	permute(str, len, perm, used);
	free(str);
	free(perm);
	free(used);
	return 0;
}
