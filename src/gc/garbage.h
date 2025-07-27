/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:10:37 by asoudani          #+#    #+#             */
/*   Updated: 2025/07/26 20:17:51 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_action
{
	ALLOC,
	FREE
}						t_action;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

void					*alloc(size_t size, t_action action);

#endif