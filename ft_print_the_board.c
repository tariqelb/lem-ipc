#include "./lemipc.h"

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
