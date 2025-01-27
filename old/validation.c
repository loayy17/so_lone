#include "includes/so_long.h"

int	validate_name_map(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (len > 4 && !ft_strncmp(str + len - 4, ".ber", 4));
}

void	fill_map_row(char **map, char *line, size_t row)
{
	size_t	i;

	i = 0;
	map[row] = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!map[row])
		exit(1);
	while (line[i] && line[i] != '\n')
	{
		map[row][i] = line[i];
		i++;
	}
	map[row][i] = '\0';
}

int	validate_dimention(char **map, size_t *old_width, size_t *height)
{
	size_t	width;
	size_t	height_2;

	height_2 = 0;
	while (height_2 < *height)
	{

		width = ft_strlen(map[height_2]);
		if (height_2 > 0 && width != *old_width)
			return (1);
		*old_width = width;
		height_2++;
	}
	return (0);
}

int	validate_wall(char **map, size_t width, size_t height)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (1);
		i++;
	}
	j = 0;
	while (j < height)
	{
		if (map[j][0] != '1' || map[j][width - 1] != '1')
			return (1);
		j++;
	}
	return (0);
}

static int	process_cell(t_game *g, size_t i, size_t j, size_t *e_p_p)
{
	const char	c = g->map[i][j];

	if (c == 'C')
	{
		g->collectibles[g->collectible].x = j;
		g->collectibles[g->collectible].y = i;
		g->collectible++;
	}
	else if (c == 'P')
	{
		e_p_p[1]++;
		g->player = (t_point){j, i};
	}
	else if (c == 'E')
	{
		e_p_p[0]++;
		g->exit = (t_point){j, i};
	}
	else if (!ft_strchr("01", c))
		return (1);
	return (0);
}

int	validate_elements(t_game *game)
{
	size_t		counts[2];
	size_t		i;
	size_t		j;

	ft_bzero(counts, sizeof(size_t) * 2);
	game->collectible = calculate_collectibles(game->map);
	game->collectibles = malloc(game->collectible * sizeof(t_point));
	if (!game->collectibles)
		return (1);
	game->collectible = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
			if (process_cell(game, i, j, counts))
				return (free(game->collectibles), 1);
	}
	if (counts[1] != 1 || counts[0] != 1 || game->collectible < 1)
		return (free(game->collectibles), 1);
	return (0);
}

void	flood_fill(t_game *game, size_t x, size_t y, t_point *check)
{
	char	original;

	if (x >= game->width || y >= game->height
		|| game->map[y][x] == '1' || game->map[y][x] == 'F')
		return ;
	original = game->map[y][x];
	game->map[y][x] = 'F';
	if (original == 'C')
		check->x++;
	else if (original == 'E')
		check->y++;
	flood_fill(game, x + 1, y, check);
	flood_fill(game, x - 1, y, check);
	flood_fill(game, x, y + 1, check);
	flood_fill(game, x, y - 1, check);
}

void	ft_destoy_images(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
}

int	close_window(t_game *game)
{
	ft_destoy_images(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	game_free(game, NULL, game->height);
	exit(0);
}


void	destroy_images(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
}

void	game_free(t_game *game, int *fd, int height)
{
	int		index;

	index = -1;
	while (++index < height)
		free(game->map[index]);
	free(game->map);
	if (fd)
		close(*fd);
	free(game->collectibles);
	game->collectibles = NULL;
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		destroy_images(game);
		free(game->mlx);
	}
	exit(1);
}


size_t	calculate_collectibles(char **map)
{
	size_t	i;
	size_t	collectible;
	size_t	j;

	i = 0;
	collectible = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				collectible++;
			j++;
		}
		i++;
	}
	return (collectible);
}

void	restore_map(t_game *game)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->map[i][j] == 'F')
				game->map[i][j] = '0';
			j++;
		}
		i++;
	}
	game->map[game->exit.y][game->exit.x] = 'E';
	// Restore collectibles
	k = 0;
	while (k < game->collectible)
	{
		game->map[game->collectibles[k].y][game->collectibles[k].x] = 'C';
		k++;
	}
}

int	validate_solution(t_game *game)
{
	t_point	check;

	check = (t_point){0, 0};
	flood_fill(game, game->player.x, game->player.y, &check);
	restore_map(game);
	return (check.x != game->collectible || check.y < 1);
}
