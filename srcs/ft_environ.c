/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:13:06 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/14 22:18:01 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add2list(t_list **is_env, char *i_str)
{
	t_env	*ls_content;
	char	**ls_env;
	t_list	*ls_new_node;

	ls_content = malloc(sizeof(t_env));
	if (!is_env || !i_str || !ls_content)
		return (1);
	ls_env = ft_split(i_str, '=');
	if (!ls_env)
		return (1);
	// printf("TEST: %s = %s\n", ls_env[0], ls_env[1]);
	ls_content->name = ls_env[0];
	ls_content->value = ls_env[1];
	ls_new_node = ft_lstnew(ls_content);
	ft_lstadd_back(is_env, ls_new_node);
	free(ls_env);
	return (0);
}

int	ft_init_env(t_list **is_env, char **env)
{
	int	err;
	int	i;

	err = 0;
	i = 0;
	while (!err && env && env[i])
	{
		err = ft_add2list(is_env, env[i]);
		i++;
	}
	if (!env || !i)
		err = 1;
	return (err);
}
