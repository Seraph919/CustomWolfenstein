/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:14:48 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 15:52:07 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *str, int search_str);
char	*ft_strdupp(const char *str1);
void	fireforcee(char **stored, char **allocated);
char	*ft_substrr(char const *s, unsigned int start, size_t len);
char	*ft_strrjoin(char *s1, char *s2);
void	allocation(char **stored, char **allocated);
size_t	ft_strlenn(const char *str);
char	*returned_line(char **stored, int readen);
int		ft_strcmp(char *s1, char *s2);

#endif