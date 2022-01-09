#include "../includes/minishell.h"

static int check_quotes(char *line)
{
	char	quotes;
	
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			quotes = *line;
			line++;
			while (*line != quotes && *line)
				line++;
			if (*line != quotes)
				return (1);
		}
		line++;
	}
	return (0);
}

static int	command_counter(char *line) // не учитывает ковычки 
{
	int	count;

	count = 1;
	while (*line)
	{
		if (*line == '|')
			count++;
		line++;
	}
	return (count);
}

// int	parse_com(char *line, t_cmd *cmd)
// {
// 	int i;
// 	char *start;

// 	i = 0;
// 	start = line;
// 	while (*line)
// 	{
// 		if (ft_isalpha(*line))

// 		line++;
// 	}
// }

int	parser(char *line, t_mini *mini)
{
	// char *tmp;
	if (check_quotes(line))
	{
		printf("ERROR unclosed quotes\n");
		return (1);
	}
	mini->count_cmd = command_counter(line);
	mini->cmd = malloc(sizeof(t_cmd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	return (0);
}