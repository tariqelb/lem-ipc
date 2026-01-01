#include "./lemipc.h"

int	main(int ac, char **av)
{
	t_player	player;

	if (ac != 2)
	{
		write(2, "Lemipc : Missing player team\n", 29);
		write(2, "Usage: ./lemipc [1 - N]\n", 24);
		return (1);
	}
	//initialize semaphore locks
	ft_initialize_semaphore_struct(&player);
	player.team_id = ft_get_team(av[1]);
	if (player.team_id == 0)
		return (1);
	//allocate memory for game board
	/*player.game = NULL;
	player.game->board = (int *) malloc(sizeof(int) * BOARD_Y_LEN * BOARD_X_LEN);
	if (player.game->board == NULL)
	{
		write(2, "Lemipc : Error, fail to allocate memory for player board\n", 57);
		return (1);
	}*/
	//Implement semaphore system for synchronization
	if (ft_create_semaphore(&player))
	{
		return (1);
	}
	//Create shared memory segment for game board 
	//Attach board to shared memory , first player
	//Get access to shared memory for other players
	if (ft_create_shared_memory(&player))
	{
		ft_exit_from_game(&player, 1);
		return (1);
	}
	//Set up message queues for inter-process communication
	if (ft_create_message_queue(&player))
	{
		ft_exit_from_game(&player, 2);
		return (1);
	}
	//Turn game to active state
	if (ft_active_the_game(&player) == 0)
		ft_exit_from_game(&player, 3);
	while (ft_is_the_game_active(&player) == 0)
	{
		//0 mean game not reach minimum nbr of players and teams

		printf("Game is waiting state, players nbr is %d\n", player.game->total_players);
		int n;

		n = 0;
		while (n < player.game->total_teams)
		{
			printf("Data nbr of player [%d] , team id [%d] , corner [%d]\n", player.game->teams[n].nbr_of_players, player.game->teams[n].team_id, player.game->teams[n].corner);
			n++;
		}
		sleep(5);
	}
	printf("Game started, total player nbr is %d\n", player.game->total_players);
	while (ft_get_into_board(&player))
	{
		printf("Place is full , x = %d , y = %d total players %d\n", player.pos_x, player.pos_y, player.game->total_players);	
		sleep(4);
		if (player.game->game_active == 0 || player.game->total_players == 1)
		{
			ft_exit_from_game(&player, 3);
			return (0);
		}
	}
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
	while (player.game->game_active == 1 && player.died == 0)
	{
		//player make move, attack , defend , escape
		printf("----------------------------------------------------[%d]\n", attack_index);
		printf("Attack defence escape : pos x [%d] pos y [%d]\n", player.pos_x, player.pos_y);
		semop(player.semid, &player.lock_op, 1);
		ft_print_the_board(&player);
		if (ft_check_if_team_win(&player))
		{
			semop(player.semid, &player.unlock_op, 1);
			break;
		}
		if (ft_attack_defend_escape_moves(&player) == 1)
		{
			semop(player.semid, &player.unlock_op, 1);
			break;
		}
		semop(player.semid, &player.unlock_op, 1);
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
