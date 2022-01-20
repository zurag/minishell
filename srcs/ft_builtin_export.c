/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:20:17 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/20 20:25:21 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_env(t_list **is_head_env)
{
	t_env	**ls_head_env;
	int		i;

	i = 0;
	ls_head_env = ft_sortenv(is_head_env);
	while (ls_head_env && ls_head_env[i])
	{
		printf("%s=\"", ls_head_env[i]->name);
		if (ft_getenv(*is_head_env, ls_head_env[i]->name))
			printf("%s\"\n", ft_getenv(*is_head_env, ls_head_env[i]->name));
		else
			printf("\"\n");
		i++;
	}
	free(ls_head_env);
}

static int	ft_has_eql(char *str)
{
	if (str && (ft_strlen(str) < 3 || !ft_isalpha(*str)))
		return (0);
	while (str && *str)
	{
		if (!ft_isalnum(*str) && *str != '=')
			return (0);
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void	ft_builtin_export(t_mshl *data)
{
	int	i;

	i = 0;
	while (data->cmd->arguments[i])
	{
		if (ft_has_eql(data->cmd->arguments[i]))
		{
			printf("");
			// как хранятся данные в токенах?
		}

		i++;
	}
	if (i == 1)
		ft_print_env(&data->head_env);
}
