#include "./lemipc.h"

int     ft_find_path_recursion(t_player *player, int p_x, int p_y,
                int board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN], int index, int side)
{
        int     top;   //1
        int     right; //2
        int     bottom;//3
        int     left;  //4

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

int     ft_find_path_to_position(t_player *player)
{
        int     left;
        int     right;
        int     top;
        int     bottom;
        int     t_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     r_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     b_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     l_board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN];
        int     i;
        int     j;

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

int	ft_move_to_position_path(t_player *player)
{
	int	short_path;
	int	side;
	int	x;
	int	y;
	int	i;

	short_path = 0;
	side = -1;
	i = 0;
	while (i < 4)
	{
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
	else if (side == 1)
		x = -1;
	if (side != -1)
	{
		semop(player->semid, &player->lock_op, 1);
		player->game->board[player->pos_x + x][player->pos_y + y] = player->team_id + 1;
		semop(player->semid, &player->unlock_op, 1);
	}
	return (0);
}

int	ft_go_closer_to_position_no_valid_path_to_it(player, int x, int y)
{
}



int	ft_find_path_to_position_and_make_move(t_player *player, int x, int y)
{

	//find path
	if (ft_find_path_to_position(player, board_x, board_y, x, y))	
		ft_move_to_position_path(player);//make move
	//else
	//	ft_go_closer_to_position_no_valid_path_to_it();
	return (0);
}
