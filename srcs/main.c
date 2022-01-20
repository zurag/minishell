/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:39:55 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/20 21:36:13 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// t_mini	**ls_head_cmd;

	rl_catch_signals = 0;
	set_input_signals();
	// ft_builtin_env(&data->head_env); // test
	// ft_builtin_pwd(&data->head_env); // test
	// printf("HOME=%s\n", ft_getenv(data->head_env, "HOME")); // test
	while (1)
	{
		line_read = readline("minishell>");
		if (!line_read)
		{
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

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	free(cmd->arguments);
	if (cmd->in_file)
		close(cmd->in_file);
	if (cmd->out_file)
		close(cmd->out_file);
}

void	free_mshl(t_mshl *mini)
{
	int	i;

	i = 0;
	while (i < mini->count_cmd)
	{
		free_cmd(mini->cmd + i);
		i++;
	}
	free(mini->cmd);
}
