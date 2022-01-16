/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:48:10 by zurag             #+#    #+#             */
/*   Updated: 2021/04/27 22:58:18 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	size_t	len_set;
	char	*str;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	len_set = ft_strlen(set);
	start = 0;
	end = ft_strlen(s1) - 1;
	while ((start <= end) && ft_memchr(set, s1[start], len_set) != NULL)
		start++;
	while ((end >= start) && ft_memchr(set, s1[end], len_set) != NULL)
		end--;
	++end;
	str = ft_substr(s1, start, end - start);
	return (str);
}
