#include "../includes/minishell.h"

int	main(void)
{
	t_mini	mini;

	char *line = readline("minishell$ ");
	while (line)
	{
		// printf("%s\n", line);
		// add_history(line);
		parser(line, &mini);
		// free (line);
		line = readline("minishell$ ");

	}
	// free (line);
	// printf("%s\n", getenv("PATH"));

	return (0);
}
