/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:13:06 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/15 17:17:23 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add2list(t_list **is_head_env, char *i_str)
{
	t_env	*ls_content;
	char	**ls_val_env;
	t_list	*ls_new_node;

	ls_content = malloc(sizeof(t_env));
	if (!is_head_env || !i_str || !ls_content)
		return (1);
	ls_val_env = ft_split(i_str, '=');
	if (!ls_val_env)
		return (1);
	ls_content->name = ls_val_env[0];
	ls_content->value = ls_val_env[1];
	ls_new_node = ft_lstnew(ls_content);
	ft_lstadd_back(is_head_env, ls_new_node);
	free(ls_val_env);
	return (0);
}

int	ft_insnewlst(t_list **is_head, char *name, char *val)
{
	t_env	*content;

	content = malloc(sizeof(t_env));
	if (!is_head || !name || !val || !content)
		return (1);
	content->name = ft_calloc(ft_strlen(name) + 1, sizeof(char));
	content->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
	if (!content->name || !content->value)
		return (1);
	content->name = ft_memcpy(content->name, name, ft_strlen(name));
	content->value = ft_memcpy(content->value, val, ft_strlen(val) + 1);
	ft_lstadd_back(is_head, ft_lstnew(content));
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

t_list	**ft_init_env(char **env)
{
	int		err;
	int		i;
	t_list	**ls_head_env;

	err = 0;
	i = 0;
	ls_head_env = (t_list **)malloc(sizeof(t_list *));
	if (!ls_head_env)
	{
		ft_print_error(ls_head_env, "Malloc returns error", 0);
		return (NULL);
	}
	while (!err && env && env[i])
		err = ft_add2list(ls_head_env, env[i++]);
	if (err != 0 || !i)
	{
		ft_print_error(ls_head_env, "Raised error in adding env's node to list", 0);
		ft_free_env(ls_head_env);
		return (NULL);
	}
	return (ls_head_env);
}
