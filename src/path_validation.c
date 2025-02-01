/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 06:14:46 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:14:47 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	flood_fill(t_game *g, size_t x, size_t y, t_point *check)
{
	char	original;

	if (x >= g->width || y >= g->height || g->map[y][x] == '1'
		|| g->map[y][x] == 'F')
		return ;
	original = g->map[y][x];
	g->map[y][x] = 'F';
	if (original == 'C')
		check->x++;
	else if (original == 'E')
		check->y++;
	flood_fill(g, x + 1, y, check);
	flood_fill(g, x - 1, y, check);
	flood_fill(g, x, y + 1, check);
	flood_fill(g, x, y - 1, check);
}

static void	restore_map_elements(t_game *g)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < g->height)
	{
		j = -1;
		while (++j < g->width)
			if (g->map[i][j] == 'F')
				g->map[i][j] = '0';
	}
	g->map[g->exit.y][g->exit.x] = 'E';
	g->map[g->player.y][g->player.x] = 'P';
}

static void	restore_collectibles(t_game *g)
{
	size_t	k;

	k = -1;
	while (++k < g->collectible)
		g->map[g->collectibles[k].y][g->collectibles[k].x] = 'C';
}

static void	restore_monsters(t_game *g)
{
	size_t	k;

	k = -1;
	while (++k < g->monster_counter)
		g->map[g->monsters[k].y][g->monsters[k].x] = 'M';
}

void	restore_map(t_game *g)
{
	restore_map_elements(g);
	restore_collectibles(g);
	restore_monsters(g);
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

int	validate_solution(t_game *g)
{
	t_point check;

	ft_bzero(&check, sizeof(t_point));
	flood_fill(g, g->player.x, g->player.y, &check);
	restore_map(g);
	if (check.x == g->collectible && check.y == 1)
		return (0);
	return (1);
}