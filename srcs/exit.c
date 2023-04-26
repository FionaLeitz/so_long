/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:40:21 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/18 10:40:23 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	end(t_map *map, t_params *params, t_all_img *img)
{
	int	i;

	i = -1;
	while (++i < map->kill_nbr)
	{
		if (map->kill[i][1] == params->px && map->kill[i][2] == params->py)
		{
			i = 0;
			params->px = -1;
			params->py = 0;
			mlx_clear_window(params->mlx_ptr, params->window_ptr);
			while (map->map[i++] && params->px++ >= -1)
			{
				mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
					img->back.img, params->px * 32, params->py * 32);
				if (map->map[i] == '\n' && params->py++ >= 0)
					params->px = -1;
			}
			mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
				img->over.img, ((map->col * 32) / 2) - 48,
				((map->line * 32) / 2) - 48);
			return (mlx_loop_end(params->mlx_ptr));
		}
	}
	return (0);
}

void	put_exit(t_map *map, t_params *params, t_all_img *img, int *xy)
{
	int	i;

	i = 0;
	while (i < map->item_nbr)
	{
		if (map->item[i][0] == 1)
			break ;
		i++;
	}
	mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
		img->exit.img, xy[0], xy[1]);
	if (i == map->item_nbr)
	{
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->exit2.img, xy[0], xy[1]);
	}
}

static void	set_tab_exit(t_map *map)
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
		else if (map->map[i] == 'E')
		{
			map->exit[j][0] = (((i - n) % map->col) - 1) * 32;
			map->exit[j][1] = ((n + 2) - 1) * 32;
			j++;
		}
	}
	return ;
}

int	exits(t_map	*map)
{
	int	i;

	map->exit = malloc(sizeof(int *) * map->e);
	if (map->exit == NULL)
		return (0);
	i = -1;
	while (++i < map->e)
	{
		map->exit[i] = malloc(sizeof(int) * 2);
		if (map->exit[i] == NULL)
		{
			while (--i > -1)
				free(map->exit[i]);
			free(map->exit);
			return (0);
		}
	}
	set_tab_exit(map);
	return (1);
}
