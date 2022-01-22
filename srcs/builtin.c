/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:19:53 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/22 18:38:24 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_mshl *data)
{
	if (data->cmd->cmd == NULL)
		return (0);
	if (ft_strncmp(data->cmd->cmd, "cd", 3) == 0)
		return (DEF_CD);
	else if (ft_strncmp(data->cmd->cmd, "pwd", 4) == 0)
		return (DEF_PWD);
	else if (ft_strncmp(data->cmd->cmd, "echo", 5) == 0)
		return (DEF_ECHO);
	else if (ft_strncmp(data->cmd->cmd, "env", 4) == 0)
		return (DEF_ENV);
	else if (ft_strncmp(data->cmd->cmd, "exit", 5) == 0)
		return (DEF_EXIT);
	else if (ft_strncmp(data->cmd->cmd, "unset", 6) == 0)
		return (DEF_UNSET);
	else if (ft_strncmp(data->cmd->cmd, "export", 7) == 0)
		return (DEF_EXPORT);
	return (0);
}

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
