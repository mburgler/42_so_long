/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:09:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/12 12:47:46 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	empty_file(char *map_file, t_masterstruc *masterstruct)
{
	int		fd;
	char	buffer;
	int		lines;

	fd = open(map_file, O_RDONLY);
	if (read(fd, &buffer, 1) == 0)
		error_message("Empty file\n", masterstruct);
	lines = seek_no_lines(map_file, masterstruct);
	return (lines);
}

int	seek_no_lines(char *map_file, t_masterstruc *masterstruct)
{
	int		fd;
	int		bytes;
	int		lines;
	char	buffer;
	char	old_buffer;

	lines = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_message("Could not open file (fd = -1)\n", masterstruct);
	bytes = 1;
	old_buffer = '\0';
	while (bytes)
	{
		bytes = read(fd, &buffer, 1);
		if (old_buffer == buffer && buffer == '\n')
			return (lines);
		if (bytes == -1)
			error_reading_file(fd, masterstruct);
		if (buffer == '\n')
			lines++;
		old_buffer = buffer;
	}
	close(fd);
	return (lines + 1);
}

char	**kill_backlash_n(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (map[j][i] == '\n')
				map[j][i] = '\0';
			i++;
		}
		j++;
	}
	return (map);
}

void	gnl_calloc_error(char **map, int i, t_masterstruc *msc)
{	
	if (!map[i])
	{
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
		error_message("Malloc failed\n", msc);
	}
}

void	init_map(char *map_file, t_masterstruc *masterstruct)
{
	char	**map;
	int		i;
	int		fd;
	int		lines;

	i = 0;
	lines = empty_file(map_file, masterstruct);
	map = ft_calloc(1, sizeof(char *) * (lines + 1));
	if (!map)
		no_map(map, masterstruct);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		error_opening_file(map, masterstruct);
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		gnl_calloc_error(map, i++, masterstruct);
	}
	free(get_next_line(fd));
	map = kill_backlash_n(map);
	masterstruct->map->map = map;
	masterstruct->map->map_height = i;
	masterstruct->map->map_width = ft_strlen(map[0]);
	close(fd);
}
