/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:27:13 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/31 17:29:27 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

bool	is_player_safe_from_doors(t_game *game)
{
	int		i;
	float	door_x;
	float	door_y;
	float	distance;
	float	min_safe_distance;

	min_safe_distance = 5.0;
	i = 0;
	while (i < game->data->ndoors)
	{
		door_x = game->data->doors[i].x * TILE_SIZE + TILE_SIZE / 2;
		door_y = game->data->doors[i].y * TILE_SIZE + TILE_SIZE / 2;
		distance = calculate_distance(game->player->x, game->player->y,
				door_x, door_y);
		if (distance < min_safe_distance && game->data->doors[i].is_open)
			return (false);
		i++;
	}
	return (true);
}

bool	can_toggle_doors(t_game *game)
{
	if (!is_door2(game, game->player->x, game->player->y))
	{
		if (!game->data->doors[0].is_open || is_player_safe_from_doors(game))
			return (true);
	}
	return (false);
}
