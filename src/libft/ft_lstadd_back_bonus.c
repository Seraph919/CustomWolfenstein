/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:02:36 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/05 11:30:39 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
// int main()
// {
//     t_list *head = malloc(sizeof(t_list));
//     head->content = "wach";
//     t_list *second = malloc(sizeof(t_list));
//     head->next = second;
//     head->next->content = "wach2";
//     head->next->next = NULL;

//     t_list *new = malloc(sizeof(t_list));
//     new->content = "wach_new";
//     new->next = NULL;
//     ft_lstadd_back(&head, new);
//     printf("%s\n", head->content);
//     printf("%s\n", head->next->content);
//     printf("%s\n", head->next->next->content);

//     return (0);
// }