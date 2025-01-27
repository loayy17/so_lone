#include "so_long.h"

void	flood_fill(t_game *g, size_t x, size_t y, t_point *check)
{
	char	original;

	if (x >= g->width || y >= g->height
		|| g->map[y][x] == '1' || g->map[y][x] == 'F')
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

void	restore_map(t_game *g)
{
	size_t	i;
	size_t	j;
	size_t	k;

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
	k = -1;
	while (++k < g->collectible)
		g->map[g->collectibles[k].y][g->collectibles[k].x] = 'C';
}

size_t	calculate_collectibles(char **map)
{
	size_t	i;
	size_t	c;
	size_t	j;

	i = 0;
	c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			if (map[i][j++] == 'C')
				c++;
		i++;
	}
	return (c);
}

int	validate_solution(t_game *g)
{
	t_point	check;

	ft_bzero(&check,sizeof(t_point));
	flood_fill(g, g->player.x, g->player.y, &check);
	restore_map(g);
	return (check.x != g->collectible || check.y < 1);
}