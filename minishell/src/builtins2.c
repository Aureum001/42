/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:51:18 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/29 12:11:11 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	execute_exit(t_cmd *cmd)
{
	int	status;

	status = 0;
	ft_putstr_fd("exit\n", 1);
	if (cmd->argv[1])
	{
		if (!is_valid_number(cmd->argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
		if (cmd->argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		status = ft_atoi(cmd->argv[1]);
	}
	return (status | (1 << 8));
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
