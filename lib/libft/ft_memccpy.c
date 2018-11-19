/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:07:56 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 16:45:45 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,
		size_t n)
{
	const char		*s;
	char			*d;
	size_t			i;

	i = 0;
	s = (char*)src;
	d = (char*)dst;
	while (i < n)
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			*d++ = *s++;
			return ((void*)d);
		}
		*d++ = *s++;
		i++;
	}
	return (NULL);
}
