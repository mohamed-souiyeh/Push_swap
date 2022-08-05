/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operations_utils_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:24:32 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/09 16:26:04 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	ft_switch(int *stack)
{
	int	head;

	head = stack[0];
	stack[head] = stack[head] + stack[head - 1];
	stack[head - 1] = stack[head] - stack[head - 1];
	stack[head] = stack[head] - stack[head - 1];
}

void	put_from_to(int	*stack_1, int *stack_2)
{
	stack_2[stack_2[0] + 1] = stack_1[stack_1[0]];
	stack_1[stack_1[0]] = 0;
	stack_1[0]--;
	stack_2[0]++;
}

void	rotate_assist(int *stack)
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
}

void	reverse_rotate_assist(int *stack)
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
}
