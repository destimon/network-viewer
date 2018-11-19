/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 13:56:45 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:31:48 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_words(char const *str, char del)
{
	int	i;

	i = 0;
	if (*str != del && *str != '\0')
		i++;
	while (*str)
	{
		if (*str == del && (*(str + 1) != del && *(str + 1) != '\0'))
			i++;
		str++;
	}
	return (i);
}

static	int		ft_count_length(char const *str, char del)
{
	int i;

	i = 0;
	while (*str != '\0' && *str != del)
	{
		i++;
		str++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		iword;
	char	**arr;
	int		wamount;

	iword = 0;
	if (s)
	{
		wamount = ft_count_words(s, c);
		arr = (char**)malloc(sizeof(*arr) * (wamount + 1));
		if (!arr)
			return (NULL);
		while (wamount--)
		{
			while (*s == c && *s != '\0')
				s++;
			arr[iword] = ft_strsub((const char*)s, 0, ft_count_length(s, c));
			if (!arr[iword])
				return (NULL);
			s = s + ft_count_length((const char*)s, c);
			iword++;
		}
		arr[iword] = NULL;
		return (arr);
	}
	return (NULL);
}
