#include "../../../headers/cub3d.h"

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