/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:32:21 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/20 08:03:52 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MAP_H
# define CUB_MAP_H

# include "cub3d.h"

typedef t_error	(*t_map_builder)(t_game *game, t_tile tile);

typedef struct s_map_swtch {
	const char		flag;
	t_map_builder	parser;
}	t_map_swtch;

t_tile	*tile(t_map *map, size_t col, size_t row);
t_error	cub_map(t_game *game, t_newline *nl);

#endif
