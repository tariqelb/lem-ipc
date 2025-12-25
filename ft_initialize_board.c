#include "./lemipc.h"

t_player	*ft_initialize_game_board(t_player *player)
{
	int	x;
	int	y;

	// Clear the board
	for (int y = 0; y < BOARD_Y_LEN; y++)
	{
		for (int x = 0; x < BOARD_X_LEN; x++)
		{
			player->game->board[y][x] = 0;  // 0 = empty
		}
	}
	player->game->game_active = -1;  // Not yet started
	player->game->total_players = 1;
	player->game->total_teams = 1;
	player->player_id = 1;
	player->died = 0;
	player->first_move = 1;
	// Initialize teams array
	for (int i = 0; i < MAX_TEAMS; i++)
	{
	    player->game->teams[i].team_id = 0;
	    player->game->teams[i].nbr_of_players = 0;
	}
	//this the player who create the shared memory
	//which mean that is the first player and first team
	//x, y, is the door where players belong 
	//to a team will use to access board
	//Sides: top 0, right 1, bottom 2, left 3
	if (player->team_id % 4 == 0)
	{
		x = player->team_id % BOARD_X_LEN;
		y = 0;
	}
	if (player->team_id % 4 == 1)
	{
		x = BOARD_X_LEN - 1;
		y = player->team_id % BOARD_Y_LEN;
	}
	if (player->team_id % 4 == 2)
	{
		x = player->team_id % BOARD_X_LEN;
		y = BOARD_Y_LEN - 1;
	}
	if (player->team_id % 4 == 3)
	{
		x = 0;
		y = player->team_id % BOARD_Y_LEN;
	}
	player->game->teams[0].team_id = player->team_id;
	player->game->teams[0].nbr_of_players = 1;
	player->game->teams[0].corner = 1;
	player->game->teams[0].init_x = x;
	player->game->teams[0].init_y = y;
	player->pos_x = -1;
	player->pos_y = -1;
	return (player);
}
