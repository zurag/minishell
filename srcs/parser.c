#include "../includes/minishell.h"

static int pre_parse(char *line) //добавить проверку ><
{
	char	quotes;
	int		count_cmd;

	count_cmd = 1;
	if (!*line)
	{
		free(line);
		return (0);
	}
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			quotes = *line;
			line++;
			while (*line != quotes && *line)
				line++;
			if (*line != quotes)
				return (-1);
		}
		if (*line == '|')
		{
			count_cmd++;
			line++;
			if (*line == '|')
				return (-1);
		}
		else
			line++;
	}
	if (*(line - 1) == '|' || *(line - 1) == '<' || *(line - 1) == '>')
		return (-1);
	return (count_cmd);
}

int	parser(char *line, t_mshl *mini)
{
	t_list	*tokens;

	tokens = NULL;
	mini->count_cmd = pre_parse(line);
	if (mini->count_cmd == -1)
	{
		printf("ERROR unclosed quotes\n");
		return (1);
	}
	mini->cmd = malloc(sizeof(t_cmd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	ft_memset(mini->cmd, '\0', sizeof(t_cmd) * mini->count_cmd);
	tokens = get_tokens(line, tokens);
	free(line);
	init_cmd(tokens, mini);
	// print_mini(mini);
	ft_lstclear(&tokens, free);
	return (0);
}
