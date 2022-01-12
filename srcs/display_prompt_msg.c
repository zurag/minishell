/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt_msg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 02:22:12 by dtentaco          #+#    #+#             */
/*   Updated: 2022/01/12 03:31:30 by dtentaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathjoin(char *p1, char *p2)
{
	int		s1_len;
	char	*tmp_path;
	char	*tmp_path2;

	if (!p2 || !p1)
		return (NULL);
	s1_len = ft_strlen(p1);
	if (p1[s1_len - 1] == '/')
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2 + 1));
		else
			return (ft_strjoin(p1, p2));
	}
	else
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2));
		else
		{
			tmp_path = ft_strjoin(p1, "/");
			tmp_path2 = ft_strjoin(tmp_path, p2);
			free(tmp_path);
			return(tmp_path2);
		}
	}
}

char	*parse_home_path(char *path, int reverse_parse)
{
	char	*home_path;
	char	*new;

	if (!path)
		return (NULL);
	home_path = getenv("HOME");
	if (ft_strcmp(path, reverse_parse ? "~" : home_path))
		return (ft_strdup(path));
	if (reverse_parse)
		new = ft_pathjoin(home_path, path + 1);
	else
	{
		if (*(path + ft_strlen(home_path)) == '\0')
			new = ft_strdup("~");
		else
			new = ft_pathjoin("~", path + ft_strlen(home_path));
	}
	return (new);
}

void	print_prompt_msg(void)
{
	char	cwd[PATH_MAX];
	char	*parsed_cwd;

	getcwd(cwd, sizeof(cwd));
	parsed_cwd = parse_home_path(cwd, 0);
	printf("%s", parsed_cwd);
	free(parsed_cwd);
}
