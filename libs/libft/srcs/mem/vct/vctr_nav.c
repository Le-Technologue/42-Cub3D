/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vctr_nav.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:59:28 by wetieven          #+#    #+#             */
/*   Updated: 2021/10/30 16:05:48 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "vct.h"

// Apparently broken, needs further testing
void	*vctr_entry(t_vctr *vctr, size_t index)
{
	return (&vctr->data + index * vctr->unit_size);
}
/*
void	*two_d_vctr_entry(t_vctr *grid, size_t col, size_t row, size_t wid)
{
	return ((void *)(&grid->data[col * grid->unit_size +
				(row * wid) * grid->unit_size]));
}
*/
