/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:51:45 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/25 22:35:41 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_flag_echo(char *s)
{
	if (!s || *s != '-')
		return (0);
	s++;
	while (*s)
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}

static void	ft_echo_print(char *s, int flag)
{
	if (!flag)
		write(STDOUT_FILENO, s, ft_strlen(s));
	else
	{
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, s, ft_strlen(s));
	}
}

void	ft_builtin_echo(t_mshl *d, int num_cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_is_flag_echo(d->cmd[num_cmd].arguments[i]))
	{
		flag++;
		i++;
	}
	while (d->cmd[num_cmd].arguments[i])
	{
		if (ft_strlen(d->cmd[num_cmd].arguments[i]) != 0)
		{
			if ((!flag && i > 1) || (flag && i > flag + 1))
				ft_echo_print(d->cmd[num_cmd].arguments[i], 1);
			else
				ft_echo_print(d->cmd[num_cmd].arguments[i], 0);
		}
		i++;
	}
	if (!flag)
		printf("\n");
	ft_print_error(&d->head_env, NULL, 0);
}

int	ft_isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
