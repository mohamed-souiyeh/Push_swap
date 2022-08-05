/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:49:17 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/09 17:04:30 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H

# define CHECKER_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_checker
{
	int		*stack_a;
	int		*stack_b;
	char	*instructions[11];
	void	(*operation_nb[11])(struct s_checker *data, char c);
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
void	my_putchar(const char *s, int *i, const char **str);
void	ft_bzero(void	*s, size_t	n);
void	*ft_calloc(size_t count, size_t size);
int		ft_strlen(char	*s);
long	ft_atoi(const char *str);
char	*ft_strjoin(int size, char **strs, char *sep);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char	*dst, const	char	*src, size_t	dstsize);
int		ft_strncmp(const	char	*s1, const	char	*s2, size_t	n);
char	*ft_strchr(const char *s, int c);

//checker
void	check_duplicate(int *stack, int index);
void	operations_initializer(void (*operation_nb[11]) \
(t_struct *data, char c));
void	instructions_initializer(char **instructions);
void	process_data(char ***av, int *ac);
char	*get_next_line(int fd);

//checker_utils
int		*fill_stack_a(int size, char **from, int **stack_b);
void	initialize_struct(t_struct **data, int ac, char **av);
int		check_sorted(t_struct *data);
int		ft_strcmp(char	*s1, char	*s2);
void	decide(t_struct *data, char *str);

//operations_utils
void	ft_switch(int *stack);
void	put_from_to(int	*stack_1, int *stack_2);
void	rotate_assist(int *stack);
void	reverse_rotate_assist(int *stack);

//operations
void	swap(t_struct *data, char c);
void	push(t_struct *data, char c);
void	rotate(t_struct *data, char c);
void	reverse_rotate(t_struct *data, char c);

#endif
