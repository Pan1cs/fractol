/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 15:19:47 by eparviai          #+#    #+#             */
/*   Updated: 2020/09/09 19:19:49 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_fract(t_fract *fract, char *str)
{
	if (ft_strequ(str, "mandelbrot"))
		fract->f = &mandelbrot;
	if (ft_strequ(str, "julia"))
		fract->f = &julia;
	if (ft_strequ(str, "burningship"))
		fract->f = &burningship;
	if (!(fract->f))
		output(1);
	fract->mlx.init = mlx_init();
	fract->img.ptr = mlx_new_image(fract->mlx.init, WIDTH, HEIGHT);
	fract->mlx.win = mlx_new_window(fract->mlx.init, WIDTH, HEIGHT,
		str);
	fract->img.data = (int*)mlx_get_data_addr(fract->img.ptr, &fract->img.bpp,
		&fract->img.size, &fract->img.endian);
	setup_fract(fract);
}

void		setup_fract(t_fract *fract)
{
	fract->max_x = FMAX;
	fract->min_x = FMIN;
	fract->max_y = FMAX;
	fract->min_y = FMIN;
	fract->zoom = 1;
	fract->stop = 0;
	fract->y_offset = 0.0;
	fract->x_offset = 0.0;
	fract->mouse_x = WIDTH / 2;
	fract->mouse_y = HEIGHT / 2;
	fract->i = 0;
	fract->x_fctr = (fract->max_x - fract->min_x) / fract->zoom / (WIDTH - 1);
	fract->y_fctr = (fract->max_y - fract->min_y) / fract->zoom / (HEIGHT - 1);
	choose_color(1, fract);
}

int			fract_keys(int key, t_fract *fract)
{
	if (key == KEY_ESCAPE)
		exit(0);
	else if (key == KEY_ANSI_KEYPAD5)
		fract->y_offset -= 0.02 / fract->zoom;
	else if (key == KEY_ANSI_KEYPAD8)
		fract->y_offset += 0.02 / fract->zoom;
	else if (key == KEY_ANSI_KEYPAD6)
		fract->x_offset += 0.02 / fract->zoom;
	else if (key == KEY_ANSI_KEYPAD4)
		fract->x_offset -= 0.02 / fract->zoom;
	else if (key == KEY_ANSI_KEYPAD1)
		choose_color(1, fract);
	else if (key == KEY_ANSI_KEYPAD2)
		choose_color(2, fract);
	else if (key == KEY_ANSI_KEYPAD3)
		choose_color(3, fract);
	else if (key == KEY_ANSI_KEYPADPLUS)
		fract->zoom *= 1.2;
	else if (key == KEY_ANSI_KEYPADMINUS)
		fract->zoom /= 1.4;
	else if (key == KEY_SPACE)
		fract->stop = (fract->stop == 1 ? 0 : 1);
	fractal_draw(fract);
	return (1);
}

int			fract_mouse(int key, int x, int y, t_fract *fract)
{
	double	min;
	double	max;

	if (key == WhUp)
		fract->zoom *= 1.2;
	else if ((key == WhDn) && (fract->zoom * 0.75 > 0.5))
		fract->zoom *= 0.6;
	min = FMIN / fract->zoom;
	max = FMAX / fract->zoom;
	fract->x_fctr = (FMAX - FMIN) / fract->zoom / (WIDTH - 1);
	fract->y_fctr = (FMAX - FMIN) / fract->zoom / (HEIGHT - 1);
	fract->x_offset += fract->x_fctr * (x - WIDTH * 0.5);
	fract->y_offset -= fract->y_fctr * (y - HEIGHT * 0.5);
	fractal_draw(fract);
	return (1);
}

int			mouse_move(int x, int y, t_fract *fract)
{
	if (fract->stop == 1)
		return (0);
	fract->mouse_x = fract->x_fctr * (x - WIDTH * 0.5);
	fract->mouse_y = fract->y_fctr * (y - HEIGHT * 0.5);
	if (fract->f == &julia)
		fractal_draw(fract);
	return (1);
}
