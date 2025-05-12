/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 20:14:47 by asoudani         ###   ########.fr       */
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


typedef struct s_data{
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
bool str_validation(char **map, int line, bool end, t_data *data);
bool map_checker(char **map);
void fireforce(t_data *data, t_place place);
void free2d(char **s, size_t size);
void free_texture(t_data *data);
bool outer_resources(t_data *data);
bool outer_error_check(t_data *data);
bool texture_valid(char *s1, char *s2);
void print_stff(t_data *data);

#endif