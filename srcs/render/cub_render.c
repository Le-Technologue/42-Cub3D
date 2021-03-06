/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:08:27 by wetieven          #+#    #+#             */
/*   Updated: 2022/01/01 13:46:18 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "cub_raycasting.h"
#include "cub_travelling.h"
#include "cub_minimap.h"
#include "cub_render.h"

void	cub_set_pixel(t_fov *fov, int col, int row, int color)
{
	int	*dst;

	if ((size_t)col > fov->width - 1 || (size_t)row > fov->height - 1
		|| (color & 0x00FFFFFF) == 0)
		return ;
	dst = fov->frm->addr + col + row * (fov->frm->line_size
			/ (fov->frm->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_ray(t_fov *fov, t_game *game, t_ray *ray, size_t x)
{
	int		y;
	float	wx;
	int		tx;
	int		ty;
	t_txtr	*texture;

	y = 0;
	texture = game->data[ray->side].ctnt;
	while (y < ray->top)
		cub_set_pixel(fov, x, y++, *(int *)game->data[CEI].ctnt);
	if (ray->side == EAS || ray->side == WES)
		wx = game->cam.pos.y + ray->wall_dist * ray->dir.y;
	else
		wx = game->cam.pos.x + ray->wall_dist * ray->dir.x;
	wx -= floor(wx);
	while (y < ray->bottom && (size_t)y < fov->height)
	{
		ty = (y - ray->top) * texture->height / (ray->bottom - ray->top);
		tx = wx * texture->width;
		cub_set_pixel(fov, x, y++,
			texture->img.addr[(ty * texture->width) + tx]);
	}
	while ((size_t)y < fov->height)
		cub_set_pixel(fov, x, y++, *(int *)game->data[FLO].ctnt);
}

int	cub_render_frame(t_game *game)
{
	cast_rays(game->fov, &game->cam, game);
	draw_map(game->fov, &game->cam, &game->map);
	mlx_put_image_to_window(game->fov->mlx.lnk, game->fov->mlx.win,
		game->fov->frm->ptr, 0, 0);
	process_input(game);
	return (0);
}
