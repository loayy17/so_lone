#include "so_long.h"
void ft_move_player(t_game *g, int x, int y)
{
    char next_pos = g->map[g->player.y + y][g->player.x + x];

    if (next_pos == '1')
        return;

    if (next_pos == 'C')
        g->collectible--;
    if (next_pos == 'E' && g->collectible == 0)
    {
        close_window(g);
    }

    g->map[g->player.y][g->player.x] = '0'; // Set the current position to empty
    g->player.x += x;
    g->player.y += y;
    g->map[g->player.y][g->player.x] = 'P';
	if(!(g->player.y == g->exit.y) || !(g->player.x == g->exit.x))
		g->map[g->exit.y][g->exit.x] = 'E';
    // Redraw the map
	printf("collectibles: %ld\n", g->collectible);
    draw_map(g);
}


int	handle_input(int key, t_game *g)
{
	if (key == KEY_ESC || key == KEY_Q) close_window(g);
	else if (key == KEY_W) ft_move_player(g, 0, -1);
	else if (key == KEY_S) ft_move_player(g, 0, 1);
	else if (key == KEY_A) ft_move_player(g, -1, 0);
	else if (key == KEY_D) ft_move_player(g, 1, 0);
	return (0);
}

int	close_window(t_game *g)
{
	game_free(g, NULL, g->height);
	exit(0);
}