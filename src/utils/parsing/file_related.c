/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:47:07 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/24 10:57:49 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

int allocations(t_data *data)
{
    data->colors = alloc(sizeof(t_colors), ALLOC);
    if (!data->colors)
        return (exit_error(NULL, "fatal allocation error"), 1);
    data->colors->f = NULL;
    data->colors->c = NULL;
    data->direction_paths = alloc(sizeof (t_direction_p), ALLOC);
    if (!data->direction_paths)
        return (exit_error(NULL, "fatal allocation error"), 1);
    data->map = alloc(sizeof(char *) * (data->map_y) + 1, ALLOC);
    if (!data->map)
        return (exit_error(NULL, "fatal allocation error"), 1); 
    return (SUCCESS);
}

void t_norm2_init(t_data *data, t_norm2 *norm)
{
    norm->colors = data->colors;
    norm->after_map = 0;
    norm->direction = data->direction_paths;
    norm->i = -1;
    norm->k = 0;
}

bool element_allocation(t_data *data, t_norm2 *n) // ! leaks here!
{
    if (ft_strncmpp("1", skip_spaces(data->cub_file[n->i]), 1) && n->after_map > 0)
        return (ERROR);
    // printf("the str is -%s-\n",data->cub_file[n->i]);
    if (data->cub_file[n->i] && texture_valid(data->cub_file[n->i], "NO"))
        n->direction->north_p  = ft_strdup(strend_trim(data->cub_file[n->i], 1, index_after_spaces(data->cub_file[n->i]))), n->direction->n_ofn++;
    else if (data->cub_file[n->i] && texture_valid(data->cub_file[n->i], "SO"))
        n->direction->south_p  = ft_strdup(strend_trim(data->cub_file[n->i], 1, index_after_spaces(data->cub_file[n->i]))), n->direction->n_ofs++;
    else if (data->cub_file[n->i] && texture_valid(data->cub_file[n->i], "WE"))
        n->direction->west_p  = ft_strdup(strend_trim(data->cub_file[n->i], 1, index_after_spaces(data->cub_file[n->i]))), n->direction->n_ofw++;
    else if (data->cub_file[n->i] && texture_valid(data->cub_file[n->i], "EA"))
        n->direction->east_p  = ft_strdup(strend_trim(data->cub_file[n->i], 1, index_after_spaces(data->cub_file[n->i]))), n->direction->n_ofe++;
    else if (data->cub_file[n->i] && texture_valid(data->cub_file[n->i], "F "))
        n->colors->f = ft_strdup(data->cub_file[n->i]), n->direction->n_off++;
    else if (data->cub_file[n->i] && texture_valid(data->cub_file[n->i], "C "))
        n->colors->c = ft_strdup(data->cub_file[n->i]), n->direction->n_ofc++;
    else
    {
        data->map[n->k++] = ft_strdup(data->cub_file[n->i]);
        n->after_map++;
    }
    return (SUCCESS);
}

bool outer_resources(t_data *data)
{
    t_norm2 norm;
    
    if (allocations(data) == ERROR)
        return (ERROR);
    t_norm2_init(data, &norm);
    set_tozero(data);
    while (data->cub_file[++norm.i])
    {
        if (char_in(data->cub_file[norm.i]))
        {
            if (element_allocation(data, &norm) == ERROR || !data->colors->f || !data->colors->c)
                return(ERROR);
        }
        else if (norm.after_map)
            return (ERROR);
    }
    data->map[norm.k] = NULL;
    data->map_y = norm.k;
    return (SUCCESS);
}
