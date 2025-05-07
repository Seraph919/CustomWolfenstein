/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:09:06 by asoudani          #+#    #+#             */
/*   Updated: 2024/11/06 09:42:26 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_element;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new_list = 0;
	while (lst)
	{
		temp = f(lst->content);
		new_element = ft_lstnew(temp);
		if (new_element == NULL)
		{
			free(temp);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_element);
		lst = lst->next;
	}
	return (new_list);
}
// int main()
// {
//     t_list *root = ft_lstnew("root");
//     t_list *root2 = ft_lstnew("root2");
//     t_list *root3 = ft_lstnew("root3");
//     t_list *root4 = ft_lstnew("root4");
//     root->next = root2;
//     root->next->next = root3;
//     root->next->next->next = root4;

//     t_list *mapped = ft_lstmap(root, f, del);
//     printf("%s\n", mapped->content);
//     printf("%s\n", mapped->next->content);
//     printf("%s\n", mapped->next->next->content);
// }
