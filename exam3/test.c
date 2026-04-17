#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	float	x;
	float	y;
}	City;

typedef struct
{
	int		n;
	City	*cities;
	int		*used;
	float	*min_len;
}	t_tsp_ctx;

float	dist(City a, City b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return (sqrt(dx * dx + dy * dy));
}

void	solve(t_tsp_ctx *ctx, int depth, float curr_len, int *path)
{
	int		i;
	float	add;

	if (ctx->n == depth)
	{
		curr_len += dist(ctx->cities[path[ctx->n - 1]], ctx->cities[path[0]]);
		if (curr_len < *(ctx->min_len))
			*(ctx->min_len) = curr_len;
		return ;
	}
	i = 0;
	while (i < ctx->n)
	{
		if (!ctx->used[i])
		{
			ctx->used[i] = 1;
			path[depth] = i;
			add = 0;
			if (depth > 0)
				add = dist(ctx->cities[i], ctx->cities[path[depth - 1]]);
			solve(ctx, depth + 1, curr_len + add, path);
			ctx->used[i] = 0;
		}
		i++;
	}
}

int	main(void)
{
	int		n;
	float	min_len;
	int		*used;
	int		*path;
	City	cities[12];

	n = 0;
	while (n < 12 && fscanf(stdin, "%f, %f\n", &cities[n].x, &cities[n].y) == 2)
		n++;
	if (n == 0)
		return (0);
	min_len = 1e9;
	used = calloc(n, sizeof(int));
	if (!used)
		return (1);
	path = malloc(n * sizeof(int));
	if (!path)
		return (free(used), 1);
	t_tsp_ctx ctx = {n, cities, used, &min_len};
	solve(&ctx, 0, 0.0f, path);
	fprintf(stdout, "%.2f\n", min_len);
	free(path);
	free(used);
	return (0);
}
