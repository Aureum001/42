#include "test.h"

int parse_header(FILE *fp, t_map *map)
{
	if (fscanf(fp, "%d %c %c %c", &map->rows, &map->empty, &map->obstacle, &map->full) != 4)
		return (-1);
	if (map->rows <= 0)
		return (-1);
	if (map->empty == map->obstacle || map->obstacle == map->full || map->full == map->empty)
		return (-1);
	if (map->empty < 32 || map->empty > 126 || map->obstacle < 32 || map->obstacle > 126 || map->full < 32 || map->full > 126)
		return (-1);
	return (0);
}

void print_map(t_map *map)
{
	int i = 0;
	while (i < map->rows)
		fprintf(stdout, "%s\n", map->grid[i++]);
}

void free_map(t_map *map)
{
	if (map->grid)
	{
		int i = 0;
		while (map->grid[i])
			free(map->grid[i++]);
		free(map->grid);
		map->grid = NULL;
	}
}

int load_map(FILE *fp, t_map *map)
{
	char *line;
	size_t cap;
	ssize_t len;
	int i;

	map->grid = calloc(map->rows + 1, sizeof(char*));
	if (!map->grid)
		return (-1);
	line = NULL;
	cap = 0;
	i = 0;
	getline(&line, &cap, fp);
	while (i < map->rows)
	{
		len = getline(&line, &cap, fp);
		if (len <= 0)
			break;
		if (line[len - 1] != '\n')
			break;
		line[--len] = 0;
		if (i == 0)
			map->cols = (int)len;
		else if (map->cols != (int)len)
			break;
		for (int j = 0; j < map->cols; j++)
		{
			if (line[j] != map->empty && line[j] != map->obstacle)
			{
				free(line);
				free_map(map);
				return(-1);
			}
		}
		map->grid[i] = malloc(len + 1);
		if (!map->grid[i])
			break;
		for (int k = 0; k < len + 1; k++)
			map->grid[i][k] = line[k];
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

void solve(t_map *map)
{
	int dp[map->rows][map->cols];
	int best_size = 0;
	int best_row = 0;
	int best_col = 0;
	int i = 0;
	int j;
	int m;

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
				m = dp[i - 1][j - 1];
				if (dp[i - 1][j] < m)
					m = dp[i - 1][j];
				if (dp[i][j - 1] < m)
					m = dp[i][j - 1];
				dp[i][j] = m + 1;
			}
			if (best_size < dp[i][j])
			{
				best_size = dp[i][j];
				best_row = i - best_size + 1;
				best_col = j - best_size + 1;
			}
			j++;
		}
		i++;
	}
	for (i = best_row; i < best_row + best_size; i++)
		for (j = best_col; j < best_col + best_size; j++)
			map->grid[i][j] = map->full;
}

int bsq(FILE *fp)
{
	t_map map;
	if (parse_header(fp, &map) == -1)
		return (-1);
	if (load_map(fp, &map) == -1)
		return (-1);
	solve(&map);
	print_map(&map);
	free_map(&map);
	return (0);
}

static void run_file(char *path)
{
	FILE *fp;
	fp = fopen(path, "r");
	if (!fp || bsq(fp) == -1)
		fprintf(stderr, "Error: invalid map");
	if (fp)
		fclose(fp);
}

int main(int argc, char *argv[])
{
	if (argc == 2)
		run_file(argv[1]);
	else
		fprintf(stdout, "Usage: ./bsq /map.txt");
	return (0);
}