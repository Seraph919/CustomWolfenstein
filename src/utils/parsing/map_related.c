/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:35:54 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/30 20:31:01 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

int	check_next_index(char **map, int x, int y)
{
	if (!map || !*map || !map[y])
		return (ERROR);
	if (map[y][x] != '0' && map[y][x] != '\0'
		&& is_white_space(map[y][x]) == false)
		return (SUCCESS);
	return (ERROR);
}

bool	not_surr(char **map, int x, int y)
{
	if (check_next_index(map, x + 1, y) == SUCCESS && check_next_index(map, x
			- 1, y) == SUCCESS)
		return (false);
	if (check_next_index(map, x, y + 1) == SUCCESS && check_next_index(map, x, y
			- 1) == SUCCESS)
		return (false);
	return (true);
}

bool	check_srnds(t_data *data, int x, int y, size_t map_max)
{
	if (!data->map || !data->map[y])
		return (false);
	if (y > 0 && data->map[y][x] && data->map[y][x] == '0')
	{
		if (is_void(data->map, x, y, map_max))
			return (false);
	}
	else if (y > 0 && data->map[y][x] && data->map[y][x] == 'D')
	{
		if (not_surr(data->map, x, y))
			return (false);
	}
	else if (!not_in_str(data->map[y][x], "NSEW"))
	{
		data->player_x = x;
		data->player_y = y;
	}
	return (true);
}

bool	checkbefore(char *s, int end)
{
	if (!s || end < 0)
		return (false);
	while (end >= 0)
	{
		if (s[end] == '1')
			return (true);
		if (!is_white_space(s[end]))
			break ;
		end--;
	}
	return (false);
}

bool	conditions(t_norm1 *norm)
{
	if (norm->i == 0 && norm->map[norm->line][norm->i] == ' ')
	{
		norm->temp = skip_spaces(norm->map[norm->line]);
		norm->endl = ft_strlen(norm->temp) - 1;
		if (!norm->temp || *norm->temp != '1')
			return (false);
		if (norm->endl > 0 && norm->temp[norm->endl] != '1')
		{
			if (!checkbefore(norm->temp, norm->endl - 1))
				return (false);
		}
	}
	return (true);
}

bool	is_player_void(char **map, size_t x, size_t y, size_t map_max)
{
	if (y > 0 && map[y - 1] && x < ft_strlen(map[y - 1]))
	{
		if (is_white_space(map[y - 1][x]))
			return (true);
	}
	else if (y == 0)
		return (true); 
	if (y + 1 < map_max && map[y + 1] && x < ft_strlen(map[y + 1]))
	{
		if (is_white_space(map[y + 1][x]))
			return (true);
	}
	else
		return (true);
	if (x > 0)
	{
		if (is_white_space(map[y][x - 1]))
			return (true);
	}
	else
		return (true);
	if (x + 1 < ft_strlen(map[y]))
	{
		if (is_white_space(map[y][x + 1]))
			return (true);
	}
	else
		return (true);
	return (false);
}
