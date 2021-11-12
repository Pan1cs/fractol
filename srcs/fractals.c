/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:01:42 by eparviai          #+#    #+#             */
/*   Updated: 2020/08/19 18:01:43 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	int		color_pixel(t_fract *fract, t_color c1, t_color c2, t_color c3)
{
	fract->t = ((fract->i / (MAX_ITER + (fract->zoom * 0.09))) * 3);
	if (fract->t < 1)
	{
		c1 = fract->color_1;
		c2 = fract->color_2;
	}
	else if (fract->t < 2.0)
	{
		c1 = fract->color_2;
		c2 = fract->color_3;
	}
	else if (fract->t < 3.0)
	{
		c1 = fract->color_3;
		c2 = fract->color_4;
	}
	else
		return ((fract->img.data[(fract->y * WIDTH) + fract->x] = GREY));
	fract->t = fabs(fract->t - round(fract->t));
	c3.r = c1.r - fract->t + c2.r * fract->t;
	c3.g = c1.g - fract->t + c2.g * fract->t;
	c3.b = c1.b - fract->t + c2.b * fract->t;
	return ((fract->img.data[(fract->y * WIDTH) + fract->x] =
			rgb2int(0x10000, c3.r, c3.g, c3.b)));
}

int				mandelbrot(t_fract *fract, int i)
{
	fract->comp.zx = fract->comp.x;
	fract->comp.zy = fract->comp.y;
	while (i < (MAX_ITER + (fract->zoom * 0.09)))
	{
		fract->comp.zx2 = fract->comp.zx * fract->comp.zx;
		fract->comp.zy2 = fract->comp.zy * fract->comp.zy;
		if (fract->comp.zx2 + fract->comp.zy2 > 4)
			break ;
		fract->comp.zy = 2 * fract->comp.zx * fract->comp.zy + fract->comp.y;
		fract->comp.zx = fract->comp.zx2 - fract->comp.zy2 + fract->comp.x;
		i++;
	}
	return (i);
}

int				julia(t_fract *fract, int i)
{
	fract->comp.zx = fract->comp.x;
	fract->comp.zy = fract->comp.y;
	while (i < (MAX_ITER + (fract->zoom * 0.09)))
	{
		fract->comp.zx2 = fract->comp.zx * fract->comp.zx;
		fract->comp.zy2 = fract->comp.zy * fract->comp.zy;
		if (fract->comp.zx2 + fract->comp.zy2 > 4)
			break ;
		fract->comp.zy = (2 * fract->comp.zx * fract->comp.zy) +
			(fract->y_fctr - fract->mouse_y);
		fract->comp.zx = (fract->comp.zx2 - fract->comp.zy2) +
			(fract->x_fctr + fract->mouse_x);
		i++;
	}
	return (i);
}

int				burningship(t_fract *fract, int i)
{
	fract->comp.zx = fract->comp.x;
	fract->comp.zy = fract->comp.y;
	while (i < (MAX_ITER + (fract->zoom * 0.09)))
	{
		fract->comp.zx = fabs(fract->comp.zx);
		fract->comp.zy = fabs(fract->comp.zy);
		fract->comp.zx2 = fract->comp.zx * fract->comp.zx;
		fract->comp.zy2 = fract->comp.zy * fract->comp.zy;
		if (fract->comp.zx2 + fract->comp.zy2 > 4)
			break ;
		fract->comp.zy = (2 * fract->comp.zx * fract->comp.zy) + fract->comp.y;
		fract->comp.zx = (fract->comp.zx2 - fract->comp.zy2) + fract->comp.x;
		i++;
	}
	return (i);
}

int				fractal_draw(t_fract *fract)
{
	t_color			c1;
	t_color			c2;
	t_color			c3;
	t_fract			*tf;

	tf = fract;
	tf->x_fctr = (tf->max_x - tf->min_x) / tf->zoom / (WIDTH - 1);
	tf->y_fctr = (tf->max_y - tf->min_y) / tf->zoom / (HEIGHT - 1);
	tf->y = 0;
	while (tf->y < HEIGHT)
	{
		tf->comp.y = (tf->max_y - tf->y * tf->y_fctr) + tf->y_offset;
		tf->x = 0;
		while (tf->x < WIDTH)
		{
			tf->comp.x = (tf->min_x + tf->x * tf->x_fctr) + tf->x_offset;
			tf->i = tf->f(tf, tf->i);
			color_pixel(tf, c1, c2, c3);
			tf->x++;
			tf->i = 0;
		}
		tf->y++;
	}
	mlx_put_image_to_window(tf->mlx.init, tf->mlx.win, tf->img.ptr, 0, 0);
	return (0);
}
