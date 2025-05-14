#include "../../headers/cub3d.h"

int get_map_height(char **map)
{
    int h = 0;
    while (map[h])
        h++;
    return h;
}

int get_map_width(char **map)
{
    int w = 0;
    while (map[0][w])
        w++;
    return w;
}

char **duplicate_map(char **map)
{
    int height;
    int i;
    int j;
    char **new_map;
    
    i = 0;
    height = get_map_height(map);
    new_map = malloc(sizeof(char *) * (height + 1));
    if (!new_map)
        return (NULL);

    while (i < height)
    {
        new_map[i] = ft_strdup(map[i]);
        if (!new_map[i])
        {
            j = 0;
            while (j < i)
                free(new_map[j++]);
            free(new_map);
            return NULL;
        }
        i++;
    }
    new_map[height] = NULL;
    return new_map;
}

int init_mlx(t_game *game, char **map)
{
    game->map = map;
    game->window_width = WINDOW_WIDTH;
    game->window_height = WINDOW_HEIGHT;
    game->player->fov = FOV * DEG_TO_RAD;
    game->player->move_speed = MOVE_SPEED;
    game->player->rotation_speed = ROTATION_SPEED;
    game->mlx = mlx_init();
    if (!game->mlx)
        return 0;
    game->window = mlx_new_window(game->mlx, game->window_width, game->window_height, "cub3D");
    if (!game->window)
        return 0;
    game->img = mlx_new_image(game->mlx, game->window_width, game->window_height);
    if (!game->img)
        return 0;
    game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    game->rays = malloc(sizeof(t_ray) * NUM_RAYS);
    if (!game->rays)
        return 0;
    game->map = duplicate_map(map);
    game->player->dir_x = 1.0;
    game->player->dir_y = 0.0;
    game->player->plane_x = 0.66;  // FOV: 66°
    game->player->plane_y = 0.0;
    for (int y = 0; y < game->map_h; y++)
    {
        for (int x = 0; x < game->map_w; x++)
        {
            if (map[y][x] == 'N')
            {
                game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
                game->player->angle = PI / 2;
                game->map[y][x] = '0';
            }
        }
    }
    game->is_game_running = true;
    return 1;
}