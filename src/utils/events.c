#include "../../headers/cub3d.h"

int is_valid_move(t_game *game, int new_x, int new_y)
{
    static int i = 1;

    if (new_x < 0 || new_x >= game->map_w || new_y < 0 || new_y >= game->map_h)
    {
        printf("Invalid move out of bounds!\n");
        return 0;
    }
    if (game->map[new_y][new_x] == '1') {
        printf("Invalid move: hit a wall\n");
        return 0;
    }
    if (game->map[new_y][new_x] == '0') {
        printf("Move-> %d\n", i++);
    }
    return 1;
}

void update_player_position(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= game->map_w || new_y < 0 || new_y >= game->map_h)
    {
        printf("Invalid move: out of bounds\n");
        return;
    }
    game->map[game->player->y][game->player->x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player->x = new_x;
    game->player->y = new_y;
    render_map(game, game->map);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}

int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->window);
    mlx_destroy_image(game->mlx, game->img);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
}

int key_press(int keycode, t_game *game)
{
    int x;
    int y;
    x = game->player->x;
    y = game->player->y;

    if (keycode == U_KEY) y--;
    if (keycode == D_KEY) y++;
    if (keycode == L_KEY) x--;
    if (keycode == R_KEY) x++;

    if (is_valid_move(game, x, y))
        update_player_position(game, x, y);
    return (0);
}