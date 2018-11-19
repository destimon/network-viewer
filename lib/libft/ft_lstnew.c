/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 15:27:14 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 20:22:27 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void	const *content, size_t content_size)
{
	t_list		*new;
	char		*cont;
	size_t		c_size;

	c_size = content_size;
	if (!content)
	{
		c_size = 0;
		cont = NULL;
	}
	else
		cont = ft_strdup(content);
	new = (t_list*)malloc(sizeof(*new));
	if (new)
	{
		new->content = cont;
		new->content_size = c_size;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}
