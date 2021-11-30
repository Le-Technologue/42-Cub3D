/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:34:22 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/30 11:03:37 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_data.h"

t_error	cub_parsing(t_game *game, const char *cub_line)
{
	static int		to_parse = CUB_DATA_RANGE;
	static t_cub	cub[] = {
		[NOR] = {.flag = "NO", .fct = &textr, .ctnt = NULL},
		[WES] = {.flag = "WE", .fct = &textr, .ctnt = NULL},
		[SOU] = {.flag = "SO", .fct = &textr, .ctnt = NULL},
		[EAS] = {.flag = "EA", .fct = &textr, .ctnt = NULL},
		[FLO] = {.flag = "F", .fct = &color, .ctnt = NULL},
		[CEI] = {.flag = "C", .fct = &color, .ctnt = NULL},
	};
	int				elem;

	elem = CUB_DATA_RANGE;
	while (to_parse && elem--)
	{
		if (ft_strncmp(cub[elem].flag, cub_line, 2) == MATCH)
			if (!cub[elem].ctnt)
				return ((cub[elem].fct)(cub, &cub_line));
			else
				return (ft_err_msg("Extraneous cub element.", PARSE));
	}
	if (*cub_line != '\0')
		return (ft_err_msg("Syntax error in cub file.", PARSE));
	else
		return (cub_parse_map()); //delegate missing cub elem mgmt to that func
}
