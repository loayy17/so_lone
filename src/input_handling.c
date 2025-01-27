#include "so_long.h"
void ft_move_player(t_game *g, int x, int y)
{
    char next_pos;

    next_pos = g->map[g->player.y + y][g->player.x + x];
    if (next_pos == '1')
        return;
    if (next_pos == 'C')
        g->collectible--;
    if(g->collectible == 0)
    {
        g->exit_img = NULL;
        int width, height;
        g->exit_img = mlx_xpm_file_to_image(g->mlx, EXIT_IMAGE_OPEN, &width, &height);
        if (g->exit_img == NULL)
            exit_err("Error\nExit image not found\n", g,NULL);
        mlx_put_image_to_window(g->mlx, g->win, g->exit_img, g->exit.x * 50, g->exit.y * 50);
    }    
    if (next_pos == 'E' && g->collectible == 0)
        close_window(g);
    g->map[g->player.y][g->player.x] = '0';
    g->player.x += x;
    g->player.y += y;
    g->map[g->player.y][g->player.x] = 'P';
	if(!(g->player.y == g->exit.y) || !(g->player.x == g->exit.x))
		g->map[g->exit.y][g->exit.x] = 'E';
    ft_printf("\033[38;5;117mStep Number is : %u\n\033[0m", g->steps++);
    draw_map(g);
}


int	handle_input(int key, t_game *g)
{
	if (key == KEY_ESC || key == KEY_Q) close_window(g);
	else if (key == KEY_UP || key == KEY_W || key == KEY_8) ft_move_player(g, 0, -1);
	else if (key == KEY_DOWN || key == KEY_S || key == KEY_5) ft_move_player(g, 0, 1);
	else if (key == KEY_LEFT || key == KEY_A || key == KEY_4) ft_move_player(g, -1, 0);
	else if (key == KEY_RIGHT || key == KEY_D || key == KEY_6) ft_move_player(g, 1, 0);
	return (0);
}

int	close_window(t_game *g)
{
	game_free(g, NULL, g->height);
	exit(0);
}