/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:24:17 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/09 16:27:02 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_gnl_strjoin(char **s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*final;
	int		i;

	if (*s1 == NULL || s2 == NULL)
		return (ft_strdup(""));
	s1len = ft_strlen(*s1);
	s2len = ft_strlen(s2);
	final = (char *)ft_calloc(s1len + s2len + 1, sizeof(char));
	if (final == NULL)
		return (NULL);
	i = -1;
	while (s1[0][++i])
		final[i] = s1[0][i];
	i--;
	while (s2[(++i) - (int)s1len])
		final [i] = s2[i - (int)s1len];
	free(*s1);
	*s1 = NULL;
	return (final);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*cpy;

	if (s1 == NULL)
		return (ft_strdup(""));
	cpy = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (cpy == NULL)
		return (0);
	i = 0;
	while (*s1)
		cpy[i++] = *s1++;
	return (cpy);
}
