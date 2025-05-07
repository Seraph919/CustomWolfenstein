/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:34:34 by asoudani          #+#    #+#             */
/*   Updated: 2024/10/28 10:20:40 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int argument)
{
	int	casee;

	casee = 0;
	if ((argument >= 'A' && argument <= 'Z') || (argument >= 'a'
			&& argument <= 'z') || (argument >= '0' && argument <= '9'))
		casee = 1;
	return (casee);
}
