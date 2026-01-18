#include "./lemipc.h"

void	ft_display_the_board(int board[BOARD_Y_LEN][BOARD_X_LEN])
{
	ft_putstr("ft_display_the_board\n");
	int	i;
	int	j;

	ft_putstr(" _________");
	i = 0;
	while (i++ < BOARD_X_LEN)
		ft_putstr("___");
	ft_putstr("_ \n");
	ft_putstr("| [x/y] | ");
	i = 0;
	while (i < BOARD_X_LEN)
	{
		ft_putstr("[");
		ft_putint(i);
		ft_putstr("]");
		i++;
	}
	ft_putstr(" |\n");
	ft_putstr("|_______|_");
	i = 0;
	while (i++ < BOARD_X_LEN)
		ft_putstr("___");
	ft_putstr("_|\n");
	i = 0;
	while (i < BOARD_Y_LEN)
	{
		ft_putstr("|  [");
		ft_putint(i);
		ft_putstr("]  | ");
		j = 0;
		while (j < BOARD_X_LEN)
		{
			ft_putstr("[");
			ft_putint(board[i][j]);
			ft_putstr("]");
			j++;
		}
		ft_putstr(" |\n");
		i++;
	}
	ft_putstr("|_______|_");
	i = 0;
	while (i++ < BOARD_X_LEN)
		ft_putstr("___");
	ft_putstr("_|\n");
}


