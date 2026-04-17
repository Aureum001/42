
/*
** bsq.h
**
** A single struct holds everything about the map:
**   - grid dimensions + character legend (parsed from the header line)
**   - the 2-D grid itself (NULL-terminated array of strings)
*/

#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct s_map
{
	int rows;	   /* number of rows declared in header    */
	int cols;	   /* width of every row (all must match)  */
	char empty;	   /* character representing an empty cell */
	char obstacle; /* character representing an obstacle   */
	char full;	   /* character used to fill the square    */
	char **grid;   /* NULL-terminated array of row strings */
} t_map;

int parse_header(char *line, t_map *map);
void free_map(t_map *map);
void print_map(t_map *map);
int load_map(FILE *fp, t_map *map);
void solve(t_map *map);
int bsq(FILE *fp);

#endif
