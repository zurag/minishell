/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:00:43 by zurag             #+#    #+#             */
/*   Updated: 2021/04/22 20:28:43 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, len_s2 + len_s1 + 1);
	ft_memcpy(str, s1, len_s1);
	ft_strlcat(str, (char *)s2, len_s2 + len_s1 + 1);
	return (str);
}
