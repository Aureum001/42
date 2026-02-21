
/*
** bsq.h
**
** A single struct holds everything about the map:
**   - grid dimensions + character legend (parsed from the header line)
**   - the 2-D grid itself (NULL-terminated array of strings)
*/

#ifndef BSQ_H
#define BSQ_H

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_map
{
	int rows;	   /* number of rows declared in header    */
	int cols;	   /* width of every row (all must match)  */
	char empty;	   /* character representing an empty cell */
	char obstacle; /* character representing an obstacle   */
	char full;	   /* character used to fill the square    */
	char **grid;   /* NULL-terminated array of row strings */
} t_map;

/* Part 1 – read & validate the header line          */
int parse_header(char *line, t_map *map);

/* Part 2 – read & validate the map rows             */
int load_map(FILE *fp, t_map *map);

/* Part 3 – DP solver (fills map->grid in place)     */
void solve(t_map *map);

/* Part 4 – print the result                         */
void print_map(t_map *map);

/* Helpers                                           */
void free_map(t_map *map);
int bsq(FILE *fp);

#endif
