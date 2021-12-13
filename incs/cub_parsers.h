/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:20:06 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/13 11:24:10 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_PARSERS_H
# define CUB_PARSERS_H

# include "cub3d.h"

t_error	textr(t_game *game, t_cub_key elem, t_newline *nl);
t_error	color(t_game *game, t_cub_key elem, t_newline *nl);

#endif
