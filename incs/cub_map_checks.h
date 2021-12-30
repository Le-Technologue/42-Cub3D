/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_checks.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:42:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/30 14:14:23 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MAP_CHECKS_H
# define CUB_MAP_CHECKS_H

# include "cub3d.h"

bool	is_map_elem(char c);
t_error	measure_map(t_game *game, t_newline *nl);
t_error	map_breached(t_game *game);
t_error	chk_map_prerequisites(t_game *game);
void	print_map_vctr(t_map map);

#endif
