/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:52:02 by asoudani          #+#    #+#             */
/*   Updated: 2025/06/21 11:54:26 by asoudani         ###   ########.fr       */
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

bool close_enough(int x, int dx, int y,  int dy)
{
    if ((x == dx || x - 1 == dx || dx - 1 == x || x + 1 == dx || dx + 1 == x) && y == dy)
        return true;
    if ((y == dy || y - 1 == dy || dy - 1 == y || y + 1 == dy || dy + 1 == y) && x == dx)
        return true;
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
        if (unlock_door == true)
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
        if (close_enough(x, head->x, y, head->y) && head->is_open == false)
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
