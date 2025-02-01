/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 06:36:32 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:37:10 by lalhindi         ###   ########.fr       */
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

void	fill_map_row(char **map, char *line, size_t row)
{
	size_t	i;

	i = 0;
	map[row] = malloc(ft_strlen(line) + 1);
	if (!map[row])
		exit_err("Malloc failed", NULL, NULL);
	while (line[i] && line[i] != '\n')
	{
		map[row][i] = line[i];
		i++;
	}
	map[row][i] = '\0';
}

int	read_map(char *file, char **map, int lines)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	i = 0;
	while (i < lines)
	{
		line = get_next_line(fd);
		if (!line || *line == '\0')
		{
			free(line);
			close(fd);
			return (0);
		}
		fill_map_row(map, line, i++);
		free(line);
	}
	close(fd);
	map[i] = NULL;
	return (i == lines);
}

void	load_images(t_game *g)
{
	int	ts;

	ts = TILE_SIZE;
	g->wall_img = mlx_xpm_file_to_image(g->mlx, WALL_IMAGE, &ts, &ts);
	g->floor_img = mlx_xpm_file_to_image(g->mlx, FLOOR_IMAGE, &ts, &ts);
	g->collectible_img = mlx_xpm_file_to_image(g->mlx, COLLECTIBLE_IMAGE, &ts,
			&ts);
	if (!g->wall_img || !g->floor_img || !g->collectible_img)
		exit_err("Failed to load Base images", g, NULL);
	load_player_anim(g);
	load_exit_anim(g);
	load_monster_images(g);
}

void	start_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_err("MLX init failed", g, NULL);
	g->win = mlx_new_window(g->mlx, g->width * TILE_SIZE, g->height * TILE_SIZE,
			"so_long");
	if (!g->win)
		exit_err("Window creation failed", g, NULL);
	load_images(g);
	draw_map(g);
	mlx_hook(g->win, DESTROY_WINDOW, EXIT_SUCCESS, close_window, g);
	mlx_hook(g->win, PRESS, RELEASE, handle_input, g);
	mlx_loop_hook(g->mlx, animation_loop, g);
	mlx_loop(g->mlx);
}
