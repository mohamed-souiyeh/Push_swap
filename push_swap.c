/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:42:37 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/05/18 22:27:01 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	process_data(char ***av, int *ac)
{
	char	*tmp;

	(*av)[1] = ft_strjoin(*ac  - 1, *av + 1, " ");
	tmp = (*av)[1];
	*av = ft_split((*av)[1], ' ');
	free(tmp);
	*ac = ft_atoi((*av)[0]);
}

void	sort5(t_struct *data)
{
	while (data->stack_a[0] > 3)
	{
		if (data->stack_a[data->stack_a[0]] \
			== data->sorted[data->big_val_index] \
			|| data->stack_a[data->stack_a[0]] == data->sorted[0])
			push('b', data->stack_a, data->stack_b);
		else if (data->stack_a[1] == data->sorted[data->big_val_index] || \
			data->stack_a[1] == data->sorted[0])
			reverse_rotate(data->stack_a, 'a');
		else
			rotate(data->stack_a, 'a');
	}
	sort3(data->stack_a);
	while (data->stack_b[0])
	{
		push('a', data->stack_a, data->stack_b);
		if (data->stack_a[data->stack_a[0]] > \
			data->stack_a[data->stack_a[0] - 1])
			rotate(data->stack_a, 'a');
	}
}

int	check_sorted(t_struct *data)
{
	int	i;

	i = data->stack_a[0];
	while (i > 1 && data->stack_a[i] < data->stack_a[i - 1])
		i--;
	return (i - 1);
}

int	main(int ac, char **av)
{	
	t_struct	*data;

	if (ac == 1)
		return (0);
	else
		process_data(&av, &ac);
	initialize_struct(&data, ac, av);
	if (!check_sorted(data))
		return (0);
	if (data->stack_a[0] > 5)
		sorter(data);
	else
		sort5(data);
	print("");
	return (0);
}
