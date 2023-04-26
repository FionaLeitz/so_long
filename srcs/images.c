/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:33:29 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/15 10:33:33 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	destroy_end(t_params *params, t_all_img *img)
{
	if (img->over.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->over.img);
	if (img->win.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->win.img);
	if (img->bye.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->bye.img);
	return (0);
}

static int	create_end(t_params *params, t_all_img *img)
{
	img->over.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/game_over2.xpm", &img->over.width, &img->over.height);
	img->win.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/win2.xpm", &img->win.width, &img->win.height);
	img->bye.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/bye2.xpm", &img->bye.width, &img->bye.height);
	return (protect_end(params, img));
}

int	destroy_perso(t_params *params, t_all_img *img)
{
	if (img->perso1.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->perso1.img);
	if (img->perso2.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->perso2.img);
	if (img->perso3.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->perso3.img);
	if (img->perso4.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->perso4.img);
	if (img->tail.img != NULL)
		mlx_destroy_image(params->mlx_ptr, img->tail.img);
	return (0);
}

static int	create_perso(t_params *params, t_all_img *img)
{
	img->perso1.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/perso_1.xpm", &img->perso1.width, &img->perso1.height);
	img->perso2.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/perso_2.xpm", &img->perso2.width, &img->perso2.height);
	img->perso3.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/perso_3.xpm", &img->perso3.width, &img->perso3.height);
	img->perso4.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/perso_4.xpm", &img->perso4.width, &img->perso4.height);
	img->tail.img = mlx_xpm_file_to_image(params->mlx_ptr,
			"./xpm/tail.xpm", &img->tail.width, &img->tail.height);
	return (protect_perso(params, img));
}

int	create_img(t_params *params, t_all_img *img)
{
	img->wall.img = mlx_xpm_file_to_image(params->mlx_ptr, "./xpm/wall.xpm",
			&img->wall.width, &img->wall.height);
	img->back.img = mlx_xpm_file_to_image(params->mlx_ptr, "./xpm/back.xpm",
			&img->back.width, &img->back.height);
	img->item.img = mlx_xpm_file_to_image(params->mlx_ptr, "./xpm/item.xpm",
			&img->item.width, &img->item.height);
	img->exit.img = mlx_xpm_file_to_image(params->mlx_ptr, "./xpm/exit1.xpm",
			&img->exit.width, &img->exit.height);
	img->exit2.img = mlx_xpm_file_to_image(params->mlx_ptr, "./xpm/exit2.xpm",
			&img->exit2.width, &img->exit2.height);
	img->kill.img = mlx_xpm_file_to_image(params->mlx_ptr, "./xpm/vilain.xpm",
			&img->kill.width, &img->kill.height);
	img->kill2.img = mlx_xpm_file_to_image(params->mlx_ptr, "./xpm/vilain2.xpm",
			&img->kill2.width, &img->kill2.height);
	if (protect_img(params, img) == 0)
		return (0);
	if (create_perso(params, img) == 0)
		return (destroy_img(params, img));
	if (create_end(params, img) == 0)
	{
		destroy_img(params, img);
		return (destroy_perso(params, img));
	}
	return (1);
}
