/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:08:50 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/09 16:27:37 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

static	int	aloclen(int n)
{
	int	len;

	len = 1;
	if (n > 0)
		len = 0;
	else if (n < 0)
		n *= -1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		nb;

	nb = -1;
	len = aloclen(n);
	str = (char *)ft_calloc((size_t)(len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n == -2147483648 && ft_strlcpy(str, "-2147483648", 12))
		return (str);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (++nb < len && n)
	{
		str[len - nb - 1] = (char)((n % 10) + 48);
		n /= 10;
	}
	return (str);
}
