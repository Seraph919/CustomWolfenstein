#include "../../../headers/cub3d.h"

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