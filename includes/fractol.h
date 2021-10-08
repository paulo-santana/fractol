#ifndef FRACTOL_H
# define FRACTOL_H
# define XK_MISCELLANY
# include <X11/keysymdef.h>

typedef struct s_image		t_image;
typedef struct s_fractol	t_fractol;

struct s_image {
	void			*img_ptr;
	char			*data;
	unsigned int	width;
	unsigned int	height;
	int				bpp;
	int				line_size;
	int				endian;
};

struct s_fractol {
	void			*mlx;
	void			*window;
	t_image			*image;
	int				shift;
	int				max_iter;
	void 			(*render_fn) (t_fractol *fractol);
	long double			c_real;
	long double			c_imag;
	unsigned int	colors[1024];
	int mouse;
	long double scale;
	long double offset_x;
	long double offset_y;
};

t_image	*generate_mlx_image(void *mlx_ptr, unsigned width, unsigned height);
int	key_handler(int keycode, void *param);
int expose_handler(void *param);
int mouse_motion_handler(int x, int y, void *param);
void draw_image(t_fractol *fractol);
void mandelbrot(t_fractol *fractol);
void generate_colors(t_fractol *fractol);
void julia(t_fractol *fractol);
void world_to_screen(t_fractol *fractol, long double world_x, long double world_y, int *screen_x, int *screen_y);
void screen_to_world(t_fractol *fractol, int screen_x, int screen_y, long double *world_x, long double *world_y);
int wheel_handler(int key, int x, int y, void *param);

#endif
