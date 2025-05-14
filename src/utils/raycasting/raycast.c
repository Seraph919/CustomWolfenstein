#include "../../../headers/cub3d.h"

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

float normalize_angle(float angle)
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

float distance_between_points(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
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