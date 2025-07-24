#include "../../headers/cub3d.h"

void draw_weapon(t_game *game, int index)
{
    if (game->animation_running)
    {
        game->current_anim_index++;
        usleep(7000);
    }
    if (game->current_anim_index > 6)
    {
        game->animation_running = false;
        game->current_anim_index = 0;
    }
    if (game->syle_animation_running)
    {
        game->current_style_index++;
        usleep(7000);
    }
    if (game->current_style_index > 52)
    {
        game->syle_animation_running = false;
        game->current_style_index = 34;
    }
    if (index == 1)
        index = game->current_style_index;
    else
        index = game->current_anim_index;
    int pistol_w = 1000;
    int pistol_h = 1000;
    int pistol_x = (game->window_width - pistol_w) / 2 + 200;
    int pistol_y = game->window_height - pistol_h;
    draw_sprite(game, &game->pistol_texture[game->current_anim_index], pistol_x, pistol_y, pistol_w, pistol_h);
}

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
    if (!game->syle_animation_running)
        draw_weapon(game, game->current_anim_index);
    draw_sprite(game, &game->textures[AIM],(WINDOW_WIDTH/ 2) -45, (WINDOW_HEIGHT / 2) - 45, 45, 45);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
    return 0;
}

void render_map(t_game *game, char **map)
{
    (void)map;
    game->key_state = 0;
}

// int weapon_shoting(t_game *game)
// {
//     int i;
//     size_t k;
    
//     i = -1;
//     while (++i < 34)
//     {
//         k = 0;
//         mlx_clear_window(game->mlx, game->window);
//         draw_weapon(game, i);
//         usleep(30000);
//         mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
//     }
//     return (0);
// }
int mouse_butt(int button, int x, int y, void *param)
{
    t_game *game;
    (void) x;
    (void) y;

    game = (t_game *) param;
    if (button == LEFT_CLICK)
        game->animation_running = true;
    if (button == RIGHT_CLICK)
        game->syle_animation_running = true;
    return (0);
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
    mlx_mouse_hook(game.window, mouse_butt, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    free(game.player);
    return (0);
}
