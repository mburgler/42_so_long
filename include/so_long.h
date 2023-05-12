/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:32:36 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/12 14:53:54 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include "../MY_LIB/ft_printf/ft_printf.h"
# include "../MY_LIB/ft_printf2/ft_printf2.h"
# include "../MY_LIB/get_next_line/get_next_line_bonus.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/X.h>

# ifdef __linux__
#  define W 119
#  define S 115
#  define A 97
#  define D 100
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
#  define ESC 65307
# endif

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
	int		map_player_count;
	int		map_exit_count;
	int		map_collectible_count;
	int		enemy_count;
	int		plyr_x;
	int		plyr_y;
	int		enemy_x;
	int		enemy_y;
	int		enemy_x_old;
	int		enemy_y_old;
}			t_map;

typedef struct s_img
{
	void	*coll;
	void	*enemy;
	void	*floor;
	void	*goal_off;
	void	*goal_on;
	void	*player;
	void	*wall;
}			t_img;

typedef struct s_masterstruc
{
	void	*win;
	void	*mlx;
	int		moves;
	int		sucess;
	int		img_pxl;
	t_map	*map;
	t_img	*img;
}			t_masterstruc;

int				ft_mapformat_and_filechecker(char *map_file);
void			check_walls(t_masterstruc *masterstruc);
void			check_chars(t_masterstruc *masterstruc);
void			count_chars(char c, t_masterstruc *msc, int done_map);
void			position_player(t_masterstruc *masterstruc);
void			check_map(t_masterstruc *masterstruc);
void			fill(char **flood_map, int y, int x);
void			check_flooded_map(t_masterstruc *masterstruc, char **flood_map);
void			flood_fill(t_masterstruc *msc);
void			free_floodmap(char **flood_map);
void			error_message(char *message, t_masterstruc *masterstruc);
void			error_opening_file(char **map, t_masterstruc *masterstruc);
void			error_reading_file(int fd, t_masterstruc *masterstruc);
void			no_map(char **map, t_masterstruc *mastersruct);
int				empty_file(char *map_file, t_masterstruc *masterstruct);
int				seek_no_lines(char *map_file, t_masterstruc *masterstruct);
char			**kill_backlash_n(char **map);
void			gnl_calloc_error(char **map, int i, t_masterstruc *msc);
void			init_map(char *map_file, t_masterstruc *masterstruct);
t_masterstruc	*init_masterstruc(char *map_file);
void			free_ma_boi(t_masterstruc *masterstruc);
void			free_ma_mlx(t_masterstruc *masterstruc);
int				main(int argc, char **argv);
int				key_press(int kc, t_masterstruc *masterstruc);
int				xpress(t_masterstruc *masterstruc);
void			xpm_to_image(t_masterstruc *masterstruc);
int				render_frame(t_masterstruc *masterstruc);
void			put_according_img(t_masterstruc *msc, char c, int x, int y);
void			put_plyr(t_masterstruc *msc);
void			put_moves(t_masterstruc *msc);
void			player_one_move(t_masterstruc *msc, int x, int y);
void			enemy_patrol(t_map *map, int *moves);
void			enemy_patrol_next_move(int	*moves, t_map *map);
void			pos_enemy(t_map *map);

#endif
