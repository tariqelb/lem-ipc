#include "./lemipc.h"

/*int     ft_find_path_recursion(t_player *player, int p_x, int p_y,
                int board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN], int index, int side)
{
        //int     top;   //1
        //int     right; //2
        //int     bottom;//3
        //int     left;  //4

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
		printf("find one with %d steps in side [%d]\n", index, side);
		if (player->path[side] == -1 || player->path[side] > index)
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
}*/



int     ft_find_path_recursion(t_player *player, int p_x, int p_y,
                int board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN], int index, int side)
{
        //int     top;   //1
        //int     right; //2
        //int     bottom;//3
        //int     left;  //4
	if (index == 1)
		printf("\n");
	//printf("Side : [%d], index : %d (%d,%d) - [[%d, %d]]   -\n", side, index, p_x, p_y, player->find_x, player->find_y);
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
		printf("find one with %d steps in side [%d]\n", index, side);
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

        if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
        	ft_find_path_recursion(player, p_x, p_y - 1, board_visited_positions, index, 0);
        if (ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y) == 0)
        	ft_find_path_recursion(player, p_x + 1, p_y, board_visited_positions, index, 1);
        if (ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1) == 0)
        	ft_find_path_recursion(player, p_x, p_y + 1, board_visited_positions, index, 2);
        if (ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y) == 0)
        	ft_find_path_recursion(player, p_x - 1, p_y, board_visited_positions, index, 3);

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
		printf("Top safe : [%d]\n", top);
        }
        if (ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y) == 0)
        {
                right = ft_find_path_recursion(player, player->pos_x + 1, player->pos_y,
                         r_board_visited_positions, 1, 1);//start from right
		printf("Right safe : [%d]\n", right);
        }
        if (ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1) == 0)
        {
                bottom = ft_find_path_recursion(player, player->pos_x, player->pos_y + 1,
                        b_board_visited_positions, 1, 2);//start from bottom
		printf("Bottom safe : [%d]\n", bottom);
        }
        if (ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y) == 0)
        {
                left = ft_find_path_recursion(player, player->pos_x - 1, player->pos_y,
                        l_board_visited_positions, 1, 3);//start from left
		printf("Left safe : [%d]\n", left);
        }
	i = 0;
	while (i < 4)
	{
		if (player->path[i] != -1)
			return (1);
		i++;
	}
        //if (top != -1 || right != -1 || bottom != -1 || left != -1)
        //        return (1);
        return (0);
}

int	ft_move_to_position_path(t_player *player)
{
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
	printf("Side and paths : %d %d %d %d %d\n", side, player->path[0],player->path[1],player->path[2],player->path[3]);
	if (side != -1)
	{
		player->game->board[player->pos_y][player->pos_x] = 0;
		player->game->board[player->pos_y + y][player->pos_x + x] = player->team_id + 1;
		player->pos_x = player->pos_x + x;
		player->pos_y = player->pos_y + y;
	}
	return (0);
}

int	ft_go_closer_to_position_no_valid_path_to_it(t_player *player, int x, int y)
{
	int	top;
	int	bottom;
	int	right;
	int	left;

	top = -1;
	right = -1;
	bottom = -1;
	left = -1;

	if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
		return (-1);

	//check the fore sides if its free and safe
	if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0 && player->game->board[player->pos_y - 1][player->pos_x] == 0)//top
	{
		top = 1;
	}
	if (ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y) == 0 && player->game->board[player->pos_y][player->pos_x + 1] == 0)//right
	{
		right = 1;
	}
	if (ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1) == 0 && player->game->board[player->pos_y + 1][player->pos_x] == 0)//bottom
	{
		bottom = 1;
	}
	if (ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y) == 0 && player->game->board[player->pos_y][player->pos_x - 1] == 0)//left
	{
		left = 1;
	}
	//after check the safe and free side
	//player will move to top and (go to y - 1) , it's similater to other sides
	//otherwise move to top-right, means go to (xy) exist on the top right of to player, similar for other sides
	//i want to move to top-right and i have to move either to the top or right, so i choose the farest move 
	//means p_x =1 p_y = 1 find_x = 4 find_y 6 in this case i will move to top
	if (top == 1 && player->pos_x == x && player->pos_y > y)
	{
		printf("Go closer top\n");
		ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
		return (1);
	}
	if (right == 1 && player->pos_y == y && player->pos_x < x)
	{
		printf("Go closer  right\n");
		ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
		return (1);
	}
	if (bottom == 1 && player->pos_x == x && player->pos_y < y)
	{
		printf("Go closer bottom\n");
		ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
		return (1);
	}
	if (left == 1 && player->pos_y == y && player->pos_x > x)
	{
		printf("Go closer left\n");
		ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
		return (1);
	}
	if ((top == 1 || right == 1) && player->pos_y > y && player->pos_x < x)//move to top-right
	{
		int len_x;
		int len_y;
		
		len_x = x - player->pos_x;
		len_y = player->pos_y - y;
		if (len_x < 0)
			len_x = len_x * -1;
		if (len_y < 0)
			len_y = len_y * -1;
		if (len_y > len_x && top == 1)//move to top
		{
			printf("Go closer top t-r\n");
			ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
			return (1);
		}
		if (len_x > len_y && right == 1)//move to right
		{
			printf("Go closer right t-r\n");
			ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
			return (1);
		}
	}
	if ((right == 1 || bottom == 1) && player->pos_y < y && player->pos_x < x)//move to right-bottom
	{
		int len_x;
		int len_y;
		
		len_x = x - player->pos_x;
		len_y = y - player->pos_y;
		if (len_x < 0)
			len_x = len_x * -1;
		if (len_y < 0)
			len_y = len_y * -1;
		if (len_x > len_y && right == 1)//move to right
		{
			printf("Go closer right r-b\n");
			ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
			return (1);
		}
		if (len_y > len_x && bottom == 1)//move to bottom
		{
			printf("Go closer bottom r-b\n");
			ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
			return (1);
		}
	}
	if ((bottom == 1 || left == 1) && player->pos_y < y && player->pos_x > x)//move to left-bottom
	{
		int len_x;
		int len_y;
		
		len_x = player->pos_x - x;
		len_y = y - player->pos_y;
		if (len_x < 0)
			len_x = len_x * -1;
		if (len_y < 0)
			len_y = len_y * -1;
		if (len_y > len_x && bottom == 1)//move to bottom
		{
			printf("Go closer bottom b-l\n");
			ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
			return (1);
		}
		if (len_x > len_y && left == 1)//move to left
		{
			printf("Go closer left b-l\n");
			ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
			return (1);
		}
	}
	if ((left == 1 || top == 1) && player->pos_y > y && player->pos_x > x)//move to top-left
	{
		int len_x;
		int len_y;
		
		len_x = player->pos_x - x;
		len_y = player->pos_y - y;
		if (len_x < 0)
			len_x = len_x * -1;
		if (len_y < 0)
			len_y = len_y * -1;
		if (len_y > len_x && top == 1)//move to top
		{
			printf("Go closer top l-t\n");
			ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
			return (1);
		}
		if (len_x > len_y && left == 1)//move to right
		{
			printf("Go closer left l-t\n");
			ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
			return (1);
		}
	}
	//case don't move to any place
	return (0);
}


int	ft_find_path_to_position_and_make_move(t_player *player, int x, int y)
{

	int	i;

	i = 0;
	while (i < 4)
	{
		player->path[i] = -1;
		i++;
	}
	player->find_x = x;
	player->find_y = y;
	//find path
	if (ft_find_path_to_position(player))	
	{
		printf("Find path \n");
		printf("Path top    to enemy [%d] steps \n", player->path[0]);
		printf("Path right  to enemy [%d] steps \n", player->path[1]);
		printf("Path bottom to enemy [%d] steps \n", player->path[2]);
		printf("Path left   to enemy [%d] steps \n", player->path[3]);
		ft_move_to_position_path(player);//make move
	}
	else
	{
		printf("Going closer\n");
		printf("My position [%d][%d]\n", player->pos_x, player->pos_y);
		printf("Go to position [%d][%d]\n", x, y);

		ft_go_closer_to_position_no_valid_path_to_it(player, x, y);
	}
	return (0);
}
