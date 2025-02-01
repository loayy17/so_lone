/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:51:19 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 05:51:19 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *g, size_t i, size_t j)
{
	int		ts;
	void	*img;

	ts = TILE_SIZE;
	if (g->map[i][j] == '1')
		img = g->wall_img;
	else if (g->map[i][j] == 'C')
		img = g->collectible_img;
	else if (g->map[i][j] == 'P')
		img = g->player_img[g->player.dir][g->frame];
	else if (g->map[i][j] == 'M')
		img = g->monster_img[g->monsters->dir][g->monster_frame];
	else if (g->map[i][j] == 'E')
		img = g->exit_img[g->exit.dir][g->frame];
	else if (g->map[i][j] == '0')
		img = g->floor_img;
	else
		exit_err("Invalid map element", g, NULL);
	if (img)
		mlx_put_image_to_window(g->mlx, g->win, img, j * ts, i * ts);
}

void	draw_map(t_game *g)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < g->height)
	{
		j = -1;
		while (++j < g->width)
			draw_tile(g, i, j);
	}
	ft_put_steps(g, g->steps);
}
