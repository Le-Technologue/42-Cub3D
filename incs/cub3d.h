/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:26 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/31 13:13:18 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

// For ft_strncmp matches
# define MATCH 0

// TILES : All the possible map bits, an OUTS tile for signaling when
// we stumble outside the map, and a FILL tile to floodfill our map
// and check it for leaks.
# define TILE_RANGE 7

typedef enum e_tile {
	OUTS,
	VOID,
	WALL,
	PL_N,
	PL_W,
	PL_S,
	PL_E,
	FILL
}	t_tile;

// PLYR : Player parsing data structure
typedef struct s_plyr {
	bool		exists;
	t_pos		pos;
	t_tile		orientation;
}	t_plyr;

typedef struct s_game	t_game;

// CUB : Data parsing and storage array structure
# define CUB_DATA_RANGE 6

typedef enum e_cub_key {
	NOR,
	SOU,
	WES,
	EAS,
	FLO,
	CEI
}	t_cub_key;

typedef t_error			(*t_cub_parser)(t_game *g, t_cub_key elem, char *line);

typedef struct s_cub {
	char			*flag;
	t_cub_parser	fct;
	void			*ctnt;
}	t_cub;

// INPUT : an array of this struct creates a key matrix,
// the following enum is its index.
typedef struct s_input {
	bool			held;
	t_mlx_keycodes	keycode;
}	t_input;

typedef enum e_cub_keys {
	LFT,
	RGT,
	W,
	A,
	S,
	D
}	t_cub_keys;

// RAY: vector probing the map in front of the player to create a line of sight.
typedef struct s_ray {
	t_vf2d		dir;
	t_vi2d		step;
	t_vf2d		delta;
	t_vf2d		trvl_along;
	t_pos		reached;
	t_cub_key	side;
	bool		hit;
	float		wall_dist;
	int			bottom;
	int			top;
}	t_ray;

// CAMERA: necessary vectors to aim our rays and render our view,
// acting eyes and legs of the player during the game.
typedef struct s_cam {
	t_vf2d	pos;
	t_vf2d	dir;
	t_vf2d	pln;
	float	pixel_x;
}	t_cam;

// FIELD OF VIEW: Overarching graphic parameters to render our frame.
# define RESOL_WID 1024
# define RESOL_HEI 768

typedef struct s_fov {
	t_mlx	mlx;
	size_t	height;
	size_t	width;
	t_img	*frm;
}	t_fov;

// GAME : All encompassing, game system data structure
typedef struct s_game {
	t_cub	*data;
	size_t	map_offset;
	t_map	map;
	t_plyr	plyr;
	t_cam	cam;
	t_input	*key;
	t_fov	*fov;
}	t_game;

t_error	cub_shutdown(t_game *game, t_error cause);

#endif
