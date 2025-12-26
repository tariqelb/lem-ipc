#include "./lemipc.h"

int	ft_scan_the_board_and_get_x_y_of_enemy_to_attack(t_player *player, int *enemy_x, int *enemy_y, int *enemy_team_id)
{
	int	y_bottom_index;
	int	y_top_index;
	int	i;
	int	j;
	int	y_max;
	int	x_max;
	

	//easest way scan the board from side to middle and update xy of enemy found and return last one close to middle 
	*enemy_team_id = -1;

	i = 0;
	y_bottom_index = BOARD_Y_LEN - 1;
	y_top_index  = 0;
	y_max = BOARD_Y_LEN / 2 + BOARD_Y_LEN % 2;
	//printf("Indexs : %d %d\n", i ,  y_max);
	while (i < y_max)
	{
		//printf("in index : %d %d %d %d\n", i, y_top_index, y_bottom_index, y_max);
		//scan top horizental side
		if (i == y_top_index)
		{
			j = i;
			x_max = j;
			while (j < BOARD_X_LEN - x_max)
			{
				//printf("x = (%d, %d) ", j, y_top_index);
				if (player->game->board[y_top_index][j] != 0 && player->game->board[y_top_index][j] != player->team_id + 1 && player->game->board[y_top_index][j] == player->target_team_id + 1)
				{
					*enemy_x = j;
					*enemy_y = y_top_index;
					*enemy_team_id = player->game->board[y_top_index][j];
					//printf("\n--------------------------------------------Enemy : (%d, %d) [%d]-- \n", j, y_top_index, *enemy_team_id);
				}
				j++;
			}
			//printf("\n");
		
		}
		//scan bottom hozental side
		if (BOARD_Y_LEN - 1 - i == y_bottom_index)
		{
			j = y_top_index;
			x_max = BOARD_X_LEN - j;	
			//printf("In index : %d %d %d\n", j, y_top_index, x_max);
			while (j < x_max)
			{
				//printf("x2 = (%d, %d) ", j, y_bottom_index);
				if (player->game->board[y_bottom_index][j] != 0 && player->game->board[y_bottom_index][j] != player->team_id + 1 && player->game->board[y_bottom_index][j] == player->target_team_id + 1)
				{
					*enemy_x = j;
					*enemy_y = y_bottom_index;
					*enemy_team_id = player->game->board[y_bottom_index][j];
				//	printf("\n--------------------------------------------Enemy : (%d, %d) [%d]-- \n", j, y_bottom_index, enemy_team_id);
				}
				j++;
			}
			printf("\n");
		}
		//scan vertical left side
		{
			int v_left_min;
			int v_left_max;
			int v_left_x;

			v_left_x = y_top_index;
			v_left_min = y_top_index + 1;
			v_left_max = y_bottom_index - 1;
			while (v_left_min <= v_left_max)
			{
				//printf("l-y = (%d, %d) ", v_left_x, v_left_min);
				if (player->game->board[v_left_min][v_left_x] != 0 && player->game->board[v_left_min][v_left_x] != player->team_id + 1 && player->game->board[v_left_min][v_left_x] == player->target_team_id + 1)
				{
					*enemy_x = v_left_x;
					*enemy_y = v_left_min;
					*enemy_team_id = player->game->board[v_left_min][v_left_x];
					//printf("\n----------------------------------------------Enemy : (%d, %d) [%d]-- \n", v_left_x ,v_left_min, enemy_team_id);
				}
				v_left_min++;
			}
			//printf("\n");
		}
		//scan vertical right side
		{
			int v_right_min;
			int v_right_max;
			int v_right_x;

			v_right_x = BOARD_X_LEN - 1 - y_top_index;
			v_right_min = y_top_index + 1;
			v_right_max = y_bottom_index - 1;
			while (v_right_min <= v_right_max)
			{
				//printf("r-y = (%d, %d)", v_right_x, v_right_min);
				if (player->game->board[v_right_min][v_right_x] != 0 && player->game->board[v_right_min][v_right_x] != player->team_id + 1 && player->game->board[v_right_min][v_right_x] == player->target_team_id + 1)
				{
					*enemy_x = v_right_x;
					*enemy_y = v_right_min;
					*enemy_team_id = player->game->board[v_right_min][v_right_x];
					//printf("\n----------------------------------------------Enemy : (%d, %d) [%d]-- \n", v_right_x, v_right_min, enemy_team_id);
				}
				v_right_min++;
			}
			//printf("\n");
		}

		i++;
		y_top_index++;
		y_bottom_index--;
	}
	//printf("--------------------------\n");
	//printf("Enemy closest to center is with team id : %d , and coordinate : (%d, %d)\n", enemy_team_id, enemy_x, enemy_y);
	//printf("--------------------------\n");
	return (*enemy_team_id);
}
