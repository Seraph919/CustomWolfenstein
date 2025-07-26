/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:49:56 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/26 20:52:17 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	init_player_vars(t_game *game)
{
	game->player->fov = FOV * DEG_TO_RAD;
	game->player->move_speed = MOVE_SPEED;
	game->player->rotation_speed = ROTATION_SPEED;
}

void	set_player_stuff(int x, int y, t_game *game, float angle)
{
	game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
	game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
	game->map[y][x] = '0';
	game->player->angle = angle;
}

void	get_player_angle(t_game *game, int y)
{
	int	x;

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

void	set_player_direction(t_game *game)
{
	game->player->dir_x = 1.0;
	game->player->dir_y = 0.0;
	game->player->plane_x = 0.66;
	game->player->plane_y = 0.0;
}

int	init_vars(t_game *game)
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
		return (ERROR);
	game->window = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "cub3D");
	if (!game->window)
		return (ERROR);
	game->img = mlx_new_image(game->mlx, game->window_width,
			game->window_height);
	if (!game->img)
		return (ERROR);
	return (SUCCESS);
}
