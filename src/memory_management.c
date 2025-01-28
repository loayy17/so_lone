#include "so_long.h"
void map_free(t_game *g,int h)
{
    int i;

    i = -1;
    while (++i < h)
            if (g->map[i])
                free(g->map[i]);
        free(g->map);
}

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

void game_free(t_game *g, int *fd, int h)
{
    if (g->collectibles)
    {
        free(g->collectibles);
    }
    if (g->map)
        map_free(g,h);
    if (fd)
    {
        close(*fd);
    }
    if (g->mlx)
    {
        destroy_images(g);
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