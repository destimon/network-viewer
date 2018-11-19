/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:37:17 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/29 13:46:05 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char			*ft_strsjoin(int amount, ...)
{
	va_list		ap;
	char		*str1;
	char		*str2;
	char		*index;
	int			i;

	if (amount < 0)
		return (NULL);
	va_start(ap, amount);
	str1 = ft_strdup(va_arg(ap, char*));
	i = 1;
	while (i < amount)
	{
		str2 = ft_strdup(va_arg(ap, char*));
		index = str1;
		str1 = ft_strjoin(str1, str2);
		free(index);
		free(str2);
		i++;
	}	
	va_end(ap);
	return (str1);
}
