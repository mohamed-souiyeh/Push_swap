/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_we_need_help_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:48:42 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 21:59:22 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

void	my_putchar(const char *s, int *i, const char **str)
{
	if (*s == '%' && *(s + 1) == '%' && *s)
	{
		ft_putchar('%', i);
		(*str) += 2;
		return (my_putchar(*str, i, str));
	}
	else if (*s != '%' && *s)
		ft_putchar(*s, i);
}

void	ft_putnbr_help(int n, int *i)
{
	char	c;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(2, "-2147483648", 11);
			(*i) += 11;
			return ;
		}
		n = n * -1;
		write(2, "-", 1);
		(*i)++;
	}
	if (n < 10)
	{
		c = n + 48;
		write(2, &c, 1);
		(*i)++;
	}
	if (n > 9)
	{
		ft_putnbr_help(n / 10, i);
		ft_putnbr_help(n % 10, i);
	}
}

void	ft_putunsign_help(unsigned int n, int *i)
{
	char	c;

	if (n < 10)
	{
		c = n + 48;
		write(2, &c, 1);
		(*i)++;
	}
	if (n > 9)
	{
		ft_putunsign_help(n / 10, i);
		ft_putunsign_help(n % 10, i);
	}
}
