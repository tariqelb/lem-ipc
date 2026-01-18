#include "./lemipc.h"

int	ft_active_the_game_and_get_into_board(t_player *player)
{
	while (ft_is_the_game_active(player) == 0)
	{
		//0 mean game not reach minimum nbr of players and teams
	 
		ft_putstr("Game is waiting state, players nbr is ");
		ft_putint(player->game->total_players);
		ft_putstr("\n");
		int n;

		n = 0;
		while (n < player->game->total_teams)
		{
			ft_putstr("Data nbr of player [");
			ft_putint( player->game->teams[n].nbr_of_players);
			ft_putstr("] , team id [");
			ft_putint(player->game->teams[n].team_id);
			ft_putstr("] , corner [");
			ft_putint(player->game->teams[n].corner);
			ft_putstr("]\n");
			n++;
		}
		sleep(DELAY);
	}
	ft_putstr("Game started, total player nbr is ");
	ft_putint(player->game->total_players);
	ft_putstr("\n");
	while (ft_get_into_board(player))
	{
		ft_putstr("Place is full , x = ");
		ft_putint(player->pos_x);
		ft_putstr(" , y = ");
		ft_putint(player->pos_y);
		ft_putstr(" total players ");
		ft_putint(player->game->total_players);
		ft_putstr("\n");
		sleep(DELAY);
		if (player->game->game_active == 0 || player->game->total_players == 1)
		{
			ft_exit_from_game(player, 3);
			return (1);
		}
	}
	return (0);
}
