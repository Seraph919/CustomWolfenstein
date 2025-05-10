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

int main()
{
    t_game game;
    // memset(&game, 0, sizeof(t_game));

    char *map[] = {
        "111111111111111",
        "100000000101001",
        "11100P010000011",
        "101000011110001",
        "101110000010001",
        "100010111010101",
        "101010101010101",
        "101010101110101",
        "101011100000101",
        "101000000000001",
        "111111111111111",
        NULL
    };

    game.player = malloc(sizeof(t_player));
    if (!game.player)
    {
        printf("Memory allocation for player failed\n");
        return (1);
    }

    game.map_h = get_map_height(map);
    game.map_w = get_map_width(map);

    if (!init_mlx(&game, map))
    {
        free(game.player);
        return (1);
    }

    render_map(&game, map);
    mlx_put_image_to_window(game.mlx, game.window, game.img, 0, 0);
    mlx_hook(game.window, 2, 1L << 0, key_press, &game);
    mlx_hook(game.window, 17, 0, close_window, &game);
    mlx_loop(game.mlx);

    free(game.player);
    return 0;
}
