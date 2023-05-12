/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:30:11 by matteobuerg       #+#    #+#             */
/*   Updated: 2023/05/12 12:48:20 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_message(char *message, t_masterstruc *masterstruc)
{
	perror("Error");
	ft_printf_2("%s\n", message);
	free_ma_boi(masterstruc);
}

void	error_opening_file(char **map, t_masterstruc *masterstruc)
{
	free(map);
	error_message("Could not open file (fd = -1)\n", masterstruc);
}

void	error_reading_file(int fd, t_masterstruc *masterstruc)
{
	close(fd);
	error_message("Could not read file (read = -1)\n", masterstruc);
}

void	no_map(char **map, t_masterstruc *mastersruct)
{
	free(map);
	error_message("Malloc failed\n", mastersruct);
}
