/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:34:33 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/25 11:39:48 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_update_dir(t_list **head)
{
	int		err;
	char	*new_pwd;

	err = 0;
	ft_print_error(head, NULL, 0);
	err = ft_putenv(head, "OLDPWD", ft_getenv(*head, "PWD"));
	if (!err)
	{
		new_pwd = getcwd(NULL, 0);
		err = ft_putenv(head, "PWD", new_pwd);
		free(new_pwd);
	}
	return (err);
}

char	*ft_check_tilde(t_list **head, char *str)
{
	if (!ft_strlen(str) || *str != '~' || !ft_getenv(*head, "HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(ft_getenv(*head, "HOME"), str));
}

int		ft_builtin_cd(t_mshl *d, int num_cmd)
{
	int		err;
	char	*new_pwd;

	if (!d || !d->head_env || !d->cmd[num_cmd].arguments[0])
		return (1);
	if (!ft_strlen(d->cmd[num_cmd].arguments[1]))
		err = chdir(ft_getenv(d->head_env, "HOME"));
	else
	{
		new_pwd = ft_check_tilde(&d->head_env, d->cmd[num_cmd].arguments[1]);
		err = chdir(new_pwd);
		if (new_pwd)
			free(new_pwd);
	}
	if (err)
		ft_print_error(&d->head_env,  d->cmd[num_cmd].arguments[1], -1);
	else
	{
		err = ft_update_dir(&d->head_env);
		ft_print_error(&d->head_env, NULL, 0);
	}
	return (err);
}
