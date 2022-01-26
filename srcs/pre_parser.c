/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:58:32 by zurag             #+#    #+#             */
/*   Updated: 2022/01/26 15:31:10 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	check_empty_line(char *line)
{
	if (!*line)
	{
		free(line);
		return (1);
	}
	while ((*line == ' ' || *line == '\t') && *line)
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

static int	ft_check_sign(char **str, char quotes, int count_cmd)
{
	char	*line;

	line = *str;
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
	return (count_cmd);
}

int	pre_parse(char *line)
{
	char	quotes;
	int		count_cmd;

	count_cmd = 1;
	if (check_empty_line(line))
		return (-1);
	while (*line)
	{
		quotes = '0';
		ft_check_sign(&line, quotes, count_cmd);
	}
	if (*(line - 1) == '|' || *(line - 1) == '<' || *(line - 1) == '>')
		return (print_er("`newline'"));
	return (count_cmd);
}
