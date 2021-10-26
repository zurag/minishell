/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:57:28 by zurag             #+#    #+#             */
/*   Updated: 2021/05/02 19:07:00 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (str);
	ft_memcpy(str, s + start, len);
	return (str);
}
