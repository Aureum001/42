#include "minishell.h"

t_token_type get_metachar_type(char c, char next)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<' && next == '<')
		return (TOKEN_HEREDOC);
	if (c == '<')
		return (TOKEN_REDIRECT_IN);
	if (c == '>' && next == '>')
		return (TOKEN_REDIRECT_APPEND);
	if (c == '>')
		return (TOKEN_REDIRECT_OUT);
	return (TOKEN_WORD);
}

int find_closing_quote(const char *str, char quote)
{
	int i;
	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

t_token *get_metachar_token(char **line_ptr)
{
	char *line;
	t_token_type type;
	int len;
	char *value;

	line = *line_ptr;
	type = get_metachar_type(line[0], line[1]);
	len = 1;
	if ((line[0] == '<' && line[1] == '<') || (line[0] == '>' && line[1] == '>'))
		len = 2;
	value = ft_substr(line, 0, len);
	*line_ptr += len;
	return (new_token(value, type));
}
