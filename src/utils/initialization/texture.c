/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:50:11 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/26 20:52:53 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	set_tozero(t_data *data)
{
	data->direction_paths->n_ofe = 0;
	data->direction_paths->n_ofw = 0;
	data->direction_paths->n_ofs = 0;
	data->direction_paths->n_ofn = 0;
	data->direction_paths->n_ofc = 0;
	data->direction_paths->n_off = 0;
	data->south = NULL;
	data->north = NULL;
	data->west = NULL;
	data->east = NULL;
}

static bool	load_single_texture(t_data *data, void **texture, char *path)
{
	int	width;
	int	height;

	if (!data || !texture || !path)
		return (printf("Error\nInvalid parameters for texture loading\n"),
			ERROR);
	if (!data->mlx_ptr)
		return (printf("Error\nMLX not initialized\n"), ERROR);
	*texture = mlx_xpm_file_to_image(data->mlx_ptr, path, &width, &height);
	if (!*texture)
		return (printf("Error\nTexture Error: %s\n", path), ERROR);
	return (SUCCESS);
}

bool	texture_loading(t_data *data)
{
	t_direction_p	*dir;

	dir = data->direction_paths;
	if (load_single_texture(data, &data->north, dir->north_p) == ERROR)
		return (ERROR);
	if (load_single_texture(data, &data->west, dir->west_p) == ERROR)
		return (ERROR);
	if (load_single_texture(data, &data->east, dir->east_p) == ERROR)
		return (ERROR);
	if (load_single_texture(data, &data->south, dir->south_p) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static bool	check_direction_counts(t_direction_p *dir)
{
	if (dir->n_ofs > 1 || dir->n_ofn > 1 || dir->n_ofw > 1 || dir->n_ofe > 1
		|| dir->n_ofc > 1 || dir->n_off > 1)
		return (ERROR);
	return (SUCCESS);
}

bool	outer_error_check(t_data *data)
{
	t_direction_p	*dir;

	dir = data->direction_paths;
	if (check_direction_counts(dir) == ERROR)
		return (ERROR);
	if (color_filling(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
