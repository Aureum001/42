/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:24 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/27 10:00:01 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	add_redir(t_cmd *cmd, t_token *redir_token, t_token *file_token)
{
	t_redir	*redir;
	t_redir	*current;

	if (!file_token)
		return ;
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = redir_token->type;
	redir->filename = ft_strdup(file_token->value);
	redir->heredoc_fd = -1;
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

int	count_args(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			i++;
		else if (tokens->type >= TOKEN_REDIRECT_IN
			&& tokens->type <= TOKEN_HEREDOC)
		{
			tokens = tokens->next;
			if (!tokens)
				return (i);
		}
		tokens = tokens->next;
	}
	return (i);
}

static int	process_pipeline(t_token **tokens, t_cmd **current,
			char **envp, int last_status)
{
	if ((*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (*tokens && (*tokens)->type == TOKEN_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
			return (0);
		}
		(*current)->next = parse_single_command(tokens, envp, last_status);
		if (!(*current)->next)
			return (0);
		*current = (*current)->next;
	}
	return (1);
}

t_cmd	*parser(t_token *tokens, char **envp, int last_status)
{
	t_cmd	*head;
	t_cmd	*current;

	if (!tokens)
		return (NULL);
	if (tokens->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			2);
		return (NULL);
	}
	head = parse_single_command(&tokens, envp, last_status);
	if (!head)
		return (NULL);
	current = head;
	while (tokens)
	{
		if (!process_pipeline(&tokens, &current, envp, last_status))
		{
			free_cmd_list(head);
			return (NULL);
		}
	}
	return (head);
}
