/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 08:44:09 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/20 07:44:01 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DATA_H
# define CUB_DATA_H

# include "libft.h"
# include "cub3d.h"

typedef t_error	(*t_cub_reader)(t_game *game, t_newline *nl);

t_error	cub_completion(t_cub *cub);
t_error	cub_data(t_game *game, t_newline *nl);

#endif
