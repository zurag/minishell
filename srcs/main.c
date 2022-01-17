/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:39:55 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/17 22:22:07 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_list		*ls_head_env;
	extern char	**environ;

	ls_head_env = ft_init_env(environ);
	if (!ls_head_env)
		return(0);
	ft_putenv(&ls_head_env, "?", "0");
	ft_run_prompt(&ls_head_env);
	return (0);
}
/***********************************************
 * TESTING UNSET FUNC
 **********************************************/
int	test_unset(t_list **is_head_env)
{
	char	**args;
	int		i;

	args = NULL;
	i = 0;
	args = malloc(sizeof(char *) * 4);
	args[3] = NULL;
	while (i < 3)
	{
		if (!(args[i] = malloc(sizeof(char) * 5)))
			return (printf("ERROR MALLOC!\n"));
		args[i][4] = '\0';
		ft_memccpy(args[i], "LAN ", '\0', ft_strlen(args[i]));
		i++;
	}
	ft_builtin_unset(is_head_env, args);
	return (0);
}

void	ft_run_prompt(t_list **is_head_env)
{
	char	*line_read;
	// t_mini	**ls_head_cmd;

	set_input_signals();
	ft_builtin_env(is_head_env); // test
	ft_builtin_pwd(is_head_env); // test
	printf("\n\nTEST UNSET\n");
	test_unset(is_head_env);
	while (1)
	{
		line_read = readline("minishell>");
		if (!line_read)
		{
			free(line_read);
			ft_exit(is_head_env);
		}
		if (!ft_strlen(line_read))
		{
			free(line_read);
			continue ;
		}
		add_history(line_read);
		// parser(line_read, &ls_head_cmd);
		// ft_execute(is_head_env, &ls_head_cmd);
		free (line_read);
	}
}

void	ft_exit(t_list **is_head_env)
{
	int	nbr;

	nbr = ft_atoi(ft_getenv(*is_head_env, "?"));
	if (is_head_env)
		ft_free_env(is_head_env);
	// if (ctt)
	// 	ft_free_env(ctt, 1);
	exit(nbr);
}
