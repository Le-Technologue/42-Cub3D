/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:34:22 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/29 02:11:44 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub_data.h"
#include "cub_map_checks.h"

t_error	cub_completion(t_cub *cub)
{
	int	elem;

	elem = CUB_DATA_RANGE;
	while (elem--)
		if (cub[elem].ctnt == NULL)
			return (PARSE);
	return (CLEAR);
}

static t_error	textr(t_game *game, t_cub_key elem, char *line)
{
	t_txtr	*txtr;

	if (!ft_isspace(line[2]))
	{
		ft_printf("Error :\nA space should follow \"%s\".\n",
			game->data[elem].flag);
		return (PARSE);
	}
	txtr = malloc(sizeof(t_txtr));
	if (!txtr)
		return (MEM_ALLOC);
	txtr->img.ptr = mlx_xpm_file_to_image(game->fov->mlx.lnk, &line[3],
			&txtr->width, &txtr->height);
	if (!txtr->img.ptr)
	{
		ft_printf("\"%s\" isn't a valid xpm file or doesn't exists.", &line[3]);
		free(txtr);
		return (PARSE);
	}
	txtr->img.addr = (int *)mlx_get_data_addr(txtr->img.ptr, &txtr->img.bpp,
			&txtr->img.line_size, &txtr->img.endian);
	game->data[elem].ctnt = txtr;
	return (CLEAR);
}

static t_error	color(t_game *game, t_cub_key elem, char *line)
{
	int		*trgb;
	int		buf;
	int		octet;
	t_error	error;

	trgb = malloc(sizeof(int));
	if (!trgb)
		return (MEM_ALLOC);
	game->data[elem].ctnt = trgb;
	line += 2;
	octet = 3;
	error = CLEAR;
	while (!error && octet--)
	{
		buf = ptr_atoi(&line);
		if (buf < 0 || buf > 255 || (octet > 0 && *line != ',')
			|| (octet == 0 && *line != '\0'))
			error = PARSE;
		*trgb = buf << octet * 8;
		line++;
	}
	if (error)
		ft_printf("Error :\n%scolor's octet %d is not sound.\n",
			game->data[elem].flag, octet);
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
	return (measure_map(game, nl));
}
