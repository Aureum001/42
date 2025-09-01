#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	execute_cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = cmd->argv[1];
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	execute_echo(t_cmd *cmd)
{
	int	i;
	int	print_newline;

	i = 1;
	print_newline = 1;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i], "-n", 2) == 0)
	{
		print_newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (print_newline)
		ft_putstr_fd("\n", 1);
	return (0);
}

int execute_pwd()
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

int execute_export(t_cmd *cmd)
{
	int	i;

	if (!cmd->argv[1])
	{
		print_all_env_vars(cmd->envp);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (export_single_var(cmd, cmd->argv[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int execute_unset(t_cmd *cmd)
{
	int i;

	if (!cmd->argv[1]) return (0);
	i = 1;
	while (cmd->argv[i])
	{
		remove_env_var(cmd, cmd->argv[i]);
		i++;
	}
	return (0);
}

int execute_exit(t_cmd *cmd)
{
	int status;

	status = 0;
	if (cmd->argv[1])
	{
		if (cmd->argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		status = ft_atoi(cmd->argv[1]);
	}
	ft_putstr_fd("exit\n", 1);
	exit(status);
}

int execute_env(t_cmd *cmd)
{
	if (cmd->argv[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (1);
	}
	print_all_env_vars(cmd->envp);
	return (0);
}
