/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:50:15 by asoudani          #+#    #+#             */
/*   Updated: 2025/06/20 11:28:47 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

char *skip_spaces(char *s)
{
    if (!s)
        return (NULL);
    while (is_white_space(*s))
        s++;
    if (*s == '\0')
        return (NULL);
    return (s);
}

int map_validation(char **map, int map_size, t_data *data)
{
    if (!map || !*map)
        return (ERROR);
    int i;

    i = 0;
    while (i < map_size)
    {
        if (i == 0)
        {
            if (str_validation(0, false, data) == false)
                return (ERROR);
        }
        else if(str_validation(i, i == map_size - 1, data) == false)
            return (ERROR);
        i++;
    }
    data->map = newlinecut(data);
    if (!data->map)
        return (ERROR);
    return (SUCCESS);
}

bool map_checker(char **map, t_data *data)
{
    int i;
    int k;
    bool player_found;

    i = -1;
    player_found = false;
    while (map[++i])
    {
        k = -1;
        while (map[i][++k])
        {
            if(not_in_str(map[i][k], VALIDCHARS))
                return (ERROR);
            if (not_in_str(map[i][k], "NWES") == false && player_found)
                return (ERROR);
            if (not_in_str(map[i][k], "NWES") == false)
            {
                data->player_char = map[i][k];
                player_found = true;
            }
        }
    }
    if (!player_found)
        return (ERROR);
    return (false);
}

int rgb_to_int(int r, int g, int b) 
{
    if (r < 0)
        r = 0;
    if (r > 255)
        r = 255;
    if (g < 0)
        g = 0;
    if (g > 255)
        g = 255;
    if (b < 0)
        b = 0;
    if (b > 255)
        b = 255;
    return (r << 16) | (g << 8) | b;
}
