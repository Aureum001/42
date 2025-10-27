/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:21 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/27 09:38:54 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_input_line(void)
{
	char	*prompt;
	char	*input;

	prompt = generate_prompt();
	input = readline(prompt);
	free(prompt);
	return (input);
}

static int	process_input(char *input, char ***shell_envp, int last_status)
{
	char	*complete_input;

	complete_input = read_multiline_input(input);
	if (complete_input && *complete_input)
		last_status = process_line(complete_input, shell_envp, last_status);
	free(complete_input);
	return (last_status);
}

static void	run_shell_loop(char ***shell_envp, int *last_status)
{
	char	*input;

	while (1)
	{
		input = get_input_line();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		*last_status = process_input(input, shell_envp, *last_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		last_status;
	char	**shell_envp;

	(void)argc;
	(void)argv;
	shell_envp = copy_env(envp);
	last_status = 0;
	setup_interactive_signals();
	run_shell_loop(&shell_envp, &last_status);
	rl_clear_history();
	free_split(shell_envp);
	return (last_status);
}
