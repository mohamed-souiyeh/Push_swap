/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:21:47 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/07 18:22:02 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../push_swap.h"

int	ft_strncmp(const	char	*s1, const	char	*s2, size_t	n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (n);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]
		&& s1[i] && s2[i] && i < n - 1)
		i++;
	return (i);
}
