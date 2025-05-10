/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:01 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/10 19:03:59 by asoudani         ###   ########.fr       */
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
            if (not_in_str(*s, "NOSWEAFC10"))
                return (SYERROR);
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
