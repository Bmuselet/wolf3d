/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycode2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:42:01 by bmuselet          #+#    #+#             */
/*   Updated: 2018/01/16 14:42:02 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_key_release(int keycode, t_mlx *mlx)
{
	if (keycode == 257)
	{
		mlx->player->move = 0.2;
		mlx->player->turn = 0.1;
	}
	return (0);
}

int		ft_switch_text_mode(t_mlx *mlx)
{
	if (mlx->map->modif_textures == 0)
		mlx->map->modif_textures = 1;
	else
		mlx->map->modif_textures = 0;
	return (0);
}
