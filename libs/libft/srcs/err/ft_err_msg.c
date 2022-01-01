/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:27:11 by wetieven          #+#    #+#             */
/*   Updated: 2021/10/26 14:18:20 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "err.h"

t_error	ft_err_msg(const char *msg, t_error cause)
{
	ft_printf("Error\n%s\n", msg);
	return (cause);
}
