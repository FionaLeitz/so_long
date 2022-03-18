/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:40:08 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/18 10:40:12 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_kill_1(t_map *map, t_params *params, t_all_img *img, int i)
{
	if (map->kill[i][3] == -1)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill.img, map->kill[i][1], map->kill[i][2]);
	else if (map->kill[i][3] == -2)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill2.img, map->kill[i][1], map->kill[i][2]);
	else if (map->kill[i][3] == 1)
	{
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill.img, map->kill[i][1], map->kill[i][2]);
		if (check_wall(map, i) == 1)
			map->kill[i][0] = map->kill[i][0] * -1;
		map->kill[i][1] += (32 * map->kill[i][0]);
	}
	else
	{
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill2.img, map->kill[i][1], map->kill[i][2]);
		if (check_wall(map, i) == 1)
			map->kill[i][0] = map->kill[i][0] * -1;
		map->kill[i][2] += (32 * map->kill[i][0]);
	}
}

static void	put_kill_2(t_map *map, t_params *params, t_all_img *img, int i)
{
	if (map->kill[i][3] == -1)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill2.img, map->kill[i][1], map->kill[i][2]);
	else if (map->kill[i][3] == -2)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill.img, map->kill[i][1], map->kill[i][2]);
	else if (map->kill[i][3] == 1)
	{
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill2.img, map->kill[i][1], map->kill[i][2]);
		if (check_wall(map, i) == 1)
			map->kill[i][0] = map->kill[i][0] * -1;
		map->kill[i][1] += (32 * map->kill[i][0]);
	}
	else
	{
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->kill.img, map->kill[i][1], map->kill[i][2]);
		if (check_wall(map, i) == 1)
			map->kill[i][0] = map->kill[i][0] * -1;
		map->kill[i][2] += (32 * map->kill[i][0]);
	}
}

static void	put_kill(t_map *map, t_params *params, t_all_img *img)
{
	int	i;

	i = -1;
	if (end(map, params, img) != 0)
		return ;
	while (++i < map->kill_nbr)
	{
		if (params->count % 2 == 0)
			put_kill_1(map, params, img, i);
		else
			put_kill_2(map, params, img, i);
	}
}

static void	if_win_2(t_map *map, t_params *params, t_all_img *img)
{
	mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
		img->back.img, params->px, params->py);
	map->p++;
	params->px += 32;
	if (map->map[map->p] == '\n')
		params->px = 0;
	if (map->map[map->p] == '\n')
		params->py += 32;
}

void	if_win(t_map *map, t_params *params, t_all_img *img, int r)
{
	int	i;

	i = 0;
	while (i < map->e)
	{
		if (params->px == map->exit[i][0] && params->py == map->exit[i][1]
			&& r == map->item_nbr)
		{
			map->p = 0;
			params->px = 0;
			params->py = 0;
			mlx_clear_window(params->mlx_ptr, params->window_ptr);
			while (map->map[map->p])
				if_win_2(map, params, img);
			mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
				img->win.img, ((map->col * 32) / 2) - 48,
				((map->line * 32) / 2) - 48);
			mlx_loop_end(params->mlx_ptr);
			return ;
		}
		i++;
	}
	put_kill(map, params, img);
}
