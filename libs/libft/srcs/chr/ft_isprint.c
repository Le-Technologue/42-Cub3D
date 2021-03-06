/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:33:26 by wetieven          #+#    #+#             */
/*   Updated: 2020/12/03 18:39:16 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (' ' <= c && c <= '~');
}
