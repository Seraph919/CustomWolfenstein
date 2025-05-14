/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/13 18:16:17 by asoudani         ###   ########.fr       */
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
    int     i;

    dir = data->direction_paths;
    i = 0;
    data->north = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->north_p), &width, &height);
    if (!data->north)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->west = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->west_p), &width, &height);
    if (!data->west)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->east = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->east_p), &width, &height);
    if (!data->east)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->south = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->south_p), &width, &height);
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
        }// free stuff here..
    }
    free2d(colors->splitted_c, 5);
    free2d(colors->splitted_f, 5);
    return (SUCCESS);
}

// bool file_copying(t_game *game, int len)
// {
//     int fd;
//     int y;
//     char *line;
    
//     y = 0;
//     fd = open("src/map/file.cub", O_RDONLY);
//     if (fd < 0 || len == 0)
//         return (printfd(2, "Error in file opening\n"),ERROR);
//     game->cub_file = alloc((sizeof(char *) * len) + 1, ALLOC);
//     if (!game->cub_file)
//         return (ERROR);
//     while ((line = get_next_line(fd)))
//     {
//         game->cub_file[y++] = line;
//     }
//     game->cub_file[y - 1] = NULL;
//     game->map_y = y;
//     close(fd);
//     return (SUCCESS);
// }

// bool get_allocation_size(int *y)
// {
//     char *line;
//     int fd;
    
//     *y = 0;
//     fd = open("src/map/file.cub", O_RDONLY);
//     if (fd < 0)
//         return (printfd(2, "Error in file opening\n"),ERROR);
//     while ((line = get_next_line(fd)))
//     {
//         *y += 1;
//         free(line);
//     }
//     close(fd);
//     if (*y == 0)
//         return (ERROR);
//     return (SUCCESS);
// }
// bool file_read(t_game *game)
// {
//     int y;

//     y = 0;
//     if (get_allocation_size(&y) || file_copying(game, y))
//         return (ERROR);
//     return (SUCCESS);
// }

// bool outer_resources(t_game *game)
// {
//     int i;
//     int k;
//     t_direction_p *direction;
    
//     game->direction_paths = alloc(sizeof (t_direction_p), ALLOC);
//     if (!game->direction_paths)
//         return (ERROR);
//     direction = game->direction_paths;
//     game->map = alloc (sizeof(char *) * (game->map_y - 6) + 1, ALLOC);
//     if (!game->map)
//         return (ERROR); // free on error
//     i = -1;
//     k = 0;
//     while (game->cub_file[++i])
//     {
//         if (char_in(game->cub_file[i]) && char_in(game->cub_file[i]) != SYERROR)
//         {
//             if (game->cub_file[i] && TILE_SIZE_first_in('N', game->cub_file[i])) // NO
//                 direction->north_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('S', game->cub_file[i])) // SO
//                 direction->south_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('W', game->cub_file[i])) // WE
//                 direction->west_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('E', game->cub_file[i])) // EA
//                 direction->east_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('F', game->cub_file[i])) // F
//                 game->f_color = ft_strdup(game->cub_file[i]);
//             else if (game->cub_file[i] && TILE_SIZE_first_in('C', game->cub_file[i])) // C 
//                 game->c_color = ft_strdup(game->cub_file[i]);
//             else
//                 game->map[k++] = ft_strdup(game->cub_file[i]);
//         }
//     }
//     return (SUCCESS);
// }

// bool file_related(t_game *game)
// {
//     if (file_read(game))
//     return (printfd(2, "Found an Error in .cub Processing\n"),ERROR);
//     if (outer_resources(game)) // need to free in case of errors
//     return (printfd(2, "Found an Error in The .cub File\n"), ERROR); // also here
//     printf("north :%s", game->direction_paths->north_p);
//     printf("west :%s", game->direction_paths->west_p);
//     printf("east :%s", game->direction_paths->east_p);
//     printf("south :%s\n", game->direction_paths->south_p);
//     printf("F :%s", game->f_color);
//     printf("c :%s\n", game->c_color);

//     for (int i = 0; game->map[i]; i++)
//         printf("%s", game->map[i]);
//     return (SUCCESS);
// }

// void fireforce(void)
// {
//     alloc(0, FREE);
// }

// int main(int ac, char **av)
// {
//     if (ac != 1)
//         return (1);
//     t_game game;
//     t_game *game;
//     (void)av;
//     game.mlx_ptr = mlx_init();
//     if (file_related(&game))
//         return (ERROR);
//     start_game(&game);
//     finTILE_SIZEh_game(&game);
//     fireforce();
//     return (SUCCESS);
// }

// Get map dimensions
// int get_map_height(char **map)
// {
//     int height = 0;
//     while (map[height])
//         height++;
//     return height;
// }

// int get_map_width(char **map)
// {
//     int width = 0;
//     int max_width = 0;
    
//     for (int i = 0; map[i]; i++)
//     {
//         width = 0;
//         while (map[i][width])
//             width++;
//         if (width > max_width)
//             max_width = width;
//     }
    
//     return max_width;
// }



// int close_window(t_game *game)
// {
//     game->is_game_running = false;
    
//     // Free resources
//     if (game->rays)
//         free(game->rays);
    
//     if (game->img)
//         mlx_destroy_image(game->mlx, game->img);
    
//     if (game->window)
//         mlx_destroy_window(game->mlx, game->window);
    
//     exit(0);
    
//     return 0;
// }



int main(int ac, char **av)
{

    if (ac != 2)
        return (1);
    t_data data;
    data.mlx_ptr = mlx_init();
    if (file_process(&data, av))
        return (ERROR);
    t_game game;

    game.map = NULL;
    start_gaming(game, data.map);
    
    return 0;
}
