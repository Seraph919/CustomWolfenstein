#include "../../headers/cub3d.h"

// void my_mlx_pixel_put(t_game *game, int x, int y, int color)
// {
//     int pixel;
//     pixel = (y * game->size_line + x * (game->bpp / 8));
//     *(unsigned int *)(game->addr + pixel) = color;
// }

// void render_map(t_game *game, char **map)
// {
//     int y;
//     int x;
//     int dy;
//     int dx;
//     int color;

//     y = 0;
//     while (y < game->map_h)
//     {
//         x = 0;
//         while (x < game->map_w)
//         {
//             dy = 0;
//             if (map[y][x] == '1')
//                 color = WALL_COLOR;
//             else if (map[y][x] == '0')
//                 color = EMPTY_COLOR;
//             else if (map[y][x] == 'N')
//             {
//                 game->player->x = x;
//                 game->player->y = y;
//                 color = PLAYER;
//             }
//             while (dy < TILE_SIZE)
//             {
//                 dx = 0;
//                 while (dx < TILE_SIZE)
//                 {
//                     my_mlx_pixel_put(game, x * TILE_SIZE + dx, y * TILE_SIZE + dy, color);
//                     dx++;
//                 }
//                 dy++;
//             }
//             x++;
//         }
//         y++;
//     }
// }

int game_loop(t_game *game)
{
    if (!game->is_game_running)
        return 1;
    mlx_clear_window(game->mlx, game->window);
    if (game->keys_held & (1 << 0))
        move_forward(game);
    if (game->keys_held & (1 << 1))
        move_backward(game);
    if (game->keys_held & (1 << 2))
        strafe_left(game);
    if (game->keys_held & (1 << 3))
        strafe_right(game);
    if (game->keys_held & (1 << 4))
        game->player->angle -= 0.05;
    if (game->keys_held & (1 << 5))
        game->player->angle += 0.05;
    cast_rays(game);
    generate_3d_projection(game);
    render_minimap(game);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
    return 0;
}

// Render the map
void render_map(t_game *game, char **map)
{
    (void)map;
    game->key_state = 0;
}

int start_gaming(t_game game, char **map)
{
    game.player = malloc(sizeof(t_player));
    if (!game.player)
    {
        printfd(2, "Memory allocation for player failed\n");
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
    mlx_hook(game.window, 2, 1L << 0, key_press, &game);
    mlx_hook(game.window, 3, 1L << 1, key_release, &game);
    mlx_hook(game.window, 6, 1L << 6, mouse_move, &game);
    mlx_hook(game.window, 17, 0, close_window, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    free(game.player);
    return (0);
}