/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:52:02 by asoudani          #+#    #+#             */
/*   Updated: 2025/06/23 06:18:18 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

int countChars(int c, t_data *data, bool assign)
{
    if (!data || !data->map)
        return 0;
    char **arr; 
    int i;
    int k;
    int counter; 
    
    i = 0;
    arr = data->map;    
    counter = 0;
    while (arr[i])
    {
        k = 0;
        while (arr[i][k])
        {
            if (arr[i][k] == c)
            {
                if (assign)
                {
                    data->doors[counter].is_open = false;
                    data->doors[counter].x = k;
                    data->doors[counter].y = i;
                }
                counter++;
            }
            k++;
        }
        i++;
    }
    return counter;
}

bool close_enough(char **map, int x, int y)
{
    for (int dy = -1; dy <= 2; dy++) {
        for (int dx = -1; dx <= 2; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            if (map[ny][nx] == 'D' || map[ny][nx] == 'O')
                return true;
        }
    }
    return false;
}

bool is_open(int x, int y, t_game *game, bool unlock_door)
{
    int i;
    int ndoors = game->data->ndoors;
    t_doorpos *head;

    x /= TILE_SIZE;
    y /= TILE_SIZE;
    i = 0;
    while (i < ndoors)
    {
        head = &game->data->doors[i];
        if (unlock_door == true && close_enough(game->map, x, y))
        {
            head->is_open = !head->is_open;
            if (head->is_open == false)
            {
                game->map[head->y][head->x] = 'D';
                return false;
            }
            game->map[head->y][head->x] = 'O';
            return true;
        }
        if (close_enough(game->map, head->x,head->y) && head->is_open == false)
        {   
            return false;
        }
        else if (head->x == x && head->y == y && head->is_open == true)
        {
            printf("closed\n");
            return true;
        }
        i++;
    }
    return false;
}
