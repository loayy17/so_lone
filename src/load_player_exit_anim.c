/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player_anim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-01 09:17:09 by lalhindi          #+#    #+#             */
/*   Updated: 2025-02-01 09:17:09 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_element_images(char *element_images[], int dir)
{
	if (dir == 4)
	{
		ft_draw_exit(element_images, 0);
	}
	else if (dir == 5)
	{
		ft_draw_exit(element_images, 1);
	}
}

static void	load_player_dir_anim(t_game *g, int ts, int dir)
{
	char	*paths[ANIM_FRAMES];
	int		i;

	if (dir == 0)
		ft_draw_player_up(paths);
	else if (dir == 1)
		ft_draw_player_down(paths);
	else if (dir == 2)
		ft_draw_player_left(paths);
	else if (dir == 3)
		ft_draw_player_right(paths);
	i = 0;
	while (i < ANIM_FRAMES)
	{
		g->player_img[dir][i] = mlx_xpm_file_to_image(g->mlx, paths[i], &ts,
				&ts);
		if (!g->player_img[dir][i])
			exit_err("Player animation load failed", g, NULL);
		i++;
	}
}

void	load_player_anim(t_game *g)
{
	const int	ts = TILE_SIZE;
	int			dir;

	dir = 0;
	while (dir < 4)
	{
		load_player_dir_anim(g, ts, dir);
		dir++;
	}
}

static void	load_exit_status_anim(t_game *g, int ts, int status)
{
	char	*paths[ANIM_FRAMES];
	int		i;

	i = 0;
	ft_draw_exit(paths, status);
	while (i < ANIM_FRAMES)
	{
		g->exit_img[status][i] = mlx_xpm_file_to_image(g->mlx, paths[i], &ts,
				&ts);
		if (!g->exit_img[status][i])
			exit_err("Exit animation load failed", g, NULL);
		i++;
	}
}

void	load_exit_anim(t_game *g)
{
	int	ts;
	int	status;

	ts = TILE_SIZE;
	status = 0;
	while (status < 2)
	{
		load_exit_status_anim(g, ts, status);
		status++;
	}
}
