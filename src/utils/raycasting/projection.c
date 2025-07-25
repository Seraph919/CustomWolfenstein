#include "../../../headers/cub3d.h"

int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
    char *pixel;

    if (!texture || !texture->addr)
        return (0);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_y < 0)
        tex_y = 0;
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;
    if (tex_y >= texture->height)
        tex_y = texture->height - 1;
    pixel = texture->addr + (tex_y * texture->size_line + tex_x * (texture->bpp / 8));
    return (*(unsigned int *)pixel);
}

void tex_x_assign(int *tex_x, bool hit_vertical, float ray_angle, int width)
{
    bool condition1;
    bool condition2;

    condition1 = (!hit_vertical && ray_angle > PI);
    condition2 = (hit_vertical && (ray_angle < PI / 2 || ray_angle > 3 * PI / 2));
    if (condition1 || condition2)
        *tex_x = width - *tex_x - 1;
}

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
    t_texture	*texture;

    texture = &game->textures[DOOR];
    if (ray->is_door == false)
        texture = &game->textures[ray->wall_face];
    return (texture);
}

float	calculate_wall_x(t_ray *ray)
{
    float	wall_x;

    if (ray->hit_vertical)
        wall_x = ray->wall_hit_y;
    else
        wall_x = ray->wall_hit_x;
    wall_x /= TILE_SIZE;
    wall_x -= floor(wall_x);
    return (wall_x);
}

void	draw_wall_column(t_game *game, t_texture *texture, int tex_x, int x, int wall_top, int wall_height)
{
    int	y;
    int	d;
    int	tex_y;
    int	color;

    y = wall_top;
    while (y < wall_top + wall_height)
    {
        d = y * 256 - game->window_height * 128 + wall_height * 128;
        tex_y = ((d * texture->height) / wall_height) / 256;
        color = get_texture_color(texture, tex_x, tex_y);
        my_mlx_pixel_put(game, x, y, color);
        y++;
    }
}

void draw_textured_wall(t_game *game, int x, int wall_top, int wall_height, int ray_id)
{
    t_ray		*ray;
    t_texture	*texture;
    float		wall_x;
    int			tex_x;

    ray = &game->rays[ray_id];
    if (!game->textures[ray->wall_face].addr)
        return;
    texture = get_wall_texture(game, ray);
    wall_x = calculate_wall_x(ray);
    tex_x = (int)(wall_x * (float)texture->width);
    tex_x_assign(&tex_x, ray->hit_vertical, ray->ray_angle, texture->width);
    draw_wall_column(game, texture, tex_x, x, wall_top, wall_height);
}

void	draw_background(t_game *game)
{
    int	half_height;

    half_height = game->window_height / 2;
    draw_rect(game, 0, 0, game->window_width, half_height, game->data->colors->c_color);
    draw_rect(game, 0, half_height, game->window_width, half_height, game->data->colors->f_color);
}

void	process_ray(t_game *game, int i)
{
    float	y_distance;
    int		wall_top;
    float	wall_height;

    y_distance = game->rays[i].distance * cos(game->rays[i].ray_angle - game->player->angle);
    wall_height = (TILE_SIZE / y_distance) * ((game->window_width / 2) / tan(game->player->fov / 2));
    game->rays[i].wall_height = wall_height;
    wall_top = (game->window_height / 2) - (wall_height / 2);
    if (wall_top < 0)
        wall_top = 0;
    draw_textured_wall(game, i, wall_top, wall_height, i);
}

void generate_3d_projection(t_game *game)
{
    int	i;

    draw_background(game);
    i = 0;
    while (i < NUM_RAYS)
    {
        process_ray(game, i);
        i++;
    }
}

void	draw_sprite_row(t_game *game, t_texture *sprite, int dest_x, int dest_y, int dest_w, int y, int tex_y)
{
    int	x;
    int	tex_x;
    int	color;

    x = 0;
    while (x < dest_w)
    {
        tex_x = (x * sprite->width) / dest_w;
        color = get_texture_color(sprite, tex_x, tex_y);
        if ((color & 0xFF000000) != 0xFF000000)
            my_mlx_pixel_put(game, dest_x + x, dest_y + y, color);
        x++;
    }
}

void draw_sprite(t_game *game, t_texture *sprite, int dest_x, int dest_y, int dest_w, int dest_h)
{
    int	y;
    int	tex_y;

    y = 0;
    while (y < dest_h)
    {
        tex_y = (y * sprite->height) / dest_h;
        draw_sprite_row(game, sprite, dest_x, dest_y, dest_w, y, tex_y);
        y++;
    }
}
