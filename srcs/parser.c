#include "../includes/minishell.h"

static int pre_parse(char *line)
{
	char	quotes;
	int		count_cmd;

	count_cmd = 1;
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
			count_cmd++;
		line++;
	}
	return (count_cmd);
}

static int	is_end(int c)
{
	if (c == '_')
		return (0);
	if (ft_isalpha(c))
		return(0);
	if (ft_isdigit(c))
		return (0);
	return (1);
}

static int	dollar(char *line, int start)
{
	int		i;
	char	*str;
	char	*tmp;
	
	i = 0;
	while (line[start + i + 1] && !(is_end(line[start + i + 1])))
		i++;
	tmp = ft_substr(line, start + 1, i);
	str = getenv(tmp);
	free(tmp);

	return (1);

}


static int del_quotes(char *line, int start)
{
	char	quotes;
	char	*tail;
	char	*head;
	char	*mid;
	int		end;

	end = start + 1;
	quotes = line[start];
	head = ft_substr(line, 0, start); 
	while (line[end])
	{
		if (line[end] == quotes)
			break ;
		end++;
	}
	tail = ft_substr(line, end + 1, ft_strlen(line) - end - 1);
	mid = ft_substr(line, start + 1, end - start - 1);
	free(line);
	line = ft_strjoin(head, mid);
	free(mid);
	free(head);
	head = ft_strdup(line);
	free(line);
	line = ft_strjoin(head, tail);
	free(head);
	free(tail);

	return (end - 2);
}

int	parse_com(char *line, t_cmd *cmd)
{
	int i;
	// char *tmp;
	(void)cmd;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = del_quotes(line, i);
			// break ;
		}
		else if (line[i] == '$')
		{
			dollar(line, i);
			break ;
		}
		i++;
	}
	return (0);
}

int	parser(char *line, t_mini *mini)
{
	// char *tmp;
	mini->count_cmd = pre_parse(line);
	if (mini->count_cmd == -1)
	{
		printf("ERROR unclosed quotes\n");
		return (1);
	}
	mini->cmd = malloc(sizeof(t_cmd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	parse_com(line, mini->cmd);
	printf("%s\n", line);
	return (0);
}