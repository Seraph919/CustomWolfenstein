/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 02:08:18 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/09 08:20:50 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	integerlen(int number)
{
	int	i;

	i = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number *= -1;
		i++;
	}
	while (number)
	{
		number /= 10;
		i++;
	}
	return (i);
}

static void	arrfill(long i, int index, long n, char *str)
{
	if (n == 0)
	{
		str[index++] = '0';
		str[index] = '\0';
		return ;
	}
	while (i * 10 <= n)
		i *= 10;
	while (i)
	{
		str[index] = (n / i) + '0';
		n %= i;
		i /= 10;
		index++;
	}
	str[index] = '\0';
}

char	*ft_itoa(int nb)
{
	long	i;
	char	*str;
	int		index;
	long	n;

	i = 1;
	index = 0;
	n = nb;
	str = (char *)malloc(sizeof(char) * (integerlen(n) + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[index++] = '-';
	}
	arrfill(i, index, n, str);
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(0));
}
*/
