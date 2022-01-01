/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 13:36:37 by wetieven          #+#    #+#             */
/*   Updated: 2022/01/01 14:03:24 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MINIMAP_H
# define CUB_MINIMAP_H

# define MAP_WID 250
# define MAP_HEI 300

# define VOID_COLOR 6579300
# define WALL_COLOR 16777215
# define PLYR_COLOR 9843271

# include "cub3d.h"

void	scale_minimap(t_fov *fov, t_map *map);
void	draw_map(t_fov *fov, t_cam *cam, t_map *map);

#endif
