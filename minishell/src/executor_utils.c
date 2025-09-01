#include "minishell.h"

static char	*join_path(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	len_dir;
	size_t	len_cmd;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	full_path = malloc(len_dir + 1 + len_cmd + 1);
	if (!full_path)
		return (NULL);
	ft_memcpy(full_path, dir, len_dir);
	full_path[len_dir] = '/';
	ft_memcpy(full_path + len_dir + 1, cmd, len_cmd);
	full_path[len_dir + 1 + len_cmd] = '\0';
	return (full_path);
}

static char	**get_paths_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || cmd[0] == '\0' || ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_split(paths);
	return (NULL);
}

void	manage_parent_fds(int *in_fd, int pipefd[2], t_cmd *current_cmd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (current_cmd->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}

void	child_process(t_cmd *cmd, char **envp, int in_fd, int pipefd[2])
{
	int	out_fd;
	int	status;

	out_fd = STDOUT_FILENO;
	if (cmd->next)
	{
		close(pipefd[0]);
		out_fd = pipefd[1];
	}
	handle_redirections(cmd, &in_fd, &out_fd);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (is_builtin(cmd))
	{
		status = execute_builtin(cmd);
		exit(status);
	}
	else
		execute_command(cmd, envp);
}