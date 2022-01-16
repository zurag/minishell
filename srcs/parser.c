#include "../includes/minishell.h"

static int pre_parse(char *line) //добавить проверку ><
{
	char	quotes;
	int		count_cmd;

	count_cmd = 1;
	if(!*line)
		return (0);
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

void	print_token(t_list *lst)
{
	while(lst)
	{
		printf("token == %s\n", (char *)lst->content);
		lst = lst->next;
	}
}



int	len_quotes(char *line, int i)
{
	char	quotes;
	int		len;

	len = 0;
	quotes = line[i];
	len++;
	while (line[i + len] != quotes)
		len++;
	return (len + 1);
}


int	len_token(char *line, int i)
{
	int	len;

	len = 0;
	if (line[i] == '<' || line[i] == '>')
	{
		i++;
		if (line[i] == '<' || line[i] == '>')
			return (2);
		return (1);
	}
	if (line[i] == '|')
		return (1);
	if (line[i] == '\"' || line[i] == '\'')
		return(len_quotes(line, i));
	while (line[i + len])
	{
		if (line[i + len] == ' ' || line[i + len] == '\t')
			return (len);
		if (line[i + len] == '<' || line[i + len] == '>')
			return (len);
		if (line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
}

t_list	*get_tokens(char *line, t_list *token)
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
		len = len_token(line, i);
		tmp = ft_substr(line, i, len);
		ft_lstadd_back(&token, ft_lstnew(tmp));
		i += len;
		
	}
	return (token);
}

int	ft_init_file(t_list *lst, t_cmd cmd)
{
	if (!ft_strncmp(lst->content, "<", 1))
	{
		if (cmd.in_file)
			close(cmd.in_file);
		cmd.in_file = open(parse_line(lst->next->content), O_RDONLY);
	}
	else if (!ft_strncmp(lst->content, ">", 1))
	{
		if (cmd.out_file)
			close(cmd.out_file);
		cmd.out_file = open(parse_line(lst->next->content), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (!ft_strncmp(lst->content, "<<", 2))
	{
		if (cmd.in_file)
			close(cmd.in_file);
		cmd.in_file = open(parse_line(lst->next->content), O_RDONLY); // ??? проверить
	}
	else if (!ft_strncmp(lst->content, ">>", 2))
	{
		if (cmd.in_file)
			close(cmd.in_file);
		cmd.out_file = open(parse_line(lst->next->content), O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (0);
}



int	args_counter(t_list *lst)
{
	int		count;
	char	*token;

	count = 0;
	while(lst)
	{
		token = lst->content;
		if (*token == '<' || *token == '>')
			break ;
		if (*token == '|')
			break ;
		lst=lst->next;
		count++;
	}
	return (count);
}

char	**init_cmd_args(t_list **lst)
{
	int		count_args;
	char	**args;
	int		i;

	i = 0;
	count_args = args_counter(*lst);
	args = (char**)malloc(sizeof(char *) * count_args + 1);
	if (!args)
		return (NULL);
	memset(args, '\0', sizeof(char *) * count_args + 1);
	while (i < count_args)
	{
		args[i] = parse_line((*lst)->content);
		(*lst) = (*lst)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	init_cmd(t_list *lst, t_mini *mini)
{
	int		i;
	char	*token;

	i = 0;
	while (lst)
	{
		token = lst->content;
		if (*token == '<' || *token == '>')
		{
			ft_init_file(lst, mini->cmd[i]);
			lst = lst->next->next;
		}
		else if (*token == '|')
		{
			i++;
			lst = lst->next;
		}
		else
		{
			mini->cmd[i].cmd = parse_line(lst->content);
			mini->cmd[i].arguments = init_cmd_args(&lst);
		}
	}

	return (0);
}

void print_mini(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mini->count_cmd)
	{
		printf(" nomber %d cmd = %s\n", i +1, mini->cmd[i].cmd);
		while (mini->cmd[i].arguments[j])
		{
			printf(" arg ==  %s\n", mini->cmd[i].arguments[j]);
			j++;
		}
		j = 0;
		i++;
		// printf(" nomber %d cmd = %s ", i +1, mini->cmd[i].cmd);
	}
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
	ft_memset(mini->cmd, '\0', sizeof(t_cmd) * mini->count_cmd);
	// line = parse_line(line);
	// printf("final line === %s\n", line);
	tokens = get_tokens(line, tokens);
	// print_token(tokens);
	init_cmd(tokens, mini);
	print_mini(mini);
	return (0);
}
