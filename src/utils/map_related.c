/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:35:54 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/13 15:03:51 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

bool check_srnds(t_data *data, int x, int y, size_t map_max)
{
    if (!data->map || !data->map[y])
        return (false);
    if (y > 0 && data->map[y][x] && data->map[y][x] == '0')
    {
        if (is_void(data->map, x, y, map_max))
            return (false);
    }
    else if(!not_in_str(data->map[y][x], "NSEW"))
    {
        data->player_x = x;
        data->player_y = y;
    }
    return (true);
}

bool checkbefore(char *s, int end) // check the trailing spc
{
    if (!s)
        return (false);
    while (end > 0)
    {
        if (s[end] == '1')
            return (true);
        if (!is_white_space(s[end]))
            break;
        end--;
    }
    return (false);
}
// this will check if i have a char that is not in the list

bool conditions(t_norm1 *norm)
{
    if (norm->i == 0 && norm->map[norm->line][norm->i] == ' ')
    {
        norm->temp = skip_spaces(norm->map[norm->line]);
        norm->endl = ft_strlen(norm->temp) - 1;
        if (!norm->temp || *norm->temp != '1' || norm->temp[norm->endl - 1] != '1')
        {
            if (!checkbefore(norm->temp, norm->endl - 1))
                return (false);
        }
    }
    return (true);
}

void t_norm1_init(t_norm1 *norm, int line, int end)
{
    norm->end = end;
    norm->endl = 0;
    norm->i = 0;
    norm->line = line;
    norm->temp = NULL;
}

bool str_validation(int line, bool end, t_data *data)
{
    if (!data->map || !data->map[line])
        return (false);
    t_norm1 norm;

    t_norm1_init(&norm, line, end);
    norm.map = data->map;
    norm.map_y = data->map_y;
    if (map_checker(norm.map))
        return (false);
    while (data->map[line][norm.i])
    {
        if ((norm.line == 0 || norm.end) && not_in_str(data->map[line][norm.i], "1 \n"))
            return (false);
        if (conditions(&norm) == false)
            return false;
        else if (check_srnds(data, norm.i, line, norm.map_y) == false)
            return (false);
        if (norm.i == ft_strlen(data->map[line]) - 2 && data->map[line][norm.i] != '1')
        {
            if (!checkbefore(norm.temp, norm.endl - 1))
                return (false);
        }
        norm.i++;
    }
    return (true);
}
