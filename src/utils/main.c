/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/07 20:59:18 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"


void set_tozero(t_data *data)
{
    data->direction_paths->n_ofe = 0;
    data->direction_paths->n_ofw = 0;
    data->direction_paths->n_ofs = 0;
    data->direction_paths->n_ofn = 0;
    data->direction_paths->n_ofc = 0;
    data->direction_paths->n_off = 0;
    data->south = NULL;
    data->north = NULL;
    data->west = NULL;
    data->east = NULL;
}

bool texture_loading(t_data *data)
{
    t_direction_p *dir;
    int width;
    int height;
    int     i;

    dir = data->direction_paths;
    i = 0;
    data->north = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->north_p), &width, &height);
    if (!data->north)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->west = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->west_p), &width, &height);
    if (!data->west)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->east = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->east_p), &width, &height);
    if (!data->east)
        return (printf("Error\nTexture Error\n"), ERROR);
    data->south = mlx_xpm_file_to_image(data->mlx_ptr, strafter_type(dir->south_p), &width, &height);
    if (!data->south)
        return (printf("Error\nTexture Error\n"), ERROR);
    return (SUCCESS);
}

bool outer_error_check(t_data *data)
{
    t_direction_p *dir;
    
    dir = data->direction_paths;
    if (dir ->n_ofs > 1 || dir ->n_ofn > 1 || dir ->n_ofw > 1 
        || dir ->n_ofe > 1 || dir ->n_ofc > 1 || dir ->n_off > 1)
        return (ERROR);
    if (color_filling(data) ==  ERROR)
        return (ERROR);
    
    return (SUCCESS);
}

void print_stff(t_data *data)
{
    printf("north :%s", data->direction_paths->north_p);
    printf("west :%s", data->direction_paths->west_p);
    printf("east :%s", data->direction_paths->east_p);
    printf("south :%s\n", data->direction_paths->south_p);
    printf("F :%s", data->colors->f);
    printf("c :%s\n", data->colors->c);

    for (size_t i = 0; i < data->map_y; i++)
        printf("%s", data->map[i]);
    printf("\n\n");
    printf("the player is in(%zu,%zu)\n", data->player_x, data->player_y);
}

bool color_filling(t_data *data)
{
    int i;
    t_colors *colors;

    colors = data->colors;
    colors->c = skip_spaces(colors->c);
    colors->f = skip_spaces(colors->f);
    if (!valid_colorstr(colors->c + 1) || !valid_colorstr(colors->f + 1))
        return (ERROR);
    if (count_char(colors->c,',') != 2 || count_char(colors->f,',') != 2)
        return (ERROR);
    colors->splitted_c = ft_split(skip_spaces(colors->c + 1), ',');
    colors->splitted_f = ft_split(skip_spaces(colors->f + 1), ',');
    if (!colors->splitted_c || !colors->splitted_f)
        return (ERROR);
    colors->f_c = alloc(sizeof(int) * 4, ALLOC);
    colors->c_c = alloc(sizeof(int) * 4, ALLOC);
    if (!colors->f_c || !colors->c_c )
    return (ERROR);
    i = -1;
    while (++i < 3)
    {
        colors->f_c[i] = ft_atoi(colors->splitted_f[i]);
        colors->c_c[i] = ft_atoi(colors->splitted_c[i]);
        if (colors->f_c[i] == -1 || colors->c_c[i] == -1)
        {
            free2d(colors->splitted_c, 5);
            free2d(colors->splitted_f, 5);
            return (ERROR);
        }// free stuff here..
    }
    free2d(colors->splitted_c, 5);
    free2d(colors->splitted_f, 5);
    return (SUCCESS);
}

// bool file_copying(t_game *game, int len)
// {
//     int fd;
//     int y;
//     char *line;
    
//     y = 0;
//     fd = open("src/map/file.cub", O_RDONLY);
//     if (fd < 0 || len == 0)
//         return (printfd(2, "Error in file opening\n"),ERROR);
//     game->cub_file = alloc((sizeof(char *) * len) + 1, ALLOC);
//     if (!game->cub_file)
//         return (ERROR);
//     while ((line = get_next_line(fd)))
//     {
//         game->cub_file[y++] = line;
//     }
//     game->cub_file[y - 1] = NULL;
//     game->map_y = y;
//     close(fd);
//     return (SUCCESS);
// }

// bool get_allocation_size(int *y)
// {
//     char *line;
//     int fd;
    
//     *y = 0;
//     fd = open("src/map/file.cub", O_RDONLY);
//     if (fd < 0)
//         return (printfd(2, "Error in file opening\n"),ERROR);
//     while ((line = get_next_line(fd)))
//     {
//         *y += 1;
//         free(line);
//     }
//     close(fd);
//     if (*y == 0)
//         return (ERROR);
//     return (SUCCESS);
// }
// bool file_read(t_game *game)
// {
//     int y;

//     y = 0;
//     if (get_allocation_size(&y) || file_copying(game, y))
//         return (ERROR);
//     return (SUCCESS);
// }

// bool outer_resources(t_game *game)
// {
//     int i;
//     int k;
//     t_direction_p *direction;
    
//     game->direction_paths = alloc(sizeof (t_direction_p), ALLOC);
//     if (!game->direction_paths)
//         return (ERROR);
//     direction = game->direction_paths;
//     game->map = alloc (sizeof(char *) * (game->map_y - 6) + 1, ALLOC);
//     if (!game->map)
//         return (ERROR); // free on error
//     i = -1;
//     k = 0;
//     while (game->cub_file[++i])
//     {
//         if (char_in(game->cub_file[i]) && char_in(game->cub_file[i]) != SYERROR)
//         {
//             if (game->cub_file[i] && TILE_SIZE_first_in('N', game->cub_file[i])) // NO
//                 direction->north_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('S', game->cub_file[i])) // SO
//                 direction->south_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('W', game->cub_file[i])) // WE
//                 direction->west_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('E', game->cub_file[i])) // EA
//                 direction->east_p  = ft_strdup(game->cub_file[i]); // free the pre-exTILE_SIZEted one..
//             else if (game->cub_file[i] && TILE_SIZE_first_in('F', game->cub_file[i])) // F
//                 game->f_color = ft_strdup(game->cub_file[i]);
//             else if (game->cub_file[i] && TILE_SIZE_first_in('C', game->cub_file[i])) // C 
//                 game->c_color = ft_strdup(game->cub_file[i]);
//             else
//                 game->map[k++] = ft_strdup(game->cub_file[i]);
//         }
//     }
//     return (SUCCESS);
// }

// bool file_related(t_game *game)
// {
//     if (file_read(game))
//     return (printfd(2, "Found an Error in .cub Processing\n"),ERROR);
//     if (outer_resources(game)) // need to free in case of errors
//     return (printfd(2, "Found an Error in The .cub File\n"), ERROR); // also here
//     printf("north :%s", game->direction_paths->north_p);
//     printf("west :%s", game->direction_paths->west_p);
//     printf("east :%s", game->direction_paths->east_p);
//     printf("south :%s\n", game->direction_paths->south_p);
//     printf("F :%s", game->f_color);
//     printf("c :%s\n", game->c_color);

//     for (int i = 0; game->map[i]; i++)
//         printf("%s", game->map[i]);
//     return (SUCCESS);
// }

// void fireforce(void)
// {
//     alloc(0, FREE);
// }

// int main(int ac, char **av)
// {
//     if (ac != 1)
//         return (1);
//     t_game game;
//     t_game *game;
//     (void)av;
//     game.mlx_ptr = mlx_init();
//     if (file_related(&game))
//         return (ERROR);
//     start_game(&game);
//     finTILE_SIZEh_game(&game);
//     fireforce();
//     return (SUCCESS);
// }

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= game->window_width || y < 0 || y >= game->window_height)
        return;

    char *dst = game->addr + (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_rect(t_game *game, int x, int y, int width, int height, int color)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            my_mlx_pixel_put(game, x + j, y + i, color);
}

void draw_line(t_game *game, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        my_mlx_pixel_put(game, x1, y1, color);
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
}

static inline float normalize_angle(float angle)
{
    angle = fmodf(angle, TWO_PI);
    return (angle < 0) ? angle + TWO_PI : angle;
}

bool is_wall(t_game *game, float x, float y)
{
    if (x < 0 || x >= game->map_w * TILE_SIZE || y < 0 || y >= game->map_h * TILE_SIZE)
        return true;

    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    return game->map[map_y][map_x] == '1';
}

static inline float distance_between_points(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}

void cast_ray(t_game *game, float ray_angle, int ray_id)
{
    ray_angle = normalize_angle(ray_angle);
    
    bool ray_facing_down = ray_angle > 0 && ray_angle < PI;
    bool ray_facing_up = !ray_facing_down;
    bool ray_facing_right = ray_angle < HALF_PI || ray_angle > 1.5 * PI;
    bool ray_facing_left = !ray_facing_right;
    
    float h_wall_hit_x = 0;
    float h_wall_hit_y = 0;
    bool found_h_wall_hit = false;
    
    float y_intercept = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
    y_intercept += ray_facing_down ? TILE_SIZE : 0;
    
    float x_intercept = game->player->x + (y_intercept - game->player->y) / tan(ray_angle);
    
    float y_step = TILE_SIZE;
    y_step *= ray_facing_up ? -1 : 1;
    
    float x_step = TILE_SIZE / tan(ray_angle);
    x_step *= (ray_facing_left && x_step > 0) ? -1 : 1;
    x_step *= (ray_facing_right && x_step < 0) ? -1 : 1;
    
    float next_h_x = x_intercept;
    float next_h_y = y_intercept;
    
    while (next_h_x >= 0 && next_h_x < game->map_w * TILE_SIZE && 
           next_h_y >= 0 && next_h_y < game->map_h * TILE_SIZE)
    {
        float check_x = next_h_x;
        float check_y = next_h_y + (ray_facing_up ? -1 : 0);
        
        if (is_wall(game, check_x, check_y))
        {
            h_wall_hit_x = next_h_x;
            h_wall_hit_y = next_h_y;
            found_h_wall_hit = true;
            break;
        }
        next_h_x += x_step;
        next_h_y += y_step;
    }
    
    float v_wall_hit_x = 0;
    float v_wall_hit_y = 0;
    bool found_v_wall_hit = false;
    
    x_intercept = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
    x_intercept += ray_facing_right ? TILE_SIZE : 0;
    
    y_intercept = game->player->y + (x_intercept - game->player->x) * tan(ray_angle);
    
    x_step = TILE_SIZE;
    x_step *= ray_facing_left ? -1 : 1;
    
    y_step = TILE_SIZE * tan(ray_angle);
    y_step *= (ray_facing_up && y_step > 0) ? -1 : 1;
    y_step *= (ray_facing_down && y_step < 0) ? -1 : 1;
    
    float next_v_x = x_intercept;
    float next_v_y = y_intercept;
    
    while (next_v_x >= 0 && next_v_x < game->map_w * TILE_SIZE && 
           next_v_y >= 0 && next_v_y < game->map_h * TILE_SIZE)
    {
        float check_x = next_v_x + (ray_facing_left ? -1 : 0);
        float check_y = next_v_y;
        
        if (is_wall(game, check_x, check_y))
        {
            v_wall_hit_x = next_v_x;
            v_wall_hit_y = next_v_y;
            found_v_wall_hit = true;
            break;
        }
        next_v_x += x_step;
        next_v_y += y_step;
    }
    
    float h_distance = found_h_wall_hit ? 
        distance_between_points(game->player->x, game->player->y, h_wall_hit_x, h_wall_hit_y) : FLT_MAX;
    float v_distance = found_v_wall_hit ? 
        distance_between_points(game->player->x, game->player->y, v_wall_hit_x, v_wall_hit_y) : FLT_MAX;
    
    if (v_distance < h_distance)
    {
        game->rays[ray_id].wall_hit_x = v_wall_hit_x;
        game->rays[ray_id].wall_hit_y = v_wall_hit_y;
        game->rays[ray_id].distance = v_distance;
        game->rays[ray_id].hit_vertical = true;
        game->rays[ray_id].wall_face = ray_facing_left ? 3 : 2;
    }
    else
    {
        game->rays[ray_id].wall_hit_x = h_wall_hit_x;
        game->rays[ray_id].wall_hit_y = h_wall_hit_y;
        game->rays[ray_id].distance = h_distance;
        game->rays[ray_id].hit_vertical = false;
        game->rays[ray_id].wall_face = ray_facing_up ? 0 : 1;
    }
    
    game->rays[ray_id].ray_angle = ray_angle;
}
void cast_rays(t_game *game)
{
    float ray_angle = game->player->angle - (game->player->fov / 2);
    
    for (int i = 0; i < NUM_RAYS; i++)
    {
        cast_ray(game, ray_angle, i);
        ray_angle += game->player->fov / NUM_RAYS;
    }
}

void generate_3d_projection(t_game *game)
{
    draw_rect(game, 0, 0, game->window_width, game->window_height / 2, 0x87CEEB);
    draw_rect(game, 0, game->window_height / 2, game->window_width, game->window_height / 2, 0x8B4513);
    
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float perpendicular_distance = game->rays[i].distance * cos(game->rays[i].ray_angle - game->player->angle);
        
        float wall_height = (TILE_SIZE / perpendicular_distance) * ((game->window_width / 2) / tan(game->player->fov / 2));
        
        game->rays[i].wall_height = wall_height;
        
        int wall_top = (game->window_height / 2) - (wall_height / 2);
        if (wall_top < 0)
            wall_top = 0;
            
        int wall_bottom = (game->window_height / 2) + (wall_height / 2);
        if (wall_bottom > game->window_height)
            wall_bottom = game->window_height;
        
        int wall_color;
        if (game->rays[i].hit_vertical)
        {
            wall_color = game->rays[i].wall_face == 2 ? 0x8A2BE2 : 0x4B0082;
        }
        else
        {
            wall_color = game->rays[i].wall_face == 0 ? 0x00BFFF : 0x1E90FF;
        }
        
        draw_rect(game, i * WALL_STRIP_WIDTH, wall_top, WALL_STRIP_WIDTH, wall_bottom - wall_top, wall_color);
    }
}

void render_minimap(t_game *game)
{
    int minimap_width = game->map_w * TILE_SIZE;
    int minimap_height = game->map_h * TILE_SIZE;
    
    (void)minimap_width;
    (void)minimap_height;

    for (int y = 0; y < game->map_h; y++)
    {
        for (int x = 0; x < game->map_w; x++)
        {
            int color = game->map[y][x] == '1' ? WALL_COLOR : EMPTY_COLOR;
            draw_rect(game, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
        }
    }
    
    draw_rect(game, 
              game->player->x - PLAYER_SIZE / 2, 
              game->player->y - PLAYER_SIZE / 2, 
              PLAYER_SIZE, PLAYER_SIZE, 
              PLAYER_COLOR);
    
    float dx = cos(game->player->angle) * 20;
    float dy = sin(game->player->angle) * 20;
    draw_line(game, 
              game->player->x, 
              game->player->y, 
              game->player->x + dx, 
              game->player->y + dy, 
              0xFF0000);
    
    for (int i = 0; i < NUM_RAYS; i += 50)
    {
        draw_line(game, 
                  game->player->x, 
                  game->player->y, 
                  game->rays[i].wall_hit_x, 
                  game->rays[i].wall_hit_y, 
                  0xFF0000);
    }
}

void move_player(t_game *game)
{
    float move_step = game->player->move_speed;
    
    float new_x = game->player->x;
    float new_y = game->player->y;
    
    if (W_KEY & (1 << 0))
    {
        new_x += cos(game->player->angle) * move_step;
        new_y += sin(game->player->angle) * move_step;
    }
    
    if (S_KEY & (1 << 1))
    {
        new_x -= cos(game->player->angle) * move_step;
        new_y -= sin(game->player->angle) * move_step;
    }
    
    if (A_KEY & (1 << 2))
    {
        new_x += cos(game->player->angle - HALF_PI) * move_step;
        new_y += sin(game->player->angle - HALF_PI) * move_step;
    }
    
    if (D_KEY & (1 << 3))
    {
        new_x += cos(game->player->angle + HALF_PI) * move_step;
        new_y += sin(game->player->angle + HALF_PI) * move_step;
    }
    
    if (LEFT_ARROW & (1 << 4))
    {
        game->player->angle -= game->player->rotation_speed;
    }
    
    if (RIGHT_ARROW & (1 << 5))
    {
        game->player->angle += game->player->rotation_speed;
    }
    
    game->player->angle = normalize_angle(game->player->angle);
    
    if (!is_wall(game, new_x, game->player->y))
        game->player->x = new_x;
    
    if (!is_wall(game, game->player->x, new_y))
        game->player->y = new_y;
}

int init_mlx(t_game *game, char **map)
{
    game->map = map;
    game->window_width = WINDOW_WIDTH;
    game->window_height = WINDOW_HEIGHT;
    
    game->player->fov = FOV * DEG_TO_RAD;
    game->player->move_speed = MOVE_SPEED;
    game->player->rotation_speed = ROTATION_SPEED;
    
    game->mlx = mlx_init();
    if (!game->mlx)
        return 0;
    
    game->window = mlx_new_window(game->mlx, game->window_width, game->window_height, "cub3D");
    if (!game->window)
        return 0;
    
    game->img = mlx_new_image(game->mlx, game->window_width, game->window_height);
    if (!game->img)
        return 0;
    
    game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    
    game->rays = malloc(sizeof(t_ray) * NUM_RAYS);
    if (!game->rays)
        return 0;

    game->map = duplicate_map(map);

    game->player->dir_x = 1.0;
    game->player->dir_y = 0.0;
    game->player->plane_x = 0.66;  // FOV: 66°
    game->player->plane_y = 0.0;

    for (int y = 0; y < game->map_h; y++)
    {
        for (int x = 0; x < game->map_w; x++)
        {
            if (map[y][x] == 'N')
            {
                game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
                game->player->angle = PI / 2;
                game->map[y][x] = '0';
            }
        }
    }
    
    game->is_game_running = true;
    
    return 1;
}

// Get map dimensions
// int get_map_height(char **map)
// {
//     int height = 0;
//     while (map[height])
//         height++;
//     return height;
// }

// int get_map_width(char **map)
// {
//     int width = 0;
//     int max_width = 0;
    
//     for (int i = 0; map[i]; i++)
//     {
//         width = 0;
//         while (map[i][width])
//             width++;
//         if (width > max_width)
//             max_width = width;
//     }
    
//     return max_width;
// }

int key_press(int keycode, t_game *game)
{
    if (keycode == W_KEY)
        game->keys_held |= (1 << 0);
    else if (keycode == S_KEY)
        game->keys_held |= (1 << 1);
    else if (keycode == A_KEY)
        game->keys_held |= (1 << 2);
    else if (keycode == D_KEY)
        game->keys_held |= (1 << 3);
    else if (keycode == LEFT_ARROW)
        game->keys_held |= (1 << 4);
    else if (keycode == RIGHT_ARROW)
        game->keys_held |= (1 << 5);
    else if (keycode == XK_Escape)
        close_window(game);

    return 0;
}

int key_release(int keycode, t_game *game)
{
    if (keycode == W_KEY)
        game->keys_held &= ~(1 << 0);
    else if (keycode == S_KEY)
        game->keys_held &= ~(1 << 1);
    else if (keycode == A_KEY)
        game->keys_held &= ~(1 << 2);
    else if (keycode == D_KEY)
        game->keys_held &= ~(1 << 3);
    else if (keycode == LEFT_ARROW)
        game->keys_held &= ~(1 << 4);
    else if (keycode == RIGHT_ARROW)
        game->keys_held &= ~(1 << 5); 

    return 0;
}



// int close_window(t_game *game)
// {
//     game->is_game_running = false;
    
//     // Free resources
//     if (game->rays)
//         free(game->rays);
    
//     if (game->img)
//         mlx_destroy_image(game->mlx, game->img);
    
//     if (game->window)
//         mlx_destroy_window(game->mlx, game->window);
    
//     exit(0);
    
//     return 0;
// }

int game_loop(t_game *game)
{
    if (!game->is_game_running)
        return 1;

    mlx_clear_window(game->mlx, game->window);
    
    if (game->keys_held & (1 << 0))
        move_forward(game);
    if (game->keys_held & (1 << 1))
        move_backward(game);
    if (game->keys_held & (1 << 2))
        strafe_left(game);
    if (game->keys_held & (1 << 3))
        strafe_right(game);

    if (game->keys_held & (1 << 4))
        game->player->angle -= 0.05;
    if (game->keys_held & (1 << 5))
        game->player->angle += 0.05;

    cast_rays(game);
    generate_3d_projection(game);
    render_minimap(game);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
    
    return 0;
}

// Render the map
void render_map(t_game *game, char **map)
{
    (void)map;

    game->key_state = 0;
}

int start_gaming(t_game game, char **map)
{
    game.player = malloc(sizeof(t_player));
    if (!game.player)
    {
        printf("Memory allocation for player failed\n");
        return (1);
    }
    
    game.map_h = get_map_height(map);
    game.map_w = get_map_width(map);
    
    if (!init_mlx(&game, map))
    {
        free(game.player);
        return (1);
    }
    
    render_map(&game, map);
    
    mlx_hook(game.window, 2, 1L << 0, key_press, &game);
    mlx_hook(game.window, 3, 1L << 1, key_release, &game);
    mlx_hook(game.window, 17, 0, close_window, &game);
    
    mlx_loop_hook(game.mlx, game_loop, &game);
    
    mlx_loop(game.mlx);
    
    free(game.player);

    return (0);
}



int main(int ac, char **av)
{

    if (ac != 2)
        return (1);
    t_data data;
    data.mlx_ptr = mlx_init();
    if (file_process(&data, av))
        return (ERROR);
    t_game game;



    game.map = NULL;
    
    start_gaming(game, data.map);
    
    return 0;
}
