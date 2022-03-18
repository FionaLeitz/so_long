/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:41:08 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/18 10:41:10 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_kill_h(t_map *map, int i, int j, int n)
{
	map->kill[j][1] = (((i - n) % map->col) - 1) * 32;
	map->kill[j][2] = ((n + 2) - 1) * 32;
	map->kill[j][3] = 1;
	if (map->map[i + 1] == '1' && map->map[i - 1] == '1')
		map->kill[j][3] = -1;
}

static void	set_kill_v(t_map *map, int i, int j, int n)
{
	map->kill[j][1] = (((i - n) % map->col) - 1) * 32;
	map->kill[j][2] = ((n + 2) - 1) * 32;
	map->kill[j][3] = 2;
	if (map->map[i + map->col + 1] == '1'
		&& map->map[i - (map->col + 1)] == '1')
		map->kill[j][3] = -2;
}

static void	set_tab_kill(t_map *map)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	j = 0;
	n = -1;
	while (map->map[++i])
	{
		if (map->map[i] == '\n')
			n++;
		else if (map->map[i] == 'K')
		{
			set_kill_h(map, i, j, n);
			j++;
		}
		else if (map->map[i] == 'k')
		{
			set_kill_v(map, i, j, n);
			j++;
		}
	}
	return ;
}

int	kill(t_map *map)
{
	int	i;

	map->kill = malloc(sizeof(int *) * map->kill_nbr);
	if (map->kill == NULL)
		return (0);
	i = -1;
	while (++i < map->kill_nbr)
	{
		map->kill[i] = malloc(sizeof(int) * 4);
		if (map->kill[i] == NULL)
		{
			while (--i > -1)
				free(map->kill[i]);
			free(map->kill);
			return (0);
		}
		map->kill[i][0] = 1;
	}
	set_tab_kill(map);
	return (1);
}
