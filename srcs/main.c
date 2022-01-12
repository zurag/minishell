#include "minishell.h"

int	main(void)
{
	// t_mini	mini;
	char	*line;

	while (1)
	{
		print_prompt_msg();
		line = readline(":");
		printf("%s\n", line);
		// parser(line, &mini);
		add_history(line);
		// execute();
		free (line);

		add_history(line);
	}
	// free (line);
	printf("%s\n", getenv("PATH"));
	return (0);
}
