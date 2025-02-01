/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:51:12 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:37:31 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_player(t_game *g, int dir, int frame)
{
	int	width;
	int	height;

	if (g->player_img[dir][frame])
		mlx_destroy_image(g->mlx, g->player_img[dir][frame]);
	g->player_img[dir][frame] = mlx_xpm_file_to_image(g->mlx,
			g->player_img[dir][frame], &width, &height);
	if (!g->player_img[dir][frame])
		exit_err("Error\nPlayer image not found\n", g, NULL);
	mlx_put_image_to_window(g->mlx, g->win, g->player_img[dir][frame],
		g->player.x * TILE_SIZE, g->player.y * TILE_SIZE);
}

void	ft_move_player(t_game *g, int x, int y)
{
	char	next_pos;

	next_pos = g->map[g->player.y + y][g->player.x + x];
	if (next_pos == '1')
		return ;
	if (next_pos == 'M')
		game_over(g);
	if (next_pos == 'C')
		g->collectible--;
	if (g->collectible == 0)
		g->exit.dir = 1;
	if (next_pos == 'E' && g->collectible == 0)
		ft_win_game(g);
	g->map[g->player.y][g->player.x] = '0';
	g->player.x += x;
	g->player.y += y;
	g->map[g->player.y][g->player.x] = 'P';
	if (!(g->player.y == g->exit.y) || !(g->player.x == g->exit.x))
		g->map[g->exit.y][g->exit.x] = 'E';
	++g->steps;
}

int	handle_input(int key, t_game *g)
{
	if (key == KEY_ESC || key == KEY_Q)
		close_window(g);
	else if (key == KEY_UP || key == KEY_W)
	{
		ft_move_player(g, 0, -1);
		g->player.dir = 0;
	}
	else if (key == KEY_DOWN || key == KEY_S)
	{
		ft_move_player(g, 0, 1);
		g->player.dir = 1;
	}
	else if (key == KEY_LEFT || key == KEY_A)
	{
		ft_move_player(g, -1, 0);
		g->player.dir = 2;
	}
	else if (key == KEY_RIGHT || key == KEY_D)
	{
		ft_move_player(g, 1, 0);
		g->player.dir = 3;
	}
	return (0);
}

void	player_render(t_game *g)
{
	if (g->monster_counter == 0)
	{
		if (++g->player_speed < 500)
			return ;
	}
	else if (++g->player_speed < 500 / g->monster_counter)
	{
		return ;
	}
	g->player_speed = 0;
	g->frame = (g->frame + 1) % ANIMATION_FRAMES;
}

int	animation_loop(t_game *g)
{
	if (g->monster_counter)
	{
		render_monsters(g);
		move_monsters(g);
	}
	draw_map(g);
	player_render(g);
	ft_put_steps(g, g->steps);
	return (0);
}
