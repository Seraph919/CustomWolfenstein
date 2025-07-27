/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 05:48:35 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/27 11:13:32 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((const unsigned char *)str1)[i]
			!= ((const unsigned char *)str2)[i])
		{
			return (((const unsigned char *)str1)[i]
				- ((const unsigned char *)str2)[i]);
		}
		i++;
	}
	return (0);
}
