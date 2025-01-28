#include "so_long.h"

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
		if (!line || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		fill_map_row(map, line, i++);
		free(line);
	}
	map[i] = NULL;
	close(fd);
	return (i == lines);
}

void	load_images(t_game *g)
{
	int	ts;

	ts = TILE_SIZE;
	g->wall_img = mlx_xpm_file_to_image(g->mlx, WALL_IMAGE, &ts, &ts);
	if (!g->wall_img)
		exit_err("Failed to load wall image", g, NULL);
	g->floor_img = mlx_xpm_file_to_image(g->mlx, FLOOR_IMAGE, &ts, &ts);
	if (!g->floor_img)
		exit_err("Failed to load floor image", g, NULL);
	g->player_img = mlx_xpm_file_to_image(g->mlx, P_DOWN_0, &ts, &ts);
	if (!g->player_img)
		exit_err("Failed to load player image", g, NULL);
	g->exit_img = mlx_xpm_file_to_image(g->mlx, EXIT_IMAGE_CLOSE, &ts, &ts);
	if (!g->exit_img)
		exit_err("Failed to load exit image", g, NULL);
	g->collectible_img = mlx_xpm_file_to_image(g->mlx, COLLECTIBLE_IMAGE, &ts, &ts);
	if (!g->collectible_img)
		exit_err("Failed to load collectible image", g, NULL);
}

void	start_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_err("MLX init failed", g, NULL);
	g->win = mlx_new_window(g->mlx, g->width * TILE_SIZE,
			g->height * TILE_SIZE, "so_long");
	if (!g->win)
		exit_err("Window creation failed", g, NULL);
	load_images(g);
	draw_map(g);
	mlx_hook(g->win,DESTROY_WINDOW, EXIT_SUCCESS, close_window, g);
	mlx_hook(g->win,PRESS,RELEASE, handle_input, g);
	mlx_loop_hook(g->mlx, ft_animation_player, g);
	mlx_loop(g->mlx);
}
