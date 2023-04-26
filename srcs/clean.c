/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:33:01 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/15 10:33:05 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	destroy_img(t_params *params, t_all_img *img)
{
	if (img->wall.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->wall.img);
	if (img->back.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->back.img);
	if (img->item.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->item.img);
	if (img->exit.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->exit.img);
	if (img->exit2.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->exit2.img);
	if (img->kill.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->kill.img);
	if (img->kill2.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->kill2.img);
	return (0);
}

int	error_img(t_params *params, t_map *map)
{
	mlx_destroy_window(params->mlx_ptr, params->window_ptr);
	free(map->map);
	mlx_destroy_display(params->mlx_ptr);
	free(params->mlx_ptr);
	return (0);
}

static void	free_tab(t_map *map)
{
	int	i;

	i = -1;
	if (map->item != NULL)
	{
		while (++i < map->item_nbr)
			free(map->item[i]);
		free(map->item);
	}
	i = -1;
	if (map->kill != NULL)
	{
		while (++i < map->kill_nbr)
			free(map->kill[i]);
		free(map->kill);
	}
	i = -1;
	if (map->exit != NULL)
	{
		while (++i < map->e)
			free(map->exit[i]);
		free(map->exit);
	}
}

void	clean(t_params *params, t_map *map, t_all_img *img)
{
	free_tab(map);
	destroy_img(params, img);
	destroy_perso(params, img);
	destroy_end(params, img);
	error_img(params, map);
}

char	*cpy(char *buff, char **map)
{
	char	*cpy;

	if (*map == NULL)
		*map = ft_strdup(buff);
	else
	{
		cpy = ft_strjoin(*map, buff);
		free(*map);
		*map = cpy;
	}
	return (*map);
}
