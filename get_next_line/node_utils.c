/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:25:15 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/18 13:04:07 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd_list	*find_fd_node(t_fd_list **list, int fd)
{
	t_fd_list	*current;

	if (!list)
		return (NULL);
	current = *list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_fd_list	*create_fd_node(int fd)
{
	t_fd_list	*new_node;

	new_node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->buffer = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	search_and_free(t_fd_list *prev, t_fd_list *current, int fd)
{
	while (current)
	{
		if (current->fd == fd)
		{
			prev->next = current->next;
			free(current->buffer);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	free_fd_node(t_fd_list **list, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	if (!list || !*list)
		return ;
	if ((*list)->fd == fd)
	{
		current = *list;
		*list = (*list)->next;
		free(current->buffer);
		free(current);
		return ;
	}
	prev = *list;
	current = prev->next;
	search_and_free(prev, current, fd);
}
