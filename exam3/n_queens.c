#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

// Print a solution: positions[i] is the row for queen in column i
void print_solution(int *positions, int n)
{
	int i = 0;
	while (i < n)
	{
		if (i > 0)
			fprintf(stdout, " ");
		fprintf(stdout, "%d", positions[i]);
		i++;
	}
	fprintf(stdout, "\n");
}

// Check if placing queen at (row, col) is safe
int is_safe(int *positions, int col, int row)
{
	int pcol = 0;
	while (pcol < col)
	{
		int prow = positions[pcol];
		int diff = prow - row;
		if (diff < 0)
			diff = -diff;
		if (prow == row || diff == col - pcol)
			return 0;
		pcol++;
	}
	return 1;
}

// Recursive backtracking
void solve(int *positions, int n, int col)
{
	int row;
	
	if (col == n)
	{
		print_solution(positions, n);
		return;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(positions, col, row))
		{
			positions[col] = row;
			solve(positions, n, col + 1);
		}
		row++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	int n = atoi(argv[1]);
	if (n < 1)
		return 0;
	int *positions = calloc(n, sizeof(int));
	if (!positions)
	{
		fprintf(stderr, "Error: ");
		perror("calloc");
		return 1;
	}
	solve(positions, n, 0);
	free(positions);
	return 0;
}
// ./nqueens 4