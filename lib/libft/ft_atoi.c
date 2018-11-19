/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:03:03 by dcherend          #+#    #+#             */
/*   Updated: 2018/03/31 20:17:39 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char const *str)
{
	long long	int		num;
	int					i;
	int					sign;

	sign = 1;
	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (num * sign);
		else if ((num > LL || (num == LL && (str[i] - '0') > 7)) && sign == 1)
			return (-1);
		else if ((num > LL || (num == LL && (str[i] - '0') > 8)) && sign == -1)
			return (0);
		else
			num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}
