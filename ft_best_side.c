#include "./lemipc.h"

int	ft_include(int best_side[4], int i, int include)
{
	int j;

	j = 0;
	while (j < i)
	{
		if (best_side[j] == include)
			return (0);
		j++;
	}
	return (1);
}

int	ft_best_side(t_player *player, int p_x, int p_y, int i, int best_side[4])
{

	if (ft_include(best_side, i, 1) && p_x < player->find_x && p_y == player->find_y)//go right
	{
		best_side[i] = 1;
	}
	if (ft_include(best_side, i, 3) && p_x > player->find_x && p_y == player->find_y)//go left
	{
		best_side[i] = 3;
	}
	if (ft_include(best_side, i, 0) && p_x == player->find_x && p_y > player->find_y)//go top
	{
		best_side[i] = 0;
	}
	if (ft_include(best_side, i, 2) && p_x == player->find_x && p_y < player->find_y)//go bottom
	{
		best_side[i] = 2;
	}
	if (p_x > player->find_x && p_y > player->find_y)//go left-top
	{
		int left = p_x - player->find_x;
		int top = p_y - player->find_y;

		if (ft_include(best_side, i, 3) &&  left <= top)
		{
			best_side[i] = 3;
		}
		else if (ft_include(best_side, i, 0))
		{
			best_side[i] = 0;
		}
	}
	if (p_x < player->find_x && p_y > player->find_y)//go right-top
	{
		int right = player->find_x - p_x;
		int top = p_y - player->find_y;

		if (ft_include(best_side, i, 1) && right <= top)
		{
			best_side[i] = 1;
		}
		else if (ft_include(best_side, i, 0))
		{
			best_side[i] = 0;
		}
	}
	if (p_x < player->find_x && p_y < player->find_y)//go right-bottom
	{
		int right = player->find_x - p_x;
		int bottom = player->find_y - p_y;

		if (ft_include(best_side, i, 1) && right <= bottom)
		{
			best_side[i] = 1;
		}
		else if (ft_include(best_side, i, 2))
		{
			best_side[i] = 2;
		}
	}
	if (p_x > player->find_x && p_y < player->find_y)//go right-bottom
	{
		int left = player->find_x - p_x;
		int bottom = p_y - player->find_y;

		if (ft_include(best_side, i, 3) && left <= bottom)
		{
			best_side[i] = 3;
		}
		else if (ft_include(best_side, i, 2))
		{
			best_side[i] = 2;
		}
	}
	if (best_side[i] == -1)
	{
		int j = 0;
		while (j < i)
		{
			if (ft_include(best_side, i, j))
				best_side[i] = j;
			j++;
		}
	}
	return (best_side[i]);
}
