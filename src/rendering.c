#include "so_long.h"

static void	draw_tile(t_game *g, size_t i, size_t j)
{
	const int	ts = TILE_SIZE;
	void		*img;
	if (g->map[i][j] == '1')
		img = g->wall_img;
	else if (g->map[i][j] == 'C')
		img = g->collectible_img;
	else if (g->map[i][j] == 'E')
		img = g->exit_img;
	else if (g->map[i][j] == 'P')
		img = g->player_img;
	else if(g->map[i][j] == '0')
		img = g->floor_img;
	else
		return ;
	mlx_put_image_to_window(g->mlx, g->win, img, j * ts, i * ts);
}

void	draw_map(t_game *g)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	while (i < g->height)
	{
		j = 0;
		while (j < g->width)
		{
			draw_tile(g, i, j);
			j++;
		}
		i++;	
	}
}