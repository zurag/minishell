/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:10:19 by zurag             #+#    #+#             */
/*   Updated: 2021/04/29 16:35:41 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	point;

	point = -1;
	i = 0;
	c = (char)c;
	while (s[i])
	{
		if (s[i] == c)
			point = i;
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	if (point == -1)
		return (NULL);
	return ((char *)s + point);
}
