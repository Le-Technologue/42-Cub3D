/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:30:13 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/20 07:45:18 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
		return (CLEAR); //just an empty line is valid, keep going
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

static int	map_fill(t_map map, size_t col, size_t row)
{
	if (col >= map.cols || row >= map.rows)
		return (ERROR);
	/* if (*tile(&map, col, row) == OUTS) */
	/* 	return (ft_err_msg("Spaces aren't valid inside the map walls", ERROR)); */
	else if (*tile(&map, col, row) == WALL)
		return (CLEAR);
	*tile(&map, col, row) = WALL;
	return (map_fill(map, col - 1, row - 1)
			+ map_fill(map, col, row - 1)
			+ map_fill(map, col + 1, row - 1)
			+ map_fill(map, col - 1, row)
			+ map_fill(map, col + 1, row)
			+ map_fill(map, col - 1, row + 1)
			+ map_fill(map, col, row + 1)
			+ map_fill(map, col + 1, row + 1));
}
