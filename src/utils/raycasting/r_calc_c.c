/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_calc_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:36:57 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/25 18:42:54 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

void	cast_rays(t_game *game)
{
	float	ray_angle;
	int		i;

	ray_angle = game->player->angle - (game->player->fov / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(game, ray_angle, i);
		ray_angle += game->player->fov / NUM_RAYS;
		i++;
	}
}

t_ray_dir	init_ray_direction(float ray_angle)
{
	t_ray_dir	dir;

	if (ray_angle > 0 && ray_angle < PI)
		dir.facing_down = true;
	else
		dir.facing_down = false;
	dir.facing_up = !dir.facing_down;
	if (ray_angle < HALF_PI || ray_angle > 1.5 * PI)
		dir.facing_right = true;
	else
		dir.facing_right = false;
	dir.facing_left = !dir.facing_right;
	return (dir);
}

t_intercept_steps	calc_h_inter_and_steps(t_game *game,
		float angle, t_ray_dir dir)
{
	t_intercept_steps	steps;

	steps.y_intercept = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
	if (dir.facing_down)
		steps.y_intercept += TILE_SIZE;
	steps.x_intercept = game->player->x
		+ (steps.y_intercept - game->player->y) / tan(angle);
	if (dir.facing_up)
		steps.y_step = TILE_SIZE * -1;
	else
		steps.y_step = TILE_SIZE * 1;
	steps.x_step = TILE_SIZE / tan(angle);
	if (dir.facing_left && steps.x_step > 0)
		steps.x_step *= -1;
	if (dir.facing_right && steps.x_step < 0)
		steps.x_step *= -1;
	return (steps);
}
