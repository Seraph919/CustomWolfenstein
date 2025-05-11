/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/11 22:07:06 by asoudani         ###   ########.fr       */
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

bool texture_valid(char *s1, char *s2)
{
    if (ft_strncmpp(skip_spaces(s1), s2, 2) == 0)
        return (true);
    return (false);
}


bool outer_resources(t_data *data)
{
    t_colors *colors;
    int i;
    int k;
    t_direction_p *direction;
    int after_map;
    
    data->colors = malloc(sizeof(t_colors));
    if (!data->colors)
        return (ERROR);
    colors = data->colors;
        
    data->direction_paths = malloc(sizeof (t_direction_p));
    if (!data->direction_paths)
        return (ERROR);
    
    set_tozero(data);
    after_map = 0;
    direction = data->direction_paths;
    data->map = malloc(sizeof(char *) * (data->map_y - 6) + 1);
    if (!data->map)
        return (ERROR); // free on error
    i = -1;
    k = 0;
    while (data->cub_file[++i])
    {
        if (char_in(data->cub_file[i]))
        {
            if (ft_strncmpp("1", skip_spaces(data->cub_file[i]), 1) && after_map > 0)
                return (ERROR); // free the stuff if an error occured..
            if (data->cub_file[i] && texture_valid(data->cub_file[i], "NO")) // NO
                direction->north_p  = ft_strdup(data->cub_file[i]), direction->n_ofn++; // free the pre-existed one..
            else if (data->cub_file[i] && texture_valid(data->cub_file[i], "SO")) // SO
                direction->south_p  = ft_strdup(data->cub_file[i]), direction->n_ofs++; // free the pre-existed one..
            else if (data->cub_file[i] && texture_valid(data->cub_file[i], "WE")) // WE
                direction->west_p  = ft_strdup(data->cub_file[i]), direction->n_ofw++; // free the pre-existed one..
            else if (data->cub_file[i] && texture_valid(data->cub_file[i], "EA")) // EA
                direction->east_p  = ft_strdup(data->cub_file[i]), direction->n_ofe++; // free the pre-existed one..
            else if (data->cub_file[i] && texture_valid(data->cub_file[i], "F ")) // F
                colors->f = ft_strdup(data->cub_file[i]), direction->n_off++;
            else if (data->cub_file[i] && texture_valid(data->cub_file[i], "C ")) // C 
                colors->c = ft_strdup(data->cub_file[i]), direction->n_ofc++;
            else
            {
                data->map[k++] = ft_strdup(data->cub_file[i]);
                after_map++; // check for anything after the map
            }
        }
        else if (after_map)
            return (ERROR); // if a newline found between map lines..
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
    if (color_filling(data) ==  ERROR)
        return (ERROR);
    
    return (SUCCESS);
}

void print_stff(t_data *data)
{
    printf("north :%s", data->direction_paths->north_p);
    printf("west :%s", data->direction_paths->west_p);
    printf("east :%s", data->direction_paths->east_p);
    printf("south :%s\n", data->direction_paths->south_p);
    printf("F :%s", data->colors->f);
    printf("c :%s\n", data->colors->c);

    for (size_t i = 0; i < data->map_y; i++)
        printf("%s", data->map[i]);
}

bool valid_colorstr(char *s)
{
    if (!s)
        return (false);
    s = skip_spaces(s);
    if (!s)
        return (false);
    while (*s)
    {
        if (!ft_isdigit(*s))
            return (false);
        if (*s == ',')
        {
            s++;
            if (*s == '\0' || !ft_isdigit(*s))
                return (false);
        }
        s++;
    }
    return (true);
}

bool color_filling(t_data *data)
{
    t_colors *colors;

    colors = data->colors;
    colors->c = skip_spaces(colors->c);
    colors->f = skip_spaces(colors->f);
    if (!valid_colorstr(colors->c + 1) || !valid_colorstr(colors->f + 1))
        return (ERROR);
    colors->splitted_c = ft_split(skip_spaces(colors->c + 1), ',');
    colors->splitted_f = ft_split(skip_spaces(colors->f + 1), ',');
    if (!colors->splitted_c || !colors->splitted_f)
        return (ERROR);
    return (SUCCESS);
}

bool file_related(t_data *data)
{
    if (file_read(data) || outer_resources(data) || outer_error_check(data))
        return (printfd(2, "ERROR\nFound an Error in .cub Processing\n"),ERROR);
     // need to free in case of errors
    
    if (map_validation(data->map, data->map_y) == ERROR)
        return (printfd(2, "ERROR\nFound an Error in map\n"),ERROR); // free the stuff
    
    print_stff(data);
    
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

// TODO colors should be at max 255,.. no nigatives
// * add a 2d int array and fill it with them numbers..
// * check the strings first, check if there is a number after ','
// * then send that number to atoi and check if it's negative.. 
// * or more that 255..

// TODO recheck boarders and stuff + flood fill..
// * The problem with the flood fill is that i should know if the player
// * should or must be surrounded by 0s or it's ok if his path is closed by 1s
// * since the map that was given in the intra is closed too.. 

