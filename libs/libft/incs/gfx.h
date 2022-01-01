/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:39:09 by wetieven          #+#    #+#             */
/*   Updated: 2022/01/01 16:04:36 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <stddef.h>
# include "err.h"
# include "vct.h"

/*
** Rendering structures
*/
typedef struct s_mlx {
	void	*lnk;
	void	*win;
}	t_mlx;

typedef struct s_img {
	void	*ptr;
	int		*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_txtr {
	t_img	img;
	int		height;
	int		width;
}	t_txtr;

// Geometrical vector (discrete and floating point) types
typedef struct s_vi2d {
	int	x;
	int	y;
}	t_vi2d;

typedef struct s_vf2d {
	float	x;
	float	y;
}	t_vf2d;

/*
** Game structures
*/
// POS : Discrete position inside a map grid.
typedef struct s_pos {
	size_t	col;
	size_t	row;
}	t_pos;

// MAP : Using our homemade t_vctr vector data structure, we parse our map in
// a one dimensional (1D) array.
// This allow for WAY simpler memory allocation and better processor cache
// optimisation.
typedef struct s_map {
	t_vctr	*grid;
	size_t	cols;
	size_t	rows;
}	t_map;

/* Linux X11 keycodes - retroengineered from my machine on the github's mlx */
/* typedef enum e_mlx_keycodes { */
/* 	ESC_K = 65307, */
/* 	LFT_K = 65361, */
/* 	A_KEY = 113, */
/* 	DWN_K = 65364, */
/* 	S_KEY = 115, */
/* 	UP_KY = 65362, */
/* 	W_KEY = 122, */
/* 	RGT_K = 65363, */
/* 	D_KEY = 100, */
/* }	t_mlx_keycodes; */

/* MacOS mlx keycodes */
typedef enum e_mlx_keycodes {
	ESC_K = 53,
	LFT_K = 123,
	A_KEY = 0,
	DWN_K = 125,
	S_KEY = 1,
	UP_KY = 126,
	W_KEY = 13,
	RGT_K = 124,
	D_KEY = 2,
}	t_mlx_keycodes;

void	set_pixel(t_img *fov, int x, int y, int color);
t_error	trns_to_int(int *color, int trans);
t_error	rgb_to_int(int *color, int r, int g, int b);

#endif
