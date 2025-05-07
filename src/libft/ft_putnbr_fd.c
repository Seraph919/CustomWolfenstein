/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/27 16:14:42 by asoudani          #+#    #+#             */
/*   Updated: 2024/10/27 16:14:42 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	i;
	long	n;

	i = 1;
	n = nb;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	while (i * 10 <= n)
	{
		i *= 10;
	}
	while (i > 0)
	{
		ft_putchar_fd((n / i) + '0', fd);
		n %= i;
		i /= 10;
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(10, 1);
	ft_putchar_fd('\n',1);
	ft_putnbr_fd(-2147483648, 1);
	ft_putchar_fd('\n',1);
	ft_putnbr_fd(0, 1);
}
*/