/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/10 22:50:15 by asoudani         ###   ########.fr       */
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

typedef struct s_data{
    void *east;
    void *west;
    void *north;
    void *south;
    void *mlx_ptr;
    void *win_ptr;
    char **map;
    char **cub_file;
    size_t map_x;
    size_t map_y;
    size_t player_x;
    char *f_color;
    char *c_color;
    size_t player_y;
    t_direction_p *direction_paths;
}   t_data;

int char_in(char *s);
bool not_in_str(char c, char *s);
bool not_in_str(char c, char *s);
bool is_white_space(char c);
bool file_copying(t_data *data, int len);
bool get_allocation_size(int *y);
bool file_read(t_data *data);
bool file_related(t_data *data);
bool is_first_in(char c, char *s);
bool texture_loading(t_data *data);
int    ft_strcmp(char *s1, char *s2);
char *strend_trim(char *str, size_t nbytes);
char *strafter_type(char *str);
void set_tozero(t_data *data);
int map_validation(char **map, int map_size);
char *skip_spaces(char *s);

#endif