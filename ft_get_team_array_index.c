#include "lemipc.h"

int	ft_get_team_array_index(t_player *player)
{
	printf("ft_get_team_array_index\n");
	int	i;

	i = 0;
	while (i < MAX_TEAMS)
	{
		if (player->team_id == player->game->teams[i].team_id)
			return (i);
		i++;
	}
	return (-1);
}
