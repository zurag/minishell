/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 20:39:01 by zurag             #+#    #+#             */
/*   Updated: 2021/04/26 20:41:26 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	long	lnb;

	lnb = n;
	if (lnb < 0)
	{
		write(fd, "-", 1);
		lnb = -lnb;
	}
	if (lnb >= 10)
	{
		ft_putnbr_fd(lnb / 10, fd);
		digit = '0' + lnb % 10;
		write(fd, &digit, 1);
	}
	else
	{
		digit = '0' + lnb;
		write(fd, &digit, 1);
	}
}
