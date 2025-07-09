#include "pipex.h"
#include <string.h>


static char	*join_path(const char *dir, const char *cmd)
{
	char *full;
	int len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	strcpy(full, dir);
	strcat(full, "/");
	strcat(full, cmd);
	return (full);
}

static void	free_paths(char **paths)
{
	int i = 0;
	if (!paths)
		return;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*full;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (!full)
			break;
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
