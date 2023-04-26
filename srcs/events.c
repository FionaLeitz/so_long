/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:33:18 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/15 10:33:24 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static int	check_wall2(t_params *params, t_map *map, char c, int n)
{
	int	i;
	int	line;

	if (c == 'x')
	{
		line = ((params->py) / 32) + 1;
		i = (((params->px + n) / 32) + 1)
			+(map->col * (line - 1)) + (line - 1);
	}
	else
	{
		line = ((params->py + n) / 32) + 1;
		i = (((params->px) / 32) + 1) + (map->col * (line - 1)) + (line - 1);
	}
	if (map->map[i - 1] == '1')
		return (1);
	return (0);
}

static void	move(t_params *params, char c, int n)
{
	params->count++;
	if (c == 'x')
	{
		params->px += n;
		mlx_clear_window(params->mlx_ptr, params->window_ptr);
		make_map(params->map, params, params->img);
	}
	else
	{
		params->py += n;
		mlx_clear_window(params->mlx_ptr, params->window_ptr);
		make_map(params->map, params, params->img);
	}
	number(params);
}

static void	escape(t_params *params)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	x = 0;
	y = 0;
	mlx_clear_window(params->mlx_ptr, params->window_ptr);
	while (params->map->map[++i])
	{
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			params->img->back.img, x, y);
		x += 32;
		if (params->map->map[i] == '\n')
			x = 0;
		if (params->map->map[i] == '\n')
			y += 32;
	}
	mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
		params->img->bye.img, ((params->map->col * 32) / 2) - 48,
		((params->map->line * 32) / 2) - 48);
	mlx_loop_end(params->mlx_ptr);
}

int	deal_key(int key, t_params *params)
{
	params->key = key;
	if (key == 119 || key == 65362)
	{
		if (check_wall2(params, params->map, 'y', -32) == 0)
			move(params, 'y', -32);
	}
	else if (key == 97 || key == 65361)
	{
		if (check_wall2(params, params->map, 'x', -32) == 0)
			move(params, 'x', -32);
	}
	else if (key == 115 || key == 65364)
	{
		if (check_wall2(params, params->map, 'y', 32) == 0)
			move(params, 'y', 32);
	}
	else if (key == 100 || key == 65363)
	{
		if (check_wall2(params, params->map, 'x', 32) == 0)
			move(params, 'x', 32);
	}
	else if (key == 65307)
		escape(params);
	return (0);
}

int	deal_cross(t_params *params)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	mlx_clear_window(params->mlx_ptr, params->window_ptr);
	while (params->map->map[i])
	{
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			params->img->back.img, x, y);
		i++;
		x += 32;
		if (params->map->map[i] == '\n')
			x = 0;
		if (params->map->map[i] == '\n')
			y += 32;
	}
	mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
		params->img->bye.img, ((params->map->col * 32) / 2) - 48,
		((params->map->line * 32) / 2) - 48);
	mlx_loop_end(params->mlx_ptr);
	return (0);
}
