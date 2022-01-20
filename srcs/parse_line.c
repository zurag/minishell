#include "../includes/minishell.h"

static int	is_end(int c)
{
	if (c == '_')
		return (0);
	if (ft_isalpha(c))
		return (0);
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

static	int	del_quotes(char **line, int start)
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
	int	i;

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
