#include "minishell.h"

int	main(void)
{
	// t_mini	mini;
	char	*line;
	char	cwd[PATH_MAX];
	
	
	while (1)
	{
		line = readline(getcwd(cwd, sizeof(cwd)));
		printf("%s\n", line);
		// parser(line, &mini);
		// add_history(line);
		// execute();
		free (line);
		
		add_history(line);
	}
	// free (line);
	printf("%s\n", getenv("PATH"));
	return (0);
}
