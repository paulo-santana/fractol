#include <fractol.h>
#include <math.h>

static inline unsigned int get_color(t_fractol *fractol, unsigned x, unsigned y)
{
	double R = 4;
	double real = 0;
	double imag = 0;
	int i = 0;
	double x2 = 0, y2 = 02;

	//screen_to_world(fractol, x, y, &real, &imag);
	real = x / fractol->scale + fractol->offset_x;
	imag = y / fractol->scale + fractol->offset_y;
	x2 = real * real;
	y2 = imag * imag;
	while (x2 + y2 <= R && i < fractol->max_iter)
	{
		imag =  (real + real) * imag + fractol->c_imag;
		real = x2 - y2 + fractol->c_real;
		x2 = real * real;
		y2 = imag * imag;
		i++;
	}
	/* if (i == fractol->max_iter) */
	/* 	return 0; */
	if (fractol->shift > 0)
		return (fractol->colors[i]) << fractol->shift;
	return (fractol->colors[i]);
}

void julia(t_fractol *fractol)
{
	unsigned int y, x;
	int current_row;
	y = 0;
	generate_colors(fractol);
	while (y < fractol->image->height)
	{
		x = 0;
		current_row = y * fractol->image->width;
		while (x < fractol->image->width)
		{
			((unsigned int*)fractol->image->data)[x + current_row] = get_color(fractol, x, y);
			x++;
		}
		y++;
	}
	draw_image(fractol);
}
