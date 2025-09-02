#include "minishell.h"
#include <fcntl.h>

static int	open_redirection_files(t_cmd *cmd, int *in_fd, int *out_fd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN)
			*in_fd = open(redir->filename, O_RDONLY);
		else if (redir->type == TOKEN_REDIRECT_OUT)
			*out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_REDIRECT_APPEND)
			*out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*in_fd < 0 || *out_fd < 0)
		{
			perror("minishell");
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}

static int	apply_redirections(int in_fd, int out_fd, int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin < 0 || *saved_stdout < 0)
	{
		perror("dup");
		return (1);
	}
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) < 0)
			return (perror("dup2"), 1);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) < 0)
			return (perror("dup2"), 1);
		close(out_fd);
	}
	return (0);
}

static int	handle_builtin_redirections(t_cmd *cmd, int *saved_stdin, int *saved_stdout)
{
	int	in_fd;
	int	out_fd;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (open_redirection_files(cmd, &in_fd, &out_fd) != 0)
		return (1);
	if (apply_redirections(in_fd, out_fd, saved_stdin, saved_stdout) != 0)
		return (1);
	return (0);
}

void	restore_builtin_redirections(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	execute_builtin_with_redirections(t_cmd *cmd, char ***envp_ptr)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (!cmd->redirs)
	{
		status = execute_builtin(cmd);
		if (cmd->envp)
			*envp_ptr = cmd->envp;
		return (status);
	}
	if (handle_builtin_redirections(cmd, &saved_stdin, &saved_stdout) != 0)
		return (1);
	status = execute_builtin(cmd);
	if (cmd->envp)
		*envp_ptr = cmd->envp;
	restore_builtin_redirections(saved_stdin, saved_stdout);
	return (status);
}
