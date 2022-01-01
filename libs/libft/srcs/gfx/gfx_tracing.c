/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:42:05 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/03 11:19:31 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

t_error	rgb_to_int(int *color, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (PARSE);
	*color |= (r << 16 | g << 8 | b);
	return (CLEAR);
}

t_error	trns_to_int(int *color, int trans)
{
	if (trans < 0 || trans > 255)
		return (PARSE);
	*color |= trans << 24;
	return (CLEAR);
}

// Should we add overflow protections for this function ?
// Also for optimization sake, shouldn't we just put 4 instead of that gruesome
// division ?
void	set_pixel(t_img *img, int col, int row, int color)
{
	int	*dst;

	if ((color & 0x00FFFFFF) == 0)
		return ;
	dst = img->addr + col + row * (img->line_size / (img->bpp / 8));
	*(unsigned int *)dst = color;
}
// Also why couldn't this work ?
/*
void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if ((color & 0x00FFFFFF) == 0)
		return ;
	dst = img->addr + x * img->bpp / 8 + y * img->line_size;
	*(unsigned int *)dst = color;
}
*/
