/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-01 10:13:44 by lalhindi          #+#    #+#             */
/*   Updated: 2025-02-01 10:13:44 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	close_window(t_game *g)
{
	game_free(g, NULL, g->height);
	exit(0);
}
