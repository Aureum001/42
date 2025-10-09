#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int init_buffers(size_t pat_len, char **read_buf, char **pro_buf, char **remainder) {
	*read_buf = malloc(1024);
	if (!*read_buf)
	{
		perror("Error");
		return (1);
	}
	*pro_buf = malloc(1024 + pat_len);
	if (!*pro_buf)
	{
		free(*read_buf);
		perror("Error");
		return (1);
	}
	*remainder = malloc(pat_len);
	if (!*remainder)
	{
		free(*read_buf);
		free(*pro_buf);
		perror("Error");
		return (1);
	}
	return (0);
}

size_t combine_buffers(char *pro_buf, char *remainder, size_t rem_len, char *read_buf, ssize_t n) {
	memcpy(pro_buf, remainder, rem_len);
	memcpy(pro_buf + rem_len, read_buf, n);
	return (rem_len + n);
}

void	search_replace(char *pro_buf, size_t process_size, char *pattern, size_t pat_len)
{
	char	*pos;
	size_t	remaining;

	pos = pro_buf;
	remaining = process_size;
	while (1)
	{
		pos = memmem(pos, remaining, pattern, pat_len);
		if (!pos)
			break ;
		memset(pos, '*', pat_len);
		pos = pos + pat_len;
		remaining = process_size - (pos - pro_buf);
	}
}

int	write_safe(char *pro_buf, size_t process_size, size_t pat_len)
{
	size_t	to_write;
	ssize_t	written;

	to_write = 0;
	if (process_size >= pat_len)
		to_write = process_size - (pat_len - 1);
	written = write(1, pro_buf, to_write);
	if (written != (ssize_t)to_write)
		return (1);
	return (0);
}

void	update_remainder(char *pro_buf, size_t process_size, size_t pat_len, char *remainder, size_t *rem_len)
{
	if (process_size >= pat_len)
		*rem_len = pat_len - 1;
	else
		*rem_len = process_size;
	memcpy(remainder, pro_buf + (process_size - *rem_len), *rem_len);
}

int	process_input(char *read_buf, char *pro_buf, char *remainder, size_t *rem_len, char *pattern)
{
	ssize_t	n;
	size_t	pat_len;
	size_t	process_size;

	*rem_len = 0;
	pat_len = strlen(pattern);
	n = read(0, read_buf, 1024);
	while (n > 0)
	{
		process_size = combine_buffers(pro_buf, remainder, *rem_len, read_buf, n);
		search_replace(pro_buf, process_size, pattern, pat_len);
		if (write_safe(pro_buf, process_size, pat_len))
			return (1);
		update_remainder(pro_buf, process_size, pat_len, remainder, rem_len);
		n = read(0, read_buf, 1024);
	}
	if (n < 0)
		return (1);
	return (0);
}

int main(int argc, char **argv) {
	char *pattern;
	char *read_buf;
	char *pro_buf;
	char *remainder;
	size_t rem_len;

	if (argc != 2 || !argv[1][0])
		return 1;
	pattern = argv[1];
	if (init_buffers(strlen(pattern), &read_buf, &pro_buf, &remainder))
		return 1;
	rem_len = 0;
	if (process_input(read_buf, pro_buf, remainder, &rem_len, pattern))
		return 1;
	if (write(1, remainder, rem_len) != (ssize_t)rem_len) {
		perror("Error");
		free(read_buf);
		free(pro_buf);
		free(remainder);
		return 1;
	}
	free(read_buf);
	free(pro_buf);
	free(remainder);
	return 0;
}