#include "../include/cub3d.h"

void	raycast(t_game *game, int x)
{
	game->ray.cameraX = 2 * x / (double)WIN_WIDTH - 1;
	game->ray.dir.x = game->player.dir.x + game->player.cam_plane.x * game->ray.cameraX;
	game->ray.dir.y = game->player.dir.y + game->player.cam_plane.y * game->ray.cameraX;
	game->ray.mapX = (int)game->player.pos.x;
	game->ray.mapY = (int)game->player.pos.y;
	if(game->ray.dir.x == 0)
		game->ray.deltaDist.x = 1e30;
	else
		game->ray.deltaDist.x = fabs(1 / game->ray.dir.x);
	if(game->ray.dir.y == 0)
		game->ray.deltaDist.y = 1e30;
	else
		game->ray.deltaDist.y = fabs(1 / game->ray.dir.y);
}

void	set_step_and_dist(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.stepX = -1;
		game->ray.sideDist.x = (game->player.pos.x - game->ray.mapX) * game->ray.deltaDist.x;
	}
	else
	{
		game->ray.stepX = 1;
		game->ray.sideDist.x = (game->ray.mapX + 1.0 - game->player.pos.x) * game->ray.deltaDist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.stepY = -1;
		game->ray.sideDist.y = (game->player.pos.y - game->ray.mapY) * game->ray.deltaDist.y;
	}
	else
	{
		game->ray.stepY = 1;
		game->ray.sideDist.y = (game->ray.mapY + 1.0 - game->player.pos.y) * game->ray.deltaDist.y;
	}
}

void	perform_DDA(t_game *game)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.sideDist.x < game->ray.sideDist.y)
		{
			game->ray.sideDist.x += game->ray.sideDist.x;
			game->ray.mapX += game->ray.stepX;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sideDist.y += game->ray.sideDist.y;
			game->ray.mapY += game->ray.stepY;
			game->ray.side = 1;
		}
		if (game->map[game->ray.mapX][game->ray.mapY] > 0)
			game->ray.hit = 1;
	}
}

void	set_wall_height(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perpWallDist = (game->ray.sideDist.x - game->ray.deltaDist.x);
	else
		game->ray.perpWallDist = (game->ray.sideDist.y - game->ray.deltaDist.y);
}

void	start_raycast(t_game *game)
{
	int	x;

	x = 0;
	while(x < WIN_WIDTH && x++)
	{
		raycast(game, x);
		set_step_and_dist(game);
		perform_DDA(game);
		set_wall_height(game);
	}
}