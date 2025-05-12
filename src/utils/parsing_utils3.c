/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:47:47 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 17:48:18 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

char *strafter_type(char *str)
{
    if (!str)
        return (NULL);
    while (!is_white_space(*str))
        str++;
    if (*str == '\0')
        return (NULL);
    while (is_white_space(*str))
        str++;
    if (*str == '\0')
        return (NULL);
    else
        return (strend_trim(str, 1));
}

int	ft_strncmpp(const char *s1, const char *s2, size_t count)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < count)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < count)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char *strend_trim(char *str, size_t nbytes)
{
    if (!str)
        return (NULL);
    size_t end;
    char *returned;
    size_t i;

    i = -1;
    end = strlen(str);
    returned = alloc((sizeof(char) * end - nbytes) + 1, ALLOC);
    if (!returned)
        return (NULL);
    while (++i  < end - nbytes)
        returned[i] = str[i];
    returned[i] = '\0';
    // free(str); // do it after removing GC..
    return (returned);
}

bool above_checker(char **map, int y)
{
    int x;

    x = -1;
    if (!map || !map[y] )
        return (ERROR);
    while (map[y][++x])
    {
        if (is_white_space(map[y][x]) 
            && map[y - 1][x] && map[y - 1][x] == '0')
            return (ERROR);
    }
    if (map[y][x] == '\0' && map[y - 1][x] && map[y - 1][x] == '0')
        return (ERROR);
    return (SUCCESS);
}

bool is_void(char **map, size_t x, size_t y, size_t map_max)
{
    if ((map[y - 1][x] && is_white_space(map[y - 1][x]))
            || (y + 1 < map_max - 1 && map[y + 1] && map[y + 1][x] && is_white_space(map[y + 1][x])) 
            || ( x != 0 && is_white_space(map[y][x - 1])) 
            || (map[y][x + 1] && is_white_space(map[y][x + 1]))
            || !map[y][x + 1])
            return (true);
    if (y + 1 == map_max - 1)
    {
        if (above_checker(map, y + 1))
            return (true);
    }
    return (false);
}
