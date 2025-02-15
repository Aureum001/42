#include "rush02.h"

int ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

char *ft_strdup(const char *src)
{
	int		len;
	char	*dup;
	int		i;

	len = 0;
	while (src[len])
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

unsigned long long ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char *ft_strtrim(char *str) {
	int	start;
	int	end;

	if (!str) {
		return NULL;
	}
	start = 0;
	end = ft_strlen(str) - 1;
	while ((str[start] == ' ' || str[start] == '\t' || str[start] == '\n'))
		start++;
	while (end > start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;
	if (start > end) 
		return ""; 
	str[end + 1] = '\0';
	return (char *)str + start;
}