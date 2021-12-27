/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:08:27 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/27 15:28:29 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	draw_ray(t_fov *fov, t_game *game, t_ray *ray, size_t x)
{
	size_t	y;
	float	wx;
	size_t	tx;
	size_t	ty;
	t_txtr	*texture;

	y = 0;
	texture = game->cub[ray->side].data;
	while (y < ray->top)
		set_pixel(fov->frm, x, y++, (int)*game->cub[CEI].data);
	if (ray->side == EAS || ray->side == WES)
		wx = game->cam.pos.y + ray->wall_dist * ray->dir.y;
	else
		wx = game->cam.pos.x + ray->wall_dist * ray->dir.x;
	wx -= floor(wx);
	while (y < ray->bottom)
	{
		ty = (y - ray->top) * texture->height / (ray->bottom - ray->top);
		tx = wx * texture->width;
		set_pixel(fov->frm, x, y++,
				texture->img.addr[(ty * texture.width) + tx]);
	}
	while (y < fov->height)
		set_pixel(fov->frm, x, y++, (int)*game->cub[FLO].data);
}

int	cub_render_frame(t_game *game)
{
	//timestamp ?
	cast_rays(game->fov, game);
	mlx_put_image_to_window(game->fov.mlx.lnk, game->fov->mlx.win,
			game->fov->frm->ptr, 0, 0);
	process_input(game);
}
