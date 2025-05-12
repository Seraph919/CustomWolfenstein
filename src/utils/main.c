/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 17:04:25 by asoudani         ###   ########.fr       */
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
    // if (data->cub_file)
    //     free2d(data->cub_file, data->file_size);
    if (place == AFTER)
        free_texture(data);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
}

bool file_copying(t_data *data, int len)
{
    int fd;
    int y;
    char *line;
    
    y = 0;
    data->file_size = len;
    fd = open("src/map/file.cub", O_RDONLY);
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
        return (ERROR); // file copp
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
    
    data->colors = alloc(sizeof(t_colors), ALLOC);
    if (!data->colors)
        return (ERROR);
    colors = data->colors;
        
    data->direction_paths = alloc(sizeof (t_direction_p), ALLOC);
    if (!data->direction_paths)
        return (ERROR);
    
    set_tozero(data);
    after_map = 0;
    direction = data->direction_paths;
    data->map = alloc(sizeof(char *) * (data->map_y - 6) + 1, ALLOC);
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

void set_tozero(t_data *data)
{
    data->direction_paths->n_ofe = 0;
    data->direction_paths->n_ofw = 0;
    data->direction_paths->n_ofs = 0;
    data->direction_paths->n_ofn = 0;
    data->direction_paths->n_ofc = 0;
    data->direction_paths->n_off = 0;
    data->south = NULL;
    data->north = NULL;
    data->west = NULL;
    data->east = NULL;
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
        return (printf("Error\ntexture error\n"), ERROR);
    data->west = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->west_p), &width, &height);
    if (!data->west)
        return (printf("Error\ntexture error\n"), ERROR);
    data->east = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->east_p), &width, &height);
    if (!data->east)
        return (printf("Error\ntexture error\n"), ERROR);
    data->south = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->south_p), &width, &height);
    if (!data->south)
        return (printf("Error\ntexture error\n"), ERROR);
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
        if (!ft_isdigit(*s) && *s != ',' && *s != '\n')
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
    int i;
    t_colors *colors;

    colors = data->colors;
    colors->c = skip_spaces(colors->c);
    colors->f = skip_spaces(colors->f);
    if (!valid_colorstr(colors->c + 1) || !valid_colorstr(colors->f + 1))
        return (ERROR);
    if (count_char(colors->c,',') != 2 || count_char(colors->f,',') != 2)
        return (ERROR);
    colors->splitted_c = ft_split(skip_spaces(colors->c + 1), ',');
    colors->splitted_f = ft_split(skip_spaces(colors->f + 1), ',');
    if (!colors->splitted_c || !colors->splitted_f)
        return (ERROR);
    colors->f_c = alloc(sizeof(int) * 4, ALLOC);
    colors->c_c = alloc(sizeof(int) * 4, ALLOC);
    if (!colors->f_c || !colors->c_c )
    return (ERROR);
    i = -1;
    while (++i < 3)
    {
        colors->f_c[i] = ft_atoi(colors->splitted_f[i]);
        colors->c_c[i] = ft_atoi(colors->splitted_c[i]);
        if (colors->f_c[i] == -1 || colors->c_c[i] == -1)
        {
            free2d(colors->splitted_c, 5);
            free2d(colors->splitted_f, 5);
            return (ERROR);
        }// free stuff here..
    }
    free2d(colors->splitted_c, 5);
    free2d(colors->splitted_f, 5);
    return (SUCCESS);
}

bool file_related(t_data *data)
{
    if (file_read(data) || outer_resources(data) || outer_error_check(data))
        return (printfd(2, "ERROR\nFound an Error in .cub Processing\n"), fireforce(data, M_ERROR), ERROR);
     // if !file_read free free (data->cub_file);
     // if (!outer) free data->colors data->directions, data->map
     // free 2d colors->splitted_c.. colors->c_c also
    if (map_validation(data->map, data->map_y, data) == ERROR)
        return (printfd(2, "ERROR\nFound an Error in map\n"), fireforce(data, M_ERROR), ERROR); // free the stuff
    print_stff(data);
    
    if (texture_loading(data))
        return (fireforce(data, AFTER), ERROR);
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
    fireforce(&data, AFTER); //removed GC so the leaks are there to remove..
    return (SUCCESS);
}

// TODO colors should be at max 255,.. no nigatives
// * add a 2d int array and fill it with them numbers.. (done!)
// * check the strings first, check if there is a number after ',' (done!)
// * then send that number to atoi and check if it's negative.. (done!)
// * or more that 255.. (done!)

// TODO free on errors~ (prob done!)

// TODO recheck boarders and stuff (done !)
// * The problem with the flood fill is that i should know if the player
// * should or must be surrounded by 0s or it's ok if his path is closed by 1s
// * since the map that was given in the intra is closed too.. 

// TODO flood fill..
// * i need to know the error cases first then see what can i do about them!
