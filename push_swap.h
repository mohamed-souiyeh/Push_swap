/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:42:45 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/10 21:23:22 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H

# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_struct
{
	int	*stack_a;
	int	*stack_b;
	int	*sorted;
	int	total;
	int	offset;
	int	midle;
	int	start;
	int	end;
	int	big_val_index;
	int	down;
	int	up;
	int	lower;
	int	upper;
}	t_struct;

//custom_functions
int		ft_printf(const char *str, ...);
void	ft_putchar(unsigned long c, int *i);
void	ft_putstr(unsigned long str, int *i);
void	ft_putptr(unsigned long ptr, int *i);
void	ft_puthex(unsigned long nb, int *i);
void	ft_putbig(unsigned long nb, int *i);
void	ft_putnbr(unsigned long n, int *i);
void	ft_putunsign(unsigned long n, int *i);
void	ft_putnbr_base(unsigned long int nb, char *base, int *i);
void	ft_putnbr_help(int n, int *i);
void	ft_putunsign_help(unsigned int n, int *i);
int		ft_getindex(const char *s, char c);
char	*ft_strchr(const char *s, int c);
void	my_putchar(const char *s, int *i, const char **str);
void	ft_bzero(void	*s, size_t	n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const	char	*s);
long	ft_atoi(const char *str);
char	*ft_strjoin(int size, char **strs, char *sep);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char	*dst, const	char	*src, size_t	dstsize);
int		ft_strncmp(const	char	*s1, const	char	*s2, size_t	n);
char	*ft_strchr(const char *s, int c);

//push_swap
void	sort5(t_struct *data);
void	process_data(char ***av, int *ac);

//optemize_operations
void	print(char *instruction);
void	sort3(int *stack);
int		check_if_in(t_struct *data);
void	change_values(t_struct *data);
void	dump_a_to_b(t_struct *data);

//sorter
void	dump_b_helper(t_struct *data);
int		get_big_index(t_struct *data);
void	decide(t_struct *data);
void	dump_b_to_a(t_struct *data);
void	sorter(t_struct *data);
void	escelate_privilege(t_struct *data);

//initialiser
void	initialize_struct(t_struct **data, int ac, char **av);
int		*fill_and_sort(int *stack_a, int *total);
int		calculat_offset(int total_nums);

//filling_stack
int		*fill_stack_a(int size, char **from, int **stack_b);
void	check_duplicate(int *stack, int index);
void	reverse_rotate(int *stack, char c);

//operations
void	ft_switch(int *stack, char c);
void	swap(int *stack_a, int *stack_b);
void	put_from_to(int	*stack_1, int *stack_2, char c);
void	push(char c, int *stack_a, int *stack_b);
void	rotate(int *stack, char c);

#endif