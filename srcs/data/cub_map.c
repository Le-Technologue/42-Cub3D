/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:30:59 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/07 12:38:16 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_data.h"

bool	is_map_elem(char c)
{
	if (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (true);
	else
		return (false);
}

static t_error	map_parser(t_game *game, const char map_elem)
{
	t_tile				i;
	static t_pars_swtch	map_pars_set[] = {
		[OUTS] = {.flag = ' ', .parser = &put_outs},
		[VOID] = {.flag = '0', .parser = &put_void},
		[WALL] = {.flag = '1', .parser = &put_wall},
		[PL_N] = {.flag = 'N', .parser = &put_plyr},
		[PL_W] = {.flag = 'W', .parser = &put_plyr},
		[PL_S] = {.flag = 'S', .parser = &put_plyr},
		[PL_E] = {.flag = 'E', .parser = &put_plyr},
	};

	i = 0;
	while (i < TILE_RANGE)
	{
		if (map_elem == parser_set[i].flag)
			return ((parser_set[i].parser)(game, i));
		i++;
	}
	ft_printf("Error\nInvalid flag \"%c\" on row %lu col %lu.\n",
		map_elem, game->map.rows,
		game->map.grid->entries % game->map.cols);
	return (PARSE);
}

t_error	cub_map(t_game *game, const char *cub_line, t_newline *nl)
{
	size_t	line_len;

	// build row logic featured in slg
	while (*cub_line && !error)
		error = map_parser(game, *cub_line);
	if (error)
		return (error);
	line_len = ft_strlen(*cub_line);
	if (line_len < game->map.cols)
	{
		while (line_len++ < game->map.cols) //chk that arithmetic
			vctr_push(game->map.grid, OUTS);
	}
}
