/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_travelling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:58:42 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/29 16:09:00 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub_map.h"
#include "cub_travelling.h"

void	rotate_cam(t_cam *cam, t_fov *fov, t_move direction)
{
	float	prv_dir_x;
	float	prv_pln_x;
	float	rot_speed;

	rot_speed = (float)fov->width / 40000.0;
	if (direction == RTWD)
		rot_speed = -rot_speed;
	prv_dir_x = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(rot_speed) - cam->dir.y * sin(rot_speed);
	cam->dir.y = prv_dir_x * sin(rot_speed) + cam->dir.y * cos(rot_speed);
	prv_pln_x = cam->pln.x;
	cam->pln.x = cam->pln.x * cos(rot_speed) - cam->pln.y * sin(rot_speed);
	cam->pln.y = prv_pln_x * sin(rot_speed) + cam->pln.y * cos(rot_speed);
}

void	move_cam(t_cam *cam, t_game *game, t_move move)
{
	t_vf2d	axis;
	int		orientation;
	t_vf2d	target;

	if (move == FRWD || move == BKWD)
		axis = cam->dir;
	else
		axis = cam->pln;
	if (move == FRWD || move == RTWD)
		orientation = 1;
	else
		orientation = -1;
	target.x = cam->pos.x + (axis.x * MOVE_SPEED) * orientation;
	target.y = cam->pos.y + (axis.y * MOVE_SPEED) * orientation;
	if (*tile(&game->map, (size_t)target.x + THRESHOLD,
				(size_t)cam->pos.y) != WALL)
		cam->pos.x = target.x;
	if (*tile(&game->map, (size_t)cam->pos.x,
				(size_t)target.y + THRESHOLD) != WALL)
		cam->pos.y = target.y;
}

void	set_camera(t_cam *cam, t_plyr *plyr)
{
	int	cam_orientation;

	cam->pos.x = (float)plyr->pos.col + 0.5;
	cam->pos.y = (float)plyr->pos.row + 0.5;
	cam_orientation = 1;
	if (plyr->orientation == PL_N || plyr->orientation == PL_E)
		cam_orientation = -1;
	if (plyr->orientation == PL_N || plyr->orientation == PL_S)
	{
		cam->dir.x = 0;
		cam->dir.y = 1 * cam_orientation;
		cam->pln.x = 0.66 * cam_orientation;
		cam->pln.y = 0;
	}
	else
	{
		cam->dir.x = 1;
		if (plyr->orientation == PL_W)
			cam->dir.x = -1;
		cam->dir.y = 0;
		cam->pln.x = 0;
		cam->pln.y = -0.66;
		if (plyr->orientation == PL_W)
			cam->pln.y = 0.66;
	}
}
