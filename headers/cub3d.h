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


#define MAP_W 15
#define MAP_H 11
#define TILE_SIZE 16

#define WALL_COLOR 0x000080
#define EMPTY_COLOR 0x808080
#define PLAYER 0xFFFF00


# define U_KEY 119
# define D_KEY 115
# define L_KEY 97
# define R_KEY 100

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

typedef struct s_player
{
    int x;
    int y;
    float angle;
} t_player;

typedef struct s_game
{
    void *mlx;
    void *window;
    void *img;
    char *addr;
    char **map;
    int bpp;
    int size_line;
    int endian;
    int map_h;
    int map_w;
    t_player *player;
} t_game;

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

// Init funcs
int init_mlx(t_game *game, char **map);
int get_map_height(char **map);
int get_map_width(char **map);

// Events funcs
int key_press(int keycode, t_game *game);
int close_window(t_game *game);

// game funcs
void render_map(t_game *game, char **map);

#endif