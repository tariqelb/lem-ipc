#include "./lemipc.h"

/*


| [x/y] | [0][1][2][3][4][5][6][7][8][9] |
|_______|________________________________|
|  [0]  | [0][0][0][0][0][0][0][0][0][0] | 
|  [1]  | [0][0][0][0][0][0][0][0][0][0] |
|  [2]  | [0][0][0][0][0][0][0][0][0][0] | 
|  [3]  | [0][0][0][0][0][0][0][0][0][0] |  
|  [4]  | [0][0][0][0][0][2][2][0][2][0] |   
|  [5]  | [0][0][0][0][0][0][8][0][8][0] |    
|  [6]  | [0][0][0][0][0][2][0][0][0][0] |          
|  [7]  | [0][0][0][0][0][0][0][0][0][0] |          
|  [8]  | [0][0][0][0][0][0][0][0][0][0] |          
|  [9]  | [0][0][0][0][0][0][0][0][0][0] |          
|_______|________________________________|     


 */

int	ft_initial_the_board(t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (y < BOARD_Y_LEN)
	{
		x = 0;
		while (x < BOARD_X_LEN)
		{
			player->game->board[y][x] = 0;
			if (x == 8 && y == 5)//place an enemy
				player->game->board[y][x] = 8;
			if (x == 6 && y == 5)//enemy
				player->game->board[y][x] = 8;
			if (x == 6 && y == 4)//enemy
				player->game->board[y][x] = 2;
			if (x == 5 && y == 4)//enemy
				player->game->board[y][x] = 2;
			//if (x == 3 && j == 3)//enemy
			//	player->game->board[y][x] = 6;
			//if (x == 3 && y == 1)//player + 1
			//	player->game->board[y][x] = 3;
			//if (x == 2 && y == 2)//player + 1
			//	player->game->board[y][x] = 3;
			//if (i == 4 && j == 5)//enemy
			//	player->game->board[y][x] = 6;
			//if (i == 5 && j == 2)//enemy
			//	player->game->board[y][x] = 6;
			//if (i == 6 && j == 3)//enemy
			//	player->game->board[y][x] = 6;
			x++;
		}
		y++;
	}
	player->game->total_players = 4;
	player->game->total_teams = 2;
	player->game->game_active = 1;
	return (0);
}
int	ft_set_player(t_player *player, int x, int y, int team_id, int target_team_id, int player_id)
{
	player->pos_x = x;
	player->pos_y = y;
	player->team_id = team_id;
	player->target_team_id = target_team_id;
	player->player_id = player_id;
	return (0);
}

int	ft_set_team(t_player *player, int nbr_of_players, int team_id, int init_x, int init_y, int corner, int team_index)
{
	player->game->teams[team_index].nbr_of_players = nbr_of_players;
	player->game->teams[team_index].team_id = team_id;
	player->game->teams[team_index].init_x = init_x;
	player->game->teams[team_index].init_y = init_y;
	player->game->teams[team_index].corner = corner;

	return (0);
}

int	main(void)
{
	t_player	player;
	t_player	player1;
	t_player	player2;
	t_player	player3;
	t_message_queue	msg;
	t_message_queue	msg1;
	t_message_queue	msg2;
	t_message_queue	msg3;

	player.game = malloc(sizeof(t_game));


	//                      x, y, team, target, p_id

	//player.find_x = 3;
	//player.find_y = 1;
	msg.x_attack = 8;
	msg.y_attack = 4;
	msg.x_defence = 8;
	msg.y_defence = 3;
	msg.x_player = 8;
	msg.y_player = 5;
	msg.defence_flag = 4;
	player.team_id = 7;
	player1.team_id = 7;
	player2.team_id = 1;
	player3.team_id = 1;
	ft_get_resouces(&player);
	ft_get_resouces(&player1);
	ft_get_resouces(&player2);
	ft_get_resouces(&player3);
	ft_initial_the_board(&player);
	//int	ft_set_player(t_player *player, int x, int y, int team_id, int target_team_id, int player_id)
	ft_set_player(&player,  8, 5, 7, 1, 1);
	ft_set_player(&player1, 6, 5, 7, 1, 2);
	ft_set_player(&player2, 6, 4, 1, 7, 1);
	ft_set_player(&player3, 5, 4, 1, 7, 2);
	//int	ft_set_team(t_player *player, int nbr_of_players, int team_id, int init_x, int init_y, int corner, int team_index)
	ft_set_team(&player,  2, 7, 9, 9, 2, 0);
	ft_set_team(&player1, 2, 7, 9, 9, 2, 0);
	ft_set_team(&player2, 2, 1, 0, 1, 2, 1);
	ft_set_team(&player3, 2, 1, 0, 1, 2, 1);
	player.first_move = 0;
	player1.first_move = 0;
	player2.first_move = 0;
	player2.first_move = 0;
	ft_print_the_board(&player);
	
/*	int i = 0;
	while (i < 8)
	{
		ft_putstr("-------------***************----------------\n");
		printf("player position x[%d] y[%d]\n", player1.pos_x, player1.pos_y);
		ft_attack_defend_escape_moves(&player, &msg);
		//ft_attack_position(player, msg.x_defence, msg.y_defence);
		//ft_second_side_to_attack(&player, &msg);
		ft_putstr("--------------------------------------------\n");
		ft_print_the_board(&player);
		i++;
	}
*/
	printf("result : %d\n", ft_check_if_player_need_to_escape_or_died(&player));
	player.game->total_players = 0;
	ft_exit_from_game(&player, 3);
	return (0);
}
