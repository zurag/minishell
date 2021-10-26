/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:32:08 by zurag             #+#    #+#             */
/*   Updated: 2021/04/29 18:02:29 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*tmp;

	tmp = ft_lstnew(f(lst->content));
	if (!tmp)
		return (NULL);
	lst = lst->next;
	first = tmp;
	while (lst)
	{
		tmp->next = ft_lstnew(f(lst->content));
		if (!tmp->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	return (first);
}
