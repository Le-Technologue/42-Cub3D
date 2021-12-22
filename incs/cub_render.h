/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:19:21 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/22 16:40:51 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_RENDER_H
# define CUB_RENDER_H

typedef struct s_ray {
	t_vc2d	tail;
	t_vc2d	dir;
	t_vc2d	travel_along;
	t_pos	reached_tile;
	float	head_dist;
}	t_ray;

typedef struct s_cam {
	t_pos	tile;
	t_vc2d	delta;
}	t_cam;

typedef struct s_fov {
	t_mlx	mlx;
	size_t	height;
	size_t	width;
	t_img	*frm;
	/* size_t	tile_hgt; */
	/* size_t	tile_wid; */
}	t_fov;

#endif
