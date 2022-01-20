#ifndef MINISHELL_H
# define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct	s_cmd{
	char	*cmd;
	char	**arguments;
	int		in_file;
	int		out_file;
}				t_cmd;

int	parser(char *line, t_mini *mini);
char	*parse_line(char *line);
int	put_in_mid_line(char **line, char *str, int start, int end);
int	len_quotes(char *line, int i);
t_list	*get_tokens(char *line, t_list *token);
int	init_cmd(t_list *lst, t_mini *mini);

#endif
