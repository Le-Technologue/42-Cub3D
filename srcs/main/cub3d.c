/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/27 11:54:20 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "cub_data.h"
#include "cub_map.h"
#include "cub_map_checks.h"

t_error	cub_shutdown(t_game *game, t_error cause)
{
	int		i;
	t_txtr	*texture;

	if (cause == MEM_ALLOC)
		ft_printf("Error\nMemory saturated, consider closing Google Chrome.\n");
	i = CUB_DATA_RANGE;
	if (game->data)
	{
		while (i-- > FLO)
			if (game->data[i].ctnt != NULL)
				free(game->data[i].ctnt);
		while (i--)
		{
			texture = game->data[i].ctnt;
			if (game->data[i].ctnt != NULL)
				mlx_destroy_image(game->fov->mlx.lnk, texture->img.ptr);
		}
	}
	if (game->map.grid != NULL)
		vctr_exit(game->map.grid);
	//then some shit to take care of the fov, and before that some consideration whether to where we should put the fov structure wise
	return (cause);
}

static t_error	cub_launch_game(t_game *game, t_fov *fov)
{
	t_img	frm;

	game->fov = fov;
	// SCALE GRAPHICS ?
	fov->mlx.win = mlx_new_window(fov->mlx.lnk, fov->width, fov->height,
	if (!fov->mlx.win)
		return (MEM_ALLOC);
		"cub3D");
	fov->frm = &frm;
	fov->frm->ptr = mlx_new_image(fov->mlx.lnk, fov->width, fov->height);
	fov->frm->addr = (int *)mlx_get_data_addr(fov->frm->ptr, &fov->frm->bpp,
			&fov->frm->line_size, &fov->frm->endian);
	if (!fov->frm->ptr)
	{
		mlx_destroy_window(fov->mlx.lnk, fov->mlx.win);
		return (MEM_ALLOC);
	}
	init_move_key_matrix(game);
	cub_run_hooks(game);
	return (CLEAR);
}

t_error	cub_gnl_loop(t_game *game, t_cub_reader mode, t_newline *nl)
{
	t_error	error;

	error = CLEAR;
	nl->count = 0;
	game->map.rows = 0; //count rows twice as we parse for plyr positioning
	while (!error)
	{
		nl->status = get_next_line(nl->fd, &nl->line);
		if (nl->status >= 0)
		{
			nl->count++;
			if (mode == cub_map && nl->count < game->map_offset)
				;
			else
				error = mode(game, nl);
			free(nl->line); // are we sure of this
		}
		if (nl->status <= 0)
			break ;
	}
	if (!error && mode == cub_data)
	{
		if (cub_completion(game->data) != CLEAR)
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

	game->data = NULL;
	if (fd_opener(cub_path, &nl.fd) != CLEAR)
	{
		ft_printf("Error\nThe map file path \"%s\" leads nowhere\n", cub_path);
		return (FD_OPENING);
	}
	error = cub_gnl_loop(game, cub_data, &nl);
	fd_killer(nl.fd);
	if (error)
		return (error);
	if (fd_opener(cub_path, &nl.fd) != CLEAR)
		return (ft_err_msg("Memory full, we can't even open a fd.", MEM_ALLOC));
	if (vctr_init(&game->map.grid, sizeof(t_tile), 512) != CLEAR)
		return (MEM_ALLOC);
	error = cub_gnl_loop(game, cub_map, &nl);
	fd_killer(nl.fd);
	if (!error)
		error = map_breached(game);
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
	game.map.grid = NULL;
	game.map.cols = 0;
	game.map_offset = 0;
	game.plyr.exists = false;
	game.fov = &fov;
	fov.mlx.lnk = mlx_init();
	if (!fov.mlx.lnk)
		return (MEM_ALLOC);
	error = CLEAR;
	if (!error)
		error = cub_read_conf(&game, av[1]);
	if (!error)
		error = cub_launch_game(&game, &fov);
	return (cub_shutdown(&game, error));
}
