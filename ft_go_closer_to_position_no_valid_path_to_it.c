#include "./lemipc.h"

int     ft_go_closer_to_position_no_valid_path_to_it(t_player *player, int x, int y)
{
        printf("ft_go_closer_to_position_no_valid_path_to_it\n");
        int     top;
        int     bottom;
        int     right;
        int     left;
	int	move;

        top = -1;
        right = -1;
        bottom = -1;
        left = -1;
	move = 0;

        if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
                return (-1);

        //check the fore sides if its free and safe
        //if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0 && player->game->board[player->pos_y - 1][player->pos_x] == 0)//top
        if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y - 1) == 0)//top
        {
                top = 1;
        }
        if (ft_check_if_position_is_free(player, player->pos_x + 1, player->pos_y) == 0)//right
        {
                right = 1;
        }
        if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y + 1) == 0)//bottom
        {
                bottom = 1;
        }
        if (ft_check_if_position_is_free(player, player->pos_x - 1, player->pos_y) == 0)//left
        {
                left = 1;
        }
	printf("Sides : t[%d]r[%d]b[%d]l[%d]\n", top, right, bottom, left);
	printf("player : pos x[%d] y[%d] ex[%d] ey[%d]\n", player->pos_x, player->pos_y, x, y);
        //after check the safe and free side
        //player will move to top and (go to y - 1) , it's similater to other sides
        //otherwise move to top-right, means go to (xy) exist on the top right of to player, similar for other sides
        //i want to move to top-right and i have to move either to the top or right, so i choose the farest move
        //means p_x =1 p_y = 1 find_x = 4 find_y 6 in this case i will move to top
        if (top == 1 && player->pos_x == x && player->pos_y - 1 > y)
        {
		printf("top\n");
		move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
                return (move);
        }
        if (right == 1 && player->pos_y == y && player->pos_x + 1 < x)
        {
		printf("right\n");
                move = !ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
                return (move);
        }
        if (bottom == 1 && player->pos_x == x && player->pos_y + 1 < y)
        {
		printf("bottom \n");
                move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
                return (move);
        }
        if (left == 1 && player->pos_y == y && player->pos_x - 1 > x)
        {
		printf("left \n");
                move = !ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
                return (move);
        }
        if ((top == 1 || right == 1) && player->pos_y  > y && player->pos_x < x)//move to top-right
        {
                int len_x;
                int len_y;

                len_x = x - player->pos_x;
                len_y = player->pos_y - y;
                if (len_x < 0)
                        len_x = len_x * -1;
                if (len_y < 0)
                        len_y = len_y * -1;
		printf("1len x [%d] len[%d] \n", len_x, len_y);
                if (len_y > len_x && top == 1)//move to top
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
                        return (move);
                }
                if ((len_x > len_y && right == 1) || (len_x && right && move == 0))//move to right
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
                        return (move);
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
		printf("2len x [%d] len[%d] \n", len_x, len_y);
                if (len_x >= len_y && right == 1)//move to right
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
                        return (move);
                }
                if ((len_y >= len_x && bottom == 1) || (len_y && bottom && move == 0))//move to bottom
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
                        return (move);
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
		printf("3len x [%d] len[%d] \n", len_x, len_y);
                if (len_y >= len_x && bottom == 1)//move to bottom
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
                        return (move);
                }
                if ((len_x >= len_y && left == 1) || (len_x && left && move == 0))//move to left
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
                        return (move);
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
		printf("4len x [%d] len[%d] \n", len_x, len_y);
                if (len_y >= len_x && top == 1)//move to top
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
                        return (move);
                }
                if ((len_x >= len_y && left == 1) || (len_x && left && move == 0))//move to right
                {
                        move = !ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
                        return (move);
                }
        }
        printf("no move in go closer\n");
        //case don't move to any place
        return (0);
}



