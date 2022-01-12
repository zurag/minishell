#include "../includes/minishell.h"

int	main(void)
{
	t_mini	mini;

	char *line = readline("minishell$ ");
	while (line)
	{
		// printf("%s\n", line);
		parser(line, &mini);
		line = readline("minishell$ ");
		// add_history(line);
	}
	// free (line);
	// printf("%s\n", getenv("PATH"));

	return (0);
}
