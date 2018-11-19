/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 15:05:34 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:31:12 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;
	char	*new;

	i = 0;
	if (s)
	{
		str = (char*)s;
		new = ft_strdup(str);
		if (new)
		{
			while (str[i])
			{
				new[i] = f(str[i]);
				i++;
			}
			return (new);
		}
	}
	return (NULL);
}
