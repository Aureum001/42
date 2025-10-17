/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:14 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 11:43:22 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_token_unclosed_quote(const char *line, int i)
{
	int	j;

	j = i + 1;
	while (line[j] && !(ft_isspace(line[j]) || ft_strchr("|<>&", line[j])))
		j++;
	return (j);
}

static int	handle_quote(char *line, int i)
{
	int	qidx;

	qidx = find_closing_quote(line + i, line[i]);
	if (qidx == -1)
		return (word_token_unclosed_quote(line, i));
	return (i + qidx + 1);
}

t_token	*get_word_token(char **line_ptr)
{
	char	*line;
	char	*start;
	int		i;

	line = *line_ptr;
	start = line;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i = handle_quote(line, i);
			continue ;
		}
		if (ft_isspace(line[i]) || ft_strchr("|<>&", line[i]))
			break ;
		i++;
	}
	*line_ptr += i;
	return (new_token(ft_substr(start, 0, i), TOKEN_WORD));
}

static void	lexer_add_token(t_token **head, t_token **current, t_token *new_tok)
{
	if (!*head)
	{
		*head = new_tok;
		*current = new_tok;
	}
	else
	{
		(*current)->next = new_tok;
		*current = new_tok;
	}
}

t_token	*lexer(char *line)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_tok;

	head = NULL;
	current = NULL;
	while (*line)
	{
		if (ft_isspace(*line))
		{
			line++;
			continue ;
		}
		if (ft_strchr("|<>&", *line))
		{
			new_tok = get_metachar_token(&line);
			if (!new_tok)
				return (NULL);
		}
		else
			new_tok = get_word_token(&line);
		lexer_add_token(&head, &current, new_tok);
	}
	return (head);
}
