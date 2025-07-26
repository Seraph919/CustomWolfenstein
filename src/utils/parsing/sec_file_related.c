/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_file_related.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:34:32 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/26 21:35:42 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

bool	handle_colors(t_norm2 *n, char *line)
{
	if (texture_valid(line, "F "))
	{
		n->colors->f = ft_strdup(line);
		n->direction->n_off++;
		return (true);
	}
	if (texture_valid(line, "C "))
	{
		n->colors->c = ft_strdup(line);
		n->direction->n_ofc++;
		return (true);
	}
	return (false);
}

void	handle_map_element(t_data *data, t_norm2 *n, char *line)
{
	data->map[n->k++] = ft_strdup(line);
	n->after_map++;
}

bool	element_allocation(t_data *data, t_norm2 *n)
{
	char	*line;

	line = data->cub_file[n->i];
	if (ft_strncmpp("1", skip_spaces(line), 1) && n->after_map > 0)
		return (ERROR);
	if (!line)
		return (SUCCESS);
	if (handle_texture_direction(n, line))
		return (SUCCESS);
	if (handle_texture_we_ea(n, line))
		return (SUCCESS);
	if (handle_colors(n, line))
		return (SUCCESS);
	handle_map_element(data, n, line);
	return (SUCCESS);
}

bool	outer_resources(t_data *data)
{
	t_norm2	norm;

	if (allocations(data) == ERROR)
		return (ERROR);
	t_norm2_init(data, &norm);
	set_tozero(data);
	while (data->cub_file[++norm.i])
	{
		if (char_in(data->cub_file[norm.i]))
		{
			if (element_allocation(data, &norm) == ERROR)
				return (ERROR);
		}
		else if (norm.after_map)
			return (ERROR);
	}
	if (!data->colors->f || !data->colors->c)
		return (ERROR);
	data->map[norm.k] = NULL;
	data->map_y = norm.k;
	return (SUCCESS);
}
