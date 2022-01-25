/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:39:22 by zurag             #+#    #+#             */
/*   Updated: 2022/01/25 19:30:43 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	set_exit_status(int exit_status)
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
	{
		ft_putenv(&head_env, "?", "127");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(command);
		return(NULL);
	}
	free(command);
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

int ft_check_open(int fd, char *name)
{
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return(1);
	}
	return (0);
}

void is_fd(int fd)
{
	if (fd)
		close(fd);
}

int	ft_redir(t_cmd *cmd, t_list *lst)
{
	t_redir *redir;
	
	while (lst)
	{
		redir = lst->content;
		if (redir->mode == MODE_READ)
		{
			is_fd(cmd->in_file);
			cmd->in_file = open(redir->name, O_RDONLY);
			return(ft_check_open(cmd->in_file, redir->name));
		}
		else if (redir->mode == MODE_WRITE)
		{
			is_fd(cmd->out_file);
			cmd->out_file = open(redir->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			return(ft_check_open(cmd->out_file, redir->name));
		}
		else if (redir->mode == MODE_APPEND)
		{
			is_fd(cmd->out_file);
			cmd->out_file = open(redir->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			return(ft_check_open(cmd->out_file, redir->name));
		}
		else if (redir->mode == MODE_HEREDOC)
		{
			is_fd(cmd->in_file);
			heredoc(cmd, redir->name);
		}
		lst = lst->next;
	}
	return (0);
}

void	process(t_mshl *data, char **envp, int i, int **fd)
{
	int ret;

	ret = 0;
	signal(SIGQUIT, SIG_DFL);
	ret = ft_redir(data->cmd + i, data->cmd[i].redir);
	if (ret)
		exit(1);
	ft_dup_fd(i, fd, data);
	if (execve(data->cmd[i].cmd, data->cmd[i].arguments, envp) == -1)
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

int	ft_processing(pid_t	*id, t_mshl *data, char **envp)
{
	int	i;
	int	**fd;
	int	ret;
	
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
			exit(EXIT_FAILURE);
		}
		else if (id[i] == 0)
			process(data, envp, i, fd);
		i++;
	}
	i = 0;
	ft_close_fd(fd, data);
	while(i < data->count_cmd)
	{
		waitpid(id[i], &ret, 0);
		ret = set_exit_status(ret);
		printf("ret === %d\n", ret);
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
	if (!data->cmd[i].cmd)
		ft_redir(&data->cmd[i], data->cmd[i].redir);
	else
	{
		while (i < data->count_cmd)
		{
			if (!(data->cmd[i].cmd = join_path(data->cmd[i].cmd, path, data->head_env)))
			{
				ft_free_arr(path);
				return (-1);
			}
			i++;
		}
		id = malloc(sizeof(pid_t) * data->count_cmd);
		if (!id)
			return (1);
		ft_processing(id, data, envp);
		free(id);
	}
	ft_free_arr(path);
	return (0);
}
