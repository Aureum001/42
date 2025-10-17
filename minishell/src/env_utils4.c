/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:00:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 10:50:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	export_with_value(t_cmd *cmd, char *arg, char *equal_pos)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, equal_pos - arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		print_export_error(arg);
		free(name);
		return (1);
	}
	value = equal_pos + 1;
	update_env_var(cmd, name, value);
	free(name);
	return (0);
}

static int	export_without_value(t_cmd *cmd, char *arg)
{
	char	*declared_entry;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (find_env_index(cmd->envp, arg) == -1)
	{
		declared_entry = ft_strdup(arg);
		if (declared_entry)
			add_entries(cmd, declared_entry);
	}
	return (0);
}

int	export_single_var(t_cmd *cmd, char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		return (export_with_value(cmd, arg, equal_pos));
	else
		return (export_without_value(cmd, arg));
}
