/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:47:50 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/06 09:56:08 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all_env_vars(char **envp)
{
	if (!envp)
		return ;
	while (*envp)
	{
		if (ft_strchr(*envp, '='))
		{
			ft_putstr_fd(*envp, 1);
			ft_putstr_fd("\n", 1);
		}
		envp++;
	}
}

int	find_env_index(char **env, char *name)
{
	int	i;
	int	len;

	if (!env)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**copy_env(char **envp)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_split(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

char	*get_env_value(char **envp, char *name)
{
	int		index;
	char	*equal_pos;

	if (!envp || !name)
		return (NULL);
	index = find_env_index(envp, name);
	if (index == -1)
		return (NULL);
	equal_pos = ft_strchr(envp[index], '=');
	if (!equal_pos)
		return (NULL);
	return (equal_pos + 1);
}
