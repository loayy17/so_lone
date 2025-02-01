/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 06:16:04 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:35:52 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_monster_up(char *monster_images[])
{
	monster_images[0] = M_UP_0;
	monster_images[1] = M_UP_1;
	monster_images[2] = M_UP_2;
	monster_images[3] = M_UP_3;
	monster_images[4] = M_UP_4;
}

void	ft_draw_monster_down(char *monster_images[])
{
	monster_images[0] = M_DOWN_0;
	monster_images[1] = M_DOWN_1;
	monster_images[2] = M_DOWN_2;
	monster_images[3] = M_DOWN_3;
	monster_images[4] = M_DOWN_4;
}

void	ft_draw_monster_left(char *monster_images[])
{
	monster_images[0] = M_LEFT_0;
	monster_images[1] = M_LEFT_1;
	monster_images[2] = M_LEFT_2;
	monster_images[3] = M_LEFT_3;
	monster_images[4] = M_LEFT_4;
}

void	ft_draw_monster_right(char *monster_images[])
{
	monster_images[0] = M_RIGHT_0;
	monster_images[1] = M_RIGHT_1;
	monster_images[2] = M_RIGHT_2;
	monster_images[3] = M_RIGHT_3;
	monster_images[4] = M_RIGHT_4;
}
