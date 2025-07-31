/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:43:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/31 16:51:35 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

bool	above_checker(char **map, int y)
{
	int	x;

	x = -1;
	if (!map || !map[y])
		return (ERROR);
	while (map[y][++x])
	{
		if (is_white_space(map[y][x]) && map[y - 1][x] && map[y - 1][x] == '0')
			return (ERROR);
	}
	if (map[y][x] == '\0' && map[y - 1][x] && map[y - 1][x] == '0')
		return (ERROR);
	return (SUCCESS);
}

bool	is_void(char **map, size_t x, size_t y, size_t map_max)
{
	if (y > 0 && map[y - 1] && x < ft_strlen(map[y - 1])
		&& is_white_space(map[y - 1][x]))
		return (true);
	if (y > 0 && map[y - 1] && x >= ft_strlen(map[y - 1]))
		return (true);
	if (y + 1 < map_max - 1 && map[y + 1] && x < ft_strlen(map[y + 1])
		&& is_white_space(map[y + 1][x]))
		return (true);
	if (y + 1 < map_max - 1 && map[y + 1] && x >= ft_strlen(map[y + 1]))
		return (true);
	if (x > 0 && is_white_space(map[y][x - 1]))
		return (true);
	if (x < ft_strlen(map[y]) - 1 && is_white_space(map[y][x + 1]))
		return (true);
	if (x >= ft_strlen(map[y]) - 1)
		return (true);
	if (y + 1 == map_max - 1)
	{
		if (above_checker(map, y + 1))
			return (true);
	}
	return (false);
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

void	door_allocation(t_data *data)
{
	if (!data->map)
		return ;
	data->ndoors = 0;
	data->ndoors = count_chars('D', data, false);
	if (data->ndoors > 0)
	{
		data->doors = alloc(sizeof(t_doorpos) * data->ndoors, ALLOC);
		if (!data->doors)
			return (fireforce(data, AFTER), exit(1), (void)0);
		count_chars('D', data, true);
	}
	return ;
}
