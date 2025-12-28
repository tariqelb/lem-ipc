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
			if (x == 1 && y == 2)//place an enemy
				player->game->board[y][x] = 4;
			if (x == 1 && y == 4)//enemy
				player->game->board[y][x] = 3;
			//if (i == 2 && j == 2)//enemy
			//	player->game->board[y][x] = 3;
			//if (i == 3 && j == 4)//enemy
			//	player->game->board[y][x] = 3;
			//if (i == 3 && j == 3)//enemy
			//	player->game->board[y][x] = 6;
			if (x == 1 && y == 5)//player + 1
				player->game->board[y][x] = 3;
			if (x == 4 && y == 1)//player + 1
				player->game->board[y][x] = 2;
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
	player->game->total_players = 6;
	player->game->total_teams = 2;
	player->game->game_active = 1;
	player->game->teams[0].nbr_of_players = 2;
	player->game->teams[0].team_id = 1;
	player->game->teams[0].init_x = 0;
	player->game->teams[0].init_y = 2;
	player->game->teams[0].corner = 2;
	player->game->teams[1].nbr_of_players = 4;
	player->game->teams[1].team_id = 2;
	player->game->teams[1].init_x = 4;
	player->game->teams[1].init_y = 0;
	player->game->teams[1].corner = 4;
	return (0);
}


int	main(void)
{
	t_player	player;
	t_message_queue	msg;

	player.game = malloc(sizeof(t_game));

	ft_initial_the_board(&player);

	player.team_id = 2;
	player.target_team_id = 3;
	player.player_id = 1;
	player.pos_x = 1;
	player.pos_y = 4;
	player.path[0] = -1;
	player.path[1] = -1;
	player.path[2] = -1;
	player.path[3] = -1;
	//player.find_x = 3;
	//player.find_y = 1;
	//msg.x_attack = 0;
	//msg.y_attack = 2;
	ft_print_the_board(&player);
	

	ft_calculate_push_new_attack(&player, &msg);
	printf("Enemy pos [%d][%d]\n", msg.x_attack, msg.y_attack);
	ft_find_path_to_position_and_make_move(&player, msg.x_attack, msg.y_attack);
	printf("------------------------------------\n");
/*	ft_calculate_push_new_attack(&player, &msg);
	printf("Enemy pos [%d][%d]\n", msg.x_attack, msg.y_attack);
	ft_find_path_to_position_and_make_move(&player, msg.x_attack, msg.y_attack);
*/	printf("------------------------------------\n");

	
	return (0);
}
