/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:19:53 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/22 19:19:55 by dtentaco         ###   ########.fr       */
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

static char	*ft_join_env(t_env *env)
{
	char	*str_env;
	char	*tmp;

	tmp = ft_strjoin(env->name, "=");
	str_env = ft_strjoin(tmp, env->value);
	free(tmp);
	return (str_env);
}

char	**list2mass_env(t_list *lst)
{
	int		i;
	int		size;
	char	**mass;
	t_env	*env;

	size = ft_lstsize(lst) + 1;
	mass = malloc(size * sizeof(char *));
	i = 0;
	while (lst && i < size)
	{
		env = (t_env *)lst->content;
		mass[i++] = ft_join_env(env);
		lst = lst->next;
	}
	mass[i] = NULL;
	return (mass);
}