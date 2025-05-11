/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:01 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/11 19:52:31 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
    returned = malloc((sizeof(char) * end - nbytes) + 1);
    if (!returned)
        return (NULL);
    while (++i  < end - nbytes)
        returned[i] = str[i];
    returned[i] = '\0';
    // free(str); // do it after removing GC..
    return (returned);
}

bool check_srnds(char **map, int x, int y)
{
    if (!map || !*map)
        return (false);
    if (y > 0 && map[y][x] && map[y][x] == '0')
    {
        if (map[y - 1][x] == ' ' || (map[y + 1][x] && map[y + 1][x] == ' ') 
            || ( x != 0 && map[y][x - 1] == ' ') || (map[y][x + 1] && map[y][x + 1] == ' '))
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


    i = -1;
    while (map[++i])
    {
        k = -1;
        while (map[i][++k])
        {
            if(not_in_str(map[i][k], "NWES10 \n"))
                return (printfd(2,"ERROR\nChar '%c' is not expected in the map\n", map[i][k]), ERROR);
        }
    }
    return (false);
}

bool str_validation(char **map, int line, bool end)
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
        
        else if (check_srnds(map, i, line) == false)
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

int map_validation(char **map, int map_size)
{
    if (!map || !*map)
        return (ERROR);
    int i;

    i = 0;
    while (i < map_size)
    {
        if (i == 0)
        {
            if (str_validation(map, 0, false) == false)
                return (ERROR);
        }
        else if(str_validation(map, i, i == map_size - 1) == false) // bool
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