/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:21 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/02 10:48:22 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_executing = 0;

static int	process_line(char *input, char ***envp_ptr)
{
	t_token	*tokens;
	t_cmd	*cmd_list;
	int		status;

	add_history(input);
	tokens = lexer(input);
	cmd_list = parser(tokens, *envp_ptr);
	status = 0;
	if (cmd_list && is_builtin(cmd_list) && !cmd_list->next)
	{
		status = execute_builtin(cmd_list);
		*envp_ptr = cmd_list->envp;
	}
	else if (cmd_list)
	{
		g_executing = 1;
		setup_exec_signals();
		status = executor(cmd_list);
		g_executing = 0;
		setup_interactive_signals();
	}
	free_tokens(tokens);
	free_cmd_list(cmd_list);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	int		last_status;
	char	**shell_envp;

	(void)argc;
	(void)argv;
	shell_envp = copy_env(envp);
	last_status = 0;
	setup_interactive_signals();
	while (1)
	{
		prompt = generate_prompt();
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			last_status = process_line(input, &shell_envp);
		free(input);
	}
	return (free_split(shell_envp), last_status);
}
