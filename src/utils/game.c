#include "../../headers/cub3d.h"

void	moves(t_game *game)
{
	if (game->keys_held & (1 << 0))
		move_forward(game);
	if (game->keys_held & (1 << 1))
		move_backward(game);
	if (game->keys_held & (1 << 2))
		strafe_left(game);
	if (game->keys_held & (1 << 3))
		strafe_right(game);
	if (game->keys_held & (1 << 4))
		game->player->angle -= 0.05;
	if (game->keys_held & (1 << 5))
		game->player->angle += 0.05;
}

int	game_loop(t_game *game)
{
	if (!game->is_game_running)
		return (1);
	mlx_clear_window(game->mlx, game->window);
	moves(game);
	// if (game->keys_held & (1 << 6))
	//      // !update this
	if (game->sounds.fire || game->sounds.game_vibes)
	{
		game->vibesound_id = play_sound(game);
		game->sounds.fire = false;
		game->sounds.game_vibes = false;
	}
	cast_rays(game);
	generate_3d_projection(game);
	render_minimap(game);
	draw_weapon(game, game->current_anim_index);
	draw_sprite(game, &game->textures[AIM], (WINDOW_WIDTH / 2) - 45,
		(WINDOW_HEIGHT / 2) - 45, 45, 45);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

void	render_map(t_game *game, char **map)
{
	(void)map;
	game->key_state = 0;
}

int	mouse_butt(int button, int x, int y, void *param)
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

int	start_gaming(t_game game, char **map)
{
	game.player = malloc(sizeof(t_player));
	if (!game.player)
		return (exit_error(game.data, "fatal allocation error"), 1);
	game.map_h = get_map_height(map); // ! do u still work with this stuff??
	game.map_w = get_map_width(map);
	if (!init_mlx(&game))
	{
		free(game.player);
		return (1);
	}
	// game.opsound_id = play_opening_sound();
	render_map(&game, map);
	// draw_opening_scene(&game);
	// game.sounds.game_vibes = true;
	mlx_hook(game.window, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game);
	mlx_hook(game.window, 6, 1L << 6, mouse_move, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_mouse_hook(game.window, mouse_butt, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free(game.player);
	return (0);
}
