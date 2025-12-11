#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// City coordinates structure
typedef struct {
	float x, y;
} City;

// Context for TSP recursion - groups all needed data
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

// Recursive backtracking to find shortest path visiting all cities
// DEPTH-FIRST: Goes deep into one path before trying alternatives
void tsp_rec(TspCtx *ctx, int depth, float curr_len, int *path) {
	// Base case: visited all cities, close the loop back to start
	if (depth == ctx->n) {
		curr_len += dist(ctx->cities[path[ctx->n - 1]], ctx->cities[path[0]]);
		if (curr_len < *(ctx->min_len))
			*(ctx->min_len) = curr_len;
		return;
	}
	
	// Try each unvisited city as next destination
	int i = 0;
	while (i < ctx->n) {
		if (!ctx->used[i]) {
			// COMMIT: Mark city as used for this entire subtree
			ctx->used[i] = 1;
			path[depth] = i;
			
			float add = 0;
			if (depth > 0)
				add = dist(ctx->cities[path[depth - 1]], ctx->cities[i]);
			
			// GO DEEP: Explore this path fully before alternatives
			tsp_rec(ctx, depth + 1, curr_len + add, path);
			
			// BACKTRACK: Unmark in REVERSE ORDER as recursion unwinds
			// When path 0→1→2→3 finishes, unmarks happen: 3, then 2, then 1, then 0
			ctx->used[i] = 0;
		}
		i++;
	}
}

int main(void) {
	City cities[12];
	int n = 0;
	
	// Read city coordinates from stdin using fscanf (allowed function)
	// Format: "x, y\n" for each city
	while (n < 12 && fscanf(stdin, "%f, %f\n", &cities[n].x, &cities[n].y) == 2)
		n++;
	
	// Need at least one city
	if (n == 0)
		return 1;
	
	// Allocate arrays for tracking
	int *used = calloc(n, sizeof(int));  // Which cities are in current path
	int *path = malloc(n * sizeof(int)); // Order of city visits
	if (!used || !path)
		return 1;
	
	// Initialize minimum length to large value
	float min_len = 1e9;
	
	// Set up context and start recursion
	TspCtx ctx = { n, cities, used, &min_len };
	tsp_rec(&ctx, 0, 0.0f, path);
	
	// Print result with 2 decimal places
	fprintf(stdout, "%.2f\n", min_len);
	
	// Clean up
	free(used);
	free(path);
	return 0;
}