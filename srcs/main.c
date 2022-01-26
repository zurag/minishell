/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:39:55 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/26 20:56:48 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_mshl		data;
	extern char	**environ;

	data.head_env = ft_init_env(environ);
	if (!data.head_env)
		return (0);
	rl_catch_signals = 0;
	ft_putenv(&data.head_env, "?", "0");
	ft_run_prompt(&data);
	return (0);
}

static void	ft_main_exit(char *line_read, t_mshl *data)
{
	ft_putstr_fd("exit\n", 1);
	free(line_read);
	ft_exit(data);
}

void	ft_run_prompt(t_mshl *data)
{
	char	*line_read;

	while (1)
	{
		set_input_signals();
		line_read = readline("\001\033[1;92m\002minishell> \001\033[0m\002");
		signal(SIGINT, &signal_handler2);
		if (!line_read)
			ft_main_exit(line_read, data);
		if (!ft_strlen(line_read))
		{
			free(line_read);
			continue ;
		}
		add_history(line_read);
		if (parser(line_read, data))
		{
			free(line_read);
			continue ;
		}
		executor(data);
		free_mshl(data);
	}
}

void	ft_exit(t_mshl *data)
{
	int	nbr;

	nbr = ft_atoi(ft_getenv(data->head_env, "?"));
	if (data->head_env)
		ft_free_env(&data->head_env);
	if (data->cmd && data->count_cmd > 0)
		free_mshl(data);
	exit(nbr);
}
