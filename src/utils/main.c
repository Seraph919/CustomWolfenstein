/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/07 20:59:18 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

bool file_copying(t_data *data, int len)
{
    int fd;
    int y;
    char *line;
    
    y = 0;
    fd = open("src/map/file.cub", O_RDONLY);
    if (fd < 0 || len == 0)
        return (printfd(2, "Error in file opening\n"),ERROR);
    data->cub_file = alloc((sizeof(char *) * len) + 1, ALLOC);
    if (!data->cub_file)
        return (ERROR);
    while ((line = get_next_line(fd)))
    {
        data->cub_file[y++] = line;
    }
    data->cub_file[y - 1] = NULL;
    data->map_y = y;
    close(fd);
    return (SUCCESS);
}

bool get_allocation_size(int *y)
{
    char *line;
    int fd;
    
    *y = 0;
    fd = open("src/map/file.cub", O_RDONLY);
    if (fd < 0)
        return (printfd(2, "Error in file opening\n"),ERROR);
    while ((line = get_next_line(fd)))
    {
        *y += 1;
        free(line);
    }
    close(fd);
    if (*y == 0)
        return (ERROR);
    return (SUCCESS);
}
bool file_read(t_data *data)
{
    int y;

    y = 0;
    if (get_allocation_size(&y) || file_copying(data, y))
        return (ERROR);
    return (SUCCESS);
}

bool outer_resources(t_data *data)
{
    int i;
    int k;
    t_direction_p *direction;
    
    data->direction_paths = alloc(sizeof (t_direction_p), ALLOC);
    if (!data->direction_paths)
        return (ERROR);
    direction = data->direction_paths;
    data->map = alloc (sizeof(char *) * (data->map_y - 6) + 1, ALLOC);
    if (!data->map)
        return (ERROR); // free on error
    i = -1;
    k = 0;
    while (data->cub_file[++i])
    {
        if (char_in(data->cub_file[i]) && char_in(data->cub_file[i]) != SYERROR)
        {
            if (data->cub_file[i] && is_first_in('N', data->cub_file[i])) // NO
                direction->north_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('S', data->cub_file[i])) // SO
                direction->south_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('W', data->cub_file[i])) // WE
                direction->west_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('E', data->cub_file[i])) // EA
                direction->east_p  = ft_strdup(data->cub_file[i]); // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('F', data->cub_file[i])) // F
                data->f_color = ft_strdup(data->cub_file[i]);
            else if (data->cub_file[i] && is_first_in('C', data->cub_file[i])) // C 
                data->c_color = ft_strdup(data->cub_file[i]);
            else
                data->map[k++] = ft_strdup(data->cub_file[i]);
        }
    }
    return (SUCCESS);
}

bool file_related(t_data *data)
{
    if (file_read(data))
    return (printfd(2, "Found an Error in .cub Processing\n"),ERROR);
    if (outer_resources(data)) // need to free in case of errors
    return (printfd(2, "Found an Error in The .cub File\n"), ERROR); // also here
    printf("north :%s", data->direction_paths->north_p);
    printf("west :%s", data->direction_paths->west_p);
    printf("east :%s", data->direction_paths->east_p);
    printf("south :%s\n", data->direction_paths->south_p);
    printf("F :%s", data->f_color);
    printf("c :%s\n", data->c_color);

    for (int i = 0; data->map[i]; i++)
        printf("%s", data->map[i]);
    return (SUCCESS);
}

void fireforce(void)
{
    alloc(0, FREE);
}

int main(int ac, char **av)
{
    if (ac != 1)
        return (1);
    t_data data;
    (void)av;
    data.mlx_ptr = mlx_init();
    if (file_related(&data))
        return (ERROR);
    fireforce();
    return (SUCCESS);
}