/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:04:47 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/25 18:44:40 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_return_error_isnum(t_mshl *data, int num_cmd, int i)
{
	printf("exit: %s : numeric positive argument required\n", \
			data->cmd[num_cmd].arguments[i]);
	ft_print_error(&data->head_env, NULL, 1);
}

static void	ft_return_error_args(t_mshl *data)
{
	printf("exit: too many arguments\n");
	ft_print_error(&data->head_env, NULL, 1);
}

static void	ft_set_retcode(t_mshl *data, int num_cmd)
{
	if (ft_atoi(data->cmd[num_cmd].arguments[1]) > 255)
		ft_print_error(&data->head_env, NULL, 255);
	else
		ft_print_error(&data->head_env, NULL, \
						ft_atoi(data->cmd[num_cmd].arguments[1]));
}

void	ft_builtin_exit(t_mshl *data, int num_cmd)
{
	int	i;
	int	num_flags;

	i = 1;
	num_flags = 0;
	while (data->cmd[num_cmd].arguments[i])
	{
		if (!ft_isnumber(data->cmd[num_cmd].arguments[i]))
		{
			ft_return_error_isnum(data, num_cmd, i);
			return ;
		}
		num_flags++;
		i++;
	}
	if (num_flags > 1)
	{
		ft_return_error_args(data);
		return ;
	}
	if (i > 1)
		ft_set_retcode(data, num_cmd);
	ft_exit(data);
}
