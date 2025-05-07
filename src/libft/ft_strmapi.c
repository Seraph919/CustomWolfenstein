/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:00:03 by asoudani          #+#    #+#             */
/*   Updated: 2024/10/28 10:00:03 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*returned;
	int		len;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	returned = malloc(sizeof(char) * (len + 1));
	if (!returned)
		return (NULL);
	while (i < len)
	{
		returned[i] = f(i, s[i]);
		i++;
	}
	returned[i] = '\0';
	return (returned);
}
