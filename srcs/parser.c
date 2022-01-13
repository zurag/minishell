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

int	put_in_mid_line(char **line, char *str, int start, int end)
{
	char	*head;
	char	*tail;
	char	*tmp;

	head = ft_substr(*line, 0, start);
	tail = ft_substr(*line, end + 1, ft_strlen(*line) - end - 1);
	free(*line);
	*line = ft_strjoin(head, str);
	tmp = ft_strdup(*line);
	free(*line);
	*line = ft_strjoin(tmp, tail);
	free(tmp);
	free(head);
	free(tail);
	return (0);
}

static int	dollar(char **line, int start) // не обрабатывает $?
{
	int		i;
	char	*str;
	char	*tmp;
	
	i = 0;
	while ((*line)[start + i + 1] && !(is_end((*line)[start + i + 1])))
		i++;
	tmp = ft_substr(*line, start + 1, i);
	str = getenv(tmp);
	if (!str)
		return (-1);
	free(tmp);
	put_in_mid_line(line, str, start, start + i);
	return (1);
}

static int del_quotes(char **line, int start)
{
	char	quotes;
	char	*mid;
	int		end;

	end = start + 1;
	quotes = (*line)[start];
	while ((*line)[end])
	{
		if ((*line)[end] == '$' && quotes == '\"')
			dollar(line, end);
		else if ((*line)[end] == quotes)
			break ;
		else
			end++;
	}
	mid = ft_substr(*line, start + 1, end - start - 1);
	put_in_mid_line(line, mid, start, end);
	free(mid);
	return (end - 2);
}

char	*parse_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = del_quotes(&line, i);
			if (i == -1)
				break ;
		}
		else if (line[i] == '$')
		{
			i = dollar(&line, i);
			if (i == -1)
				break ;
		}
		i++;
	}
	return (line);
}



int	len_token(char *line)
{
	int	len;

	len = 0;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			break;
		if (*line == '<' || *line == '>')
			break;
		if (*line == '\"' || *line == '\'')
			break ;
		if (*line == '|')
			break ;
		len++;
		line++;
	}
	return (len);
}

int	parse_cmd(char *line, t_cmd *cmd, t_list *token)
{	
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		len = len_token(line + i);
		tmp = ft_substr(line, i, len);
		ft_lstadd_back(&token, ft_lstnew(tmp));
		i += len;
	}
	return (0);
}

int	parser(char *line, t_mini *mini)
{
	t_list *tokens;

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
	line = parse_line(line);
	printf("final line === %s\n", line);
	return (0);
}
