/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:42:44 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/26 17:40:45 by zurag            ###   ########.fr       */
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
	int		i;
	t_redir	*redir;

	i = 0;
	while (cmd->arguments[i])
	{
		free (cmd->arguments[i]);
		i++;
	}
	i = 0;
	free(cmd->arguments);
	if (cmd->in_file)
		close(cmd->in_file);
	if (cmd->out_file)
		close(cmd->out_file);
	free(cmd->cmd);
	while (cmd->redir)
	{
		redir = cmd->redir->content;
		free(redir->name);
		cmd->redir = cmd->redir->next;
	}
	ft_lstclear(&cmd->redir, free);
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
	mini->count_cmd = 0;
	free(mini->cmd);
	mini->cmd = NULL;
}

