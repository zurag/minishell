/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:18:29 by zurag             #+#    #+#             */
/*   Updated: 2022/01/26 18:56:20 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process(t_mshl *data, char **envp, int i, int **fd)
{
	int	ret;

	ret = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	ret = ft_redir(data->cmd + i, data->cmd[i].redir);
	if (ret)
		exit(EXIT_FAILURE);
	ft_dup_fd(i, fd, data);
	if (is_builtin(data, i))
		execute_builtin(data, i);
	else if (execve(data->cmd[i].cmd, data->cmd[i].arguments, envp) == -1)
	{
		perror(data->cmd[i].cmd);
		exit (126);
	}
	exit(EXIT_SUCCESS);
}

int	ft_create_pipe(int **fd, t_mshl *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			write(2, "error in pipe\n", 15);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_close_fd(int *fd[2], t_mshl *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < data->count_cmd - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

static void	ft_wait_process(pid_t	*id, t_mshl *data)
{
	int		i;
	int		ret;

	i = 0;
	while (i < data->count_cmd)
	{
		waitpid(id[i], &ret, 0);
		ret = set_exit_status(ret);
		ft_print_error(&data->head_env, NULL, ret);
		i++;
	}
}

int	ft_processing(pid_t	*id, t_mshl *data, char **envp)
{
	int		i;
	int		**fd;

	i = -1;
	if (is_builtin(data, 0) && data->count_cmd == 1)
		return (execute_builtin(data, 0));
	fd = malloc(sizeof(int *) * (data->count_cmd - 1));
	while (++i < data->count_cmd - 1)
		fd[i] = malloc(sizeof(int ) * 2);
	if ((ft_create_pipe(fd, data)) || !fd)
		return (1);
	i = 0;
	while (i < data->count_cmd)
	{
		id[i] = fork();
		if (id[i] == -1)
			exit(EXIT_FAILURE);
		else if (id[i] == 0)
			process(data, envp, i, fd);
		i++;
	}
	ft_close_fd(fd, data);
	ft_wait_process(id, data);
	return (0);
}
