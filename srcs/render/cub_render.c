/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:08:27 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/25 11:22:57 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* void	set_ray(t_ray *ray) */
/* { */
/* 	ray->len = 0; */
/* } */

void	dda(t_map *map, t_ray *ray)
{
	while(*tile(map, ray->reached.col, ray->reached.row) != WALL)
	{
		if (ray->trvl_along.x < ray->trvl_along.y)
		{
			ray->trvl_along.x += ray->delta.x;
			ray->reached.col += ray->step.x;
			if (ray->step.x == 1)
				ray->side = EAS;
			else
				ray->side = WES;
		}
		else
		{
			ray->trvl_along.y += ray->delta.y;
			ray->reached.row += ray->step.y;
			if (ray->step.y == 1)
				ray->side = SOU;
			else
				ray->side = NOR;
		}
	}
}

void	reach_grid(t_plyr plyr, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->trvl_along.x = (plyr.pos.col - ray->reached.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->trvl_along.x = (ray->reached.x + 1 - plyr.pos.col) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->trvl_along.y = (plyr.pos.row - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->trvl_along.y = (ray->map.y + 1 - plyr.pos.y) * ray->delta.y;
	}
}

void	cast_rays(t_fov *fov)
{
	t_ray	ray;
	size_t	x;

	x = 0;
	while (x < fov->width)
	{
		fov->pixel.x = ((2 * x) / fov->width) - 1; //init
		ray.dir.x = fov->cam.dir.x + fov->cam.plane.x * fov->pixel.x;
		ray.dir.y = fov->cam.dir.y + fov->cam.plane.y * fov->pixel.x;
		ray.reached.col = fov->game->plyr.pos.col;
		ray.reached.row = fov->game->plyr.pos.row;
		ray.delta.x = fabs(1 / ray.dir.x);
		ray.delta.y = fabs(1 / ray.dir.y);
		reach_grid(fov->game->plyr, &ray);
		dda(fov->game->map, &ray);
		// calc dist au mur...
	}
}
