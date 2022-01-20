#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	free(cmd->arguments);
	if (cmd->in_file)
		close(cmd->in_file);
	if (cmd->out_file)
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
