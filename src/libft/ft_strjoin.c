/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:14:35 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/06 12:27:09 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*returned;

	if (!s1 || !s2)
		return (NULL);              // for better results, if one is null, you return  the other one, and include this condition
	i = -1;				    // to hundle the other case :     if (!s1 && !s2) return NULL;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	returned = malloc(sizeof(char) * len1 + len2 + 1);
	if (!returned)
		return (NULL);
	while (s1[++i])
		returned[i] = s1[i];
	i = 0;
	while (s2[i])
	{
		returned[len1 + i] = s2[i];
		i++;
	}
	returned[len1 + i] = '\0';
	return (returned);
}
