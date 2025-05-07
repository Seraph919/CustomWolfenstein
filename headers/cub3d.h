/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/06 18:53:35 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../lib/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
#include "../src/printfd/printfd.h"
#include "../src/C_Garbage-Collector_v2/garbage.h"
#include "../src/get_next_line/get_next_line.h"

#define SUCCESS 0
#define ERROR 1

typedef struct s_data{
    void *mlx_ptr;
    void *win_ptr;
    char **map;
    size_t map_x;
    size_t map_y;
    size_t player_x;
    size_t player_y;
}   t_data;

#endif