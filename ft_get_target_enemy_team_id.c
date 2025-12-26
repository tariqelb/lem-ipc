#include "./lemipc.h"

int	ft_get_target_enemy_team_id(t_player *player)
{
	int	i;
	int	prev_id;
	int	next_id;
	int enemy_id;

	//target team is the team who have next or previews (if no next exist) id number
	//my team id is 8 and other teams ids are ex(1 4 12 77) , my target enemy team is 12 

	enemy_id = -1;
	prev_id = -1;
	next_id = -1;
	i = 0;
	while (i < MAX_TEAMS)
	{
		if (player->game->teams[i].nbr_of_players > 0)
		{
			enemy_id = player->game->teams[i].team_id; 
			if (enemy_id != player->team_id)
			{
				if (enemy_id < player->team_id)
				{
					if (prev_id == -1)
						prev_id = enemy_id;
					else if (prev_id < enemy_id)
						prev_id = enemy_id;
				}
				else if (enemy_id > player->team_id)
				{
					if (next_id == -1)
						next_id = enemy_id;
					else if (next_id > enemy_id)
						next_id = enemy_id;
				}
			}
		}
		i++;
	}

	if (prev_id != -1)
		player->target_team_id = prev_id;
	if (next_id != -1)
		player->target_team_id = next_id;
	return (player->target_team_id);
}
