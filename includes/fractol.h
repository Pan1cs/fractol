/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 16:11:04 by eparviai          #+#    #+#             */
/*   Updated: 2020/08/19 16:11:06 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Required system headers
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

/*
** Required user headers
*/

# include "mlx.h"
# include "libft.h"
# include "keys.h"

/*
** Value Macros (self explanatory)
*/

# define WIDTH			500
# define HEIGHT			500
# define MAX_ITER		75
# define FMAX			2.0
# define FMIN			-2.0
# define GREY			0xBBBBBB

/*
**	Defined Fractal sets
*/

/*
** Fractol Structures
**
** t_mlx   : required minilibx arguments.
** t_image : variables to be used for creation of the image (map).
**           data -> Image information.
**           size -> move from one line to another in the image.
**           endian -> Stores the Endian of the system, defining how to
**			 store the color
**           bpp -> Bits-per-pixel.
** t_map   : values used to manipulate the fractal map.
** t_color : define the color, argb value (32-bits).
*/

typedef struct	s_mlx
{
	void		*init;
	void		*win;
}				t_mlx;

typedef struct	s_image
{
	void		*ptr;
	int			*data;
	int			size;
	int			endian;
	int			bpp;
}				t_image;

typedef struct 	s_comp
{
	double		x;
	double		y;
	double		zx;
	double		zy;
	double		zx2;
	double		zy2;
}				t_comp;

typedef struct	s_color
{
	int			a;
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_fract
				t_fract;

typedef struct 	s_fract
{
	double			zoom;
	int				(*f)(t_fract *fract, int i);
	int 			y;
	int 			x;
	int				i;
	int				stop;
	double			x_offset;
	double			y_offset;
	double			min_x;
	double			max_x;
	double 			min_y;
	double 			max_y;
	double			x_fctr;
	double			y_fctr;
	double			t;
	double			mouse_x;
	double			mouse_y;
	t_color			color_1;
	t_color			color_2;
	t_color			color_3;
	t_color			color_4;
	t_comp 			comp;
	t_image			img;
	t_mlx			mlx;
}				t_fract;

void				init_fract(t_fract *fract, char *str);
void				setup_fract(t_fract *fract);
void				choose_color(int i, t_fract *fract);
int					fractal_draw(t_fract *fract);
void				output(int error);
int					fract_keys(int key, t_fract *fract);
int					fract_mouse(int key,int x, int y, t_fract *fract);
int					mouse_move(int x, int y, t_fract *fract);
int					mandelbrot(t_fract *fract, int i);
int					julia(t_fract *fract, int i);
int					burningship(t_fract *fract, int i);

#endif
