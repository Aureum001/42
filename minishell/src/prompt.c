/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:27 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/02 10:48:28 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static char	*build_prompt(char *path_part)
{
	char	*user;
	char	*prompt;
	char	*temp;

	user = getenv("USER");
	if (user)
	{
		prompt = ft_strjoin(ft_strdup(user), ":");
		temp = ft_strjoin(prompt, path_part);
		return (temp);
	}
	else
	{
		prompt = ft_strjoin(ft_strdup("user:"), path_part);
		return (prompt);
	}
}

char	*generate_prompt(void)
{
	char	cwd[1024];
	char	*home;
	char	*prompt;
	char	*path_part;
	char	*tilde;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("minishell> "));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tilde = ft_strdup("~");
		path_part = ft_strjoin(tilde, cwd + ft_strlen(home));
	}
	else
	{
		path_part = ft_strdup(cwd);
	}
	prompt = ft_strjoin(build_prompt(path_part), "> ");
	free(path_part);
	return (prompt);
}
