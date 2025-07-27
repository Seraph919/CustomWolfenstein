/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:53:22 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/27 11:54:48 by asoudani         ###   ########.fr       */
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

void	sprite_args_init(t_sprite_args *sprite_args, int pistol_y,
	int pistol_w, int pistol_h)
{
	sprite_args->dest_y = pistol_y;
	sprite_args->dest_w = pistol_w;
	sprite_args->dest_h = pistol_h;
}

void	draw_weapon(t_game *game, int index)
{
	int				pistol_w;
	int				pistol_h;
	int				pistol_x;
	int				pistol_y;
	t_sprite_args	sprite_args;

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
	sprite_args.game = game;
	sprite_args.sprite = &game->pistol_texture[game->current_anim_index];
	sprite_args.dest_x = pistol_x;
	sprite_args_init(&sprite_args, pistol_y, pistol_w, pistol_h);
	draw_sprite(&sprite_args);
}

void	draw_opening_scene(t_game *game)
{
	t_sprite_args	sprite_args;

	sprite_args.game = game;
	sprite_args.sprite = &game->textures[OPEN];
	sprite_args.dest_x = 0;
	sprite_args.dest_y = 0;
	sprite_args.dest_w = WINDOW_WIDTH;
	sprite_args.dest_h = WINDOW_HEIGHT;
	draw_sprite(&sprite_args);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	sleep(10);
}
