/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 13:55:24 by eparviai          #+#    #+#             */
/*   Updated: 2020/08/17 13:55:26 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		output(int error)
{
	if (error == 1)
	{
		ft_putstr("Usage:\n\t");
		ft_putstr("fractol");
		ft_putstr(" 'fractal name'\n");
		ft_putstr(" Available fractals.\x1B[32m\n"
			"  julia\n\n  mandelbrot\n\n"
			"  burningship.\n \x1B[0m");
		ft_putstr("Controls:\n");
		ft_putstr("\t\x1B[32m[Esc]				  \x1B[0m->"
		" \x1B[32mExit the program.\n");
		ft_putstr("\t[R]				  \x1B[0m->"
		"\x1B[32m Reset the map.\n");
		ft_putstr("\t[M]			   	  \x1B[0m->"
		"\x1B[32m Randomize colors.\n");
		ft_putstr("\t[+][-]			  	  \x1B[0m->"
		"\x1B[32m Zoom in and zoom out.\n");
		ft_putstr("\t[1][2]				  \x1B[0m->"
		"\x1B[32m Change between 2 color schemes\n");
		ft_putstr("\t[Mousemove & scroll]		  \x1B[0m->"
		"\x1B[32m You can zoom with scroll and move with mouse\n");
		ft_putstr("\t[kp8][kp4][kp5][kp6]		  \x1B[0m->"
		"\x1B[32m Move the map.\n\x1B[0m");
	}
	exit(-1);
}

void		choose_color(int i, t_fract *fract)
{
	if (i == 1)
	{
		fract->color_1 = (t_color){0, 42, 20, 20};
		fract->color_2 = (t_color){0, 255, 12, 12};
		fract->color_3 = (t_color){0, 255, 128, 0};
		fract->color_4 = (t_color){0, 187, 187, 187};
	}
	if (i == 2)
	{
		fract->color_1 = (t_color){0};
		fract->color_2 = (t_color){0, 20, 70, 255};
		fract->color_3 = (t_color){0, 20, 255, 42};
		fract->color_4 = (t_color){0, 187, 187, 187};
	}
	if (i == 3)
	{
		fract->color_1 = (t_color){0, 42, 42, 42};
		fract->color_2 = (t_color){0, 0, 170, 155};
		fract->color_3 = (t_color){0, 255, 0, 10};
		fract->color_4 = (t_color){0, 187, 187, 187};
	}
}

int			main(int argc, char **argv)
{
	t_fract	fract;
	int		i;

	i = argc;
	if (argc < 2)
		output(1);
	init_fract(&fract, argv[i - 1]);
	if (fract.mlx.init)
	{
		mlx_hook(fract.mlx.win, 6, 0, mouse_move, &fract);
		mlx_mouse_hook(fract.mlx.win, &fract_mouse, &fract);
		mlx_key_hook(fract.mlx.win, &fract_keys, &fract);
		mlx_loop(fract.mlx.init);
	}
	return (0);
}
