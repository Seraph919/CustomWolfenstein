/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 06:44:04 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/05 00:19:25 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
// void f(void *s)
// {
//     char **ret = (char **)s;
//     *ret = malloc(sizeof(char) * 5);
//     if (*ret)
//         strcpy(*ret, "wach");
// }
// //pass the adress of lst->content if u wanna change content to "wach";
// int main()
// {

//     t_list *new = malloc(sizeof(t_list));
//     new->content = "wach_new";
//     new->next = NULL;
//     ft_lstiter(new, f);
//     printf("%s\n", new->content);

//     return (0);
// }