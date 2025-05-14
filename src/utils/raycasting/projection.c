#include "../../../headers/cub3d.h"

void generate_3d_projection(t_game *game)
{
    draw_rect(game, 0, 0, game->window_width, game->window_height / 2, 0x87CEEB);
    draw_rect(game, 0, game->window_height / 2, game->window_width, game->window_height / 2, 0x8B4513);
    
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float perpendicular_distance = game->rays[i].distance * cos(game->rays[i].ray_angle - game->player->angle);
        float wall_height = (TILE_SIZE / perpendicular_distance) * ((game->window_width / 2) / tan(game->player->fov / 2));
        game->rays[i].wall_height = wall_height;
        int wall_top = (game->window_height / 2) - (wall_height / 2);
        if (wall_top < 0)
            wall_top = 0;
        int wall_bottom = (game->window_height / 2) + (wall_height / 2);
        if (wall_bottom > game->window_height)
            wall_bottom = game->window_height;
        int wall_color;
        if (game->rays[i].hit_vertical)
            wall_color = game->rays[i].wall_face == 2 ? 0x8A2BE2 : 0x4B0082;
        else
            wall_color = game->rays[i].wall_face == 0 ? 0x00BFFF : 0x1E90FF;
        draw_rect(game, i * WALL_STRIP_WIDTH, wall_top, WALL_STRIP_WIDTH, wall_bottom - wall_top, wall_color);
    }
}