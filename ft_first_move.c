#include "./lemipc.h"


int     ft_first_move(t_player *player)
{
	printf("ft_first_move\n");
	int	top;
	int	right;
	int	bottom;
	int	left;
	int	random;

	top = -1;
	right = -1;
	bottom = -1;
	left = -1;

        if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y - 1) == 0)
        {
		top = 1;
        }
        if (ft_check_if_position_is_free(player, player->pos_x + 1, player->pos_y) == 0)
        {
		right = 1;
        }
        if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y + 1) == 0)
        {
		bottom = 1;
        }
        if (ft_check_if_position_is_free(player, player->pos_x - 1, player->pos_y) == 0)
        {
		left = 1;
        }

	random = ft_random_direction(top, right, bottom, left);

        if (random == 1)
        {
                ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
                player->first_move = 0;
        }
        else if (random == 2)
        {
                ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
                player->first_move = 0;
        }
        else if (random == 3)
        {
                ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
                player->first_move = 0;
        }
        else if (random == 4)
        {
                ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
                player->first_move = 0;
        }
        return (0);
}

