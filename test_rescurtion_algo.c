#include "./lemipc.h"


int	ft_initial_the_board(t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < BOARD_Y_LEN)
	{
		j = 0;
		while (j < BOARD_X_LEN)
		{
			player->game->board[i][j] = 0;
			if (i == 1 && j == 1)//place an enemy
				player->game->board[i][j] = 4;
			if (i == 3 && j == 3)//enemy
				player->game->board[i][j] = 2;
			//if (i == 2 && j == 2)//enemy
			//	player->game->board[i][j] = 3;
			//if (i == 3 && j == 4)//enemy
			//	player->game->board[i][j] = 3;
			//if (i == 3 && j == 3)//enemy
			//	player->game->board[i][j] = 6;
			if (i == 0 && j == 0)//player + 1
				player->game->board[i][j] = 3;
			if (i == 2 && j == 4)//player + 1
				player->game->board[i][j] = 3;
			//if (i == 4 && j == 5)//enemy
			//	player->game->board[i][j] = 6;
			//if (i == 5 && j == 2)//enemy
			//	player->game->board[i][j] = 6;
			//if (i == 6 && j == 3)//enemy
			//	player->game->board[i][j] = 6;
			j++;
		}
		i++;
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

/*
void	ft_print_the_board(t_player *player)
{
	int	i;
	int	j;
	
	printf(" _________");
	i = 0;
	while (i++ < BOARD_X_LEN)
		printf("___");
	printf("_ \n");
	printf("| [x/y] | ");
	i = 0;
	while (i < BOARD_X_LEN)
		printf("[%d]", i++);
	printf(" |\n");
	printf("|_______|_");
	i = 0;
	while (i++ < BOARD_X_LEN)
		printf("___");
	printf("_|\n");
	i = 0;
	while (i < BOARD_Y_LEN)
	{
		printf("|  [%d]  | ", i);
		j = 0;
		while (j < BOARD_X_LEN)
		{
			printf("[%d]", player->game->board[i][j]);
			j++;
		}
		printf(" |\n");
		i++;
	}
	printf("|_______|_");
	i = 0;
	while (i++ < BOARD_X_LEN)
		printf("___");
	printf("_|\n");
}
*/

int	main(void)
{
	t_player	player;
	t_message_queue	msg;

	player.game = malloc(sizeof(t_game));

	ft_initial_the_board(&player);

	player.team_id = 2;
	player.player_id = 1;
	player.pos_x = 0;
	player.pos_y = 0;
	player.path[0] = -1;
	player.path[1] = -1;
	player.path[2] = -1;
	player.path[3] = -1;
	//player.find_x = 3;
	//player.find_y = 1;
	//msg.x_attack = 0;
	//msg.y_attack = 2;
	ft_print_the_board(&player);
	
	//printf("Position (%d,%d) is [%d]\n",
	//	 2, 1 ,ft_check_position_is_safe(&player, 2, 1));
	//printf("Position (%d,%d) is [%d]\n",
	//	 1, 2 ,ft_check_position_is_safe(&player, 1, 2));
	//printf("Position (%d,%d) is [%d]\n",
	//	 -1, 2 ,ft_check_position_is_safe(&player, -1, 2));
	//int status = ft_find_path_to_position(&player);
	//printf("Status : %d\n", status);
	/*int status = ft_choose_one_side_to_attack(&player, 2, 3);
	printf("status : %d\n", status);
	printf("is it one step : %d\n", ft_is_one_step_to_position(&player, msg, 0));
	printf("is it one step : %d\n", ft_is_one_step_to_position(&player, msg, 1));
	printf("is it one step : %d\n", ft_is_one_step_to_position(&player, msg, 2));
	printf("is it one step : %d\n", ft_is_one_step_to_position(&player, msg, 3));
	*/

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
