/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_strtol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:38:56 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/17 15:17:53 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Parsing friendly strtol, with custom overflow and string completion signaling

#include <limits.h>
#include "cnv.h"
#include "chr.h"

t_error	prs_strtol(long *res, char **str, long min, long max)
{
	int	sign;

	sign = 1;
	*res = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-' || **str == '+')
		if (*((*str)++) == '-')
			sign *= -1;
	while (ft_isdigit(**str) && **str)
	{
		*res = *res * 10 + (**str - 48);
		(*str)++;
	}
	*res *= sign;
	if (*res > LONG_MAX && sign == -1)
		*res = LONG_MIN;
	if (*res >= LONG_MAX && sign == 1)
		*res = LONG_MAX;
	if (*res < min || *res > max || **str != '\0')
		return (PARSE);
	return (CLEAR);
}
