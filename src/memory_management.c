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
