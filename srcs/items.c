/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:40:46 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/18 10:40:51 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static void	remove_items(t_map *map, t_params *params)
{
	int	i;

	i = 0;
	while (i < map->item_nbr)
	{
		if (params->px == map->item[i][1] && params->py == map->item[i][2])
			map->item[i][0] = 0;
		i++;
	}
	return ;
}

void	put_item(t_map *map, t_params *params, t_all_img *img)
{
	int	i;
	int	r;

	r = 1;
	i = -1;
	while (++i < map->item_nbr)
	{
		if (params->px == map->item[i][1] && params->py == map->item[i][2]
			&& map->item[i][0] == 1)
			r = 2;
	}
	put_perso(params, img, r);
	remove_items(map, params);
	i = -1;
	r = 0;
	while (++i < map->item_nbr)
	{
		if (map->item[i][0] == 1)
			mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
				img->item.img, map->item[i][1], map->item[i][2]);
		if (map->item[i][0] == 0)
			r++;
	}
	if_win(map, params, img, r);
	return ;
}

static void	set_tab_item(t_map *map)
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
		else if (map->map[i] == 'C')
		{
			map->item[j][1] = (((i - n) % map->col) - 1) * 32;
			map->item[j][2] = ((n + 2) - 1) * 32;
			j++;
		}
	}
	return ;
}

int	items(t_map *map)
{
	int	i;

	map->item = malloc(sizeof(int *) * map->item_nbr);
	if (map->item == NULL)
		return (0);
	i = -1;
	while (++i < map->item_nbr)
	{
		map->item[i] = malloc(sizeof(int) * 3);
		if (map->item[i] == NULL)
		{
			while (--i > -1)
				free(map->item[i]);
			free(map->item);
			return (0);
		}
		map->item[i][0] = 1;
	}
	set_tab_item(map);
	if (kill(map) == 0)
		return (0);
	if (exits(map) == 0)
		return (0);
	return (1);
}
