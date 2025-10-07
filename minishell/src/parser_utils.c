/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:48:46 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/07 10:59:06 by ancanale         ###   ########.fr       */
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

char	*expand_and_remove_quotes(char *value, char **envp, int last_status)
{
	int		len;
	char	*temp;
	char	*result;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	if (len >= 2 && value[0] == '\'' && value[len - 1] == '\'')
		result = ft_substr(value, 1, len - 2);
	else if (len >= 2 && value[0] == '"' && value[len - 1] == '"')
	{
		temp = ft_substr(value, 1, len - 2);
		result = expand_variables(temp, envp, last_status);
		free(temp);
	}
	else
		result = expand_variables(value, envp, last_status);
	return (result);
}
