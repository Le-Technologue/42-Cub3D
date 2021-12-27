/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:26 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/27 15:02:40 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "cub_render.h"

# define MATCH 0

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
typedef struct s_cub	t_cub;

typedef t_error	(*t_cub_parser)(t_game *game, t_cub_key elem, char *line);

# define CUB_DATA_RANGE 6
typedef enum e_cub_key {
	NOR,
	SOU,
	WES,
	EAS,
	FLO,
	CEI
}	t_cub_key;

typedef struct s_cub {
	char			*flag;
	t_cub_parser	fct;
	void			*ctnt;
}	t_cub;

typedef enum e_cub_keys {
	LFT,
	RGT,
	W,
	A,
	S,
	D
}	t_cub_keys;

typedef struct s_input {
	bool			held;
	t_mlx_keycodes	keycode;
}	t_input;

// GAME : Overarching game system structure
typedef struct s_game {
	t_cub	*data;
	size_t	map_offset;
	t_map	map;
	t_plyr	plyr;
	t_cam	cam;
	t_fov	*fov;
	t_input	*key;
}	t_game;

#endif
