/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:39:55 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/20 21:02:02 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
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
/***********************************************
 * TESTING UNSET FUNC
 **********************************************/
// int	test_unset(t_mshl *data)
// {
// 	char	**args;
// 	int		i;

// 	// args = NULL;
// 	// i = 0;
// 	// data->cmd->arguments = (char **)malloc(sizeof(char *) * 4);
// 	// data->cmd->arguments[3] = NULL;
// 	// while (i < 3)
// 	// {
// 	// 	if (!(data->cmd->arguments[i] = malloc(sizeof(char) * 5)))
// 	// 		return (printf("ERROR MALLOC!\n"));
// 	// 	data->cmd->arguments[i][4] = '\0';
// 	// 	ft_memccpy(data->cmd->arguments[i], "LAN ", '\0', ft_strlen(data->cmd->arguments[i]));
// 	// 	i++;
// 	// }
// 	// ft_builtin_unset(data);
// 	return (0);
// }

void	ft_run_prompt(t_mshl *data)
{
	char	*line_read;
	// t_mini	**ls_head_cmd;

	rl_catch_signals = 0;
	set_input_signals();
	ft_builtin_env(&data->head_env); // test
	ft_builtin_pwd(&data->head_env); // test
	// printf("\n\nTEST UNSET\n");
	// test_unset(data);
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
		// parser(line_read, data);
		// ft_execute(data);
		free (line_read);
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

void	free_mini(t_mini *mini)
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
