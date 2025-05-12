/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireforce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:42:06 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 19:45:35 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
    if (data->south)
        mlx_destroy_image(data->mlx_ptr, data->south);
    if (data->north)
        mlx_destroy_image(data->mlx_ptr, data->north);
    if (data->west)
        mlx_destroy_image(data->mlx_ptr, data->west);
    if (data->east)
        mlx_destroy_image(data->mlx_ptr, data->east);
}

void fireforce(t_data *data, t_place place)
{
    alloc(0, FREE);

    if (place == AFTER)
        free_texture(data);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
}
