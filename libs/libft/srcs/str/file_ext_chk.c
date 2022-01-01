/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ext_chk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:46:17 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/03 11:54:15 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "err.h"

t_error	file_ext_chk(const char *file_name, const char *extension)
{
	size_t	name_len;
	size_t	ext_len;
	char	*checked;

	name_len = ft_strlen(file_name);
	ext_len = ft_strlen(extension);
	if (name_len < ext_len)
		return (PARSE);
	checked = ft_substr(file_name, name_len - ext_len, ext_len);
	if (ft_strncmp(extension, checked, ext_len) != 0)
	{
		free(checked);
		return (PARSE);
	}
	free(checked);
	return (CLEAR);
}
