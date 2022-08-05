/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions_collection_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:15:07 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 21:59:22 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

void	ft_putchar(unsigned long c, int *i)
{
	char	p;

	p = (char)c;
	write(2, &p, 1);
	(*i)++;
}

void	ft_putnbr_base(unsigned long nb, char	*base, int *i)
{
	if (nb < 16)
	{
		write(2, &base[nb], 1);
		(*i)++;
		return ;
	}
	if (nb >= 16)
	{
		ft_putnbr_base((nb / 16), base, i);
		ft_putnbr_base((nb % 16), base, i);
	}
}

void	ft_putptr(unsigned long ptr, int *i)
{
	unsigned long	fake;

	fake = (unsigned long)ptr;
	write(2, "0x", 2);
	(*i) += 2;
	ft_putnbr_base(fake, "0123456789abcdef", i);
}

void	ft_puthex(unsigned long nb, int *i)
{
	ft_putnbr_base((unsigned int)nb, "0123456789abcdef", i);
}

void	ft_putbig(unsigned long nb, int *i)
{
	ft_putnbr_base((unsigned int)nb, "0123456789ABCDEF", i);
}
