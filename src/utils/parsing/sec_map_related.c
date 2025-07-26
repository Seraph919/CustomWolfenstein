/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_map_related.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:40:55 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/26 21:41:07 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	t_norm1_init(t_norm1 *norm, int line, int end)
{
	norm->end = end;
	norm->endl = 0;
	norm->i = 0;
	norm->line = line;
	norm->temp = NULL;
}

bool	str_validation(int line, bool end, t_data *data)
{
	t_norm1	norm;

	if (!data->map || !data->map[line])
		return (false);
	t_norm1_init(&norm, line, end);
	norm.map = data->map;
	norm.map_y = data->map_y;
	if (map_checker(norm.map, data))
		return (false);
	while (data->map[line][norm.i])
	{
		if ((norm.line == 0 || norm.end) && not_in_str(data->map[line][norm.i],
				"1 \n"))
			return (false);
		if (conditions(&norm) == false)
			return (false);
		else if (check_srnds(data, norm.i, line, norm.map_y) == false)
			return (false);
		if (norm.i == ft_strlen(data->map[line]) - 2
			&& data->map[line][norm.i] != '1')
		{
			if (!checkbefore(norm.temp, norm.endl - 1))
				return (false);
		}
		norm.i++;
	}
	return (true);
}
