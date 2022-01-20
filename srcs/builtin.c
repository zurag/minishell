/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:19:53 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/20 20:24:54 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_mshl *data)
{
	if (!ft_strcmp(data->cmd->arguments[0], "pwd"))
		ft_builtin_pwd(&data->head_env);
	// else if (!ft_strcmp(data->cmd->arguments[0], "echo"))
		// ft_echo(data);
	// else if (!ft_strcmp(data->cmd->arguments[0], "cd"))
	// 	ft_cd(data);
	else if (!ft_strcmp(data->cmd->arguments[0], "env"))
		ft_builtin_env(&data->head_env);
	else if (!ft_strcmp(data->cmd->arguments[0], "export"))
		ft_builtin_export(data);
	else if (!ft_strcmp(data->cmd->arguments[0], "unset"))
		ft_builtin_unset(data);
	// else if (!ft_strcmp(data->cmd->arguments[0], "exit"))
	// 	ft_builtin_exit(data);
}