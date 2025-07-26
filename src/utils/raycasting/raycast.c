/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:21:17 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/25 18:27:31 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	cast_ray_intersections(t_game *game, t_cast_ray_data *data)
{
	t_ray_input	ray_input_h;
	t_ray_input	ray_input_v;

	ray_input_h = (t_ray_input){.angle = data->ray_angle, .dir = data->dir,
		.found_door = &data->found_door_h};
	ray_input_v = (t_ray_input){.angle = data->ray_angle, .dir = data->dir,
		.found_door = &data->found_door_v};
	data->h_hit = find_horizontal_intersection(game, ray_input_h);
	data->v_hit = find_vertical_intersection(game, ray_input_v);
	if (data->h_hit.found)
		data->h_distance = distance_between_points(game->player->x,
				game->player->y, data->h_hit.x, data->h_hit.y);
	if (data->v_hit.found)
		data->v_distance = distance_between_points(game->player->x,
				game->player->y, data->v_hit.x, data->v_hit.y);
}

void	finalize_hit_type(t_cast_ray_data *data)
{
	if (data->v_distance < data->h_distance && data->found_door_v)
		data->final_hit_is_door = true;
	else if (data->h_distance <= data->v_distance && data->found_door_h)
		data->final_hit_is_door = true;
}

void	cast_ray(t_game *game, float ray_angle, int ray_id)
{
	t_cast_ray_data	data;
	t_ray_hit_data	hit_data;

	init_cast_ray_data(game, &data, ray_angle, ray_id);
	cast_ray_intersections(game, &data);
	finalize_hit_type(&data);
	hit_data = (t_ray_hit_data){.ray_angle = data.ray_angle,
		.ray_id = data.ray_id, .dir = data.dir, .h_hit = data.h_hit,
		.v_hit = data.v_hit, .for_door = data.final_hit_is_door};
	store_ray_properties(game, hit_data);
}
