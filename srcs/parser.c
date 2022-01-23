#include "../includes/minishell.h"


static	int check_empty_line(char *line)
{
	if (!*line)
	{
		free(line);
		return (1);
	}
	while((*line == ' ' || *line == '\t') && *line)
		line++;
	if (!*line)
		return (1);
	return (0);
}


static int pre_parse(char *line) //добавить проверку ><
{
	char	quotes;
	int		count_cmd;

	count_cmd = 1;
	if (check_empty_line(line))
		return (-1);
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
	tokens = get_tokens(line, tokens);
	free(line);
	mini->cmd = malloc(sizeof(t_cmd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	ft_memset(mini->cmd, '\0', sizeof(t_cmd) * mini->count_cmd);
	init_cmd(tokens, mini);
	// // print_mini(mini);
	// ft_lstclear(&tokens, free);
	return (0);
}
