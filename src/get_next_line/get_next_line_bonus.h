/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:20:58 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 15:53:11 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 11
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include "../gc/garbage.h"
# include <string.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchrr(const char *str, int search_str);
char	*ft_strdupps(const char *str1);
void	fireforce(char **stored, char **allocated);
char	*ft_substrr(char const *s, unsigned int start, size_t len);
char	*ft_strrjoin(char *s1, char *s2);
void	allocation(char **stored, char **allocated);
size_t	ft_strlen(const char *str);
char	*returned_line(char **stored, int readen);
int		ft_strcmpp(char *s1, char *s2);

#endif