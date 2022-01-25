#include "../includes/minishell.h"

int	read_heredoc(const char *end, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (strncmp(line, end, ft_strlen(line)) == 0 && *line)
			break ;
		rl_redisplay();
		ft_putstr_fd(line, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

int	heredoc(t_cmd *cmd, const char *end_file)
{
	int	fd[2];
	pid_t	id;
	// struct termios	*attr_out;
	// struct termios	*attr_in;

	// attr_out = (struct termios *)malloc(sizeof(struct termios));
	// attr_in = (struct termios *)malloc(sizeof(struct termios));
	pipe(fd);
	// tcgetattr(STDOUT_FILENO, attr_out);
	// tcgetattr(STDIN_FILENO, attr_in);
	id = fork();
	if (id == 0)
		read_heredoc(end_file, fd);
	close(fd[1]);
	waitpid(id, NULL, 0);
	// tcsetattr(STDOUT_FILENO, TCSAFLUSH, attr_out);
	// tcsetattr(STDIN_FILENO, TCSANOW, attr_in);
	// free(attr_out);
	// free(attr_in);
	dup2(fd[0], cmd->in_file);
	close(fd[0]);
	return(0);
}

void	ft_init_file(t_list *lst, t_cmd *cmd)
{
	char	*file;
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	lst->next->content = parse_line(lst->next->content);
	file = lst->next->content;
	if (!ft_strncmp(lst->content, "<<", 2))
		redir->mode = MODE_HEREDOC;
	else if (!ft_strncmp(lst->content, ">>", 2))
		redir->mode = MODE_APPEND;
	else if (!ft_strncmp(lst->content, ">", 1))
		redir->mode = MODE_WRITE;
	else if (!ft_strncmp(lst->content, "<", 1))
		redir->mode = MODE_READ;
	redir->name = ft_strdup(file);
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
}
