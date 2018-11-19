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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;

	if (s1 && s2)
	{
		str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (str)
		{
			str = ft_strncat(str, s1, ft_strlen(s1));
			str = ft_strncat(str, s2, ft_strlen(s2));
			return (str);
		}
	}
	return (NULL);
}
