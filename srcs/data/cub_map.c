/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:30:59 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/17 16:11:07 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_data.h"
#include "cub_map.h"

static t_error	put_tile(t_game *game, t_tile tile)
{
	return (vctr_push(game->map.grid, &tile));
}

static t_error	put_plyr(t_game *game, t_tile tile)
{
	if (game->plyr.exists)
		return (ft_err_msg("You can't have several players on the map", PARSE));
	game->plyr.exists = true;
	game->plyr.orientation = tile;
	game->plyr.pos.row = game->map.rows;
	game->plyr.pos.col = game->map.grid->entries % game->map.cols;
	return (put_tile(game, VOID));
}

static t_error	map_parser(t_game *game, const char map_elem)
{
	static t_map_swtch	map_pars_set[] = {
	[OUTS] = {.flag = ' ', .parser = &put_tile},
	[VOID] = {.flag = '0', .parser = &put_tile},
	[WALL] = {.flag = '1', .parser = &put_tile},
	[PL_N] = {.flag = 'N', .parser = &put_plyr},
	[PL_W] = {.flag = 'W', .parser = &put_plyr},
	[PL_S] = {.flag = 'S', .parser = &put_plyr},
	[PL_E] = {.flag = 'E', .parser = &put_plyr},
	};
	t_tile				i;

	i = 0;
	while (i < TILE_RANGE)
	{
		if (map_elem == map_pars_set[i].flag)
			return ((map_pars_set[i].parser)(game, i));
		i++;
	}
	ft_printf("Error\nInvalid flag \"%c\" on row %lu col %lu.\n",
		map_elem, game->map.rows,
		game->map.grid->entries % game->map.cols);
	return (PARSE);
}

t_error	cub_map(t_game *game, t_newline *nl)
{
	size_t	i;
	size_t	line_len;
	t_error	error;

	if (!is_map_elem(*nl->line)) // skip over cub data lines
		return (CLEAR);
	i = 0;
	error = CLEAR;
	while (nl->line[i] && !error)
		error = map_parser(game, nl->line[i++]);
	if (!error)
	{
		line_len = ft_strlen(nl->line);
		if (line_len < game->map.cols)
		{
			while (!error && line_len++ < game->map.cols)
				error = put_tile(game, OUTS);
		}
		game->map.rows++;
	}
	return (error);
}
