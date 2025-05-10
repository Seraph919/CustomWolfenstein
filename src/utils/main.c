/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/10 20:18:53 by asoudani         ###   ########.fr       */
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
    data->cub_file = malloc(sizeof(char *) * (len + 1));
    if (!data->cub_file)
        return (ERROR);
    while ((line = get_next_line(fd)))
    {
        data->cub_file[y++] = line;
    }
    data->cub_file[y] = NULL;
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
    
    data->direction_paths = malloc(sizeof (t_direction_p));
    if (!data->direction_paths)
    return (ERROR);
    set_tozero(data);
    direction = data->direction_paths;
    data->map = malloc(sizeof(char *) * (data->map_y - 6) + 1);
    if (!data->map)
        return (ERROR); // free on error
    i = -1;
    k = 0;
    while (data->cub_file[++i])
    {
        if (char_in(data->cub_file[i]) && char_in(data->cub_file[i]) != SYERROR)
        {
            if (data->cub_file[i] && is_first_in('N', data->cub_file[i])) // NO
                direction->north_p  = ft_strdup(data->cub_file[i]), direction->n_ofn++; // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('S', data->cub_file[i])) // SO
                direction->south_p  = ft_strdup(data->cub_file[i]), direction->n_ofs++; // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('W', data->cub_file[i])) // WE
                direction->west_p  = ft_strdup(data->cub_file[i]), direction->n_ofw++; // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('E', data->cub_file[i])) // EA
                direction->east_p  = ft_strdup(data->cub_file[i]), direction->n_ofe++; // free the pre-existed one..
            else if (data->cub_file[i] && is_first_in('F', data->cub_file[i])) // F
                data->f_color = ft_strdup(data->cub_file[i]), direction->n_off++;
            else if (data->cub_file[i] && is_first_in('C', data->cub_file[i])) // C 
                data->c_color = ft_strdup(data->cub_file[i]), direction->n_ofc++;
            else
                data->map[k++] = ft_strdup(data->cub_file[i]);
        }
    }
    data->map[k] = NULL;
    data->map_y = k;
    return (SUCCESS);
}

void set_tozero(t_data *data)
{
    data->direction_paths->n_ofe = 0;
    data->direction_paths->n_ofw = 0;
    data->direction_paths->n_ofs = 0;
    data->direction_paths->n_ofn = 0;
    data->direction_paths->n_ofc = 0;
    data->direction_paths->n_off = 0;
}

bool texture_loading(t_data *data)
{
    t_direction_p *dir;
    int width;
    int height;
    int     i;

    dir = data->direction_paths;
    i = 0;
    data->north = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->north_p), &width, &height);
    if (!data->north)
        return (printf("texture error\n"), ERROR);
    data->west = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->west_p), &width, &height);
    if (!data->west)
        return (printf("texture error\n"), ERROR);
    data->east = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->east_p), &width, &height);
    if (!data->east)
        return (printf("texture error\n"), ERROR);
    data->south = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->south_p), &width, &height);
    if (!data->south)
        return (printf("texture error\n"), ERROR);
    return (SUCCESS);
}

bool outer_error_check(t_data *data)
{
    t_direction_p *dir;
    
    dir = data->direction_paths;
    if (dir ->n_ofs > 1 || dir ->n_ofn > 1 || dir ->n_ofw > 1 
        || dir ->n_ofe > 1 || dir ->n_ofc > 1 || dir ->n_off > 1)
        return (ERROR);
    return (SUCCESS);
}

bool file_related(t_data *data)
{
    if (file_read(data) || outer_resources(data) || outer_error_check(data))
        return (printfd(2, "Found an Error in .cub Processing\n"),ERROR);
     // need to free in case of errors

    printf("north :%s", data->direction_paths->north_p);
    printf("west :%s", data->direction_paths->west_p);
    printf("east :%s", data->direction_paths->east_p);
    printf("south :%s\n", data->direction_paths->south_p);
    printf("F :%s", data->f_color);
    printf("c :%s\n", data->c_color);

    for (size_t i = 0; i < data->map_y; i++)
        printf("%s", data->map[i]);
    if (texture_loading(data))
        return (ERROR);
    return (SUCCESS);
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
    // fireforce(); removed GC so the leaks are there to remove..
    return (SUCCESS);
}

// take the paths and convert them to images
// check the images

// check the dup, the order, only one space before path..
// paths then colors then map.

// take a copy of the map and check the boarders..

// check if the character have a void space near it

