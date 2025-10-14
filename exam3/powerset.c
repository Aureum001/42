#include <stdlib.h>
#include <stdio.h>

// Print a subset in input order
void print_subset(int *subset, int subset_size)
{
	int i = 0;
	while (i < subset_size)
	{
		if (i > 0)
			printf(" ");
		printf("%d", subset[i]);
		i++;
	}
	printf("\n");
}

// Recursive backtracking to generate all subsets
void powerset(int *set, int set_size, int target, int idx, int *subset, int subset_size, int sum)
{
	if (idx == set_size)
	{
		if (sum == target)
			print_subset(subset, subset_size);
		return;
	}
	// Exclude current element
	powerset(set, set_size, target, idx + 1, subset, subset_size, sum);
	// Include current element
	subset[subset_size] = set[idx];
	powerset(set, set_size, target, idx + 1, subset, subset_size + 1, sum + set[idx]);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	int target = atoi(argv[1]);
	int set_size = argc - 2;
	int *set = malloc(set_size * sizeof(int));
	if (!set)
	{
		fprintf(stderr, "Error: ");
		perror("malloc");
		return 1;
	}
	int i = 0;
	while (i < set_size)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}
	int *subset = malloc(set_size * sizeof(int));
	if (!subset)
	{
		fprintf(stderr, "Error: ");
		perror("malloc");
		free(set);
		return 1;
	}
	powerset(set, set_size, target, 0, subset, 0, 0);
	free(set);
	free(subset);
	return 0;
}
