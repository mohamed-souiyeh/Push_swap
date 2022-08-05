/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:33:48 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/09 16:26:04 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	swap(t_struct *data, char c)
{
	if (c == 'a')
		ft_switch(data->stack_a);
	else if (c == 'b')
		ft_switch(data->stack_b);
	else if (c == 's')
	{
		ft_switch(data->stack_a);
		ft_switch(data->stack_b);
	}
}

void	push(t_struct *data, char c)
{
	if (c == 'a')
		put_from_to(data->stack_b, data->stack_a);
	else if (c == 'b')
		put_from_to(data->stack_a, data->stack_b);
}

void	rotate(t_struct *data, char c)
{
	if (c == 'a')
		rotate_assist(data->stack_a);
	else if (c == 'b')
		rotate_assist(data->stack_b);
	else if (c == 'r')
	{
		rotate_assist(data->stack_a);
		rotate_assist(data->stack_b);
	}
}

void	reverse_rotate(t_struct *data, char c)
{
	if (c == 'a')
		reverse_rotate_assist(data->stack_a);
	else if (c == 'b')
		reverse_rotate_assist(data->stack_b);
	else if (c == 'r')
	{
		reverse_rotate_assist(data->stack_a);
		reverse_rotate_assist(data->stack_b);
	}
}
