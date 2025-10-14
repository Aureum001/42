#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Struct for city coordinates
typedef struct {
	float x, y;
} City;

// Calculate Euclidean distance between two cities
float dist(City a, City b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrtf(dx * dx + dy * dy);
}

typedef struct {
	int n;
	City *cities;
	int *used;
	int *path;
	float *min_len;
} TspCtx;

void tsp_rec(TspCtx *ctx, int depth, float curr_len) {
	if (depth == ctx->n) {
		curr_len += dist(ctx->cities[ctx->path[ctx->n-1]], ctx->cities[ctx->path[0]]);
		if (curr_len < *(ctx->min_len))
			*(ctx->min_len) = curr_len;
		return;
	}
	int i = 0;
	while (i < ctx->n) {
		if (!ctx->used[i]) {
			ctx->used[i] = 1;
			ctx->path[depth] = i;
			float add = 0;
			if (depth > 0)
				add = dist(ctx->cities[ctx->path[depth-1]], ctx->cities[i]);
			tsp_rec(ctx, depth + 1, curr_len + add);
			ctx->used[i] = 0;
		}
		i++;
	}
}

int main(void) {
	City cities[12];
	int n = 0;
	// Read cities from stdin
	while (n < 12 && fscanf(stdin, "%f, %f\n", &cities[n].x, &cities[n].y) == 2)
		n++;
	if (n == 0)
		return 1;
	int *used = calloc(n, sizeof(int));
	int *path = malloc(n * sizeof(int));
	if (!used || !path)
		return 1;
	float min_len = 1e9;
	TspCtx ctx = { n, cities, used, path, &min_len };
	tsp_rec(&ctx, 0, 0.0f);
	fprintf(stdout, "%.2f\n", min_len);
	free(used);
	free(path);
	return 0;
}