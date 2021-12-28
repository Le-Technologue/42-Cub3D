/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_events.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 11:31:32 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/28 11:33:53 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_EVENTS_H
# define CUB_EVENTS_H

void	process_input(t_game *game);
void	cub_run_hooks(t_game *game);
void	set_key_matrix(t_game *game);

#endif
