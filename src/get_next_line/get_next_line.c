/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:21:25 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:08 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	allocation(char **stored, char **allocated)
{
	if (!*stored)
	{
		*stored = ft_strdupp("");
		if (!*stored)
			*stored = NULL;
	}
	*allocated = malloc((size_t)BUFFER_SIZE + 1);
	if (!*allocated)
	{
		if (*stored)
			free(*stored);
		*stored = NULL;
	}
}

void	fireforcee(char **stored, char **allocated)
{
	free(*stored);
	*stored = NULL;
	free(*allocated);
	allocated = NULL;
}

char	*returned_line(char **stored, int readen)
{
	char	*temp_saved;
	char	*pos;

	if (readen > 0)
	{
		temp_saved = *stored;
		pos = ft_strchr(temp_saved, '\n');
		*stored = ft_strdupp(pos + 1);
		if (*stored && **stored == '\0')
		{
			free(*stored);
			*stored = NULL;
		}
		*(pos + 1) = '\0';
		return (temp_saved);
	}
	temp_saved = ft_strdupp(*stored);
	free(*stored);
	*stored = NULL;
	return (temp_saved);
}

char	*get_next_line(int fd)
{
	char			*allocated;
	int				readen;
	static char		*stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	allocation(&stored, &allocated);
	if (!stored || !allocated)
		return (fireforcee(&stored, &allocated), NULL);
	readen = 1;
	while (!(ft_strchr(stored, '\n')) && readen > 0)
	{
		readen = read(fd, allocated, BUFFER_SIZE);
		if (readen == 0)
			break ;
		if (readen == -1)
			return (fireforcee(&stored, &allocated), NULL);
		allocated[readen] = '\0';
		stored = ft_strrjoin(stored, allocated);
		if (!stored)
			return (fireforcee(&stored, &allocated), NULL);
	}
	if (ft_strcmp(stored, "") == 0)
		return (fireforcee(&stored, &allocated), NULL);
	return (free(allocated), returned_line(&stored, readen));
}
// int main()
// {
//     int i = 1;
//     int fd = open("files.txt", O_RDONLY | O_CREAT, 0644);
//     if (fd == -1)
//         return (0);
//     char *s = get_next_line(fd);
//     printf("[%d] : %s", i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
//     s = get_next_line(fd);
//     printf("[%d] : %s", ++i, s);
//     free(s);
// }
