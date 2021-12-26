/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:08:27 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/26 19:13:26 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	draw_ray(t_fov *fov, t_ray *ray, size_t x)
{
	size_t	y;
	float	wx;
	size_t	tx;
	size_t	ty;

	y = 0;
	while (y < ray->top)
		set_pixel(fov, x, y++, 
}

int	cub_render_frame(t_fov *fov)// or t_game ??
