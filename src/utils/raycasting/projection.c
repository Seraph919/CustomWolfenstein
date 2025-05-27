#include "../../../headers/cub3d.h"

int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
    char *pixel;
    if (!texture || !texture->addr)
        return 0;
    if (tex_x < 0)
        tex_x = 0;
    if (tex_y < 0)
        tex_y = 0;
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;
    if (tex_y >= texture->height)
        tex_y = texture->height - 1;
    pixel = texture->addr + (tex_y * texture->size_line + tex_x * (texture->bpp / 8));
    return *(unsigned int *)pixel;
}

void draw_textured_wall(t_game *game, int x, int wall_top, int wall_height, int ray_id)
{
    t_ray *ray;
    int face;
    t_texture *texture;
    float wall_x;
    int tex_x;
    int d;
    int tex_y;
    int color;

    ray = &game->rays[ray_id];
    face= ray->wall_face;
    if (face < 0 || face > 3 || !game->textures[face].addr)
        return;
    texture = &game->textures[face]; // ! here are the sides..
    if (ray->hit_vertical)
        wall_x = ray->wall_hit_y;
    else
        wall_x = ray->wall_hit_x;
    wall_x /= TILE_SIZE;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (float)texture->width);

    if ((!ray->hit_vertical && ray->ray_angle > PI) || (ray->hit_vertical && (ray->ray_angle < PI/2 || ray->ray_angle > 3*PI/2)))
        tex_x = texture->width - tex_x - 1;

    for (int y = wall_top; y < wall_top + wall_height; y++)
    {
        d = y * 256 - game->window_height * 128 + wall_height * 128;
        tex_y = ((d * texture->height) / wall_height) / 256;
        color = get_texture_color(texture, tex_x, tex_y);
        my_mlx_pixel_put(game, x, y, color);
    }
}

void generate_3d_projection(t_game *game)
{
    float y_distance;
    int wall_top;
    float wall_height;
    int i = 0;
    draw_rect(game, 0, 0, game->window_width, game->window_height / 2, game->data->colors->c_color);
    draw_rect(game, 0, game->window_height / 2, game->window_width, game->window_height / 2, game->data->colors->f_color);
    for (i = 0; i < NUM_RAYS; i++)
    {
        y_distance = game->rays[i].distance * cos(game->rays[i].ray_angle - game->player->angle);
        wall_height = (TILE_SIZE / y_distance) * ((game->window_width / 2) / tan(game->player->fov / 2));
        game->rays[i].wall_height = wall_height;
        wall_top = (game->window_height / 2) - (wall_height / 2);
        if (wall_top < 0) wall_top = 0;
        draw_textured_wall(game, i, wall_top, wall_height, i);
    }
}

void draw_sprite(t_game *game, t_texture *sprite, int dest_x, int dest_y, int dest_w, int dest_h)
{
    for (int y = 0; y < dest_h; y++)
    {
        int tex_y = (y * sprite->height) / dest_h;
        for (int x = 0; x < dest_w; x++)
        {
            int tex_x = (x * sprite->width) / dest_w;
            int color = get_texture_color(sprite, tex_x, tex_y);
            if ((color & 0xFF000000) != 0xFF000000)
                my_mlx_pixel_put(game, dest_x + x, dest_y + y, color);
        }
    }
}
