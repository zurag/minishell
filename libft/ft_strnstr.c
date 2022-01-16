/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:30:08 by zurag             #+#    #+#             */
/*   Updated: 2021/05/02 19:07:02 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		len_lit;

	len_lit = ft_strlen(little);
	j = 0;
	i = 0;
	if (len_lit == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		if (len_lit > len - i)
			return (NULL);
		if (ft_strncmp(big + i, little, len_lit) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
