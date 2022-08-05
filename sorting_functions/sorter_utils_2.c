/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:29 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/10 12:13:40 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	dump_b_helper(t_struct *data)
{
	if (data->stack_b[0] > 1 && data->stack_b[data->stack_b[0] - 1] \
		== data->sorted[data->big_val_index])
		swap(NULL, data->stack_b);
	else
		rotate(data->stack_b, 'b');
}

int	get_big_index(t_struct *data)
{
	int	i;

	i = data->stack_b[0] + 1;
	while (--i > 0)
		if (data->stack_b[i] == data->sorted[data->big_val_index])
			return (data->stack_b[0] - i);
	return (-1);
}

void	escelate_privilege(t_struct *data)
{
	while (data->stack_a[data->stack_a[0]] < data->stack_b[data->stack_b[0]])
	{
		rotate(data->stack_a, 'a');
		data->up--;
		data->down++;
	}
	push('a', data->stack_a, data->stack_b);
	data->up++;
}
