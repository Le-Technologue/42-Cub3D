/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_travelling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:58:42 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/30 13:53:27 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub_map.h"
#include "cub_travelling.h"

static void	rotate_cam(t_cam *cam, t_fov *fov, t_move direction)
{
	float	prv_dir_x;
	float	prv_pln_x;
	float	rot_speed;

	rot_speed = (float)fov->width / 40000.0;
	if (direction == LTWD)
		rot_speed = -rot_speed;
	prv_dir_x = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(rot_speed) - cam->dir.y * sin(rot_speed);
	cam->dir.y = prv_dir_x * sin(rot_speed) + cam->dir.y * cos(rot_speed);
	prv_pln_x = cam->pln.x;
	cam->pln.x = cam->pln.x * cos(rot_speed) - cam->pln.y * sin(rot_speed);
	cam->pln.y = prv_pln_x * sin(rot_speed) + cam->pln.y * cos(rot_speed);
}

static void	move_cam(t_cam *cam, t_game *game, t_move move)
{
	t_vf2d	axis;
	int		orientation;
	t_vf2d	target;

	if (move == FRWD || move == BKWD)
		axis = cam->dir;
	else
		axis = cam->pln;
	if (move == FRWD || move == LTWD)
		orientation = 1;
	else
		orientation = -1;
	target.x = cam->pos.x + (axis.x * MOVE_SPEED) * orientation;
	target.y = cam->pos.y + (axis.y * MOVE_SPEED) * orientation;
	if (*tile(&game->map, (size_t)target.x, (size_t)cam->pos.y) == VOID)
		cam->pos.x = target.x;
	if (*tile(&game->map, (size_t)cam->pos.x, (size_t)target.y) == VOID)
		cam->pos.y = target.y;
}

void	process_input(t_game *game)
{
	if (game->key[W].held && !game->key[S].held)
		move_cam(&game->cam, game, FRWD);
	else if (game->key[S].held && !game->key[W].held)
		move_cam(&game->cam, game, BKWD);
	if (game->key[A].held && !game->key[D].held)
		move_cam(&game->cam, game, LTWD);
	else if (game->key[D].held && !game->key[A].held)
		move_cam(&game->cam, game, RTWD);
	if (game->key[LFT].held && !game->key[RGT].held)
		rotate_cam(&game->cam, game->fov, LTWD);
	else if (game->key[RGT].held && !game->key[LFT].held)
		rotate_cam(&game->cam, game->fov, RTWD);
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
