#include "./lemipc.h"


int	ft_random_rule_check_if_other_enemy_exist(short player_sides[8], short index)
{
	short i;

	i = 0;
	while (i < 8)
	{
		if (i != index && player_sides[i] > 0 && player_sides[index] == player_sides[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_random_rule_check_if_player_surrounded(t_player *player, int player_id, int x, int y)
{
	ft_putstr("ft_random_rule_check_if_player_surrounded\n");
	short	player_sides[8];//[0-top-left]->[1-top]->[2-top-right]->[3-right]->[4-btm-right]->[5-btm]->[6-btm-left]->[7-left]
	short	i;
	
	if (x < 0 || x >= BOARD_X_LEN || y < 0 || y > BOARD_Y_LEN)
		return (0);

	i = 0;
	while (i < 8)
	{
		player_sides[i] = -1;
		i++;
	}
	if (x > 0 && y > 0)
		player_sides[0] = player->game->board[y - 1][x - 1];
	if (y > 0)
		player_sides[1] = player->game->board[y - 1][x];
	if (x < BOARD_X_LEN - 1 && y > 0)
		player_sides[2] = player->game->board[y - 1][x + 1];
	if (x < BOARD_X_LEN - 1)
		player_sides[3] = player->game->board[y][x + 1];
	if (x < BOARD_X_LEN - 1 && y < BOARD_Y_LEN - 1)
		player_sides[4] = player->game->board[y + 1][x + 1];
	if (y < BOARD_Y_LEN - 1)
		player_sides[5] = player->game->board[y + 1][x];
	if (x > 0 && player->pos_y < BOARD_Y_LEN - 1)
		player_sides[6] = player->game->board[y + 1][x - 1];
	if (x > 0)
		player_sides[7] = player->game->board[y][x - 1];
	
	i = 0;
	while (i < 8)
	{
		if (player_sides[i] > 0 && player_sides[i] != player_id)
		{
			if (ft_random_rule_check_if_other_enemy_exist(player_sides, i))
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_check_if_player_surrounded(t_player *player)
{
	ft_putstr("ft_check_if_player_surrounded : RANDOM\n");
	//player died if sourended by the same team from two diagonal position
	//if player in broad side then one or even two var from below can have -1
	//which mean out of the board
	int	left_pos_team_id;
	int	right_pos_team_id;
	int	up_pos_team_id;
	int	bottom_pos_team_id;
	
	int	x;
	int	y;

	x = player->pos_x;
	y = player->pos_y;

	left_pos_team_id = -1;
	right_pos_team_id = -1;
	up_pos_team_id = -1;
	bottom_pos_team_id = -1;

	if (RANDOM)
		return (ft_random_rule_check_if_player_surrounded(player, player->team_id + 1, player->pos_x, player->pos_y));

	if (player->pos_x > 0)
		left_pos_team_id = player->game->board[y][x - 1];
	if (player->pos_x < BOARD_X_LEN)
		right_pos_team_id = player->game->board[y][x + 1];
	if (player->pos_y > 0)
		up_pos_team_id = player->game->board[y - 1][x];
	if (player->pos_y < BOARD_Y_LEN)
		bottom_pos_team_id = player->game->board[y + 1][x];
	if (left_pos_team_id != -1 && left_pos_team_id != player->team_id + 1 
		&& right_pos_team_id != -1 && right_pos_team_id != player->team_id + 1) 
	{
		//player dead
		//update board
		//update team
		player->died = 1;
		player->game->teams[player->team_id].nbr_of_players--;	
		if (player->game->teams[player->team_id].nbr_of_players <= 0)
			player->game->total_teams--;
		player->game->board[y][x] = 0;
		player->died = 1;
		return (1);	
	}
	if (up_pos_team_id != -1 && up_pos_team_id != player->team_id + 1
		&& bottom_pos_team_id != -1 && bottom_pos_team_id != player->team_id + 1)
	{
		player->died = 1;
		player->game->teams[player->team_id].nbr_of_players--;	
		if (player->game->teams[player->team_id].nbr_of_players <= 0)
			player->game->total_teams--;
		player->game->board[y][x] = 0;
		player->died = 1;
		return (1);	
	}
	return (0);
}
