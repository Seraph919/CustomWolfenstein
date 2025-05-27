#include "../../headers/cub3d.h"

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

    int pistol_w = 600;
    int pistol_h = 600;
    int pistol_x = (game->window_width - pistol_w) / 2;
    int pistol_y = game->window_height - pistol_h - 65;
    draw_sprite(game, &game->pistol_texture, pistol_x, pistol_y, pistol_w, pistol_h);
    return 0;
}

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