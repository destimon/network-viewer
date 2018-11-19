/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 16:43:32 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 20:22:12 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*first;
	t_list		*another;

	if (lst && f)
	{
		first = f(lst);
		another = first;
		lst = lst->next;
		while (lst)
		{
			another->next = f(lst);
			if (!(another->next))
				return (NULL);
			another = another->next;
			lst = lst->next;
		}
		another->next = NULL;
		return (first);
	}
	return (NULL);
}
