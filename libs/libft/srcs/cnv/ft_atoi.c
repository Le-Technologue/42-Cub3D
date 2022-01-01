/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 18:53:46 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/08 13:21:40 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "chr.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				sign;

	sign = 1;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - 48);
	if (res > LONG_MAX)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (res * sign);
}
