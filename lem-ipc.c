#include "./lemipc.h"

int	main(int ac, char **av)
{
	t_player	player;
	t_message_queue msg;

	if (ft_get_team(ac, av[1], &player))
		return (1);
	//initialze board , get semaphore ...
	if (ft_get_resouces(&player))
		return (1);

	if (ft_active_the_game_and_get_into_board(&player))
		return (1);
	//fork and create a process that handle graphic window
	if (player.graphic_representative)
	{
		int	pid;

		pid = fork();
		if (pid == -1)
        		return (1);

		if (pid != 0)
		{
			ft_graphic_representation(&player);
			waitpid(pid, NULL, 0);
			exit(0);
			return (0);
		}
	}
	printf("Player get into board : team id %d\n", player.team_id);
	printf("Player position x = %d , y = %d\n", player.pos_x, player.pos_y);
	printf("Total players %d\n", player.game->total_players);
	printf("Total teams %d\n", player.game->total_teams);
	printf("Team color ----[%d]----\n", player.team_color);
	int attack_index = 0;
	int win;
	while (player.game->game_active == 1 && player.died == 0)
	{
		//player make move, attack , defend , escape
		printf("----------------------------------------------------[%d]\n", attack_index);
		win = ft_check_if_team_win(&player);
		if (win)
		{
			if (win == 2)
				write(1, "Lemipc: --_0_-- Better state no one win\n", 40);
			break;
		}
		printf("after----------------------------------------------------[%d]\n", attack_index);
		if (ft_scan_board_if_a_player_surrounded(&player))
		{
			printf("ft_scan_the_board_and_get_x_y_of_enemy_to_attack\n");
			if (ft_is_player_surrounded(&player))
			{
				semop(player.semid, &player.lock_op, 1);
				ft_print_the_board(&player);
				printf("Dead move\n");
				semop(player.semid, &player.unlock_op, 1);
				break;
			}
		}
		else
		{
			printf("Attack defence escape : pos x [%d] pos y [%d]\n", player.pos_x, player.pos_y);
			semop(player.semid, &player.lock_op, 1);
			ft_print_the_board(&player);
			if (ft_attack_defend_escape_moves(&player, &msg) == 1)
			{
				semop(player.semid, &player.unlock_op, 1);
				break;
			}
			ft_print_the_board(&player);
			semop(player.semid, &player.unlock_op, 1);
		}
		sleep(3);
		//temprorary break
		//break;
		printf("----------------------------------------------------[%d]\n", attack_index);
		printf("\n\n\n");
		attack_index++;
	}
	//--------------------------
	ft_exit_from_game(&player, 3);
	return (0);
}
