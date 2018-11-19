/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 17:30:04 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/04 18:47:25 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_numlen(int num)
{
	char		*str;
	int			len;

	str = ft_itoa(num);
	len = ft_strlen(str);
	free(str);
	return (len);
}
