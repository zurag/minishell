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

typedef struct	s_env
{
	char	*name;
	char	*value;
}				t_env;

int		parser(char *line, t_mini *mini);

void	ft_run_prompt(t_list **is_head_env);

void	set_input_signals(void);
void	signal_handler(int signo);

t_list	*ft_init_env(char **env);
t_list	*ft_add2list(t_list *is_env, char *i_str);
int		ft_insnewlst(t_list **is_head, char *name, char *val);
int		ft_putenv(t_list **is_head, char *name, char *val);
char	*ft_getenv(t_list *is_head, char *i_str);
void	ft_free_env(t_list **is_head);
void	ft_delete_env(void *lst);

int		ft_builtin_env(t_list **is_head_env);

void	ft_exit(t_list **is_head_env);
int		ft_print_error(t_list **is_head, const char *str, int nbr);
#endif
