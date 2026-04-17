#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	float x, y;
} City;

typedef struct {
	int n;          // Number of cities
	City *cities;   // Array of city coordinates
	int *used;      // Track which cities are in current path
	float *min_len; // Pointer to minimum path length found
} TspCtx;

float dist(City a, City b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrtf(dx * dx + dy * dy);
}

void tsp_rec(TspCtx *ctx, int depth, float curr_len, int *path) {
	if (depth == ctx->n) {
		curr_len += dist(ctx->cities[path[ctx->n - 1]], ctx->cities[path[0]]);
		if (curr_len < *(ctx->min_len))
			*(ctx->min_len) = curr_len;
		return;
	}
	int i = 0;
	while (i < ctx->n) {
		if (!ctx->used[i]) {
			ctx->used[i] = 1;
			path[depth] = i;
			float add = 0;
			if (depth > 0)
				add = dist(ctx->cities[path[depth - 1]], ctx->cities[i]);
			tsp_rec(ctx, depth + 1, curr_len + add, path);
			ctx->used[i] = 0;
		}
		i++;
	}
}

int main(void) {
	City cities[12];
	int n = 0;

	while (n < 12 && fscanf(stdin, "%f, %f\n", &cities[n].x, &cities[n].y) == 2)
		n++;
	if (n == 0)
		return 1;
	int *used = calloc(n, sizeof(int));
	if (!used)
		return (1);
	int *path = malloc(n * sizeof(int));
	if (!path)
		return (free(used), 1);
	float min_len = 1e9;
	TspCtx ctx = { n, cities, used, &min_len };
	tsp_rec(&ctx, 0, 0.0f, path);
	fprintf(stdout, "%.2f\n", min_len);
	free(used);
	free(path);
	return 0;
}