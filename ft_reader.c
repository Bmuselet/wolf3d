/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:26:38 by gnegri            #+#    #+#             */
/*   Updated: 2018/01/08 11:50:51 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
/*
 int	ft_strlen_content(char *str)
{
	int		i;
	int		nb_int;

	i = 0;
	nb_int = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		if (ft_isdigit(str[i]) == 1)
		{
			nb_int++;
			i++;
			while (ft_isdigit(str[i]) == 1)
				i++;
		}
	}
	return (nb_int);
}

 void	ft_put_in_tab(t_map *map, int l)
{
	int i;

	i = 0;
	while (map->content[l][i] != '\n' || map->content[l][i] != '\0')
	{
		map->tab[l][i] = ft_atoi(&map->content[l][i]);
		i++;
	}
}

int	ft_verif_int_nb(t_map *map)
{
	int		l;
	int		c;
	int 	i;

	l = 0;
	i = 0;
	map->tab = (int **)malloc(sizeof(int *) * map->nb_line + 1);
	while (l < map->nb_line - 1)
	{
		c = ft_strlen_content(map->content[l]);
		if (ft_strlen_content(map->content[l + 1]) != c)
			return (-1);
		if ((map->tab[l] = (int *)malloc(sizeof(int) * c + 1)) == NULL)
			return (-1);
		ft_put_in_tab(map, l);
		l++;
	}
	if ((map->tab[l] = (int *)malloc(sizeof(int) * c + 1)) == NULL)
		return (-1);
	ft_put_in_tab(map, l);
	map->tab[l + 1] = 0;
	return (1);
}

 int	ft_verifs(int fd, t_map *map, char *line)
{
	if (get_next_line(fd, &line) < 0)
	{
		ft_putstr("get_next_line : error\n");
		free(map->content);
		free(map->str);
		return (-1);
	}
	if (close(fd) == -1 || ft_check_errors(map->str) != 1 ||
		ft_verif_int_nb(map) != 1)
	{
		ft_putstr("error\n");
		free(map->content);
		free(map->str);
		free(map->tab);
		return (-1);
	}
	return (1);
}

*/
static int	ft_put_in_tab(t_map *map, int fd)
{
	int		l;
	int		i;
	int		j;
	char	*line;

	l = 0;
	printf("ligne : %d\n", map->nb_line);
	printf("int : %d\n", map->nb_int);
	if (!(map->tab = (int **)malloc(sizeof(int *) * (map->nb_line + 1))))
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		j = 0;
		if (!(map->tab[l] = (int *)malloc(sizeof(int) * (map->nb_int / map->nb_line))))
			return (-1);
		while (line[i])
		{
			if (line[i] >= '0' && line[i] <= '9')
			{
				//printf("%d", ft_atoi_wolf(line, i));
				map->tab[l][j] = ft_atoi_wolf(line, i);
				printf("%d", map->tab[l][i]);
			}
			j++;
			i++;
		}
		printf("\n");
		l++;
	}
	return (0);
}

static int	ft_errors(char *buff, t_map *map)
{
	int i;
	int c;

	i = 0;
	c = 0;
	map->nb_int = 0;
	while(buff[i + 1] != '\0')
	{
		if (buff[i] == ' ' && ((buff[i + 1] < '0' || buff[i + 1] > '9') &&
			buff[i + 1] != '\n'))
			return (-1);
		else if ((buff[i] >= '0' && buff[i] <= '9') && (buff[i + 1] != ' ' &&
			buff[i + 1] != '\n'))
			return (-1);
		else if ((buff[i] < '0' && buff[i] > '9') && (buff[i] != ' ' &&
			buff[i] != '\n'))
			return (-1);
		else if (buff[i] >= '0' && buff[i] <= '9')
			c++;
		i++;
	}
	return (c);
}

static int	ft_read_data(t_map *map, int fd)
{
	int ret;
	char *buff;
	int i;
	int c;
	
	c = 0;
	map->nb_line = 0;
	if (!(buff = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		i = 0;
		if (((c = ft_errors(buff, map)) == -1) || buff == 0)
		{
			printf("%d\n", c);
			return (-1);
		}
		while (buff[i])
		{
			if (buff[i] == '\n')
				map->nb_line += 1;
			i++;
		}
	}
	if ((map->nb_int = c) < 1)
	{
		ft_putstr("file is empty : error\n");
		return (-1);
	}
	printf("ligne : %d\n", map->nb_line);
	printf("int : %d\n", map->nb_int);
	free(buff);
	return (0);
}

static int	ft_check_read(int argc, char *argv, int *fd)
{
	if (argc < 2)
	{
		ft_putstr("usage: ./fdf input_file\n");
		return (0);
	}
	if ((*fd = open(argv, O_RDONLY)) < 0)
	{
		ft_putstr("bad_file : error\n");
		return (0);
	}
	if (BUFF_SIZE <= 0)
	{
		ft_putstr("BUFF_SIZE : error\n");
		return (0);
	}
	return (0);
}

int			ft_reader(int argc, char *argv, t_mlx *mlx)
{
	int a;
	int fd;

	a = argc;
	if (ft_check_read(argc, argv, &fd) != 0)
		return (-1);
	if (ft_read_data(mlx->map, fd) != 0)
		return (-1);
	if (close (fd == -1))
		return (-1);
	fd = open(argv, O_RDONLY);
	if (ft_put_in_tab(mlx->map, fd) != 0)
		return (-1);
	return (0);
}
