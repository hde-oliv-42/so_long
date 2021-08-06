/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:23:37 by hde-oliv          #+#    #+#             */
/*   Updated: 2021/05/20 17:08:11 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr_1;
	t_list	*ptr_2;

	if (!lst)
		return (NULL);
	ptr_2 = ft_lstnew((*f)(lst->content));
	if (!ptr_2)
	{
		free(ptr_2);
		return (NULL);
	}
	ptr_1 = ptr_2;
	lst = lst->next;
	while (lst)
	{
		ptr_2->next = ft_lstnew((*f)(lst->content));
		if (!ptr_2->next)
		{
			ft_lstclear(&ptr_1, del);
			return (NULL);
		}
		ptr_2 = ptr_2->next;
		lst = lst->next;
	}
	return (ptr_1);
}
