/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:48:32 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:31:01 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*str;
	unsigned char	ch;
	size_t			i;

	i = 0;
	ch = (unsigned char)c;
	if (len)
	{
		str = (char*)b;
		while (i < len)
		{
			str[i] = ch;
			i++;
		}
	}
	return ((void*)b);
}
