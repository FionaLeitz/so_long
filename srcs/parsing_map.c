/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:33:52 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/15 10:33:55 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static char	*ft_get_map(char *path)
{
	int		fd;
	int		r;
	char	buff[101];
	char	*map;

	map = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	r = 1;
	while (r != 0)
	{
		r = read(fd, buff, 100);
		if (r == -1)
			return (NULL);
		buff[r] = '\0';
		cpy(buff, &map);
		if (map == NULL)
			return (NULL);
	}
	close(fd);
	return (map);
}

static void	check_map(char *maps, t_map *map)
{
	int	i;

	i = -1;
	while (maps[++i] && maps[i] != '\n')
	{
		if (maps[i] != '1')
			map->item_nbr = 0;
	}
	while (maps[++i + 1])
	{
		if (!(maps[i] == '0' || maps[i] == '1' || maps[i] == 'C'
				|| maps[i] == 'E' || maps[i] == 'P' || maps[i] == '\n'
				|| maps[i] == 'K' || maps[i] == 'k'))
			map->item_nbr = -1;
		if (maps[i] == '\n' && (maps[i - 1] != '1' || maps[i + 1] != '1'))
			map->item_nbr = 0;
	}
	while (--i > 0 && maps[i] != '\n')
	{
		if (maps[i] != '1')
			map->item_nbr = 0;
	}
}

static int	map_wall(char *maps, t_map *map)
{
	if (map->item_nbr == 0)
		ft_printf("Error\nNot enough items\n");
	else if (map->p != 1)
		ft_printf("Error\nNot one Fox\n");
	if (map->item_nbr == 0 || map->e != 1 || map->p != 1)
		return (1);
	check_map(maps, map);
	if (map->item_nbr == 0)
		ft_printf("Error\nWalls missing around !\n");
	else if (map->item_nbr == -1)
		ft_printf("Error\nWrong character in map\n");
	return (1);
}

static int	map_count(t_map *map, int i)
{
	while (map->map[i])
	{
		if (map->map[i] == '\n')
		{
			if (map->col == 0 || (i - map->line) % map->col != 0)
			{
				map->item_nbr = 0;
				ft_printf("Error\nMap lines are not the same...\n");
				free(map->map);
				return (0);
			}
			map->line++;
		}
		if (map->map[i] == 'E')
			map->e++;
		if (map->map[i] == 'P')
			map->p++;
		if (map->map[i] == 'C')
			map->item_nbr++;
		if (map->map[i] == 'K' || map->map[i] == 'k')
			map->kill_nbr++;
		i++;
	}
	return (map_wall(map->map, map));
}

int	map_info(char *maps, t_map *map)
{
	int		i;

	map->map = ft_get_map(maps);
	if (map->map == NULL)
		return (0);
	map->line = 0;
	map->col = 0;
	map->item_nbr = 0;
	map->kill_nbr = 0;
	map->e = 0;
	map->p = 0;
	i = 0;
	while (map->map[i] && map->map[i] != '\n')
		i++;
	map->col = i;
	return (map_count(map, i));
}
