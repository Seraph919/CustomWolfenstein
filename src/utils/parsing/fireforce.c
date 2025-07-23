/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireforce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:42:06 by asoudani          #+#    #+#             */
/*   Updated: 2025/06/30 12:38:52 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void free2d(char **s, size_t size)
{
    size_t i;

    i = -1;
    if (!s)
        return ;
    while (++i < size - 1)
    {
        if (s && s[i])
            free(s[i]);
    }
    free(s);
}

void free_texture(t_data *data)
{
    if (data->game->south)
        mlx_destroy_image(data->game->mlx, data->game->south);
    if (data->game->north)
        mlx_destroy_image(data->game->mlx, data->game->north);
    if (data->game->west)
        mlx_destroy_image(data->game->mlx, data->game->west);
    if (data->game->east)
        mlx_destroy_image(data->game->mlx, data->game->east);
}

void fireforce(t_data *data, t_place place)
{
    alloc(0, FREE);

    if (place == AFTER)
        free_texture(data);
    mlx_destroy_display(data->game->mlx);
    free(data->game->mlx);
}

void exit_error(t_data *data, char *s)
{
    if (s)
        printfd(2, "%s\n", s);
    fireforce(data, AFTER);
    // alloc(0, FREE); // !doenst contain the mlx ptr and stuff.. so free them prev
    exit(1);
}
