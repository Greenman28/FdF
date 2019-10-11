/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 08:35:37 by kcharla           #+#    #+#             */
/*   Updated: 2019/10/12 01:20:48 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ESC_KEY 53
#define R_KEY   15

#define SHIFT_KEY   257
#define CTRL_KEY    256

#define UP_KEY		126
#define DOWN_KEY	125
#define RIGHT_KEY	124
#define LEFT_KEY	123

#define HA_MIN 0
#define HA_MAX (M_PI * 2)
#define HA_DELTA (M_PI * 2 / 48)

#define VA_MIN 0
#define VA_MAX (M_PI / 2)
#define VA_DELTA (M_PI / 2 / 8)

#define SCALE_MIN 1
#define SCALE_MAX 100
#define SCALE_DELTA 1

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	double		va;
	double		ha;
	int			scale;
}				t_data;

double	clamp(double val, double min, double max)
{
	if (val < min)
	{
		return (min);
	}
	if (val > max)
	{
		return (max);
	}
	return (val);
}

double	cycle(double val, double min, double max)
{
	while (val > max)
	{
		val = min + (val - max);
	}
	return (val);
}

int		key_pressed(int key, void *data)
{
	t_data *d = (t_data *)data;
	//t_data d = param;

	printf("key pressed: %d (\'%c\')\n", key, (char) key);
	//printf("param: %d\n", b);
	if (key >= LEFT_KEY && key <= UP_KEY)
	{
		if (key == LEFT_KEY)
			d->ha = cycle(d->ha - HA_DELTA, HA_MIN, HA_MAX);
		else if (key == RIGHT_KEY)
			d->ha = cycle(d->ha + HA_DELTA, HA_MIN, HA_MAX);
		else if (key == UP_KEY)
			d->va = clamp(d->va + VA_DELTA, VA_MIN, VA_MAX);
		else if (key == DOWN_KEY)
			d->va = clamp(d->va - VA_DELTA, VA_MIN, VA_MAX);

		printf("va: %f, ha: %f\n",  d->va, d->ha);

		re_draw(d->mlx_ptr, d->win_ptr, d->va, d->ha, d->scale);
		return (0);
	}
	if (key == R_KEY || key == SHIFT_KEY || key == CTRL_KEY)
	{
		if (key == SHIFT_KEY)
			d->scale = clamp(d->scale + SCALE_DELTA, SCALE_MIN, SCALE_MAX);
		else if (key == CTRL_KEY)
			d->scale = clamp(d->scale - SCALE_DELTA, SCALE_MIN, SCALE_MAX);

		printf("scale: %d\n",  d->scale);

		re_draw(d->mlx_ptr, d->win_ptr, d->va, d->ha, d->scale);
		return (0);
	}
	//if ()
	if (key == ESC_KEY)
	{
		printf("esc pressed!\n");
		exit (0);
	}
	return (0);
}

int		main()
{
	void * mlx_ptr = mlx_init();
	void * win_ptr = mlx_new_window(mlx_ptr, 512, 512, "FdF");
	//void * win2_ptr = mlx_new_window(mlx_ptr, 512, 512, "FdF - 2");
	//win2_ptr = 0;
//	double vertical_angle = M_PI / 4;
//	double horizontal_angle = M_PI / 8;

	t_data d = {mlx_ptr, win_ptr, M_PI / 4, M_PI / 8, 10};

	mlx_key_hook(win_ptr, key_pressed, (void *) &d);

	draw_stuff(mlx_ptr, win_ptr, d.va, d.ha, d.scale);

	mlx_clear_window(mlx_ptr, win_ptr);
	//mlx_destroy_window(mlx_ptr, win_ptr);

	mlx_loop(mlx_ptr);
	return (0);
}