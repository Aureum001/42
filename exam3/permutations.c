#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_isalpha(int c)
{
	return ((c >='A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

void	ft_swap(char *a, char *b)
{
	char	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *sort_string(char *s)
{
	int	len;
	int	swapped;
	int	i;

	len = ft_strlen(s);
	swapped = 1;
	while(swapped)
	{
		swapped = 0;
		i = 0;
		while (i < len - 1)
		{
			if (s[i] > s[i + 1])
			{
				ft_swap(&s[i], &s[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
	return (s);
}

void	permute(char *src, char	*res, int pos)
{
	int	src_len;
	int	i;

	src_len = ft_strlen(src);
	if (pos == src_len)
	{
		write(1, res, src_len);
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	while (i < src_len)
	{
		if (!ft_strchr(res, src[i]))
		{
			res[pos] = src[i];
			permute(src, res, pos + 1);
			res[pos] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	len;
	char	*res;
	char	*src;

	if (argc != 2)
		return (1);
	if (ft_strlen(argv[1]) == 0 || (argv[1][0] == ' ' && !argv[1][1]))
		return (0);
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isalpha(argv[1][i]))
			return (0);
		i++;
	}
	len = ft_strlen(argv[1]);
	res = calloc(len + 1, 1);
	if (!res)
		return (1);
	src = sort_string(argv[1]);
	permute(src, res, 0);
	free(res);
	return (0);
}