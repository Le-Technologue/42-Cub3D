/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:32:21 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/07 15:17:50 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MAP_H
# define CUB_MAP_H

# define TILE_RANGE 7

typedef enum e_tile {
	OUTS,
	VOID,
	WALL,
	PL_N,
	PL_W,
	PL_S,
	PL_E
}	t_tile;

typedef t_error	(*t_map_builder)(t_game *game, t_tile tile);

typedef struct s_pars_swtch {
	const char		flag;
	t_map_builder	parser;
}	t_pars_swtch;

bool	is_map_elem(char c);
t_error	build_map(t_game *game, t_newline *nl);

#endif
