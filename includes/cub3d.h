/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr  >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/25 11:35:27 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/includes/libft.h"
# include "../libraries/mlx/include/MLX42/MLX42.h"
# include <sys/stat.h>
# include <fcntl.h>


# define MSG_ERROR "\033[1;41mError!\033[0m\n\033[0;31m"
# define MSG_LEN_ERROR 25

# define MSG_ARG_COUNT "Arguments: Invalid number of arguments.\n"
# define MSG_INV_EXEC "Invalid .cub map file\n"
# define MSG_INV_TEXTURES "Invalid texture configurations\n"
# define MSG_INV_COLORS "Invalid RGB colors configurations\n"
# define MSG_INV_ARG "Invalid arguments\n"

# define MSG_ERROR_EXIT "\033[0m\n"
# define MSG_LEN_ERROR_EXIT 5

# define FALSE 0
# define TRUE 1

# define WIDTH 720
# define HEIGHT 480

# define BLACK_COLOR 0x00000FF
# define RED_COLOR 0xFFFFFFFF

typedef struct s_rgb_colors
{
	char	floor_color[50];
	char	ceiling_color[50];
}	t_rgb_colors;

typedef struct s_texture_paths
{
	char	no_texture_path[50];
	char	so_texture_path[50];
	char	we_texture_path[50];
	char	ea_texture_path[50];
}	t_texture_paths;

typedef struct s_player_start
{
	int x;
	int y;
	char orientation;
}	t_player_start;

typedef struct s_cub3d
{
	t_texture_paths	texture_paths;
	t_rgb_colors	rgb_colors;
	char			map[8][6];
	t_player_start	player_start;
}	t_cub3d;


int	handle_mlx(mlx_t **mlx, mlx_image_t **image);
void	key_hook(mlx_key_data_t keydata, void *mlx);
void	draw_box(mlx_image_t *image, int height, int width, int beginx, int beginy, int color);
void	draw_player_minimap (mlx_image_t *image, t_cub3d *s_cub3d);
#endif
