/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:06:08 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 21:25:05 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calculat_offset(int total_nums)
{
	if (total_nums < 5)
		return (1);
	if (total_nums < 10)
		return (total_nums / 5);
	else if (total_nums < 150)
		return (total_nums / 6);
	else
		return (total_nums / 13);
}

int	*eleminate_top_3(int *stack, int size)
{
	int	*update;
	int	i;

	update = ft_calloc(size - 3, sizeof(int));
	if (!update)
		exit(1);
	i = -1;
	while (++i < size - 3)
		update[i] = stack[i];
	free(stack);
	return (update);
}

void	sort(int *stack_a, int *sorted)
{
	int	i;
	int	j;

	i = -1;
	while (++i < stack_a[0])
	{
		j = 0;
		while (++j < stack_a[0])
		{
			if (sorted[j - 1] > sorted[j])
			{
				sorted[j] ^= sorted[j - 1];
				sorted[j - 1] ^= sorted[j];
				sorted[j] ^= sorted[j - 1];
			}
		}
	}
}

int	*fill_and_sort(int *stack_a, int *total)
{
	int	i;
	int	*sorted;

	sorted = ft_calloc(stack_a[0], sizeof(int));
	if (!sorted)
		exit(1);
	i = -1;
	while (++i < stack_a[0])
		sorted[i] = stack_a[i + 1];
	sort(stack_a, sorted);
	if (stack_a[0] > 5)
	{
		sorted = eleminate_top_3(sorted, stack_a[0]);
		*total = stack_a[0] - 3;
	}
	else
		*total = stack_a[0];
	return (sorted);
}

void	initialize_struct(t_struct **data, int ac, char **av)
{
	(*data) = ft_calloc(1, sizeof(t_struct));
	if (!(*data))
		exit(1);
	(*data)->stack_a = fill_stack_a(ac, av, &((*data)->stack_b));
	(*data)->sorted = fill_and_sort((*data)->stack_a, &((*data)->total));
	(*data)->offset = calculat_offset((*data)->total);
	(*data)->midle = (*data)->total / 2;
	(*data)->big_val_index = (*data)->total - 1;
	(*data)->start = (*data)->midle - (*data)->offset;
	(*data)->end = (*data)->midle + (*data)->offset;
	(*data)->down = 0;
	(*data)->up = 0;
	(*data)->lower = 0;
	(*data)->upper = 0;
}
