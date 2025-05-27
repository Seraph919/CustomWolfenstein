/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 03:50:52 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/09 09:53:37 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	casee;
	int	number;

	i = 0;
	casee = 1;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			casee *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i++] - '0');
	}
	return (number * casee);
}
/*
int	main(void)
{
	printf("\n");
	printf("my fun %d\n",ft_atoi("  ++2131312"));
	printf("original %d\n",atoi("  ++2131312"));
	printf("\n");
	printf("my fun %d\n",ft_atoi(" a -2147483648"));
	printf("original %d\n",atoi(" a -2147483648"));
	printf("\n");
	printf("my fun %d\n",ft_atoi("0"));
	printf("original %d\n",atoi("0"));
	printf("\n");
	printf("my fun %d\n",ft_atoi("  a+2131312"));
	printf("original %d\n",atoi("  a+2131312"));
}
static int	innerwhile(const char *str, int casee, int i, int counter)
{
	int	number;

	number = 0;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		if (counter >= 19)
		{
			if (casee == -1)
				return (-1);
			else
				return (0);
		}
		number = number * 10 + (str[i++] - '0');
		++counter;
	}
	return (number * casee);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	casee;
	int	counter;

	i = 0;
	casee = 1;
	counter = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			casee *= -1;
		i++;
	}
	return (innerwhile(str, casee, i, counter));
}
*/