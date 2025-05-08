/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/07 20:59:18 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

// bool file_copying(t_data *data, int len)
// {
//     int fd;
//     int y;
//     char *line;
    
//     y = 0;
//     fd = open("src/map/file.cub", O_RDONLY);
//     if (fd < 0 || len == 0)
//         return (printfd(2, "Error in file opening\n"),ERROR);
//     data->cub_file = alloc((sizeof(char *) * len) + 1, ALLOC);
//     if (!data->cub_file)
//         return (ERROR);
//     while ((line = get_next_line(fd)))
//     {
//         data->cub_file[y++] = line;
//     }
//     data->cub_file[y - 1] = NULL;
//     data->map_y = y;
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
// bool file_read(t_data *data)
// {
//     int y;

//     y = 0;
//     if (get_allocation_size(&y) || file_copying(data, y))
//         return (ERROR);
//     return (SUCCESS);
// }

// bool outer_resources(t_data *data)
// {
//     int i;
//     int k;
//     t_direction_p *direction;
    
//     data->direction_paths = alloc(sizeof (t_direction_p), ALLOC);
//     if (!data->direction_paths)
//         return (ERROR);
//     direction = data->direction_paths;
//     data->map = alloc (sizeof(char *) * (data->map_y - 6) + 1, ALLOC);
//     if (!data->map)
//         return (ERROR); // free on error
//     i = -1;
//     k = 0;
//     while (data->cub_file[++i])
//     {
//         if (char_in(data->cub_file[i]) && char_in(data->cub_file[i]) != SYERROR)
//         {
//             if (data->cub_file[i] && is_first_in('N', data->cub_file[i])) // NO
//                 direction->north_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
//             else if (data->cub_file[i] && is_first_in('S', data->cub_file[i])) // SO
//                 direction->south_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
//             else if (data->cub_file[i] && is_first_in('W', data->cub_file[i])) // WE
//                 direction->west_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
//             else if (data->cub_file[i] && is_first_in('E', data->cub_file[i])) // EA
//                 direction->east_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
//             else if (data->cub_file[i] && is_first_in('F', data->cub_file[i])) // F
//                 data->f_color = ft_strdup(data->cub_file[i]);
//             else if (data->cub_file[i] && is_first_in('C', data->cub_file[i])) // C 
//                 data->c_color = ft_strdup(data->cub_file[i]);
//             else
//                 data->map[k++] = ft_strdup(data->cub_file[i]);
//         }
//     }
//     return (SUCCESS);
// }

// bool file_related(t_data *data)
// {
//     if (file_read(data))
//     return (printfd(2, "Found an Error in .cub Processing\n"),ERROR);
//     if (outer_resources(data)) // need to free in case of errors
//     return (printfd(2, "Found an Error in The .cub File\n"), ERROR); // also here
//     printf("north :%s", data->direction_paths->north_p);
//     printf("west :%s", data->direction_paths->west_p);
//     printf("east :%s", data->direction_paths->east_p);
//     printf("south :%s\n", data->direction_paths->south_p);
//     printf("F :%s", data->f_color);
//     printf("c :%s\n", data->c_color);

//     for (int i = 0; data->map[i]; i++)
//         printf("%s", data->map[i]);
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
//     t_data data;
//     t_game *game;
//     (void)av;
//     data.mlx_ptr = mlx_init();
//     if (file_related(&data))
//         return (ERROR);
//     start_game(&game);
//     finish_game(&game);
//     fireforce();
//     return (SUCCESS);
// }

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    int pixel;

    pixel = (y * data->size_line + x * (data->bpp / 8));
    *(unsigned int *)(data->addr + pixel) = color;
}

void render_map(t_data *data, int map[MAP_H][MAP_W])
{
    int y;
    int x;
    int dy;
    int dx;

    y = 0;
    while (y < MAP_H)
    {
        x = 0;
        while (x < MAP_W)
        {
            dy = 0;
            int color = (map[y][x] == 1) ? WALL_COLOR : EMPTY_COLOR;
            while (dy < TILE_SIZE)
            {
                dx = 0;
                while (dx < TILE_SIZE)
                {
                    my_mlx_pixel_put(data, x * TILE_SIZE + dx, y * TILE_SIZE + dy, color);
                    dx++;
                }
                dy++;
            }
            x++;
        }
        y++;
    }
}

int init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx) {
        printf("mlx_init failed\n");
        return 1;
    }
    data->window = mlx_new_window(data->mlx, MAP_W * TILE_SIZE, MAP_H * TILE_SIZE, "Cub3D Map");
    if (!data->window) {
        printf("mlx_new_window failed\n");
        return 1;
    }
    data->img = mlx_new_image(data->mlx, MAP_W * TILE_SIZE, MAP_H * TILE_SIZE);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);
    return 0;
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->window);
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
}

int main()
{
    int map[MAP_H][MAP_W] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    t_data data;
    if (init_mlx(&data))
        return 1;
    render_map(&data, map);
    mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
    mlx_hook(data.window, 17, 0, close_window, &data);
    mlx_loop(data.mlx);

    return 0;
}
