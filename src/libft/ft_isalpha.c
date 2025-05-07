/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:34:48 by asoudani          #+#    #+#             */
/*   Updated: 2024/10/28 10:21:03 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int argument)
{
	int	casee;

	casee = 0;
	if ((argument >= 'A' && argument <= 'Z') || (argument >= 'a'
			&& argument <= 'z'))
		casee = 1;
	return (casee);
}
