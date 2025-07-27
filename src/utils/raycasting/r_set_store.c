/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_set_store.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:44:01 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/27 13:45:42 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	set_ray_hit_result(t_ray *ray, t_ray_hit_data input, float h_distance,
		float v_distance)
{
	if (v_distance < h_distance)
	{
		ray->wall_hit_x = input.v_hit.x;
		ray->wall_hit_y = input.v_hit.y;
		ray->distance = v_distance;
		ray->hit_vertical = true;
		if (input.dir.facing_left)
			ray->wall_face = 3;
		else
			ray->wall_face = 2;
	}
	else
	{
		ray->wall_hit_x = input.h_hit.x;
		ray->wall_hit_y = input.h_hit.y;
		ray->distance = h_distance;
		ray->hit_vertical = false;
		if (input.dir.facing_up)
			ray->wall_face = 0;
		else
			ray->wall_face = 1;
	}
}

void	store_ray_properties(t_game *game, t_ray_hit_data input)
{
	float	h_distance;
	float	v_distance;
	t_ray	*ray;

	if (input.h_hit.found)
		h_distance = distance_between_points(game->player->x, game->player->y,
				input.h_hit.x, input.h_hit.y);
	else
		h_distance = F_FLT_MAX;
	if (input.v_hit.found)
		v_distance = distance_between_points(game->player->x, game->player->y,
				input.v_hit.x, input.v_hit.y);
	else
		v_distance = F_FLT_MAX;
	ray = &game->rays[input.ray_id];
	ray->is_door = input.for_door;
	ray->ray_angle = input.ray_angle;
	set_ray_hit_result(ray, input, h_distance, v_distance);
}

void	init_cast_ray_data(t_game *game, t_cast_ray_data *data, float ray_angle,
		int ray_id)
{
	(void)game;
	data->ray_angle = normalize_angle(ray_angle);
	data->ray_id = ray_id;
	data->dir = init_ray_direction(data->ray_angle);
	data->found_door_h = false;
	data->found_door_v = false;
	data->final_hit_is_door = false;
	data->h_distance = F_FLT_MAX;
	data->v_distance = F_FLT_MAX;
}

int	count_chars(int c, t_data *data, bool assign)
{
	int	i;
	int	k;
	int	counter;

	if (!data || !data->map)
		return (0);
	i = 0;
	counter = 0;
	while (data->map[i])
	{
		k = 0;
		while (data->map[i][k])
		{
			if (data->map[i][k] == c)
			{
				if (assign)
					assigner(data, k, i, counter);
				counter++;
			}
			k++;
		}
		i++;
	}
	return (counter);
}
