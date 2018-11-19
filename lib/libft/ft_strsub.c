/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:46:40 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:32:16 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char				*dst;
	unsigned int		i;

	if (s)
	{
		i = 0;
		dst = ft_strnew(len);
		if (!dst)
			return (NULL);
		while (i < len)
		{
			dst[i] = s[start];
			i++;
			start++;
		}
		dst[i] = '\0';
		return (dst);
	}
	return (NULL);
}
