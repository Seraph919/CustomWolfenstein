/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/06/20 17:21:55 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void set_tozero(t_data *data)
{
    data->direction_paths->n_ofe = 0;
    data->direction_paths->n_ofw = 0;
    data->direction_paths->n_ofs = 0;
    data->direction_paths->n_ofn = 0;
    data->direction_paths->n_ofc = 0;
    data->direction_paths->n_off = 0;
    data->south = NULL;
    data->north = NULL;
    data->west = NULL;
    data->east = NULL;
}

bool texture_loading(t_data *data)
{
    t_direction_p *dir;
    int width;
    int height;
    // int     i;
    dir = data->direction_paths;
    // i = 0;
    // exit(0);
    data->north = mlx_xpm_file_to_image(data->mlx_ptr, dir->north_p, &width, &height);
    if (!data->north)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->west = mlx_xpm_file_to_image(data->mlx_ptr, dir->west_p, &width, &height);
    if (!data->west)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->east = mlx_xpm_file_to_image(data->mlx_ptr, dir->east_p, &width, &height);
    if (!data->east)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->south = mlx_xpm_file_to_image(data->mlx_ptr, dir->south_p, &width, &height);
    if (!data->south)
        return (printf("Error\nTexture Error\n"), ERROR);
    return (SUCCESS);
}

bool outer_error_check(t_data *data)
{
    t_direction_p *dir;
    
    dir = data->direction_paths;
    if (dir ->n_ofs > 1 || dir ->n_ofn > 1 || dir ->n_ofw > 1 
        || dir ->n_ofe > 1 || dir ->n_ofc > 1 || dir ->n_off > 1)
        return (ERROR);
    if (color_filling(data) ==  ERROR)
        return (ERROR);
    
    return (SUCCESS);
}

void print_stff(t_data *data)
{
    printf("north :%s", data->direction_paths->north_p);
    printf("west :%s", data->direction_paths->west_p);
    printf("east :%s", data->direction_paths->east_p);
    printf("south :%s\n", data->direction_paths->south_p);
    printf("F :%s", data->colors->f);
    printf("c :%s\n", data->colors->c);

    for (size_t i = 0; i < data->map_y; i++)
        printf("%s", data->map[i]);
    printf("\n\n");
    printf("the player is in(%zu,%zu)\n", data->player_x, data->player_y);
}

bool color_filling(t_data *data)
{
    int i;
    t_colors *colors;

    colors = data->colors;
    colors->c = skip_spaces(colors->c);
    colors->f = skip_spaces(colors->f);
    if (!valid_colorstr(colors->c + 1) || !valid_colorstr(colors->f + 1))
        return (ERROR);
    if (count_char(colors->c,',') != 2 || count_char(colors->f,',') != 2)
        return (ERROR);
    colors->splitted_c = ft_split(skip_spaces(colors->c + 1), ',');
    colors->splitted_f = ft_split(skip_spaces(colors->f + 1), ',');
    if (!colors->splitted_c || !colors->splitted_f)
        return (ERROR);
    colors->f_c = alloc(sizeof(int) * 4, ALLOC);
    colors->c_c = alloc(sizeof(int) * 4, ALLOC);
    if (!colors->f_c || !colors->c_c )
    return (ERROR);
    i = -1;
    while (++i < 3)
    {
        colors->f_c[i] = ft_atoi(colors->splitted_f[i]);
        colors->c_c[i] = ft_atoi(colors->splitted_c[i]);
        if (colors->f_c[i] == -1 || colors->c_c[i] == -1)
        {
            free2d(colors->splitted_c, 5);
            free2d(colors->splitted_f, 5);
            return (ERROR);
        }
    }
    free2d(colors->splitted_c, 5);
    free2d(colors->splitted_f, 5);
    colors->c_color = rgb_to_int(colors->c_c[0], colors->c_c[1], colors->c_c[2]);
    colors->f_color = rgb_to_int(colors->f_c[0], colors->f_c[1], colors->f_c[2]);
    return (SUCCESS);
}

int main(int ac, char **av)
{

    if (ac != 2)
        return (1);
    t_data data;
    data.mlx_ptr = mlx_init();
    if (file_process(&data, av))
        return (ERROR);
    t_game game;
    // printf("the player side is : %c\n", data.player_char);
    game.map = NULL;
    game.data = &data;
    start_gaming(game, data.map);
    
    return 0;
}
// ! free memory after game opening success..
// ! use gc only for errors..
// TODO : check all the image sources and return an error if something fails..

//  TODO : create a t_door stucture where you save the door index and condition (open/closed)  done!
//  TODO : force the player to not move if the next is D and door is closed.. 
//  TODO : save door rays and draw texture.