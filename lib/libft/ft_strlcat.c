/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 17:56:38 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:44:47 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t		ft_strlcat(char *dst, const char *src,
		size_t dst_size)
{
	size_t		index;
	int			len;
	char		*tmp;

	index = 0;
	tmp = (char*)dst;
	len = ft_strlen(dst);
	while (*tmp)
		tmp++;
	if (dst_size < ft_strlen(dst))
		return (dst_size + ft_strlen(src));
	while (*src && (index + 1) < (dst_size - len))
	{
		*tmp++ = *src++;
		index++;
	}
	*tmp = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
