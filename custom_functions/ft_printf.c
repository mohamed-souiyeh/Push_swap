/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:33:44 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/07 18:22:02 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../push_swap.h"

void	do_it(void (*wands[8])(unsigned long, int *))
{
	wands[0] = ft_putchar;
	wands[1] = ft_putstr;
	wands[2] = ft_putnbr;
	wands[3] = ft_putnbr;
	wands[4] = ft_putunsign;
	wands[5] = ft_putptr;
	wands[6] = ft_puthex;
	wands[7] = ft_putbig;
}

int	ft_printf(const char *str, ...)
{
	va_list			ptr;
	void			(*wands[8])(unsigned long, int *);
	int				i;

	i = 0;
	do_it(wands);
	va_start(ptr, str);
	while (*str)
	{
		if (*str == '%' && ft_getindex("csdiupxX", *(str + 1)) >= 0)
		{
			wands[ft_getindex("csdiupxX", *(str + 1))]
			(va_arg(ptr, unsigned long), &i);
			str++;
		}
		else
			my_putchar(str, &i, &str);
		if (*str && *str != '%')
			str++;
	}
	va_end(ptr);
	return (0);
}

// int	main(void)
// {
// 	// char			c = 'a';
// 	// char			*s = "hello world!";
// 	// int				i = -1337;
// 	// unsigned int	nb = 1313371337;
// 	// void			*ptr = &i;
// 	ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%", 'A', 
//"42", 42, 42 ,42 , 42, 42);	
// 	// printf("%i\n",ft_printf("|%c,|", c));
// 	// printf("%i\n",printf("|%c,|", c));
// 	// printf("%i\n",ft_printf("|%s,|", s));
// 	// printf("%i\n",printf("|%s,|", s));
// 	// printf("%i\n",ft_printf("|%p,|", ptr));
// 	// printf("%i\n",printf("|%p,|", ptr));
// 	// printf("%i\n",ft_printf("|%d,|", i));
// 	// printf("%i\n",printf("|%d,|", i));
// 	// printf("%i\n",ft_printf("|%i,|", i));
// 	// printf("%i\n",printf("|%i,|", i));
// 	// printf("%i\n",ft_printf("|%u,|", nb));
// 	// printf("%i\n",printf("|%u,|", nb));
// 	// printf("%i\n",ft_printf("|%x,|", i));
// 	// printf("%i\n",printf("|%x,|", i));
// 	// printf("%i\n",ft_printf("|%X|", i));
// 	// printf("%i\n",printf("|%X|", i));
// 	// printf("%i\n",ft_printf("%%%%"));
// 	//printf("%i\n",printf(" %% "));
// 	return (0);
// }