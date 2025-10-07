/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:05:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/07 10:53:20 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_var_end(t_var_info *info)
{
	if (*info->end == '?')
		info->end++;
	else
		while (*info->end && (ft_isalnum(*info->end) || *info->end == '_'))
			info->end++;
}

char	*process_variable(char **result, char **search_pos,
			char **envp, int last_status)
{
	t_var_info	info;

	info.start = ft_strchr(*search_pos, '$');
	if (!info.start)
		return (NULL);
	info.end = info.start + 1;
	find_var_end(&info);
	if (info.end == info.start + 1)
		return (info.end);
	info.name = ft_substr(info.start, 1, info.end - (info.start + 1));
	*search_pos = replace_and_rebuild(result, &info, envp, last_status);
	free(info.name);
	return (*search_pos);
}

char	*build_replaced_string(char *before, char *value, char *after)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(before, value);
	result = ft_strjoin(temp, after);
	free(after);
	free(value);
	return (result);
}

char	*perform_string_replacement(char **result_ptr, t_var_info *info,
			char *value)
{
	char	*before;
	char	*after;
	char	*new_result;
	size_t	len;

	before = ft_substr(*result_ptr, 0, info->start - *result_ptr);
	after = ft_strdup(info->end);
	len = ft_strlen(before) + ft_strlen(value);
	new_result = build_replaced_string(before, value, after);
	free(*result_ptr);
	*result_ptr = new_result;
	return (new_result + len);
}

char	*replace_and_rebuild(char **result_ptr, t_var_info *info,
			char **envp, int last_status)
{
	char	*value;
	int		index;

	if (ft_strncmp(info->name, "?", 1) == 0)
		value = ft_itoa(last_status);
	else
	{
		index = find_env_index(envp, info->name);
		if (index == -1)
			value = ft_strdup("");
		else
			value = ft_strdup(envp[index] + ft_strlen(info->name) + 1);
	}
	return (perform_string_replacement(result_ptr, info, value));
}
