/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:29:30 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/27 11:43:51 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	draw_ceiling_and_floor(t_game *game)
{
	t_rect	r;

	r = (t_rect){0, 0, game->window_width, game->window_height / 2,
		game->data->colors->c_color};
	draw_rect(game, r);
	r = (t_rect){0, game->window_height / 2, game->window_width,
		game->window_height / 2, game->data->colors->f_color};
	draw_rect(game, r);
}

void	init_wall_args(t_wall_args *wall_args, t_game *game,
	int i, t_wall_atr wall)
{
	wall_args->game = game;
	wall_args->x = i;
	wall_args->wall_top = wall.wall_top;
	wall_args->wall_height = wall.wall_height;
	wall_args->ray_id = i;
	wall_args->isdoor = game->rays[i].is_door;
}

void	draw_projection_strips(t_game *game)
{
	int			i;
	float		y_distance;
	t_wall_atr	wall;
	t_wall_args	wall_args;

	i = 0;
	while (i < NUM_RAYS)
	{
		y_distance = game->rays[i].distance * cos(game->rays[i].ray_angle
				- game->player->angle);
		wall.wall_height = (TILE_SIZE / y_distance) * ((game->window_width / 2)
				/ tan(game->player->fov / 2));
		game->rays[i].wall_height = wall.wall_height;
		wall.wall_top = (game->window_height / 2) - (wall.wall_height / 2);
		if (wall.wall_top < 0)
			wall.wall_top = 0;
		init_wall_args(&wall_args, game, i, wall);
		draw_textured_wall(&wall_args);
		i++;
	}
}

static void	draw_sprite_inner(t_sprite_args *args)
{
	int	y;
	int	x;
	int	tex_y;
	int	tex_x;
	int	color;

	y = 0;
	while (y < args->dest_h)
	{
		x = 0;
		tex_y = (y * args->sprite->height) / args->dest_h;
		while (x < args->dest_w)
		{
			tex_x = (x * args->sprite->width) / args->dest_w;
			color = get_texture_color(args->sprite, tex_x, tex_y);
			if ((color & 0xFF000000) != 0xFF000000)
				my_mlx_pixel_put(args->game, args->dest_x + x,
					args->dest_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_sprite(t_sprite_args *sprite_args)
{
	draw_sprite_inner(sprite_args);
}
