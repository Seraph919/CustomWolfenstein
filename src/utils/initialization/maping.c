#include "../../../headers/cub3d.h"

int get_map_height(char **map)
{
    int height;
    height = 0;
    if (!map || !*map)
        return 0;
    while (map[height])
        height++;
    return height;
}

int get_map_width(char **map)
{
    int width;
    width = 0;
    if (!map || !*map)
        return 0;
    while (map[0][width])
        width++;
    return width;
}

void free_partial_map(char **new_map, int count)
{
    int j;
    j = 0;
    while (j < count)
    {
        free(new_map[j]);
        j++;
    }
    free(new_map);
}

char **duplicate_map(char **map)
{
    int height;
    int i;
    char **new_map;

    i = 0;
    height = get_map_height(map);
    new_map = malloc(sizeof(char *) * (height + 1));
    if (!new_map)
        return NULL;
    while (i < height)
    {
        new_map[i] = ft_strdup(map[i]);
        if (!new_map[i])
        {
            free_partial_map(new_map, i);
            return NULL;
        }
        i++;
    }
    new_map[height] = NULL;
    return new_map;
}