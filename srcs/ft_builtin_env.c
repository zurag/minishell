/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:36:37 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/15 16:44:09 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_lst(void *lst)
{
	t_env	*ls_env_node;

	ls_env_node = (t_env *)(lst);
	if (ls_env_node->name)
		printf("%s=", ls_env_node->name);
	if (ls_env_node->value)
		printf("%s;\n", ls_env_node->value);
}

int	ft_builtin_env(t_list **is_head_env)
{
	if (!is_head_env)
		return (1);
	ft_lstiter(*is_head_env, &ft_read_lst);
	ft_print_error(is_head_env, NULL, 0);
	return (0);
}
