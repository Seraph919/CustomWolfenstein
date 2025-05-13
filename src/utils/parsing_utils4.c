/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:50:15 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/13 15:03:25 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
        else if(str_validation(i, i == map_size - 1, data) == false) // bool
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

bool map_checker(char **map)
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
            if(not_in_str(map[i][k], "NWES10 \n"))
                return (ERROR);
            if (not_in_str(map[i][k], "NWES") == false && player_found)
                return (ERROR);
            if (not_in_str(map[i][k], "NWES") == false)
                player_found = true;
        }
    }
    return (false);
}
