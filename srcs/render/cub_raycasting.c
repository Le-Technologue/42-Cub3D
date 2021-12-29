/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:09:18 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/29 11:19:33 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub_map.h"
#include "cub_render.h"
#include "cub_raycasting.h"

/* void	set_ray(t_ray *ray) */
/* { */
/* 	ray->len = 0; */
/* } */

static void	set_ray_spread(t_fov *fov, t_ray *ray)
{
	size_t	ray_height;

	ray_height = fov->height / ray->wall_dist;
	ray->top = -ray_height / 2 + fov->height / 2;
	if (ray->top >= fov->height)
		ray->top = 0;
	ray->bottom = ray_height / 2 + fov->height / 2;
	if (ray->bottom >= fov->height)
		ray->bottom = fov->height - 1;
}

static void	normalize_wall_dist(t_cam *cam, t_ray *ray)
{
	if (ray->side == EAS || ray->side == WES)
		ray->wall_dist = (ray->reached.col - cam->pos.x
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->wall_dist = (ray->reached.row - cam->pos.y
				+ (1 - ray->step.y) / 2) / ray->dir.y;
}

static void	dda(t_ray *ray, t_map *map)
{
	while (!ray->hit)
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
		if (*tile(map, ray->reached.col, ray->reached.row) == WALL)
			ray->hit = true;
	}
}

static void	reach_grid(t_ray *ray, t_cam *cam)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->trvl_along.x = (cam->pos.x - ray->reached.col) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->trvl_along.x = (ray->reached.col + 1 - cam->pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->trvl_along.y = (cam->pos.y - ray->reached.row) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->trvl_along.y = (ray->reached.row + 1 - cam->pos.y) * ray->delta.y;
	}
}

void	cast_rays(t_fov *fov, t_cam *cam, t_game *game)
{
	t_ray	ray;
	size_t	x;

	x = 0;
	while (x < fov->width)
	{
		ray.hit = false;
		cam->pixel_x = ((2 * x) / fov->width) - 1; //init
		ray.dir.x = cam->dir.x + cam->pln.x * cam->pixel_x;
		ray.dir.y = cam->dir.y + cam->pln.y * cam->pixel_x;
		ray.reached.col = (size_t)cam->pos.x;
		ray.reached.row = (size_t)cam->pos.y;
		ray.delta.x = fabs(1 / ray.dir.x);
		ray.delta.y = fabs(1 / ray.dir.y);
		reach_grid(&ray, cam);
		dda(&ray, &game->map);
		normalize_wall_dist(cam, &ray);
		set_ray_spread(fov, &ray);
		draw_ray(fov, game, &ray, fov->width - x++); // Weird formula or incr ?
	}
}
