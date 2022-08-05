/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:42:42 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/04 00:28:14 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_switch(int *stack, char c)
{
	int	head;

	head = stack[0];
	stack[head] = stack[head] + stack[head - 1];
	stack[head - 1] = stack[head] - stack[head - 1];
	stack[head] = stack[head] - stack[head - 1];
	if (c == 'a')
		print("sa");
	else if (c == 'b')
		print("sb");
}

void	swap(int *stack_a, int *stack_b)
{
	if (stack_a && !stack_b)
		ft_switch(stack_a, 'a');
	else if (stack_b && !stack_a)
		ft_switch(stack_b, 'b');
}

void	put_from_to(int	*stack_1, int *stack_2, char c)
{
	stack_2[stack_2[0] + 1] = stack_1[stack_1[0]];
	stack_1[stack_1[0]] = 0;
	stack_1[0]--;
	stack_2[0]++;
	if (c == 'a')
		print("pa");
	if (c == 'b')
		print("pb");
}

void	push(char c, int *stack_a, int *stack_b)
{
	if (c == 'a' && stack_b[0])
		put_from_to(stack_b, stack_a, c);
	else if (c == 'b' && stack_a[0])
		put_from_to(stack_a, stack_b, c);
}

void	rotate(int *stack, char c)
{
	int	holder;
	int	control;

	holder = stack[stack[0]];
	control = stack[0];
	while (control > 1)
	{
		stack[control] = stack[control - 1];
		control--;
	}
	stack[control] = holder;
	if (c == 'a')
		print("ra");
	else if (c == 'b')
		print("rb");
}
