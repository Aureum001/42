/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/29 12:27:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_heredoc_quoted(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 2)
		return (0);
	if ((filename[0] == '\'' && filename[len - 1] == '\'')
		|| (filename[0] == '"' && filename[len - 1] == '"'))
		return (1);
	return (0);
}

static char	*get_redir_filename(t_token *redir_token, t_token *file_token,
				int *quoted)
{
	char	*filename;

	filename = file_token->value;
	*quoted = 0;
	if (redir_token->type == TOKEN_HEREDOC
		&& is_heredoc_quoted(filename))
	{
		*quoted = 1;
		filename = remove_quotes(filename);
	}
	else
		filename = ft_strdup(file_token->value);
	return (filename);
}

static void	append_redir_to_list(t_cmd *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		current = cmd->redirs;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}

void	add_redir(t_cmd *cmd, t_token *redir_token, t_token *file_token)
{
	t_redir	*redir;
	char	*filename;
	int		quoted;

	if (!file_token)
		return ;
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return ;
	filename = get_redir_filename(redir_token, file_token, &quoted);
	redir->type = redir_token->type;
	redir->filename = filename;
	redir->heredoc_fd = -1;
	redir->quoted_heredoc = quoted;
	append_redir_to_list(cmd, redir);
}
