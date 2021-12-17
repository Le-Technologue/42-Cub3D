/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:34:22 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/17 16:20:14 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_data.h"
#include "cub_parsers.h"

bool	is_map_elem(char c)
{
	if (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (true);
	else
		return (false);
}

t_error	cub_chk(t_cub *cub)
{
	int	elem;

	elem = CUB_DATA_RANGE;
	while (elem--)
		if (cub[elem].ctnt == NULL)
			return (PARSE);
	return (CLEAR);
}

static t_error	measure_map(t_game *game, t_newline *nl)
{
	t_error			error;

	if (*nl->line == '\0')
		return (CLEAR); //just an empty line is valid, keep going
	error = CLEAR;
	if (cub_chk(game->data) != CLEAR)
		error = PARSE;
	if (!is_map_elem(*nl->line) || (error && is_map_elem(*nl->line)))
		error = ft_err_msg("Syntax error in cub file.", PARSE);
	if (!error)
	{
		if (!game->map_offset)
			game->map_offset = nl->count;
		if (ft_strlen(nl->line) > game->map.cols)
			game->map.cols = ft_strlen(nl->line);
		game->map.rows++;
	}
	return (error);
}

t_error	cub_data(t_game *game, t_newline *nl)
{
	static t_cub	cub[] = {
	[NOR] = {.flag = "NO", .fct = &textr, .ctnt = NULL},
	[WES] = {.flag = "WE", .fct = &textr, .ctnt = NULL},
	[SOU] = {.flag = "SO", .fct = &textr, .ctnt = NULL},
	[EAS] = {.flag = "EA", .fct = &textr, .ctnt = NULL},
	[FLO] = {.flag = "F ", .fct = &color, .ctnt = NULL},
	[CEI] = {.flag = "C ", .fct = &color, .ctnt = NULL},
	};
	t_cub_key		elem;

	game->data = cub;
	elem = CUB_DATA_RANGE;
	while (*nl->line != '\0' && elem--)
	{
		if (ft_strncmp(cub[elem].flag, nl->line, 2) == MATCH)
		{
			if (!cub[elem].ctnt)
				return ((cub[elem].fct)(game, elem, nl->line));
			else
				return (ft_err_msg("Extraneous cub element.", PARSE));
		}
	}
	return (measure_map(game, nl)); //missing cub elem and bogus line checks are delegated to that function
}
