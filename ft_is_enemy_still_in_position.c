#include "./lemipc.h"

int     ft_is_enemy_still_in_position(t_player *player, int x, int y)
{
	ft_putstr("ft_is_enemy_still_in_position\n");
        if (x >= 0 && y >= 0 && x < BOARD_X_LEN && y < BOARD_Y_LEN)
        {
                int position = player->game->board[y][x];

                if (position != 0 && position != player->team_id + 1)
                {
                        return (1);
                }
                else
                        return (0);
        }
        return (0);
}
