/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:30:13 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/30 14:22:15 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_data.h"
#include "cub_map.h"
#include "cub_map_checks.h"

bool	is_map_elem(char c)
{
	if (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (true);
	else
		return (false);
}

t_error	measure_map(t_game *game, t_newline *nl)
{
	t_error			error;

	if (*nl->line == '\0')
		return (CLEAR);
	error = CLEAR;
	if (cub_completion(game->data) != CLEAR)
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

static int	map_fill(t_map map, size_t col, size_t row, t_tile fill)
{
	int		c;
	int		r;
	t_error	error;

	if (col >= map.cols || row >= map.rows || *tile(&map, col, row) == OUTS)
	{
		ft_printf("Error:\nMap breach found around col %i row %i\n", col, row);
		return (PARSE);
	}
	else if (*tile(&map, col, row) == WALL || *tile(&map, col, row) == fill)
		return (CLEAR);
	*tile(&map, col, row) = fill;
	error = CLEAR;
	r = -1;
	while (!error && r <= 1)
	{
		c = -1;
		while (!error && c <= 1)
		{
			error = map_fill(map, col + c, row + r, fill);
			c++;
		}
		r++;
	}
	return (error);
}

t_error	map_breached(t_game *game)
{
	t_error	error;

	/* ft_printf("Parsed map :\n"); //TESTING */
	/* print_map_vctr(game->map); // TESTING */
	error = map_fill(game->map, game->plyr.pos.col, game->plyr.pos.row, FILL);
	/* ft_printf("Map fill :\n"); //TESTING */
	/* print_map_vctr(game->map); //TESTING */
	if (error)
		return (error);
	map_fill(game->map, game->plyr.pos.col, game->plyr.pos.row, VOID);
	return (CLEAR);
}

t_error	chk_map_prerequisites(t_game *game)
{
	t_error	error;

	error = CLEAR;
	if (cub_completion(game->data) != CLEAR)
		return (ft_err_msg("The cub file is missing data.", PARSE));
	if (!game->map.rows)
		return (ft_err_msg("The cub file is missing a map.", PARSE));
	if (game->map.cols <= 2)
		error = ft_err_msg("Insufficient map width.", PARSE);
	if (game->map.rows <= 2)
		error = ft_err_msg("Insufficient map height.", PARSE);
	return (error);
}

void	print_map_vctr(t_map map) // Map parsing tester
{
	size_t	c;
	size_t	r;

	r = 0;
	while (r < map.rows)
	{
		c = 0;
		while (c < map.cols)
			ft_printf("%i", *tile(&map, c++, r));
		ft_printf("\n");
		r++;
	}
	ft_printf("\n");
}
