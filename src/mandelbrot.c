#include <fractol.h>
#include <mlx.h>

static inline unsigned int get_color(t_fractol *fractol, unsigned int x, unsigned int y)
{
	double x2 = 0, y2 = 0;
	long double real = 0;
	long double imag = 0;
	int i = 0;
	long double c_real, c_imag;

	screen_to_world(fractol, x, y, &c_real, &c_imag);
	while (x2 + y2 <= 4 && i < fractol->max_iter)
	{
		imag = (real + real) * imag + c_imag;
		real = x2 - y2 + c_real;
		x2 = real * real;
		y2 = imag * imag;
		i++;
	}
	return (fractol->colors[i]) << fractol->shift;
}

void mandelbrot(t_fractol *fractol)
{
	unsigned int i, j;
	int current_row;

	i = 0;
	generate_colors(fractol);
	while (i < fractol->image->height)
	{
		j = 0;
		current_row = i * fractol->image->width;
		while (j < fractol->image->width)
		{
			((unsigned int*)fractol->image->data) [j + current_row] = get_color(fractol, j, i);
			j++;
		}
		i++;
	}
	draw_image(fractol);
}
