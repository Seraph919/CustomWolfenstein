/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 01:37:47 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/05 10:41:18 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	int		i;
	char	*lastseen;

	i = 0;
	lastseen = NULL;
	while (str[i])
	{
		if (str[i] == (char)chr)
		{
			lastseen = (char *)&str[i];
		}
		i++;
	}
	if ((char)chr == '\0')
		return ((char *)&str[i]);
	return (lastseen);
}
/*
int main()
{
	printf("%p\n",strrchr("https://www.find_the_Error.com", 't'));
	printf("%p\n",ft_strrchr("https://www.find_the_Error.com", 't'));
}
*/
	// if (!str)
	// 	return (NULL);