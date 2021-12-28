/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:19:21 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/28 11:13:08 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_RENDER_H
# define CUB_RENDER_H

// RAY: vector probing the map in front of the player to create a line of sight.
typedef struct s_ray {
	t_vf2d		dir;
	t_vi2d		step;
	t_vf2d		delta;
	t_vf2d		trvl_along;
	t_pos		reached;
	t_cub_key	side;
	float		wall_dist;
	size_t		bottom;
	size_t		top;
}	t_ray;

// CAMERA: necessary vectors to aim our rays and render our view,
// acting eyes and legs of the player during the game.
typedef struct s_cam {
	t_vf2d	pos;
	t_vf2d	dir;
	t_vf2d	pln;
	int		pixel_x;
}	t_cam;

// FIELD OF VIEW: overarching graphic parameters to render our frame.
# define RESOL_WID 1024
# define RESOL_HEI 768

typedef struct s_fov {
	t_mlx	mlx;
	size_t	height;
	size_t	width;
	t_img	*frm;
	/* size_t	tile_hgt; */
	/* size_t	tile_wid; */
}	t_fov;

#endif
