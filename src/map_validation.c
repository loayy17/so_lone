#include "so_long.h"

int	validate_name_map(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (len > 4 && !ft_strncmp(str + len - 4, ".ber", 4));
}

int	validate_dimension(char **map, size_t *w, size_t *h)
{
	size_t	width;
	size_t	i;

	i = 0;
	while (i < *h)
	{
		width = ft_strlen(map[i]);
		if (i++ > 0 && width != *w)
			return (1);
		*w = width;
	}
	return (0);
}

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
	const char	ch = g->map[i][j];

	if (ch == 'C')
	{
		g->collectibles[g->collectible].x = j;
		g->collectibles[g->collectible++].y = i;
	}
	else if (ch == 'P' && ++c[1])
	{
	g->player = (t_point){j, i};
	}
	else if (ch == 'E' && ++c[0])
		g->exit = (t_point){j, i};
	else if (!ft_strchr("01", ch))
		return (1);
	return (0);
}

int	validate_elements(t_game *g)
{
	size_t	c[2];
	size_t	i;
	size_t	j;

	ft_bzero(c, sizeof(size_t) * 2);
	g->collectible = calculate_collectibles(g->map);
	g->collectibles = malloc(g->collectible * sizeof(t_point));
	if (!g->collectibles)
		return (1);
	g->collectible = 0;
	i = -1;
	while (g->map[++i])
	{
		j = -1;
		while (g->map[i][++j])
			if (process_cell(g, i, j, c))
				return (free(g->collectibles), 1);
	}
	if (c[1] != 1 || c[0] != 1 || g->collectible < 1)
		return (free(g->collectibles), 1);
	return (0);
}
