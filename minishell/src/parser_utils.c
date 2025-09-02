#include "minishell.h"

static char	*replace_and_rebuild(char **result_ptr, t_var_info *info, char **envp)
{
	char	*before;
	char	*after;
	char	*value;
	char	*temp;
	char	*new_result;
	int		index;

	index = find_env_index(envp, info->name);
	if (index == -1)
		return (info->end);
	value = envp[index] + ft_strlen(info->name) + 1;
	before = ft_substr(*result_ptr, 0, info->start - *result_ptr);
	after = ft_strdup(info->end);
	temp = ft_strjoin(before, value);
	new_result = ft_strjoin(temp, after);
	free(after);
	free(*result_ptr);
	*result_ptr = new_result;
	return (new_result + (info->start - *result_ptr) + ft_strlen(value));
}

char	*expand_variables(char *str, char **envp)
{
	char		*result;
	char		*search_pos;
	t_var_info	info;

	result = ft_strdup(str);
	search_pos = result;
	while (search_pos && *search_pos)
	{
		info.start = ft_strchr(search_pos, '$');
		if (!info.start)
			break ;
		info.end = info.start + 1;
		while (*info.end && (ft_isalnum(*info.end) || *info.end == '_'))
			info.end++;
		if (info.end == info.start + 1)
		{
			search_pos = info.end;
			continue ;
		}
		info.name = ft_substr(info.start, 1, info.end - (info.start + 1));
		search_pos = replace_and_rebuild(&result, &info, envp);
		free(info.name);
	}
	return (result);
}

char	*expand_and_remove_quotes(char *value, char **envp)
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
		result = expand_variables(temp, envp);
		free(temp);
	}
	else
		result = expand_variables(value, envp);
	return (result);
}