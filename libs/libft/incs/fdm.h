/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:36:49 by wetieven          #+#    #+#             */
/*   Updated: 2021/10/26 14:16:21 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDM_H
# define FDM_H

# include "err.h"
# include "vct.h"

t_error	fd_opener(const char *file_path, int *fd);
t_error	fd_to_vctr(t_vctr *vct, int fd, size_t buf_size);
int		gnl_to_vctr(t_vctr **vct, int fd);
t_error	fd_killer(int fd);

#endif
