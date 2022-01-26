/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:21:24 by zurag             #+#    #+#             */
/*   Updated: 2022/01/26 13:52:47 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	args_counter(t_list *lst)
{
	int		count;
	char	*token;

	count = 0;
	while (lst)
	{
		token = lst->content;
		if (*token == '<' || *token == '>')
			break ;
		if (*token == '|')
			break ;
		lst = lst->next;
		count++;
	}
	return (count);
}

static char	**init_cmd_args(t_list **lst, t_mshl *data)
{
	int		count_args;
	char	**args;
	int		i;

	i = 0;
	count_args = args_counter(*lst);
	args = malloc((sizeof(char *) * count_args) + 1);
	if (!args)
		return (NULL);
	memset(args, '\0', sizeof(char *) * count_args + 1);
	while (i < count_args)
	{
		(*lst)->content = parse_line((*lst)->content, data);
		args[i] = ft_strdup((*lst)->content);
		(*lst) = (*lst)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

static void	init_command(t_list **lst, t_mshl *data, int i)
{
	data->cmd[i].cmd = ft_strdup((*lst)->content);
	data->cmd[i].cmd = parse_line(data->cmd[i].cmd, data);
	data->cmd[i].arguments = init_cmd_args(lst, data);
}

int	init_cmd(t_list *lst, t_mshl *mini)
{
	int		i;
	char	*token;

	i = 0;
	while (lst)
	{
		token = lst->content;
		if (!token)
			return (1);
		if (*token == '<' || *token == '>')
		{
			ft_init_file(lst, &(mini->cmd[i]));
			lst = lst->next->next;
		}
		else if (*token == '|')
		{
			i++;
			lst = lst->next;
		}
		else
			init_command(&lst, mini, i);
	}
	return (0);
}
