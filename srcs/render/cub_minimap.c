/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:15:33 by wetieven          #+#    #+#             */
/*   Updated: 2022/01/01 14:09:20 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_map.h"
#include "cub_minimap.h"

void	scale_minimap(t_fov *fov, t_map *map)
{
	if (map->cols <= 30)
		fov->map_tile_wid = 10;
	else
		fov->map_tile_wid = MAP_WID / map->cols;
	if (map->rows <= 25)
		fov->map_tile_hei = 10;
	else
		fov->map_tile_hei = MAP_HEI / map->rows;
}

static void	draw_tile(size_t col, size_t row, t_tile tile, t_fov *fov)
{
	static int	color[] = {
	[VOID] = VOID_COLOR,
	[WALL] = WALL_COLOR,
	[PL_N] = PLYR_COLOR,
	};
	size_t		x;
	size_t		y;

	if (tile == OUTS)
		return ;
	y = 0;
	while (y < fov->map_tile_hei)
	{
		x = 0;
		while (x < fov->map_tile_wid)
		{
			set_pixel(fov->frm, col * fov->map_tile_wid + x,
				row * fov->map_tile_hei + y, color[tile]);
			x++;
		}
		y++;
	}
}

void	draw_map(t_fov *fov, t_cam *cam, t_map *map)
{
	size_t	c;
	size_t	r;

	r = 0;
	while (r < map->rows)
	{
		c = 0;
		while (c < map->cols)
		{
			draw_tile(c, r, *tile(map, c, r), fov);
			c++;
		}
		r++;
	}
	draw_tile((size_t)cam->pos.x, (size_t)cam->pos.y, PL_N, fov);
}
