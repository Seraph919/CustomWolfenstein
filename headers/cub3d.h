/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/14 15:24:45 by asoudani         ###   ########.fr       */
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
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FOV 60
#define NUM_RAYS WINDOW_WIDTH
#define WALL_COLOR 0x424242
#define EMPTY_COLOR 0xebebeb
#define PLAYER_COLOR 0x003aba
#define WALL_STRIP_WIDTH 1
#define PLAYER_SIZE 5

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
#define MOVE_SPEED 0.15
#define ROTATION_SPEED 0.02

// Texture properties
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define PLAYER_SPEED 0.15

#define ROT_SPEED 0.05

// This will be used to store the paths to the direction textures
// typedef struct s_direction
// {
//     char *east_p;
//     char *west_p;
//     char *north_p;
//     char *south_p;
// } t_direction_p;

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




// Init funcs
int init_mlx(t_game *game, char **map);
int get_map_height(char **map);
int get_map_width(char **map);
int init_mlx(t_game *game, char **map);

// Events funcs
int key_press(int keycode, t_game *game);
int close_window(t_game *game);
char **duplicate_map(char **map);
void move_player(t_game *game);

int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);


void move_forward(t_game *game);
void move_backward(t_game *game);
void strafe_left(t_game *game);
void strafe_right(t_game *game);

void my_mlx_pixel_put(t_game *game, int x, int y, int color);

// game funcs
void render_map(t_game *game, char **map);

// Raycasting funcs
void cast_ray(t_game *game, float ray_angle, int ray_id);
void draw_rect(t_game *game, int x, int y, int width, int height, int color);
void draw_line(t_game *game, int x1, int y1, int x2, int y2, int color);
float normalize_angle(float angle);
bool is_wall(t_game *game, float x, float y);
float distance_between_points(float x1, float y1, float x2, float y2);
void cast_rays(t_game *game);

//projection funcs
void generate_3d_projection(t_game *game);

// minimap funcs
void render_minimap(t_game *game);

// Game funcs
int game_loop(t_game *game);
void render_map(t_game *game, char **map);
int start_gaming(t_game game, char **map);






#define SUCCESS 0
#define ERROR 1
#define SYERROR 2

// ** this will be used to store the paths to the direction textures..
typedef struct s_direction{
    char *east_p;
    char *west_p;
    char *north_p;
    char *south_p;
    int n_ofs;
    int n_ofn;
    int n_ofe;
    int n_ofw;
    int n_off;
    int n_ofc;
} t_direction_p;

typedef enum e_types{
    NO,
    SO,
    WE,
    EA,
    F,
    C
} t_types;

typedef enum place{
    START,
    M_ERROR,
    T_ERROR,
    AFTER
} t_place;

typedef struct usedonce{
    char *temp;
    int endl;
    int map_y;
    int end;
    int line;
    char **map;
    size_t i;
} t_norm1;

typedef struct s_colors{
    char *c;
    char *f;
    char **splitted_c;
    char **splitted_f;
    int *f_c;
    int *c_c;
} t_colors;

typedef struct usedonce2{
    int i;
    int k;
    int after_map;
    t_colors *colors;
    t_direction_p *direction;
    
} t_norm2;


typedef struct s_data
{
    void *east;
    void *west;
    void *north;
    void *south;
    void *mlx_ptr;
    void *win_ptr;
    char **map;
    char **cub_file;
    size_t file_size;
    size_t map_x;
    size_t map_y;
    size_t player_x;
    t_colors *colors;
    size_t player_y;
    t_direction_p *direction_paths;
}   t_data;

int char_in(char *s);
bool not_in_str(char c, char *s);
bool not_in_str(char c, char *s);
bool is_white_space(char c);
bool file_copying(t_data *data, int len, char **av);
bool get_allocation_size(int *y, char **av);
bool file_read(t_data *data, char **av);
bool file_process(t_data *data, char **av);
bool is_first_in(char c, char *s);
bool texture_loading(t_data *data);
int    ft_strcmp(char *s1, char *s2);
char *strend_trim(char *str, size_t nbytes);
char *strafter_type(char *str);
void set_tozero(t_data *data);
int map_validation(char **map, int map_size, t_data *data);
char *skip_spaces(char *s);
int	ft_strncmpp(const char *s1, const char *s2, size_t count);
bool map_checker(char **map);
bool color_filling(t_data *data);
bool valid_colorstr(char *s);
size_t count_char(char *s, char c);
bool valid_file_name(char *s);
bool is_void(char **map, size_t x, size_t y, size_t map_max);
bool str_validation(int line, bool end, t_data *data);
bool map_checker(char **map);
void fireforce(t_data *data, t_place place);
void free2d(char **s, size_t size);
void free_texture(t_data *data);
bool outer_resources(t_data *data);
bool outer_error_check(t_data *data);
bool texture_valid(char *s1, char *s2);
void print_stff(t_data *data);
char **remove_newlines(t_data *data);




#endif