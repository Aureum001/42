/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:47:55 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 11:09:05 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_insert_position(char **envp, char *new_entry)
{
	int		i;
	char	*eq_pos;
	int		key_len;

	eq_pos = ft_strchr(new_entry, '=');
	if (!eq_pos)
		key_len = ft_strlen(new_entry);
	else
		key_len = eq_pos - new_entry;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], new_entry, key_len) > 0
			&& (envp[i][key_len] == '=' || envp[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (i);
}

void	add_entries(t_cmd *cmd, char *new_entry)
{
	char	**new_env;
	int		count;
	int		pos;
	int		i;

	count = 0;
	while (cmd->envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return ((void)(free(new_entry)));
	pos = find_insert_position(cmd->envp, new_entry);
	i = -1;
	while (++i < pos)
		new_env[i] = cmd->envp[i];
	new_env[pos] = new_entry;
	while (i < count)
	{
		new_env[i + 1] = cmd->envp[i];
		i++;
	}
	new_env[count + 1] = NULL;
	free(cmd->envp);
	cmd->envp = new_env;
}

void	update_env_var(t_cmd *cmd, char *name, char *value)
{
	int		index;
	char	*new_entry;
	int		name_len;
	int		value_len;

	index = find_env_index(cmd->envp, name);
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_entry = malloc(name_len + 1 + value_len + 1);
	if (!new_entry)
		return ;
	ft_strlcpy(new_entry, name, name_len + 1);
	new_entry[name_len] = '=';
	ft_strlcpy(new_entry + name_len + 1, value, value_len + 1);
	if (index != -1)
	{
		free(cmd->envp[index]);
		cmd->envp[index] = new_entry;
	}
	else
		add_entries(cmd, new_entry);
}

static char	**create_new_env_array(char **old_env, int index_to_remove)
{
	int		count;
	char	**new_env;
	int		i;
	int		j;

	count = 0;
	while (old_env[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	j = 0;
	i = 0;
	while (i < count)
	{
		if (i != index_to_remove)
		{
			new_env[j] = old_env[i];
			j++;
		}
		else
			free(old_env[i]);
		i++;
	}
	return (new_env[j] = NULL, new_env);
}

void	remove_env_var(t_cmd *cmd, char *name)
{
	int		index;
	char	**new_env;

	index = find_env_index(cmd->envp, name);
	if (index == -1)
		return ;
	new_env = create_new_env_array(cmd->envp, index);
	if (!new_env)
		return ;
	free(cmd->envp);
	cmd->envp = new_env;
}
