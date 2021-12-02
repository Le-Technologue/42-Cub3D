/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/02 17:43:22 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

static t_error	cub_read_conf(t_game *game, const char *cub_path, )
{
	int		fd;
	char	*cub_line;
	t_error	error;
	int		gnl_status;

	if (fd_opener(cub_path, &fd) != CLEAR)
	{
		ft_printf("Error\nThe map file path \"%s\" leads nowhere\n", map_path);
		return (FD_OPENING);
	}
	error = CLEAR;
	while (!error)
	{
		gnl_status = get_next_line(fd, &cub_line);
		if (gnl_status >= 0)
			error = cub_parsing(game, cub_line, gnl_status);
		free(map_line);
		if (gnl_status <= 0)
			break ;
	}
	fd_killer(fd);
	return (error);
}
