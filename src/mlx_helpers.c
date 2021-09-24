#include <fractol.h>
#include <mlx.h>
#include <stdlib.h>

void draw_image(t_fractol *fractol)
{
	mlx_put_image_to_window(fractol->mlx, fractol->window,
			fractol->image->img_ptr, 0, 0);
}

t_image *generate_mlx_image(void *mlx_ptr, unsigned width, unsigned height)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (image == NULL)
		exit(1);
	image->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (image->img_ptr == NULL)
		exit(1);
	image->data = mlx_get_data_addr(image->img_ptr, &image->bpp,
			&image->line_size, &image->endian);
	if (image->data == NULL)
		exit(1);
	image->width = width;
	image->height = height;
	return (image);
}
