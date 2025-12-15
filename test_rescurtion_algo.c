#include "./lemipc.h"


int     ft_check_position_is_safe(t_player *player, int x, int y)
{
        int     left;
        int     right;
        int     top;
        int     bottom;

        if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
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

int	ft_initial_the_board(t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < BOARD_Y_LEN)
	{
		printf("\ni = %d\n" , i);
		j = 0;
		while (j < BOARD_X_LEN)
		{
			printf("j = %d ", j);
			player->game->board[i][j] = 0;
			if (i == 0 && j == 2)//place an enemy
				player->game->board[i][j] = 3;
			if (i == 1 && j == 1)//enemy
				player->game->board[i][j] = 3;
			if (i == 2 && j == 2)//enemy
				player->game->board[i][j] = 3;
			if (i == 3 && j == 4)//enemy
				player->game->board[i][j] = 3;
			if (i == 4 && j == 1)//player + 1
				player->game->board[i][j] = 2;
			if (i == 0 && j == 4)//player + 1
				player->game->board[i][j] = 2;
			j++;
		}
		i++;
	}
	player->game->total_players = 6;
	player->game->total_teams = 2;
	player->game->game_active = 1;
	player->game->teams[0].nbr_of_players = 2;
	player->game->teams[0].team_id = 1;
	player->game->teams[0].init_x = 0;
	player->game->teams[0].init_y = 2;
	player->game->teams[0].corner = 2;
	player->game->teams[1].nbr_of_players = 4;
	player->game->teams[1].team_id = 2;
	player->game->teams[1].init_x = 4;
	player->game->teams[1].init_y = 0;
	player->game->teams[1].corner = 4;
	return (0);
}


void	ft_print_the_board(t_player *player)
{
	int	i;
	int	j;
	

	printf(" _________________________ \n");
	printf("| [x/y] | [0][1][2][3][4] |\n");
	printf("|_______|_________________|\n");
	i = 0;
	while (i < BOARD_Y_LEN)
	{
		printf("|  [%d]  | ", i);
		j = 0;
		while (j < BOARD_X_LEN)
		{
			printf("[%d]", player->game->board[i][j]);
			j++;
		}
		printf(" |\n");
		i++;
	}
	printf("|_______|_________________|\n");
}

int	ft_find_path_recursion(t_player *player, int p_x, int p_y,
		int board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN], int index, int side)
{
	int	top;   //1
	int	right; //2
	int	bottom;//3
	int	left;  //4

	//out of the board
	if (p_x < 0 || p_x >= BOARD_X_LEN || p_y < 0 || p_y >= BOARD_Y_LEN)
		return (-1);
	//already visited
	if (board_visited_positions[p_y][p_x] == -1)
		return (-1);
	//not free position
	if (player->game->board[p_y][p_x] != 0)
		return (-1);
	//set position as visited
	board_visited_positions[p_y][p_x] = -1;
	//find position
	if (p_x == player->find_x && p_y == player->find_y)
	{
		player->path[side] = index;
		return (index);
	}
	
	index++;
	
	if (ft_find_path_recursion(player, p_x, p_y - 1, board_visited_positions, index, side) > 0)
	{
		return (index);
	}
	if (ft_find_path_recursion(player, p_x + 1, p_y, board_visited_positions, index, side) > 0)
	{
		return (index);
	}
	if (ft_find_path_recursion(player, p_x, p_y + 1, board_visited_positions, index, side) > 0)
	{
		return (index);
	}
	if (ft_find_path_recursion(player, p_x - 1, p_y, board_visited_positions, index, side) > 0)
	{
		return (index);
	}
	return (-1);
}

int	ft_find_path_to_position(t_player *player)
{
	int	left;
	int	right;
	int	top;
	int	bottom;
	int	t_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
	int	r_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
	int	b_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
	int	l_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
	int	i;
	int	j;

	top = -1;//come from 1
	right = -1;//2
	bottom = -1;//3
	left = -1;//4
	
	i = 0;
	while (i < BOARD_Y_LEN)
	{
		j = 0;
		while (j < BOARD_X_LEN)
		{
			t_board_visited_positions[i][j] = player->game->board[i][j];
			r_board_visited_positions[i][j] = player->game->board[i][j];
			b_board_visited_positions[i][j] = player->game->board[i][j];
			l_board_visited_positions[i][j] = player->game->board[i][j];
			j++;
		}
		i++;
	}


	//return 1 if there is a path and total number of steps saved on player->path[N]
	//board_visited_positions set -1 on visited position to no return to it
	// 1 for first step for path total number of steps, and (0, 1, 2, 3) for sides
	if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
	{
		top = ft_find_path_recursion(player, player->pos_x, player->pos_y - 1,
			 t_board_visited_positions, 1, 0);//start from top
	}
	if (ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y) == 0)
	{
		right = ft_find_path_recursion(player, player->pos_x + 1, player->pos_y,
			 r_board_visited_positions, 1, 1);//start from right
	}
	if (ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1) == 0)
	{
		bottom = ft_find_path_recursion(player, player->pos_x, player->pos_y + 1,
			 b_board_visited_positions, 1, 2);//start from bottom
	}
	if (ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y) == 0)
	{
		left = ft_find_path_recursion(player, player->pos_x - 1, player->pos_y, 
			l_board_visited_positions, 1, 3);//start from left
	}
	if (top != -1 || right != -1 || bottom != -1 || left != -1)
		return (1);
	return (0);
}

int	main(void)
{
	t_player	player;

	player.game = malloc(sizeof(t_game));

	ft_initial_the_board(&player);

	player.team_id = 1;
	player.player_id = 1;
	player.pos_x = 1;
	player.pos_y = 4;
	player.path[0] = 0;
	player.path[1] = 0;
	player.path[2] = 0;
	player.path[3] = 0;
	player.find_x = 3;
	player.find_y = 1;
	ft_print_the_board(&player); 
	
	//printf("Position (%d,%d) is [%d]\n",
	//	 2, 1 ,ft_check_position_is_safe(&player, 2, 1));
	//printf("Position (%d,%d) is [%d]\n",
	//	 1, 2 ,ft_check_position_is_safe(&player, 1, 2));
	//printf("Position (%d,%d) is [%d]\n",
	//	 -1, 2 ,ft_check_position_is_safe(&player, -1, 2));
	int status = ft_find_path_to_position(&player);
	printf("Status : %d\n", status);

	return (0);
}
