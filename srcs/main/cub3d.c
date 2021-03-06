/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:29 by wetieven          #+#    #+#             */
/*   Updated: 2022/01/04 09:13:59 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "cub_data.h"
#include "cub_map.h"
#include "cub_map_checks.h"
#include "cub_events.h"
#include "cub_travelling.h"
#include "cub_minimap.h"

t_error	cub_shutdown(t_game *game, t_error cause)
{
	int		i;
	t_txtr	*texture;

	if (cause == MEM_ALLOC)
		ft_printf("Error\nMemory saturated, consider closing Google Chrome.\n");
	vctr_exit(game->map.grid);
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
	if (game->fov->frm)
		mlx_destroy_image(game->fov->mlx.lnk, game->fov->frm->ptr);
	if (game->fov->mlx.win)
		mlx_destroy_window(game->fov->mlx.lnk, game->fov->mlx.win);
	exit(cause);
	return (cause);
}

static t_error	cub_launch_game(t_game *game, t_fov *fov)
{
	t_img	frm;

	fov->width = RESOL_WID;
	fov->height = RESOL_HEI;
	game->fov = fov;
	fov->mlx.win = mlx_new_window(fov->mlx.lnk, fov->width, fov->height,
			"cub3D");
	if (!fov->mlx.win)
		return (MEM_ALLOC);
	fov->frm = &frm;
	fov->frm->ptr = mlx_new_image(fov->mlx.lnk, fov->width, fov->height);
	fov->frm->addr = (int *)mlx_get_data_addr(fov->frm->ptr, &fov->frm->bpp,
			&fov->frm->line_size, &fov->frm->endian);
	if (!fov->frm->ptr)
	{
		mlx_destroy_window(fov->mlx.lnk, fov->mlx.win);
		return (MEM_ALLOC);
	}
	set_key_matrix(game);
	set_camera(&game->cam, &game->plyr);
	scale_minimap(fov, &game->map);
	cub_run_hooks(game);
	return (CLEAR);
}

t_error	cub_gnl_loop(t_game *game, t_cub_reader mode, t_newline *nl)
{
	t_error	error;

	error = CLEAR;
	nl->count = 0;
	nl->line = NULL;
	game->map.rows = 0;
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
		}
		if (!nl->line)
			return (ft_err_msg("There's something fishy with that cub file...",
					PARSE));
		free(nl->line);
		if (nl->status <= 0)
			break ;
	}
	return (error);
}

static t_error	cub_read_conf(t_game *game, const char *cub_path)
{
	t_error		error;
	t_newline	nl;

	if (fd_opener(cub_path, &nl.fd) != CLEAR)
	{
		ft_printf("Error\nThe map file path \"%s\" leads nowhere\n", cub_path);
		return (FD_OPENING);
	}
	error = cub_gnl_loop(game, cub_data, &nl);
	fd_killer(nl.fd);
	if (!error)
		error = chk_map_prerequisites(game);
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
	cub_data_init(&game, &fov);
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
