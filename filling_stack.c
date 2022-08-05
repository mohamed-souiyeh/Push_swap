/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:44:01 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 22:03:32 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	check_duplicate(int *stack, int index)
{
	int	i;

	i = index;
	while (--i > 0)
	{
		if (stack[index] == stack[i])
			exit(ft_printf("Error\n"));
	}
}

//an intruder that belongs to operations file
void	reverse_rotate(int *stack, char c)
{
	int	holder;
	int	control;

	holder = stack[1];
	control = 1;
	while (control < stack[0])
	{
		stack[control] = stack[control + 1];
		control++;
	}
	stack[control] = holder;
	if (c == 'a')
		print("rra");
	else if (c == 'b')
		print("rrb");
}
