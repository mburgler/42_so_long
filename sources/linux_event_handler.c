/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_event_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:50:46 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 20:10:29 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	key_press(int kc, t_masterstruc *msc)
{
	int	plyr_x;
	int	plyr_y;

	plyr_x = msc->map->plyr_x;
	plyr_y = msc->map->plyr_y;
	if (kc == ESC)
		free_ma_boi(msc);
	if ((kc == W || kc == UP) && msc->map->map[plyr_y - 1][plyr_x] != '1')
		msc->map->plyr_y--;
	if ((kc == S || kc == DOWN) && msc->map->map[plyr_y + 1][plyr_x] != '1')
		msc->map->plyr_y++;
	if ((kc == A || kc == LEFT) && msc->map->map[plyr_y][plyr_x - 1] != '1')
		msc->map->plyr_x--;
	if ((kc == D || kc == RIGHT) && msc->map->map[plyr_y][plyr_x + 1] != '1')
		msc->map->plyr_x++;
	player_one_move(msc, plyr_x, plyr_y);
	return (0);
}

int	xpress(t_masterstruc *masterstruc)
{
	free_ma_boi(masterstruc);
	return (0);
}
