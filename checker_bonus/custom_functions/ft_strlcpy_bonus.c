/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:44:17 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/09 16:27:37 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

size_t	ft_strlcpy(char	*dst, const	char	*src, size_t	dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen((char *)src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (*src && i < dstsize - 1)
	{
		*dst = *src;
		i++;
		dst++;
		src++;
	}
	*dst = '\0';
	return (srclen);
}
