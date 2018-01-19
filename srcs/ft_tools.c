/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:57:43 by bmuselet          #+#    #+#             */
/*   Updated: 2018/01/18 18:57:45 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_expose_commands_bis(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 35, 35, WHITE, "Quit = ESC");
	mlx_string_put(mlx->mlx, mlx->win, 35, 55, WHITE,
		"Move = ^ v < > or W S A D");
	mlx_string_put(mlx->mlx, mlx->win, 35, 75,
		WHITE, "Show/Hide textures and sky = T");
	mlx_string_put(mlx->mlx, mlx->win, 35, 95, WHITE, "Show/Hide minimap = M");
	mlx_string_put(mlx->mlx, mlx->win, 35, 115, WHITE,
		"Show/Hide commands = H");
	mlx_string_put(mlx->mlx, mlx->win, 35, 135, WHITE,
		"Reset position = Backspace");
	mlx_string_put(mlx->mlx, mlx->win, 35, 155,
		WHITE, "Shoot = Left click");
	mlx_string_put(mlx->mlx, mlx->win, 35, 175, WHITE, "Sprint = Hold SHIFT");
	mlx_string_put(mlx->mlx, mlx->win, 35, 195,
		WHITE, "Change texture mode = TAB");
	return (0);
}

int			ft_expose_commands(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 27;
	y = 34;
	while (x <= 345)
		mlx_pixel_put(mlx->mlx, mlx->win, x++, y, WHITE);
	while (y <= 220)
		mlx_pixel_put(mlx->mlx, mlx->win, x, y++, WHITE);
	while (x >= 27)
		mlx_pixel_put(mlx->mlx, mlx->win, x--, y, WHITE);
	while (y >= 34)
		mlx_pixel_put(mlx->mlx, mlx->win, x, y--, WHITE);
	ft_expose_commands_bis(mlx);
	return (0);
}

int			ft_big_int_error(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	while (i < mlx->map->nb_line)
	{
		j = 0;
		while (j < mlx->map->nb_int)
		{
			if (mlx->map->tab[i][j] > 49)
			{
				ft_putstr(
					"Error : The value of a number is too big. Limit is 50.\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void		ft_calc_pos_hit(t_ray *ray, t_map *map, t_player *player)
{
	ray->texture_num = map->tab[player->map_x][player->map_y] - 1;
	if (ray->side == 0)
		ray->wall_hit = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_hit = ray->pos_x + ray->wall_dist * ray->dir_x;
	ray->texture_coord = (int)(ray->wall_hit * (double)(TEXTURE_WIDTH));
	if ((ray->side == 0 && ray->dir_x > 0) ||
		(ray->side == 1 && ray->dir_y < 0))
		ray->texture_coord = TEXTURE_WIDTH - ray->texture_coord - 1;
	ray->texture_coord = abs(ray->texture_coord);
}

void		ft_draw_sky(t_mlx *mlx)
{
	int	x;
	int	y;
	int j;
	int	color;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT / 2)
		{
			j = x + y * 512;
			color = mlx->map->texture[6].str_img[j];
			ft_fill_pixel(mlx->img, x, y, color);
			y++;
		}
		x++;
	}
}
