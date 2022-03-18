/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:34:27 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/15 10:34:29 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux/mlx.h"
# include "libft/headers/libft.h"
# include "libft/headers/ft_printf.h"
# include <fcntl.h>
# include <unistd.h>

typedef struct s_map
{
	int		line;
	int		col;
	int		item_nbr;
	int		kill_nbr;
	int		e;
	int		p;
	char	*map;
	int		**item;
	int		**exit;
	int		**kill;
	int		direction;
}			t_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}			t_img;

typedef struct s_all_img
{
	t_img	wall;
	t_img	back;
	t_img	exit;
	t_img	exit2;
	t_img	over;
	t_img	win;
	t_img	bye;
	t_img	item;
	t_img	kill;
	t_img	kill2;
	t_img	perso1;
	t_img	perso2;
	t_img	perso3;
	t_img	perso4;
	t_img	tail;
}			t_all_img;

typedef struct s_params
{
	void		*mlx_ptr;
	void		*window_ptr;
	t_all_img	*img;
	t_map		*map;
	int			count;
	int			px;
	int			py;
	int			key;
}				t_params;

//parsing_map.c
int		map_info(char *map, t_map *map_infos);
//images.c
int		create_img(t_params *params, t_all_img *img);
int		destroy_perso(t_params *params, t_all_img *img);
int		destroy_end(t_params *params, t_all_img *img);
//clean.c
void	clean(t_params *params, t_map *map, t_all_img *img);
char	*cpy(char *buff, char **map);
int		error_img(t_params *params, t_map *map);
int		destroy_img(t_params *params, t_all_img *img);
//show.c
void	put_perso(t_params *params, t_all_img *img, int i);
void	make_map(t_map *map, t_params *params, t_all_img *wall);
int		check_wall(t_map *map, int j);
//events.c
int		deal_key(int key, t_params *params);
int		deal_cross(t_params *params);
//items.c
int		items(t_map *map);
void	put_item(t_map *map, t_params *params, t_all_img *img);
//kill.c
int		kill(t_map *map);
//end.c
void	if_win(t_map *map, t_params *params, t_all_img *img, int r);
//exit.c
int		end(t_map *map, t_params *params, t_all_img *img);
int		exits(t_map	*map);
void	put_exit(t_map *map, t_params *params, t_all_img *img, int *xy);
//protect.c
int		protect_end(t_params *params, t_all_img *img);
int		protect_perso(t_params *params, t_all_img *img);
int		protect_img(t_params *params, t_all_img *img);

#endif
