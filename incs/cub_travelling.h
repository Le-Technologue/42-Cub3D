/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_travelling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:58:25 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/30 13:54:02 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_TRAVELLING_H
# define CUB_TRAVELLING_H

# include "cub3d.h"

# define MOVE_SPEED 0.05
# define BUMPER 0.25

typedef enum e_move {
	FRWD,
	BKWD,
	LTWD,
	RTWD
}	t_move;

void	process_input(t_game *game);
void	set_camera(t_cam *cam, t_plyr *plyr);

#endif
