#include "./lemipc.h"

int	ft_new_enemy_found_select_best_side_to_attack(t_player *player, int enemy_x, int enemy_y, int enemy_team_id)
{
	printf("ft_new_enemy_found_select_best_side_to_attack\n");
	int	e_top;
	int	e_right;
	int	e_bottom;
	int	e_left;

	e_top = -1;
	e_right = -1;
	e_bottom = -1;
	e_left = -1;

	if (enemy_x < 0 || enemy_x >= BOARD_X_LEN || enemy_y < 0 || enemy_y >= BOARD_Y_LEN)
		return (-1);
	if (enemy_x > 0)
		e_left = player->game->board[enemy_y][enemy_x - 1];
	if (enemy_x < BOARD_X_LEN - 1)
		e_right = player->game->board[enemy_y][enemy_x + 1];
	if (enemy_y > 0)
		e_top = player->game->board[enemy_y - 1][enemy_x];
	if (enemy_x < BOARD_Y_LEN - 1)
		e_bottom = player->game->board[enemy_y + 1][enemy_x];

	if (e_top == 0 && e_bottom > 0 && e_bottom != enemy_team_id)
		return (0);
	if (e_right == 0 && e_left > 0 && e_left != enemy_team_id)
		return (1);
	if (e_bottom == 0 && e_top > 0 && e_top != enemy_team_id)
		return (2);
	if (e_left == 0 && e_right > 0 && e_right != enemy_team_id)
		return (3);
	return (-1);
}
