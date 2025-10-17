/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 10:03:00 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_executing;

static int	execute_builtin_if_simple(t_cmd *cmd, char ***envp_ptr)
{
	int		status;

	status = execute_builtin(cmd);
	*envp_ptr = cmd->envp;
	return (status);
}

static int	execute_pipeline(t_cmd *cmd_list)
{
	int		status;

	g_executing = 1;
	setup_exec_signals();
	status = executor(cmd_list);
	g_executing = 0;
	setup_interactive_signals();
	return (status);
}

int	process_line(char *input, char ***envp_ptr, int last_status)
{
	t_token	*tokens;
	t_cmd	*cmd_list;
	int		status;

	add_history(input);
	tokens = lexer(input);
	cmd_list = parser(tokens, *envp_ptr, last_status);
	if (cmd_list)
		process_all_heredocs(cmd_list);
	status = 0;
	if (cmd_list && is_builtin(cmd_list)
		&& !cmd_list->next && !cmd_list->redirs)
		status = execute_builtin_if_simple(cmd_list, envp_ptr);
	else if (cmd_list)
		status = execute_pipeline(cmd_list);
	free_tokens(tokens);
	free_cmd_list(cmd_list);
	return (status);
}
