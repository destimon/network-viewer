/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:50:42 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/23 15:20:05 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char		*str;
	size_t			i;

	str = (char*)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)*str == (unsigned char)c)
		{
			return ((void*)str);
		}
		str++;
		i++;
	}
	return (NULL);
}
