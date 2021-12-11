/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:37:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/11 16:37:35 by wetieven         ###   ########lyon.fr   */
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

t_error	color(char **line, t_cub_data elem, t_cub *cub)
{
	int	*trgb;
	int buf;
&txtrs
	if (!alloc_safe(trgb, sizeof(int), 1, heap_top())
		return (mem_alloc);
	buf = ptr_atoi(line);
	if (buf < 0 || buf > 255)
		return (parse);
	*trgb = buf << 16;
	buf = ptr_atoi(line);
	if (buf < 0 || buf > 255)
		return (parse);
	*trgb = buf << 8;
	buf = ptr_atoi(line);
	if (buf < 0 || buf > 255)
		return (parse);
	*trgb = buf;
	cub[elem]->(int *)ctnt = trgb;
	return (clear);
}
