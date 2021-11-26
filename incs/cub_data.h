/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 08:44:09 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/26 10:11:43 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DATA_H
# define CUB_DATA_H

# include "libft.h"

/* # define CUB_DATA_RANGE 7 */
# define TILE_RANGE 3

typedef enum e_cub_key {
	NOR,
	SOU,
	WES,
	EAS,
	FLO,
	CEI,
	MAP
}	t_cub_key;

typedef struct s_cub {
	char		*flag,
	t_parser	fct,
	void		*ctnt,
}	t_cub;

typedef enum e_tile {
	VOID,
	WALL,
	PL_N,
	PL_W,
	PL_S,
	PL_E
}	t_tile;

typedef struct s_plyr {
	bool		exists;
	t_pos		pos;
	t_tile		orientation;
}	t_plyr;

typedef struct s_cub {
	char			*flag,
	t_cub_parser	fct,
	void			*ctnt
}	t_cub;

typedef struct s_game {
	t_cub	data;
	t_map	map;
	t_plyr	plyr;
}	t_game;

typedef struct s_fov {
	t_mlx	mlx;
	size_t	height;
	size_t	width;
	t_img	*frm;
	/* size_t	tile_hgt; */
	/* size_t	tile_wid; */
	t_game	*game;
}	t_fov;

typedef t_error	(*t_cub_parser)(char **line, t_cub *cub);

#endif
