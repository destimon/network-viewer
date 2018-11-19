/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:47:46 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/29 14:02:27 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t		i;
	char		*str;

	i = 0;
	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return (0);
	else
	{
		while (i < size)
		{
			str[i] = '\0';
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
