/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:46:37 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/27 14:31:32 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_moves.h"

void	rotation(t_fov *fov, t_cam *cam, t_move direction)
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

void	longitudinal_move(
