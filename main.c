/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/07 09:48:00 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

bool map_copying(t_data *data, int len)
{
    int fd;
    int y;
    char *line;
    
    y = 0;
    fd = open("src/map/map.cub", O_RDONLY);
    if (fd < 0 || len == 0)
        return (printfd(2, "Error in file opening\n"),ERROR);
    data->map = alloc(sizeof(char *) * len + 1, ALLOC);
    if (!data->map)
        return (ERROR);
    while ((line = get_next_line(fd)))
    {
        data->map[y] = line;
        y++;
        free(line);
    }
    data->map[y] = NULL;
    data->map_y = y;
    close(fd);
    return (SUCCESS);
}

bool map_read(t_data *data)
{
    int fd;
    int y;
    char *line;

    y = 0;
    fd = open("src/map/map.cub", O_RDONLY);
    if (fd < 0)
        return (printfd(2, "Error in file opening\n"),ERROR);
    while ((line = get_next_line(fd)))
    {
        y++;
        free(line);
    }
    close(fd);
    if (y == 0)
        return (ERROR);
    if (map_copying(data, y))
        return (ERROR);
    return (SUCCESS);
}

bool map_related(t_data *data)
{
    if (map_read(data))
        return (printfd(2, "Found an Error in Map Processing\n"),ERROR);
    for (int i = 0;(size_t)i < data->map_y; i++)
        printf("%s", data->map[i]);
    return (SUCCESS);
}

int main(int ac, char **av)
{
    if (ac != 1)
        return (1);
    t_data data;
    (void)av;
    data.mlx_ptr = mlx_init();
    if (map_related(&data))
        return (ERROR);
    return (SUCCESS);
}