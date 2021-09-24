#include <libft.h>
#include <stdio.h>
#include <fractol.h>
#include <mlx.h>
#include <X11/X.h>
#include <math.h>

void generate_colors(t_fractol *fractol)
{
	int		iter = 0;
	float	factor = 0;
	int		r = 0;
	int		g = 0;
	int		b = 0;

	while (iter < fractol->max_iter)
	{
		factor = (float)iter / fractol->max_iter;
		if (iter < fractol->max_iter / 2)
			fractol->colors[iter] = 255 * iter / fractol->max_iter;
		else
		{
			float diff = 1. - factor;
			r = 9 * diff * pow(factor, 3) * 255;
			g = 15 * pow(diff, 2) * pow(factor, 2) * 255;
			b = 8.5 * pow(diff, 3) * factor * 255;
			fractol->colors[iter] = (r & 0xff) << 16 |(g & 0xff) << 8 | (b & 0xff);
		}
		iter++;
	}
}

void init(t_fractol *fractol)
{
	ft_bzero(fractol, sizeof(t_fractol));
	fractol->mlx = mlx_init();
	fractol->window = mlx_new_window(fractol->mlx, 800, 600, "Fractol");
	fractol->image = generate_mlx_image(fractol->mlx, 800, 600);
	 
	fractol->max_iter = 255;
	fractol->render_fn = julia;
	fractol->mouse = 1;
	fractol->scale = 300;
	fractol->offset_x = -1.5;
	fractol->offset_y = -1.0;
	generate_colors(fractol);
}

int main(int argc, char *argv[])
{
	t_fractol fractol;

	init(&fractol);
	if (argc < 2 || argc > 3)
		return 1;
	printf("%s\n", argv[1]);
	mlx_key_hook(fractol.window, key_handler, &fractol);
	mlx_mouse_hook(fractol.window, wheel_handler, &fractol);
	mlx_expose_hook(fractol.window, expose_handler, &fractol);
	if (fractol.render_fn == julia)
		mlx_hook(fractol.window, MotionNotify, PointerMotionMask, mouse_motion_handler, &fractol);
	fractol.render_fn(&fractol);
	mlx_loop(fractol.mlx);
}
