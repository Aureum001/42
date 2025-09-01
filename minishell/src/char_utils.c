#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ')
		return (1);
	if (c >= '\t' && c <= '\r')
		return (1);
	return (0);
}