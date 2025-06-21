/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:35:54 by asoudani          #+#    #+#             */
/*   Updated: 2025/06/19 18:33:35 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"


int check_next_index(char **map, int x, int y)
{
    if (!map || !*map || !map[y])
        return ERROR;
    if (map[y][x] != '0' && map[y][x] != '\0' && is_white_space(map[y][x]) == false)
        return SUCCESS;
    return ERROR;
}


bool not_surr(char **map, int x, int y)
{
    // check for holes or completly surronded by 0
    if (check_next_index(map, x + 1, y) == SUCCESS && check_next_index(map, x - 1, y) == SUCCESS)
        return false;
    if (check_next_index(map, x, y + 1) == SUCCESS && check_next_index(map, x, y - 1) == SUCCESS)
        return false;
    return true;
}


bool check_srnds(t_data *data, int x, int y, size_t map_max)
{
    if (!data->map || !data->map[y])
        return (false);
    if (y > 0 && data->map[y][x] && data->map[y][x] == '0')
    {
        if (is_void(data->map, x, y, map_max))
            return (false);
    }
    else if (y > 0 && data->map[y][x] && data->map[y][x] == 'D')
    {
        if (not_surr(data->map, x, y))
            return (false);
    }
    else if(!not_in_str(data->map[y][x], "NSEW"))
    {
        data->player_x = x;
        data->player_y = y;
    }
    return (true);
}

bool checkbefore(char *s, int end)
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
    if (map_checker(norm.map, data))
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
