/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:37:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/11 18:09:11 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub_data.h"

t_error	textr(t_game *game, t_cub_key elem, t_newline *nl)
{
	t_txtr	*txtr;

	nl->line += 2;
	if (ft_isspace(*nl->line))
		nl->line++;
	else
	{
		ft_printf("Error :\nA space should follow \"%s\".\n", cub[elem].flag);
		return (PARSE);
	}
	txtr = malloc(sizeof(t_txtr));
	if (!txtr)
		return (MEM_ALLOC);
	txtr->img.ptr = mlx_xpm_file_to_image(game->fov.mlx.lnk, nl->line,
			&txtr->width, &txtr->height);
	if (!txtr->img.ptr)
	{
		ft_printf("\"%s\" isn't a valid xpm file or doesn't exists.", nl->line);
		return (PARSE);
	}
	txtr->img.addr = (int *)mlx_get_data_addr(txtr->img.ptr, &txtr->img.bpp
			&txtr->img.line_size, &txtr->img.endian);
	game->cub[elem].ctnt = txtr;
	return (CLEAR);
}

t_error	color(t_game *game, t_cub_key elem, t_newline *nl)
{
	int		*trgb;
	int		buf;
	int		octet;
	t_error	error;

	trgb = malloc(sizeof(int));
	if (!trgb)
		return (MEM_ALLOC);
	game->cub[elem].ctnt = trgb;
	octet = 3;
	error = CLEAR;
	while (!error && octet--)
	{
		buf = ptr_atoi(&nl->line);
		if (buf < 0 || buf > 255 || (octet > 0 && *nl->line != ',')
			|| (octet == 0 && *nl->line != '\0'))
			error = PARSE;
		*trgb = *buf << octet * 8;
		nl->line++;
	}
	if (error)
		ft_printf("Error :\n%s color's octet %d is not sound.\n",
			game->cub[elem].flag, octet);
	return (error);
}
