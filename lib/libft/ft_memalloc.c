/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:57:51 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/30 18:03:50 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t		i;
	char		*str;

	i = 0;
	str = (char*)malloc(sizeof(str) * size);
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	return ((void*)str);
}
