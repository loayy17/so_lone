/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:51:43 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 05:51:43 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_wall(char **map, size_t w, size_t h)
{
	size_t	i;

	i = 0;
	while (i < w)
		if (map[0][i] != '1' || map[h - 1][i++] != '1')
			return (1);
	i = 0;
	while (i < h)
		if (map[i][0] != '1' || map[i++][w - 1] != '1')
			return (1);
	return (0);
}

static int	process_cell(t_game *g, size_t i, size_t j, size_t *c)
{
	char	ch;

	ch = g->map[i][j];
	if (ch == 'C')
	{
		g->collectibles[g->collectible].x = j;
		g->collectibles[g->collectible].y = i;
		g->collectible++;
	}
	else if (ch == 'P' && ++c[1])
		g->player = (t_element){j, i, 0};
	else if (ch == 'E' && ++c[0])
		g->exit = (t_element){j, i, 0};
	else if (ch == 'M')
	{
		g->monsters[g->monster_counter].x = j;
		g->monsters[g->monster_counter].y = i;
		g->monsters[g->monster_counter].dir = rand() % 4;
		g->monster_counter++;
	}
	else if (!ft_strchr("01", ch))
		return (1);
	return (0);
}

static int	init_entities(t_game *g)
{
	g->collectible = count_entities(g->map, 'C', g->height, g->width);
	g->monster_counter = count_entities(g->map, 'M', g->height, g->width);
	g->collectibles = malloc(g->collectible * sizeof(t_point));
	g->monsters = malloc(g->monster_counter * sizeof(t_element));
	if (!g->collectibles || !g->monsters)
	{
		if (g->collectibles)
			free(g->collectibles);
		if (g->monsters)
			free(g->monsters);
		return (1);
	}
	g->collectible = 0;
	g->monster_counter = 0;
	return (0);
}

int	validate_map_elements(t_game *g, size_t *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (process_cell(g, i, j, c))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_elements(t_game *g)
{
	size_t	c[2];

	c[0] = 0;
	c[1] = 0;
	if (init_entities(g))
		exit_err("Malloc failed", g, NULL);
	if (validate_map_elements(g, c))
		exit_err("Invalid map element", g, NULL);
	if (c[1] == 1 && c[0] == 1 && g->collectible > 1)
		return (0);
	exit_err("Invalid map configuration elements", g, NULL);
	return (1);
}
