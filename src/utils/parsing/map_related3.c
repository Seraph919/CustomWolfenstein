/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:52:02 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/16 00:40:33 by asoudani         ###   ########.fr       */
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

bool ray_hit(t_ray *rays)
{
    int i = 0;
    while (i < WINDOW_WIDTH)
    {
        if (rays[i].is_door == true && rays[i].distance <= 10)
            return true;
        i++;
    }
    return false;
    
}

void change_door_state(char **s)
{
    int i;
    char *c;

    i = 0;
    if (s && *s)
    {
        while (s[i])
        {       
            c = s[i];
            while (*c)
            {
                if (*c == 'D')
                    *c = 'O';
                else if (*c == 'O')
                    *c = 'D';
                c++;
            }     
            i++;
        }
    }

}

bool is_door2(t_game *game, float x, float y)
{
    if (x < 0 || x >= (game->map_w - 1) * TILE_SIZE || y < 0 || y >= (game->map_h - 1) * TILE_SIZE)
        return false;

    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    if (game->map[map_y][map_x] == 'D' || game->map[map_y][map_x] == 'O')
        return true;
    else
        return false;
}

bool is_open(int x, int y, t_game *game, bool unlock_door)
{
    // static bool return_type = false;
    int i;
    int ndoors = game->data->ndoors;
    t_doorpos *head;

    x /= TILE_SIZE;
    y /= TILE_SIZE;
    i = 0;
    if (ndoors > 0)
    {
        head = &game->data->doors[i];
        if (unlock_door)
        {
            if (!is_door2(game, game->player->x, game->player->y))
            {
                while (i < ndoors)
                {
                    head = &game->data->doors[i];
                    head->is_open = !head->is_open; 
                    i++;
                }
                i = 0;
                change_door_state(game->map);
            }
            else
                printfd(1, "you're stepping on one of the doors\n");
        }
        return head->is_open;
    }
    return false;
}
