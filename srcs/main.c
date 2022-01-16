#include "../includes/minishell.h"

int	main(void)
{
	t_mini	mini;

	char *line = readline("minishell$ ");
	// char *line = "ls -la file2 file3 >file3 | cat -e | grep f > outfile";
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
