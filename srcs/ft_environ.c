/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:13:06 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/14 23:25:01 by dtentaco         ###   ########.fr       */
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

int	ft_insnewlst(t_list **head, char *name, char *val)
{
	t_env	*content;

	content = malloc(sizeof(t_env));
	if (!head || !name || !val || !content)
		return (1);
	content->name = ft_calloc(ft_strlen(name) + 1, sizeof(char));
	content->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
	if (!content->name || !content->value)
		return (1);
	content->name = ft_memcpy(content->name, name, ft_strlen(name));
	content->value = ft_memcpy(content->value, val, ft_strlen(val) + 1);
	ft_lstadd_back(head, ft_lstnew(content));
	return (0);
}

int	ft_putenv(t_list **is_head, char *name, char *val)
{
	t_env	*ls_ptr;
	t_list	*ls_tmp_head;

	ls_tmp_head = *is_head;
	while (ls_tmp_head)
	{
		ls_ptr = (t_env *)(ls_tmp_head->content);
		if (!ft_strncmp(ls_ptr->name, name, ft_strlen(name) + 1))
			break ;
		ls_tmp_head = ls_tmp_head->next;
	}
	if (ls_tmp_head)
	{
		free(ls_ptr->value);
		ls_ptr->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
		ls_ptr->value = ft_memcpy(ls_ptr->value, val, ft_strlen(val));
	}
	else
		return (ft_insnewlst(is_head, name, val));
	if (ls_ptr->value)
		return (0);
	else
		return (1);
}

char	*ft_getenv(t_list *is_head, char *i_str)
{
	t_env	*val;

	if (!is_head || !i_str)
		return (NULL);
	while (is_head)
	{
		val = (t_env *)(is_head->content);
		if (!ft_strncmp(val->name, i_str, ft_strlen(i_str) + 1))
			return (val->value);
		is_head = is_head->next;
	}
	return (NULL);
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
