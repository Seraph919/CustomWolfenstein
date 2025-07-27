/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/27 10:40:14 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <pthread.h>
#include <signal.h>
#include "data_structures.h"
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
#define DEBUGGING 0

#define VALIDCHARS "DNWES10 \n"

#define DRAW_RAYS 0

#define MAP_W 15
#define MAP_H 11

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WALL_COLOR 0x424242
#define EMPTY_COLOR 0xebebeb
#define PLAYER_COLOR 0x003aba
#define PLAYER 0xFF0000

#define TILE_SIZE 5
#define PLAYER_SIZE 3

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define FOV 60
#define NUM_RAYS WINDOW_WIDTH
#define WALL_STRIP_WIDTH 1


// #define U_KEY   85
// #define L_KEY   76
#define R_KEY   82

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

#define PLAYER_SPEED 0.30

#define ROT_SPEED 0.05


// mouse buttons

#define LEFT_CLICK 1
#define RIGHT_CLICK 2


// Init funcs
int init_mlx(t_game *game);
int get_map_height(char **map);
int get_map_width(char **map);
int init_mlx(t_game *game);

// Events funcs
int key_press(int keycode, t_game *game);
int close_window(t_game *game);
char **duplicate_map(char **map);
void move_player(t_game *game);

int mouse_move(int x, int y, t_game *game);

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
void draw_rect(t_game *game, t_rect rect);
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

// Texture loading functions
// int load_texture(t_game *game, t_texture *texture, char *path);
// void destroy_textures(t_game *game);

// Texture drawing functions
int get_texture_color(t_texture *texture, int tex_x, int tex_y);
void draw_textured_wall(t_game *game, int x, int wall_top, int wall_height, int ray_id, bool isdoor);

bool is_door(t_game *game, float x, float y);

int char_in(char *s);
bool not_in_str(char c, char *s);
bool is_white_space(char c);
bool file_copying(t_data *data, int len, char **av);
bool get_allocation_size(int *y, char **av);
bool file_read(t_data *data, char **av);
bool file_process(t_data *data, char **av);
bool is_first_in(char c, char *s);
bool texture_loading(t_data *data);
int    ft_strcmp(char *s1, char *s2);
char *strend_trim(char *str, size_t nbytes, int start_index);
int index_after_spaces(char *s);
char *strafter_type(char *str);
void set_tozero(t_data *data);
int map_validation(char **map, int map_size, t_data *data);
char *skip_spaces(char *s);
int	ft_strncmpp(const char *s1, const char *s2, size_t count);
bool map_checker(char **map, t_data *data);
bool color_filling(t_data *data);
bool valid_colorstr(char *s);
size_t count_char(char *s, char c);
int rgb_to_int(int r, int g, int b);
bool valid_file_name(char *s);
bool is_void(char **map, size_t x, size_t y, size_t map_max);
bool str_validation(int line, bool end, t_data *data);
void fireforce(t_data *data, t_place place);
void free2d(char **s, size_t size);
void free_texture(t_data *data);
bool outer_resources(t_data *data);
bool outer_error_check(t_data *data);
bool texture_valid(char *s1, char *s2);
bool above_checker(char **map, int y);
bool is_void(char **map, size_t x, size_t y, size_t map_max);
void print_stff(t_data *data);
char **newlinecut(t_data *data);
int count_chars(int c, t_data *data, bool assign);
bool is_open(t_game *game, bool unlock_door);

void draw_sprite(t_game *game, t_texture *sprite, int dest_x, int dest_y, int dest_w, int dest_h);
void draw_weapon(t_game *game, int index);
void exit_error(t_data *data, char *s);
t_ray_dir init_ray_direction(float ray_angle);
t_intercept_steps calc_h_inter_and_steps(t_game *game, float angle, t_ray_dir dir);
t_wall_hit find_horizontal_intersection(t_game *game, t_ray_input input);
t_wall_hit find_vertical_intersection(t_game *game, t_ray_input input);
void set_ray_hit_result(t_ray *ray, t_ray_hit_data input, float h_distance, float v_distance);
void store_ray_properties(t_game *game, t_ray_hit_data input);
void init_cast_ray_data(t_game *game, t_cast_ray_data *data, float ray_angle, int ray_id);

// init stuff
bool initialize_game_data(t_data *data, t_game *game);
void init_player_vars(t_game *game);
void set_player_stuff(int x, int y, t_game *game, float angle);
void get_player_angle(t_game *game, int y);
void set_player_direction(t_game *game);
int init_vars(t_game *game);
void init_sound_vars(t_game *game);
void set_mouse_and_textures(t_game *game);
int load_direction_textures(t_game *game);
int texture_data(t_game *game);
int	is_valid_move(t_game *game, float new_x, float new_y);

// gaming moves and sounds
pid_t play_sound(t_game *game);
pid_t play_opening_sound(void);
int	allocations(t_data *data);
void	t_norm2_init(t_data *data, t_norm2 *norm);
bool	handle_texture_direction(t_norm2 *n, char *line);
bool	handle_texture_we_ea(t_norm2 *n, char *line);
bool	outer_resources(t_data *data);
bool	element_allocation(t_data *data, t_norm2 *n);
void	handle_map_element(t_data *data, t_norm2 *n, char *line);
bool	handle_colors(t_norm2 *n, char *line);
bool	conditions(t_norm1 *norm);
bool	checkbefore(char *s, int end);
bool	check_srnds(t_data *data, int x, int y, size_t map_max);
bool	not_surr(char **map, int x, int y);
int	check_next_index(char **map, int x, int y);
int	count_chars(int c, t_data *data, bool assign);
void	assigner(t_data *data, int x, int y, int counter);
int	index_after_spaces(char *s);
void	draw_opening_scene(t_game *game);

#endif