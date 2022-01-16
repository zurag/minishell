/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:37:34 by zurag             #+#    #+#             */
/*   Updated: 2021/04/22 16:56:42 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*copy;

	len = ft_strlen(s);
	copy = malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s, len + 1);
	return (copy);
}
