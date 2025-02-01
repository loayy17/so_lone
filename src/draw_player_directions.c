/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-01 09:17:16 by lalhindi          #+#    #+#             */
/*   Updated: 2025-02-01 09:17:16 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_player_up(char *player_images[])
{
	player_images[0] = P_UP_0;
	player_images[1] = P_UP_1;
	player_images[2] = P_UP_2;
	player_images[3] = P_UP_3;
	player_images[4] = P_UP_4;
}

void	ft_draw_player_down(char *player_images[])
{
	player_images[0] = P_DOWN_0;
	player_images[1] = P_DOWN_1;
	player_images[2] = P_DOWN_2;
	player_images[3] = P_DOWN_3;
	player_images[4] = P_DOWN_4;
}

void	ft_draw_player_left(char *player_images[])
{
	player_images[0] = P_LEFT_0;
	player_images[1] = P_LEFT_1;
	player_images[2] = P_LEFT_2;
	player_images[3] = P_LEFT_3;
	player_images[4] = P_LEFT_4;
}

void	ft_draw_player_right(char *player_images[])
{
	player_images[0] = P_RIGHT_0;
	player_images[1] = P_RIGHT_1;
	player_images[2] = P_RIGHT_2;
	player_images[3] = P_RIGHT_3;
	player_images[4] = P_RIGHT_4;
}

void	ft_draw_exit(char *exit_image[], int open)
{
	if (!open)
	{
		exit_image[0] = E_CLOSE_0;
		exit_image[1] = E_CLOSE_1;
		exit_image[2] = E_CLOSE_2;
		exit_image[3] = E_CLOSE_3;
		exit_image[4] = E_CLOSE_4;
	}
	else
	{
		exit_image[0] = E_OPEN_0;
		exit_image[1] = E_OPEN_1;
		exit_image[2] = E_OPEN_2;
		exit_image[3] = E_OPEN_3;
		exit_image[4] = E_OPEN_4;
	}
}
