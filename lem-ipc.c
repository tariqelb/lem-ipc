#include "./lemipc.h"

int	main(int ac, char **av)
{
	t_player	player;
	t_message_queue msg;

	if (ft_get_team(ac, av[1], &player) == -1)
		return (1);
	if (ft_check_defines())
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
	int attack_index = 0;
	int win;
	while (player.game->game_active == 1 && player.died == 0)
	{
		//player make move, attack , defend , escape
		ft_putstr("-------------new attack ----------");
		ft_putint(attack_index);
		ft_putstr("\n");
		win = ft_check_if_team_win(&player);
		if (win)
		{
			if (win == 2)
				write(1, "Lemipc: --_0_-- Better state no one win\n", 40);
			break;
		}
		if (ft_scan_board_if_a_player_surrounded(&player))
		{
			if (ft_is_player_surrounded(&player))
			{
				semop(player.semid, &player.lock_op, 1);
				ft_print_the_board(&player);
				semop(player.semid, &player.unlock_op, 1);
				break;
			}
		}
		else
		{
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
		sleep(DELAY);
		ft_putstr("-----------------------------------------\n");
		attack_index++;
	}
	//--------------------------
	ft_exit_from_game(&player, 3);
	return (0);
}
