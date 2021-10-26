/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 20:44:47 by zurag             #+#    #+#             */
/*   Updated: 2021/04/29 18:17:42 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_nbr(long d)
{
	int	len;

	len = 1;
	if (d < 0)
	{
		d = -d;
		len += 1;
	}
	while (d >= 10)
	{
		len++;
		d /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;
	long	nbr;

	nbr = n;
	i = 0;
	len = ft_len_nbr(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		str[i] = '-';
	}
	str[len - i++] = '\0';
	while (nbr >= 10)
	{
		str[len - i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[len - i] = (nbr % 10) + '0';
	return (str);
}
