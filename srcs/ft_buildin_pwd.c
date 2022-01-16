/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:21:58 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/16 22:27:10 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_pwd(t_list **is_head_env)
{
	char	*str;

	str = ft_getenv(*is_head_env, "PWD");
	if (str)
		printf("%s\n", str);
	ft_print_error(is_head_env, NULL, 0);
}
