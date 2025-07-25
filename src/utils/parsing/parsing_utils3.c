/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:47:47 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/25 09:19:31 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

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
        return (strend_trim(str, 1, 0));
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

char *strend_trim(char *str, size_t nbytes, int start_index)
{
    if (!str)
        return (NULL);
    size_t end;
    char *returned;
    size_t i;
    int k = 0;

    i = start_index--;
    end = strlen(str);
    returned = alloc((sizeof(char) * end - nbytes) + 1, ALLOC);
    if (!returned)
        return (exit_error(NULL, "fatal malloc error\n"), NULL);
    while (++i  < end - nbytes)
        returned[k++] = str[i];
    returned[k] = '\0';
    return (returned);
}

bool file_process(t_data *data, char **av)
{
    if (file_read(data, av) || outer_resources(data) 
    || outer_error_check(data))
        return (printfd(2, "ERROR\nFound an Error in .cub Processing\n"),
         fireforce(data, M_ERROR), ERROR);
    if (map_validation(data->map, data->map_y, data) == ERROR)
        return (printfd(2, "ERROR\nFound an Error in map\n"),
         fireforce(data, M_ERROR), ERROR);
    // print_stff(data);
    if (texture_loading(data))
        return (fireforce(data, AFTER), ERROR);
    optimizer(data);
    return (SUCCESS);
}

bool valid_colorstr(char *s)
{
    if (!s)
        return (false);
    s = skip_spaces(s);
    if (!s)
        return (false);
    while (*s)
    {
        if (!ft_isdigit(*s) && *s != ',' && *s != '\n')
            return (false);
        if (*s == ',')
        {
            s++;
            if (*s == '\0' || !ft_isdigit(*s))
                return (false);
        }
        s++;
    }
    return (true);
}

int index_after_spaces(char *s)
{
    int i = 0;
    if (!s)
        return (0);
    while (is_white_space(s[i]))
        i++;
    if (!s[i])
        return (0);
    while (!is_white_space(s[i]))
        i++;
    return (i);
}