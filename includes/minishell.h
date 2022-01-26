/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:16:19 by zurag             #+#    #+#             */
/*   Updated: 2022/01/26 19:04:35 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>



typedef struct s_redir{
	char	*name;
	char	mode;
}				t_redir;

# define MODE_APPEND 1
# define MODE_READ 2
# define MODE_WRITE 3
# define MODE_HEREDOC 4

# define DEF_CD 1
# define DEF_PWD 2
# define DEF_ECHO 3
# define DEF_ENV 4
# define DEF_EXIT 5
# define DEF_UNSET 6
# define DEF_EXPORT 7

typedef struct s_cmd{
	char	*cmd;
	char	**arguments;
	int		in_file;
	int		out_file;
	t_list	*redir;
}				t_cmd;


typedef struct s_mshl{
	t_cmd	*cmd;
	int		count_cmd;
	t_list	*head_env;
}				t_mshl;

typedef struct s_env{
	char	*name;
	char	*value;
}				t_env;


void	ft_run_prompt(t_mshl *data);

void	set_input_signals(void);
void	signal_handler(int signo);
void	signal_handler2(int signo);

t_list	*ft_init_env(char **env);
t_list	*ft_add2list(t_list *is_env, char *i_str);
int		ft_insnewlst(t_list **is_head, char *name, char *val);
int		ft_putenv(t_list **is_head, char *name, char *val);
char	*ft_getenv(t_list *is_head, char *i_str);
void	ft_free_env(t_list **is_head);
void	ft_delete_env(void *lst);
t_env	**ft_sortenv(t_list **is_head_env);
t_list	*ft_search_dubname(t_list **is_head, char *name);
char	*get_name(char *s);
char	*ft_check_tilde(t_list **head, char *str);
int		ft_update_dir(t_list **head);
char	*get_name_env(char *s);
char	*get_value_env(char *s);
int		ft_isset(char c, char *set);

int		ft_builtin_env(t_list **is_head_env);
void	ft_builtin_pwd(t_list **is_head_env);
void	ft_builtin_unset(t_mshl *data, int num_cmd);
void	ft_builtin_export(t_mshl *data, int num_cmd);
int		ft_builtin_cd(t_mshl *d, int num_cmd);
void	ft_builtin_echo(t_mshl *d, int num_cmd);
void	ft_builtin_exit(t_mshl *data, int num_cmd);

void	ft_exit(t_mshl *data);
int		ft_print_error(t_list **is_head, const char *str, int nbr);

int		parser(char *line, t_mshl *mini);
int		pre_parse(char *line);
char	*parse_line(char *line, t_mshl *data);
int		put_in_mid_line(char **line, char *str, int start, int end);
int		len_quotes(char *line, int i);
t_list	*get_tokens(char *line, t_list *token);
int		init_cmd(t_list *lst, t_mshl *mini);
void	free_cmd(t_cmd *cmd);
void	free_mshl(t_mshl *mini);
void	ft_init_file(t_list *lst, t_cmd *cmd, t_mshl *data);
int		is_builtin(t_mshl *data, int num_cmd);
int		execute_builtin(t_mshl *data, int num_cmd);
char	**list2mass_env(t_list *lst);

int		executor(t_mshl *data, char **envp);
void	ft_close_fd(int *fd[2], t_mshl *data);
int		ft_create_pipe(int **fd, t_mshl *data);
void	process(t_mshl *data, char **envp, int i, int **fd);
int		heredoc(t_cmd *cmd, const char *end_file);
int		set_exit_status(int exit_status);
void	ft_free_arr(char **arr);
int		ft_check_open(int fd, char *name);
char	*join_path(char *cmd, char **path, t_list *head_env);
int		ft_processing(pid_t	*id, t_mshl *data, char **envp);
int		ft_redir(t_cmd *cmd, t_list *lst);
void	ft_dup_fd(int i, int **fd, t_mshl *data);
#endif
