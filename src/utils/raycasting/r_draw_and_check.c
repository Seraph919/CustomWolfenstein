/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_and_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:51:56 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/25 18:55:24 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->window_width || y < 0 || y >= game->window_height)
		return ;
	dst = game->addr + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_game *game, t_rect rect)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			my_mlx_pixel_put(game, rect.x + j, rect.y + i, rect.color);
			j++;
		}
		i++;
	}
}

float	normalize_angle(float angle)
{
	angle = fmodf(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

bool	is_door(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= (game->map_w - 1) * TILE_SIZE || y < 0
		|| y >= (game->map_h - 1) * TILE_SIZE)
		return (false);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (game->map[map_y][map_x] == 'D')
		return (true);
	else
		return (false);
}

bool	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= (game->map_w - 1) * TILE_SIZE || y < 0
		|| y >= (game->map_h - 1) * TILE_SIZE)
		return (true);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (game->map[map_y][map_x] == '1')
		return (true);
	else
		return (false);
}
