/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:26:40 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/30 18:34:04 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	print_stff(t_data *data)
{
	size_t	map_index;

	printf("\nnorth :%s", data->direction_paths->north_p);
	printf("\nwest :%s", data->direction_paths->west_p);
	printf("\neast :%s", data->direction_paths->east_p);
	printf("\nsouth :%s\n", data->direction_paths->south_p);
	printf("\nF :%s", data->colors->f);
	printf("\nc :%s\n", data->colors->c);
	map_index = 0;
	while (map_index < data->map_y)
	{
		printf("%s\n", data->map[map_index]);
		map_index++;
	}
	printf("\n\n");
	printf("the player is in(%zu,%zu)\n", data->player_x, data->player_y);
}

bool	validate_color_strings(t_colors *colors)
{
	colors->c = skip_spaces(colors->c);
	colors->f = skip_spaces(colors->f);
	if (!valid_colorstr(colors->c + 1) || !valid_colorstr(colors->f + 1))
		return (ERROR);
	if (count_char(colors->c, ',') != 2 || count_char(colors->f, ',') != 2)
		return (ERROR);
	return (SUCCESS);
}

bool	allocate_color_arrays(t_colors *colors, t_data *data)
{
	colors->f_c = alloc(sizeof(int) * 4, ALLOC);
	colors->c_c = alloc(sizeof(int) * 4, ALLOC);
	if (!colors->f_c || !colors->c_c)
		return (fireforce(data, AFTER), false);
	return (SUCCESS);
}

bool	parse_color_values(t_colors *colors)
{
	int	color_index;

	color_index = 0;
	while (color_index < 3)
	{
		colors->f_c[color_index] = ft_atoi(colors->splitted_f[color_index]);
		colors->c_c[color_index] = ft_atoi(colors->splitted_c[color_index]);
		if (colors->f_c[color_index] == -1 || colors->c_c[color_index] == -1)
		{
			free2d(colors->splitted_c, 5);
			free2d(colors->splitted_f, 5);
			return (ERROR);
		}
		color_index++;
	}
	return (SUCCESS);
}

bool	color_filling(t_data *data)
{
	t_colors	*colors;

	colors = data->colors;
	if (validate_color_strings(colors) == ERROR)
		return (ERROR);
	colors->splitted_c = ft_split(skip_spaces(colors->c + 1), ',');
	colors->splitted_f = ft_split(skip_spaces(colors->f + 1), ',');
	if (!colors->splitted_c || !colors->splitted_f)
		return (ERROR);
	if (allocate_color_arrays(colors, data) == ERROR)
		return (ERROR);
	if (parse_color_values(colors) == ERROR)
		return (ERROR);
	free2d(colors->splitted_c, 5);
	free2d(colors->splitted_f, 5);
	colors->c_color = rgb_to_int(colors->c_c[0], colors->c_c[1],
			colors->c_c[2]);
	colors->f_color = rgb_to_int(colors->f_c[0], colors->f_c[1],
			colors->f_c[2]);
	return (SUCCESS);
}
