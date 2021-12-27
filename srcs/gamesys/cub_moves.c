/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:46:37 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/27 15:45:44 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_moves.h"

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
		axis = cam->plane;
	if (move == FRWD || move == RTWD)
		orientation = 1;
	else
		orientation = -1;
	target.x = cam->pos.x + (axis.x * MOVE_SPEED) * orientation;
	target.y = cam->pos.y + (axis.y * MOVE_SPEED) * orientation;
	if (!collision(game, target.x, cam->pos.y)
		cam->pos.x = target.x;
	if (!collision(game, cam->pos.x, target.y)
		cam->pos.y = target.y;
}
