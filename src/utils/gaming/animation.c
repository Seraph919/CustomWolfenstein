/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:53:22 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/26 14:56:40 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	animation(t_game *game)
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
	if (game->syle_animation_running)
	{
		game->current_style_index++;
		usleep(7000);
	}
}

void	draw_weapon(t_game *game, int index)
{
	int	pistol_w;
	int	pistol_h;
	int	pistol_x;
	int	pistol_y;

	animation(game);
	if (game->current_style_index > 52)
	{
		game->syle_animation_running = false;
		game->current_style_index = 34;
	}
	if (index == 1)
		index = game->current_style_index;
	else
		index = game->current_anim_index;
	pistol_w = 1000;
	pistol_h = 1000;
	pistol_x = (game->window_width - pistol_w) / 2 + 200;
	pistol_y = game->window_height - pistol_h;
	draw_sprite(game, &game->pistol_texture[game->current_anim_index], pistol_x,
		pistol_y, pistol_w, pistol_h);
}

void	draw_opening_scene(t_game *game)
{
	draw_sprite(game, &game->textures[OPEN], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	sleep(10);
}
