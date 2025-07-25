#include "../../headers/cub3d.h"

void	update_animation(t_game *game)
{
    if (game->animation_running)
    {
        game->current_anim_index++;
        usleep(7000);
    }
    if (game->current_anim_index > 6)
    {
        game->animation_running = false;
        game->current_anim_index = 0;
    }
}

void	update_style_animation(t_game *game)
{
    if (game->syle_animation_running)
    {
        game->current_style_index++;
        usleep(7000);
    }
    if (game->current_style_index > 52)
    {
        game->syle_animation_running = false;
        game->current_style_index = 34;
    }
}

void draw_weapon(t_game *game, int index)
{
    int	pistol_w;
    int	pistol_h;
    int	pistol_x;
    int	pistol_y;

    update_animation(game);
    update_style_animation(game);
    if (index == 1)
        index = game->current_style_index;
    else
        index = game->current_anim_index;
    pistol_w = 1000;
    pistol_h = 1000;
    pistol_x = (game->window_width - pistol_w) / 2 + 200;
    pistol_y = game->window_height - pistol_h;
    draw_sprite(game, &game->pistol_texture[game->current_anim_index], pistol_x, pistol_y, pistol_w, pistol_h);
}

void	close_all_fds(void)
{
    int	fd;

    fd = 3;
    while (fd < 1024)
    {
        close(fd);
        fd++;
    }
}

pid_t play_sound(t_game *game)
{
    // int	fd;
    int	id;

    id = fork();
    if (id == 0)
    {
        close_all_fds();
        if (game->sounds.game_vibes)
            execlp("paplay", "paplay", "./sounds/one_piece_ingame.wav", (char *)NULL);
        else
            execlp("paplay", "paplay", "./sounds/pew.wav", (char *)NULL);
        _exit(1);
    }
    if (game->sounds.game_vibes)
        return (id);
    else
        return (0);
}
void	handle_movement_keys(t_game *game)
{
    if (game->keys_held & (1 << 0))
        move_forward(game);
    if (game->keys_held & (1 << 1))
        move_backward(game);
    if (game->keys_held & (1 << 2))
        strafe_left(game);
    if (game->keys_held & (1 << 3))
        strafe_right(game);
}

void	handle_rotation_keys(t_game *game)
{
    if (game->keys_held & (1 << 4))
        game->player->angle -= 0.05;
    if (game->keys_held & (1 << 5))
        game->player->angle += 0.05;
}

void	handle_sound_effects(t_game *game)
{
    if (game->sounds.fire || game->sounds.game_vibes)
    {
        game->vibesound_id = play_sound(game);
        game->sounds.fire = false;
        game->sounds.game_vibes = false;
    }
}

void	render_game_elements(t_game *game)
{
    int	aim_x;
    int	aim_y;

    cast_rays(game);
    generate_3d_projection(game);
    render_minimap(game);
    draw_weapon(game, game->current_anim_index);
    aim_x = (WINDOW_WIDTH / 2) - 45;
    aim_y = (WINDOW_HEIGHT / 2) - 45;
    draw_sprite(game, &game->textures[AIM], aim_x, aim_y, 45, 45);
}

int game_loop(t_game *game)
{
    if (!game->is_game_running)
        return (1);
    mlx_clear_window(game->mlx, game->window);
    handle_movement_keys(game);
    handle_rotation_keys(game);
    handle_sound_effects(game);
    render_game_elements(game);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
    return (0);
}

void render_map(t_game *game, char **map)
{
    (void)map;
    game->key_state = 0;
}

int mouse_butt(int button, int x, int y, void *param)
{
    t_game	*game;

    (void)x;
    (void)y;
    game = (t_game *)param;
    if (button == LEFT_CLICK)
    {
        game->animation_running = true;
        game->sounds.fire = true;
    }
    if (button == RIGHT_CLICK)
        game->syle_animation_running = true;
    else
        printf("button == %d\n", button);
    return (0);
}

pid_t play_opening_sound(void)
{
    int	id;

    id = fork();
    if (id == 0)
    {
        close_all_fds();
        execlp("paplay", "paplay", "./sounds/op.wav", (char *)NULL);
        _exit(1);
    }
    return (id);
}

void draw_opening_scene(t_game *game)
{
    draw_sprite(game, &game->textures[OPEN], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
    sleep(10);
}

int	initialize_game(t_game *game, char **map)
{
    game->player = malloc(sizeof(t_player));
    if (!game->player)
    {
        exit_error(game->data, "fatal allocation error");
        return (1);
    }
    game->map_h = get_map_height(map);
    game->map_w = get_map_width(map);
    if (!init_mlx(game, map))
    {
        free(game->player);
        return (1);
    }
    return (0);
}

void	setup_hooks(t_game *game)
{
    mlx_hook(game->window, 2, 1L << 0, key_press, game);
    mlx_hook(game->window, 3, 1L << 1, key_release, game);
    mlx_hook(game->window, 6, 1L << 6, mouse_move, game);
    mlx_hook(game->window, 17, 0, close_window, game);
    mlx_mouse_hook(game->window, mouse_butt, game);
    mlx_loop_hook(game->mlx, game_loop, game);
}

int start_gaming(t_game game, char **map)
{
    if (initialize_game(&game, map))
        return (1);
    render_map(&game, map);
    setup_hooks(&game);
    mlx_loop(game.mlx);
    free(game.player);
    return (0);
}
