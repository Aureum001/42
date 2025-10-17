/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:00:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 11:54:02 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quote(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_trailing_pipe(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		i++;
	}
	i--;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	if (i >= 0 && line[i] == '|' && !quote)
		return (1);
	return (0);
}

char	*join_with_newline(char *s1, char *s2)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, "\n");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s2);
	return (result);
}
