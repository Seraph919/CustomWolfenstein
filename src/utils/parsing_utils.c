/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:01 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/07 20:18:53 by asoudani         ###   ########.fr       */
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