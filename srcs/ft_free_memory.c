/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:42:44 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/25 22:37:30 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_env(void *lst)
{
	t_env	*ls_env_node;

	ls_env_node = (t_env *)(lst);
	if (ls_env_node->name)
		free(ls_env_node->name);
	if (ls_env_node->value)
		free(ls_env_node->value);
	free(ls_env_node);
}

void	ft_free_env(t_list **is_head)
{
	t_list	**ls_current;
	t_list	*ls_next;
	int		i;

	i = 0;
	ls_current = is_head;
	while (*ls_current)
	{
		ls_next = (*ls_current)->next;
		ft_lstdelone(*ls_current, &ft_delete_env);
		*ls_current = ls_next;
		i++;
	}
	if (*is_head != NULL)
		free(is_head);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->arguments[i])
	{
		free(cmd->arguments[i]);
		i++;
	}
	free(cmd->arguments);
	if (cmd->in_file)
		close(cmd->in_file);
	if (cmd->out_file)
		close(cmd->out_file);
}

void	free_mshl(t_mshl *mini)
{
	int	i;

	i = 0;
	while (i < mini->count_cmd)
	{
		free_cmd(mini->cmd + i);
		i++;
	}
	free(mini->cmd);
	mini->count_cmd = 0;
	mini->cmd = NULL;
}
