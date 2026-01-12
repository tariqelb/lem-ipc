#include "./lemipc.h"


int     ft_find_path_recursion(t_player *player, int p_x, int p_y,
                int board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN], int index, int side)
{
	//ft_display_the_board(board_visited_positions);
        //out of the board
        if (p_x < 0 || p_x >= BOARD_X_LEN || p_y < 0 || p_y >= BOARD_Y_LEN)
                return (-1);
        //already visited
        if (board_visited_positions[p_y][p_x] == -1)
                return (-1);
        //not free position
        //set position as visited
        //find position
        if (p_x == player->find_x && p_y == player->find_y)
        {
		printf("side [%d], index[%d]\n", side, index);
		if (player->path[side] == -1 || player->path[side] > index)
               		player->path[side] = index;
                return (index);
        }
        if (board_visited_positions[p_y][p_x] != 0)
                return (-1);
        if (board_visited_positions[p_y][p_x] == 0)
	{
		board_visited_positions[p_y][p_x] = -1;
        	index++;
	}

	int best_sides[4] = {-1, -1, -1, -1};
	int i = 0;
	int selected = -1;
	while (i < 4)
	{
		selected = ft_best_side(player, p_x, p_y, i, best_sides);
		
		switch (selected)
		{
			case 0:
        			ft_find_path_recursion(player, p_x, p_y - 1, board_visited_positions, index, side);
				break;
			case 1:
        			ft_find_path_recursion(player, p_x + 1, p_y, board_visited_positions, index, side);
				break;
			case 2:
        			ft_find_path_recursion(player, p_x, p_y + 1, board_visited_positions, index, side);
				break;
			case 3:
        			ft_find_path_recursion(player, p_x - 1, p_y, board_visited_positions, index, side);
				break;
		}
		i++;
	}

        return (-1);
}

int	ft_get_last_position(t_player *player)
{
	if (player->pos_x == player->last_x_pos && player->pos_y - 1 == player->last_y_pos)
		return (0);

	if (player->pos_x + 1 == player->last_x_pos && player->pos_y == player->last_y_pos)
		return (1);

	if (player->pos_x == player->last_x_pos && player->pos_y + 1 == player->last_y_pos)
		return (2);

	if (player->pos_x - 1 == player->last_x_pos && player->pos_y == player->last_y_pos)
		return (3);

	return (-1);
}


int     ft_find_path_to_position(t_player *player)
{
	printf("ft_find_path_to_position\n");
        int     t_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     r_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     b_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     l_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     i;
        int     j;


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

	player->path[0] = -1;
	player->path[1] = -1;
	player->path[2] = -1;
	player->path[3] = -1;
        //return 1 if there is a path and total number of steps saved on player->path[N]
        //board_visited_positions set -1 on visited position to no return to it
        // 1 for first step for path total number of steps, and (0, 1, 2, 3) for sides
        //if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
	int skip_last_position = -1;
	if (player->find_path_active == 1)
		skip_last_position = ft_get_last_position(player);

        if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y - 1) == 0 && skip_last_position != 0)
        {
		printf("find path : one goes on top\n");
                ft_find_path_recursion(player, player->pos_x, player->pos_y - 1,
                         t_board_visited_positions, 1, 0);//start from top
        }
        if (ft_check_if_position_is_free(player, player->pos_x + 1, player->pos_y) == 0 && skip_last_position != 1)
        {
		printf("find path : one goes on right\n");
                ft_find_path_recursion(player, player->pos_x + 1, player->pos_y,
                         r_board_visited_positions, 1, 1);//start from right
        }
        if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y + 1) == 0 && skip_last_position != 2)
        {
		printf("find path : one goes on bottom\n");
                ft_find_path_recursion(player, player->pos_x, player->pos_y + 1,
                        b_board_visited_positions, 1, 2);//start from bottom
        }
        if (ft_check_if_position_is_free(player, player->pos_x - 1, player->pos_y) == 0 && skip_last_position != 3)
        {
		printf("find path : one goes on left\n");
                ft_find_path_recursion(player, player->pos_x - 1, player->pos_y,
                        l_board_visited_positions, 1, 3);//start from left
        }
	i = 0;
	while (i < 4)
	{
		printf("find path flag: %d , skip var %d\n", player->find_path_active, skip_last_position);
		printf("path len i = %d: [%d]\n", 0, player->path[0]);
		printf("path len i = %d: [%d]\n", 1, player->path[1]);
		printf("path len i = %d: [%d]\n", 2, player->path[2]);
		printf("path len i = %d: [%d]\n", 3, player->path[3]);
		if (player->path[i] != -1)
		{
			return (i);
		}
		i++;
	}
        //if (top != -1 || right != -1 || bottom != -1 || left != -1)
        //        return (1);
        return (-1);
}

int	ft_move_to_position_path(t_player *player)
{
	printf("ft_move_to_position_path\n");
	int	short_path;
	int	side;
	int	x;
	int	y;
	int	i;

	short_path = -1;
	side = -1;
	i = 0;
	while (i < 4)
	{
		printf("path result : i %d = [%d]", i, player->path[i]);
		if (player->path[i] != -1)
		{
			if (short_path == -1)
			{
				short_path = player->path[i];
				side = i;
			}
			else if (player->path[i] < short_path)
			{
				short_path = player->path[i];
				side = i;
			}
		}
		i++;
	}
	x = 0;
	y = 0;
	if (side == 0)
		y = -1;
	else if (side == 1)
		x = 1;
	else if (side == 2)
		y = 1;
	else if (side == 3)
		x = -1;
	if (side != -1)
	{
		if (player->pos_x + x >= 0 && player->pos_x + x < BOARD_X_LEN && player->pos_y + y >= 0 && player->pos_y + y < BOARD_Y_LEN)
		{
			if (player->game->board[player->pos_y + y][player->pos_x + x] == 0)
			{
				printf("short path pos_x[%d] pos_y[%d] [%d][%d]", player->pos_x, player->pos_y, x, y);
				printf(" board now [%d] board after move [%d]\n", player->game->board[player->pos_y][player->pos_x], player->game->board[player->pos_y + y][player->pos_x + x]);
				player->game->board[player->pos_y][player->pos_x] = 0;
				player->game->board[player->pos_y + y][player->pos_x + x] = player->team_id + 1;
				player->last_x_pos = player->pos_x;
				player->last_y_pos = player->pos_y;
				player->find_path_active = 1;
				player->pos_x = player->pos_x + x;
				player->pos_y = player->pos_y + y;
				return (1);
			}
			else
			{
				printf("place full . move to path fun \n");
			}
		}
		else
			printf("out of the board");
	}
	return (0);
}



int	ft_find_path_to_position_and_make_move(t_player *player, int x, int y)
{
	printf("ft_find_path_to_position_and_make_move\n");

	int	i;
	int	move;

	move = 0;
	i = 0;
	while (i < 4)
	{
		player->path[i] = -1;
		i++;
	}
	player->find_x = x;
	player->find_y = y;
	//find path
	{
		move = ft_go_closer_to_position_no_valid_path_to_it(player, x, y);
		printf("Going closer move [%d]\n", move);

	}
	if (move == 0 && ft_find_path_to_position(player) != -1)	
	{
		move = ft_move_to_position_path(player);//make move
		printf("Find path [%d]\n", move);
	}
	if (move == 0)
	{
		move = ft_find_best_move_and_escape(player);
		printf("Random escape [%d]\n", move);
	}
	
	return (move);
}
