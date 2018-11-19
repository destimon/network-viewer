/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:48:06 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:22:07 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*n;
	const char	*h;

	if (*needle == '\0')
		return ((char*)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			n = needle;
			h = haystack;
			while (*h++ == *n++)
			{
				if (*n == '\0')
					return ((char*)haystack);
			}
		}
		haystack++;
	}
	return (NULL);
}
