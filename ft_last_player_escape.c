#include "./lemipc.h"

int ft_random_direction(int a, int b, int c, int d)
{
	int valid_directions[4] = {0};
	int count = 0;

	// Check each argument and store valid directions (1-indexed)
	if (a == 1) valid_directions[count++] = 1;
	if (b == 1) valid_directions[count++] = 2;
	if (c == 1) valid_directions[count++] = 3;
	if (d == 1) valid_directions[count++] = 4;

	// If no arguments have value 1, return 0 or handle error
	if (count == 0)
	    return 0;

	// Initialize random seed (do this only once in your program)
	static int initialized = 0;
	if (!initialized)
	{
	    srand(time(NULL));
	    initialized = 1;
	}

	// Randomly select one of the valid directions
	int random_index = rand() % count;
	return (valid_directions[random_index]);
}


int	ft_find_best_move_and_escape(t_player *player)
{
	int	left;
	int	right;
	int	top;
	int	bottom;
	int	free_position;
	int	random_direction;

	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
	if (player->pos_x == 0)
		left = -1;
	if (player->pos_x == 31)
		right = -1;
	if (player->pos_y == 0)
		top = -1;
	if (player->pos_y == 31)
		bottom = -1;
	if (left != -1)
		left = player->game->board[player->pos_y][player->pos_x - 1];
	if (right != -1)
		right = player->game->board[player->pos_y][player->pos_x + 1];
	if (top != -1)
		top = player->game->board[player->pos_y - 1][player->pos_x];
	if (bottom != -1)
		bottom = player->game->board[player->pos_y + 1][player->pos_x];

	free_position = 0;
	if (left == 0)
	{
		//left = ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y);
		left = ft_check_if_position_is_free(player, player->pos_x - 1, player->pos_y);
		if (left == 0)
		{
			left = 1;
			free_position++;
		}
	}
	if (right == 0)
	{
		right = ft_check_if_position_is_free(player, player->pos_x + 1, player->pos_y);
		if (right == 0)
		{
			right = 1;
			free_position++;
		}
	}
	if (top == 0)
	{
		top = ft_check_if_position_is_free(player, player->pos_x, player->pos_y - 1);
		if (top == 0)
		{
			top = 1;
			free_position++;
		}
	}
	if (bottom == 0)
	{
		bottom = ft_check_if_position_is_free(player, player->pos_x, player->pos_y + 1);
		if (bottom == 0)
		{
			free_position++;
			bottom = 1;
		}
	}
	if (free_position > 0)
	{
		random_direction = ft_random_direction(left, top, right, bottom);
		if (random_direction == 1)//move to left
			return (!ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y));
		else if (random_direction == 2)//move to top
			return (!ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1));
		else if (random_direction == 3)//move to right
			return (!ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y));
		else if (random_direction == 4)//move to bottom
			return (!ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1));
	}
	return (0);
}


int	ft_last_player_escape(t_player *player)
{
	//int	team_array_index;

	//team_array_index = ft_get_team_array_index(player);
	//if (team_array_index == -1)
	//	return (0);
	//if (player->game->teams[team_array_index].nbr_of_players == 1)
	//{
		ft_find_best_move_and_escape(player);
		return (1);
	//}
	//return (0);
}
