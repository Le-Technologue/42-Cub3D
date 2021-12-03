/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:29 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/03 18:14:25 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	cub_gnl_loop(t_game *game, t_cub_reader mode, t_nl_data *nl)
{
	t_error	error;

	error = CLEAR;
	while (!error)
	{
		nl->status = get_next_line(nl->fd, &nl->line);
		if (nl->status >= 0)
			error = mode(game, nl->line, nl->status);
		free(&nl->line);
		if (nl->status <= 0)
			break ;
	}
}

static t_error	cub_read_conf(t_game *game, const char *cub_path)
{
	t_error		error;
	t_nl_data	nl;

	if (fd_opener(cub_path, &nl->fd) != CLEAR)
	{
		ft_printf("Error\nThe map file path \"%s\" leads nowhere\n", map_path);
		return (FD_OPENING);
	}
	error = cub_gnl_loop(game, cub_data, &nl);
	fd_killer(nl->fd);
	if (error)
		return (error);
	error = cub_gnl_loop(game, cub_map, &nl);
	fd_killer(nl->fd);
	return (error);
}

int	main(int ac, char **av)
{
	t_game	game;

	cub_read_conf(game, av[1]);
}
