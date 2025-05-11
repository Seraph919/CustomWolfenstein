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
#include <float.h>
#include <math.h>
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
#define TILE_SIZE 8
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FOV 60
#define NUM_RAYS WINDOW_WIDTH
#define WALL_COLOR 0x000080
#define EMPTY_COLOR 0x808080
#define PLAYER_COLOR 0xFFFF00
#define WALL_STRIP_WIDTH 1
#define PLAYER_SIZE 4

#define U_KEY   85
#define L_KEY   76
#define R_KEY   82

#define PLAYER 0xFF0000

#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363

// Radians conversion
#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define HALF_PI 1.57079632679
#define DEG_TO_RAD 0.01745329251 // PI / 180.0

// Player movement constants
#define MOVE_SPEED 0.05
#define ROTATION_SPEED 0.03

// Texture properties
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define PLAYER_SPEED 0.1f

#define ROT_SPEED 0.05

// This will be used to store the paths to the direction textures
typedef struct s_direction
{
    char *east_p;
    char *west_p;
    char *north_p;
    char *south_p;
} t_direction_p;

// Ray structure to store ray casting results
typedef struct s_ray
{
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    bool hit_vertical;
    int wall_face;   // 0=north, 1=south, 2=east, 3=west
    int wall_height;
} t_ray;

// Texture structure
typedef struct s_texture
{
    void *img;
    char *addr;
    int width;
    int height;
    int bpp;
    int size_line;
    int endian;
} t_texture;

typedef struct s_player
{
    float x;
    float y;
    float angle;
    float fov;
    double dir_x;   // Direction X
    double dir_y;   // Direction Y
    float move_speed;
    float rotation_speed;
    double plane_x;
    double plane_y;
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
    int window_width;
    int window_height;
    t_player *player;
    t_ray *rays;
    t_texture textures[4]; // North, South, East, West
    bool is_game_running;
    int key_state;
    int keys_held;
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
char **duplicate_map(char **map);


void move_forward(t_game *game);
void move_backward(t_game *game);
void strafe_left(t_game *game);
void strafe_right(t_game *game);

// game funcs
void render_map(t_game *game, char **map);

#endif