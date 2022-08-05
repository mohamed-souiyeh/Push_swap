/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:51:45 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/10 19:22:37 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	prepare_for_big(t_struct *data)
{
	while (data->up > 1)
	{
		rotate(data->stack_a, 'a');
		data->up--;
		data->down++;
	}
	push('a', data->stack_a, data->stack_b);
	if (data->up == 1)
		swap(data->stack_a, NULL);
	data->big_val_index--;
}

void	decide(t_struct *data)
{
	if (!data->down || data->stack_b[data->stack_b[0]] > data->stack_a[1])
		escelate_privilege(data);
	else
		dump_b_helper(data);
}

void	check_up_down(t_struct *data)
{
	if (data->sorted[data->big_val_index] == data->stack_a[data->stack_a[0]])
		data->up--;
	else
	{
		reverse_rotate(data->stack_a, 'a');
		data->down--;
	}
	data->big_val_index--;
}

void	dump_b_to_a(t_struct *data)
{
	int	index;

	index = get_big_index(data);
	if (index == -1)
		return (check_up_down(data));
	if (index <= data->stack_b[0] / 2)
		while (index-- > 0)
			decide(data);
	else if (index > data->stack_b[0] / 2)
		while (data->stack_b[0] - (index++) > 0)
			reverse_rotate(data->stack_b, 'b');
	if (data->stack_b[data->stack_b[0]] == data->sorted[data->big_val_index])
		prepare_for_big(data);
}

void	sorter(t_struct *data)
{
	dump_a_to_b(data);
	sort3(data->stack_a);
	while (data->down || data->stack_b[0] || data->up)
		dump_b_to_a(data);
}
