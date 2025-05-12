/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:08:40 by asoudani          #+#    #+#             */
/*   Updated: 2025/05/12 15:36:06 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*returned;
	size_t	slen;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (len == 0 || start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	returned = (char *)malloc(sizeof(char) * (len + 1));
	if (!returned)
		return (NULL);
	while (i < len)
	{
		returned[i] = s[start + i];
		i++;
	}
	returned[i] = '\0';
	return (returned);
}
