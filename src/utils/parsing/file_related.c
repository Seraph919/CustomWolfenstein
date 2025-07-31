/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:47:07 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/31 14:22:37 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

int	allocations(t_data *data)
{
	data->colors = alloc(sizeof(t_colors), ALLOC);
	if (!data->colors)
		return (exit_error(NULL, "fatal allocation error"), 1);
	data->direction_paths = alloc(sizeof(t_direction_p), ALLOC);
	if (!data->direction_paths)
		return (exit_error(NULL, "fatal allocation error"), 1);
	data->map = alloc(sizeof(char *) * (data->map_y) + 1, ALLOC);
	if (!data->map)
		return (exit_error(NULL, "fatal allocation error"), 1);
	return (SUCCESS);
}

void	t_norm2_init(t_data *data, t_norm2 *norm)
{
	norm->colors = data->colors;
	data->colors->f = NULL;
	data->colors->c = NULL;
	norm->after_map = 0;
	norm->direction = data->direction_paths;
	norm->i = -1;
	norm->k = 0;
}

bool	handle_texture_direction(t_norm2 *n, char *line)
{
	if (texture_valid(line, "NO"))
	{
		n->direction->north_p = ft_strdup(strafter_type(line));
		n->direction->n_ofn++;
		return (true);
	}
	if (texture_valid(line, "SO"))
	{
		n->direction->south_p = ft_strdup(strafter_type(line));
		n->direction->n_ofs++;
		return (true);
	}
	return (false);
}

bool	handle_texture_we_ea(t_norm2 *n, char *line)
{
	if (texture_valid(line, "WE"))
	{
		n->direction->west_p = ft_strdup(strafter_type(line));
		n->direction->n_ofw++;
		return (true);
	}
	if (texture_valid(line, "EA"))
	{
		n->direction->east_p = ft_strdup(strafter_type(line));
		n->direction->n_ofe++;
		return (true);
	}
	return (false);
}

int	check_next_index(char **map, int x, int y)
{
	if (!map || !*map || !map[y])
		return (ERROR);
	if (map[y][x] != '0' && map[y][x] != '\0'
		&& is_white_space(map[y][x]) == false)
		return (SUCCESS);
	return (ERROR);
}
