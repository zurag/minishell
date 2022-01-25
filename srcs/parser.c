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

static int	print_quotes_er(char quotes)
{
	if (quotes == '\'')
		ft_putstr_fd("minishell: unclosed single quote error\n", 2);
	else
		ft_putstr_fd("minishell: unclosed double quote error\n", 2);
	return (-1);
}

static int	print_er(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

static int pre_parse(char *line)
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
				return (print_quotes_er(quotes));
		}
		if (*line == '|')
		{
			count_cmd++;
			line++;
			if (*line == '|')
				return (print_er("`|'"));
		}
		else
			line++;
	}
	if (*(line - 1) == '|' || *(line - 1) == '<' || *(line - 1) == '>')
		return (print_er("`newline'"));
	return (count_cmd);
}

void	print_token(t_list *lst)
{
	while(lst)
	{
		printf("token == %s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	parser(char *line, t_mshl *mini)
{
	t_list	*tokens;

	tokens = NULL;
	mini->count_cmd = pre_parse(line);
	if (mini->count_cmd == -1)
		return (1);
	tokens = get_tokens(line, tokens);
	// print_token(tokens);
	mini->cmd = malloc(sizeof(t_cmd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	ft_memset(mini->cmd, '\0', sizeof(t_cmd) * mini->count_cmd);
	init_cmd(tokens, mini);
	// print_mini(mini);
	free(line);
	ft_lstclear(&tokens, free);
	return (0);
}
