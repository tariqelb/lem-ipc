#include "./lemipc.h"

int	ft_active_the_game_and_get_into_board(t_player *player)
{
	while (ft_is_the_game_active(player) == 0)
	{
		//0 mean game not reach minimum nbr of players and teams
	 
		printf("Game is waiting state, players nbr is %d\n", player->game->total_players);
		int n;

		n = 0;
		while (n < player->game->total_teams)
		{
			printf("Data nbr of player [%d] , team id [%d] , corner [%d]\n", player->game->teams[n].nbr_of_players, player->game->teams[n].team_id, player->game->teams[n].corner);
			n++;
		}
		sleep(5);
	}
	printf("Game started, total player nbr is %d\n", player->game->total_players);
	while (ft_get_into_board(player))
	{
		printf("Place is full , x = %d , y = %d total players %d\n", player->pos_x, player->pos_y, player->game->total_players);
		sleep(4);
		if (player->game->game_active == 0 || player->game->total_players == 1)
		{
			ft_exit_from_game(player, 3);
			return (1);
		}
	}
	return (0);
}
