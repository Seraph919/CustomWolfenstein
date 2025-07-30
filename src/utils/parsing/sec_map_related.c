/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_map_related.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:40:55 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/30 20:30:19 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

void	t_norm1_init(t_norm1 *norm, int line, int end, char **map)
{
	norm->end = end;
	norm->map = map;
	norm->endl = 0;
	norm->i = 0;
	norm->line = line;
	norm->temp = NULL;
}

bool	str_validation(int line, bool end, t_data *data)
{
	t_norm1	n;

	if (!data->map || !data->map[line])
		return (false);
	t_norm1_init(&n, line, end, data->map);
	n.map_y = data->map_y;
	if (map_checker(n.map, data))
		return (false);
	while (data->map[line][n.i])
	{
		if ((n.line == 0 || n.end) && not_in_str(data->map[line][n.i], "1 \n"))
			return (false);
		if (conditions(&n) == false)
			return (false);
		else if (check_srnds(data, n.i, line, n.map_y) == false)
			return (false);
		if ((n.line == 0 || n.end) && n.i == ft_strlen(data->map[line]) - 2
			&& data->map[line][n.i] != '1' && ft_strlen(data->map[line]) > 2)
		{
			if (!checkbefore(n.temp, n.endl - 1))
				return (false);
		}
		n.i++;
	}
	return (true);
}

int	index_after_spaces(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (is_white_space(s[i]))
		i++;
	if (!s[i])
		return (0);
	while (!is_white_space(s[i]))
		i++;
	return (i);
}
