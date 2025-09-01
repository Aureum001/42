#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token	*tokens;

	if (argc != 2)
	{
		printf("Usage: ./lexer_tester \"<input_string>\"\n");
		return (1);
	}
	tokens = lexer(argv[1]);
	print_tokens(tokens);
	free_tokens(tokens);
	return (0);
}
