#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "cub3d.h"
#include <stdbool.h>
#include <stdio.h>
typedef struct s_data t_data;

typedef struct s_ray
{
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    bool hit_vertical;
    // int hit_horizontal; // 1 if the ray hit a horizontal wall, 0 otherwise
    int wall_face;   // 0=north, 1=south, 2=east, 3=west
    int wall_height;
} t_ray;

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

typedef struct s_wall_hit
{
    float x;
    float y;
    bool found;
}   t_wall_hit;

typedef struct s_ray_dir
{
    bool facing_down;
    bool facing_up;
    bool facing_right;
    bool facing_left;
}   t_ray_dir;

typedef struct s_game
{
    void **imgs;
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
    t_texture pistol_texture; // <-- Add this line
    bool is_game_running;
    int key_state;
    int keys_held;
    int last_mouse_x;
    int last_mouse_y;
    t_data *data;
} t_game;



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
    int c_color;
    int f_color;
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

#endif
