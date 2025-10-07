/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:50:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/07 11:56:07 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_var(char *env_var)
{
	char	*equals;
	char	*name;
	char	*value;

	equals = ft_strchr(env_var, '=');
	ft_putstr_fd("declare -x ", 1);
	if (!equals)
	{
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	name = ft_substr(env_var, 0, equals - env_var);
	if (!name)
		return ;
	value = equals + 1;
	ft_putstr_fd(name, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(value, 1);
	ft_putstr_fd("\"\n", 1);
	free(name);
}

static int	env_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		if (*s1 == '=')
			return (0);
		s1++;
		s2++;
	}
	if (*s1 == '=' || *s2 == '=')
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	sort_env_copy(char **env_copy, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (env_strcmp(env_copy[i], env_copy[j]) > 0)
			{
				tmp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	**copy_env_array(char **envp, int *count)
{
	char	**env_copy;
	int		i;

	*count = 0;
	while (envp[*count])
		(*count)++;
	env_copy = malloc(sizeof(char *) * (*count + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		env_copy[i] = envp[i];
		i++;
	}
	env_copy[*count] = NULL;
	return (env_copy);
}

void	print_all_env_vars(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	if (!envp)
		return ;
	env_copy = copy_env_array(envp, &count);
	if (!env_copy)
		return ;
	sort_env_copy(env_copy, count);
	i = 0;
	while (i < count)
	{
		print_export_var(env_copy[i]);
		i++;
	}
	free(env_copy);
}
