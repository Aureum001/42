/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:48:46 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 09:57:35 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(char *str, char **envp, int last_status)
{
	char	*result;
	char	*search_pos;

	result = ft_strdup(str);
	search_pos = result;
	while (search_pos && *search_pos)
	{
		search_pos = process_variable(&result, &search_pos, envp, last_status);
		if (!search_pos)
			break ;
	}
	return (result);
}

static char	*process_quote_section(char *value, int *i,
			char **envp, int last_status)
{
	char	quote;
	int		start;
	char	*section;
	char	*expanded;

	quote = value[*i];
	start = ++(*i);
	while (value[*i] && value[*i] != quote)
		(*i)++;
	section = ft_substr(value, start, *i - start);
	if (value[*i] == quote)
		(*i)++;
	if (quote == '"')
	{
		expanded = expand_variables(section, envp, last_status);
		free(section);
		return (expanded);
	}
	return (section);
}

static char	*process_unquoted_section(char *value, int *i,
				char **envp, int last_status)
{
	int		start;
	char	*section;
	char	*expanded;

	start = *i;
	while (value[*i] && value[*i] != '\'' && value[*i] != '"')
		(*i)++;
	section = ft_substr(value, start, *i - start);
	expanded = expand_variables(section, envp, last_status);
	free(section);
	return (expanded);
}

char	*expand_and_remove_quotes(char *value, char **envp, int last_status)
{
	char	*result;
	char	*section;
	int		i;

	if (!value)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			section = process_quote_section(value, &i, envp, last_status);
		else
			section = process_unquoted_section(value, &i, envp, last_status);
		if (!section)
			return (free(result), NULL);
		result = ft_strjoin(result, section);
		free(section);
		if (!result)
			return (NULL);
	}
	return (result);
}
