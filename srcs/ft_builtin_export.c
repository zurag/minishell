/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:20:17 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/26 14:22:10 by dtentaco         ###   ########.fr       */
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
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (0);
}

int	add_value(char *name, t_mshl *d, int num_cmd, int i)
{
	char	*value;
	int		flag;

	flag = 0;
	if (ft_check_name(name))
	{
		if (ft_isset('=', d->cmd[num_cmd].arguments[i]))
			value = get_value_env(d->cmd[num_cmd].arguments[i]);
		else
			value = get_value_env(d->cmd[num_cmd].arguments[++i]);
		if (ft_strlen(value))
			ft_putenv(&d->head_env, name, value);
		else
		{
			ft_putstr_fd("export: \'", 2);
			ft_putstr_fd(value, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			ft_print_error(&d->head_env, NULL, 1);
			free(value);
			return (-1);
		}
		free(value);
	}
	else
		return (-1);
	return (i);
}

void	ft_builtin_export(t_mshl *data, int num_cmd)
{
	int		i;
	char	*name;

	if (!data->cmd[num_cmd].arguments[1])
		return (ft_print_env(&data->head_env));
	i = 1;
	while (ft_strlen(data->cmd[num_cmd].arguments[i]))
	{
		name = get_name_env(data->cmd[num_cmd].arguments[i]);
		i = add_value(name, data, num_cmd, i);
		free(name);
		if (i == -1)
			return ;
		i++;
	}
	ft_print_error(&data->head_env, NULL, 0);
}
