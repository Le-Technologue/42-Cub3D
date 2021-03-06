/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:19:21 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/28 12:18:04 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_RENDER_H
# define CUB_RENDER_H

# include "cub3d.h"

void	draw_ray(t_fov *fov, t_game *game, t_ray *ray, size_t x);
int		cub_render_frame(t_game *game);

#endif
