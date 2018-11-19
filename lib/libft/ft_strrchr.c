/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:44:48 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 17:22:41 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *occ;

	occ = NULL;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			occ = (char*)s;
		s++;
	}
	if (!c)
		return ((char*)s);
	if ((char*)s == occ)
		occ = (char*)s;
	return (occ);
}
