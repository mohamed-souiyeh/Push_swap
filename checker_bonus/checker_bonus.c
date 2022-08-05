/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:16:34 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 22:18:34 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	process_data(char ***av, int *ac)
{
	char	*tmp;

	(*av)[1] = ft_strjoin(*ac - 1, *av + 1, " ");
	tmp = (*av)[1];
	*av = ft_split((*av)[1], ' ');
	free(tmp);
	*ac = ft_atoi((*av)[0]);
}

void	instructions_initializer(char **instructions)
{
	instructions[0] = "sa";
	instructions[1] = "sb";
	instructions[2] = "ss";
	instructions[3] = "pa";
	instructions[4] = "pb";
	instructions[5] = "ra";
	instructions[6] = "rb";
	instructions[7] = "rr";
	instructions[8] = "rra";
	instructions[9] = "rrb";
	instructions[10] = "rrr";
}

void	operations_initializer(void (*operation_nb[11])(t_struct *data, char c))
{
	operation_nb[0] = &swap;
	operation_nb[1] = &swap;
	operation_nb[2] = &swap;
	operation_nb[3] = &push;
	operation_nb[4] = &push;
	operation_nb[5] = &rotate;
	operation_nb[6] = &rotate;
	operation_nb[7] = &rotate;
	operation_nb[8] = &reverse_rotate;
	operation_nb[9] = &reverse_rotate;
	operation_nb[10] = &reverse_rotate;
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

int	main(int ac, char **av)
{	
	t_struct	*data;
	char		*str;

	if (ac == 1)
		return (0);
	else
		process_data(&av, &ac);
	initialize_struct(&data, ac, av);
	str = *av;
	while (str)
	{
		str = get_next_line(0);
		if (str)
			decide(data, str);
	}
	if (!check_sorted(data))
		write (1, "OK\n", 3);
	else
		write (1, "KO\n", 3);
	return (0);
}
