/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:57:27 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/26 14:59:47 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

pid_t	play_sound(t_game *game)
{
	int	fd;
	int	id;

	id = fork();
	if (id == 0)
	{
		fd = 3;
		while (fd < 1024)
			close(fd++);
		if (game->sounds.game_vibes)
			execlp("paplay", "paplay", "./sounds/one_piece_ingame.wav",
				(char *)NULL);
		else
		{
			execlp("paplay", "paplay", "./sounds/pew.wav", (char *)NULL);
		}
		_exit(1);
	}
	if (game->sounds.game_vibes)
		return (id);
	else
		return (0);
}

pid_t	play_opening_sound(void)
{
	int	id;
	int	fd;

	id = fork();
	if (id == 0)
	{
		fd = 3;
		while (fd < 1024)
			close(fd++);
		execlp("paplay", "paplay", "./sounds/op.wav", (char *)NULL);
		_exit(1);
	}
	return (id);
}
