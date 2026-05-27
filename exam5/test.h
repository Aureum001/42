#ifndef BSQ_H
#define BSQ_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
	char **grid;
	char empty;
	char obstacle;
	char full;
	int rows;
	int cols;
}	t_map;

int parse_header(FILE *fp, t_map *map);
void print_map(t_map *map);
void free_map(t_map *map);
int load_map(FILE *fp, t_map *map);
void solve(t_map *map);
int bsq(FILE *fp);

#endif