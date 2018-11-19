/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:46:51 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:23:11 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		len;

	if (s)
	{
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		if (*s == '\0')
			return (ft_strdup(""));
		len = ft_strlen(s);
		while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
			len--;
		str = ft_strsub(s, 0, len);
		return ((char*)str);
	}
	return (NULL);
}
