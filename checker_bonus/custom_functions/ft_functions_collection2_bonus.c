/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions_collection2_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:56:15 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 21:59:22 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

void	ft_putnbr(unsigned long nb, int *i)
{
	int	n;

	n = (int)nb;
	ft_putnbr_help(n, i);
}

void	ft_putunsign(unsigned long nb, int *i)
{
	unsigned int	n;

	n = (unsigned int)nb;
	ft_putunsign_help(n, i);
}

void	ft_putstr(unsigned long str, int *i)
{
	int	j;

	if (!str)
	{
		write(2, "(null)", 6);
		(*i) += 6;
		return ;
	}
	j = ft_strlen((char *)str);
	write(2, (const void *)str, j);
	(*i) += j;
}

int	ft_getindex(const char *s, char c)
{	
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] == c)
			return (j);
		j++;
	}
	return (-1);
}
