/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-01 10:08:30 by lalhindi          #+#    #+#             */
/*   Updated: 2025-02-01 10:08:30 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_free(t_game *g, int h)
{
	int	i;

	i = -1;
	while (++i < h)
	{
		if (g->map[i])
			free(g->map[i]);
	}
	free(g->map);
}

size_t	count_entities(char **map, char c, size_t h, size_t w)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
			if (map[i][j++] == c)
				count++;
		i++;
	}
	return (count);
}

void	game_free(t_game *g, int *fd, int h)
{
	if (g->collectibles)
		free(g->collectibles);
	if (g->monsters)
		free(g->monsters);
	if (g->map)
		map_free(g, h);
	if (g->valid_path)
		free(g->valid_path);
	if (fd)
		close(*fd);
	if (g->mlx)
	{
		destroy_images(g);
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

void	exit_err(char *msg, t_game *g, int *fd)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (g)
		game_free(g, fd, g->height);
	else if (fd)
		close(*fd);
	exit(1);
}

void	render_monsters(t_game *g)
{
	int		ts;
	size_t	i;

	if (++g->monster_speed < MOVE_SPEED / g->monster_counter)
		return ;
	g->monster_speed = 0;
	g->anim_frame = (g->anim_frame + 1) % ANIM_FRAMES;
	ts = TILE_SIZE;
	i = 0;
	while (i < g->monster_counter)
	{
		mlx_put_image_to_window(g->mlx, g->win,
			g->monster_img[g->monsters[i].dir][g->anim_frame], g->monsters[i].x
			* ts, g->monsters[i].y * ts);
		i++;
	}
}
