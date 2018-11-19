/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:03:11 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:32:52 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		i;
	size_t		len;
	char		*s2;

	len = ft_strlen(s1);
	i = 0;
	s2 = ft_strnew(len);
	if (s2)
	{
		while (i < len)
		{
			s2[i] = s1[i];
			i++;
		}
		s2[i] = '\0';
		return ((char*)s2);
	}
	return (NULL);
}
