/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanmazir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:13:59 by aanmazir          #+#    #+#             */
/*   Updated: 2025/07/26 15:29:31 by aanmazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	move_forward(t_game *game)
{
	float	move_x;
	float	move_y;
	float	new_x;
	float	new_y;

	move_x = cos(game->player->angle) * PLAYER_SPEED;
	move_y = sin(game->player->angle) * PLAYER_SPEED;
	new_x = game->player->x + move_x;
	new_y = game->player->y + move_y;
	if (is_valid_move(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
	else if (is_valid_move(game, game->player->x + move_x, game->player->y))
		game->player->x += move_x;
	else if (is_valid_move(game, game->player->x, game->player->y + move_y))
		game->player->y += move_y;
	else
	{
		if (game->keys_held & (1 << 2))
			strafe_left(game);
		else if (game->keys_held & (1 << 3))
			strafe_right(game);
	}
}

void	move_backward(t_game *game)
{
	float	move_y;
	float	move_x;
	float	new_x;
	float	new_y;

	move_x = cos(game->player->angle) * PLAYER_SPEED;
	move_y = sin(game->player->angle) * PLAYER_SPEED;
	new_x = game->player->x - move_x;
	new_y = game->player->y - move_y;
	if (is_valid_move(game, (int)(new_x), (int)(new_y)))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
	else if (is_valid_move(game, game->player->x + move_x, game->player->y))
		game->player->y += move_y;
	else if (is_valid_move(game, game->player->x, game->player->y + move_y))
		game->player->x += move_x;
	else
	{
		if (game->keys_held & (1 << 2))
			strafe_left(game);
		else if (game->keys_held & (1 << 3))
			strafe_right(game);
	}
}

void	strafe_left(t_game *game)
{
	float	move_x;
	float	move_y;
	float	new_x;
	float	new_y;

	move_x = cos(game->player->angle - PI / 2) * PLAYER_SPEED;
	move_y = sin(game->player->angle - PI / 2) * PLAYER_SPEED;
	new_x = game->player->x + move_x;
	new_y = game->player->y + move_y;
	if (is_valid_move(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
	else
		printf("Invalid move: strafe left failed.\n");
}

void	strafe_right(t_game *game)
{
	float	move_x;
	float	move_y;
	float	new_x;
	float	new_y;

	move_x = cos(game->player->angle + PI / 2) * PLAYER_SPEED;
	move_y = sin(game->player->angle + PI / 2) * PLAYER_SPEED;
	new_x = game->player->x + move_x;
	new_y = game->player->y + move_y;
	if (is_valid_move(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
	else
		printf("Invalid move: strafe right failed.\n");
}
