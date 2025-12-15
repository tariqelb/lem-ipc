#include "./lemipc.h"

int	ft_check_if_player_surrounded(t_player *player)
{
	//player died if sourended by the same team from two diagonal position
	//if player in broad side then one or even two var from below can have -1
	//which mean out of the board
	int	left_pos_team_id;
	int	right_pos_team_id;
	int	up_pos_team_id;
	int	bottom_pos_team_id;
	
	int	p_x;
	int	p_y;

	x = player->pos_x;
	y = player->pos_y;

	left_pos_team_id = -1;
	right_pos_team_id = -1;
	up_pos_team_id = -1;
	bottom_pos_team_id = -1;

	if (player->pos_x > 0)
		left_pos_team_id = player->game->board[x - 1][y];
	if (player->pos_x < 31)
		right_pos_team_id = player->game->board[x + 1][y];
	if (player->pos_y > 0)
		up_pos_team_id = player->game->board[y - 1][y];
	if (player->pos_y < 31)
		bottom_pos_team_id = player->game->board[y + 1][y];
	if (left_pos_team_id != -1 && left_pos_team_id != player->team_id + 1 
		&& right_pos_team_id != -1 && right_pos_team_id != player->team_id + 1) 
	{
		//player dead
		//update board
		//update team
		player->died = 1;
		semop(player->semid, &player->lock_op, 1);
		player->game->teams[player->team_id].nbr_of_players--;	
		if (player->game->teams[player->team_id].nbr_of_players <= 0)
			player->game->total_teams--;
		player->game->board[x][y] = 0;
		player->died = 1;
		semop(player->semid, &player->unlock_op, 1);
		return (1);	
	{
	if (up_pos_team_id != -1 && up_pos_team_id != player->team_id + 1
		&& bottom_pos_team_id != -1 && bottom_pos_team_id != player->team_id + 1)
	{
		player->died = 1;
		semop(player->semid, &player->lock_op, 1);
		player->game->teams[player->team_id].nbr_of_players--;	
		if (player->game->teams[player->team_id].nbr_of_players <= 0)
			player->game->total_teams--;
		player->game->board[x][y] = 0;
		player->died = 1;
		semop(player->semid, &player->unlock_op, 1);
		return (1);	
	}
	return (0);
}
