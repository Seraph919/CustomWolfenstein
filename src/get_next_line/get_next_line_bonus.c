/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:21:05 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/28 13:22:14 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*returned_line(char **stored, int readen)
{
	char	*temp_stored;
	char	*pos;

	if (readen > 0)
	{
		temp_stored = *stored;
		pos = ft_strchr(temp_stored, '\n');
		*stored = ft_strdup(pos + 1);
		*(pos + 1) = '\0';
		return (temp_stored);
	}
	temp_stored = ft_strdup(*stored);
	free(*stored);
	*stored = NULL;
	return (temp_stored);
}

void	fireforce(char **stored, char **allocated)
{
	free(*stored);
	*stored = NULL;
	free(*allocated);
	allocated = NULL;
}

char	*get_next_line(int fd)
{
	static char	*stored[1024];
	char		*allocated;
	int			readen;

	if ((fd < 0 || fd > 1024) || BUFFER_SIZE <= 0)
		return (NULL);
	allocation(&stored[fd], &allocated);
	if (!stored[fd] || !allocated)
		return (fireforce(&stored[fd], &allocated), NULL);
	readen = 1;
	while (!(ft_strchr(stored[fd], '\n')) && readen > 0)
	{
		readen = read(fd, allocated, BUFFER_SIZE);
		if (readen == 0)
			break ;
		if (readen == -1)
			return (fireforce(&stored[fd], &allocated), NULL);
		allocated[readen] = '\0';
		stored[fd] = ft_strjoin(stored[fd], allocated);
		if (!stored[fd])
			return (fireforce(&stored[fd], &allocated), NULL);
	}
	if (ft_strcmp(stored[fd], "") == 0)
		return (fireforce(&stored[fd], &allocated), NULL);
	return (free(allocated), returned_line(&stored[fd], readen));
}
