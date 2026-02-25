
/*
** ============================================================
** BSQ  –  Find the Biggest SQuare on a map
** ============================================================
**
** ALGORITHM OVERVIEW
** ------------------
** We use a classic 2-D dynamic-programming trick:
**
**   dp[i][j]  =  side-length of the largest all-empty square
**                whose BOTTOM-RIGHT corner is at (i, j)
**
** Recurrence:
**   • if grid[i][j] == obstacle  →  dp[i][j] = 0
**   • if i == 0 || j == 0        →  dp[i][j] = 1  (border cell)
**   • otherwise                  →  dp[i][j] = min(dp[i-1][j],
**                                                   dp[i][j-1],
**                                                   dp[i-1][j-1]) + 1
**
** Why min(…)+1?  A square of side s at (i,j) requires three
** overlapping squares of side s-1:  above, left, and diagonal.
** The limiting one is the smallest of the three.
**
** Tie-breaking: we update the best only on STRICT improvement,
** so the first (top-most, then left-most) maximum wins.
** ============================================================
*/

#include "bsq.h"

/* ============================================================
** Part 1 – Parse the header line
** ============================================================
** Format (space-separated):  "<rows> <empty> <obstacle> <full>"
** Example:                    "9 . o x"
**
** Validation rules (from subject):
**   • rows >= 1
**   • all three chars are printable (32-126)
**   • all three chars are distinct
**
** Returns  0 on success,  -1 on any error.
** ============================================================ */
int parse_header(char *line, t_map *map)
{
	if (sscanf(line, "%d %c %c %c",
			   &map->rows, &map->empty, &map->obstacle, &map->full) != 4)
		return (-1);
	if (map->rows <= 0)
		return (-1);
	if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full)
		return (-1);
	if (map->empty < 32 || map->empty > 126 || map->obstacle < 32 || map->obstacle > 126 || map->full < 32 || map->full > 126)
		return (-1);
	return (0);
}

/* ============================================================
** Part 2 – Load and validate the map rows
** ============================================================
** After the header, read exactly map->rows lines with getline.
** For each line:
**   • strip the mandatory trailing '\n'  (no '\n' → invalid)
**   • every character must be empty or obstacle
**   • all lines must have the same width
**
** map->grid is a NULL-terminated array of heap-allocated strings.
** Returns  0 on success,  -1 on any error (grid is freed).
** ============================================================ */

/* Free a NULL-terminated grid (and the array itself). */
void free_map(t_map *map)
{
	int i;

	if (!map->grid)
		return;
	i = 0;
	while (map->grid[i])
		free(map->grid[i++]);
	free(map->grid);
	map->grid = NULL;
}

int load_map(FILE *fp, t_map *map)
{
	char *line;
	size_t cap;
	ssize_t len;
	int i;

	map->grid = calloc(map->rows + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	line = NULL;
	cap = 0;
	i = 0;
	while (i < map->rows)
	{
		len = getline(&line, &cap, fp);
		if (len <= 0)
			break;
		/* Strip the newline – its absence means the line is malformed */
		if (line[len - 1] != '\n')
			break;
		line[--len] = '\0';
		/* All rows must share the same width */
		if (i == 0)
			map->cols = (int)len;
		else if ((int)len != map->cols)
			break;
		/* Every character must be empty or obstacle */
		for (int j = 0; j < map->cols; j++)
		{
			if (line[j] != map->empty && line[j] != map->obstacle)
			{
				free(line);
				free_map(map);
				return (-1);
			}
		}
		map->grid[i] = strdup(line);
		if (!map->grid[i])
			break;
		i++;
	}
	free(line);
	if (i != map->rows || map->cols == 0)
	{
		free_map(map);
		return (-1);
	}
	return (0);
}

/* ============================================================
** Part 3 – Dynamic-programming solver
** ============================================================
** Build the dp table described at the top of this file.
** Track the BEST square as we go:
**   best_size  – largest side seen so far
**   best_row   – row of the top-left corner of that square
**   best_col   – col of the top-left corner of that square
**
** When we find dp[i][j] > best_size we record the NEW best.
** Because we scan top→bottom, left→right, the first
** occurrence of any given maximum size is always the
** top-most / left-most solution – exactly what the subject
** requires.
**
** After finding the best square, fill it in map->grid in-place
** so that print_map just needs to iterate the grid.
** ============================================================ */
void solve(t_map *map)
{
	/* Variable-length 2-D array on the stack (C99). */
	int dp[map->rows][map->cols];
	int best_size;
	int best_row;
	int best_col;
	int i;
	int j;
	int m;

	best_size = 0;
	best_row = 0;
	best_col = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] == map->obstacle)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			else
			{
				/* min of the three neighbours + 1 */
				m = dp[i - 1][j];
				if (dp[i][j - 1] < m)
					m = dp[i][j - 1];
				if (dp[i - 1][j - 1] < m)
					m = dp[i - 1][j - 1];
				dp[i][j] = m + 1;
			}
			/* Strict >  →  keep first (topmost / leftmost) maximum */
			if (dp[i][j] > best_size)
			{
				best_size = dp[i][j];
				best_row = i - dp[i][j] + 1; /* top-left row */
				best_col = j - dp[i][j] + 1; /* top-left col */
			}
			j++;
		}
		i++;
	}
	/* Fill the best square directly into the grid */
	for (i = best_row; i < best_row + best_size; i++)
		for (j = best_col; j < best_col + best_size; j++)
			map->grid[i][j] = map->full;
}

/* ============================================================
** Part 4 – Print the (already filled) map
** ============================================================
** Each row is printed with a trailing newline.
** The caller (bsq / main) adds the extra blank line required
** when multiple files are processed.
** ============================================================ */
void print_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->rows)
		fprintf(stdout, "%s\n", map->grid[i++]);
}

/* ============================================================
** Top-level entry point for one file/stream
** ============================================================
** 1. Read the header line.
** 2. Load the map.
** 3. Solve.
** 4. Print.
** Returns 0 on success, -1 on any error.
** ============================================================ */
int bsq(FILE *fp)
{
	t_map map;
	char *line;
	size_t cap;

	memset(&map, 0, sizeof(map));
	/* Read the header line */
	line = NULL;
	cap = 0;
	if (getline(&line, &cap, fp) <= 0)
	{
		free(line);
		return (-1);
	}
	if (parse_header(line, &map) == -1)
	{
		free(line);
		return (-1);
	}
	free(line);
	/* Load and validate map rows */
	if (load_map(fp, &map) == -1)
		return (-1);
	/* Solve and print */
	solve(&map);
	print_map(&map);
	free_map(&map);
	return (0);
}

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