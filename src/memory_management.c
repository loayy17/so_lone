/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 06:15:27 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:15:28 by lalhindi         ###   ########.fr       */
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

void	destroy_basic_images(t_game *g)
{
	if (g->wall_img)
		mlx_destroy_image(g->mlx, g->wall_img);
	if (g->floor_img)
		mlx_destroy_image(g->mlx, g->floor_img);
	if (g->collectible_img)
		mlx_destroy_image(g->mlx, g->collectible_img);
}

void	destroy_exit_images(t_game *g)
{
	int	i;
	int	dir;

	dir = -1;
	while (++dir < 2)
	{
		i = -1;
		while (++i < ANIMATION_FRAMES)
		{
			if (g->exit_img[dir][i])
				mlx_destroy_image(g->mlx, g->exit_img[dir][i]);
		}
	}
}

void	destroy_player_images(t_game *g)
{
	int	i;
	int	dir;

	dir = -1;
	while (++dir < 4)
	{
		i = -1;
		while (++i < ANIMATION_FRAMES)
		{
			if (g->player_img[dir][i])
				mlx_destroy_image(g->mlx, g->player_img[dir][i]);
		}
	}
}

void	destroy_monster_images(t_game *g)
{
	int	i;
	int	dir;

	dir = -1;
	while (++dir < 4)
	{
		i = -1;
		while (++i < ANIMATION_FRAMES)
		{
			if (g->monster_img[dir][i])
				mlx_destroy_image(g->mlx, g->monster_img[dir][i]);
		}
	}
}

void	destroy_images(t_game *g)
{
	destroy_basic_images(g);
	destroy_exit_images(g);
	destroy_player_images(g);
	destroy_monster_images(g);
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