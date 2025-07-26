/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:32:44 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/26 15:36:51 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	init_corners(float corners[4][2], float new_x, float new_y,
		float buffer)
{
	corners[0][0] = new_x - buffer;
	corners[0][1] = new_y - buffer;
	corners[1][0] = new_x + buffer;
	corners[1][1] = new_y - buffer;
	corners[2][0] = new_x - buffer;
	corners[2][1] = new_y + buffer;
	corners[3][0] = new_x + buffer;
	corners[3][1] = new_y + buffer;
}

int	is_valid_move(t_game *game, float new_x, float new_y)
{
	int		i;
	float	buffer;
	float	corners[4][2];
	int		cx;
	int		cy;

	buffer = 1.0f;
	i = 0;
	init_corners(corners, new_x, new_y, buffer);
	while (i < 4)
	{
		cx = (int)(corners[i][0] / TILE_SIZE);
		cy = (int)(corners[i][1] / TILE_SIZE);
		if (cx < 0 || cx >= game->map_w || cy < 0 || cy >= game->map_h)
			return (printf("Invalid move: out of bounds!\n"), 0);
		if (game->map[cy][cx] == '1')
			return (printf("Invalid move: too close to wall!\n"), 0);
		if ((game->map[cy][cx] == 'D' && is_open(game, false) == false))
			return (printf("Unlock the door first!\n"), 0);
		i++;
	}
	return (1);
}

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		center_y;
	int		mouse_delta_x;
	float	sensitivity;

	center_x = game->window_width / 2;
	center_y = game->window_height / 2;
	mouse_delta_x = x - center_x;
	sensitivity = 0.002f;
	game->player->angle += mouse_delta_x * sensitivity;
	mlx_mouse_move(game->mlx, game->window, center_x, center_y);
	game->last_mouse_x = center_x;
	game->last_mouse_y = center_y;
	(void)y;
	return (0);
}

void	update_player_position(t_game *game, int new_x, int new_y)
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
	if (new_x < 0 || new_x >= game->map_w || new_y < 0 || new_y >= game->map_h)
	{
		printf("Invalid move: out of bounds\n");
		return ;
	}
	if (game->map[(int)game->player->y][(int)game->player->x] != 'D'
		&& game->map[(int)game->player->y][(int)game->player->x] != 'O')
		game->map[(int)game->player->y][(int)game->player->x] = '0';
	game->map[new_y][new_x] = game->data->player_char;
	game->player->x = new_x;
	game->player->y = new_y;
	render_map(game, game->map);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}

int	close_window(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= DOOR)
		mlx_destroy_image(game->mlx, game->textures[i].img);
	mlx_destroy_image(game->data->mlx_ptr, game->data->north);
	mlx_destroy_image(game->data->mlx_ptr, game->data->west);
	mlx_destroy_image(game->data->mlx_ptr, game->data->east);
	mlx_destroy_image(game->data->mlx_ptr, game->data->south);
	i = -1;
	while (++i < 7)
		mlx_destroy_image(game->mlx, game->pistol_texture[i].img);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_display(game->mlx);
	free(game->map);
	free(game->player);
	free(game->mlx);
	mlx_destroy_display(game->data->mlx_ptr);
	free(game->data->mlx_ptr);
	alloc(0, FREE);
	system("pkill -9 paplay");
	exit(0);
}
