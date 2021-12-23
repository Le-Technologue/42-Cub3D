/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:08:27 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/23 17:06:56 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
void	set_ray(t_ray *ray)
{
	ray->len = 0;
}

void	cast_rays(t_game *game, t_fov *fov)
{
	t_ray	ray;
	size_t	x;

	x = 0;
	while (x < fov->width)
	{
		fov->grid.x = ((2 * x) / fov->width) - 1;
		ray.dir.x = fov->cam.dir.x + fov->cam.plane.x * fov->grid.x;
		ray.dir.y = fov->cam.dir.y + fov->cam.plane.y * fov->grid.x;
		ray.reached.col = game->plyr.pos.col;
		ray.reached.row = game->plyr.pos.row;
		ray.delta.x = fabs(1 / ray.dir.x);
		ray.delta.y = fabs(1 / ray.dir.y);
	}
}
