/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:50:30 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/02 10:50:31 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_redir;

	while (cmd_list)
	{
		tmp_cmd = cmd_list->next;
		while (cmd_list->redirs)
		{
			tmp_redir = cmd_list->redirs->next;
			free(cmd_list->redirs->filename);
			free(cmd_list->redirs);
			cmd_list->redirs = tmp_redir;
		}
		if (cmd_list->argv)
			free_split(cmd_list->argv);
		free(cmd_list);
		cmd_list = tmp_cmd;
	}
}

char	*remove_quotes(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		return (ft_substr(str, 1, len - 2));
	}
	return (ft_strdup(str));
}
