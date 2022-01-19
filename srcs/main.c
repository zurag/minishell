#include "../includes/minishell.h"


void	free_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	// while (cmd->arguments[i])
	// {
	// 	free(cmd->arguments[i]);
	// 	i++;
	// }
	free(cmd->arguments);
	// free(cmd->cmd);
	if(cmd->in_file)
		close(cmd->in_file);
	if(cmd->out_file)
		close(cmd->out_file);
}

void	free_mini(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->count_cmd)
	{
		free_cmd(mini->cmd + i);
		i++;
	}
	free(mini->cmd);
}

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
		free_mini(&mini);
		// free (line);
		line = readline("minishell$ ");

	}
	// free (line);
	// printf("%s\n", getenv("PATH"));

	return (0);
}
