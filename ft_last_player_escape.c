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
    return valid_directions[random_index];
}

int	ft_move_to_position_x_y(t_player *player, int x, int y)
{
	if (x == -1 || y == -1)
		return (1);
	if (player->game->board[x][y] != 0)
		return (1);
	semop(player->semid, &player->lock_op, 1);
	player->game->board[x][y] = player->team_id + 1;
	semop(player->semid, &player->unlock_op, 1);
	return (0);
}

int     ft_check_position_is_safe(t_player *player, int x, int y)
{
        int     left;
        int     right;
        int     top;
        int     bottom;

        if (x == -1 || x == 32 || y == -1 || y == 32)
                return (-1);
        if (x == 0)
                left = -1;
        else
                left = player->game->board[y][x - 1];
        if (x == 31)
                right = -1;
        else
                right = player->game->board[y][x + 1];
        if (y == 0)
                top = -1;
        else
                top = player->game->board[y - 1][x];
        if (y == 31)
                bottom = -1;
        else
                bottom = player->game->board[y + 1][x];
        if (top > 0 && top != player->team_id + 1 &&
                bottom  > 0 && bottom != player->team_id + 1)
                return (1);
        if (left > 0 && left != player->team_id + 1 &&
                right > 0 && right != player->team_id + 1)
                return (1);
        //0 = safe
        return (0);
}

void	ft_find_best_move_and_escape(t_player *player)
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
		left = player->game->board[player->pos_x - 1][player->pos_y];
	if (right != -1)
		right = player->game->board[player->pos_x + 1][player->pos_y];
	if (top != -1)
		top = player->game->board[player->pos_x][player->pos_y - 1];
	if (bottom != -1)
		bottom = player->game->board[player->pos_x][player->pos_y + 1];

	free_position = 0;
	if (left == 0)
	{
		left = ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y);
		if (left == 0)
			free_position++;
	}
	if (right == 0)
	{
		right = ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y);
		if (right == 0)
			free_position++;
	}
	if (top == 0)
	{
		top = ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1);
		if (top == 0)
			free_position++;
	}
	if (bottom == 0)
	{
		bottom = ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1);
		if (bottom == 0)
			free_position++;
	}
	if (free_position > 0)
	{
		random_direction = ft_random_direction(left, top, right, bottom);
		if (random_direction == 1)//move to left
			ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
		else if (random_direction == 2)//move to top
			ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
		else if (random_direction == 3)//move to right
			ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
		else if (random_direction == 4)//move to bottom
			ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
	}
	return;
}


int	ft_last_player_escape(t_player *player)
{
	int	team_array_index;

	team_array_index = ft_get_team_array_index(player);
	if (team_array_index == -1)
		return (0);
	if (player->game->teams[team_array_index].nbr_of_players == 1)
	{
		ft_find_best_move_and_escape(player);
		return (1);
	}
	return (0);
}
