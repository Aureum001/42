/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:47:31 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/06 10:04:00 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cd(t_cmd *cmd)
{
	char	*path;
	char	*cwd;

	if (cmd->argv[1] && cmd->argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	path = cmd->argv[1];
	if (!path)
	{
		path = get_env_value(cmd->envp, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("minishell: cd");
	else
		free(cwd);
	update_pwd_after_cd(cmd);
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

int	execute_pwd(t_cmd *cmd)
{
	char	cwd[1024];
	char	*pwd_env;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (cmd && cmd->envp)
	{
		pwd_env = get_env_value(cmd->envp, "PWD");
		if (pwd_env)
		{
			ft_putstr_fd(pwd_env, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	perror("minishell: pwd");
	return (1);
}

int	execute_export(t_cmd *cmd)
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

int	execute_unset(t_cmd *cmd)
{
	int	i;

	if (!cmd->argv[1])
		return (0);
	i = 1;
	while (cmd->argv[i])
	{
		remove_env_var(cmd, cmd->argv[i]);
		i++;
	}
	return (0);
}
