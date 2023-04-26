/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:33:40 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/15 10:33:43 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static void	get_perso(t_params *params, t_map *map)
{
	int	i;
	int	line;

	i = 0;
	line = 1;
	while (map->map[i] != 'P')
	{
		if (map->map[i] == '\n')
			line++;
		i++;
	}
	if (map->map[i] == 'P')
	{
		params->py = (line - 1) * 32;
		params->px = (((i - line) % map->col) + 1) * 32;
	}
	return ;
}

static int	initial(t_map *map, t_params *params)
{
	if (map->item_nbr <= 0 || map->p != 1)
	{
		free(map->map);
		return (0);
	}
	params->mlx_ptr = mlx_init();
	if (params->mlx_ptr == NULL)
	{
		free(map->map);
		return (0);
	}
	params->window_ptr = mlx_new_window(params->mlx_ptr, map->col * 32,
			map->line * 32, "This is my game !");
	if (params->window_ptr == NULL)
	{
		free(map->map);
		free(params->mlx_ptr);
		return (0);
	}
	get_perso(params, map);
	return (1);
}

static int	start(t_params *params, t_map *map, t_all_img *img, char *file)
{
	int	i;

	i = ft_strlen(file);
	if (file[i] != '\0' || file[--i] != 'r' || file[--i] != 'e'
		|| file[--i] != 'b' || file[--i] != '.')
	{
		ft_printf("Error\nWrong file type\n");
		return (0);
	}
	if (map_info(file, map) == 0)
		return (0);
	if (map->line > 42 || map->col > 80)
	{
		ft_printf("Error\nToo big for screen\n");
		free(map->map);
		return (0);
	}
	if (initial(map, params) == 0)
		return (0);
	if (create_img(params, img) == 0)
		return (error_img(params, map));
	if (items(map) == 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map		map_infos;
	t_params	params;
	t_all_img	img;

	if (argc != 2)
		return (0);
	if (start(&params, &map_infos, &img, argv[1]) == 0)
		return (0);
	params.key = 0;
	params.count = 0;
	make_map(&map_infos, &params, &img);
	params.img = &img;
	params.map = &map_infos;
	mlx_key_hook(params.window_ptr, deal_key, &params);
	mlx_hook(params.window_ptr, 17, 0, deal_cross, &params);
	mlx_loop(params.mlx_ptr);
	map_infos.p = -40000000;
	while (map_infos.p++ < 400000000)
		ft_strlen(NULL);
	clean(&params, &map_infos, &img);
	return (0);
}
