/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:47:36 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/06 09:27:21 by ancanale         ###   ########.fr       */
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
		return (execute_pwd());
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
