/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:02:00 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/26 21:00:26 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

void	free_garbage(t_garbage **garbage)
{
	t_garbage	*temp;

	if (!garbage)
		return ;
	if (*garbage)
	{
		while (*garbage)
		{
			temp = *garbage;
			*garbage = (*garbage)->next;
			if (temp->ptr)
				free(temp->ptr);
			free(temp);
		}
	}
}

t_garbage	*new_garbage(void *allocated)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (write(2, "malloc failure\n", 15), NULL);
	new->ptr = allocated;
	new->next = NULL;
	return (new);
}

void	garbage_add_back(void *allocated, t_garbage **garbage)
{
	t_garbage	*last;
	t_garbage	*new_allocation;

	if (!garbage)
		return ;
	new_allocation = new_garbage(allocated);
	if (!new_allocation)
		return (free(allocated));
	if (!*garbage)
		return (*garbage = new_allocation, (void)0);
	last = *garbage;
	while (last->next)
		last = last->next;
	if (last)
		last->next = new_allocation;
}

void	*alloc(size_t size, t_action action)
{
	void				*returned;
	static t_garbage	*garbage;

	if (action == ALLOC)
	{
		returned = malloc(size);
		if (!returned)
			return (write(2, "malloc failure\n", 15), NULL);
		garbage_add_back(returned, &garbage);
		return (returned);
	}
	else if (action == FREE)
		free_garbage(&garbage);
	return (NULL);
}
