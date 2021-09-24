#include <fractol.h>
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>

int expose_handler(void *param)
{
	t_fractol *fractol;

	fractol = param;
	draw_image(fractol);
	return (0);
}

inline void world_to_screen(t_fractol *fractol, double world_x, double world_y, int *screen_x, int *screen_y)
{
	*screen_x = (world_x - fractol->offset_x) * fractol->scale;
	*screen_y = (world_y - fractol->offset_y) * fractol->scale;
}

inline void screen_to_world(t_fractol *fractol, int screen_x, int screen_y, double *world_x, double *world_y)
{
	*world_x = ((float)screen_x) / fractol->scale + fractol->offset_x;
	*world_y = ((float)screen_y) / fractol->scale + fractol->offset_y;
}

void apply_zoom(t_fractol *fractol, float factor)
{
	int x, y;

	double mouse_world_x_before_zoom;
	double mouse_world_y_before_zoom;
	double mouse_world_x_after_zoom;
	double mouse_world_y_after_zoom;

	mlx_mouse_get_pos(fractol->mlx, fractol->window, &x, &y);
	screen_to_world(fractol, x, y, &mouse_world_x_before_zoom, &mouse_world_y_before_zoom);
	fractol->scale *= factor;
	screen_to_world(fractol, x, y, &mouse_world_x_after_zoom, &mouse_world_y_after_zoom);
	fractol->offset_x += mouse_world_x_before_zoom - mouse_world_x_after_zoom;
	fractol->offset_y += mouse_world_y_before_zoom - mouse_world_y_after_zoom;
}

int	key_handler(int keycode, void *param)
{
	t_fractol *fractol;

	fractol = param;
	if (keycode == XK_Escape)
		exit(0);
	else if (keycode == 'k')
	{
		if (fractol->shift < 23)
			fractol->shift++;
	}
	else if (keycode == 'j')
	{
		if (fractol->shift > 0)
			fractol->shift--;
	}
	else if (keycode == 'h')
	{
		if (fractol->max_iter < 1024)
			fractol->max_iter++;
	}
	else if (keycode == 'l')
	{
		if (fractol->max_iter > 0)
			fractol->max_iter--;
	}
	else if (keycode == ' ')
	{
		fractol->mouse = !fractol->mouse;
	}
	else if (keycode == 'f')
		apply_zoom(fractol, .9);
	else if (keycode == 'g')
		apply_zoom(fractol, 1.1);
	generate_colors(fractol);
	fractol->render_fn(fractol);
	return (0);
}

int mouse_motion_handler(int x, int y, void *param)
{
	char buff[100];
	t_fractol *fractol;

	fractol = param;
	if (!fractol->mouse)
		return (1);
	screen_to_world(fractol, x, y, &fractol->c_real, &fractol->c_imag);
	fractol->render_fn(fractol);
	sprintf(buff, "coord: %.3f %.3fi", fractol->c_real, fractol->c_imag);
	mlx_string_put(fractol->mlx, fractol->window, 15, 15, 0xff5700, buff);
	return (0);
}

int wheel_handler(int key, int x, int y, void *param)
{
	t_fractol *fractol;

	(void)x;
	(void)y;

	fractol = param;
	if (key == 5)
		apply_zoom(fractol, .9);
	else if (key == 4)
		apply_zoom(fractol, 1.1);
	fractol->render_fn(fractol);
	return (1);
}
