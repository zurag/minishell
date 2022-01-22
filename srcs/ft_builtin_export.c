/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:20:17 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/22 23:34:27 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	ft_print_env(t_list **is_head_env)
{
	t_env	**ls_head_env;
	int		i;

	i = 0;
	ls_head_env = ft_sortenv(is_head_env);
	while (ls_head_env && ls_head_env[i])
	{
		printf("declare -x ");
		printf("%s=\"", ls_head_env[i]->name);
		if (ft_getenv(*is_head_env, ls_head_env[i]->name))
			printf("%s\"\n", ft_getenv(*is_head_env, ls_head_env[i]->name));
		else
			printf("\"\n");
		i++;
	}
	free(ls_head_env);
}

static int	ft_has_eql(char *str, t_mshl *data)
{
	t_list	*ls_tmp_head;

	if (str && !ft_isalpha(*str))
		return (1);
	ls_tmp_head = ft_search_dubname(&data->head_env, str);
	if (ls_tmp_head)
		return (1);
	return (0);
}

char	*get_name(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	temp = ft_substr(s, 0, i);
	return (temp);
}

int	ft_check_name(char *name)
{
	if (ft_isalpha(name[0]) || name[0] == '_')
		return (1);
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (0);
}

void	ft_builtin_export(t_mshl *data)
{
	int		i;
	// char	*name;

	i = 1;
	while (data->cmd->arguments[i])
	{
		// name = get_name();
		// if (ft_check_name(data->cmd->arguments[i]))

		if (!ft_has_eql(data->cmd->arguments[i], data))
		{

		}
		i++;
	}
	if (i == 1)
		ft_print_env(&data->head_env);
}
