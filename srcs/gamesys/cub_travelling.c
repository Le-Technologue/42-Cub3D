/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_travelling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:58:42 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/28 10:26:20 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_travelling.h"

void	rotate(t_fov *fov, t_cam *cam, t_move direction)
{
	float	prv_dir_x;
	float	prv_pln_x;
	float	rot_speed;

	rot_speed = ((float)fov->width * 2) / 40000.0;
	if (direction == RTWD)
		rot_speed = -rot_speed;
	prv_dir_x = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(rot_speed) - cam->dir.y * sin(rot_speed);
	cam->dir.y = prv_dir_x * sin(rot_speed) + cam->dir.y * cos(rot_speed);
	prv_plane_x = cam->plane.x;
	cam->pln.x = cam->pln.x * cos(rot_speed) - cam->pln.y * sin(rot_speed);
	cam->pln.y = prv_pln_x * sin(rot_speed) + cam->pln.y * cos(rot_speed);
}

void	move(t_cam *cam, t_game *game, t_move move)
{
	vf2d	axis;
	int		orientation;
	vf2d	target;

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
	if (*tile(game, (size_t)target.x, (size_t)cam->pos.y) != WALL)
		cam->pos.x = target.x;
	if (*tile(game, (size_t)cam->pos.x, (size_t)target.y) != WALL)
		cam->pos.y = target.y;
}

void	set_camera(t_cam *cam, t_plyr *plyr)
{
	int cam_orientation;

	cam->pos.x = (float)plyr->pos.x + 0.5;
	cam->pos.y = (float)plyr->pos.y + 0.5;
	if (plyr->orientation == PL_N || plyr->orientation == PL_W)
		cam_orientation = -1;
	else
		cam_orientation = 1;
	if (plyr->orientation == PL_N || PL_S)
	{
		cam->dir.x = 0;
		cam->dir.y = 1 * cam_orientation;
		cam->pln.x = 0.66 * cam_orientation;
		cam->pln.y = 0;
	}
	else
	{
		cam->dir.x = 1 * cam_orientation;
		cam->dir.y = 0;
		cam->pln.x = 0;
		cam->pln.y = 0.66 * cam_orientation;
	}
}
