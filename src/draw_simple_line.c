/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 08:35:29 by kcharla           #+#    #+#             */
/*   Updated: 2019/10/12 05:29:45 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_simple_line_x(void *m_p, void *w_p, t_point p1, t_point p2)
{
	t_point			d;
	unsigned char	blend_step;

	if (p1.x > p2.x)
		return (draw_simple_line_x(m_p, w_p, p2, p1));
	d.z = 0;
	p2.z = ft_abs(p2.x - p1.x);
	d.col = p2.y - p1.y;
	p1.z = ft_abs(d.col);
	d.col = (d.col > 0) - (d.col < 0);
	d.x = p1.x;
	d.y = p1.y;
	while (d.x <= p2.x)
	{
		blend_step = (d.x - p1.x) * MAX_BLEND / (p2.x - p1.x);
		mlx_pixel_put(m_p, w_p, d.x, d.y, blend(p2.col, p1.col, blend_step));
		d.z += p1.z;
		if (2 * d.z >= p2.z)
		{
			d.y += d.col;
			d.z -= p2.z;
		}
		d.x++;
	}
}

static void	draw_simple_line_y(void *m_p, void *w_p, t_point p1, t_point p2)
{
	t_point			d;
	unsigned char	blend_step;

	if (p1.y > p2.y)
		return (draw_simple_line_y(m_p, w_p, p2, p1));
	d.z = 0;
	p2.z = ft_abs(p2.y - p1.y);
	d.col = p2.x - p1.x;
	p1.z = ft_abs(d.col);
	d.col = (d.col > 0) - (d.col < 0);
	d.x = p1.x;
	d.y = p1.y;
	while (d.y <= p2.y)
	{
		blend_step = (((d.y - p1.y) * MAX_BLEND / (p2.y - p1.y)));
		mlx_pixel_put(m_p, w_p, d.x, d.y, blend(p2.col, p1.col, blend_step));
		d.z += p1.z;
		if (2 * d.z >= p2.z)
		{
			d.x += d.col;
			d.z -= p2.z;
		}
		d.y++;
	}
}

void		draw_simple_line(void *mlx_p, void *win_p, t_line l)
{
	double k;

	if ((l.p2->x) == (l.p1->x) && (l.p2->y) == (l.p1->y))
		return ;
	k = ((l.p2->x) == (l.p1->x)) ? 1 : ((l.p2->y) - (l.p1->y) + 0.0)
			/ ((l.p2->x) - (l.p1->x) + 0.0);
	if (ft_abs(k) >= 1)
		draw_simple_line_y(mlx_p, win_p, *(l.p1), *(l.p2));
	else
		draw_simple_line_x(mlx_p, win_p, *(l.p1), *(l.p2));
}
