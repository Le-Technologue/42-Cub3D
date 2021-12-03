/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:34:22 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/03 16:49:07 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_data.h"

static bool	is_map_elem(char c)
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

t_error	map_parsing(t_game *game, const char *cub_line, int gnl_status)
{
	t_error	error;

	error = CLEAR;
	if (cub_chk(game->data) != CLEAR)
		error = ft_err_msg("Incomplete cub file.", PARSE);
	if (!is_map_elem(*cub_line) || (error && is_map_elem(*cub_line));
		error = ft_err_msg("Syntax error in cub file.", PARSE);
	if (error)
		return (error);
	// read map
	// write map
}

t_error	cub_parsing(t_game *game, const char *cub_line, int gnl_status)
{
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
	while (*cub_line != '\0' && elem--)
	{
		if (ft_strncmp(cub[elem].flag, cub_line, 2) == MATCH)
			if (!cub[elem].ctnt)
				return ((cub[elem].fct)(cub, &cub_line));
			else
				return (ft_err_msg("Extraneous cub element.", PARSE));
	}
	if (gnl_status == 0 && *cub_line == '\0')
		return (PARSE); //If we haven't got ourselves a map at that stage, this is fucked.
	else if (*cub_line == '\0')
		return (CLEAR); //just an empty line is valid, keep going
	else
		return (cub_parse_map(game, gnl_status)); //delegate missing cub elem mgmt, and the bogus line check
}
