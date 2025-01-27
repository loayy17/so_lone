#include "so_long.h"

void	destroy_images(t_game *g)
{
	if (g->wall_img)
		mlx_destroy_image(g->mlx, g->wall_img);
	if (g->player_img)
		mlx_destroy_image(g->mlx, g->player_img);
	if (g->exit_img)
		mlx_destroy_image(g->mlx, g->exit_img);
	if (g->collectible_img)
		mlx_destroy_image(g->mlx, g->collectible_img);
	if (g->floor_img)
		mlx_destroy_image(g->mlx, g->floor_img);
}

void	game_free(t_game *g, int *fd, int h)
{
	int	i;

	i = -1;
	if (g->map)
	{
		while (++i < h)
			free(g->map[i]);
		free(g->map);
	}
	if (g->collectibles)
		free(g->collectibles);
	if (fd)
		close(*fd);
	if (g->mlx)
	{
		destroy_images(g);
		if (g->win)
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