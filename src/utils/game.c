#include "../../headers/cub3d.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    int pixel;
    pixel = (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int *)(game->addr + pixel) = color;
}

void render_map(t_game *game, char **map)
{
    int y;
    int x;
    int dy;
    int dx;
    int color;

    y = 0;
    while (y < game->map_h)
    {
        x = 0;
        while (x < game->map_w)
        {
            dy = 0;
            if (map[y][x] == '1')
                color = WALL_COLOR;
            else if (map[y][x] == '0')
                color = EMPTY_COLOR;
            else if (map[y][x] == 'N')
            {
                game->player->x = x;
                game->player->y = y;
                color = PLAYER;
            }
            while (dy < TILE_SIZE)
            {
                dx = 0;
                while (dx < TILE_SIZE)
                {
                    my_mlx_pixel_put(game, x * TILE_SIZE + dx, y * TILE_SIZE + dy, color);
                    dx++;
                }
                dy++;
            }
            x++;
        }
        y++;
    }
}
