/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:09:00 by asoudani          #+#    #+#             */
/*   Updated: 2024/10/28 09:54:12 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(*(char *)s++) = 0;
		i++;
	}
}
/*
int	main(void)
{
	int		tab[3] = {1,2,3};
	char	s[] = "wach";

	printf("%d  %d  %d\n", tab[0], tab[1], tab[2]);
	ft_bzero(tab, 3 * sizeof(int));
	printf("%d  %d  %d\n", tab[0], tab[1], tab[2]);
	printf("%s\n", s);
	ft_bzero(s, 4);
	printf("%s\n", s);
}
*/
