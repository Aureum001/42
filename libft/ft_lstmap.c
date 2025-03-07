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

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*head;

	if (!lst)
		return (NULL);
	result = ft_lstnew(lst->content);
	if (!result)
		return (NULL);
	head = result;
	while (lst->next)
	{
		lst = lst->next;
		result->next = ft_lstnew(f(lst->content));
		if (!result->next)
		{
			ft_lstclear(&head, del);
			break ;
		}
		result = result->next;
	}
	return (head);
}
