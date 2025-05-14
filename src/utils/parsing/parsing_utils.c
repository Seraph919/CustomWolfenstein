/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:01 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 20:13:32 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

bool file_copying(t_data *data, int len, char **av)
{
    int fd;
    int y;
    char *line;
    
    y = 0;
    data->file_size = len;
    fd = open(av[1], O_RDONLY);
    if (fd < 0 || len == 0)
        return (printfd(2, "Error\nError in file opening\n"),ERROR);
    data->cub_file = alloc(sizeof(char *) * (len + 1), ALLOC);
    if (!data->cub_file)
        return (ERROR);
    while ((line = get_next_line(fd)))
    {
        data->cub_file[y++] = ft_strdup(line);
        free(line);
    }
    data->cub_file[y] = NULL;
    data->map_y = y;
    close(fd);
    return (SUCCESS);
}

bool get_allocation_size(int *y, char **av)
{
    char *line;
    int fd;
    
    *y = 0;
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (printfd(2, "Error in file opening\n"),ERROR);
    line = get_next_line(fd);
    while (line)
    {
        *y += 1;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    // printf("the len is : %d\n", *y);
    if (*y == 0)
        return (ERROR);
    return (SUCCESS);
}

bool file_read(t_data *data, char **av)
{
    int y;

    y = 0;
    if (!valid_file_name(av[1]))
        return (ERROR);
    if (get_allocation_size(&y, av) || file_copying(data, y, av))
        return (ERROR); // file copp
    return (SUCCESS);
}

bool texture_valid(char *s1, char *s2)
{
    if (ft_strncmpp(skip_spaces(s1), s2, 2) == 0)
        return (true);
    return (false);
}

size_t count_char(char *s, char c)
{
    size_t counter;

    counter = 0;
    if (!s)
        return (0);
    while (*s)
    {
        if (*s == c)
            counter++;
        s++;
    }
    return (counter);
}
