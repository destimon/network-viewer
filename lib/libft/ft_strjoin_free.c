/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:53:18 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/04 18:46:02 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, _Bool s1b, _Bool s2b)
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
		if (s1b)
			free(s1);
		if (s2b)
			free(s2);
	}
	return (NULL);
}
