/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:47:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/17 18:15:29 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../gc/garbage.h"

char	*ft_strdup(const char *str1)
{
	int		i;
	char	*allocated;

	i = 0;
	allocated = alloc(sizeof(char) * ft_strlen(str1) + 1, ALLOC);
	if (!allocated)
		return (NULL);
	while (str1[i])
	{
		allocated[i] = str1[i];
		i++;
	}
	allocated[i] = '\0';
	return (allocated);
}
/*
int	main(void)
{
	char	*s;
	char	*d;

	s = "maroc";
	d = ft_strdup(s);
	printf("%s\n", d);
}
*/