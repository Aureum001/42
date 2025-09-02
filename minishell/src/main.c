#include "minishell.h"

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
		status = execute_builtin_with_redirections(cmd_list, envp_ptr);
	}
	else if (cmd_list)
	{
		status = executor(cmd_list);
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
	while (1)
	{
		prompt = generate_prompt(shell_envp);
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
	free_split(shell_envp);
	return (last_status);
}
