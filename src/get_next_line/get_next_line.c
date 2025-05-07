/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:21:25 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/28 13:25:36 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i])
		i++;
	return (i);
}

void	allocation(char **stored, char **allocated)
{
	if (!*stored)
	{
		*stored = ft_strdup("");
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

void	fireforce(char **stored, char **allocated)
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
		*stored = ft_strdup(pos + 1);
		if (*stored && **stored == '\0')
		{
			free(*stored);
			*stored = NULL;
		}
		*(pos + 1) = '\0';
		return (temp_saved);
	}
	temp_saved = ft_strdup(*stored);
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
		return (fireforce(&stored, &allocated), NULL);
	readen = 1;
	while (!(ft_strchr(stored, '\n')) && readen > 0)
	{
		readen = read(fd, allocated, BUFFER_SIZE);
		if (readen == 0)
			break ;
		if (readen == -1)
			return (fireforce(&stored, &allocated), NULL);
		allocated[readen] = '\0';
		stored = ft_strjoin(stored, allocated);
		if (!stored)
			return (fireforce(&stored, &allocated), NULL);
	}
	if (ft_strcmp(stored, "") == 0)
		return (fireforce(&stored, &allocated), NULL);
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
