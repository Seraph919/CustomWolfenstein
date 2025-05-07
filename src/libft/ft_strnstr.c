/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:05:16 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/09 13:36:28 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *nd, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!hay && nd && n == 0)
		return (NULL);
	if (*nd == '\0' || !nd)
		return ((char *)hay);
	while (((char *)hay)[i] && i < n)
	{
		j = 0;
		while (((char *)nd)[j] == ((char *)hay)[i + j] && i + j < n)
		{
			if (((char *)nd)[j + 1] == '\0')
			{
				return ((char *)hay + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
// int main()
// {
// 	char *s = NULL;
// 	char *d = "wach";
// 	int len  = 0;
// 	printf("%s\n", strnstr(s, d, len));
// }