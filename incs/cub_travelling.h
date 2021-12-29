/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_travelling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:58:25 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/29 21:41:49 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_TRAVELLING_H
# define CUB_TRAVELLING_H

# include "cub3d.h"

# define MOVE_SPEED 0.05
# define THRESHOLD 0.25

typedef enum e_move {
	FRWD,
	BKWD,
	LTWD,
	RTWD
}	t_move;

void	rotate_cam(t_cam *cam, t_fov *fov, t_move direction);
void	move_cam(t_cam *cam, t_game *game, t_move move);
void	set_camera(t_cam *cam, t_plyr *plyr);

#endif
