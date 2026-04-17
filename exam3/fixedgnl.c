#include "get_next_line.h"
// Fixed: Add null-terminator check to avoid infinite loop and out-of-bounds access
char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return s + i;
	return NULL;
}
// Fixed: memcpy must copy all n bytes, not n-1, and copy forward
void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}
size_t ft_strlen(char *s)
{
	size_t ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return ret;
}
int str_append_mem(char **s1, char *s2, size_t size2)
// Fixed: handle NULL *s1 (first allocation)
{
	size_t size1 = *s1 ? ft_strlen(*s1) : 0;
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}
int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}
// Fixed: proper memmove implementation (handle overlap)
void *ft_memmove(void *dest, const void *src, size_t n)
{
	char *d = (char *)dest;
	const char *s = (const char *)src;
	if (d == s || n == 0)
		return dest;
	if (d < s)
	{
		for (size_t i = 0; i < n; i++)
			d[i] = s[i];
	}
	else
	{
		for (size_t i = n; i > 0; i--)
			d[i - 1] = s[i - 1];
	}
	return dest;
}
// Fixed: spelling error, buffer management, and missing static BUFFER_SIZE definition
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp;
	int read_ret;
	while (1) //"Hello World\n Hey"
	{
		tmp = ft_strchr(b, '\n');
		if (tmp)
			break;
		if (!str_append_str(&ret, b)) //Like strjoin for ret and the buffer
			return NULL;
		read_ret = read(fd, b, BUFFER_SIZE); //read() OVERWRITES b from b[0]
		// Iteration 1: reads "Hello" (5 bytes) -> b = "Hello\0..."
		// Iteration 2: reads " Worl" (5 bytes) -> b = " Worl\0..." (overwrites "Hello")
		if (read_ret == -1)
		{
			free(ret);
			return NULL;
		}
		b[read_ret] = 0; //Manually add null terminator at position read_ret
		if (read_ret == 0)
		{
			return (ret && *ret) ? ret : NULL;
		}
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	// Move remaining buffer after newline to front
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	return ret;
}

int main(int argc, char **argv)
{
	int fd;
	char *line;
	int line_num = 1;

	if (argc == 1)
		fd = 0; // Read from stdin
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening file");
			return 1;
		}
	}

	while ((line = get_next_line(fd)))
	{
		printf("Line %d: %s\n", line_num++, line);
		free(line);
	}

	if (fd != 0)
		close(fd);

	return 0;
}
