/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:34:10 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/15 10:34:16 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_perso(t_params *params, t_all_img *img, int i)
{
	if (i == 2)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->tail.img, params->px, params->py);
	else if (params->key == 119 || params->key == 65362)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->perso2.img, params->px, params->py);
	else if (params->key == 97 || params->key == 65361)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->perso4.img, params->px, params->py);
	else if (params->key == 115 || params->key == 65364 || params->key == 0)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->perso1.img, params->px, params->py);
	else if (params->key == 100 || params->key == 65363)
		mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
			img->perso3.img, params->px, params->py);
}

int	check_wall(t_map *map, int j)
{
	int	i;
	int	line;

	if (map->kill[j][3] == 1)
	{
		line = ((map->kill[j][2]) / 32) + 1;
		i = (((map->kill[j][1] + map->kill[j][0]) / 32) + 1)
			+ (map->col * (line - 1)) + (line - 1);
		if (map->kill[j][0] == 1 && map->map[i] == '1')
			return (1);
		else if (map->kill[j][0] == -1 && map->map[i - 1] == '1')
			return (1);
	}
	else
	{
		line = ((map->kill[j][2] + map->kill[j][0]) / 32) + 1;
		i = ((map->kill[j][1] / 32) + 1) + (map->col * (line - 1)) + (line - 1);
		if (map->kill[j][0] == 1 && map->map[i + map->col] == '1')
			return (1);
		else if (map->kill[j][0] == -1 && map->map[i - 1] == '1')
			return (1);
	}
	return (0);
}

void	make_map(t_map *map, t_params *params, t_all_img *img)
{
	int	xy[2];
	int	i;

	xy[0] = 0;
	xy[1] = 0;
	i = -1;
	while (map->map[++i])
	{
		if (map->map[i] == '1')
			mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
				img->wall.img, xy[0], xy[1]);
		else if (map->map[i] == '0' || map->map[i] == 'C' || map->map[i] == 'P'
			|| map->map[i] == 'K' || map->map[i] == 'k')
			mlx_put_image_to_window(params->mlx_ptr, params->window_ptr,
				img->back.img, xy[0], xy[1]);
		else if (map->map[i] == 'E')
			put_exit(map, params, img, xy);
		xy[0] += 32;
		if (map->map[i] == '\n')
			xy[0] = 0;
		if (map->map[i] == '\n')
			xy[1] += 32;
	}
	put_item(map, params, img);
	return ;
}

void	number(t_params *params)
{
	char	*s;
	char	*s2;

	s2 = ft_itoa(params->count);
	if (params->count == 1)
	{
		s = ft_strjoin(s2, " move made");
		ft_printf("%s\n", s);
	}
	else
	{
		s = ft_strjoin(s2, " moves made");
		ft_printf("%s\n", s);
	}
	free(s2);
	mlx_string_put(params->mlx_ptr, params->window_ptr, 32, 24, 0xFFFFFFFF, s);
	free(s);
}
