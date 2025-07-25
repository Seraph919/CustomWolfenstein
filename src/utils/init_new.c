/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:00:26 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/25 16:02:24 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/cub3d.h"

int get_map_height(char **map)
{
    int	h;

    if (!map || !*map)
        return (0);
    h = 0;
    while (map[h])
        h++;
    return (h);
}

int get_map_width(char **map)
{
    int	w;

    if (!map || !*map)
        return (0);
    w = 0;
    while (map[0][w])
        w++;
    return (w);
}

void	free_partial_map(char **new_map, int count)
{
    int	j;

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
    int		height;
    int		i;
    char	**new_map;

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
            free_partial_map(new_map, i);
            return (NULL);
        }
        i++;
    }
    new_map[height] = NULL;
    return (new_map);
}

int texture_data(t_game *game)
{
    int	i;

    i = 0;
    while (i < 7)
    {
        if (!game->textures[i].img)
        {
            exit_error(game->data, "Failed to load texture");
            return (1);
        }
        game->textures[i].addr = mlx_get_data_addr(game->textures[i].img, 
            &game->textures[i].bpp, &game->textures[i].size_line,
            &game->textures[i].endian);
        i++;
    }
    return (SUCCESS);
}

void	init_game_variables(t_game *game)
{
    game->vibesound_id = 0;
    game->opsound_id = 0;
    game->first_time = true;
    game->syle_animation_running = false;
    game->current_anim_index = 0;
    game->current_style_index = 0;
    game->animation_running = false;
    game->keys_held = false;
    game->sounds.opening_song = true;
    game->sounds.game_vibes = false;
    game->sounds.fire = false;
}

void	init_player_settings(t_game *game)
{
    game->window_width = WINDOW_WIDTH;
    game->window_height = WINDOW_HEIGHT;
    game->player->fov = FOV * DEG_TO_RAD;
    game->player->move_speed = MOVE_SPEED;
    game->player->rotation_speed = ROTATION_SPEED;
    game->player->dir_x = 1.0;
    game->player->dir_y = 0.0;
    game->player->plane_x = 0.66;
    game->player->plane_y = 0.0;
}

int	init_mlx_components(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    game->window = mlx_new_window(game->mlx, game->window_width, 
        game->window_height, "cub3D");
    if (!game->window)
        return (0);
    game->img = mlx_new_image(game->mlx, game->window_width, 
        game->window_height);
    if (!game->img)
        return (0);
    game->addr = mlx_get_data_addr(game->img, &game->bpp, 
        &game->size_line, &game->endian);
    return (1);
}

int	allocate_rays(t_game *game)
{
    game->rays = alloc(sizeof(t_ray) * NUM_RAYS, ALLOC);
    if (!game->rays)
    {
        exit_error(game->data, "fatal allocation error");
        return (0);
    }
    return (1);
}

void	find_player_position(t_game *game, char **map)
{
    int	y;
    int	x;

    y = 0;
    while (y < game->map_h)
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'N')
            {
                game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
                game->map[y][x] = '0';
                game->player->angle = 3 * PI / 2;
            }
            else if (map[y][x] == 'S')
            {
                game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
                game->player->angle = PI / 2;
                game->map[y][x] = '0';
            }
            else if (map[y][x] == 'E')
            {
                game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
                game->player->angle = 0;
                game->map[y][x] = '0';
            }
            else if (map[y][x] == 'W')
            {
                game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
                game->player->angle = PI;
                game->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
}

void	setup_mouse(t_game *game)
{
    game->last_mouse_x = WINDOW_WIDTH / 2;
    game->last_mouse_y = WINDOW_HEIGHT / 2;
    mlx_mouse_move(game->mlx, game->window, game->last_mouse_x, game->last_mouse_y);
    mlx_mouse_hide(game->mlx, game->window);
}

int	load_main_textures(t_game *game)
{
    game->textures = alloc(sizeof(t_texture) * 7, ALLOC);
    if (!game->textures)
    {
        exit_error(game->data, "fatal allocation error");
        return (0);
    }
    game->textures[NORTH].img = mlx_xpm_file_to_image(game->mlx, 
        game->data->direction_paths->north_p, &game->textures[NORTH].width, 
        &game->textures[NORTH].height);
    game->textures[SOUTH].img = mlx_xpm_file_to_image(game->mlx, 
        game->data->direction_paths->south_p, &game->textures[SOUTH].width, 
        &game->textures[SOUTH].height);
    game->textures[EAST].img = mlx_xpm_file_to_image(game->mlx, 
        game->data->direction_paths->east_p, &game->textures[EAST].width, 
        &game->textures[EAST].height);
    game->textures[WEST].img = mlx_xpm_file_to_image(game->mlx, 
        game->data->direction_paths->west_p, &game->textures[WEST].width, 
        &game->textures[WEST].height);
    return (1);
}

int	load_ui_textures(t_game *game)
{
    game->textures[AIM].img = mlx_xpm_file_to_image(game->mlx, 
        "./src/textures/aim_cross.xpm", &game->textures[AIM].width, 
        &game->textures[AIM].height);
    game->textures[OPEN].img = mlx_xpm_file_to_image(game->mlx, 
        "./src/textures/opening_scene.xpm", &game->textures[OPEN].width, 
        &game->textures[OPEN].height);
    game->textures[DOOR].img = mlx_xpm_file_to_image(game->mlx, 
        "./src/textures/door.xpm", &game->textures[DOOR].width, 
        &game->textures[DOOR].height);
    game->imgs = alloc(sizeof(char *) * 4, ALLOC);
    return (1);
}

char	*create_pistol_path(int i)
{
    char	*num_str;
    char	*file_name;
    char	*path;

    num_str = ft_itoa(i + 1);
    file_name = ft_strjoin(num_str, ".xpm");
    path = ft_strjoin("./src/textures/", file_name);
    free(num_str);
    free(file_name);
    return (path);
}

int	load_pistol_textures(t_game *game)
{
    int		width;
    int		height;
    int		i;
    char	*path;

    game->pistol_texture = alloc(sizeof(t_texture) * 7, ALLOC);
    i = 0;
    while (i < 7)
    {
        path = create_pistol_path(i);
        game->pistol_texture[i].img = mlx_xpm_file_to_image(game->mlx, 
            path, &width, &height);
        free(path);
        if (!game->pistol_texture[i].img)
        {
            exit_error(game->data, "Failed to load pistol texture");
            return (0);
        }
        game->pistol_texture[i].addr = mlx_get_data_addr(
            game->pistol_texture[i].img, &game->pistol_texture[i].bpp, 
            &game->pistol_texture[i].size_line, &game->pistol_texture[i].endian);
        game->pistol_texture[i].width = width;
        game->pistol_texture[i].height = height;
        i++;
    }
    return (1);
}

int init_mlx(t_game *game, char **map)
{
    init_game_variables(game);
    game->map = duplicate_map(map);
    init_player_settings(game);
    if (!init_mlx_components(game))
        return (0);
    if (!allocate_rays(game))
        return (0);
    find_player_position(game, map);
    setup_mouse(game);
    if (!load_main_textures(game))
        return (0);
    if (!load_ui_textures(game))
        return (0);
    if (texture_data(game) == ERROR)
        return (ERROR);
    if (!load_pistol_textures(game))
        return (0);
    game->is_game_running = true;
    return (1);
}
