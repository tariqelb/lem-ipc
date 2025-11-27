#include "./lemipc.h"

int	ft_active_the_game(t_player *player)
{
	int	team_have_at_less_one_player;
	int	team_have_at_less_two_player;
	int	team_one_id;
	int	team_two_id;
	int	i;

	team_one_id = 0;
	team_two_id = 0;
	team_have_at_less_one_player = 0;
	team_have_at_less_two_player = 0;
	i = 0;
	while (i < MAX_TEAMS)
	{
		if (team_one_id == 0 && player->game->teams[i].nbr_of_players >= 1)
		{
			team_one_id = 1;
			team_have_at_less_one_player = 1;
		}
		else if (team_two_id == 0 && player->game->teams[i].nbr_of_players >= 2)
		{
			team_two_id = 1;
			team_have_at_less_two_player = 1;
		}
		i++;
	}
	if (team_have_at_less_two_player && team_have_at_less_one_player)
		player->game->game_active = 1;
	return (player->game->game_active);
}

int	ft_is_the_game_active(t_player *player)
{
	int	team_have_at_less_one_player;
	int	team_have_at_less_two_player;
	int	team_one_id;
	int	team_two_id;
	int	i;

	team_one_id = 0;
	team_two_id = 0;
	team_have_at_less_one_player = 0;
	team_have_at_less_two_player = 0;
	i = 0;
	while (i < MAX_TEAMS)
	{
		if (team_one_id == 0 && player->game->teams[i].nbr_of_players >= 1)
		{
			team_one_id = 1;
			team_have_at_less_one_player = 1;
		}
		else if (team_two_id == 0 && player->game->teams[i].nbr_of_players >= 2)
		{
			team_two_id = 1;
			team_have_at_less_two_player = 1;
		}
		i++;
	}
	if (team_have_at_less_two_player && team_have_at_less_one_player)
		return(1);
	return (0);
}
