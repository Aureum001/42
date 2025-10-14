#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    float x, y;
} City;

// Calculate Euclidean distance between two cities
float dist(City a, City b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrtf(fabsf(dx * dx + dy * dy));
}

typedef struct {
	int n;
	City *cities;
	int *used;
	int *path;
	float *min_len;
} TspCtx;

void tsp_rec(TspCtx *ctx, int depth, float curr_len, int *path_buf) {
	if (depth == ctx->n) {
		curr_len += dist(ctx->cities[path_buf[ctx->n-1]], ctx->cities[path_buf[0]]);
		if (curr_len < *(ctx->min_len))
			*(ctx->min_len) = curr_len;
		return;
	}
	int i = 0;
	while (i < ctx->n) {
		if (!ctx->used[i]) {
			ctx->used[i] = 1;
			int *next_path = malloc(ctx->n * sizeof(int));
			if (!next_path) return;
			memcpy(next_path, path_buf, ctx->n * sizeof(int));
			next_path[depth] = i;
			float add = 0;
			if (depth > 0)
				add = dist(ctx->cities[path_buf[depth-1]], ctx->cities[i]);
			tsp_rec(ctx, depth + 1, curr_len + add, next_path);
			free(next_path);
			ctx->used[i] = 0;
		}
		i++;
	}
}

int main(void) {
	City cities[12];
	int n = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	while (n < 12 && (read = getline(&line, &len, stdin)) != -1) {
		if (sscanf(line, "%f, %f", &cities[n].x, &cities[n].y) == 2)
			n++;
	}
	free(line);
	if (n == 0)
		return 1;
	int *used = calloc(n, sizeof(int));
	int *path = malloc(n * sizeof(int));
	int *path_buf = malloc(n * sizeof(int));
	if (!used || !path || !path_buf)
		return 1;
	float min_len = 1e9;
	TspCtx ctx = { n, cities, used, path, &min_len };
	tsp_rec(&ctx, 0, 0.0f, path_buf);
	fprintf(stdout, "%.2f\n", min_len);
	free(used);
	free(path);
	free(path_buf);
	return 0;
}