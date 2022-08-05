/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:50:47 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 22:01:16 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

long	ft_atoi(const	char	*str)
{
	int		sign;
	long	final;

	final = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' && *(str + 1))
	{
		sign = -1;
		str++;
	}
	else if (*str == '+' && *(str + 1))
		str++;
	while (*str >= 48 && *str <= 57)
	{
		final = (final * 10) + (long)(*str - '0');
		str++;
	}
	final *= sign;
	if (*str || final > 2147483647 || final < -2147483648)
		exit(ft_printf("Error\n"));
	return (final);
}
