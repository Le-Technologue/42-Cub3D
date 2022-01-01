/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_opener.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:09:19 by wetieven          #+#    #+#             */
/*   Updated: 2021/10/26 14:15:13 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "err.h"

t_error	fd_opener(const char *file_path, int *fd)
{
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
		return (FD_OPENING);
	return (CLEAR);
}
