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
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("mlx_init failed\n");
        return (0);
    }
    game->window = mlx_new_window(game->mlx, game->map_w * TILE_SIZE, game->map_h * TILE_SIZE, "Cub3D Map");
    if (!game->window)
    {
        printf("mlx_new_window failed\n");
        return (0);
    }
    game->map = duplicate_map(map);
    game->img = mlx_new_image(game->mlx, game->map_w * TILE_SIZE, game->map_h * TILE_SIZE);
    game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    return (1);
}