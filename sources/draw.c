/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:27:24 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 19:57:36 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static uint32_t		get_color(t_cub3d *s_cub3d);

void	draw_texturized_line(int x, t_cub3d *s_cub3d)
{
	int	i;

	i = s_cub3d->wall.draw_start;
	while (i < s_cub3d->wall.draw_end)
	{
		s_cub3d->textures.texture_y = (int)s_cub3d->textures.texture_pos;
		s_cub3d->textures.texture_pos += s_cub3d->textures.step;
		mlx_put_pixel(s_cub3d->image, x, i, get_color(s_cub3d));
		i++;
	}
}

static uint32_t	get_color(t_cub3d *s_cub3d)
{
	uint8_t	*pixel;
	int		texture_y;
	int		texture_x;

	texture_y = s_cub3d->textures.texture_y;
	texture_x = s_cub3d->textures.texture_x;
	pixel = &s_cub3d->textures.wall_texture->pixels[(texture_y
			* s_cub3d->textures.wall_texture->width + texture_x)
		* s_cub3d->textures.wall_texture->bytes_per_pixel];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	draw_box(mlx_image_t *image, int beginx, int beginy, uint32_t color)
{
	int	temp;
	int	x;
	int	y;

	temp = beginx;
	x = 0;
	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(image, beginx, beginy, color);
			beginx++;
			x++;
		}
		beginx = temp;
		x = 0;
		y += 1;
		beginy++;
	}
}

static u_int32_t	str_to_color(char *str)
{
	char		**rgb;
	u_int32_t	color;

	rgb = ft_split(str, ',');
	color = ft_atoi(rgb[0]) << 24 | ft_atoi(rgb[1]) << 16
		| ft_atoi(rgb[2]) << 8 | 255;
	ft_for_each((void **)rgb, free);
	free(rgb);
	return (color);
}

void	draw_background(t_cub3d *s_cub3d)
{
	draw_box(s_cub3d->image, 0, 0,
		str_to_color(s_cub3d->rgb_colors.floor_color));
	draw_box(s_cub3d->image, 0, SCREEN_HEIGHT / 2,
		str_to_color(s_cub3d->rgb_colors.ceiling_color));
}
