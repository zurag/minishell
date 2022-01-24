/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:34:33 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/24 14:46:14 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_builtin_cd(t_mshl *d)
{
	int		err;
	char	*new;

	if (!d || !d->head_env || !d->cmd->arguments[0])
		return (1);
	if (!ft_strlen(d->cmd->arguments[1]))
		err = chdir(ft_getenv(d->head_env, "HOME"));
	else
	{
		new = NULL;
		// new = ft_checktilde(d->head_env, d->cmd->arguments[1]);
		err = chdir(new);
		if (new)
			free(new);
	}

	return (err);
}
