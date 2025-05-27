/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:43:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/27 18:58:47 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

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

char **remove_newlines(t_data *data)
{
    size_t i;
    if (!data->map)
        return (NULL);

    i = -1;
    while (++i < data->map_y)
    {
        if (data->map[i] && i != (data->map_y - 1))
            data->map[i] = strend_trim(data->map[i], 1, 0);
    }
    return (data->map);
}
