/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:01 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 17:42:38 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

bool valid_file_name(char *s)
{
    int end;
    if (!s)
        return (false);
    end = ft_strlen(s) - 1;
    if (s[end--] == 'b' && s[end--] == 'u'
        && s[end--] == 'c' && s[end--] == '.' 
        && (s[end--] != '/' && end != -1))
        return (true);
    return (false);
}

bool is_white_space(char c)
{
    if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f')
        return (true);
    return (false);
}

bool not_in_str(char c, char *s)
{
    if (!s)
        return (true);
    while (*s)
    {
        if (c == *s)
            return (false);
        s++;
    }
    return (true);
}

// ** this will be used to pick the paths and colors from the .cub file..

bool is_first_in(char c, char *s)
{
    if (!s)
        return (false);
    while (*s && is_white_space(*s))
        s++;
    if (*s && *s == c)
        return (true);
    return (false);
}

int char_in(char *s)
{
    if (!s)
        return (SYERROR);
    while (*s)
    {
        while (*s && is_white_space(*s))
            s++;
        if (*s && !is_white_space(*s))
        {
            return (1);
        }
        if (*s == '\0')
            break;
        s++;
    }
    return (0);
}

char *strafter_type(char *str)
{
    if (!str)
        return (NULL);
    while (!is_white_space(*str))
        str++;
    if (*str == '\0')
        return (NULL);
    while (is_white_space(*str))
        str++;
    if (*str == '\0')
        return (NULL);
    else
        return (strend_trim(str, 1));
}

int	ft_strncmpp(const char *s1, const char *s2, size_t count)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < count)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < count)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char *strend_trim(char *str, size_t nbytes)
{
    if (!str)
        return (NULL);
    size_t end;
    char *returned;
    size_t i;

    i = -1;
    end = strlen(str);
    returned = alloc((sizeof(char) * end - nbytes) + 1, ALLOC);
    if (!returned)
        return (NULL);
    while (++i  < end - nbytes)
        returned[i] = str[i];
    returned[i] = '\0';
    // free(str); // do it after removing GC..
    return (returned);
}

bool above_checker(char **map, int y)
{
    int x;

    x = -1;
    if (!map || !map[y] )
        return (ERROR);
    while (map[y][++x])
    {
        if (is_white_space(map[y][x]) 
            && map[y - 1][x] && map[y - 1][x] == '0')
            return (ERROR);
    }
    if (map[y][x] == '\0' && map[y - 1][x] && map[y - 1][x] == '0')
        return (ERROR);
    return (SUCCESS);
}

bool is_void(char **map, size_t x, size_t y, size_t map_max)
{
    if ((map[y - 1][x] && is_white_space(map[y - 1][x]))
            || (y + 1 < map_max - 1 && map[y + 1] && map[y + 1][x] && is_white_space(map[y + 1][x])) 
            || ( x != 0 && is_white_space(map[y][x - 1])) 
            || (map[y][x + 1] && is_white_space(map[y][x + 1]))
            || !map[y][x + 1])
            return (true);
    if (y + 1 == map_max - 1)
    {
        if (above_checker(map, y + 1))
            return (true);
    }
    return (false);
}
bool check_srnds(char **map, int x, int y, size_t map_max)
{
    if (!map || !*map)
        return (false);
    if (y > 0 && map[y][x] && map[y][x] == '0')
    {
        if (is_void(map, x, y, map_max))
            return (false);
    }
    return (true);
}

bool checkbefore(char *s, int end) // check the trailing spc
{
    if (!s)
        return (false);
    while (end > 0)
    {
        if (s[end] == '1')
            return (true);
        if (!is_white_space(s[end]))
            break;
        end--;
    }
    return (false);
}
// this will check if i have a char that is not in the list
bool map_checker(char **map)
{
    int i;
    int k;
    bool player_found;


    i = -1;
    player_found = false;
    while (map[++i])
    {
        k = -1;
        while (map[i][++k])
        {
            if(not_in_str(map[i][k], "NWES10 \n"))
                return (ERROR);
            if (not_in_str(map[i][k], "NWES") == false && player_found)
                return (ERROR);
            if (not_in_str(map[i][k], "NWES") == false)
                player_found = true;
        }
    }
    return (false);
}

bool str_validation(char **map, int line, bool end, t_data *data)
{
    if (!map || !map[line])
        return (false);
    size_t i;
    char *temp;
    int   endl;

    i = 0;
    if (map_checker(map))
        return (false);
    while (map[line][i])
    {
        if ((line == 0 || end) && not_in_str(map[line][i], "1 \n"))
            return (false);
        
        else if (check_srnds(map, i, line, data->map_y) == false)
            return (false);
        
        if (i == 0 && map[line][i] == ' ')
        {
            temp = skip_spaces(map[line]);
            endl = ft_strlen(temp) - 1;
            if (!temp || *temp != '1' || temp[endl - 1] != '1')
            {
                if (checkbefore(temp, endl - 1))
                    ;
                else
                    return (false);
            }
        }
        
        if (i == ft_strlen(map[line]) - 2 && map[line][i] != '1')
        {
            if (checkbefore(temp, endl - 1))
                ;
            else
                return (false);
        }
        i++;
    }
    return (true);
}


int map_validation(char **map, int map_size, t_data *data)
{
    if (!map || !*map)
        return (ERROR);
    int i;

    i = 0;
    while (i < map_size)
    {
        if (i == 0)
        {
            if (str_validation(map, 0, false, data) == false)
                return (ERROR);
        }
        else if(str_validation(map, i, i == map_size - 1, data) == false) // bool
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

char *skip_spaces(char *s)
{
    if (!s)
        return (NULL);
    while (is_white_space(*s))
        s++;
    if (*s == '\0')
        return (NULL);
    return (s);
}