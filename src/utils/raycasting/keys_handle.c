/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:12:29 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/25 18:16:15 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->keys_held |= (1 << 0);
	if (keycode == XK_space)
	{
		game->animation_running = true;
		game->sounds.fire = true;
	}
	else if (keycode == S_KEY)
		game->keys_held |= (1 << 1);
	else if (keycode == A_KEY)
		game->keys_held |= (1 << 2);
	else if (keycode == D_KEY)
		game->keys_held |= (1 << 3);
	else if (keycode == LEFT_ARROW)
		game->keys_held |= (1 << 4);
	else if (keycode == RIGHT_ARROW)
		game->keys_held |= (1 << 5);
	else if (keycode == XK_E || keycode == XK_e)
		is_open(game, true);
	else if (keycode == XK_Escape)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	int	i;

	i = 0;
	if (keycode == W_KEY)
		game->keys_held &= ~(1 << 0);
	else if (keycode == S_KEY)
		game->keys_held &= ~(1 << 1);
	else if (keycode == A_KEY)
		game->keys_held &= ~(1 << 2);
	else if (keycode == D_KEY)
		game->keys_held &= ~(1 << 3);
	else if (keycode == LEFT_ARROW)
		game->keys_held &= ~(1 << 4);
	else if (keycode == RIGHT_ARROW)
		game->keys_held &= ~(1 << 5);
	else if (keycode == XK_p || keycode == XK_P)
	{
		while (i < NUM_RAYS)
		{
			printf("ray[%d] isdoor == %d\n", i, game->rays[i].is_door);
			i++;
		}
	}
	return (0);
}
