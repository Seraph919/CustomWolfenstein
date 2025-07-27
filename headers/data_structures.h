#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "cub3d.h"
#include <stdbool.h>
#include <stdio.h>
typedef struct s_data t_data;
typedef struct s_game t_game;

typedef struct s_rect
{
    int x;
    int y;
    int width;
    int height;
    int color;
} t_rect;

typedef struct s_wall_atr
{
	int		wall_top;
	float	wall_height;
} t_wall_atr;

// for each door
typedef struct doorpos{
    int x;
    int y;
    bool is_open;
}   t_doorpos;

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
    bool is_door;
} t_ray;

typedef struct sound{
    bool fire;
    bool opening_song;
    bool game_vibes;
} t_sounds;

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

typedef struct s_strip_args
{
	t_game		*game;
	int			x;
	int			wall_top;
	int			wall_height;
	t_texture	*texture;
	int			tex_x;
}	t_strip_args;

typedef struct s_wall_args
{
	t_game	*game;
	int		x;
	int		wall_top;
	int		wall_height;
	int		ray_id;
	bool	isdoor;
}	t_wall_args;

typedef struct s_sprite_args
{
	t_game		*game;
	t_texture	*sprite;
	int			dest_x;
	int			dest_y;
	int			dest_w;
	int			dest_h;
}	t_sprite_args;

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
    char player_char;
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
    t_texture *textures;
    t_texture *pistol_texture;
    bool is_game_running;
    int key_state;
    int keys_held;
    int last_mouse_x;
    int last_mouse_y;
    t_data *data;
    bool animation_running;
    int current_anim_index;
    bool syle_animation_running;
    int current_style_index;
    bool first_time;
    t_sounds sounds;
    pid_t vibesound_id;
    pid_t opsound_id;
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

typedef enum direction{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    AIM,
    OPEN,
    DOOR
} t_texture_direction;

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
    char player_char;
    t_doorpos *doors;
    int ndoors;
    t_game *game;
}   t_data;


typedef struct s_intercept_steps
{
    float x_intercept;
    float y_intercept;
    float x_step;
    float y_step;
} t_intercept_steps;

typedef struct s_ray_input
{
    float angle;
    t_ray_dir dir;
    bool *found_door;
} t_ray_input;

typedef struct s_ray_trace
{
    t_game *game;
    t_ray_input input;
} t_ray_trace;

typedef struct s_trace_params
{
    t_ray_dir dir;
    bool *found_door;
} t_trace_params;

typedef struct s_ray_hit_data
{
    float ray_angle;
    int ray_id;
    t_ray_dir dir;
    t_wall_hit h_hit;
    t_wall_hit v_hit;
    bool for_door;
} t_ray_hit_data;


typedef struct s_cast_ray_data
{
    float ray_angle;
    int ray_id;
    t_ray_dir dir;
    bool found_door_h;
    bool found_door_v;
    t_wall_hit h_hit;
    t_wall_hit v_hit;
    bool final_hit_is_door;
    float h_distance;
    float v_distance;
} t_cast_ray_data;

#endif
