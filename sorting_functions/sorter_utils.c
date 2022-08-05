/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:01:06 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 23:02:41 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	just_print(char *holder)
{
	write (1, holder, ft_strlen(holder));
	write (1, "\n", 1);
}

void	print(char *instruction)
{
	static char	*holder;
	int			len;
	int			comp;

	if (!holder)
	{
		holder = instruction;
		return ;
	}
	comp = ft_strncmp(instruction, holder, 20);
	if ((instruction[comp] == 'a' && holder[comp] == 'b') \
		|| (instruction[comp] == 'b' && holder[comp] == 'a'))
	{
		len = ft_strlen(instruction);
		while (len-- > 0 && *holder != 'p')
		{
			write (1, holder, 1);
			if (len == 0)
				write (1, "\n", 1);
		}
		instruction = NULL;
	}
	else
		just_print(holder);
	holder = instruction;
}

void	sort3(int *stack)
{
	if (stack[0] > 2)
	{
		if (stack[stack[0]] > stack[1] && stack[stack[0]] > stack[2])
			rotate(stack, 'a');
		else if (stack[2] > stack[1] && stack[2] > stack[stack[0]])
			reverse_rotate(stack, 'a');
	}
	if (stack[stack[0]] > stack[stack[0] - 1])
		swap(stack, NULL);
}

void	change_values(t_struct *data)
{
	if (data->lower == data->offset)
	{
		if (data->start - data->offset < 0)
			data->start = 0;
		else
			data->start -= data->offset;
		data->lower = 0;
	}
	else if (data->upper == data->offset)
	{
		if (data->end + data->offset >= data->big_val_index)
			data->end = data->big_val_index + 1;
		else
			data->end += data->offset;
		data->upper = 0;
	}
}

void	dump_a_to_b(t_struct *data)
{
	while (data->stack_a[0] > 3)
	{
		if (data->stack_a[data->stack_a[0]] >= data->sorted[data->start] && \
			data->stack_a[data->stack_a[0]] <= data->sorted[data->end - 1])
		{
			push('b', data->stack_a, data->stack_b);
			if (data->stack_b[data->stack_b[0]] < data->sorted[data->midle])
			{
				data->lower++;
				if (data->stack_b[0] > 1)
					rotate(data->stack_b, 'b');
			}
			else
				data->upper++;
		}
		else
			rotate(data->stack_a, 'a');
		change_values(data);
	}
}
