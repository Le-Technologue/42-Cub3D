/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:34:22 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/26 12:04:03 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_data.h"

t_error	cub_parsing(t_game *game, const char *cub_line)
{
	static t_cub	cub[] = {
		[NOR] = {.flag = "NO", .fct = &textr, .ctnt = NULL},
		[WES] = {.flag = "WE", .fct = &textr, .ctnt = NULL},
		[SOU] = {.flag = "SO", .fct = &textr, .ctnt = NULL},
		[EAS] = {.flag = "EA", .fct = &textr, .ctnt = NULL},
		[FLO] = {.flag = "F", .fct = &color, .ctnt = NULL},
		[CEI] = {.flag = "C", .fct = &color, .ctnt = NULL},
		[MAP] = {NULL, .fct = &cub_parse_map, .ctnt = NULL},
	};
}
