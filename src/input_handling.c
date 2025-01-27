#include "so_long.h"

int	handle_input(int key, t_game *g)
{
	if (key == KEY_ESC || key == KEY_Q)
		close_window(g);
	else if (key == KEY_W)
		ft_printf("Move up\n");
	else if (key == KEY_S)
		ft_printf("Move down\n");
	else if (key == KEY_A)
		ft_printf("Move left\n");
	else if (key == KEY_D)
		ft_printf("Move right\n");
	return (0);
}

int	close_window(t_game *g)
{
	game_free(g, NULL, g->height);
	exit(0);
}