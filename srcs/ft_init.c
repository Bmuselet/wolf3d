/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:54:22 by gnegri            #+#    #+#             */
/*   Updated: 2018/01/09 13:54:30 by gnegri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_find_position(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (i < mlx->map->nb_line)
	{
		j = 0;
		while (j < mlx->map->nb_int)
		{
			if (mlx->map->tab[i][j] != 0)
				j++;
			else
			{
				mlx->player->pos_x = i + 0.5;
				mlx->player->pos_y = j + 0.5;
				return (0);
			}
		}
		i++;
	}
	return (0);
}

static void	ft_init_map(t_mlx *mlx)
{
	mlx->map->switch_tex = 1;
	mlx->map->show_map = 0;
	mlx->map->show_help = 1;
	mlx->map->modif_textures = 0;
	if (WIN_WIDTH > 500 && WIN_HEIGHT > 250)
		mlx->map->resize = 1;
	else
		mlx->map->resize = 2;
	ft_draw_texture(mlx, mlx->map);
}

int			ft_init_player(t_mlx *mlx)
{
	t_player	*player;
	t_ray		*ray;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (-1);
	if (!(ray = (t_ray *)malloc(sizeof(t_ray))))
		return (-1);
	mlx->player = player;
	player->ray = ray;
	player->dir_x = 1;
	player->dir_y = 0;
	player->move = 0.2;
	player->turn = 0.1;
	player->plane_x = 0;
	player->plane_y = 0.66;
	mlx->player->weapon = 0;
	mlx->player->shoot = 0;
	ft_find_position(mlx);
	ft_init_map(mlx);
	return (0);
}
