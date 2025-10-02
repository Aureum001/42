/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:24 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/02 11:00:32 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

static void	add_redir(t_cmd *cmd, t_token *redir_token, t_token *file_token)
{
	t_redir	*redir;
	t_redir	*current;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = redir_token->type;
	redir->filename = ft_strdup(file_token->value);
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

static int	count_args(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			i++;
		else if (tokens->type >= TOKEN_REDIRECT_IN
			&& tokens->type <= TOKEN_HEREDOC)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (i);
}

static t_cmd	*parse_single_command(t_token **tokens, char **envp)
{
	t_cmd	*cmd;
	int		argc;
	int		i;
	char	*tmp;

	cmd = new_cmd();
	argc = count_args(*tokens);
	cmd->argv = ft_calloc(argc + 1, sizeof(char *));
	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			tmp = remove_quotes((*tokens)->value);
			cmd->argv[i++] = tmp;
		}
		else if ((*tokens)->type >= TOKEN_REDIRECT_IN
			&& (*tokens)->type <= TOKEN_HEREDOC)
		{
			add_redir(cmd, *tokens, (*tokens)->next);
			*tokens = (*tokens)->next;
		}
		*tokens = (*tokens)->next;
	}
	return (cmd->envp = envp, cmd);
}

t_cmd	*parser(t_token *tokens, char **envp)
{
	t_cmd	*head;
	t_cmd	*current;

	if (!tokens)
		return (NULL);
	head = parse_single_command(&tokens, envp);
	current = head;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			tokens = tokens->next;
			current->next = parse_single_command(&tokens, envp);
			current = current->next;
		}
	}
	return (head);
}
