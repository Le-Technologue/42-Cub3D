/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:37:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/17 11:46:26 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub_data.h"

t_error	textr(t_game *game, t_cub_key elem, char *line)
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
		return (PARSE);
	}
	txtr->img.addr = (int *)mlx_get_data_addr(txtr->img.ptr, &txtr->img.bpp,
			&txtr->img.line_size, &txtr->img.endian);
	game->data[elem].ctnt = txtr;
	return (CLEAR);
}

t_error	color(t_game *game, t_cub_key elem, char *line)
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
