/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:39:55 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/15 17:28:37 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_list		**ls_head_env;
	extern char	**environ;

	ls_head_env = ft_init_env(environ);
	if (!ls_head_env)
		return(0);
	ft_putenv(ls_head_env, "?", "0");
	ft_run_prompt(ls_head_env);
	return (0);
}

void	ft_run_prompt(t_list **is_head_env)
{
	char	*line_read;

	set_input_signals();
	ft_builtin_env(is_head_env); // test
	while (1)
	{
		line_read = readline("minishell>");
		if (line_read && *line_read)
			add_history(line_read);
		// parser(line_read, &mini);
		// execute(is_head_env);
		free (line_read);
	}
}
