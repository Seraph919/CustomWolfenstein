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

int texture_data(t_game *game)
{
     if (!game->textures[NORTH].img || !game->textures[SOUTH].img || !game->textures[EAST].img || !game->textures[WEST].img || !game->textures[AIM].img)
        return (printfd(2, "Failed to load direction textures\n"), alloc (0, FREE), ERROR);
    game->textures[NORTH].addr = mlx_get_data_addr(game->textures[NORTH].img, &game->textures[NORTH].bpp, &game->textures[NORTH].size_line, &game->textures[NORTH].endian);
    game->textures[SOUTH].addr = mlx_get_data_addr(game->textures[SOUTH].img, &game->textures[SOUTH].bpp, &game->textures[SOUTH].size_line, &game->textures[SOUTH].endian);
    game->textures[EAST].addr = mlx_get_data_addr(game->textures[EAST].img, &game->textures[EAST].bpp, &game->textures[EAST].size_line, &game->textures[EAST].endian);
    game->textures[WEST].addr = mlx_get_data_addr(game->textures[WEST].img, &game->textures[WEST].bpp, &game->textures[WEST].size_line, &game->textures[WEST].endian);
    game->textures[AIM].addr = mlx_get_data_addr(game->textures[AIM].img, &game->textures[AIM].bpp, &game->textures[AIM].size_line, &game->textures[AIM].endian);
    return (SUCCESS);
}

int init_mlx(t_game *game, char **map)
{
    game->syle_animation_running = false;
    game->current_anim_index = 0; // ! change
    game->current_style_index = 0;
    game->animation_running = false;
    game->keys_held = false;

    game->map = duplicate_map(map);
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
    game->player->dir_x = 1.0;
    game->player->dir_y = 0.0;
    game->player->plane_x = 0.66;
    game->player->plane_y = 0.0;
    for (int y = 0; y < game->map_h; y++)
    {
        for (int x = 0; map[y][x]; x++)
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
    game->last_mouse_x = WINDOW_WIDTH / 2;
    game->last_mouse_y = WINDOW_HEIGHT / 2;

    mlx_mouse_move(game->mlx, game->window, game->last_mouse_x, game->last_mouse_y);
    mlx_mouse_hide(game->mlx, game->window);
    game->textures = alloc(sizeof(t_texture) *  5, ALLOC);
    if (!game->textures)
        return (alloc(0, FREE), exit(1), ERROR);
    game->textures[NORTH].img = mlx_xpm_file_to_image(game->mlx, game->data->direction_paths->north_p, &game->textures[NORTH].width, &game->textures[NORTH].height);
    game->textures[SOUTH].img = mlx_xpm_file_to_image(game->mlx, game->data->direction_paths->south_p, &game->textures[SOUTH].width, &game->textures[SOUTH].height);
    game->textures[EAST].img = mlx_xpm_file_to_image(game->mlx, game->data->direction_paths->east_p, &game->textures[EAST].width, &game->textures[EAST].height);
    game->textures[WEST].img = mlx_xpm_file_to_image(game->mlx, game->data->direction_paths->west_p, &game->textures[WEST].width, &game->textures[WEST].height);
    game->textures[AIM].img = mlx_xpm_file_to_image(game->mlx, "./src/textures/aim_cross.xpm", &game->textures[AIM].width, &game->textures[AIM].height);
    game->imgs = alloc(sizeof(char *) * 4, ALLOC);

    if (texture_data(game) == ERROR)
        return (ERROR);
    int width, height;
    int i = -1;
    game->pistol_texture = alloc(sizeof (t_texture) * 52, ALLOC);
    while (++i < 52)
    {
        game->pistol_texture[i].img = mlx_xpm_file_to_image(game->mlx, ft_strjoin("./src/textures/", ft_strjoin(ft_itoa(i + 1), ".xpm")), &width, &height);
        if (!game->pistol_texture[i].img)
            printf("Failed to load pistol texture\n");
        else {
            game->pistol_texture[i].addr = mlx_get_data_addr(game->pistol_texture[i].img, &game->pistol_texture[i].bpp, &game->pistol_texture[i].size_line, &game->pistol_texture[i].endian);
            game->pistol_texture[i].width = width;
            game->pistol_texture[i].height = height;
        }
    }
    game->is_game_running = true;
    return 1;
}
