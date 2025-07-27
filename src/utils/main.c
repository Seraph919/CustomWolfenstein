/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/27 10:25:36 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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

void	print_stff(t_data *data)
{
	size_t	map_index;

	printf("north :%s", data->direction_paths->north_p);
	printf("west :%s", data->direction_paths->west_p);
	printf("east :%s", data->direction_paths->east_p);
	printf("south :%s\n", data->direction_paths->south_p);
	printf("F :%s", data->colors->f);
	printf("c :%s\n", data->colors->c);
	map_index = 0;
	while (map_index < data->map_y)
	{
		printf("%s", data->map[map_index]);
		map_index++;
	}
	printf("\n\n");
	printf("the player is in(%zu,%zu)\n", data->player_x, data->player_y);
}

static bool	validate_color_strings(t_colors *colors)
{
	colors->c = skip_spaces(colors->c);
	colors->f = skip_spaces(colors->f);
	if (!valid_colorstr(colors->c + 1) || !valid_colorstr(colors->f + 1))
		return (ERROR);
	if (count_char(colors->c, ',') != 2 || count_char(colors->f, ',') != 2)
		return (ERROR);
	return (SUCCESS);
}

static bool	allocate_color_arrays(t_colors *colors, t_data *data)
{
	colors->f_c = alloc(sizeof(int) * 4, ALLOC);
	colors->c_c = alloc(sizeof(int) * 4, ALLOC);
	if (!colors->f_c || !colors->c_c)
		return (fireforce(data, AFTER), false);
	return (SUCCESS);
}

static bool	parse_color_values(t_colors *colors)
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

// bool	initialize_game_data(t_data *data, t_game *game)
// {
// 	printf("the player side is : %c\n", data->player_char);
// 	game->map = NULL;
// 	game->data = data;
// 	return (SUCCESS);
// }

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;

	if (ac != 2)
		return (1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (printf("Error\nMLX initialization failed\n"), ERROR);
	if (file_process(&data, av))
		return (ERROR);
	initialize_game_data(&data, &game);
	start_gaming(game, data.map);
	fireforce(&data, AFTER);
	return (0);
}
// TODO : use file colors..
