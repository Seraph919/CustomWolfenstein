#include "../../../headers/cub3d.h"

void draw_final(t_game *game)
{
    t_rect r = {game->player->x - PLAYER_SIZE / 2,
        game->player->y - PLAYER_SIZE / 2,
        PLAYER_SIZE, PLAYER_SIZE, 0xffffff};
    draw_rect(game, r);
}

void render_minimap(t_game *game)
{
    int y;
    int x;
    int color;
    t_rect r;

    y = 0;
    while (y < game->map_h - 1)
    {
        x = 0;
        while (x < game->map_w - 1)
        {
            color = WALL_COLOR;
            if (game->map[y][x] && game->map[y][x]== '1')
                color = EMPTY_COLOR;
            else if (game->map[y][x] && game->map[y][x]== 'D')
                color = 0xFF0000;
            else if (game->map[y][x] && game->map[y][x]== 'O')
                color = 0x00FF00;
            r = (t_rect){x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color};
            draw_rect(game, r);
            x++;
        }
        y++;
    }
    draw_final(game);
}
