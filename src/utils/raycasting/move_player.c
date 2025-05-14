#include "../../../headers/cub3d.h"

void move_player(t_game *game)
{
    float move_step = game->player->move_speed;
    float new_x = game->player->x;
    float new_y = game->player->y;
    
    if (W_KEY & (1 << 0))
    {
        new_x += cos(game->player->angle) * move_step;
        new_y += sin(game->player->angle) * move_step;
    }
    if (S_KEY & (1 << 1))
    {
        new_x -= cos(game->player->angle) * move_step;
        new_y -= sin(game->player->angle) * move_step;
    }
    if (A_KEY & (1 << 2))
    {
        new_x += cos(game->player->angle - HALF_PI) * move_step;
        new_y += sin(game->player->angle - HALF_PI) * move_step;
    }
    if (D_KEY & (1 << 3))
    {
        new_x += cos(game->player->angle + HALF_PI) * move_step;
        new_y += sin(game->player->angle + HALF_PI) * move_step;
    }
    if (LEFT_ARROW & (1 << 4))
        game->player->angle -= game->player->rotation_speed;
    if (RIGHT_ARROW & (1 << 5))
        game->player->angle += game->player->rotation_speed;
    game->player->angle = normalize_angle(game->player->angle);
    if (!is_wall(game, new_x, game->player->y))
        game->player->x = new_x;
    if (!is_wall(game, game->player->x, new_y))
        game->player->y = new_y;
}