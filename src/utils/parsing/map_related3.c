/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:52:02 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/25 09:18:29 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	assigner(t_data *data, int x, int y, int counter)
{
	data->doors[counter].is_open = false;
	data->doors[counter].x = x;
	data->doors[counter].y = y;
}

int	countChars(int c, t_data *data, bool assign)
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

bool	ray_hit(t_ray *rays)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		if (rays[i].is_door == true && rays[i].distance <= 10)
			return (true);
		i++;
	}
	return (false);
}

void	change_door_state(char **s)
{
	int		i;
	char	*c;

	i = 0;
	if (s && *s)
	{
		while (s[i])
		{
			c = s[i];
			while (*c)
			{
				if (*c == 'D')
					*c = 'O';
				else if (*c == 'O')
					*c = 'D';
				c++;
			}
			i++;
		}
	}
}

bool	is_door2(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= (game->map_w - 1) * TILE_SIZE || y < 0
		|| y >= (game->map_h - 1) * TILE_SIZE)
		return (false);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (game->map[map_y][map_x] == 'D' || game->map[map_y][map_x] == 'O')
		return (true);
	else
		return (false);
}

bool	is_open(t_game *game, bool unlock_door)
{
	int			i;
	t_doorpos	*head;

	i = 0;
	if (game->data->ndoors > 0)
	{
		head = &game->data->doors[i];
		if (unlock_door)
		{
			if (!is_door2(game, game->player->x, game->player->y))
			{
				while (i < game->data->ndoors)
				{
					head = &game->data->doors[i];
					head->is_open = !head->is_open;
					i++;
				}
				i = 0;
				change_door_state(game->map);
			}
		}
		return (head->is_open);
	}
	return (false);
}
