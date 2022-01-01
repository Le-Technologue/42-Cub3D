/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:11:12 by wetieven          #+#    #+#             */
/*   Updated: 2021/11/17 16:18:40 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CNV_H
# define CNV_H

# include "err.h"

/*
** String to number conversion
*/
int		ft_atoi(const char *str);
int		ptr_atoi(char **str);
long	ft_atol_base(const char *str, const char *base);
long	ptr_atol_base(char **str, const char *base);
t_error	prs_strtol(long *res, char **str, long min, long max);

/*
** Number to string conversion
*/
char	*ft_itoa(int nb);
char	*ft_ltoa_base(long lnb, const char *base);
char	*ft_sztoa_base(unsigned long nb, const char *base);

/*
** System boundaries check
*/
void	ft_print_limits(void);

#endif
