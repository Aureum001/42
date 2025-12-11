#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

typedef struct s_filter_ctx
{
	char	*pattern;
	size_t	pat_len;
	char	buffer[4096];
	size_t	buffer_size;
	size_t	remaining;
}	t_filter_ctx;

int	init_filter_ctx(t_filter_ctx *ctx, char const *pat)
{
	size_t	len;

	len = strlen(pat);
	ctx->pattern = malloc(len + 1);
	if (!ctx->pattern)
		return (1);
	strcpy(ctx->pattern, pat);
	ctx->pat_len = len;
	ctx->buffer_size = 0;
	ctx->remaining = 0;
	return (0);
}

ssize_t filter_read(t_filter_ctx *ctx)
{
	return(read(0, ctx->buffer + ctx->remaining, sizeof(ctx->buffer) - ctx->remaining));
}

int	filter_write(t_filter_ctx *ctx, size_t write_size)
{
	if ((write(1, ctx->buffer, write_size)) != (ssize_t)write_size)
	{
		fprintf(stderr, "Error: ");
		perror("write");
		return (1);
	}
	return (0);
}

void	filter_update_remainder(t_filter_ctx *ctx)
{
	if (ctx->buffer_size >= ctx->pat_len - 1)
		ctx->remaining = ctx->pat_len - 1;
	else
		ctx->remaining = ctx->buffer_size;
	if (ctx->remaining > 0)
		memmove(ctx->buffer, ctx->buffer + ctx->buffer_size - ctx->remaining, ctx->remaining);
}

void	filter_replace_pattern(t_filter_ctx *ctx)
{
	void	*found;
	char	*search_start;
	size_t	search_len;
	size_t	offset;
	size_t	next_offset;

	search_len = ctx->buffer_size;
	search_start = ctx->buffer;
	while (search_len >= ctx->pat_len)
	{
		found = memmem(search_start, search_len, ctx->pattern, ctx->pat_len);
		if (!found)
			break ;
		offset = (char *)found - ctx->buffer;
		memset(ctx->buffer + offset, '*', ctx->pat_len);
		next_offset = offset + ctx->pat_len;
		search_len = ctx->buffer_size - next_offset;
		search_start = ctx->buffer + next_offset;
	}
}

int	main(int argc, char **argv)
{
	t_filter_ctx	filter;
	ssize_t		bytes_read;

	if (argc != 2 || !argv[1][0])
		return (1);
	if (init_filter_ctx(&filter, argv[1]))
		return (1);
	while (1)
	{
		bytes_read = filter_read(&filter);
		if (bytes_read < 0)
		{
			fprintf(stderr, "Error: ");
			perror("read");
			free(filter.pattern);
			return (1);
		}
		if (bytes_read == 0)
		{
			filter.buffer_size = filter.remaining;
			if(filter_write(&filter, filter.remaining))
			{
				free(filter.pattern);
				return (1);
			}
			break ;
		}
		filter.buffer_size = filter.remaining + (size_t)bytes_read;
		filter_replace_pattern(&filter);
		if(filter_write(&filter, filter.buffer_size - (filter.pat_len - 1)))
		{
			free(filter.pattern);
			return (1);
		}
		filter_update_remainder(&filter);
	}
	return (free(filter.pattern), 0);
}