/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:51:18 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/07 11:50:27 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_cmd *cmd)
{
	int	status;

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

int	execute_env(t_cmd *cmd)
{
	if (cmd->argv[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (1);
	}
	print_env_vars(cmd->envp);
	return (0);
}
