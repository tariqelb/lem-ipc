#include "./lemipc.h"

int     ft_check_position_is_safe(t_player *player, int x, int y)
{
	printf("ft_check_position_is_safe\n");
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


int	ft_check_if_position_is_free(t_player *player, int x, int y)
{
	printf("ft_check_if_position_is_free\n");
        if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
                return (-1);
	if (player->game->board[y][x] != 0)	
		return (1);
	return (0);
}
