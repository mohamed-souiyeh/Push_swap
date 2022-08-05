/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:26:01 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/09 17:05:02 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

char	*handel_the_shit(char **saved);
char	*free_it(char **target);
char	*handel_the_shit(char **saved);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
int		ft_strlen(char *s);
char	*ft_gnl_strjoin(char **s1, char *s2);
char	*ft_strdup(char *s1);
void	*ft_calloc(size_t count, size_t size);

#endif