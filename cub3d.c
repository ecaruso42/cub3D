/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:07:13 by grinella          #+#    #+#             */
/*   Updated: 2024/05/24 15:07:14 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec + (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

//FUNZIONE DI MLX, DOPO AVER SETTATO I PIXEL QUESTA LI RENDERIZZA SULLA FINESTRA
int	raycast_loop(t_game *game)
{
	clear_image(game);
	start_raycast(game);
	fps_counter(game);
	mlx_put_image_to_window(game->graphic.mlx_pointer,
		game->graphic.mlx_window, game->data.img, 0, 0);
	mlx_string_put(game->graphic.mlx_pointer, game->graphic.mlx_window,
		1250, 10, create_trgb(0, 255, 0, 0), game->graphic.fps);
	free(game->graphic.fps);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error: wrong number of arguments\n");
		return (-1);
	}
	init(argv[1], &game);
	create_window(&game);
	init_images(&game);
	set_keys(&game);
	init_raycast(&game);
	mlx_loop_hook(game.graphic.mlx_pointer, raycast_loop, &game);
	mlx_loop(game.graphic.mlx_pointer);
	return (0);
}
