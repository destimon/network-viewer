/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:29:56 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 20:48:07 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	void	ft_kostyl(int *n, int *min)
{
	if (*n < 0)
	{
		*n *= -1;
		*min = 1;
	}
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		zero;
	int		min;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	zero = 10;
	min = 0;
	len = ft_count(n);
	ft_kostyl(&n, &min);
	if (!(str = ft_strnew(len)))
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (n % zero) + '0';
		n /= 10;
	}
	if (min)
		str[0] = '-';
	return (str);
}
