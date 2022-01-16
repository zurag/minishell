/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:48:25 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/17 00:08:46 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_namecmp(t_list *lst, char *str)
{
	t_env	*ptr;

	ptr = (t_env *)lst->content;
	if (!ft_strncmp(str, ptr->name, ft_strlen(ptr->name) + 1))
		return (1);
	return (0);
}

void	ft_del_var_env(void *lst)
{
	t_env	*ls_node_env;

	ls_node_env = (t_env *)(lst);
	if (ls_node_env->name)
		free(ls_node_env->name);
	if (ls_node_env->value)
		free(ls_node_env->value);
	free(ls_node_env);
}

static void	ft_unset_var_env(t_list **is_head_env, char *str)
{
	t_list	**ls_current;
	t_list	*ls_next;
	int		i;

	i = 0;
	ls_current = is_head_env;
	while (*ls_current)
	{
		if (ft_namecmp(*ls_current, str))
		{
			ls_next = (*ls_current)->next;
			ft_lstdelone(*ls_current, &ft_del_var_env);
			*ls_current = ls_next;
			break ;
		}
		i++;
		ls_current = &(*ls_current)->next;
	}
}

static int	ft_is_valid_token_unset(char *s)
{
	while (s && *s)
	{
		if (!ft_isalnum(*s))
			return (0);
		s++;
	}
	return (1);
}

void	ft_buildin_unset(t_list **is_head_env, t_mini *is_data)
{
	int	i;

	if (!is_data)
		return ;
	i = 0;
	while (i < is_data->count_cmd)
	{
		if (ft_is_valid_token_unset(is_data->cmd[i].cmd))
			ft_unset_var_env(is_head_env, is_data->cmd[i].cmd);
		else
		{
			printf("unset : \'%s\': not a valid", is_data->cmd[i].cmd);
			printf(" identifier\n");
			ft_print_error(is_head_env, NULL, 1);
			break ;
		}
		i++;
	}
	return ;
}
