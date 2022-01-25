/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:51:45 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/25 11:43:11 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_echo(t_mshl *d, int num_cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	// while (ft_check_echoflag(d->cmd[num_cmd].arguments[i]))
	// {
	// 	flag++;
	// 	i++;
	// }
	while (d->cmd[num_cmd].arguments[i])
	{
	// 	if (ft_strlen(d->cmd[num_cmd].arguments[i]) != 0)
	// 	{
	// 		if ((!flag && i > 1) || (flag && i > flag + 1))
	// 			echo_print(d->cmd[num_cmd].arguments[i], 1);
	// 		else
	// 			echo_print(d->cmd[num_cmd].arguments[i], 0);
	// 	}
		i++;
	}
	if (!flag)
		printf("\n");
	ft_print_error(&d->head_env, NULL, 0);
}
