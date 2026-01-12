#include "./lemipc.h"

void	ft_display_the_board(int board[BOARD_Y_LEN][BOARD_X_LEN])
{
	printf("ft_display_the_board\n");
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
			printf("[%d]", board[i][j]);
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


