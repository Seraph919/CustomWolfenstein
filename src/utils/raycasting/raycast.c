#include "../../../headers/cub3d.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= game->window_width || y < 0 || y >= game->window_height)
        return;
    dst = game->addr + (y * game->size_line + x * (game->bpp / 8));
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
    int sx, sy;
    int err;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;
    if (y1 < y2)
        sy = 1;
    else
        sy = -1;
    err = dx - dy;

    while (1)
    {
        if (x1 == x2 && y1 == y2) break;
        my_mlx_pixel_put(game, x1, y1, color);
        
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

float normalize_angle(float angle)
{
    angle = fmodf(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return angle;
}

bool is_door(t_game *game, float x, float y)
{
    if (x < 0 || x >= game->map_w * TILE_SIZE || y < 0 || y >= game->map_h * TILE_SIZE)
        return true;

    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    if (game->map[map_y][map_x] == 'D')
        return true;
    else
        return false;
}

bool is_wall(t_game *game, float x, float y)
{
    if (x < 0 || x >= game->map_w * TILE_SIZE || y < 0 || y >= game->map_h * TILE_SIZE)
        return true;

    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    if (game->map[map_y][map_x] == '1')
        return true;
    else
        return false;
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

t_ray_dir init_ray_direction(float ray_angle)
{
    t_ray_dir dir;
    if (ray_angle > 0 && ray_angle < PI)
        dir.facing_down = true;
    else
        dir.facing_down = false;
    dir.facing_up = !dir.facing_down;
    if (ray_angle < HALF_PI || ray_angle > 1.5 * PI)
        dir.facing_right = true;
    else
        dir.facing_right = false;
    dir.facing_left = !dir.facing_right;
    return dir;
}

t_wall_hit find_horizontal_intersection(t_game *game, float ray_angle, t_ray_dir dir)
{
    t_wall_hit hit = {0, 0, false};
    float y_intercept;
    float x_intercept;
    float y_step;
    float x_step;
    float next_h_x;
    float next_h_y;

    y_intercept = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
    if (dir.facing_down)
        y_intercept += TILE_SIZE;
    x_intercept = game->player->x + (y_intercept - game->player->y) / tan(ray_angle);

    y_step = TILE_SIZE;
    if (dir.facing_up)
        y_step *= -1;
    x_step = TILE_SIZE / tan(ray_angle);
    if (dir.facing_left && x_step > 0)
        x_step *= -1;
    if (dir.facing_right && x_step < 0)
        x_step *= -1;

    next_h_x = x_intercept;
    next_h_y = y_intercept;

    while (next_h_x >= 0 && next_h_x < game->map_w * TILE_SIZE &&
           next_h_y >= 0 && next_h_y < game->map_h * TILE_SIZE)
    {
        float check_x = next_h_x;
        float check_y;
        if (dir.facing_up)
            check_y = next_h_y - 1;
        else
            check_y = next_h_y;
        if (is_wall(game, check_x, check_y))
        {
            hit.x = next_h_x;
            hit.y = next_h_y;
            hit.found = true;
            return hit;
        }
        next_h_x += x_step;
        next_h_y += y_step;
    }
    return hit;
}

t_wall_hit find_vertical_intersection(t_game *game, float ray_angle, t_ray_dir dir)
{
    t_wall_hit hit = {0, 0, false};
    float x_intercept;
    float y_intercept;
    float x_step;
    float y_step;
    float next_v_x;
    float next_v_y;

    x_intercept = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
    if (dir.facing_right)
        x_intercept += TILE_SIZE;
    y_intercept = game->player->y + (x_intercept - game->player->x) * tan(ray_angle);

    x_step = TILE_SIZE;
    if (dir.facing_left)
        x_step *= -1;
    y_step = TILE_SIZE * tan(ray_angle);
    if (dir.facing_up && y_step > 0)
        y_step *= -1;
    if (dir.facing_down && y_step < 0)
        y_step *= -1;

    next_v_x = x_intercept;
    next_v_y = y_intercept;

    while (next_v_x >= 0 && next_v_x < game->map_w * TILE_SIZE &&
           next_v_y >= 0 && next_v_y < game->map_h * TILE_SIZE)
    {
        float check_x;
        float check_y = next_v_y;
        if (dir.facing_left)
            check_x = next_v_x - 1;
        else
            check_x = next_v_x;
        if (is_wall(game, check_x, check_y))
        {
            hit.x = next_v_x;
            hit.y = next_v_y;
            hit.found = true;
            return hit;
        }
        next_v_x += x_step;
        next_v_y += y_step;
    }
    return hit;
}

void store_ray_properties(t_game *game, int ray_id, float ray_angle,
                        t_wall_hit h_hit, t_wall_hit v_hit, t_ray_dir dir)
{
    float h_distance;
    float v_distance;

    if (h_hit.found)
        h_distance = distance_between_points(game->player->x, game->player->y, h_hit.x, h_hit.y);
    else
        h_distance = FLT_MAX;

    if (v_hit.found)
        v_distance = distance_between_points(game->player->x, game->player->y, v_hit.x, v_hit.y);
    else
        v_distance = FLT_MAX;

    if (v_distance < h_distance)
    {
        game->rays[ray_id].wall_hit_x = v_hit.x;
        game->rays[ray_id].wall_hit_y = v_hit.y;
        game->rays[ray_id].distance = v_distance;
        game->rays[ray_id].hit_vertical = true;
        if (dir.facing_left)
            game->rays[ray_id].wall_face = 3;
        else
            game->rays[ray_id].wall_face = 2;
    }
    else
    {
        game->rays[ray_id].wall_hit_x = h_hit.x;
        game->rays[ray_id].wall_hit_y = h_hit.y;
        game->rays[ray_id].distance = h_distance;
        game->rays[ray_id].hit_vertical = false;
        if (dir.facing_up)
            game->rays[ray_id].wall_face = 0;
        else
            game->rays[ray_id].wall_face = 1;
    }
    game->rays[ray_id].ray_angle = ray_angle;
    // printf("h = %f v = %f\n  ", h_distance, v_distance);
}

void cast_ray(t_game *game, float ray_angle, int ray_id)
{
    ray_angle = normalize_angle(ray_angle);
    t_ray_dir dir = init_ray_direction(ray_angle);
    t_wall_hit h_hit = find_horizontal_intersection(game, ray_angle, dir);
    t_wall_hit v_hit = find_vertical_intersection(game, ray_angle, dir);
    store_ray_properties(game, ray_id, ray_angle, h_hit, v_hit, dir);
}