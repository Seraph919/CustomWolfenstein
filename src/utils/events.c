#include "../../headers/cub3d.h"

int mouse_move(int x, int y, t_game *game)
{
    int center_x = game->window_width / 2;
    int center_y = game->window_height / 2;
    int mouse_delta_x;
    float sensitivity;

    mouse_delta_x = x - center_x;
    sensitivity = 0.002f;
    game->player->angle += mouse_delta_x * sensitivity;
    mlx_mouse_move(game->mlx, game->window, center_x, center_y);
    game->last_mouse_x = center_x;
    game->last_mouse_y = center_y;

    (void) y;
    return (0);
}


int is_valid_move(t_game *game, float new_x, float new_y)
{
    int i = 0;
    float buffer = 1.0f; // distance from the wall bel pixels
    float corners[4][2] = {
        {new_x - buffer, new_y - buffer},
        {new_x + buffer, new_y - buffer},
        {new_x - buffer, new_y + buffer},
        {new_x + buffer, new_y + buffer}
    };
    while (i < 4)
    {
        int cx = (int)(corners[i][0] / TILE_SIZE);
        int cy = (int)(corners[i][1] / TILE_SIZE);

        if (cx < 0 || cx >= game->map_w || cy < 0 || cy >= game->map_h)
        {
            printf("Invalid move: out of bounds!\n");
            return 0;
        }
        if (game->map[cy][cx] == '1')
        {
            printf("Invalid move: too close to wall!\n");
            return 0;
        }
        if ((game->map[cy][cx] == 'D' && is_open(cx, cy, game, false) == false))
        {
            printf("check x = %d y = %d\n", cx, cy);
            return printf("Unlock the door first!\n"), 0;
        }
        i++;
    }
    // for (int i = 0; game->map[i]; i++)
    // {
    //     printf("'%s'\n", game->map[i]);
    // }
    // static int j = 1;
    // printf("Move-> %d\n", j++);
    return 1;
}


void move_forward(t_game *game)
{
    float move_x = cos(game->player->angle) * PLAYER_SPEED;
    float move_y = sin(game->player->angle) * PLAYER_SPEED;
    float new_x = game->player->x + move_x;
    float new_y = game->player->y + move_y;

    if (is_valid_move(game, new_x, new_y))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    }
    else if (is_valid_move(game, game->player->x + move_x, game->player->y))
    {
        game->player->x += move_x;
    }
    else if (is_valid_move(game, game->player->x, game->player->y + move_y))
    {
        game->player->y += move_y;
    }
    else
    {
        if (game->keys_held & (1 << 2))
            strafe_left(game);
        else if (game->keys_held & (1 << 3))
            strafe_right(game);
    }
}


void move_backward(t_game *game)
{
    float move_x = cos(game->player->angle) * PLAYER_SPEED;
    float move_y = sin(game->player->angle) * PLAYER_SPEED;

    float new_x = game->player->x - move_x;
    float new_y = game->player->y - move_y;

    if (is_valid_move(game, (int)(new_x), (int)(new_y)))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    }
    else if (is_valid_move(game, game->player->x + move_x, game->player->y))
    {
        game->player->y += move_y;
    }
    else if (is_valid_move(game, game->player->x, game->player->y + move_y))
    {
        game->player->x += move_x;
    }
    else
    {
        if (game->keys_held & (1 << 2))
            strafe_left(game);
        else if (game->keys_held & (1 << 3))
            strafe_right(game);
    }
}

void strafe_left(t_game *game)
{
    float move_x = cos(game->player->angle - PI / 2) * PLAYER_SPEED;
    float move_y = sin(game->player->angle - PI / 2) * PLAYER_SPEED;
    float new_x = game->player->x + move_x;
    float new_y = game->player->y + move_y;
    
    if (is_valid_move(game, new_x, new_y))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    } else {
        printf("Invalid move: strafe left failed.\n");
    }
}

void strafe_right(t_game *game)
{
    float move_x = cos(game->player->angle + PI / 2) * PLAYER_SPEED;
    float move_y = sin(game->player->angle + PI / 2) * PLAYER_SPEED;
    float new_x = game->player->x + move_x;
    float new_y = game->player->y + move_y;
    
    if (is_valid_move(game, new_x, new_y))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    } else {
        printf("Invalid move: strafe right failed.\n");
    }
}

void update_player_position(t_game *game, int new_x, int new_y)
{
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
        
    if (new_x < 0 || new_x >= game->map_w || new_y < 0 || new_y >= game->map_h)
    {
        printf("Invalid move: out of bounds\n");
        return;
    }
    if (game->map[(int)game->player->y][(int)game->player->x] != 'D'  // ! make sure that this is usefuLL
        && game->map[(int)game->player->y][(int)game->player->x] != 'O')
        game->map[(int)game->player->y][(int)game->player->x] = '0';
    game->map[new_y][new_x] = game->data->player_char;
    game->player->x = new_x;
    game->player->y = new_y;
    render_map(game, game->map);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}

int close_window(t_game *game)
{

    int i = 0;
    while (i <= DOOR)
    {
        mlx_destroy_image(game->mlx, game->textures[i].img);
        i++;
    }

    // mlx_destroy_image(game->mlx, game->textures[NORTH].img);
    // mlx_destroy_image(game->mlx, game->textures[SOUTH].img);
    // mlx_destroy_image(game->mlx, game->textures[EAST].img);
    // mlx_destroy_image(game->mlx, game->textures[WEST].img);
    // mlx_destroy_image(game->mlx, game->textures[AIM].img);
    // mlx_destroy_image(game->mlx, game->textures[OPEN].img);
    // mlx_destroy_image(game->mlx, game->textures[DOOR].img);


    i = 0;
    while (i < 7)
    {
        mlx_destroy_image(game->mlx, game->pistol_texture[i].img);
        i++;
    }
    // mlx_destroy_image(game->mlx, game->pistol_texture[0].img);
    // mlx_destroy_image(game->mlx, game->pistol_texture[1].img);
    // mlx_destroy_image(game->mlx, game->pistol_texture[2].img);
    // mlx_destroy_image(game->mlx, game->pistol_texture[3].img);
    // mlx_destroy_image(game->mlx, game->pistol_texture[4].img);
    // mlx_destroy_image(game->mlx, game->pistol_texture[5].img);
    // mlx_destroy_image(game->mlx, game->pistol_texture[6].img);


    mlx_destroy_window(game->mlx, game->window);
    mlx_destroy_image(game->mlx, game->img);
    mlx_destroy_display(game->mlx);
    free(game->map);
    free(game->player);
    
    // free(game->pistol_texture[0].img);
    // free(game->pistol_texture[1].img);
    // free(game->pistol_texture[2].img);
    // free(game->pistol_texture[3].img);
    // free(game->pistol_texture[4].img);
    // free(game->pistol_texture[5].img);
    // free(game->pistol_texture[6].img);

    // int i = 0;
    // while (i < 7)
    // {
    //     if (game->pistol_texture[i].addr)
    //     {
    //         free(game->pistol_texture[i].addr);
    //     }
    //     i++;
    // }


    // free(game->textures[NORTH].img);
    // free(game->textures[SOUTH].img);
    // free(game->textures[EAST].img);
    // free(game->textures[WEST].img);
    // free(game->textures[AIM].img);
    // free(game->textures[OPEN].img);
    // free(game->textures[DOOR].img);

//     for (int i = 0; i <= DOOR; i++)
// {
//     if (game->textures[i].img)
//         mlx_destroy_image(game->mlx, game->textures[i].img);
// }


    free(game->mlx);
    free(game->data->mlx_ptr);
    alloc(0, FREE);
    // printf("PID 1 = %d PID 2 = %d\n", game->vibesound_id, game->opsound_id);
    if (game->vibesound_id > 0)
        kill(game->vibesound_id, SIGKILL);
    if (game->opsound_id > 0)
        kill(game->opsound_id, SIGKILL);
    system("pkill -9 paplay");
    exit(0);
}