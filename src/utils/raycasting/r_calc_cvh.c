#include "../../../headers/cub3d.h"

static t_wall_hit trace_h_ray(t_game *game, t_trace_params params, t_intercept_steps steps)
{
    t_wall_hit hit;
    float x;
    float y;
    float check_x;
    float check_y;

    x = steps.x_intercept;
    y = steps.y_intercept;
    hit = (t_wall_hit){0, 0, false};
    while (x >= 0 && x < game->map_w * TILE_SIZE &&
           y >= 0 && y < game->map_h * TILE_SIZE)
    {
        check_x = x;
        check_y = params.dir.facing_up ? y - 1 : y;
        if (is_door(game, check_x, check_y))
        {
            *params.found_door = true;
            return ((t_wall_hit){x, y, true});
        }
        if (is_wall(game, check_x, check_y))
            return ((t_wall_hit){x, y, true});
        x += steps.x_step;
        y += steps.y_step;
    }
    return (hit);
}


t_wall_hit find_horizontal_intersection(t_game *game, t_ray_input input)
{
    t_intercept_steps steps;
    t_trace_params params;

    steps = calc_h_inter_and_steps(game, input.angle, input.dir);
    params = (t_trace_params){.dir = input.dir,.found_door = input.found_door};
    return (trace_h_ray(game, params, steps));
}




static t_intercept_steps calc_v_inter_and_steps(t_game *game, float angle, t_ray_dir dir)
{
    t_intercept_steps steps;

    steps.x_intercept = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
    if (dir.facing_right)
        steps.x_intercept += TILE_SIZE;
    steps.y_intercept = game->player->y + 
        (steps.x_intercept - game->player->x) * tan(angle);
    steps.x_step = TILE_SIZE * (dir.facing_left ? -1 : 1);
    steps.y_step = TILE_SIZE * tan(angle);
    if (dir.facing_up && steps.y_step > 0)
        steps.y_step *= -1;
    if (dir.facing_down && steps.y_step < 0)
        steps.y_step *= -1;
    return (steps);
}

static t_wall_hit trace_v_ray(t_game *game, t_trace_params params, t_intercept_steps steps)
{
    t_wall_hit hit;
    float y;
    float x;
    float check_x;
    float check_y;

    hit = (t_wall_hit){0, 0, false};
    x = steps.x_intercept;
    y = steps.y_intercept;
    while (x >= 0 && x < game->map_w * TILE_SIZE &&
           y >= 0 && y < game->map_h * TILE_SIZE)
    {
        check_x = params.dir.facing_left ? x - 1 : x;
        check_y = y;
        if (is_door(game, check_x, check_y))
        {
            *params.found_door = true;
            return ((t_wall_hit){x, y, true});
        }
        if (is_wall(game, check_x, check_y))
            return ((t_wall_hit){x, y, true});
        x += steps.x_step;
        y += steps.y_step;
    }
    return (hit);
}

t_wall_hit find_vertical_intersection(t_game *game, t_ray_input input)
{
    t_intercept_steps steps;
    t_trace_params params;

    steps = calc_v_inter_and_steps(game, input.angle, input.dir);
    params = (t_trace_params){.dir = input.dir, .found_door = input.found_door};
    return (trace_v_ray(game, params, steps));
}