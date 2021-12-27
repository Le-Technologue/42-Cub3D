/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 10:46:04 by wetieven          #+#    #+#             */
/*   Updated: 2021/12/27 14:29:50 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub_moves.h"

void	process_input(t_game *game)
{
	if (game->key[W].held && !game->key[S].held)
		longitudinal_move(game, FRWD);
	else if (game->key[S].held && !game->key[W].held)
		longitudinal_move(game, BKWD);
	if (game->key[A].held && !game->key[D].held)
		lateral_move(game, LTWD);
	else if (game->key[D].held && !game->key[W].held)
		lateral_move(game, RTWD);
	if (game->key[LFT].held && !game->key[RGT].held)
		rotation(game->fov, game->fov->cam, LTWD);
	else if (game->key[RGT].held && !game->key[LFT].held)
		rotation(game->fov, game->fov->cam, RTWD);
}

int	cub_key_release(int keycode, t_input *key)
{
	if (keycode == LFT_K)
		key[LFT].held = false;
	else if (keycode == RGT_K)
		key[RGT].held = false;
	else if (keycode == W_KEY)
		key[W].held = false;
	else if (keycode == A_KEY)
		key[A].held = false;
	else if (keycode == S_KEY)
		key[S].held = false;
	else if (keycode == D_KEY)
		key[D].held = false;
}

int	cub_key_press(int keycode, t_game *game)
{
	if (keycode == ESC_K)
		return (cub_shutdown(game));
	else if (keycode == LFT_K)
		game->key[LFT].held = true;
	else if (keycode == RGT_K)
		game->key[RGT].held = true;
	else if (keycode == W_KEY)
		game->key[W].held = true;
	else if (keycode == A_KEY)
		game->key[A].held = true;
	else if (keycode == S_KEY)
		game->key[S].held = true;
	else if (keycode == D_KEY)
		game->key[D].held = true;
}

void	cub_run_hooks(t_game *game)
{
	mlx_hook(game->fov->mlx.win, 2, 1L << 0, cub_key_press, game);
	mlx_hook(game->fov->mlx.win, 3, 1L << 1, cub_key_release, game->key);
	mlx_hook(game->fov->mlx.win, 17, 1L << 17, cub_shutdown, game);
	mlx_loop_hook(game->fov->mlx.lnk, cub_render_frame, game);
	mlx_loop(game->fov->mlx.lnk);
}

void	init_move_key_matrix(t_game *game)
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
