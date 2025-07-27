/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcalc_extention.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:47:33 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/27 11:47:45 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

t_intercept_steps	calc_v_inter_and_steps(t_game *game, float angle,
		t_ray_dir dir)
{
	t_intercept_steps	steps;

	steps.x_intercept = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
	if (dir.facing_right)
		steps.x_intercept += TILE_SIZE;
	steps.y_intercept = game->player->y + (steps.x_intercept - game->player->x)
		* tan(angle);
	if (dir.facing_left)
		steps.x_step = TILE_SIZE * -1;
	else
		steps.x_step = TILE_SIZE * 1;
	steps.y_step = TILE_SIZE * tan(angle);
	if (dir.facing_up && steps.y_step > 0)
		steps.y_step *= -1;
	if (dir.facing_down && steps.y_step < 0)
		steps.y_step *= -1;
	return (steps);
}

bool	check_v_wall_and_door(t_game *game, t_trace_params params,
	float check_x, float check_y)
{
	if (is_door(game, check_x, check_y))
	{
		*params.found_door = true;
		return (true);
	}
	if (is_wall(game, check_x, check_y))
		return (true);
	return (false);
}

t_wall_hit	trace_v_ray(t_game *game, t_trace_params params,
	t_intercept_steps steps)
{
	t_wall_hit	hit;
	float		y;
	float		x;
	float		check_x;
	float		check_y;

	hit = (t_wall_hit){0, 0, false};
	x = steps.x_intercept;
	y = steps.y_intercept;
	while (x >= 0 && x < game->map_w * TILE_SIZE && y >= 0
		&& y < game->map_h * TILE_SIZE)
	{
		if (params.dir.facing_left)
			check_x = x - 1;
		else
			check_x = x;
		check_y = y;
		if (check_v_wall_and_door(game, params, check_x, check_y))
			return ((t_wall_hit){x, y, true});
		x += steps.x_step;
		y += steps.y_step;
	}
	return (hit);
}

t_wall_hit	find_vertical_intersection(t_game *game, t_ray_input input)
{
	t_intercept_steps	steps;
	t_trace_params		params;

	steps = calc_v_inter_and_steps(game, input.angle, input.dir);
	params = (t_trace_params){.dir = input.dir, .found_door = input.found_door};
	return (trace_v_ray(game, params, steps));
}
