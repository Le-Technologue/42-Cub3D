/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 10:46:04 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/30 13:52:18 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "cub_travelling.h"
#include "cub_render.h"

static int	cub_close_win(t_game *game)
{
	cub_shutdown(game, CLEAR);
	return (0);
}

static int	cub_key_release(int keycode, t_input *key)
{
	if (keycode == LFT_K)
		key[LFT].held = false;
	else if (keycode == RGT_K)
		key[RGT].held = false;
	else if (keycode == W_KEY || keycode == UP_KY)
		key[W].held = false;
	else if (keycode == A_KEY)
		key[A].held = false;
	else if (keycode == S_KEY || keycode == DWN_K)
		key[S].held = false;
	else if (keycode == D_KEY)
		key[D].held = false;
	return (0);
}

static int	cub_key_press(int keycode, t_game *game)
{
	if (keycode == ESC_K)
		return (cub_close_win(game));
	else if (keycode == LFT_K)
		game->key[LFT].held = true;
	else if (keycode == RGT_K)
		game->key[RGT].held = true;
	else if (keycode == W_KEY || keycode == UP_KY)
		game->key[W].held = true;
	else if (keycode == A_KEY)
		game->key[A].held = true;
	else if (keycode == S_KEY || keycode == DWN_K)
		game->key[S].held = true;
	else if (keycode == D_KEY)
		game->key[D].held = true;
	return (0);
}

void	cub_run_hooks(t_game *game)
{
	mlx_hook(game->fov->mlx.win, 2, 1L << 0, cub_key_press, game);
	mlx_hook(game->fov->mlx.win, 3, 1L << 1, cub_key_release, game->key);
	mlx_hook(game->fov->mlx.win, 17, 1L << 17, cub_close_win, game);
	mlx_loop_hook(game->fov->mlx.lnk, cub_render_frame, game);
	mlx_loop(game->fov->mlx.lnk);
}

void	set_key_matrix(t_game *game)
{
	static t_input	move_keyboard[] = {
	[LFT] = {.held = false, .keycode = LFT_K},
	[RGT] = {.held = false, .keycode = RGT_K},
	[W] = {.held = false, .keycode = W_KEY},
	[A] = {.held = false, .keycode = A_KEY},
	[S] = {.held = false, .keycode = S_KEY},
	[D] = {.held = false, .keycode = D_KEY},
	};

	game->key = move_keyboard;
}
