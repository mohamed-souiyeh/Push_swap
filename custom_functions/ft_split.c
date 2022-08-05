/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:51:29 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/07 18:22:02 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../push_swap.h"

static	int	wc(const char *s, char c)
{
	int	counter;
	int	flag;

	flag = 1;
	counter = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			flag = 1;
		}
		if ((*s != c && flag == 1) && *s)
		{
			counter++;
			flag = 0;
		}
		if (*s)
			s++;
	}
	return (counter + 1);
}

static	size_t	len_count(const	char *s, char c)
{
	if (ft_strchr(s, c))
		return ((size_t)(ft_strchr(s, c) - s) + 1);
	else
		return (ft_strlen(s) + 1);
}

static	char	**abortmission(char **final, int i)
{
	if (i != 0)
	{
		while (i >= 0)
		{
			free(final[i]);
			i--;
		}
	}
	free(final);
	return (NULL);
}

static	char	**fill_it(const	char *s, char c, char **final)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			flag = 1;
		}
		if (*s != c && flag == 1 && *s)
		{	
			final[++i] = (char *)ft_calloc(len_count(s, c), sizeof(char));
			if (final[i] == NULL)
				return (abortmission(final, i));
			ft_strlcpy(final[i], s, len_count(s, c));
			flag = 0;
		}
		if (*s)
			s++;
	}
	return (final);
}

char	**ft_split(const char *s, char c)
{
	char	**final;

	if (s == NULL)
		return (NULL);
	final = (char **)ft_calloc((size_t)wc(s, c), sizeof(char *));
	if (final == NULL)
		return (NULL);
	final[0] = ft_itoa(wc(s, c));
	final = fill_it(s, c, final);
	return (final);
}
