/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:41:16 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/18 10:41:21 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	protect_end(t_params *params, t_all_img *img)
{
	if (img->over.img == NULL)
		return (destroy_end(params, img));
	if (img->win.img == NULL)
		return (destroy_end(params, img));
	if (img->bye.img == NULL)
		return (destroy_end(params, img));
	return (1);
}

int	protect_perso(t_params *params, t_all_img *img)
{
	if (img->perso1.img == NULL)
		return (destroy_perso(params, img));
	else if (img->perso2.img == NULL)
		return (destroy_perso(params, img));
	else if (img->perso3.img == NULL)
		return (destroy_perso(params, img));
	else if (img->perso4.img == NULL)
		return (destroy_perso(params, img));
	else if (img->tail.img == NULL)
		return (destroy_perso(params, img));
	return (1);
}

int	protect_img(t_params *params, t_all_img *img)
{
	if (img->wall.img == NULL)
		return (destroy_img(params, img));
	else if (img->back.img == NULL)
		return (destroy_img(params, img));
	else if (img->item.img == NULL)
		return (destroy_img(params, img));
	else if (img->exit.img == NULL)
		return (destroy_img(params, img));
	else if (img->exit2.img == NULL)
		return (destroy_img(params, img));
	else if (img->kill.img == NULL)
		return (destroy_img(params, img));
	else if (img->kill2.img == NULL)
		return (destroy_img(params, img));
	return (1);
}
