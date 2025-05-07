/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:24:28 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/09 14:29:44 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*ptr;

	if (size == 0 || nitems == 0)
		return (malloc(0));
	if (size != 0 && (nitems > SIZE_MAX / size))
		return (NULL);
	ptr = (char *)malloc(nitems * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nitems * size);
	return (ptr);
}
/*
int	main(void)
{
	char	*s;

 	s = ft_calloc(0, 0);
 	printf("%s\n", s);

	
}
*/
