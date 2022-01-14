#include "minishell.h"

int	main(void)
{
	// t_mini	mini;
	// char		*line;
	t_list		**ls_env;
	extern char	**environ;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ls_env = malloc(sizeof(t_list *));
	if (!ls_env)
		return (1);	
	ft_init_env(ls_env, environ);
	// while (1)
	// {
	// 	line = readline("minishell>");
	// 	if (line && *line)
	// 		add_history(line);
	// 	// parser(line, &mini);
	// 	// execute();
	// 	free (line);
	// }
	return (0);
}
