/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:51:12 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:37:31 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_player(t_game *g, int dir, int frame)
{
	int	width;
	int	height;

	if (g->player_img[dir][frame])
		mlx_destroy_image(g->mlx, g->player_img[dir][frame]);
	g->player_img[dir][frame] = mlx_xpm_file_to_image(g->mlx,
			g->player_img[dir][frame], &width, &height);
	if (!g->player_img[dir][frame])
		exit_err("Error\nPlayer image not found\n", g, NULL);
	mlx_put_image_to_window(g->mlx, g->win, g->player_img[dir][frame],
		g->player.x * TILE_SIZE, g->player.y * TILE_SIZE);
}

void	set_element_images(char *element_images[], int dir)
{
	if (dir == 4)
	{
		ft_draw_exit(element_images, 0);
	}
	else if (dir == 5)
	{
		ft_draw_exit(element_images, 1);
	}
}

void	ft_put_background(t_game *g, int width)
{
	int	i;
	int	j;

	i = 10;
	j = 0;
	while (i < 35)
	{
		j = 0;
		while (j < 100)
		{
			mlx_pixel_put(g->mlx, g->win, (width + j) - 10, i, 0x4F77B4CF);
			j++;
		}
		i++;
	}
}

void	ft_put_steps(t_game *g, size_t steps)
{
	int				width;
	int				height;
	unsigned int	color;
	char			*message;
	char			*steps_counter;

	color = 0x000000;
	steps_counter = ft_itoa(steps);
	height = 25;
	width = (g->width * 50 / 2) - 50;
	message = ft_strjoin("Steps ==> ", steps_counter);
	if (!steps_counter)
	{
		free(steps_counter);
		exit_err("Error\nFailed to allocate memory\n", g, NULL);
	}
	if (!message)
	{
		free(message);
		exit_err("Error\nFailed to allocate memory\n", g, NULL);
	}
	ft_put_background(g, width);
	mlx_string_put(g->mlx, g->win, width, height, color, message);
	free(steps_counter);
	free(message);
}

void	ft_win_game(t_game *g)
{
	ft_printf("\033[1;36m");
	ft_printf("************************************************************\n");
	ft_printf("************************************************************\n");
	ft_printf("************************************************************\n");
	ft_printf("*******              شغل نظيف نظيف                   *******\n");
	ft_printf("*******                                              *******\n");
	ft_printf("*******              مرفوضة مرفوضة                   *******\n");
	ft_printf("*******                                              *******\n");
	ft_printf("*               \033[1;33mYOU WIN\033[1;36m               *\n");
	ft_printf("*               \033[1;33mGO TO SLEEP\033[1;36m           *\n");
	ft_printf("*******                                                   **\n");
	ft_printf("*            \033[0;36mcreated by lalhindi\033[1;36m      *\n");
	ft_printf("*******                                              *******\n");
	ft_printf("************************************************************\n");
	ft_printf("************************************************************\n");
	ft_printf("************************************************************\n");
	ft_printf("\033[0m");
	close_window(g);
}

void	game_over(t_game *g)
{
	ft_printf("\033[1;36m");
	ft_printf("************************************************************\n");
	ft_printf("█████       ███████     █████████  ██████████ ███████████ \n");
	ft_printf("░███       ██░░░░░██  ███░░░░░███░░███░░░░░█░███░░░░░███\n");
	ft_printf("░███      ██     ░░██░███    ░░░  ░███  █ ░  ███    ░███ \n");
	ft_printf("░███     ░██      ░██░░█████████  ░██████    ██████████ \n");
	ft_printf("░███     ░██      ░██ ░░░░░░░░███ ░███░░█    ░███░░░░░███ \n");
	ft_printf("░███     ░░██     ██  ███    ░███ ░███ ░   █ ░███    ░███ \n");
	ft_printf("█████████ ░░███████░ ░░█████████  ██████████ █████   █████\n");
	ft_printf("░░░░░░░░░░   ░░░░░░░    ░░░░░░░░░  ░░░░░░░░░░ ░░░░░   ░░░░░\n");
	ft_printf("\033[0m");
	ft_printf("************************************************************\n");
	ft_printf("************************************************************\n");
	ft_printf("******\033[1;32m    created by lalhindi\033[0m    ******\n");
	ft_printf("************************************************************\n");
	close_window(g);
}

void	ft_move_player(t_game *g, int x, int y)
{
	char	next_pos;

	next_pos = g->map[g->player.y + y][g->player.x + x];
	if (next_pos == '1')
		return ;
	if (next_pos == 'M')
		game_over(g);
	if (next_pos == 'C')
		g->collectible--;
	if (g->collectible == 0)
		g->exit.dir = 1;
	if (next_pos == 'E' && g->collectible == 0)
		ft_win_game(g);
	g->map[g->player.y][g->player.x] = '0';
	g->player.x += x;
	g->player.y += y;
	g->map[g->player.y][g->player.x] = 'P';
	if (!(g->player.y == g->exit.y) || !(g->player.x == g->exit.x))
		g->map[g->exit.y][g->exit.x] = 'E';
	++g->steps;
}

int	handle_input(int key, t_game *g)
{
	if (key == KEY_ESC || key == KEY_Q)
		close_window(g);
	else if (key == KEY_UP || key == KEY_W)
	{
		ft_move_player(g, 0, -1);
		g->player.dir = 0;
	}
	else if (key == KEY_DOWN || key == KEY_S)
	{
		ft_move_player(g, 0, 1);
		g->player.dir = 1;
	}
	else if (key == KEY_LEFT || key == KEY_A)
	{
		ft_move_player(g, -1, 0);
		g->player.dir = 2;
	}
	else if (key == KEY_RIGHT || key == KEY_D)
	{
		ft_move_player(g, 1, 0);
		g->player.dir = 3;
	}
	return (0);
}

int	close_window(t_game *g)
{
	game_free(g, NULL, g->height);
	exit(0);
}

void	player_render(t_game *g)
{
	if (++g->player_speed < 1000)
		return ;
	g->player_speed = 0;
	g->frame = (g->frame + 1) % ANIMATION_FRAMES;
}

int	animation_loop(t_game *g)
{
	render_monsters(g);
	move_monsters(g);
	draw_map(g);
	player_render(g);
	ft_put_steps(g, g->steps);
	return (0);
}