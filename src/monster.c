/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 06:15:03 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:15:04 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_move(t_game *g, size_t x, size_t y)
{
	return (x > 0 && x < g->width - 1 && y > 0 && y < g->height - 1
		&& g->map[y][x] != '1' && g->map[y][x] != 'E' && g->map[y][x] != 'C');
}

static void	load_monster_dir_anim(t_game *g, int ts, int dir)
{
	char	*paths[ANIM_FRAMES];
	int		i;

	if (dir == 0)
		ft_draw_monster_up(paths);
	else if (dir == 1)
		ft_draw_monster_down(paths);
	else if (dir == 2)
		ft_draw_monster_left(paths);
	else if (dir == 3)
		ft_draw_monster_right(paths);
	i = 0;
	while (i < ANIM_FRAMES)
	{
		g->monster_img[dir][i] = mlx_xpm_file_to_image(g->mlx, paths[i], &ts,
				&ts);
		if (!g->monster_img[dir][i])
			exit_err("Monster animation load failed", g, NULL);
		i++;
	}
}

void	load_monster_images(t_game *g)
{
	const int	ts = TILE_SIZE;
	int			dir;

	dir = 0;
	while (dir < 4)
	{
		load_monster_dir_anim(g, ts, dir);
		dir++;
	}
}

static void	update_monster_position(t_game *g, size_t i)
{
	int	new_x;
	int	new_y;

	new_x = g->monsters[i].x;
	new_y = g->monsters[i].y;
	if (g->monsters[i].dir == 0)
		new_y--;
	else if (g->monsters[i].dir == 1)
		new_y++;
	else if (g->monsters[i].dir == 2)
		new_x--;
	else if (g->monsters[i].dir == 3)
		new_x++;
	if (is_valid_move(g, new_x, new_y))
	{
		if (g->map[new_y][new_x] == 'P')
			game_over(g);
		g->map[g->monsters[i].y][g->monsters[i].x] = '0';
		g->monsters[i].x = new_x;
		g->monsters[i].y = new_y;
		g->map[new_y][new_x] = 'M';
	}
	else
		g->monsters[i].dir = rand() % 4;
}

void	move_monsters(t_game *g)
{
	size_t	i;

	if (++g->monster_speed < MOVE_SPEED / g->monster_counter)
		return ;
	g->monster_speed = 0;
	i = 0;
	while (i < g->monster_counter)
	{
		update_monster_position(g, i);
		i++;
	}
}
