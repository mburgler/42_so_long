/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:15:49 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 22:19:17 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	xpm_to_image(t_masterstruc *msc)
{
	int	pxl_size;

	msc->img = ft_calloc(1, sizeof(t_img));
	if (!msc->img)
		error_message("Malloc failed\n", msc);
	msc->img->coll = mlx_xpm_file_to_image(msc->mlx,
			"graphics/collectible.xpm", &pxl_size, &pxl_size);
	msc->img->enemy = mlx_xpm_file_to_image(msc->mlx,
			"graphics/enemy.xpm", &pxl_size, &pxl_size);
	msc->img->floor = mlx_xpm_file_to_image(msc->mlx,
			"graphics/floor.xpm", &pxl_size, &pxl_size);
	msc->img->goal_off = mlx_xpm_file_to_image(msc->mlx,
			"graphics/goal_off.xpm", &pxl_size, &pxl_size);
	msc->img->goal_on = mlx_xpm_file_to_image(msc->mlx,
			"graphics/goal_on.xpm", &pxl_size, &pxl_size);
	msc->img->player = mlx_xpm_file_to_image(msc->mlx,
			"graphics/player.xpm", &pxl_size, &pxl_size);
	msc->img->wall = mlx_xpm_file_to_image(msc->mlx,
			"graphics/wall.xpm", &pxl_size, &pxl_size);
	if (msc->img->coll == NULL || msc->img->enemy == NULL
		|| msc->img->floor == NULL || msc->img->goal_off == NULL
		|| msc->img->goal_on == NULL || msc->img->player == NULL
		|| msc->img->wall == NULL)
		error_message("Couldn't initialise XPM images", msc);
	msc->img_pxl = pxl_size;
}

int	render_frame(t_masterstruc *msc)
{
	int	x;
	int	y;

	y = 0;
	while (y < msc->map->map_height)
	{
		x = 0;
		while (x < msc->map->map_width)
		{
			put_according_img(msc, msc->map->map[y][x], x, y);
			x++;
		}
		y ++;
	}
	return (0);
}

void	put_according_img(t_masterstruc *msc, char c, int x, int y)
{
	put_plyr(msc);
	if (x != msc->map->plyr_x || y != msc->map->plyr_y)
	{
		if (c == '0')
			mlx_put_image_to_window(msc->mlx, msc->win, msc->img->floor,
				x * msc->img_pxl, y * msc->img_pxl);
		if (c == '1')
			mlx_put_image_to_window(msc->mlx, msc->win, msc->img->wall,
				x * msc->img_pxl, y * msc->img_pxl);
		if (c == 'C')
			mlx_put_image_to_window(msc->mlx, msc->win, msc->img->coll,
				x * msc->img_pxl, y * msc->img_pxl);
		if (c == 'E')
			mlx_put_image_to_window(msc->mlx, msc->win, msc->img->goal_off,
				x * msc->img_pxl, y * msc->img_pxl);
		if (c == 'X')
			mlx_put_image_to_window(msc->mlx, msc->win, msc->img->enemy,
				x * msc->img_pxl, y * msc->img_pxl);
	}
	put_moves(msc);
}

void	put_moves(t_masterstruc *msc)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_itoa(msc->moves - 1);
	tmp = ft_strjoin("Number of moves: ", tmp2);
	mlx_string_put(msc->mlx, msc->win, 2, 10, 0xccccff, tmp);
	free(tmp);
	free(tmp2);
}

void	put_plyr(t_masterstruc *msc)
{
	if (msc->map->map[msc->map->plyr_y][msc->map->plyr_x] == 'E'
		&& msc->map->map_collectible_count == 0)
	{
		mlx_put_image_to_window(msc->mlx, msc->win, msc->img->goal_on,
			msc->map->plyr_x * msc->img_pxl, msc->map->plyr_y * msc->img_pxl);
		if (msc->sucess > 50000)
		{
			ft_printf("### YOU WON <3 ###\n");
			free_ma_boi(msc);
		}
		msc->sucess++;
	}
	else if (msc->map->map[msc->map->plyr_y][msc->map->plyr_x] == 'X'
		|| (msc->map->plyr_y == msc->map->enemy_y_old
		&& msc->map->plyr_x == msc->map->enemy_x_old))
	{	
		ft_printf("### GAME OVER ###\n");
		free_ma_boi(msc);
	}
	else
		mlx_put_image_to_window(msc->mlx, msc->win, msc->img->player,
			msc->map->plyr_x * msc->img_pxl, msc->map->plyr_y * msc->img_pxl);
}
