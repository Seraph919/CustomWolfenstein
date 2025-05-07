/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:23:18 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/08 20:06:19 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ftt_memcpy(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	while (i < size)
	{
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t numBytes)
{
	if (numBytes == 0)
		return (dest);
	if (src >= dest)
	{
		ftt_memcpy(dest, src, numBytes);
		return (dest);
	}
	while (numBytes--)
		*((unsigned char *)dest + numBytes) = *((unsigned char *)src
				+ numBytes);
	return (dest);
}
