/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:39:22 by zurag             #+#    #+#             */
/*   Updated: 2022/01/23 16:07:14 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*join_path(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
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
	{
		write(2, "Incorrect command\n", 19);
		return(NULL);
	}
	free(tmp);
	return (cmd);
}

// signal(SIGQUIT, SIG_DFL); перед exec


void	ft_dup_fd(int i, int **fd, t_mshl *data)
{
	if (i != 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i != data->count_cmd -1)
		dup2(fd[i][1], STDOUT_FILENO);
	if (data->cmd[i].in_file)
	{
		dup2(data->cmd[i].in_file, STDIN_FILENO);
		close(data->cmd[i].in_file);
	}
	if (data->cmd[i].out_file)
	{
		dup2(data->cmd[i].out_file, STDOUT_FILENO);
		close(data->cmd[i].out_file);
	}
	ft_close_fd(fd, data);
	
}

void	process(t_mshl *data, char **envp, int i, int **fd)
{
	ft_dup_fd(i, fd, data);
	if (execve(data->cmd[i].cmd, data->cmd[i].arguments, envp) == -1)
	{
		perror(NULL);
		exit (errno);
	}
	exit(EXIT_SUCCESS);
}

int	ft_create_pipe(int **fd, t_mshl *data)
{
	int	i;

	i = 0;
	while(i < data->count_cmd - 1)
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
	int i;
	i = 0;
	while (i < data->count_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

//ls -la | cat -e | grep 2 | wc -l

int	ft_processing(pid_t	*id, t_mshl *data, char **envp)
{
	int	i;
	int	**fd;
	
	i = 0;
	fd = malloc(sizeof(int *) * (data->count_cmd - 1));
	while(i < data->count_cmd - 1)
	{
		fd[i] = malloc(sizeof(int ) * 2);
		i++;
	}
	if ((ft_create_pipe(fd, data)) || !fd)
		return (1);
	i = 0;
	while(i < data->count_cmd)
	{
		id[i] = fork();
		if (id[i] == -1)
		{
			exit(1);
		}
		else if (id[i] == 0)
			process(data, envp, i, fd);
		i++;
	}
	i = 0;
	while(i < data->count_cmd)
	{
		waitpid(id[i], NULL, 0);
		ft_close_fd(fd, data);
		i++;
	}
	return (0);
}

int	executor(t_mshl *data, char **envp)
{
	pid_t	*id;
	char	**path;
	int		i;

	// (void)envp;
	i = 0;
	path = ft_split(getenv("PATH"), ':');
	while (i < data->count_cmd)
	{
		if (!(data->cmd[i].cmd = join_path(data->cmd[i].cmd, path)))
			return (-1);
		i++;
	}
	id = malloc(sizeof(pid_t) * data->count_cmd);
	if (!id)
		return (1);
	ft_processing(id, data, envp);
	ft_free_arr(path);
	return (0);
}
