/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:50:04 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/27 13:50:12 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

bool	initialize_game_data(t_data *data, t_game *game)
{
	printf("the player side is : %c\n", data->player_char);
	game->map = NULL;
	game->data = data;
	return (SUCCESS);
}

void	image_adrr(t_game *game, int i, int width, int height)
{
	game->pistol_texture[i].addr = mlx_get_data_addr(
			game->pistol_texture[i].img,
			&game->pistol_texture[i].bpp, &game->pistol_texture[i].size_line,
			&game->pistol_texture[i].endian);
	game->pistol_texture[i].width = width;
	game->pistol_texture[i].height = height;
}

int	load_pistol_textures(t_game *game)
{
	t_pistol_stff	pistol;

	pistol.i = -1;
	game->pistol_texture = alloc(sizeof(t_texture) * 7, ALLOC);
	while (++pistol.i < 7)
	{
		pistol.num_str = ft_itoa(pistol.i + 1);
		pistol.file_name = ft_strjoin(pistol.num_str, ".xpm");
		pistol.temp = ft_strjoin("./src/textures/", pistol.file_name);
		game->pistol_texture[pistol.i].img = mlx_xpm_file_to_image(game->mlx,
				pistol.temp, &pistol.width, &pistol.height);
		free(pistol.num_str);
		free(pistol.file_name);
		free(pistol.temp);
		if (!game->pistol_texture[pistol.i].img)
			return (exit_error(game->data, "Failed to load pistol texture"), 1);
		image_adrr(game, pistol.i, pistol.width, pistol.height);
	}
	return (0);
}

int	init_mlx(t_game *game)
{
	int	y;

	if (init_vars(game) == ERROR)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	game->rays = alloc(sizeof(t_ray) * NUM_RAYS, ALLOC);
	if (!game->rays)
		return (exit_error(game->data, "fatal allocation error"), 0);
	set_player_direction(game);
	y = -1;
	while (++y < game->map_h)
		get_player_angle(game, y);
	set_mouse_and_textures(game);
	if (!game->textures)
		return (exit_error(game->data, "fatal allocation error"), 1);
	load_direction_textures(game);
	game->imgs = alloc(sizeof(char *) * 4, ALLOC);
	if (texture_data(game) == ERROR)
		return (ERROR);
	if (load_pistol_textures(game) != 0)
		return (1);
	game->is_game_running = true;
	return (1);
}
