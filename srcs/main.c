#include "minishell.h"

int	main(void)
{
	// t_mini	mini;
	char		*line;
	t_list		**ls_env = NULL;
	extern char	**environ;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_init_env(ls_env, environ);
	while (1)
	{
		line = readline("minishell>");
		if (line && *line)
			add_history(line);
		// parser(line, &mini);
		// execute();
		free (line);
	}
	// free (line);
	printf("%s\n", getenv("PATH"));
	return (0);
}
