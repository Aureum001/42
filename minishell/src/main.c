/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:21 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/29 12:11:18 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flush_stdin(void)
{
	int		bytes_available;
	char	buffer[1024];

	if (ioctl(STDIN_FILENO, FIONREAD, &bytes_available) == 0)
	{
		while (bytes_available > 0)
		{
			read(STDIN_FILENO, buffer, sizeof(buffer));
			ioctl(STDIN_FILENO, FIONREAD, &bytes_available);
		}
	}
}

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
		if (get_heredoc_interrupted())
		{
			set_heredoc_interrupted(0);
			flush_stdin();
		}
		input = get_input_line();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		*last_status = process_input(input, shell_envp, *last_status);
		if (*last_status & (1 << 8))
		{
			*last_status &= 0xFF;
			break ;
		}
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
