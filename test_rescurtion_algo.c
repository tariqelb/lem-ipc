#include "./lemipc.h"


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
			if (x == 5 && y == 2)//place an enemy
				player->game->board[y][x] = 8;
			if (x == 5 && y == 3)//enemy
				player->game->board[y][x] = 8;
			if (x == 6 && y == 4)//enemy
				player->game->board[y][x] = 8;
			if (x == 6 && y == 3)//enemy
				player->game->board[y][x] = 4;
			//if (i == 3 && j == 3)//enemy
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
	msg.x_attack = 6;
	msg.y_attack = 3;
	msg.x_defence = 5;
	msg.y_defence = 2;
	msg.x_player = 6;
	msg.y_player = 4;
	msg.defence_flag = 0;
	player.team_id = 3;
	player1.team_id = 7;
	player2.team_id = 7;
	player3.team_id = 7;
	ft_get_resouces(&player);
	ft_get_resouces(&player1);
	ft_get_resouces(&player2);
	ft_get_resouces(&player3);
	ft_initial_the_board(&player);
	ft_set_player(&player,  6, 3, 3, 7, 1);
	ft_set_player(&player1, 5, 3, 7, 3, 1);
	ft_set_player(&player2, 5, 2, 7, 3, 2);
	ft_set_player(&player3, 6, 4, 7, 3, 3);
	ft_set_team(&player,  1, 3, 9, 9, 2, 0);
	ft_set_team(&player1, 3, 7, 0, 1, 2, 1);
	ft_set_team(&player2, 3, 7, 0, 1, 2, 1);
	ft_set_team(&player3, 3, 7, 0, 1, 2, 1);
	player.first_move = 0;
	player1.first_move = 0;
	player2.first_move = 0;
	player2.first_move = 0;
	ft_print_the_board(&player);
	
	int i = 0;
	while (i < 8)
	{
		printf("-------------***************----------------\n");
		printf("player position x[%d] y[%d]\n", player1.pos_x, player1.pos_y);
		ft_attack_defend_escape_moves(&player1, &msg);
		//ft_attack_position(player, msg.x_defence, msg.y_defence);
		//ft_second_side_to_attack(&player, &msg);
		printf("--------------------------------------------\n");
		ft_print_the_board(&player);
		i++;
	}
	player.game->total_players = 0;
	ft_exit_from_game(&player, 3);
	return (0);
}
