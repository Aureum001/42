/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:47:36 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/06 10:08:43 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->argv[0], "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return (execute_cd(cmd));
	if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return (execute_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return (execute_pwd(cmd));
	if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
		return (execute_export(cmd));
	if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		return (execute_unset(cmd));
	if (ft_strncmp(cmd->argv[0], "exit", 4) == 0)
		return (execute_exit(cmd));
	if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
		return (execute_env(cmd));
	return (1);
}

static void	update_pwd(t_cmd *cmd, t_cmd *export_cmd, char *new_pwd_var)
{
	if (export_cmd)
	{
		export_cmd->argv = malloc(sizeof(char *) * 3);
		if (export_cmd->argv)
		{
			export_cmd->argv[0] = "export";
			export_cmd->argv[1] = new_pwd_var;
			export_cmd->argv[2] = NULL;
			export_cmd->envp = cmd->envp;
			execute_export(export_cmd);
			free(export_cmd->argv);
		}
		free(export_cmd);
	}
}

void	update_pwd_after_cd(t_cmd *cmd)
{
	char	cwd[1024];
	char	*new_pwd_var;
	t_cmd	*export_cmd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	new_pwd_var = malloc(4 + 1 + ft_strlen(cwd) + 1);
	if (!new_pwd_var)
		return ;
	ft_strlcpy(new_pwd_var, "PWD=", 5);
	ft_strlcat(new_pwd_var, cwd, 4 + 1 + ft_strlen(cwd) + 1);
	export_cmd = new_cmd();
	update_pwd(cmd, export_cmd, new_pwd_var);
	free(new_pwd_var);
}
