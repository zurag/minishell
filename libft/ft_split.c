/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:54:14 by zurag             #+#    #+#             */
/*   Updated: 2021/05/02 16:16:57 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countword(char const *s, char c)
{
	int	i;
	int	count_word;

	count_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			count_word++;
			while (s[i] != c && s[i])
				i++;
		}
		if (!s[i])
			return (count_word);
		i++;
	}
	return (count_word);
}

void	ft_free_mem(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_len_word(char const *s, int *i, char c)
{
	int	len_word;

	len_word = 0;
	while (s[*i] && s[*i] != c)
	{
		*i += 1;
		len_word++;
	}
	return (len_word);
}

char	**ft_fill_array(char **array, char c, int count_word, char const *s)
{
	int		i;
	int		j;
	int		len_word;

	len_word = 0;
	j = 0;
	i = 0;
	while (j < count_word)
	{
		if (s[i] != c && s[i])
		{
			len_word = ft_len_word(s, &i, c);
			array[j] = ft_substr(s, i - len_word, len_word);
			if (!array[j])
			{
				ft_free_mem(array);
				return (NULL);
			}
			len_word = 0;
			j++;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count_word;

	count_word = ft_countword(s, c);
	array = malloc(sizeof(char *) * (count_word + 1));
	if (array == NULL)
		return (NULL);
	ft_fill_array(array, c, count_word, s);
	if (array == NULL)
		return (NULL);
	return (array);
}
