/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:44:25 by zurag             #+#    #+#             */
/*   Updated: 2022/01/16 20:07:57 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (last == NULL)
		*lst = new;
	else
		last->next = new;
	// t_list	*add;

	// if (lst && new)
	// {
	// 	if (*lst)
	// 	{
	// 		add = ft_lstlast(*lst);
	// 		add->next = new;
	// 		new->next = NULL;
	// 	}
	// 	else
	// 	{
	// 		*lst = new;
	// 		new->next = NULL;
	// 	}
	// }
}
