/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:17:42 by zurag             #+#    #+#             */
/*   Updated: 2022/01/26 20:39:29 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ret_sign(int sign)
{
	if (sign > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		res;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += (nptr[i] - '0');
		i++;
	}
	if (i > 19)
		return (ft_ret_sign(sign));
	return (sign * res);
}
