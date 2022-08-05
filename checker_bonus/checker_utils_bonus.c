/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 14:35:20 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 21:25:05 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	*fill_stack_a(int size, char **from, int **stack_b)
{
	int	*final;
	int	i;

	final = ft_calloc(size, sizeof(int));
	if (!final)
		exit(1);
	i = 1;
	final[0] = size - 1;
	while (i < final[0] + 1)
	{
		final[i++] = ft_atoi(from[--size]);
		check_duplicate((int *)final, i - 1);
	}
	*stack_b = ft_calloc(final[0] + 1, sizeof(int));
	if (!*stack_b)
		exit(1);
	return (final);
}

void	initialize_struct(t_struct **data, int ac, char **av)
{
	(*data) = ft_calloc(1, sizeof(t_struct));
	if (!(*data))
		exit(1);
	(*data)->stack_a = fill_stack_a(ac, av, &((*data)->stack_b));
	instructions_initializer((*data)->instructions);
	operations_initializer((*data)->operation_nb);
}

int	check_sorted(t_struct *data)
{
	int	i;

	i = data->stack_a[0];
	while (i > 1 && data->stack_a[i] < data->stack_a[i - 1])
		i--;
	return (i - 1);
}

int	ft_strcmp(char	*s1, char	*s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	decide(t_struct *data, char *str)
{
	int	i;

	i = -1;
	while (++i < 11)
	{
		if (ft_strcmp(data->instructions[i], str) == 0)
		{
			data->operation_nb[i](data, str[ft_strlen(str) - 1]);
			return ;
		}
	}
	exit(ft_printf("Error\n"));
}
