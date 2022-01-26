/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:37:11 by zurag             #+#    #+#             */
/*   Updated: 2022/01/26 18:22:21 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		exit_status = 128 + WTERMSIG(exit_status);
	}
	return (exit_status);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*error_path(t_list *head_env, char *command, char *tmp, char *cmd)
{
	ft_putenv(&head_env, "?", "127");
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(command);
	free(tmp);
	free(cmd);
	return (NULL);
}

char	*join_path(char *cmd, char **path, t_list *head_env)
{
	int		i;
	char	*tmp;
	char	*command;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	command = ft_strdup(cmd);
	tmp = ft_strjoin("/", cmd);
	free(cmd);
	cmd = ft_strjoin(path[i], tmp);
	while (path[i] && access(cmd, X_OK) != 0)
	{
		free(cmd);
		cmd = ft_strjoin(path[i], tmp);
		i++;
	}
	if (path[i] == NULL)
		return (error_path(head_env, command, tmp, cmd));
	free(command);
	free(tmp);
	return (cmd);
}

int	ft_check_open(int fd, char *name)
{
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
