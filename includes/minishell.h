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
	int		in_file;
	int		out_file;
}				t_cmd;

typedef struct	s_mshl{
	t_cmd	*cmd;
	int		count_cmd;
	t_list	*head_env;
}				t_mshl;

typedef struct	s_env
{
	char	*name;
	char	*value;
}				t_env;

int		parser(char *line, t_mshl *data);

void	ft_run_prompt(t_mshl *data);

void	set_input_signals(void);
void	signal_handler(int signo);

t_list	*ft_init_env(char **env);
t_list	*ft_add2list(t_list *is_env, char *i_str);
int		ft_insnewlst(t_list **is_head, char *name, char *val);
int		ft_putenv(t_list **is_head, char *name, char *val);
char	*ft_getenv(t_list *is_head, char *i_str);
void	ft_free_env(t_list **is_head);
void	ft_delete_env(void *lst);
t_env	**ft_sortenv(t_list **is_head_env);

int		ft_builtin_env(t_list **is_head_env);
void	ft_builtin_pwd(t_list **is_head_env);
void	ft_builtin_unset(t_mshl *data);
void	ft_builtin_export(t_mshl *data);

void	ft_exit(t_list **is_head_env);
int		ft_print_error(t_list **is_head, const char *str, int nbr);

int		parser(char *line, t_mshl *mini);
char	*parse_line(char *line);
int		put_in_mid_line(char **line, char *str, int start, int end);
int		len_quotes(char *line, int i);
t_list	*get_tokens(char *line, t_list *token);
int		init_cmd(t_list *lst, t_mshl *mini);

#endif
