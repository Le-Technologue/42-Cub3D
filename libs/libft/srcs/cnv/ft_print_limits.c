/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_limits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:10:23 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/08 13:26:02 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"

// This obviously is lazily put for a quick check and should definetely include
// the rest of the limits.h definitions
void	ft_print_limits(void)
{
	ft_printf("LONG_MAX : %lli", LONG_MAX);
}
