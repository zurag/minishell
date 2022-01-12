#ifndef MINISHELL_H
# define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

typedef struct	s_cmd{
	char	*cmd;
	char	**arguments;
	char	**infile;
	char	**outfile;
	char	*mode_in;
	char	*mode_out;
	int		count_infile;
	int		count_outfile;
}				t_cmd;

typedef struct	s_mini{
	t_cmd	*cmd;
	int		count_cmd;
}				t_mini;


int		parser(char *line, t_mini *mini);
void	print_prompt_msg(void);


#endif
