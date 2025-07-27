/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:34:03 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/27 11:48:45 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (!texture || !texture->addr)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	pixel = texture->addr + (tex_y * texture->size_line + tex_x * (texture->bpp
				/ 8));
	return (*(unsigned int *)pixel);
}

int	get_tex_x(t_ray *ray, t_texture *texture)
{
	float	wall_x;
	int		tex_x;

	if (ray->hit_vertical)
		wall_x = ray->wall_hit_y;
	else
		wall_x = ray->wall_hit_x;
	wall_x /= TILE_SIZE;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)texture->width);
	if ((!ray->hit_vertical && ray->ray_angle > PI) || (ray->hit_vertical
			&& (ray->ray_angle < PI / 2 || ray->ray_angle > 3 * PI / 2)))
	{
		tex_x = texture->width - tex_x - 1;
	}
	return (tex_x);
}

void	draw_textured_strip(t_strip_args *args)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;

	y = args->wall_top;
	while (y < args->wall_top + args->wall_height)
	{
		d = y * 256 - args->game->window_height * 128 + args->wall_height * 128;
		tex_y = ((d * args->texture->height) / args->wall_height) / 256;
		color = get_texture_color(args->texture, args->tex_x, tex_y);
		my_mlx_pixel_put(args->game, args->x, y, color);
		y++;
	}
}

void	get_wall_texture(t_game *game, t_ray *ray, t_texture **texture,
	int *face)
{
	*face = ray->wall_face;
	*texture = &game->textures[DOOR];
	if (ray->is_door == false)
		*texture = &game->textures[*face];
}

void	draw_textured_wall(t_wall_args *wall_args)
{
	t_texture		*texture;
	t_ray			*ray;
	int				face;
	int				tex_x;
	t_strip_args	args;

	(void)wall_args->isdoor;
	ray = &wall_args->game->rays[wall_args->ray_id];
	get_wall_texture(wall_args->game, ray, &texture, &face);
	if (face < 0 || face > 3 || !wall_args->game->textures[face].addr)
		return ;
	tex_x = get_tex_x(ray, texture);
	args.game = wall_args->game;
	args.x = wall_args->x;
	args.wall_top = wall_args->wall_top;
	args.wall_height = wall_args->wall_height;
	args.texture = texture;
	args.tex_x = tex_x;
	draw_textured_strip(&args);
}
