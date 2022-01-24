/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:39:55 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/24 22:12:06 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_mini(t_mshl *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mini->count_cmd)
	{
		if (mini->cmd[i].cmd)
		{
			printf(" nomber %d cmd = %s\n", i +1, mini->cmd[i].cmd);
			while (mini->cmd[i].arguments[j])
			{
				printf(" arg ==  %s\n", mini->cmd[i].arguments[j]);
				j++;
			}
			j = 0;
		}
		printf("fd_in %d, fd_out %d\n", mini->cmd[i].in_file, mini->cmd[i].out_file);
		i++;
	}
}

int	main(void)
{
	t_mshl		data;
	extern char	**environ;

	data.head_env = ft_init_env(environ);
	if (!data.head_env)
		return(0);
	ft_putenv(&data.head_env, "?", "0");
	ft_run_prompt(&data);
	return (0);
}

void	ft_run_prompt(t_mshl *data)
{
	char	*line_read;

	rl_catch_signals = 0;
	while (1)
	{
		set_input_signals();
		line_read = readline("\001\033[1;92m\002minishell> \001\033[0m\002");
		if (!line_read)
		{
			ft_putstr_fd("exit\n", 1);
			free(line_read);
			ft_exit(&data->head_env);
		}
		if (!ft_strlen(line_read))
		{
			free(line_read);
			continue ;
		}
		add_history(line_read);
		parser(line_read, data);
		print_mini(data);
		// ft_execute(data);
		free_mshl(data);
	}
}

void	ft_exit(t_list **is_head_env)
{
	int	nbr;

	nbr = ft_atoi(ft_getenv(*is_head_env, "?"));
	if (is_head_env)
		ft_free_env(is_head_env);
	exit(nbr);
}
