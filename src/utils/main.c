/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/26 15:02:39 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
