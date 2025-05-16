/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:32:09 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/05 11:32:09 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_mapped_node(void *(*f)(void *),
					void *content, void (*del)(void *))
{
	void	*new_content;
	t_list	*new_node;

	new_content = f(content);
	new_node = ft_lstnew(new_content);
	if (!new_node)
		del(new_content);
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*head;

	if (!lst || !f)
		return (NULL);
	result = create_mapped_node(f, lst->content, del);
	if (!result)
		return (NULL);
	head = result;
	while (lst->next)
	{
		lst = lst->next;
		result->next = create_mapped_node(f, lst->content, del);
		if (!result->next)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		result = result->next;
	}
	return (head);
}
