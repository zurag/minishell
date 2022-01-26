/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:19:53 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/26 12:05:04 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_mshl *data, int num_cmd)
{
	if (!ft_strcmp(data->cmd[num_cmd].arguments[0], "pwd"))
		ft_builtin_pwd(&data->head_env);
	else if (!ft_strcmp(data->cmd[num_cmd].arguments[0], "echo"))
		ft_builtin_echo(data, num_cmd);
	else if (!ft_strcmp(data->cmd[num_cmd].arguments[0], "cd"))
		ft_builtin_cd(data, num_cmd);
	else if (!ft_strcmp(data->cmd[num_cmd].arguments[0], "env"))
		ft_builtin_env(&data->head_env);
	else if (!ft_strcmp(data->cmd[num_cmd].arguments[0], "export"))
		ft_builtin_export(data, num_cmd);
	else if (!ft_strcmp(data->cmd[num_cmd].arguments[0], "unset"))
		ft_builtin_unset(data, num_cmd);
	else if (!ft_strcmp(data->cmd[num_cmd].arguments[0], "exit"))
		ft_builtin_exit(data, num_cmd);
}
