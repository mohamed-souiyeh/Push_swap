# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 16:58:05 by msouiyeh          #+#    #+#              #
#    Updated: 2022/03/10 18:55:58 by msouiyeh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	push_swap
NAME_BONUS		=	checker

SRCS 			=	operations.c push_swap.c initializer.c filling_stack.c \
					sorting_functions/sorter.c sorting_functions/sorter_utils.c \
					custom_functions/ft_atoi.c custom_functions/ft_bzero.c custom_functions/ft_calloc.c \
					custom_functions/ft_functions_collection.c custom_functions/ft_functions_collection2.c \
					custom_functions/ft_itoa.c custom_functions/ft_printf.c custom_functions/ft_split.c \
					custom_functions/ft_strchr.c custom_functions/ft_strjoin.c custom_functions/ft_strlcpy.c \
					custom_functions/ft_strlen.c custom_functions/ft_strncmp.c custom_functions/ft_we_need_help.c \
					sorting_functions/sorter_utils_2.c

BONUS_SRCS		=	checker_bonus/custom_functions/ft_atoi_bonus.c checker_bonus/custom_functions/ft_bzero_bonus.c \
					checker_bonus/custom_functions/ft_calloc_bonus.c checker_bonus/custom_functions/ft_functions_collection_bonus.c \
					checker_bonus/custom_functions/ft_functions_collection2_bonus.c checker_bonus/custom_functions/ft_itoa_bonus.c \
					checker_bonus/custom_functions/ft_printf_bonus.c checker_bonus/custom_functions/ft_split_bonus.c \
					checker_bonus/custom_functions/ft_strchr_bonus.c checker_bonus/custom_functions/ft_strjoin_bonus.c \
					checker_bonus/custom_functions/ft_strlcpy_bonus.c checker_bonus/custom_functions/ft_strlen_bonus.c \
					checker_bonus/custom_functions/ft_strncmp_bonus.c checker_bonus/custom_functions/ft_we_need_help_bonus.c \
					checker_bonus/checker_bonus.c checker_bonus/checker_operations_bonus.c \
					checker_bonus/checker_operations_utils_bonus.c checker_bonus/checker_utils_bonus.c \
					checker_bonus/get_next_line/get_next_line_bonus.c checker_bonus/get_next_line/get_next_line_utils_bonus.c

OBJS			=	$(SRCS:.c=.o)

BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)

CFLAGS			= 	-Wall -Wextra -Werror -g

$(NAME)			:	$(OBJS)
					@cc $(CFLAGS) $(OBJS) -o $(NAME)
				
all				:	$(NAME)

bonus			:	$(NAME_BONUS)

$(NAME_BONUS)	:	$(BONUS_OBJS)
					@cc $(CFLAGS) $(BONUS_OBJS) -o $(NAME_BONUS)

c.o.			:
					cc $(CFLAGS) -c $<
	
clean			:
					@$(RM) $(OBJS)
					@$(RM) $(BONUS_OBJS)

fclean			:	clean
					@$(RM) $(NAME) $(NAME_BONUS)

re				:	fclean all

.PHONY			:	all clean fclean re