// BUGGY VERSION:
/*
char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] != c)
		i++;
	if (s[i] == c)
		return s + i;
	else
		return (NULL);
}
*/
// BUGGY VERSION:
/*
void *ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
	return dest;
}
*/
// BUGGY VERSION:
/*
int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free (*s1);
	*s1 = tmp;
	return 1;
}
*/
// BUGGY VERSION:
/*
void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
	size_t i = ft_strlen((char *)src) -1;
	while (i >= 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return dest;
}
*/
// BUGGY VERSION:
/*
char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return NULL;
		b[read_ret] = 0;
	}
	if (!str_appen_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	return ret;
}
*/
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
// Fixed: handle NULL *s1 (first allocation)
int str_append_mem(char **s1, char *s2, size_t size2)
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
			return NULL;
		b[read_ret] = 0; //Manually add null terminator at position read_ret
		if (read_ret == 0)
			break;
	}
	if (tmp)
	{
		if (!str_append_mem(&ret, b, tmp - b + 1))
		{
			free(ret);
			return NULL;
		}
		// Move remaining buffer after newline to front
		ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	}
	else if (ft_strlen(b) > 0)
	{
		if (!str_append_str(&ret, b))
		{
			free(ret);
			return NULL;
		}
		b[0] = 0;
	}
	return ret;
}






