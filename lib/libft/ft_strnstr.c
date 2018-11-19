/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 19:22:05 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 20:38:52 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*n;
	const char	*h;
	int			l;

	l = 0;
	if (*needle == '\0')
		return ((char*)haystack);
	while (len--)
	{
		if (*haystack == *needle)
		{
			n = needle;
			h = haystack;
			l = len + 1;
			while (*h++ == *n++ && l--)
			{
				if (*n == '\0')
					return ((char*)haystack);
			}
		}
		haystack++;
	}
	return (NULL);
}
