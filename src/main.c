#include <X11/X.h>
#include <fractol.h>
#include <libft.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>

void generate_colors(t_fractol *fractol) {
	int iter = 0;
	float factor = 0;
	int r = 0;
	int g = 0;
	int b = 0;

	while (iter < fractol->max_iter) {
		factor = (float)iter / fractol->max_iter;
		float diff = 1. - factor;
		r = 9 * diff * pow(factor, 3) * 255;
		g = 15 * pow(diff, 2) * pow(factor, 2) * 255;
		b = 8.5 * pow(diff, 3) * factor * 255;
		fractol->colors[iter] = (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff);
		iter++;
	}
}

void init(t_fractol *fractol) {
	int width, height;


	width = 800;
	height = 600;
	ft_bzero(fractol, sizeof(t_fractol));
	fractol->mlx = mlx_init();
	fractol->window = mlx_new_window(fractol->mlx, width, height, "Fractol");
	fractol->image = generate_mlx_image(fractol->mlx, width, height);

	fractol->max_iter = 80;
	fractol->render_fn = mandelbrot;
	fractol->mouse = 0;
	fractol->scale = (width / 2. + height / 2.) / 4.;
	fractol->offset_x = width / 2. / fractol->scale * -1;
	fractol->offset_y = height / 2. / fractol->scale * -1;
	generate_colors(fractol);
}

int main(int argc, char *argv[]) {
	t_fractol fractol;

	init(&fractol);
	if (argc < 2 || argc > 3)
		return 1;
	printf("%s\n", argv[1]);
	mlx_key_hook(fractol.window, key_handler, &fractol);
	mlx_mouse_hook(fractol.window, wheel_handler, &fractol);
	mlx_expose_hook(fractol.window, expose_handler, &fractol);
	mlx_hook(fractol.window, MotionNotify, PointerMotionMask,
			mouse_motion_handler, &fractol);
	fractol.render_fn(&fractol);
	mlx_loop(fractol.mlx);
}
