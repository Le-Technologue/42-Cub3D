/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/07 16:56:57 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

t_error	cub_gnl_loop(t_game *game, t_cub_reader mode, t_newline *nl)
{
	t_error	error;

	error = CLEAR;
	game->map.rows == 0; //count rows twice as we parse for plyr positioning
	while (!error)
	{
		nl->status = get_next_line(nl->fd, &nl->line);
		if (nl->status >= 0)
			error = mode(game, nl->line, nl->status);
		free(&nl->line);
		if (nl->status <= 0)
			break ;
	}
	if (!error && mode == cub_data) //does this last check works ?
	{
		if (cub_chk(game->data) != CLEAR)
			return (ft_err_msg("The cub file is missing data.", PARSE));
		if (!game->map.rows)
			return (ft_err_msg("The cub file is missing a map.", PARSE));
		if (game->map.cols <= 2)
			error = ft_err_msg("Insufficient map width.", PARSE);
		if (game->map.rows <= 2)
			error = ft_err_msg("Insufficient map height.", PARSE);
	}
	return (error);
}

static t_error	cub_read_conf(t_game *game, const char *cub_path)
{
	t_error		error;
	t_newline	nl;

	if (fd_opener(cub_path, &nl->fd) != CLEAR)
	{
		ft_printf("Error\nThe map file path \"%s\" leads nowhere\n", map_path);
		return (FD_OPENING);
	}
	error = cub_gnl_loop(game, cub_data, &nl);
	fd_killer(nl->fd);
	if (error)
		return (error);
	if (fd_opener(cub_path, &nl->fd) != CLEAR)
		return (ft_err_msg("No luck. You can't open a lousy fd.", FD_OPENING));
	error = cub_gnl_loop(game, cub_map, &nl);
	fd_killer(nl->fd);
	return (error);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_fov	fov;
	t_error	error;

	if (ac != 2)
		return (ft_err_msg("USAGE : ./cub3d <MAP_PATH>.cub", PARSE));
	if (file_ext_chk(av[1], ".cub") != CLEAR)
		return (ft_err_msg("Config file extension must be \".cub\"", PARSE));
	error = CLEAR;

	// init game struct
	if (!error)
		error = cub_read_conf(game, av[1]);
	if (!error)
		// init fov struct upon success
	return (cub_shutdown(error));
}
