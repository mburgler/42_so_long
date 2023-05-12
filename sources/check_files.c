/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:09:52 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 20:11:16 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_mapformat_and_filechecker(char *map_file)
{
	if (access(map_file, F_OK | R_OK) == -1)
		return (-1);
	else if (ft_strncmp(map_file + ft_strlen(map_file) - 4, ".ber", 4))
		return (-1);
	else
	{
		if (access("graphics/collectible.xpm", F_OK | R_OK) == -1
			|| access("graphics/enemy.xpm", F_OK | R_OK) == -1
			|| access("graphics/floor.xpm", F_OK | R_OK) == -1
			|| access("graphics/goal_off.xpm", F_OK | R_OK) == -1
			|| access("graphics/goal_on.xpm", F_OK | R_OK) == -1
			|| access("graphics/player.xpm", F_OK | R_OK) == -1
			|| access("graphics/wall.xpm", F_OK | R_OK) == -1)
		{
			error_message("Graphics resource missing\n", NULL);
		}
		return (1);
	}
}
