/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:29:42 by zurag             #+#    #+#             */
/*   Updated: 2021/05/02 14:38:21 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t					i;
	unsigned char			*dest_u;
	const unsigned char		*src_u;

	i = 0;
	c = (unsigned char)c;
	src_u = (const unsigned char *)src;
	dest_u = (unsigned char *)dest;
	if (src_u == NULL && dest_u == NULL)
		return (NULL);
	while (i < n)
	{
		dest_u[i] = src_u[i];
		if (src_u[i] == c)
			return (dest_u + i + 1);
		i++;
	}
	return (NULL);
}
