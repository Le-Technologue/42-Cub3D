/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_builders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:05:48 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/07 16:44:03 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

t_error	put_tile(t_game *game, t_tile tile)
{
	return (vctr_push(game->map.grid, &tile));
}

t_error	put_plyr(t_game *game, t_tile tile)
{
	if (game->plyr.exists)
		return (ft_err_msg("You can't have several players on the map", PARSE));
	game->plyr.exists = true;
	game->plyr.orientation = tile;
	game->plyr.pos.row = game->map.rows;
	game->plyr.pos.col = game->map.grid->entries % game->map.cols;
	return (put_tile(game, VOID));
}
