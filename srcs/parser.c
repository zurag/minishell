/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:43:34 by zurag             #+#    #+#             */
/*   Updated: 2022/01/26 13:58:27 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(char *line, t_mshl *mini)
{
	t_list	*tokens;

	tokens = NULL;
	mini->count_cmd = pre_parse(line);
	if (mini->count_cmd == -1)
	{
		ft_putenv(mini->head_env, "?", 1);
		return (1);
	}
	tokens = get_tokens(line, tokens);
	mini->cmd = malloc(sizeof(t_cmd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	ft_memset(mini->cmd, '\0', sizeof(t_cmd) * mini->count_cmd);
	init_cmd(tokens, mini);
	free(line);
	ft_lstclear(&tokens, free);
	return (0);
}
