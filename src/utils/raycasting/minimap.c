#include "../../../headers/cub3d.h"

void render_minimap(t_game *game)
{
    int minimap_width = game->map_w * TILE_SIZE;
    int minimap_height = game->map_h * TILE_SIZE;
    
    (void)minimap_width;
    (void)minimap_height;
    for (int y = 0; y < game->map_h; y++)
    {
        for (int x = 0; x < game->map_w; x++)
        {
            int color = game->map[y][x] == '1' ? WALL_COLOR : EMPTY_COLOR;
            draw_rect(game, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
        }
    }
    draw_rect(game, 
              game->player->x - PLAYER_SIZE / 2, 
              game->player->y - PLAYER_SIZE / 2, 
              PLAYER_SIZE, PLAYER_SIZE, 
              PLAYER_COLOR);
    float dx = cos(game->player->angle) * 20;
    float dy = sin(game->player->angle) * 20;
    draw_line(game, 
              game->player->x, 
              game->player->y, 
              game->player->x + dx, 
              game->player->y + dy, 
              0xFF0000);
    for (int i = 0; i < NUM_RAYS; i += 50)
    {
        draw_line(game, 
                  game->player->x, 
                  game->player->y, 
                  game->rays[i].wall_hit_x, 
                  game->rays[i].wall_hit_y, 
                  0xFF0000);
    }
}