#include "../../../headers/cub3d.h"

int key_press(int keycode, t_game *game)
{
    if (keycode == W_KEY)
        game->keys_held |= (1 << 0);
    if (keycode == XK_space)
    {
        game->animation_running = true;
        game->sounds.fire = true;
    }
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
    else if (keycode == XK_E || keycode == XK_e)
        is_open(game->player->x , game->player->y, game, true); // * lock/unlock door
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
    else if (keycode == XK_p || keycode == XK_P)
    {
        for (int i = 0; i < NUM_RAYS; i++)
        {
            printf("ray[%d] isdoor == %d\n", i, game->rays[i].is_door);
        }
    }
    return 0;
}