/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:38:16 by ancanale          #+#    #+#             */
/*   Updated: 2025/07/30 09:32:13 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

static char	*join_path(const char *dir, const char *cmd)
{
	char	*full;
	int		len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	full[0] = '\0';
	ft_strlcat(full, dir, len);
	ft_strlcat(full, "/", len);
	ft_strlcat(full, cmd, len);
	return (full);
}

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	**get_paths_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*full;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (!full)
			break ;
		if (access(full, X_OK) == 0)
		{
			free_paths(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_paths(paths);
	return (NULL);
}
