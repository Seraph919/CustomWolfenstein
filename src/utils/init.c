#include "../../headers/cub3d.h"

int get_map_height(char **map)
{
    int height;
    height = 0;
    if (!map || !*map)
        return 0;
    while (map[height])
        height++;
    return height;
}

int get_map_width(char **map)
{
    int width;
    width = 0;
    if (!map || !*map)
        return 0;
    while (map[0][width])
        width++;
    return width;
}

void free_partial_map(char **new_map, int count)
{
    int j;
    j = 0;
    while (j < count)
    {
        free(new_map[j]);
        j++;
    }
    free(new_map);
}

char **duplicate_map(char **map)
{
    int height;
    int i;
    char **new_map;

    i = 0;
    height = get_map_height(map);
    new_map = malloc(sizeof(char *) * (height + 1));
    if (!new_map)
        return NULL;
    while (i < height)
    {
        new_map[i] = ft_strdup(map[i]);
        if (!new_map[i])
        {
            free_partial_map(new_map, i);
            return NULL;
        }
        i++;
    }
    new_map[height] = NULL;
    return new_map;
}

int texture_data(t_game *game)
{
    int i;
    i = 0;
    while (i < 7)
    {
        if (!game->textures[i].img)
            return exit_error(game->data, "Failed to load texture"), 1;
        game->textures[i].addr = mlx_get_data_addr(
            game->textures[i].img,
            &game->textures[i].bpp,
            &game->textures[i].size_line,
            &game->textures[i].endian);
        i++;
    }
    return SUCCESS;
}


void init_sound_vars(t_game *game)
{
    game->sounds.opening_song = true;
    game->sounds.game_vibes = false;
    game->sounds.fire = false;
}

void init_player_vars(t_game *game)
{
    game->player->fov = FOV * DEG_TO_RAD;
    game->player->move_speed = MOVE_SPEED;
    game->player->rotation_speed = ROTATION_SPEED;
}

int init_vars(t_game *game)
{
    game->vibesound_id = 0;
    game->opsound_id = 0;
    game->current_anim_index = 0;
    game->first_time = true;
    game->syle_animation_running = false;
    game->current_style_index = 0;
    game->animation_running = false;
    game->keys_held = false;
    init_sound_vars(game);
    game->map = duplicate_map(game->data->map);
    game->window_width = WINDOW_WIDTH;
    game->window_height = WINDOW_HEIGHT;
    init_player_vars(game);
    game->mlx = mlx_init();
    if (!game->mlx)
        return ERROR;
    game->window = mlx_new_window(
        game->mlx, game->window_width, game->window_height, "cub3D");
    if (!game->window)
        return ERROR;
    game->img = mlx_new_image(
        game->mlx, game->window_width, game->window_height);
    if (!game->img)
        return ERROR;
    return SUCCESS;
}

void set_player_stuff(int x, int y, t_game *game, float angle)
{
    game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
    game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
    game->map[y][x] = '0';
    game->player->angle = angle;
}

void get_player_angle(t_game *game, int y)
{
    int x;
    x = 0;
    while (game->map[y][x])
    {
        if (game->map[y][x] == 'N')
            set_player_stuff(x, y, game, 3 * PI / 2);
        else if (game->map[y][x] == 'S')
            set_player_stuff(x, y, game, PI / 2);
        else if (game->map[y][x] == 'E')
            set_player_stuff(x, y, game, 0);
        else if (game->map[y][x] == 'W')
            set_player_stuff(x, y, game, PI);
        x++;
    }
}


void set_player_direction(t_game *game)
{
    game->player->dir_x = 1.0;
    game->player->dir_y = 0.0;
    game->player->plane_x = 0.66;
    game->player->plane_y = 0.0;
}

void set_mouse_and_textures(t_game *game)
{
    game->last_mouse_x = WINDOW_WIDTH / 2;
    game->last_mouse_y = WINDOW_HEIGHT / 2;
    mlx_mouse_move(game->mlx, game->window,
        game->last_mouse_x, game->last_mouse_y);
    mlx_mouse_hide(game->mlx, game->window);
    game->textures = alloc(sizeof(t_texture) * 7, ALLOC);
}

int load_direction_textures(t_game *game)
{
    game->textures[NORTH].img = mlx_xpm_file_to_image(
        game->mlx, game->data->direction_paths->north_p,
        &game->textures[NORTH].width, &game->textures[NORTH].height);
    game->textures[SOUTH].img = mlx_xpm_file_to_image(
        game->mlx, game->data->direction_paths->south_p,
        &game->textures[SOUTH].width, &game->textures[SOUTH].height);
    game->textures[EAST].img = mlx_xpm_file_to_image(
        game->mlx, game->data->direction_paths->east_p,
        &game->textures[EAST].width, &game->textures[EAST].height);
    game->textures[WEST].img = mlx_xpm_file_to_image(
        game->mlx, game->data->direction_paths->west_p,
        &game->textures[WEST].width, &game->textures[WEST].height);
    game->textures[AIM].img = mlx_xpm_file_to_image(
        game->mlx, "./src/textures/aim_cross.xpm",
        &game->textures[AIM].width, &game->textures[AIM].height);
    game->textures[OPEN].img = mlx_xpm_file_to_image(
        game->mlx, "./src/textures/opening_scene.xpm",
        &game->textures[OPEN].width, &game->textures[OPEN].height);
    game->textures[DOOR].img = mlx_xpm_file_to_image(
        game->mlx, "./src/textures/door.xpm",
        &game->textures[DOOR].width, &game->textures[DOOR].height);
    return 0;
}

void image_adrr(t_game *game, int i, int width, int height)
{
    game->pistol_texture[i].addr = mlx_get_data_addr(
        game->pistol_texture[i].img, &game->pistol_texture[i].bpp,
        &game->pistol_texture[i].size_line, &game->pistol_texture[i].endian);
    game->pistol_texture[i].width = width;
    game->pistol_texture[i].height = height;
}

int load_pistol_textures(t_game *game)
{
    int i;
    int width;
    int height;
    char *num_str;
    char *file_name;
    char *path;

    i = -1;
    game->pistol_texture = alloc(sizeof(t_texture) * 7, ALLOC);
    while (++i < 7)
    {
        num_str = ft_itoa(i + 1);
        file_name = ft_strjoin(num_str, ".xpm");
        path = ft_strjoin("./src/textures/", file_name);
        game->pistol_texture[i].img = mlx_xpm_file_to_image(
            game->mlx, path, &width, &height);
        free(num_str);
        free(file_name);
        free(path);
        if (!game->pistol_texture[i].img)
            return exit_error(game->data, "Failed to load pistol texture"), 1;
        image_adrr(game, i, width, height);
    }
    return 0;
}

int init_mlx(t_game *game)
{
    int y;

    if (init_vars(game) == ERROR)
        return 0;
    game->addr = mlx_get_data_addr(
        game->img, &game->bpp, &game->size_line, &game->endian);
    game->rays = alloc(sizeof(t_ray) * NUM_RAYS, ALLOC);
    if (!game->rays)
        return exit_error(game->data, "fatal allocation error"), 0;
    set_player_direction(game);
    y = -1;
    while (++y < game->map_h)
        get_player_angle(game, y);
    set_mouse_and_textures(game);
    if (!game->textures)
        return exit_error(game->data, "fatal allocation error"), 1;
    load_direction_textures(game);
    game->imgs = alloc(sizeof(char *) * 4, ALLOC);
    if (texture_data(game) == ERROR)
        return ERROR;
    if (load_pistol_textures(game) != 0)
        return 1;
    game->is_game_running = true;
    return 1;
}
