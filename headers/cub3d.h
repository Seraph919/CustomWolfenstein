/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/07 20:53:42 by asoudani         ###   ########.fr       */
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
#include "../src/libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
#include "../src/printfd/printfd.h"
#include "../src/gc/garbage.h"
#include "../src/get_next_line/get_next_line.h"

#define SUCCESS 0
#define ERROR 1
#define SYERROR 2


#define MAP_W 13
#define MAP_H 10
#define TILE_SIZE 64

#define WALL_COLOR 0xFF0000
#define EMPTY_COLOR 0x808080

// ** this will be used to store the paths to the direction textures..
typedef struct s_direction
{
    char *east_p;
    char *west_p;
    char *north_p;
    char *south_p;
} t_direction_p;

// typedef struct s_data
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     char **map;
//     char **cub_file;
//     size_t map_x;
//     size_t map_y;
//     size_t player_x;
//     char *f_color;
//     char *c_color;
//     size_t player_y;
//     t_direction_p *dir_paths;
// }   t_data;

typedef struct s_data
{
    void *mlx;
    void *window;
    void *img;
    char *addr;
    int bpp;
    int size_line;
    int endian;
} t_data;

// typedef struct s_game
// {
//     t_data *data;
// }   t_game;

// int char_in(char *s);
// bool not_in_str(char c, char *s);
// bool not_in_str(char c, char *s);
// bool is_white_space(char c);
// bool file_copying(t_data *data, int len);
// bool get_allocation_size(int *y);
// bool file_read(t_data *data);
// bool file_related(t_data *data);
// bool is_first_in(char c, char *s);


// t_game *start_game(t_game *game);

#endif