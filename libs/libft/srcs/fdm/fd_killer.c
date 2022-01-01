/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_killer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 10:05:20 by wetieven          #+#    #+#             */
/*   Updated: 2021/10/26 14:15:25 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "err.h"

t_error	fd_killer(int fd)
{
	if (close(fd) == -1)
		return (FD_CLOSING);
	return (CLEAR);
}
