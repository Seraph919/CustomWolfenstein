#include "../../headers/cub3d.h"

int is_valid_move(t_game *game, float new_x, float new_y)
{
    int map_x = (int)(new_x / TILE_SIZE);
    int map_y = (int)(new_y / TILE_SIZE);
    
    static int i = 1;
    
    if (map_x < 0 || map_x >= game->map_w || map_y < 0 || map_y >= game->map_h)
    {
        printf("Invalid move out of bounds!\n");
        return 0;
    }
    if (game->map[map_y][map_x] == '1') {
        printf("Invalid move: hit a wall\n");
        return 0;
    }
    if (game->map[map_y][map_x] == '0') {
        printf("Move-> %d\n", i++);
    }
    return 1;
}

void move_forward(t_game *game)
{
    float move_x = cos(game->player->angle) * PLAYER_SPEED;
    float move_y = sin(game->player->angle) * PLAYER_SPEED;
    float new_x = game->player->x + move_x;
    float new_y = game->player->y + move_y;
    
    if (is_valid_move(game, new_x, new_y))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    } else {
        printf("Invalid move: move forward failed.\n");
    }
}

void move_backward(t_game *game)
{
    float move_x = cos(game->player->angle) * PLAYER_SPEED;
    float move_y = sin(game->player->angle) * PLAYER_SPEED;

    float new_x = game->player->x - move_x;
    float new_y = game->player->y - move_y;

    if (is_valid_move(game, (int)(new_x), (int)(new_y)))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    } else {
        printf("Invalid move: move backward failed.\n");
    }
}

void strafe_left(t_game *game)
{
    float move_x = cos(game->player->angle - PI / 2) * PLAYER_SPEED;
    float move_y = sin(game->player->angle - PI / 2) * PLAYER_SPEED;
    float new_x = game->player->x + move_x;
    float new_y = game->player->y + move_y;
    
    if (is_valid_move(game, new_x, new_y))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    } else {
        printf("Invalid move: strafe left failed.\n");
    }
}

void strafe_right(t_game *game)
{
    float move_x = cos(game->player->angle + PI / 2) * PLAYER_SPEED;
    float move_y = sin(game->player->angle + PI / 2) * PLAYER_SPEED;
    float new_x = game->player->x + move_x;
    float new_y = game->player->y + move_y;
    
    if (is_valid_move(game, new_x, new_y))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    } else {
        printf("Invalid move: strafe right failed.\n");
    }
}

void update_player_position(t_game *game, int new_x, int new_y)
{
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

    if (new_x < 0 || new_x >= game->map_w || new_y < 0 || new_y >= game->map_h)
    {
        printf("Invalid move: out of bounds\n");
        return;
    }
    game->map[(int)game->player->y][(int)game->player->x] = '0';
    game->map[new_y][new_x] = 'N';
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