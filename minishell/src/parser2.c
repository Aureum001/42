/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:00:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/27 10:00:36 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_word_token(t_cmd *cmd, t_token **tokens, int *i,
				t_parse_ctx *ctx)
{
	char	*tmp;

	tmp = expand_and_remove_quotes((*tokens)->value, ctx->envp,
			ctx->last_status);
	cmd->argv[(*i)++] = tmp;
}

static int	process_redir_token(t_cmd *cmd, t_token **tokens)
{
	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		if (!(*tokens)->next)
			ft_putstr_fd("`newline'\n", 2);
		else
			ft_putstr_fd("`newline'\n", 2);
		return (0);
	}
	add_redir(cmd, *tokens, (*tokens)->next);
	*tokens = (*tokens)->next;
	return (1);
}

int	parse_command_token(t_cmd *cmd, t_token **tokens,
			int *i, t_parse_ctx *ctx)
{
	if ((*tokens)->type == TOKEN_WORD)
		process_word_token(cmd, tokens, i, ctx);
	else if ((*tokens)->type >= TOKEN_REDIRECT_IN
		&& (*tokens)->type <= TOKEN_HEREDOC)
	{
		if (!process_redir_token(cmd, tokens))
			return (0);
	}
	return (1);
}

t_cmd	*parse_single_command(t_token **tokens, char **envp, int last_status)
{
	t_cmd		*cmd;
	int			argc;
	int			i;
	t_parse_ctx	ctx;

	cmd = new_cmd();
	cmd->last_status = last_status;
	argc = count_args(*tokens);
	cmd->argv = ft_calloc(argc + 1, sizeof(char *));
	i = 0;
	ctx.envp = envp;
	ctx.last_status = last_status;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if (!parse_command_token(cmd, tokens, &i, &ctx))
		{
			free_cmd_list(cmd);
			return (NULL);
		}
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	cmd->envp = envp;
	return (cmd);
}
